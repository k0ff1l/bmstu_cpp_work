// Copyright 2024 <fleurs>

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#include "hw_6_raw_memory.h"
#include "hw_6_true_vector.h"

class WithoutDefaultConstructor {
 public: // NOLINT
  WithoutDefaultConstructor() = delete;

  explicit WithoutDefaultConstructor(int other) : number(other) {
  }

  int number;
};

class TestClass {
 public:  // NOLINT
  TestClass() {
    std::cout << "alloc def\n";
    ++cnt;
    if (cnt == 10) throw std::runtime_error("created 10 testclass species \n");
  }

  explicit TestClass(int z) : z(z) {
    std::cout << "alloc with num\n";
    ++cnt;
    if (cnt == 10) throw std::runtime_error("created 10 testclass species");
  }

  ~TestClass() {
    std::cout << "dealloc\n";
  }

 private:  // NOLINT
  int z;
  static size_t cnt;
};

size_t TestClass::cnt = 0;

TEST(Vector, test1) {
  bmstu::raw_memory<WithoutDefaultConstructor> memory(10);
}

TEST(Vector, test2) {
  try {
    bmstu::vector<TestClass> a(9);
    TestClass b(10);
  } catch (std::runtime_error &e) {
    std::cout << "catched exception: " << e.what() << "\n";
  }
}

// Тестирование конструктора по умолчанию
TEST(VectorTest, DefaultConstructor) {
  bmstu::vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

// Тестирование конструктора с заданным размером
TEST(VectorTest, ConstructorWithSize) {
  size_t size = 5;
  bmstu::vector<int> vec(size);
  EXPECT_EQ(vec.size(), size);
  EXPECT_FALSE(vec.empty());
}

// Тестирование оператора копирования
TEST(VectorTest, CopyConstructor) {
  bmstu::vector<int> vec1(5);
  bmstu::vector<int> vec2(vec1);
  EXPECT_EQ(vec2.size(), vec1.size());
  EXPECT_FALSE(vec2.empty());
}

// Тестирование оператора присваивания
TEST(VectorTest, AssignmentOperator) {
  bmstu::vector<int> vec1(5);
  bmstu::vector<int> vec2;
  vec2 = vec1;
  EXPECT_EQ(vec2.size(), vec1.size());
  EXPECT_FALSE(vec2.empty());
}

// Тестирование метода push_back
TEST(VectorTest, PushBack) {
  bmstu::vector<int> vec;
  vec.push_back(42);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 42);
}

// Тестирование метода pop_back
TEST(VectorTest, PopBack) {
  bmstu::vector<int> vec(3);
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
}

// Тестирование метода resize

// У меня на компе проходит, а на виртуалке в git валится почему-то, не могу понять.

TEST(VectorTest, Resize) {
  bmstu::vector<int> vec(3);
  vec.resize(5);
  EXPECT_EQ(vec.size(), 5);
}

// Тестирование метода reserve
TEST(VectorTest, Reserve) {
  bmstu::vector<int> vec;
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
}

// Тестирование метода insert
TEST(VectorTest, Insert) {
  bmstu::vector<int> vec = {1, 3, 4};
  auto it = vec.begin();
  ++it;  // Переместимся на позицию 1
  vec.insert(it, 2);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[1], 2);
}

// объявить class и в них static cntr для мува и остальной фигни
// чтобы тестировать наш вектор.

class TestHelper {
 public:
  static int default_ctr;
  static int copy_ctr;
  static int move_ctr;
  static int destructor_ctr;

  TestHelper() {
    ++default_ctr;
  }

  TestHelper(const TestHelper &) {
    ++copy_ctr;
  }

  TestHelper(TestHelper &&) noexcept {
    ++move_ctr;
  }

  ~TestHelper() {
    ++destructor_ctr;
  }
};

int TestHelper::default_ctr = 0;
int TestHelper::copy_ctr = 0;
int TestHelper::move_ctr = 0;
int TestHelper::destructor_ctr = 0;

