#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

// описываем функцию f1() как внешнюю
extern int sum();

// описываем функцию sub() как внешнюю
extern int sub();

int main(int argc, char *argv[])
{
	void *library_handler; // хандлер внешней библиотеки
	int num1, num2;
	int (*sum)(int, int);	// переменная для хранения адреса функции
	int (*sub)(int, int);
	
	if (argc == 1)
	{
		num1 = num2 = 2; 	
	}
	else
	{
		sscanf(argv[1], "%d", &num1);
		sscanf(argv[2], "%d", &num2);
	}
	
	//загрузка библиотеки
	library_handler = dlopen("./libdyn.so",RTLD_LAZY);
	if (!library_handler){
	// если ошибка, то вывести ее на экран
	fprintf(stderr,"dlopen() error: %s\n", dlerror());
	exit(1); // в случае ошибки можно, например, закончить работу программы
	};
	
	sum = dlsym(library_handler, "sum");
	sub = dlsym(library_handler, "sub");
	//value=3.0;
	
	printf("%d + %d = %d\n",num1,num2,(sum)(num1,num2));
	printf("%d - %d = %d\n",num1,num2,(sub)(num1,num2));

	dlclose(library_handler);
	return 0;
}
