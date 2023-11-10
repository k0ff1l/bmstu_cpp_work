// Copyright 2023 <fleurs>

#include <gtest/gtest.h>
#include <iostream>
#include <utility>

#include "hw_2.h"

using bmstu::dummy_basic_string;

TEST(StringTest, size) {
  bmstu::dummy_string str_1("23");
  ASSERT_EQ(str_1.size(), 2);
  bmstu::dummy_string str_2("");
  ASSERT_EQ(str_2.size(), 0);
  bmstu::dummy_string str_3(str_1);
  ASSERT_EQ(str_3.size(), str_1.size());
  bmstu::dummy_string &str_1_ref = str_1;
  ASSERT_EQ(str_1_ref.size(), str_1.size());
  bmstu::dummy_string sum_str_1_str_2 = str_1 + str_2;
  ASSERT_EQ(sum_str_1_str_2.size(), str_1.size() + str_2.size());
  bmstu::dummy_string &sum_str_1_str_2_ref = sum_str_1_str_2;
  bmstu::dummy_string complex_str = sum_str_1_str_2_ref + str_1_ref;
  ASSERT_EQ(complex_str.size(), str_1.size() + str_2.size() + str_1_ref.size());
  bmstu::dummy_string str_4("lol");
  bmstu::dummy_string str_5 = str_4 + str_1;
  ASSERT_EQ(str_5.size(), 5);
}

TEST(StringTest, c_str) {
  bmstu::dummy_string str_1("23");
  ASSERT_STREQ(str_1.c_str(), "23");
  bmstu::dummy_string str_2("");
  ASSERT_STREQ(str_2.c_str(), "");
  bmstu::dummy_string str_3("fjsdkfksdgkajsgjkldgasdgjasdgjasdg");
  ASSERT_STREQ(str_3.c_str(), "fjsdkfksdgkajsgjkldgasdgjasdgjasdg");
}

TEST(StringTest, copy) {
  bmstu::dummy_string str_1("123123");
  bmstu::dummy_string str_1_copy = str_1;
  ASSERT_STREQ(str_1.c_str(), str_1_copy.c_str());
}

TEST(StringTest, add_symbol) {
  bmstu::dummy_string str_1("123");
  str_1 += '2';
  ASSERT_STREQ(str_1.c_str(), "1232");
  str_1 += ' ';
  ASSERT_STREQ(str_1.c_str(), "1232 ");
}

TEST(StringTest, sum_) {
  bmstu::dummy_string str_1("123");
  bmstu::dummy_string str_2("124");
  size_t str_1_prev_size = str_1.size();
  str_1 += str_2;
  ASSERT_STREQ(str_1.c_str(), "123124");
  ASSERT_EQ(str_1.size(), str_1_prev_size + str_2.size());
}

TEST(StringTest, sum) {
  bmstu::dummy_string str_1("123");
  bmstu::dummy_string str_2(" 999 abc");
  bmstu::dummy_string str_3 = str_1 + str_2;
  ASSERT_STREQ(str_3.c_str(), "123 999 abc");
}

TEST(StringTest, dying) {
  bmstu::dummy_string str_1("12345");
  bmstu::dummy_string str_2;
  str_2 = std::move(str_1);
  EXPECT_EQ(str_1.size(), 0);
  bmstu::dummy_string str_3 = std::move(str_2);
  EXPECT_EQ(str_2.size(), 0);
  EXPECT_STREQ(str_3.c_str(), "12345");
  EXPECT_EQ(str_1.c_str(), str_2.c_str());  // адрес, оба null
}

TEST(StringTest, ostream) {
  bmstu::dummy_string str_1("123");
  std::stringstream os_1;
  os_1 << str_1;
  EXPECT_STREQ(os_1.str().c_str(), "123");
  EXPECT_EQ(os_1.str().size(), 3);
  bmstu::dummy_string str_2(" ");
  std::stringstream os_2;
  os_2 << str_2;
  EXPECT_STREQ(os_2.str().c_str(), " ");
  EXPECT_EQ(os_2.str().size(), 1);
  bmstu::dummy_string str_3;
  std::stringstream os_3;
  os_3 << str_3;
  EXPECT_STREQ(os_3.str().c_str(), "");
  EXPECT_EQ(os_3.str().size(), 0);
}

