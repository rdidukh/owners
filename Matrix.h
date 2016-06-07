#pragma once

#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <fstream>
#include <vector>

class Matrix
{
public:
	Matrix(unsigned rows = 0, unsigned cols = 0);
    Matrix(unsigned rows, unsigned cols, double defaultValue);

	std::vector<double> & operator[](size_t index);
    bool operator==(const Matrix & rhs) const;

	const std::vector<double> & operator[](size_t index) const;
	friend std::istream & operator >> (std::istream & is, Matrix & matrix);
	bool fail() const;
	unsigned rows() const;
	unsigned cols() const;

	/* Support range-based for loop */
	std::vector<std::vector<double>>::iterator begin();
	std::vector<std::vector<double>>::iterator end();
	std::vector<std::vector<double>>::const_iterator begin() const;
	std::vector<std::vector<double>>::const_iterator end() const;

	static bool test();

private:
	std::istream & readFromStream(std::istream & is);

	static bool readFromStreamTest();

	/* private members */
	std::vector<std::vector<double>> mtx;
	bool failBit;
};

#endif // FILE_MATRIX_H