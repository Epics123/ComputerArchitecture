// Ethan Heil, Assignment 9.1

#include <iostream>

void getInput(float &a, float &b);
void printFloat(float num);

int main()
{
	float a = 0, b = 0;
	float res1 = 0, res2 = 0, res3 = 0;

	getInput(a, b);

	// floating point addition
	__asm 
	{
		finit
		fld a
		fld b
		fadd ST(0), ST(1)
		fstp res1
	}

	// floating point multiplication
	__asm
	{
		fld a
		fld b
		fmul ST(0), ST(1)
		fstp res2
	}

	// floating point division
	__asm
	{
		fld a
		fld b
		fdiv ST(0), ST(1)
		fstp res3
	}

	printf("Addition\n");
	printFloat(res1);
	printf("\n");
	printf("Multiplication\n");
	printFloat(res2);
	printf("\n");
	printf("Division\n");
	printFloat(res3);

	system("pause");

	return 0;
}

void getInput(float &a, float &b)
{
	std::cout << "Enter first number: ";
	std::cin >> a;
	printf("\n");

	std::cout << "Enter second number:";
	std::cin >> b;
	printf("\n");
}

void printFloat(float num)
{
	printf("Result: %f\n", num);
}