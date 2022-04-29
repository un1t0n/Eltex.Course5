#include <stdio.h>

// описываем функцию f1() как внешнюю
extern int sum();

// описываем функцию sub() как внешнюю
extern int sub();

int main(int argc, char **argv)
{
	int num1, num2;
	
	if (argc == 1)
	{
		num1 = num2 = 2; 	
	}
	else
	{
		sscanf(argv[1], "%d", &num1);
		sscanf(argv[2], "%d", &num2);
	}
	printf("%d + %d = %d\n",num1,num2,sum(num1,num2));
	printf("%d - %d = %d\n",num1,num2,sub(num1,num2));

	return 0;
}
