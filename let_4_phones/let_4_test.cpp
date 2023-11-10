// Copyright 2023 <fleurs>

#include <gtest/gtest.h>
#include <string>
#include <sstream>

#include "let_4.h"

// Define a test fixture
class let_4_phones_test : public ::testing::Test {
};

// Test case to check the XML output for one phone
TEST_F(let_4_phones_test, SinglePhoneOutput) {
  std::ostringstream os;
  std::istringstream is("1\n100.5 0 500\n");
  std::streambuf *orig_cin = std::cin.rdbuf(is.rdbuf());
  std::streambuf *orig_cout = std::cout.rdbuf(os.rdbuf());

  EXPECT_EQ(phones(), 0);

  std::string expected_output = "<MobilePhones>\n"
                                "\t<MobilePhone id=\"0\" weight=\"100.5\" "
                                "is_broken=\"false\"" " price=\"500\"/>\n"
                                "</MobilePhones>\n";
  EXPECT_EQ(os.str(), expected_output);

  std::cin.rdbuf(orig_cin);
  std::cout.rdbuf(orig_cout);
}

// Test case to check the XML output for multiple phones
TEST_F(let_4_phones_test, MultiplePhonesOutput) {
  std::ostringstream os;
  std::istringstream is("3\n150.2 1 300\n120.7 0 700\n180.1 1 200\n");
  std::streambuf *orig_cin = std::cin.rdbuf(is.rdbuf());
  std::streambuf *orig_cout = std::cout.rdbuf(os.rdbuf());

  EXPECT_EQ(phones(), 0);

  std::string expected_output = "<MobilePhones>\n"
                                "\t<MobilePhone id=\"0\""
                                "weight=\"150.2\" is_broken=\"true\""
                                "price=\"300\"/>\n"
                                "\t<MobilePhone id=\"1\" weight=\"120.7\""
                                "is_broken=\"false\" price=\"700\"/>\n"
                                "\t<MobilePhone id=\"2\" weight=\"180.1\""
                                "is_broken=\"true\" price=\"200\"/>\n"
                                "</MobilePhones>\n";
  EXPECT_EQ(os.str(), expected_output);

  std::cin.rdbuf(orig_cin);
  std::cout.rdbuf(orig_cout);
}

// Test case for an empty phone list
TEST_F(let_4_phones_test, EmptyPhoneList) {
  std::ostringstream os;
  std::istringstream is("0\n");
  std::streambuf *orig_cin = std::cin.rdbuf(is.rdbuf());
  std::streambuf *orig_cout = std::cout.rdbuf(os.rdbuf());

  EXPECT_EQ(phones(), 0);

  std::string expected_output = "<MobilePhones>\n</MobilePhones>\n";
  EXPECT_EQ(os.str(), expected_output);

  std::cin.rdbuf(orig_cin);
  std::cout.rdbuf(orig_cout);
}
