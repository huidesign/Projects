#include <iostream>
using std::cout;
#include "complexA.h"

//Constructor
Complex::Complex(double r, double i)
	: real(r), imaginary(i) {}

//Overloaded addition operator
Complex Complex::operator+(const Complex &operand2) const
{
	return Complex(real + operand2.real, imaginary + operand2.imaginary);
}

//overloaded subtraction operator
Complex Complex::operator-(const Complex &operand2) const
{
	return Complex(real - operand2.real, imaginary - operand2.imaginary);
}

//overloaded assign operator
const Complex& Complex::operator=(const Complex &right)
{
	real = right.real;
	imaginary = right.imaginary;
	return *this;		//enable cascading
}

//Display a Complex object in the form: (a, b)
void Complex::print() const
{
	cout << '(' << real << " ," << imaginary << ')'; 
}