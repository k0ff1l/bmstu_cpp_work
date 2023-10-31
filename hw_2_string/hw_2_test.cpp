#include <gtest/gtest.h>
#include <iostream>
#include <utility>

#include "hw_2.h"

using bmstu::string;

TEST(hw_2_string_test, size) {
  string<char> str_1("23");
  ASSERT_EQ(str_1.size(), 2);
  string<char> str_2("");
  ASSERT_EQ(str_2.size(), 0);
  string<char> str_3(str_1);
  ASSERT_EQ(str_3.size(), str_1.size());
  string<char> &str_1_ref = str_1;
  ASSERT_EQ(str_1_ref.size(), str_1.size());
  string<char> sum_str_1_str_2 = str_1 + str_2;
  ASSERT_EQ(sum_str_1_str_2.size(), str_1.size() + str_2.size());
  string<char> &sum_str_1_str_2_ref = sum_str_1_str_2;
  string<char> complex_str = sum_str_1_str_2_ref + str_1_ref;
  ASSERT_EQ(complex_str.size(), str_1.size() + str_2.size() + str_1_ref.size());
  string<char> str_4("lol");
  string<char> str_5 = str_4 + str_1;
  ASSERT_EQ(str_5.size(), 5);
}

TEST(hw_2_string_test, c_str) {
  string<char> str_1("23");
  ASSERT_STREQ(str_1.c_str(), "23");
  string<char> str_2("");
  ASSERT_STREQ(str_2.c_str(), "");
  string<char> str_3("fjsdkfksdgkajsgjkldgasdgjasdgjasdg");
  ASSERT_STREQ(str_3.c_str(), "fjsdkfksdgkajsgjkldgasdgjasdgjasdg");
}

TEST(hw_2_string_test, copy) {
  string<char> str_1("123123");
  string<char> str_1_copy = str_1;
  ASSERT_STREQ(str_1.c_str(), str_1_copy.c_str());
}

TEST(hw_2_string_test, add_symbol) {
  string<char> str_1("123");
  str_1 += '2';
  ASSERT_STREQ(str_1.c_str(), "1232");
  str_1 += ' ';
  ASSERT_STREQ(str_1.c_str(), "1232 ");
}

TEST(hw_2_string_test, sum_) {
  string<char> str_1("123");
  string<char> str_2("124");
  size_t str_1_prev_size = str_1.size();
  str_1 += str_2;
  ASSERT_STREQ(str_1.c_str(), "123124");
  ASSERT_EQ(str_1.size(), str_1_prev_size + str_2.size());
}

TEST(hw_2_string_test, index) {
  string<char> str_1("123456789");
  for (size_t i = 0; i < str_1.size(); ++i) {
    ASSERT_EQ(str_1[i], 49 + i);  // test in ascii
  }
  // Index out of range
  try {
    str_1[14];
  } catch (std::out_of_range &e) {
    std::cerr << e.what() << "  // hw_2_string_test, index, намеренно для теста" << std::endl;
  }
}

TEST(hw_2_string_test, sum) {
  string<char> str_1("123");
  string<char> str_2(" 999 abc");
  string<char> str_3 = str_1 + str_2;
  ASSERT_STREQ(str_3.c_str(), "123 999 abc");
}

TEST(hw_2_string_test, dying) {
  string<char> str_1("12345");
  string<char> str_2;
  str_2 = std::move(str_1);
  EXPECT_EQ(str_1.size(), 0);
  string<char> str_3 = std::move(str_2);
  EXPECT_EQ(str_2.size(), 0);
  EXPECT_STREQ(str_3.c_str(), "12345");
  EXPECT_EQ(str_1.c_str(), str_2.c_str());  // адрес, оба null
}

TEST(hw_2_string_test, ostream) {
  string<char> str_1("123");
  std::stringstream os_1;
  os_1 << str_1;
  EXPECT_STREQ(os_1.str().c_str(), "123");
  EXPECT_EQ(os_1.str().size(), 3);
  string<char> str_2(" ");
  std::stringstream os_2;
  os_2 << str_2;
  EXPECT_STREQ(os_2.str().c_str(), " ");
  EXPECT_EQ(os_2.str().size(), 1);
  string<char> str_3;
  std::stringstream os_3;
  os_3 << str_3;
  EXPECT_STREQ(os_3.str().c_str(), "");
  EXPECT_EQ(os_3.str().size(), 0);
}