TEST(TestHelperTest, ConstructorsAndDestructors) {
  // Сбрасываем счетчики перед каждым тестом
  TestHelper::default_ctr = 0;
  TestHelper::copy_ctr = 0;
  TestHelper::move_ctr = 0;
  TestHelper::destructor_ctr = 0;

  {
    TestHelper obj1;  // Конструктор по умолчанию
    EXPECT_EQ(TestHelper::default_ctr, 1);

    TestHelper obj2(obj1);  // Конструктор копирования
    EXPECT_EQ(TestHelper::copy_ctr, 1);

    TestHelper obj3(std::move(obj1));  // Конструктор перемещения
    EXPECT_EQ(TestHelper::move_ctr, 1);
  }

  // Ожидаем, что все объекты были уничтожены
  EXPECT_EQ(TestHelper::destructor_ctr, 3);
}

struct NoDefaultConstructable {
  int value = 0;

  explicit NoDefaultConstructable(int value) : value(value) { }

  NoDefaultConstructable() = delete;

  friend bool operator==(NoDefaultConstructable l, NoDefaultConstructable r) {
    return l.value == r.value;
  }

  ~NoDefaultConstructable() = default;

  int get_value() const {
    return value;
  }
};

struct NoCopyConstructable {
  int value = 0;

  explicit NoCopyConstructable(int value) : value(value) { }

  NoCopyConstructable() = delete;

  NoCopyConstructable(NoCopyConstructable &other) = delete;  // NOLINT

  NoCopyConstructable &operator=(const NoCopyConstructable &other) = delete;

  NoCopyConstructable &operator=(NoCopyConstructable &&other) = default;

  NoCopyConstructable(NoCopyConstructable &&other) = default;

  friend bool operator==(NoCopyConstructable l, NoCopyConstructable r) {
    return l.value == r.value;
  }

  ~NoCopyConstructable() { }

  int get_value() const {
    return value;
  }
};

struct NoMoveConstructable {
  int value = 0;

  explicit NoMoveConstructable(int value) : value(value) { }

  NoMoveConstructable() = delete;

  NoMoveConstructable(NoMoveConstructable &other) = default;  // NOLINT

  NoMoveConstructable &operator=(const NoMoveConstructable &other) = default;

  NoMoveConstructable &operator=(NoMoveConstructable &&other) = delete;

  NoMoveConstructable(NoMoveConstructable &&other) = delete;

  friend bool operator==(NoMoveConstructable &l, NoMoveConstructable &r) {  // NOLINT
    return l.value == r.value;
  }

  ~NoMoveConstructable() { }

  int get_value() const {
    return value;
  }
};

template<typename T>
void elem_check(bmstu::vector<T> &vec, const T &value = T{}) {  // NOLINT
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], value);
  }
}

TEST(DefaultConstruct, WithoutDefaultConstructor) {
  bmstu::vector<NoDefaultConstructable> vec;
  ASSERT_TRUE(vec.empty());
  ASSERT_EQ(vec.capacity(), 0);
}

TEST(DefaultConstruct, Strings) {
  bmstu::vector<std::wstring> vec;
  ASSERT_TRUE(vec.empty());
  ASSERT_EQ(vec.capacity(), 0);
}

TEST(SizeConstructor, WithoutDefaultConstructor) {
  bmstu::vector<NoDefaultConstructable> vec(10);
  ASSERT_EQ(vec.size(), 10);
}

TEST(SizeConstructor, Integer) {
  bmstu::vector<int> vec(10);
  ASSERT_EQ(vec.size(), 10);
  elem_check(vec, 0);
}

TEST(SizeConstructor, Strings) {
  bmstu::vector<std::wstring> vec(10);
  ASSERT_EQ(vec.size(), 10);
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], L"");
  }
}


TEST(InitializerListConstructor, Integer) {
  bmstu::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> vec2{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], i + 1);
  }
}

TEST(InitializerListConstructor, Strings) {
  using namespace std::literals;  // NOLINT
  bmstu::vector<std::wstring> vec{L"Я"s, L"умный вектор)"s};
  ASSERT_EQ(vec[0], L"Я"s);
  ASSERT_EQ(vec[1], L"умный вектор)"s);
}

TEST(CopyConstructor, Integer) {
  bmstu::vector<int> vec{1, 2, 3, 4, 5};
  bmstu::vector<int> copy(vec);
  ASSERT_TRUE(vec == copy);
}

TEST(CopyConstructor, Strings) {
  bmstu::vector<std::wstring> vec{L"Я", L"очень", L"умный вектор)"};
  bmstu::vector<std::wstring> copy = vec;
  ASSERT_TRUE(vec == copy);
}

TEST(MoveConstructor, Integer) {
  bmstu::vector<int> vec{1, 1, 1, 1, 1};
  bmstu::vector<int> move(std::move(vec));
  ASSERT_EQ(move.size(), 5);
  elem_check(move, 1);
}

