#include "Matrix.h"
#include "TestFramework.h"
#include <string>
#include <sstream>

bool Matrix::readFromStreamTest()
{
	std::istringstream iss;
	Matrix matrix(0, 0);
	auto & mtx = matrix.mtx;
	bool ret;

	auto test = [&matrix, &iss, &ret](const std::string & str)
	{
		matrix.mtx.clear();
		iss.clear();
		iss.str(str);
		matrix.readFromStream(iss);
	};

	test("1 1");
	ASSERT_TRUE(matrix.failBit);

	test("1 1 0.5");
	ASSERT_FALSE(matrix.failBit);
	ASSERT_EQ(1, mtx.size());
	ASSERT_EQ(1, mtx[0].size());
	ASSERT_FLOAT_EQ(0.5, mtx[0][0], 0.001);

	test("1 2 0.5");
	ASSERT_TRUE(matrix.failBit);
	ASSERT_EQ(0, mtx.size());

	test("3 1 0.5 0.7");
	ASSERT_TRUE(matrix.failBit);
	ASSERT_EQ(0, mtx.size());

	test("2 1 0.5 0.7");
	ASSERT_FALSE(matrix.failBit);
	ASSERT_EQ(2, mtx.size());
	ASSERT_EQ(1, mtx[0].size());
	ASSERT_EQ(1, mtx[1].size());
	ASSERT_FLOAT_EQ(0.5, mtx[0][0], 0.001);
	ASSERT_FLOAT_EQ(0.7, mtx[1][0], 0.001);

	test("1 2 0.5 0.7");
	ASSERT_FALSE(matrix.failBit);
	ASSERT_EQ(1, mtx.size());
	ASSERT_EQ(2, mtx[0].size());
	ASSERT_FLOAT_EQ(0.5, mtx[0][0], 0.001);
	ASSERT_FLOAT_EQ(0.7, mtx[0][1], 0.001);

	test("3 3 0.1 0.2 0.3   .4 0 0.6   1 0.8 1.0");
	ASSERT_FALSE(matrix.failBit);
	ASSERT_EQ(3, mtx.size());
	ASSERT_EQ(3, mtx[0].size());
	ASSERT_EQ(3, mtx[1].size());
	ASSERT_EQ(3, mtx[2].size());
	ASSERT_FLOAT_EQ(0.1, mtx[0][0], 0.001);
	ASSERT_FLOAT_EQ(0.2, mtx[0][1], 0.001);
	ASSERT_FLOAT_EQ(0.3, mtx[0][2], 0.001);
	ASSERT_FLOAT_EQ(0.4, mtx[1][0], 0.001);
	ASSERT_FLOAT_EQ(0.0, mtx[1][1], 0.001);
	ASSERT_FLOAT_EQ(0.6, mtx[1][2], 0.001);
	ASSERT_FLOAT_EQ(1.0, mtx[2][0], 0.001);
	ASSERT_FLOAT_EQ(0.8, mtx[2][1], 0.001);
	ASSERT_FLOAT_EQ(1.0, mtx[2][2], 0.001);

	mtx.push_back(std::vector<double>());
	iss.clear();
	iss.str("0 0");
	matrix.readFromStream(iss);
	ASSERT_FALSE(matrix.failBit);
	ASSERT_TRUE(mtx.empty());

	return true;
}

bool Matrix::test()
{
	bool ret = true;
	ret &= Matrix::readFromStreamTest();
	return ret;
}
