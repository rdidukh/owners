#include "Matrix.h"
#include "TestFramework.h"

#include <sstream>
#include <vector>
#include <string>
#include <cassert>

std::istream & Matrix::readFromStream(std::istream & is)
{
	assert(is.good());
	mtx.clear();
	unsigned rows, cols;
	failBit = true;

	is >> rows;
	if(is.fail())
		return is;

	is >> cols;
	if(is.fail())
		return is;

	double val;

	mtx.resize(rows, std::vector<double>(cols));
	for(auto & row : mtx)
	{
		for(auto & cell : row)
		{
			is >> val;
			if(is.fail())
			{
				mtx.clear();
				return is;
			}
			cell = val;
		}
	}

	failBit = false;
	return is;
}

Matrix::Matrix(unsigned rows, unsigned cols) :
	mtx(rows, std::vector<double>(cols)),
	failBit(false)
{
}

std::vector<double>& Matrix::operator[](size_t index)
{
	return mtx[index];
}

const std::vector<double>& Matrix::operator[](size_t index) const
{
	return mtx[index];
}

std::istream & operator >> (std::istream & is, Matrix & matrix)
{
	return matrix.readFromStream(is);
}

bool Matrix::fail() const
{
	return failBit;
}

unsigned Matrix::rows() const
{
	return  mtx.size();
}

unsigned Matrix::cols() const
{
	if(mtx.empty())
		return 0;
	return mtx[0].size();
}

std::vector<std::vector<double>>::iterator Matrix::begin()
{
	return mtx.begin();
}

std::vector<std::vector<double>>::iterator Matrix::end()
{
	return mtx.end();
}

std::vector<std::vector<double>>::const_iterator Matrix::begin() const
{
	return mtx.cbegin();
}

std::vector<std::vector<double>>::const_iterator Matrix::end() const
{
	return mtx.cend();
}