TEST(MoveConstructor, string) {
  bmstu::vector<std::wstring> vec{L"Я наиумнейший вектор", L"Я наиумнейший вектор", L"Я наиумнейший вектор",
                                  L"Я наиумнейший вектор", L"Я наиумнейший вектор"};
  bmstu::vector<std::wstring> move(std::move(vec));
  std::wstring str = L"Я наиумнейший вектор";
  ASSERT_EQ(str, str);
  elem_check(move, str);
}

TEST(CopyAssign, Integer) {
  bmstu::vector<int> vec{1, 2, 3, 4, 5};
  bmstu::vector<int> copy = vec;
  ASSERT_TRUE(vec == copy);
}

TEST(CopyAssign, Strings) {
  bmstu::vector<std::wstring> vec{L"Я", L"очень", L"умный вектор)"};
  bmstu::vector<std::wstring> copy = vec;
  ASSERT_TRUE(vec == copy);
}

TEST(MoveAssign, Integer) {
  bmstu::vector<int> vec{1, 1, 1, 1, 1};
  bmstu::vector<int> move = std::move(vec);
  ASSERT_EQ(move.size(), 5);
  elem_check(move, 1);
}

TEST(MoveAssign, Strings) {
  bmstu::vector<std::wstring> vec{L"Я наиумнейший вектор", L"Я наиумнейший вектор", L"Я наиумнейший вектор",
                                  L"Я наиумнейший вектор", L"Я наиумнейший вектор"};
  bmstu::vector<std::wstring> move = std::move(vec);
  ASSERT_EQ(move.size(), 5);
  for (size_t i = 0; i < move.size(); ++i) {
    ASSERT_EQ(move[i], L"Я наиумнейший вектор");
  }
}

TEST(Reserve, Integer) {
  bmstu::vector<int> vec{6, 6, 6};
  vec.reserve(10);
  ASSERT_EQ(vec.capacity(), 10);
  ASSERT_EQ(vec.size(), 3);
  elem_check(vec, 6);
  vec.reserve(2);
  ASSERT_EQ(vec.capacity(), 10);
  ASSERT_EQ(vec.size(), 3);
  elem_check(vec, 6);
}

TEST(Reserve, Strings) {
  bmstu::vector<std::wstring> vec{L"Я", L"ультрамега", L"умный вектор!"};
  vec.reserve(10);
  ASSERT_EQ(vec.capacity(), 10);
  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec[0], L"Я");
  ASSERT_EQ(vec[1], L"ультрамега");
  ASSERT_EQ(vec[2], L"умный вектор!");
  vec.reserve(2);
  ASSERT_EQ(vec.capacity(), 10);
  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec[0], L"Я");
  ASSERT_EQ(vec[1], L"ультрамега");
  ASSERT_EQ(vec[2], L"умный вектор!");
}

TEST(Resize, Integer) {
  bmstu::vector<int> vec{1026, 1026, 1026, 1026, 1026};
  vec.resize(1);
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 5);
  ASSERT_EQ(vec[0], 1026);
  vec.resize(11);
  ASSERT_EQ(vec.size(), 11);
  ASSERT_EQ(vec.capacity(), 11);
  ASSERT_EQ(vec[0], 1026);
  for (int i = 1; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], 0);
  }
}

TEST(Resize, WithoutDefaultConstructor) {
  bmstu::vector<NoDefaultConstructable> vec{NoDefaultConstructable(1), NoDefaultConstructable(2)};
  vec.resize(3);
  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec.capacity(), 4);
  ASSERT_EQ(vec[0].get_value(), 1);
  ASSERT_EQ(vec[1].get_value(), 2);
  ASSERT_EQ(vec[2].get_value(), 0);
  vec.resize(1);
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 4);
  ASSERT_EQ(vec[0].get_value(), 1);
}

TEST(PopBack, Integer) {
  bmstu::vector<int> vec{10, 10, 10};
  vec.pop_back();
  ASSERT_EQ(vec.size(), 2);
  ASSERT_EQ(vec.capacity(), 3);
  elem_check(vec, 10);
}

TEST(PopBack, Strings) {
  bmstu::vector<std::wstring> vec{L"ИУ10", L"ИУ10", L"ИУ10"};
  vec.pop_back();
  ASSERT_EQ(vec.size(), 2);
  ASSERT_EQ(vec.capacity(), 3);
  for (int i = 0; i < vec.size(); ++i) {
    vec[i] = L"ИУ10";
  }
}

