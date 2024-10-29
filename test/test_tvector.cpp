#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	EXPECT_NO_THROW(TDynamicVector<int> v(5));
	TDynamicVector<int> v(5);
	EXPECT_EQ(v.size(), 5);
}

TEST(TDynamicVector, can_create_vector_with_basic_constructor) 
{
	EXPECT_NO_THROW(TDynamicVector<int> v);
	TDynamicVector<int> v;
	EXPECT_EQ(v.size(), 1);
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	EXPECT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	EXPECT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	EXPECT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(10);
	
	for (int i = 0; i < 10; i++) {
		v1[i] = i;
	}

	TDynamicVector<int> v2 = v1;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10);
	
	for (int i = 0; i < 10; i++) {
		v1[i] = i;
	}

	TDynamicVector<int> v2 = v1;

	v1[0] = 10;

	EXPECT_EQ(0, v2[0]);
	EXPECT_EQ(10, v1[0]);
}

TEST(TDynamicVector, vector_can_use_move_constructor)
{
	TDynamicVector<int> v1(10);

	EXPECT_NO_THROW(TDynamicVector<int> v2(std::move(v1)));
}

TEST(TDynamicVector, initial_vector_is_empty_after_moving_constructor)
{
	TDynamicVector<int> v1(10);

	TDynamicVector<int> v2(std::move(v1));

	EXPECT_EQ(v1.size(), 0);
}

TEST(TDynamicVector, vector_data_is_correct_after_moving_data_with_constructor)
{
	TDynamicVector<int> v1(10);

	TDynamicVector<int> v2 = v1;

	TDynamicVector<int> v3(std::move(v1));

	EXPECT_EQ(v3, v2);
}

TEST(TDynamicVector, vector_can_use_move_operator)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2;

	EXPECT_NO_THROW(v2 = std::move(v1));
}

TEST(TDynamicVector, initial_vector_is_empty_after_moving_operator)
{
	TDynamicVector<int> v1(10);

	TDynamicVector<int> v2;
	v2 = std::move(v1);

	EXPECT_EQ(v1.size(), 0);
}

TEST(TDynamicVector, vector_data_is_correct_after_moving_data_with_operator)
{
	TDynamicVector<int> v1(10);

	TDynamicVector<int> v2 = v1;

	TDynamicVector<int> v3;
	v3 = std::move(v1);

	EXPECT_EQ(v3, v2);
}

TEST(TDynamicVector, can_get_vector_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index) 
{
	TDynamicVector<int> v1(10);

	EXPECT_ANY_THROW(v1.at(-1) = 0);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v1(10);

	EXPECT_ANY_THROW(v1.at(10) = 0);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);

	EXPECT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(7);

	v2 = v1;

	EXPECT_EQ(v2.size(), 10);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(7);

	EXPECT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(v1);

	EXPECT_NO_THROW(v1 = v1);
	v1 = v1;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);
	
	for (int i = 0; i < 10; i++) {
		v1[i] = i;
		v2[i] = i;
	}

	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_different_vectors_return_false) 
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);

	for (int i = 0; i < 10; i++) {
		v1[i] = i;
		v2[i] = i + 1;
	}

	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(10);

	EXPECT_TRUE(v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(9);

	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++) {
		v1[i] = i;
	}


	EXPECT_NO_THROW(v1 + 1);

	TDynamicVector<int> v2(v1 + 1);

	bool isRight = true;
	for (int i = 0; i < 10; i++) {
		if (v2[i] != v1[i] + 1) isRight = false;
	}

	EXPECT_TRUE(isRight);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++) {
		v1[i] = i;
	}


	EXPECT_NO_THROW(v1 - 1);

	TDynamicVector<int> v2(v1 - 1);

	bool isRight = true;
	for (int i = 0; i < 10; i++) {
		if (v2[i] != v1[i] - 1) isRight = false;
	}

	EXPECT_TRUE(isRight);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < 10; i++) {
		v1[i] = i;
	}

	EXPECT_NO_THROW(v1 * 2);

	TDynamicVector<int> v2(v1 * 2);

	bool isRight = true;
	for (int i = 0; i < 10; i++) {
		if (v2[i] != v1[i] * 2) isRight = false;
	}

	EXPECT_TRUE(isRight);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);

	for (int i = 0; i < 10; i++) {
		v1[i] = i;
		v2[i] = i;
	}

	EXPECT_NO_THROW(v1 + v2);

	TDynamicVector<int> v3(v1 + v2);

	bool isRight = true;
	for (int i = 0; i < 10; i++) {
		if (v3[i] != v1[i] + v2[i]) isRight = false;
	}

	EXPECT_TRUE(isRight);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(9);

	EXPECT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);

	for (int i = 0; i < 10; i++) {
		v1[i] = i + 1;
		v2[i] = i;
	}

	EXPECT_NO_THROW(v1 - v2);

	TDynamicVector<int> v3(v1 - v2);

	bool isRight = true;
	for (int i = 0; i < 10; i++) {
		if (v3[i] != v1[i] - v2[i]) isRight = false;
	}

	EXPECT_TRUE(isRight);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(9);

	EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);

	for (int i = 0; i < 10; i++) {
		v1[i] = 2 * i;
		v2[i] = i + 5;
	}

	EXPECT_NO_THROW(v1 * v2);

	int proizv = v1 * v2;

	int rightValue = 0;
	for (int i = 0; i < 10; i++) {
		rightValue += v1[i] * v2[i];
	}

	EXPECT_EQ(proizv, rightValue);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(9);
	   
	EXPECT_ANY_THROW(v1 * v2);
}

