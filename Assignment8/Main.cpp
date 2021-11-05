// Ethan Heil, Assignment 8.1

#include <iostream>
using namespace std;

extern "C" void _asmMain();

extern "C" double _getDouble()
{
	double d;
	std::cin >> d;
	return d;
}

extern "C" void _printString(char* s)
{
	std::cout << s;
	return;
}

extern "C" void _printDouble(double d)
{
	std::cout << d << std::endl;
}

int main()
{
	_asmMain();
	return 0;
}