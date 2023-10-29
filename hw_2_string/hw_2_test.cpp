#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "hw_2.cpp"

using namespace bmstu;

TEST(string_test, size) {
  string str_1("23");
  ASSERT_EQ(str_1.size(), 2);
  string str_2("");
  ASSERT_EQ(str_2.size(), 0);
  string str_3(str_1);
  ASSERT_EQ(str_3.size(), str_1.size());
  string &str_1_ref = str_1;
  ASSERT_EQ(str_1_ref.size(), str_1.size());
  string sum_str_1_str_2 = str_1 + str_2;
  ASSERT_EQ(sum_str_1_str_2.size(), str_1.size() + str_2.size());
  string &sum_str_1_str_2_ref = sum_str_1_str_2;
  string complex_str = sum_str_1_str_2_ref + str_1_ref;
  ASSERT_EQ(complex_str.size(), str_1.size() + str_2.size() + str_1_ref.size());
  string str_4 = "lol";
  string str_5 = str_4 + str_1;
  ASSERT_EQ(str_5.size(), 5);
}

TEST(string_test, c_str) {
  string str_1("23");
  ASSERT_STREQ(str_1.c_str(), "23");
  string str_2("");
  ASSERT_STREQ(str_2.c_str(), "");
  string str_3("fjsdkfksdgkajsgjkldgasdgjasdgjasdg");
  ASSERT_STREQ(str_3.c_str(), "fjsdkfksdgkajsgjkldgasdgjasdgjasdg");
}

TEST(string_test, copy) {
  string str_1("123123");
  string str_1_copy = str_1;
  ASSERT_STREQ(str_1.c_str(), str_1_copy.c_str());
}

TEST(string_test, add_symbol) {
  string str_1("123");
  str_1 += '2';
  ASSERT_STREQ(str_1.c_str(), "1232");
  str_1 += ' ';
  ASSERT_STREQ(str_1.c_str(), "1232 ");
}

TEST(string_test, sum_) {
  string str_1("123");
  string str_2("124");
  size_t str_1_prev_size = str_1.size();
  str_1 += str_2;
  ASSERT_STREQ(str_1.c_str(), "123124");
  ASSERT_EQ(str_1.size(), str_1_prev_size + str_2.size());
}

TEST(string_test, index) {
  string str_1("123456789");
  for (size_t i = 0; i < str_1.size(); ++i) {
    ASSERT_EQ(str_1[i], 49 + i);  // test in ascii
  }
  // Index out of range
  try {
    str_1[14];
  } catch (std::out_of_range &e) {
    std::cerr << e.what() << "  // string_test, index, намеренно для теста" << std::endl;
  }
}

TEST(string_test, sum) {
  string str_1("123");
  string str_2(" 999 abc");
  string str_3 = str_1 + str_2;
  ASSERT_STREQ(str_3.c_str(), "123 999 abc");
}

TEST(string_test, dying) {
  string str_1("12345");
  string str_2;
  str_2 = std::move(str_1);
  EXPECT_EQ(str_1.size(), 0);
  string str_3 = std::move(str_2);
  EXPECT_EQ(str_2.size(), 0);
  EXPECT_STREQ(str_3.c_str(), "12345");
  EXPECT_EQ(str_1.c_str(), str_2.c_str());  // адрес, оба null
}

TEST(string_test, ostream) {
  string str_1("123");
  std::stringstream os_1;
  os_1 << str_1;
  EXPECT_STREQ(os_1.str().c_str(), "123");
  EXPECT_EQ(os_1.str().size(), 3);
  string str_2(" ");
  std::stringstream os_2;
  os_2 << str_2;
  EXPECT_STREQ(os_2.str().c_str(), " ");
  EXPECT_EQ(os_2.str().size(), 1);
  string str_3;
  std::stringstream os_3;
  os_3 << str_3;
  EXPECT_STREQ(os_3.str().c_str(), "");
  EXPECT_EQ(os_3.str().size(), 0);
}

