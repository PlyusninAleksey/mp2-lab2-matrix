#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	int* arr = new int[5] { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);

	delete[] arr;

	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		m[i] = v;
	}

	TDynamicMatrix<int> mCopy(10);
	mCopy = m;

	ASSERT_EQ(mCopy, m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	int* arr = new int[5] { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);

	delete[] arr;

	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		m[i] = v;
	}

	TDynamicMatrix<int> mCopy(10);
	mCopy = m;
	mCopy[0][0] = 100;

	ASSERT_NE(mCopy, m);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	ASSERT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	m[0][0] = 1;
	ASSERT_EQ(m[0][0], 1);
}

//TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
//{
//	TDynamicMatrix<int> m(5);
//	ASSERT_ANY_THROW(m[-10] = 10);
//}

//TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
//{
//	TDynamicMatrix<int> m(5);
//	ASSERT_ANY_THROW(m[MAX_MATRIX_SIZE + 1] = 10);
//}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	int* arr = new int[5] { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);

	delete[] arr;

	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		m[i] = v;
	}

	TDynamicMatrix<int> mCopy(5);
	mCopy = m;

	ASSERT_EQ(mCopy, m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	int* arr = new int[5] { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);

	delete[] arr;

	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		m[i] = v;
	}

	TDynamicMatrix<int> mCopy(10);
	mCopy = m;

	ASSERT_EQ(mCopy.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	int* arr = new int[5] { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);

	delete[] arr;

	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		m[i] = v;
	}

	TDynamicMatrix<int> mCopy(10);
	mCopy = m;

	ASSERT_EQ(mCopy, m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	int* arr = new int[5] { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);

	delete[] arr;

	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
	{
		m[i] = v;
	}

	TDynamicMatrix<int> mCopy(m);

	ASSERT_EQ(mCopy == m, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);
	ASSERT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(10);
	TDynamicMatrix<int> m2(20);
	ASSERT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(10);
	TDynamicVector<int> v(10);

	for (size_t i = 0; i < 10; i++)
	{
		v[i] = i;
	}
	for (size_t i = 0; i < 10; i++)
	{
		m1[i] = v;
	}
	m1 = m1 + m1;

	TDynamicVector<int> v2(10);

	for (size_t i = 0; i < 10; i++)
	{
		v2[i] = i * 2;
	}

	TDynamicMatrix<int> m2(10);

	for (size_t i = 0; i < 10; i++)
	{
		m2[i] = v2;
	}

	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(10);
	TDynamicMatrix<int> m2(20);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(10);
	TDynamicVector<int> v(10);

	for (size_t i = 0; i < 10; i++)
	{
		v[i] = i;
	}
	for (size_t i = 0; i < 10; i++)
	{
		m1[i] = v;
	}
	m1 = m1 - m1;

	TDynamicVector<int> v2(10);

	for (size_t i = 0; i < 10; i++)
	{
		v2[i] = 0;
	}

	TDynamicMatrix<int> m2(10);

	for (size_t i = 0; i < 10; i++)
	{
		m2[i] = v2;
	}

	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(10);
	TDynamicMatrix<int> m2(20);
	ASSERT_ANY_THROW(m1 - m2);
}