TEST(hw_2_string_test, istream) {
  string<char> str_1;
  std::stringstream is_1("123");
  is_1 >> str_1;
  EXPECT_STREQ(str_1.c_str(), "123");
  EXPECT_EQ(str_1.size(), 3);
  string<char> str_2;
  std::stringstream is_2("abcdefg");
  is_2 >> str_2;
  EXPECT_STREQ(str_2.c_str(), "abcdefg");
  EXPECT_EQ(str_2.size(), 7);
}

TEST(hw_2_string_test, multi) {
  string<char> str_empty;
  string<char> str_1("you ");
  string<char> str_2("are ");
  string<char> str_3("nigger");
  string<char> result = str_empty + str_1 + str_2;
  result += str_3;
  EXPECT_EQ(result.size(), 14);
}

TEST(hw_2_string_test, equal) {
  string<char> str_1("1234567890");
  str_1 = str_1;
  EXPECT_STREQ(str_1.c_str(), "1234567890");
  EXPECT_EQ(str_1.size(), 10);
}

TEST(hw_2_string_test, ifequal) {
  string<char> str_1("1234");
  string<char> str_2("1234");
  string<char> str_3("");
  string<char> str_4;
  string<char> &str_5 = str_2;
  string<char> str_6("123");
  string<char> str_7("12 34");
  EXPECT_TRUE(str_1 == str_2);
  EXPECT_FALSE(str_1 == str_3);
  EXPECT_TRUE(str_5 == str_2);
  EXPECT_TRUE(str_3 == str_4);
  EXPECT_FALSE(str_6 == str_1);
  EXPECT_FALSE(str_7 == str_1);
}

TEST(hw_2_string_test, gpt_constructor_from_char_pointer) {
  const char *charArray = "Hello, World!";
  string<char> mystring(charArray);
  EXPECT_EQ(mystring.size(), strlen(charArray));  // Проверка размера строки.
  EXPECT_STREQ(mystring.c_str(), charArray);  // Сравнение содержимого строки с исходным массивом char.
}

TEST(hw_2_string_test, gpt_copy_constructor) {
  const char *charArray = "Hello, World!";
  string<char> original(charArray);
  string<char> replica(original);  // Используем конструктор копирования.
  EXPECT_EQ(original.size(), replica.size());  // Проверка равенства размеров.
  EXPECT_STREQ(original.c_str(), replica.c_str());  // Проверка равенства содержимого.
}

TEST(hw_2_string_test, gpt_concatenation) {
  string<char> first("Hello, ");
  string<char> second("World!");
  string<char> result = first + second;
  EXPECT_STREQ(result.c_str(), "Hello, World!");  // Проверка правильности конкатенации.
}

TEST(hw_2_string_test, gpt_default_constructor) {
  string<char> mystring;
  EXPECT_EQ(mystring.size(), 0);  // Проверка, что размер пустой строки равен 0.
  std::stringstream ss;
  ss << mystring;
  EXPECT_EQ(ss.str(), "");  // Проверка, что вывод в поток пустой.
}

TEST(hw_2_string_test, gpt_assignment_operator) {
  string<char> str1("Original");
  string<char> str2("New");
  str1 = str2;  // Используем оператор присваивания.
  EXPECT_STREQ(str1.c_str(), "New");  // Проверка правильности присваивания.
  EXPECT_EQ(str1.size(), 3);  // Проверка размера после присваивания.
}

TEST(hw_2_string_test, gpt_move_constructor) {
  string<char> source("Move this");
  string<char> destination(std::move(source));  // Используем конструктор перемещения.
  EXPECT_STREQ(destination.c_str(), "Move this");  // Проверка содержимого после перемещения.
  EXPECT_EQ(source.size(), 0);  // Проверка, что исходная строка пуста после перемещения.
}

TEST(hw_2_string_test, gpt_input_output) {
  string<char> mystring;
  std::stringstream ss;
  ss << "Input Test";
  ss >> mystring;
  EXPECT_STREQ(mystring.c_str(), "Input Test");  // Проверка ввода.
  std::stringstream os;
  os << mystring;
  EXPECT_EQ(os.str(), "Input Test");  // Проверка вывода.
}