TEST(string_test, istream) {
  string str_1;
  std::stringstream is_1("123");
  is_1 >> str_1;
  EXPECT_STREQ(str_1.c_str(), "123");
  EXPECT_EQ(str_1.size(), 3);
  string str_2;
  std::stringstream is_2("abcdefg");
  is_2 >> str_2;
  EXPECT_STREQ(str_2.c_str(), "abcdefg");
  EXPECT_EQ(str_2.size(), 7);
}

TEST(string_test, multi) {
  string str_empty;
  string str_1("you ");
  string str_2("are ");
  string str_3("nigger");
  string result = str_empty + str_1 + str_2;
  result += str_3;
  EXPECT_EQ(result.size(), 14);
}

TEST(string_test, equal) {
  string str_1("1234567890");
  str_1 = str_1;
  EXPECT_STREQ(str_1.c_str(), "1234567890");
  EXPECT_EQ(str_1.size(), 10);
}

TEST(string_test, ifequal) {
  string str_1("1234");
  string str_2("1234");
  string str_3("");
  string str_4;
  string &str_5 = str_2;
  string str_6("123");
  string str_7("12 34");
  EXPECT_TRUE(str_1 == str_2);
  EXPECT_FALSE(str_1 == str_3);
  EXPECT_TRUE(str_5 == str_2);
  EXPECT_TRUE(str_3 == str_4);
  EXPECT_FALSE(str_6 == str_1);
  EXPECT_FALSE(str_7 == str_1);
}

TEST(ChatGPT_test, constructor_from_char_pointer) {
  const char *charArray = "Hello, World!";
  string myString(charArray);
  EXPECT_EQ(myString.size(), strlen(charArray));  // Проверка размера строки.
  EXPECT_STREQ(myString.c_str(), charArray);  // Сравнение содержимого строки с исходным массивом char.
}

TEST(ChatGPT_test, copy_constructor) {
  const char *charArray = "Hello, World!";
  string original(charArray);
  string copy(original);  // Используем конструктор копирования.
  EXPECT_EQ(original.size(), copy.size());  // Проверка равенства размеров.
  EXPECT_STREQ(original.c_str(), copy.c_str());  // Проверка равенства содержимого.
}

TEST(ChatGPT_test, concatenation) {
  string first("Hello, ");
  string second("World!");
  string result = first + second;
  EXPECT_STREQ(result.c_str(), "Hello, World!");  // Проверка правильности конкатенации.
}

TEST(ChatGPT_test, default_constructor) {
  string myString;
  EXPECT_EQ(myString.size(), 0);  // Проверка, что размер пустой строки равен 0.
  std::stringstream ss;
  ss << myString;
  EXPECT_EQ(ss.str(), "");  // Проверка, что вывод в поток пустой.
}

TEST(ChatGPT_test, assignment_operator) {
  string str1("Original");
  string str2("New");
  str1 = str2;  // Используем оператор присваивания.
  EXPECT_STREQ(str1.c_str(), "New");  // Проверка правильности присваивания.
  EXPECT_EQ(str1.size(), 3);  // Проверка размера после присваивания.
}

TEST(ChatGPT_test, move_constructor) {
  string source("Move this");
  string destination(std::move(source));  // Используем конструктор перемещения.
  EXPECT_STREQ(destination.c_str(), "Move this");  // Проверка содержимого после перемещения.
  EXPECT_EQ(source.size(), 0);  // Проверка, что исходная строка пуста после перемещения.
}

TEST(ChatGPT_test, input_output) {
  string myString;
  std::stringstream ss;
  ss << "Input Test";
  ss >> myString;
  EXPECT_STREQ(myString.c_str(), "Input Test");  // Проверка ввода.
  std::stringstream os;
  os << myString;
  EXPECT_EQ(os.str(), "Input Test");  // Проверка вывода.
}