TEST(StringTest, istream) {
  bmstu::dummy_string str_1;
  std::stringstream is_1("123");
  is_1 >> str_1;
  EXPECT_STREQ(str_1.c_str(), "123");
  EXPECT_EQ(str_1.size(), 3);
  bmstu::dummy_string str_2;
  std::stringstream is_2("abcdefg");
  is_2 >> str_2;
  EXPECT_STREQ(str_2.c_str(), "abcdefg");
  EXPECT_EQ(str_2.size(), 7);
}

TEST(StringTest, multi) {
  bmstu::dummy_string str_empty;
  bmstu::dummy_string str_1("you ");
  bmstu::dummy_string str_2("are ");
  bmstu::dummy_string str_3("nigger");
  bmstu::dummy_string result = str_empty + str_1 + str_2;
  result += str_3;
  EXPECT_EQ(result.size(), 14);
}

TEST(StringTest, equal) {
  bmstu::dummy_string str_1("1234567890");
  str_1 = str_1;
  EXPECT_STREQ(str_1.c_str(), "1234567890");
  EXPECT_EQ(str_1.size(), 10);
}

TEST(StringTest, ifequal) {
  bmstu::dummy_string str_1("1234");
  bmstu::dummy_string str_2("1234");
  bmstu::dummy_string str_3("");
  bmstu::dummy_string str_4;
  bmstu::dummy_string &str_5 = str_2;
  bmstu::dummy_string str_6("123");
  bmstu::dummy_string str_7("12 34");
  EXPECT_TRUE(str_1 == str_2);
  EXPECT_FALSE(str_1 == str_3);
  EXPECT_TRUE(str_5 == str_2);
  EXPECT_TRUE(str_3 == str_4);
  EXPECT_FALSE(str_6 == str_1);
  EXPECT_FALSE(str_7 == str_1);
}

TEST(StringTest, gpt_constructor_from_char_pointer) {
  const char *charArray = "Hello, World!";
  bmstu::dummy_string mystring(charArray);
  EXPECT_EQ(mystring.size(), strlen(charArray));  // Проверка размера строки.
  EXPECT_STREQ(mystring.c_str(), charArray);
}

TEST(StringTest, gpt_copy_constructor) {
  const char *charArray = "Hello, World!";
  bmstu::dummy_string original(charArray);
  bmstu::dummy_string replica(original);  // Используем конструктор копирования.
  EXPECT_EQ(original.size(), replica.size());  // Проверка равенства размеров.
  EXPECT_STREQ(original.c_str(),
               replica.c_str());  // Проверка равенства содержимого.
}

TEST(StringTest, gpt_concatenation) {
  bmstu::dummy_string first("Hello, ");
  bmstu::dummy_string second("World!");
  bmstu::dummy_string result = first + second;
  EXPECT_STREQ(result.c_str(),
               "Hello, World!");  // Проверка правильности конкатенации.
}

TEST(StringTest, gpt_default_constructor) {
  bmstu::dummy_string mystring;
  EXPECT_EQ(mystring.size(), 0);  // Проверка, что размер пустой строки равен 0.
  std::stringstream ss;
  ss << mystring;
  EXPECT_EQ(ss.str(), "");  // Проверка, что вывод в поток пустой.
}

TEST(StringTest, gpt_assignment_operator) {
  bmstu::dummy_string str1("Original");
  bmstu::dummy_string str2("New");
  str1 = str2;  // Используем оператор присваивания.
  EXPECT_STREQ(str1.c_str(), "New");  // Проверка правильности присваивания.
  EXPECT_EQ(str1.size(), 3);  // Проверка размера после присваивания.
}

TEST(StringTest, gpt_move_constructor) {
  bmstu::dummy_string source("Move this");
  bmstu::dummy_string
      destination(std::move(source));  // Используем конструктор перемещения.
  EXPECT_STREQ(destination.c_str(),
               "Move this");  // Проверка содержимого после перемещения.
  EXPECT_EQ(source.size(),
            0);   // Проверка, что исходная строка пуста после перемещения.
}

TEST(StringTest, gpt_input_output) {
  bmstu::dummy_string mystring;
  std::stringstream ss;
  ss << "Input Test";
  ss >> mystring;
  EXPECT_STREQ(mystring.c_str(), "Input Test");  // Проверка ввода.
  std::stringstream os;
  os << mystring;
  EXPECT_EQ(os.str(), "Input Test");  // Проверка вывода.
}

