#include "aes.h"
#include <cunit.h>

void test_SubBytes(void)
{
	int i;
	unsigned char expected[] = {
		0x63, 0x7c, 0x77, 0x7b,
        0xca, 0x82, 0xc9, 0x7d,
        0xb7, 0xfd, 0x93, 0x26,
        0x04, 0xc7, 0x23, 0xc3};

	unsigned char actual[] = {
		0x00, 0x01, 0x02, 0x03,
		0x10, 0x11, 0x12, 0x13,
		0x20, 0x21, 0x22, 0x23,
		0x30, 0x31, 0x32, 0x33};
	SubBytes(actual);

	for (i = 0; i < 4*4; i++)
	{
	  CU_ASSERT_INT_EQ(expected[i], actual[i]);
	}
}

void test_ShiftRows(void)
{
	int i;
	unsigned char expected[] = {
		0x00, 0x01, 0x02, 0x03,
		0x11, 0x12, 0x13, 0x10,
		0x22, 0x23, 0x20, 0x21,
		0x33, 0x30, 0x31, 0x32};

	unsigned char actual[] = {
		0x00, 0x01, 0x02, 0x03,
		0x10, 0x11, 0x12, 0x13,
		0x20, 0x21, 0x22, 0x23,
		0x30, 0x31, 0x32, 0x33};
	ShiftRows(actual);

	for (i = 0; i < 4*4; i++)
	{
	  CU_ASSERT_INT_EQ(expected[i], actual[i]);
	}
}

void test_MixColumns_single_input_col2(void)
{
	int i;
	unsigned char expected[] = {
		0x00, 0x06, 0x00, 0x00,
		0x00, 0x04, 0x00, 0x00,
		0x00, 0x02, 0x00, 0x00,
		0x00, 0x02, 0x00, 0x00};

	unsigned char actual[] = {
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x02, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00};
	MixColumns(actual);

	for (i = 0; i < 4*4; i++)
	{
	  CU_ASSERT_INT_EQ(expected[i], actual[i]);
	}
}

void test_MixColumns_full_input_col2(void)
{
	int i;
	unsigned char expected[] = {
		0x00,   3, 0x00, 0x00,
		0x00,   4, 0x00, 0x00,
		0x00,   9, 0x00, 0x00,
		0x00,  10, 0x00, 0x00};

	unsigned char actual[] = {
		0x00, 0x01, 0x00, 0x00,
		0x00, 0x02, 0x00, 0x00,
		0x00, 0x03, 0x00, 0x00,
		0x00, 0x04, 0x00, 0x00};
	MixColumns(actual);

	for (i = 0; i < 4*4; i++)
	{
	  CU_ASSERT_INT_EQ(expected[i], actual[i]);
	}
}

void test_MixColumns_full_input_low_values(void)
{
	int i;
	unsigned char expected[] = {
		 23,   3,  15,  11,
         16,   4,   8,  12,
         45,   9,  21,   1,
         54,  10,  30,   2};

	unsigned char actual[] = {
		 13,   1,   5,   9,
		 14,   2,   6,  10,
		 15,   3,   7,  11,
		 16,   4,   8,  12};
	MixColumns(actual);

	for (i = 0; i < 4*4; i++)
	{
	  CU_ASSERT_INT_EQ(expected[i], actual[i]);
	}
}

void test_MixColumns_full_input_high_values(void)
{
	int i;
	unsigned char expected[] = {
		142, 159,   1, 198,
		 77, 220,   1, 198,
		161,  88,   1, 198,
		188, 157,   1, 198};

	unsigned char actual[] = {
	    219, 242,   1, 198,
		 19,  10,   1, 198,
		 83,  34,   1, 198,
		 69,  92,   1, 198};

	MixColumns(actual);

	for (i = 0; i < 4*4; i++)
	{
	  CU_ASSERT_INT_EQ(expected[i], actual[i]);
	}
}

void test_AddRoundKey_simple_input(void)
{
	int i;
	unsigned char expected[] = {
		0x00, 0x88, 0x00, 0x00,
		0x00, 0x99, 0x00, 0x00,
		0x00, 0xaa, 0x00, 0x00,
		0x00, 0xbb, 0x00, 0x00};

	unsigned char subkey[] = {
		0xcc, 0x00, 0x44, 0x00,
		0xdd, 0x00, 0x55, 0x11,
		0xee, 0x00, 0x66, 0x22,
		0xff, 0x00,	0x77, 0x33};

	unsigned char actual[] = {
		0xcc, 0x88, 0x44, 0x00,
		0xdd, 0x99, 0x55, 0x11,
		0xee, 0xaa, 0x66, 0x22,
		0xff, 0xbb, 0x77, 0x33};

	AddRoundKey(actual, subkey);

	for (i = 0; i < 4*4; i++)
	{
	  CU_ASSERT_INT_EQ(expected[i], actual[i]);
	}
}

int main(void)
{
  test_SubBytes();
  test_ShiftRows();
  test_MixColumns_single_input_col2();
  test_MixColumns_full_input_col2();
  test_MixColumns_full_input_low_values();
  test_MixColumns_full_input_high_values();
  test_AddRoundKey_simple_input();

  return 0;
}

