#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

/* 
    Задание.
    Warcraft. Заданное количество юнитов добывают золото равными порциями 
    из одной шахты, задерживаясь в пути на случайное время, до ее истощения. 
    Работа каждого юнита реализуется в порожденном процессе.
*/

/*  
    Программа ждет ввода количества юнитов, размера шахты и порции золота для юнита.
    Затем происходит инициализация и выделение памяти под необходимые переменные.
    Когда все готово, то создаем потоки.
    Юниты должны дойти с базы до шахты за случайное время delay_time, поработать и придти обратно на базу тоже за случайное delay_time.
    Работа идет пока шахта не будет пуста.
*/

static int mineSize = 0; /* Переменная, хранящая величину золота в шахте. */ 

/* Структура, хранящая данные, которые будут использовать юниты.*/
typedef struct
{
    unsigned int gold_portion;  /* Порция золота, которую добывает юнит из шахты.*/
    unsigned int delay_time;    /* Время, на которое случайно задерживается в пути юнит. */ 
    pthread_mutex_t* mutex;     /* Указатель на общий для всех юнитов мьютекс.*/
} unit;

/* Генератор случайной задержки юнита в пути. */
int randDelayTime()
{
    srand(time(NULL));
    return rand() % 2 + 1; /* Генерируем случайную задержку в пути из диапозона от 1 до 2. */
}

/* Функция добывания золота из шахты. */
void* goldMining(void* thread_data)
{
    pid_t tid = pthread_self();
    unit* un = (unit*)thread_data;
    /* Юниты работают пока шахта не будет истощена. */
    while(mineSize != 0)
    {
        /* Ушел на шахту из базы. */ 
        un->delay_time = randDelayTime();
        sleep(un->delay_time);

        /* Зашел в шахту и начал работать. */ 
        pthread_mutex_lock(un->mutex);
        if(mineSize == 0) {
        pthread_mutex_unlock(un->mutex);
        break;
        };
        if(mineSize < un->gold_portion) mineSize -= mineSize;
        else mineSize -= un->gold_portion;
        printf("Tid: %i. Количество золота в шахте: %i. \n", tid, mineSize);

        /* Поработал, освободил шахту и пошел относить золото на базу. */
        pthread_mutex_unlock(un->mutex);
        un->delay_time = randDelayTime();
        sleep(un->delay_time);
    }
    return NULL;
}

int main()
{
    pthread_mutex_t mutex;     /* Мютекс для синхронизации обращения к переменной шахты (mine). */
    int numOfUnits = 0;   /* Число юнитов. */ 
    int gold_portion = 0; /* Порция золота, которую добывает юнит из шахты.  */
    pthread_t* th_id;          /* Идентификаторы потоков */
    unit* units;               /* Структура с данными для юнита */
    /* Запрашиваем первоначальные условия для задачи.*/
    do
    {
        printf("Введите число юнитов: ");
        scanf("%i", &numOfUnits);
    } while(numOfUnits == 0);

    do 
    {
        printf("Введите количество золота шахты: ");
        scanf("%i", &mineSize);
    } while(mineSize == 0);

    do
    {
    printf("Введите размер порции золота для юнитов: ");
    scanf("%i", &gold_portion);
    } while(gold_portion == 0);

    /* Инициализируем мьютекс значениями по умолчанию. */
    pthread_mutex_init(&(mutex), NULL);

    /* Выделяем память под юнитов. */
    units = calloc(numOfUnits, sizeof(units));

    /* Выделяем память под идентифкаторы потоков. */
    th_id = calloc(numOfUnits, sizeof(pthread_t));


    /* Инициализируем юнитов. */ 
    for(int i = 0; i < numOfUnits; i++)
    {
        units[i].gold_portion = gold_portion;
        units[i].mutex = &mutex;
    }

    printf("Количество золота в шахте до прибытия юнитов: %i. \n", mineSize);


    /* Отправляем наших юнитов на работу в шахту. */
    for(size_t i = 0; i < numOfUnits; i++)
        pthread_create(&th_id[i], NULL, goldMining, units);
        
    /* Ожидаем возвращения наших юнитов, опустошивших шахту. */
    for (int i = 0; i < numOfUnits; i++)
        pthread_join(th_id[i], NULL);

    /* Уничтожаем мьютекс. */
    pthread_mutex_destroy(&(mutex));

    printf("Количество золота в шахте после прибытия юнитов: %i. \n", mineSize);

    free(units);
    return 0;
}
