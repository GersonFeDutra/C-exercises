#include <stdio.h>


int main() {
	float salary = 1500;
	printf("Your salary was R$%f.\n", salary);
	salary += salary * 0.1;
	printf("The new salary, with increase, is: R$%f", salary);
	return 0;
}

