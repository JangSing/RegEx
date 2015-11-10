#include "unity.h"
#include "findText.h"

#include <stdio.h>
#include <stdlib.h>



void setUp()
{

}

void tearDown()
{
}

//text,word
void test_findText_given_A_find_A_should_return_0()
{
  Match *match=findText("A","A");
	TEST_ASSERT_EQUAL(0, match->possition);
  TEST_ASSERT_EQUAL(1 , match->length);
  TEST_ASSERT_EQUAL_STRING("A" , match->text);
  free(match);
}

void test_findText_given_B_find_A_should_return_minus_1()
{
  Match *match=findText("B","A");
	TEST_ASSERT_EQUAL(-1, match->possition);
	free(match);
}

void test_findText_given_ALL_find_L_should_return_1()
{
  Match *match=findText("ALL","L");
	TEST_ASSERT_EQUAL(2 , match->possition);
  TEST_ASSERT_EQUAL(1 , match->length);
  TEST_ASSERT_EQUAL_STRING("L" , match->text);
	free(match);
}

void test_findText_given_WORLD_find_RL_should_return_2()
{
  Match *match=findText("WORLD","RL");
	TEST_ASSERT_EQUAL(2 , match->possition);
  TEST_ASSERT_EQUAL(2 , match->length);
  TEST_ASSERT_EQUAL_STRING("RL" , match->text);
	free(match);
}

void test_findText_given_WORLD_find_RX_should_return_minus_1()
{
  Match *match=findText("WORLD","RX");
	TEST_ASSERT_EQUAL(-1 , match->possition);
	free(match);
}

void test_findText_given_WORLD_find_D_should_return_4()
{
  Match *match=findText("WORLD","D");
  TEST_ASSERT_EQUAL(4 , match->possition);
	TEST_ASSERT_EQUAL(1 , match->length);
  TEST_ASSERT_EQUAL_STRING("D" , match->text);
	free(match);
}

void test_findText_given_WORLD_find_DX_should_return_minus_1()
{
  Match *match=findText("WORLD","DX");
	TEST_ASSERT_EQUAL(-1 , match->possition);
	free(match);
}

void test_findText_given_WORLD_find_W_should_return_0()
{
  Match *match=findText("WORLD","W");
	TEST_ASSERT_EQUAL(0 , match->possition);
  TEST_ASSERT_EQUAL(1 , match->length);
  TEST_ASSERT_EQUAL_STRING("W" , match->text);
	free(match);
}

void test_findText_given_WORLD_find_R_L_should_return_minus_1()
{
  Match *match=findText("WORLD","R L");
	TEST_ASSERT_EQUAL(-1 , match->possition);
	free(match);
}

void test_findText_given_WOR_LD_find_R_L_should_return_2()
{
  Match *match=findText("WOR LD","R L");
	TEST_ASSERT_EQUAL(2 , match->possition);
  TEST_ASSERT_EQUAL(3 , match->length);
  TEST_ASSERT_EQUAL_STRING("R L" , match->text);
	free(match);
}

void test_findText_given_WORLD_find_ORL_should_return_1()
{
  Match *match=findText("WORLD","ORL");
	TEST_ASSERT_EQUAL(1 , match->possition);
  TEST_ASSERT_EQUAL(3 , match->length);
  TEST_ASSERT_EQUAL_STRING("ORL" , match->text);
	free(match);
}

void test_findText_given_RRARARRARATATUI_find_RARAT_should_return_6()
{
  Match *match=findText("RRARARRARATATUI","RARAT");
	TEST_ASSERT_EQUAL(6 , match->possition);
	TEST_ASSERT_EQUAL(5 , match->length);
  TEST_ASSERT_EQUAL_STRING("RARAT" , match->text);
	free(match);
}

void test_findText_given_Hello_my_name_is_Alladin_find_lad_should_return_20()
{
  Match *match=findText("Hello, my name is Alladin","lad");
	TEST_ASSERT_EQUAL(20 , match->possition);
	TEST_ASSERT_EQUAL(3  , match->length);
	TEST_ASSERT_EQUAL_STRING("lad" , match->text);
	free(match);
}


