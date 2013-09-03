#pragma once
#ifndef _COMPLEXA_H
#define _COMPLEXA_H

class Complex {
public:
	Complex(double = 0.0, double = 0.0);
	Complex operator+(const Complex &) const;
	Complex operator-(const Complex &) const;
	const Complex &operator=(const Complex &);
	void print() const;
private:
	double real;
	double imaginary;
};
#endif