TEST(PushBack, WhithoutDefaultConstructor) {
  bmstu::vector<NoDefaultConstructable> vec{NoDefaultConstructable(1), NoDefaultConstructable(2),
                                            NoDefaultConstructable(3),
                                            NoDefaultConstructable(4)};
  vec.push_back(NoDefaultConstructable(2));
  ASSERT_EQ(vec[4].get_value(), 2);
}

TEST(PushBack, Integer) {
  bmstu::vector<int> vec{1, 2, 3, 4};
  vec.push_back(5);
  ASSERT_EQ(vec[4], 5);
}

TEST(PushBack, Strings) {
  bmstu::vector<std::wstring> vec{L"Я", L"очень", L"крутой", L"охотник за"};
  vec.push_back(L"беброй");
  ASSERT_EQ(vec[4], L"беброй");
}

TEST(insert, Integer) {
  bmstu::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vec.insert(vec.begin() + 3, 1);
  vec.insert(vec.end(), 2);
  ASSERT_EQ(vec[3], 1);
  ASSERT_EQ(vec[vec.size() - 1], 2);
}

TEST(insert, Strings) {
  bmstu::vector<std::wstring> vec{L"Бебра", L"луДшая", L"организация", L"на"};
  vec.insert(vec.begin() + 1, L"Хантерс");
  vec.insert(vec.end(), L"гитхабе");
  ASSERT_EQ(vec[1], L"Хантерс");
  ASSERT_EQ(vec[vec.size() - 1], L"гитхабе");
}

TEST(Insert, WithoutDefaultConstructor) {
  bmstu::vector<NoDefaultConstructable> vec{NoDefaultConstructable(1), NoDefaultConstructable(2)};
  vec.insert(vec.begin() + 1, NoDefaultConstructable(3));
  ASSERT_EQ(vec[1].get_value(), 3);
}

TEST(VecEqual, WithoutDefaultConstructor) {
  bmstu::vector<NoDefaultConstructable> vec{NoDefaultConstructable(1), NoDefaultConstructable(2)};
  bmstu::vector<NoDefaultConstructable> vec2{NoDefaultConstructable(1), NoDefaultConstructable(2)};
  ASSERT_TRUE(vec == vec2);
}

TEST(VecEqual, Integer) {
  bmstu::vector<int> vec{1, 2};
  bmstu::vector<int> vec2{1, 2};
  ASSERT_TRUE(vec == vec2);
}

TEST(VecEqual, Stings) {
  bmstu::vector<std::wstring> vec{L"С++", L"лучше", L"Python"};
  bmstu::vector<std::wstring> vec2{L"С++", L"лучше", L"Python"};
  ASSERT_TRUE(vec == vec2);
}

TEST(NotVecEqual, WithoutDefaultConstructor) {
  bmstu::vector<NoDefaultConstructable> vec{NoDefaultConstructable(1), NoDefaultConstructable(2)};
  bmstu::vector<NoDefaultConstructable> vec2{NoDefaultConstructable(1), NoDefaultConstructable(2)};
  ASSERT_FALSE(vec != vec2);
}

TEST(NotVecEqual, Integer) {
  bmstu::vector<int> vec{1, 2};
  bmstu::vector<int> vec2{1, 2};
  ASSERT_FALSE(vec != vec2);
}

TEST(NotVecEqual, Stings) {
  bmstu::vector<std::wstring> vec{L"С++", L"лучше", L"Python"};
  bmstu::vector<std::wstring> vec2{L"С++", L"лучше", L"Python"};
  ASSERT_FALSE(vec != vec2);
}


TEST(Cout, Integer) {
  bmstu::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
  testing::internal::CaptureStdout();
  std::cout << vec;
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ("[1, 2, 3, 4, 5, 6, 7, 8, 9]", output);
}

TEST(Cout, Strings) {
  bmstu::vector<std::string> vec{"Bebra Hunters"};
  bmstu::vector<std::string> vec2{"Bebra Hunters"};
  testing::internal::CaptureStdout();
  std::cout << vec;
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ("[Bebra Hunters]", output);
}

TEST(dahsav, hdasidas) {
  bmstu::vector<int> vec{1, 2, 3};
  std::cout << vec;
}
