#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	EXPECT_NO_THROW(TDynamicMatrix<int> m(5));
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_create_matrix_with_basic_constructor) 
{
	EXPECT_NO_THROW(TDynamicMatrix<int> m);
	TDynamicMatrix<int> m;
	EXPECT_EQ(m.size(), 1);
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	EXPECT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) 
{
	EXPECT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);
	
	EXPECT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(5);
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m1[i][j] = 5;
		}
	}
	
	TDynamicMatrix<int> m2 = m1;
	
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m1[i][j] = 5;
		}
	}

	TDynamicMatrix<int> m2 = m1;
	m1[0][0] = 0;

	EXPECT_EQ(m2[0][0], 5);
	EXPECT_EQ(m1[0][0], 0);
}

TEST(TDynamicMatrix, matrix_can_use_move_constructor)
{
	TDynamicMatrix<int> m1(10);

	EXPECT_NO_THROW(TDynamicMatrix<int> m2(std::move(m1)));
}

TEST(TDynamicMatrix, initial_matrix_is_empty_after_moving_constructor)
{
	TDynamicMatrix<int> m1(10);

	TDynamicMatrix<int> m2(std::move(m1));

	EXPECT_EQ(m1.size(), 0);
}

TEST(TDynamicMatrix, matrix_data_is_correct_after_moving_data_with_constructor)
{
	TDynamicMatrix<int> m1(10);

	TDynamicMatrix<int> m2 = m1;

	TDynamicMatrix<int> m3(std::move(m1));

	EXPECT_EQ(m3, m2);
}

TEST(TDynamicMatrix, matrix_can_use_move_operator)
{
	TDynamicVector<int> m1(10);
	TDynamicVector<int> m2;

	EXPECT_NO_THROW(m2 = std::move(m1));
}


TEST(TDynamicMatrix, initial_matrix_is_empty_after_moving_operator)
{
	TDynamicMatrix<int> m1(10);

	TDynamicMatrix<int> m2;
	m2 = std::move(m1);

	EXPECT_EQ(m1.size(), 0);
}

TEST(TDynamicMatrix, matrix_data_is_correct_after_moving_data_with_operator)
{
	TDynamicMatrix<int> m1(10);

	TDynamicMatrix<int> m2 = m1;

	TDynamicMatrix<int> m3;
	m3 = std::move(m1);

	EXPECT_EQ(m3, m2);
}

TEST(TDynamicMatrix, can_get_matrix_size)
{
	TDynamicMatrix<int> m(10);

	EXPECT_EQ(m.size(), 10);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(10);
	m[0][1] = 8;

	EXPECT_EQ(m[0][1], 8);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(10);

	EXPECT_ANY_THROW(m.at(-1, 0) = 1);        
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(10);

	EXPECT_ANY_THROW(m.at(11, 0) = 1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);

	EXPECT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(6);
	m2 = m1;

	EXPECT_EQ(m2.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(6);

	EXPECT_NO_THROW(m1 = m2);
}


TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m1(10);
	TDynamicMatrix<int> m2(m1);

	EXPECT_NO_THROW(m1 = m1);
	m1 = m1;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m1[i][j] = i + j;
			m2[i][j] = i + j;
		}
	}

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = 6;
		}
	}

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, compare_different_matrix_return_false)
{
	TDynamicMatrix<int> m1(10);
	TDynamicMatrix<int> m2(10);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m1[i][j] = i;
			m2[i][j] = i + 1;
		}
	}

	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(6);

	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_multiply_scalar_by_matrix) {
	TDynamicMatrix<int> m1(5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m1[i][j] = i + j;
		}
	}

	EXPECT_NO_THROW(m1 * 3);

	TDynamicMatrix<int> m2(m1 * 3);

	bool isRight = true;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (m2[i][j] != m1[i][j] * 3) isRight = false;
		}
	}

	EXPECT_TRUE(isRight);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m1[i][j] = i + j;
			m2[i][j] = i + j;
		}
	}

	EXPECT_NO_THROW(m1 + m2);

	TDynamicMatrix<int> m3(m1 + m2);

	bool isRight = true;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (m3[i][j] != m1[i][j] + m2[i][j]) isRight = false;
		}
	}

	EXPECT_TRUE(isRight);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(6);

	EXPECT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m1[i][j] = i + j + 1;
			m2[i][j] = i + j;
		}
	}

	EXPECT_NO_THROW(m1 - m2);

	TDynamicMatrix<int> m3(m1 - m2);

	bool isRight = true;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (m3[i][j] != m1[i][j] - m2[i][j]) isRight = false;
		}
	}

	EXPECT_TRUE(isRight);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(6);

	EXPECT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector) {
	TDynamicMatrix<int> m(5);
	TDynamicVector<int> v1(5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j;
		}
		v1[i] = i;
	}

	EXPECT_NO_THROW(m * v1);

	TDynamicVector<int> v2(m * v1);
	TDynamicVector<int> rightValue(5);

	for (int i = 0; i < 5; i++) {
		rightValue[i] = 0;
		for (int j = 0; j < 5; j++) {
			rightValue[i] += v1[j] * m[i][j];
		}
	}

	EXPECT_EQ(v2, rightValue);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_incorrect_sizes) {
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> v(4);

	EXPECT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_matrix) {
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m1[i][j] = i + j;
			m2[i][j] = i + j;
		}
	}

	EXPECT_NO_THROW(m1 * m2);

	TDynamicMatrix<int> m3 (m1 * m2);

	TDynamicMatrix<int> rightValue(5);
	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			for (int j = 0; j < 5; j++) {
				rightValue[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}

	EXPECT_EQ(rightValue, m3);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_incorrect_sizes) {
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(4);

	EXPECT_ANY_THROW(m1 * m2);
}