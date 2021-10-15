// Assignment 6.1, Ethan Heil

#include <iostream>

extern "C" void asmMain();
extern "C" int getInput();
extern "C" void printResult(int result);

// Main
int main() 
{
	// Call main assembly function
	asmMain();
	system("pause");
	return 0;
}

// Get input from user
int getInput() 
{
	int num = 0;

	std::cout << "Enter Number: " << std::endl;
	std::cin >> num;

	return num;
}

// Print result of sum
void printResult(int result) 
{
	printf("\nSum = %i\n", result);
}