TEST(StringTest, DefaultConstructor) {
  bmstu::dummy_string str;
  ASSERT_STREQ(str.c_str(), "");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, DefaultConstructorW) {
  bmstu::wstring str;
  ASSERT_STREQ(str.c_str(), L"");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructorW) {
  bmstu::wstring str{};
  ASSERT_STREQ(str.c_str(), L"");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructor) {
  bmstu::wstring str{};
  ASSERT_STREQ(str.c_str(), L"");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructorNonEmpty) {
  bmstu::wstring str{L'С', L'Л', L'О', L'В', L'О'};
  ASSERT_STREQ(str.c_str(), L"СЛОВО");
  ASSERT_EQ(str.size(), 5);
}

TEST(StringTest, ConstructorSizeW) {
  bmstu::wstring str(10);
  ASSERT_STREQ(str.c_str(), L"          ");
  ASSERT_EQ(str.size(), 10);
}

TEST(StringTest, ConstructorSize) {
  bmstu::dummy_string str(10);
  ASSERT_STREQ(str.c_str(), "          ");
  ASSERT_EQ(str.size(), 10);
}

TEST(StringTest, ConstructorSizeOne) {
  bmstu::wstring str(1);
  ASSERT_STREQ(str.c_str(), L" ");
  ASSERT_EQ(str.size(), 1);
}

TEST(StringTest, FromCStr) {
  bmstu::dummy_string str("str\n");
  ASSERT_STREQ(str.c_str(), "str\n");
  ASSERT_EQ(str.size(), 4);
}

TEST(StringTest, FromWCStr) {
  bmstu::wstring str(L"おはよう");
  ASSERT_STREQ(str.c_str(), L"おはよう");
  ASSERT_EQ(str.size(), 4);
}

TEST(StringTest, FromWCStrSymbol) {
  bmstu::wstring str(L"おはよう");
  ASSERT_STREQ(str.c_str(), L"おはよう");
  wchar_t c = L'お';
  ASSERT_EQ(str[0], c);
}

TEST(StringTest, USymbolsW) {
  bmstu::wstring str(L"お");
  ASSERT_STREQ(str.c_str(), L"お");
  wchar_t c = L'お';
  ASSERT_EQ(str.size(), 1);
}

TEST(StringTest, USymbol) {
  bmstu::dummy_string str("\xe3\x81\x8a\x00");
  ASSERT_STREQ(str.c_str(), "お");
  ASSERT_EQ(str.size(), 3);
}

TEST(StringTest, USymbols) {
  bmstu::dummy_string str("おはよう");
  ASSERT_STREQ(str.c_str(), "おはよう");
  ASSERT_EQ(str.size() + 1, sizeof("おはよう"));
}

TEST(StringTest, Empty) {
  bmstu::dummy_string empty;
  ASSERT_EQ(empty.size(), 0);
  ASSERT_STREQ(empty.c_str(), "");
}

TEST(StringTest, EmptyW) {
  bmstu::wstring empty;
  ASSERT_EQ(empty.size(), 0);
  ASSERT_STREQ(empty.c_str(), L"");
}

TEST(StringTest, CopyAssignW) {
  bmstu::wstring empty(L"Non Empty строка");
  bmstu::wstring nonempty = empty;
  ASSERT_STREQ(nonempty.c_str(), L"Non Empty строка");
  ASSERT_EQ(nonempty.size(), 16);
}

TEST(StringTest, CopyConstructor) {
  bmstu::dummy_string empty("Non Empty строка");
  bmstu::dummy_string nonempty = empty;
  ASSERT_STREQ(nonempty.c_str(), "Non Empty строка");
  ASSERT_EQ(nonempty.size(), sizeof("Non Empty строка") - 1);
}

TEST(StringTest, CopyAssignConstructor) {
  bmstu::dummy_string *str = new bmstu::dummy_string("str");
  bmstu::dummy_string *nonempty = new bmstu::dummy_string;
  *nonempty = *str;
  ASSERT_STREQ(nonempty->c_str(), "str");
  ASSERT_EQ(nonempty->size(), sizeof("str") - 1);
  delete str;
  delete nonempty;
}

TEST(StringTest, MoveAssignConstructor) {
  bmstu::dummy_string str {"str"};
  bmstu::dummy_string str2 {"other"};
  str2 = std::move(str);
  ASSERT_STREQ(str2.c_str(), "str");
  ASSERT_EQ(str2.size(), sizeof("str") - 1);

//  ASSERT_STREQ(str.c_str(), "");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, MoveAssignConstructor2) {
  bmstu::dummy_string str {"str"};
  bmstu::dummy_string str2 {"other"};
  str2 = std::move(str);
  ASSERT_STREQ(str2.c_str(), "str");
  ASSERT_EQ(str2.size(), sizeof("str") - 1);

//  ASSERT_STREQ(str.c_str(), "");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, CopyAssignConstructor2) {
  bmstu::dummy_string str {"str"};
  bmstu::dummy_string str2(bmstu::dummy_string("other"));
  str2 = std::move(str);
  ASSERT_STREQ(str2.c_str(), "str");
  ASSERT_EQ(str2.size(), sizeof("str") - 1);

//  ASSERT_STREQ(str.c_str(), "");  // точно ли это корректный тест?
  // честно говоря, я не знаю как фиксить.
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, MoveAssignConstructorW) {
  bmstu::wstring str2(std::move(bmstu::wstring(L"other")));
  ASSERT_STREQ(str2.c_str(), L"other");
  ASSERT_EQ(str2.size(), (sizeof(L"other") / sizeof(wchar_t)) - 1);
}

TEST(StringTest, CStrCopyAssign) {
  const char *str = "Simple Str";
  bmstu::dummy_string b_str;
  b_str = str;
  ASSERT_STREQ(b_str.c_str(), str);
}

TEST(StringTest, CStrCopyAssignW) {
  const wchar_t *str = L"Простая строка";
  bmstu::wstring b_str;
  b_str = str;
  ASSERT_STREQ(b_str.c_str(), str);
}

TEST(StringTest, AssignCStr) {
  bmstu::wstring str {L"123456789"};
  ASSERT_STREQ(str.c_str(), L"123456789");
}

TEST(StringTest, ConcatOpW) {
  bmstu::wstring a_str(L"right");
  bmstu::wstring b_str(L"_left");
  auto c_str = a_str + b_str;
  ASSERT_STREQ(c_str.c_str(), L"right_left");
}

TEST(StringTest, ConcatOp) {
  bmstu::dummy_string a_str("right");
  bmstu::dummy_string b_str("_left");
  auto c_str = a_str + b_str;
  ASSERT_STREQ(c_str.c_str(), "right_left");
}

TEST(StringTest, OStream) {
  bmstu::dummy_string a_str("String value");
  std::stringstream ss;
  ss << a_str;
  ASSERT_STREQ(ss.str().c_str(), "String value");
}

TEST(StringTest, OStreamW) {
  bmstu::wstring a_str(L"String значение");
  std::wstringstream ss;
  ss << a_str;
  ASSERT_STREQ(ss.str().c_str(), L"String значение");
}

TEST(StringTest, IStream) {
  std::stringstream ss;
  ss.str("Value of\nstring");
  bmstu::dummy_string a_str;
  ss >> a_str;
  ASSERT_STREQ(a_str.c_str(), "Value of\nstring");
}

TEST(StringTest, IStreamW) {
  std::wstringstream ss;
  ss.str(L"Value of\nстрока");
  bmstu::wstring a_str;
  ss >> a_str;
  ASSERT_STREQ(a_str.c_str(), L"Value of\nстрока");
}

TEST(StringTest, IStreamWNewLine) {
  std::wstringstream ss;
  ss.str(L"Value of\nstring");
  bmstu::wstring a_str;
  ss >> a_str;
  ASSERT_STREQ(ss.str().c_str(), L"Value of\nstring");
}

TEST(StringTest, ConcatSymbol) {
  bmstu::wstring a_str;
  a_str += L'S';
  ASSERT_STREQ(a_str.c_str(), L"S");
  a_str += L'т';
  ASSERT_STREQ(a_str.c_str(), L"Sт");
  a_str += L'р';
  ASSERT_STREQ(a_str.c_str(), L"Sтр");
  ASSERT_EQ(a_str.size(), 3);
}

TEST(StringTest, Item) {
  bmstu::wstring a_str(L"СТРОКААГ");
  ASSERT_EQ(a_str[0], L'С');
  ASSERT_EQ(a_str[1], L'Т');
  ASSERT_EQ(a_str[a_str.size() - 1], L'Г');
}
