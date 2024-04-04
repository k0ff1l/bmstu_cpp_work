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


// Тестирование метода pop_back

// Тестирование метода resize

// У меня на компе проходит, а на виртуалке в git валится почему-то, не могу понять.

// Тестирование метода reserve

// Тестирование метода insert

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

TEST(VectorTest, VectorInsert) {
  bmstu::vector<int> vec{0, 1, 2, 3, 4};
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec.capacity(), 5);
  vec.insert(vec.begin() + 3, 666);
  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec.capacity(), 10);
  ASSERT_EQ(vec[0], 0);
  ASSERT_EQ(vec[1], 1);
  ASSERT_EQ(vec[2], 2);
  ASSERT_EQ(vec[3], 666);
  ASSERT_EQ(vec[4], 3);
  ASSERT_EQ(vec[5], 4);
}

TEST(Resize, Strings) {
  bmstu::vector<std::wstring> vec{L"Бебра", L"Хантерс", L"обязательно", L"помогут", L"девочкам"};
  vec.resize(1);
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 5);
  ASSERT_EQ(vec[0], L"Бебра");
  vec.resize(10);
  ASSERT_EQ(vec.size(), 10);
  ASSERT_EQ(vec.capacity(), 10);
  ASSERT_EQ(vec[0], L"Бебра");
  for (int i = 1; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], L"");
  }
}


TEST(VectorTest, null) {
  bmstu::vector<int> a;
  ASSERT_EQ(a.capacity(), 0);
  ASSERT_EQ(a.size(), 0);
}

TEST(VectorTest, pushback) {
  bmstu::vector<int> a;
  ASSERT_EQ(a.capacity(), 0);
  ASSERT_EQ(a.size(), 0);
  a.push_back(6);
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.capacity(), 1);
  a.push_back(6);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.capacity(), 2);
  a.push_back(6);
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.capacity(), 4);
  a.push_back(6);
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.capacity(), 4);
  a.push_back(6);
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 8);
}

TEST(VectorTest, insert) {
  bmstu::vector<int> v;
  bmstu::vector<int> v_expected{0, 666, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }
  v.insert(v.begin() + 1, 666);
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(v[i], v_expected[i]);
  }
}

TEST(VectorTest, lexical) {
  bmstu::vector<char> v{'1', '2', '3'};
  bmstu::vector<char> v_c{'1', '2', '3'};
  ASSERT_TRUE(!(v > v_c));
  ASSERT_TRUE(v >= v_c);
  ASSERT_TRUE(v == v_c);
}

TEST(VectorTest, complex) {
  bmstu::vector<int> v;
  v.push_back(23);
  ASSERT_EQ(v[0], 23);
  size_t big_number = 1;
  for (size_t i = 0; i < 10; ++i) {
    big_number *= 2;
  }
  for (size_t i = 0; i < big_number; ++i) {
    v.push_back(i);
  }
  ASSERT_EQ(v.size(), big_number + 1);
  for (size_t i = 0; i < big_number; ++i) {
    v.pop_back();
  }
  ASSERT_EQ(v.size(), 1);
}

TEST(VectorTest, 1reserve) {
  bmstu::vector<int> vec;
  vec.reserve(10);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 10);
  for (size_t i = 0; i < vec.capacity(); ++i) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), 10);
  EXPECT_EQ(vec.capacity(), 10);
}

TEST(VectorTest, DefaultVectorTest) {
  bmstu::vector<int> vec_default;
  EXPECT_EQ(vec_default.size(), 0);
  EXPECT_EQ(vec_default.capacity(), 0);
}

TEST(VectorTest, VectorTestWithSizeAndValue) {
  bmstu::vector<int> vec_with_size(5, 42);
  EXPECT_EQ(vec_with_size.size(), 5);
  EXPECT_EQ(vec_with_size.capacity(), 5);
  for (int value : vec_with_size) {
    EXPECT_EQ(value, 42);
  }
}

TEST(VectorTest, CopyVectorTest) {
  bmstu::vector<int> original(3, 7);
  bmstu::vector<int> copy(original);
  EXPECT_EQ(original.size(), copy.size());
  EXPECT_EQ(original.capacity(), copy.capacity());
  EXPECT_TRUE(std::equal(original.begin(), original.end(), copy.begin()));
}

TEST(VectorTest, MoveVectorTest) {
  bmstu::vector<int> original(3, 7);
  bmstu::vector<int> moved(std::move(original));
  EXPECT_EQ(original.size(), 0);
  EXPECT_EQ(original.capacity(), 0);
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.capacity(), 3);
  moved.push_back(4);
  ASSERT_EQ(moved.capacity(), 6);
  ASSERT_EQ(moved[3], 4);
}

TEST(VectorTest, Resize) {
  bmstu::vector<int> vec;
  vec.resize(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec.capacity(), 5);
}

TEST(VectorTest, Reserve) {
  bmstu::vector<int> vec;
  vec.reserve(10);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 10);
}

TEST(VectorTest, 1Insert) {
  bmstu::vector<int> vec = {1, 2, 3};
  auto it = vec.insert(vec.begin() + 1, 42);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[1], 42);
  EXPECT_EQ(*it, 42);
}

TEST(VectorTest, PushBack) {
  bmstu::vector<int> vec = {1, 2, 3};
  vec.push_back(42);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[3], 42);
  vec.clear();
  vec.push_back(42);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 42);
}

TEST(VectorTest, At) {
  bmstu::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.at(1), 2);
}

TEST(VectorTest, PopBack) {
  bmstu::vector<int> vec = {1, 2, 3};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, Swap) {
  bmstu::vector<int> vec1 = {1, 2, 3};
  bmstu::vector<int> vec2 = {4, 5, 6};
  vec1.swap(vec2);
  EXPECT_EQ(vec1.size(), 3);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec2[0], 1);
}

TEST(VectorTest, Equality) {
  bmstu::vector<int> vec1 = {1, 2, 3, 4, 5};
  bmstu::vector<int> vec2 = {1, 2, 3, 4, 5};
  bmstu::vector<int> vec3 = {1, 2, 3, 4, 6};
  ASSERT_TRUE(vec1 == vec2);
  ASSERT_FALSE(vec1 == vec3);
}

TEST(VectorTest, Comparison) {
  bmstu::vector<int> vec1 = {1, 2, 3, 4, 5};
  bmstu::vector<int> vec2 = {1, 2, 3, 4, 5};
  bmstu::vector<int> vec3 = {1, 2, 3, 4, 6};
  bmstu::vector<int> vec4 = {1, 2, 3};
  ASSERT_TRUE(vec1 == vec2);
  ASSERT_TRUE(vec1 < vec3);
  ASSERT_TRUE(vec4 < vec1);
  ASSERT_TRUE(vec3 > vec2);
}

TEST(VectorTest, OutputVectorTest) {
  bmstu::vector<int> vec = {1, 2, 3, 4, 5};
  std::stringstream ss;
  ss << vec;
  ASSERT_EQ(ss.str(), "[1, 2, 3, 4, 5]");
}

TEST(VectorTest, Default) {
  bmstu::vector<int> my_vec;
  ASSERT_EQ(my_vec.size(), 0);
  ASSERT_EQ(my_vec.capacity(), 0);
}

TEST(VectorTest, InList) {
  bmstu::vector my_vec({0, 1, 2});
  ASSERT_EQ(my_vec.size(), 3);
  ASSERT_EQ(my_vec.capacity(), 3);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], i);
    ASSERT_EQ(my_vec.at(i), i);
  }
}

TEST(VectorTest, Parametr) {
  bmstu::vector my_vec(4, 20);
  ASSERT_EQ(my_vec.size(), 4);
  ASSERT_EQ(my_vec.capacity(), 4);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], 20);
    ASSERT_EQ(my_vec.at(i), 20);
  }
}

TEST(VectorTest, 1Copy) {
  bmstu::vector my_vec1(4, 20);
  bmstu::vector my_vec2(my_vec1);
  ASSERT_EQ(my_vec1.size(), 4);
  ASSERT_EQ(my_vec1.capacity(), 4);
  ASSERT_EQ(my_vec2.size(), my_vec1.size());
  ASSERT_EQ(my_vec2.capacity(), my_vec1.capacity());
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec1[i], 20);
    ASSERT_EQ(my_vec1.at(i), 20);
    ASSERT_EQ(my_vec2[i], 20);
    ASSERT_EQ(my_vec2.at(i), 20);
  }
}

TEST(VectorTest, 1Move) {
  bmstu::vector my_vec1(4, 20);
  bmstu::vector my_vec2(std::move(my_vec1));
  ASSERT_EQ(my_vec1.size(), 0);
  ASSERT_EQ(my_vec1.capacity(), 0);
  ASSERT_EQ(my_vec2.size(), 4);
  ASSERT_EQ(my_vec2.capacity(), 4);
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec2[i], 20);
    ASSERT_EQ(my_vec2.at(i), 20);
  }
}

TEST(VectorTest, Copy) {
  bmstu::vector my_vec1(4, 20);
  bmstu::vector my_vec2 = my_vec1;
  ASSERT_EQ(my_vec1.size(), 4);
  ASSERT_EQ(my_vec1.capacity(), 4);
  ASSERT_EQ(my_vec2.size(), my_vec1.size());
  ASSERT_EQ(my_vec2.capacity(), my_vec1.capacity());
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec1[i], 20);
    ASSERT_EQ(my_vec1.at(i), 20);
    ASSERT_EQ(my_vec2[i], 20);
    ASSERT_EQ(my_vec2.at(i), 20);
  }
}

TEST(VectorTest, Move) {
  bmstu::vector my_vec1(4, 20);
  bmstu::vector my_vec2 = std::move(my_vec1);
  ASSERT_EQ(my_vec1.size(), 0);
  ASSERT_EQ(my_vec1.capacity(), 0);
  ASSERT_EQ(my_vec2.size(), 4);
  ASSERT_EQ(my_vec2.capacity(), 4);
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec2[i], 20);
    ASSERT_EQ(my_vec2.at(i), 20);
  }
}

TEST(VectorTest, BeginAndEnd) {
  bmstu::vector my_vec({0, 1, 2, 3, 4, 5});
  bmstu::vector<int>::iterator itb = my_vec.begin();
  bmstu::vector<int>::iterator ite = my_vec.end();
  size_t n = 0;
  for (; itb != ite; ++itb) {
    ASSERT_EQ(*itb, n);
    n += 1;
  }
}

TEST(VectorTest, Empty) {
  bmstu::vector<int> my_vec1;
  bmstu::vector my_vec2({1, 2, 3});
  ASSERT_TRUE(my_vec1.empty());
  ASSERT_FALSE(my_vec2.empty());
}

TEST(VectorTest, clear) {
  bmstu::vector my_vec({1, 2, 3});
  my_vec.clear();
  ASSERT_EQ(my_vec.size(), 0);
  ASSERT_EQ(my_vec.capacity(), 3);
}

TEST(VectorTest, SwapV1) {
  bmstu::vector my_vec1(4, 20);
  bmstu::vector my_vec2(13, 3);
  my_vec1.swap(my_vec2);
  ASSERT_EQ(my_vec1.size(), 13);
  ASSERT_EQ(my_vec1.capacity(), 13);
  ASSERT_EQ(my_vec2.size(), 4);
  ASSERT_EQ(my_vec2.capacity(), 4);
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec1[i], 3);
  }
  for (size_t i = 0; i < my_vec2.size(); ++i) {
    ASSERT_EQ(my_vec2[i], 20);
  }
}

TEST(VectorTest, SwapV2) {
  bmstu::vector my_vec1(4, 20);
  bmstu::vector my_vec2(13, 3);
  swap(my_vec1, my_vec2);
  ASSERT_EQ(my_vec1.size(), 13);
  ASSERT_EQ(my_vec1.capacity(), 13);
  ASSERT_EQ(my_vec2.size(), 4);
  ASSERT_EQ(my_vec2.capacity(), 4);
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec1[i], 3);
  }
  for (size_t i = 0; i < my_vec2.size(); ++i) {
    ASSERT_EQ(my_vec2[i], 20);
  }
}

TEST(VectorTest, resize) {
  bmstu::vector my_vec(5, 20);
  my_vec.resize(4);
  ASSERT_EQ(my_vec.size(), 4);
  ASSERT_EQ(my_vec.capacity(), 5);

  my_vec.resize(7);
  ASSERT_EQ(my_vec.size(), 7);
  ASSERT_EQ(my_vec.capacity(), 10);

  my_vec.resize(21);
  ASSERT_EQ(my_vec.size(), 21);
  ASSERT_EQ(my_vec.capacity(), 21);
}

TEST(VectorTest, reserve) {
  bmstu::vector my_vec(5, 20);
  my_vec.reserve(21);
  ASSERT_EQ(my_vec.size(), 5);
  ASSERT_EQ(my_vec.capacity(), 21);
}

TEST(VectorTest, Insert) {
  bmstu::vector my_vec = {0, 1, 2, 4, 5, 6};
  bmstu::vector<int>::iterator it = my_vec.begin() + 3;
  my_vec.insert(it, 3);
  ASSERT_EQ(my_vec.size(), 7);
  ASSERT_EQ(my_vec.capacity(), 12);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], i);
  }

  bmstu::vector<int> vec = {1, 3, 4};
  it = vec.begin();
  ++it;  // Переместимся на позицию 1
  vec.insert(it, 2);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, Push_Pop_back) {
  bmstu::vector my_vec = {0, 1, 2, 3, 4, 5, 6};
  my_vec.push_back(7);
  ASSERT_EQ(my_vec.size(), 8);
  ASSERT_EQ(my_vec.capacity(), 14);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], i);
  }
  my_vec.pop_back();
  ASSERT_EQ(my_vec.size(), 7);
  ASSERT_EQ(my_vec.capacity(), 14);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], i);
  }
}

TEST(VectorTest, EQs) {
  bmstu::vector my_vec1 = {0, 1, 2, 3, 4, 5, 6};
  bmstu::vector my_vec2 = {0, 1, 2, 3, 4, 5, 6};
  bmstu::vector my_vec3 = {0, 1, 2, 3, 4, 5, 7};
  bmstu::vector my_vec4 = {1, 2, 3, 4, 5, 7, 8};
  bmstu::vector my_vec5 = {1, 1, 2, 3, 4, 5, 7};
  ASSERT_TRUE(my_vec1 == my_vec2);
  ASSERT_FALSE(my_vec1 == my_vec3);
  ASSERT_TRUE(my_vec1 != my_vec3);
  ASSERT_FALSE(my_vec1 != my_vec2);
  ASSERT_TRUE(my_vec1 < my_vec4);
  ASSERT_TRUE(my_vec4 > my_vec1);
  ASSERT_TRUE(my_vec1 <= my_vec5);
  ASSERT_TRUE(my_vec5 >= my_vec1);
}

TEST(VectorTest, one) {
  bmstu::vector<int> v;
  ASSERT_EQ(v.size(), 0u);
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.capacity(), 0u);
}

//
//
TEST(VectorTest, Init) {
  // Инициализация вектора указанного размера
  bmstu::vector<int> v(5);
  ASSERT_EQ(v.size(), 5u);
  ASSERT_EQ(v.capacity(), 5u);
  ASSERT_TRUE(!v.empty());
  for (size_t i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], 0);
  }
}

TEST(VectorTest, Init2) {
  bmstu::vector<int> v(3, 42);
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 3);
  for (size_t i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], 42);
  }
}

//
TEST(VectorTest, InitList) {
  bmstu::vector<int> v{1, 2, 3};
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 3);
  ASSERT_EQ(v[2], 3);
}

//
TEST(VectorTest, Resize1) {
  {
    bmstu::vector<int> v(3);
    v[0] = 42;
    v[1] = 55;
    const size_t old_capacity = v.capacity();
    v.resize(2);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), old_capacity);
    ASSERT_EQ(v[0], 42);
    ASSERT_EQ(v[1], 55);
  }
}

//
TEST(VectorTest, Resize2) {
  const size_t old_size = 3;
  bmstu::vector<int> v(3);
  v.resize(old_size + 5);
  v[3] = 42;
  v.resize(old_size);
  ASSERT_EQ(v[2], 0);
  v.resize(old_size + 3);
  ASSERT_EQ(v[3], 0);
}

//
TEST(VectorTest, VectorTests) {
  {
    bmstu::vector<int> v(5);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    bmstu::vector<int> c(v);
    ASSERT_EQ(v[2], v[2]);
  }
  {
    bmstu::vector<int> v(5);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    bmstu::vector<int> c(v);
    ASSERT_EQ(v[2], v[2]);
  }
  {
    bmstu::vector<int> v(1);
    v.push_back(1);
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(*(v.begin()) + 1, 1);
  }
}

TEST(VectorTest, Push) {
  bmstu::vector<int> v(1);
  v.push_back(42);
  ASSERT_EQ(v.size(), 2);
  ASSERT_TRUE(v.capacity() >= v.size());
  ASSERT_EQ(v[0], 0);
  ASSERT_EQ(v[1], 42);
}

TEST(VectorTest, CopyConstruct) {
  bmstu::vector<int> numbers{1, 2};
  auto numbers_copy(numbers);
  ASSERT_TRUE(&numbers_copy[0] != &numbers[0]);
  ASSERT_EQ(numbers_copy.size(), numbers.size());
  for (size_t i = 0; i < numbers.size(); ++i) {
    ASSERT_EQ(numbers_copy[i], numbers[i]);
    ASSERT_TRUE(&numbers_copy[i] != &numbers[i]);
  }
}

TEST(VectorTest, Capacity) {
  bmstu::vector<int> v(2);
  v.resize(1);
  const size_t old_capacity = v.capacity();
  v.push_back(123);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), old_capacity);
}

TEST(VectorTest, Iterate) {
  // Итерирование по bmstu::vector
  {
    // Непустой вектор
    {
      bmstu::vector<int> v(10, 42);
      //            ASSERT_TRUE(v.begin());
      ASSERT_EQ(*v.begin(), 42);
      ASSERT_EQ(v.end(), v.begin() + v.size());
    }
  }
}

TEST(VectorTest, Compare) {
  {
    ASSERT_TRUE((bmstu::vector{1, 2, 3} == bmstu::vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::vector{1, 2, 3} != bmstu::vector{1, 2, 2}));

    ASSERT_TRUE((bmstu::vector{1, 2, 3}
                 < bmstu::vector{1, 2, 3, 1}));
    ASSERT_TRUE((bmstu::vector{1, 2, 3}
                 > bmstu::vector{1, 2, 2, 1}));

    ASSERT_TRUE((bmstu::vector{1, 2, 3} >= bmstu::vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::vector{1, 2, 4} >= bmstu::vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::vector{1, 2, 3} <= bmstu::vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::vector{1, 2, 3} <= bmstu::vector{1, 2, 4}));
  }
}

TEST(VectorTest, Pushback2) {
  bmstu::vector<int> v2;
  v2.push_back(0);
  v2.push_back(1);
  v2.push_back(2);
  ASSERT_EQ(v2, (bmstu::vector<int>{0, 1, 2}));
}

TEST(VectorTest, Swap2) {
  // Обмен значений векторов
  {
    bmstu::vector<int> v1{42, 666};
    bmstu::vector<int> v2;
    v2.push_back(0);
    v2.push_back(1);
    v2.push_back(2);
    const int *const begin1 = &v1[0];
    const int *const begin2 = &v2[0];

    const size_t capacity1 = v1.capacity();
    const size_t capacity2 = v2.capacity();

    const size_t size1 = v1.size();
    const size_t size2 = v2.size();

    v1.swap(v2);
    ASSERT_TRUE(&v2[0] == begin1);
    ASSERT_TRUE(&v1[0] == begin2);
    ASSERT_TRUE(v1.size() == size2);
    ASSERT_TRUE(v2.size() == size1);
    ASSERT_TRUE(v1.capacity() == capacity2);
    ASSERT_TRUE(v2.capacity() == capacity1);
  }
}

TEST(VectorTest, Test1) {
  bmstu::vector<int> src_vector{1, 2, 3, 4};
  bmstu::vector<int> dst_vector{1, 2, 3, 4, 5, 6};
  dst_vector = src_vector;
  ASSERT_EQ(dst_vector, src_vector);
}

TEST(VectorTest, Insert2) {
  // Вставка элементов

  bmstu::vector<int> v;
  v.insert(v.begin(), 42);
  ASSERT_EQ(v, (bmstu::vector<int>{42}));
}

TEST(VectorTest, Reserve2) {
  {
    bmstu::vector<int> v(5);
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_FALSE(v.empty());
  }
  {
    bmstu::vector<int> v;
    // зарезервируем 5 мест в векторе
    v.reserve(5);
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_TRUE(v.empty());

    // попытаемся уменьшить capacity до 1
    v.reserve(1);
    // capacity должно остаться прежним
    ASSERT_EQ(v.capacity(), 5);
    // поместим 10 элементов в вектор
    for (int i = 0; i < 10; ++i) {
      v.push_back(i);
    }
    ASSERT_EQ(v.size(), 10);
    // увеличим capacity до 100
    v.reserve(100);
    // проверим, что размер не поменялся
    ASSERT_EQ(v.size(), 10);
    ASSERT_EQ(v.capacity(), 100);
    // проверим, что элементы на месте
    for (int i = 0; i < 10; ++i) {
      ASSERT_EQ(v[i], i);
    }
  }
}

bmstu::vector<int> GenerateVector(size_t size) {
  bmstu::vector<int> v(size);
  std::iota(v.begin(), v.end(), 1);
  return v;
}

TEST(VectorTest, temporary) {
  const size_t size = 1000000;
  bmstu::vector<int> moved_vector(GenerateVector(size));
  ASSERT_EQ(moved_vector.size(), size);
}

TEST(VectorTest, moveconstructor) {
  const size_t size = 1000000;

  bmstu::vector<int> vector_to_move(GenerateVector(size));
  ASSERT_EQ(vector_to_move.size(), size);

  bmstu::vector<int> moved_vector(std::move(vector_to_move));
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);
}

TEST(VectorTest, moveoperator) {
  const size_t size = 1000000;
  bmstu::vector<int> vector_to_move(GenerateVector(size));
  ASSERT_EQ(vector_to_move.size(), size);

  bmstu::vector<int> moved_vector = std::move(vector_to_move);
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);
}

TEST(VectorTest, test_new_push) {
  bmstu::vector<int> v;
  ASSERT_EQ(v.capacity(), 0);
  ASSERT_EQ(v.size(), 0);
  v.push_back(1);
  ASSERT_EQ(v.capacity(), 1);
  ASSERT_EQ(v.size(), 1);
  v.push_back(2);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
}

TEST(VectorTest, 1one) {
  bmstu::vector<int> v;
  ASSERT_EQ(v.size(), 0u);
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.capacity(), 0u);
}

//
//
TEST(VectorTest, 1Init) {
  // Инициализация вектора указанного размера
  bmstu::vector<int> v(5);
  ASSERT_EQ(v.size(), 5u);
  ASSERT_EQ(v.capacity(), 5u);
  ASSERT_TRUE(!v.empty());
  for (size_t i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], 0);
  }
}

TEST(VectorTest, 1Init2) {
  bmstu::vector<int> v(3, 42);
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 3);
  for (size_t i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], 42);
  }
}

//
TEST(VectorTest, 1InitList) {
  bmstu::vector<int> v{1, 2, 3};
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 3);
  ASSERT_EQ(v[2], 3);
}

//
TEST(VectorTest, 1At) {
  bmstu::vector<int> v(3);
  ASSERT_EQ(&v.at(2), &v[2]);
  try {
    v.at(3);
  }
  catch (std::out_of_range const &err) {
    EXPECT_EQ(err.what(), std::string("Index out of range"));
  }
}

//
TEST(VectorTest, 1Clear) {
  bmstu::vector<int> v(10);
  const size_t old_capacity = v.capacity();
  v.clear();
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), old_capacity);
}

//
TEST(VectorTest, 1Resize) {
  // Изменение размера
  {
    bmstu::vector<int> v(3);
    v[2] = 17;
    v.resize(7);
    ASSERT_EQ(v.size(), 7);
    ASSERT_TRUE(v.capacity() >= v.size());
    ASSERT_EQ(v[2], 17);
    ASSERT_EQ(v[3], 0);
  }
}

//
TEST(VectorTest, 1Resize1) {
  {
    bmstu::vector<int> v(3);
    v[0] = 42;
    v[1] = 55;
    const size_t old_capacity = v.capacity();
    v.resize(2);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), old_capacity);
    ASSERT_EQ(v[0], 42);
    ASSERT_EQ(v[1], 55);
  }
}

//
TEST(VectorTest, 1Resize2) {
  const size_t old_size = 3;
  bmstu::vector<int> v(3);
  v.resize(old_size + 5);
  v[3] = 42;
  v.resize(old_size);
  ASSERT_EQ(v[2], 0);
  v.resize(old_size + 3);
  ASSERT_EQ(v[3], 0);
}

//
TEST(VectorTest, 1Constructors) {
  {
    bmstu::vector<int> v(5);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    bmstu::vector<int> c(v);
    ASSERT_EQ(v[2], v[2]);
  }
  {
    bmstu::vector<int> v(5);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    bmstu::vector<int> c(v);
    ASSERT_EQ(v[2], v[2]);
  }
  {
    bmstu::vector<int> v(1);
    v.push_back(1);
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(*(v.begin()) + 1, 1);
  }
}

TEST(VectorTest, 1Push) {
  bmstu::vector<int> v(1);
  v.push_back(42);
  ASSERT_EQ(v.size(), 2);
  ASSERT_TRUE(v.capacity() >= v.size());
  ASSERT_EQ(v[0], 0);
  ASSERT_EQ(v[1], 42);
}

TEST(VectorTest, 1CopyConstruct) {
  bmstu::vector<int> numbers{1, 2};
  auto numbers_copy(numbers);
  ASSERT_TRUE(&numbers_copy[0] != &numbers[0]);
  ASSERT_EQ(numbers_copy.size(), numbers.size());
  for (size_t i = 0; i < numbers.size(); ++i) {
    ASSERT_EQ(numbers_copy[i], numbers[i]);
    ASSERT_TRUE(&numbers_copy[i] != &numbers[i]);
  }
}

TEST(VectorTest, 1PopBack) {
  // PopBack
  {
    bmstu::vector<int> v{0, 1, 2, 3};
    const size_t old_capacity = v.capacity();
    const auto old_begin = v.begin();
    v.pop_back();
    ASSERT_EQ(v.capacity(), old_capacity);
    ASSERT_EQ(v.begin(), old_begin);
    ASSERT_EQ(v, (bmstu::vector<int>{0, 1, 2}));
  }
}

TEST(VectorTest, 1Capacity) {
  bmstu::vector<int> v(2);
  v.resize(1);
  const size_t old_capacity = v.capacity();
  v.push_back(123);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), old_capacity);
}

TEST(VectorTest, 1Iterate) {
  // Итерирование по bmstu::vector
  {
    // Пустой вектор
    {
      bmstu::vector<int> v;
      ASSERT_EQ(v.begin(), nullptr);
      ASSERT_EQ(v.end(), nullptr);
    }

    // Непустой вектор
    {
      bmstu::vector<int> v(10, 42);
      //            ASSERT_TRUE(v.begin());
      ASSERT_EQ(*v.begin(), 42);
      ASSERT_EQ(v.end(), v.begin() + v.size());
    }
  }
}

TEST(VectorTest, 1Compare) {
  {
    ASSERT_TRUE((bmstu::vector{1, 2, 3} == bmstu::vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::vector{1, 2, 3} != bmstu::vector{1, 2, 2}));

    ASSERT_TRUE((bmstu::vector{1, 2, 3}
                 < bmstu::vector{1, 2, 3, 1}));
    ASSERT_TRUE((bmstu::vector{1, 2, 3}
                 > bmstu::vector{1, 2, 2, 1}));

    ASSERT_TRUE((bmstu::vector{1, 2, 3} >= bmstu::vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::vector{1, 2, 4} >= bmstu::vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::vector{1, 2, 3} <= bmstu::vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::vector{1, 2, 3} <= bmstu::vector{1, 2, 4}));
  }
}

TEST(VectorTest, 1Pushback2) {
  bmstu::vector<int> v2;
  v2.push_back(0);
  v2.push_back(1);
  v2.push_back(2);
  ASSERT_EQ(v2, (bmstu::vector<int>{0, 1, 2}));
}

TEST(VectorTest, 1Swap) {
  // Обмен значений векторов
  {
    bmstu::vector<int> v1{42, 666};
    bmstu::vector<int> v2;
    v2.push_back(0);
    v2.push_back(1);
    v2.push_back(2);
    const int *const begin1 = &v1[0];
    const int *const begin2 = &v2[0];

    const size_t capacity1 = v1.capacity();
    const size_t capacity2 = v2.capacity();

    const size_t size1 = v1.size();
    const size_t size2 = v2.size();

    v1.swap(v2);
    ASSERT_TRUE(&v2[0] == begin1);
    ASSERT_TRUE(&v1[0] == begin2);
    ASSERT_TRUE(v1.size() == size2);
    ASSERT_TRUE(v2.size() == size1);
    ASSERT_TRUE(v1.capacity() == capacity2);
    ASSERT_TRUE(v2.capacity() == capacity1);
  }
}

TEST(VectorTest, 1Test1) {
  {
    bmstu::vector<int> src_vector{1, 2, 3, 4};
    bmstu::vector<int> dst_vector{1, 2, 3, 4, 5, 6};
    dst_vector = src_vector;
    ASSERT_EQ(dst_vector, src_vector);
  }
}

TEST(VectorTest, 11Insert) {
  // Вставка элементов
  {
    bmstu::vector<int> v{1, 2, 3, 4};
    auto vit = v.begin() + 3;
    v.insert(v.begin() + 2, 42);
    ASSERT_EQ(v, (bmstu::vector<int>{1, 2, 42, 3, 4}));
  }
}

TEST(VectorTest, 1Insert2) {
  // Вставка элементов

  bmstu::vector<int> v;
  v.insert(v.begin(), 42);
  ASSERT_EQ(v, (bmstu::vector<int>{42}));
}

TEST(VectorTest, 1Erase) {
  {
    bmstu::vector<int> v{1, 2, 3, 4};
    v.erase(v.begin() + 2);

    ASSERT_EQ(v, (bmstu::vector<int>{1, 2, 4}));
  }
}

TEST(VectorTest, 1Reserve) {
  {
    bmstu::vector<int> v(5);
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_FALSE(v.empty());
  }
  {
    bmstu::vector<int> v;
    // зарезервируем 5 мест в векторе
    v.reserve(5);
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_TRUE(v.empty());

    // попытаемся уменьшить capacity до 1
    v.reserve(1);
    // capacity должно остаться прежним
    ASSERT_EQ(v.capacity(), 5);
    // поместим 10 элементов в вектор
    for (int i = 0; i < 10; ++i) {
      v.push_back(i);
    }
    ASSERT_EQ(v.size(), 10);
    // увеличим capacity до 100
    v.reserve(100);
    // проверим, что размер не поменялся
    ASSERT_EQ(v.size(), 10);
    ASSERT_EQ(v.capacity(), 100);
    // проверим, что элементы на месте
    for (int i = 0; i < 10; ++i) {
      ASSERT_EQ(v[i], i);
    }
  }
}

class X {
 public:
  X()
      : X(5) {
  }

  explicit X(size_t num)
      : x_(num) {
  }

  X(const X &other) = delete;

  X &operator=(const X &other) = delete;

  X(X &&other) {
    x_ = std::exchange(other.x_, 0);
  }

  X &operator=(X &&other) {
    x_ = std::exchange(other.x_, 0);
    return *this;
  }

  size_t GetX() const {
    return x_;
  }

 private:
  size_t x_;
};

TEST(VectorTest, 1temporary) {
  const size_t size = 1000000;
  bmstu::vector<int> moved_vector(GenerateVector(size));
  ASSERT_EQ(moved_vector.size(), size);
}

TEST(VectorTest, 1moveconstructor) {
  const size_t size = 1000000;

  bmstu::vector<int> vector_to_move(GenerateVector(size));
  ASSERT_EQ(vector_to_move.size(), size);

  bmstu::vector<int> moved_vector(std::move(vector_to_move));
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);
}

TEST(VectorTest, 1moveoperator) {
  const size_t size = 1000000;
  bmstu::vector<int> vector_to_move(GenerateVector(size));
  ASSERT_EQ(vector_to_move.size(), size);

  bmstu::vector<int> moved_vector = std::move(vector_to_move);
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);
}

TEST(VectorTest, 1noncopybable2) {
  const size_t size = 5;
  bmstu::vector<X> vector_to_move;
  for (size_t i = 0; i < size; ++i) {
    vector_to_move.push_back(X(i));
  }
  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(vector_to_move[i].GetX(), i);
  }

  bmstu::vector<X> moved_vector = std::move(vector_to_move);
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);

  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(moved_vector[i].GetX(), i);
  }
}

TEST(VectorTest, 1noncopypable3) {
  const size_t size = 5;
  bmstu::vector<X> v;
  for (size_t i = 0; i < size; ++i) {
    v.push_back(X(i));
  }

  ASSERT_EQ(v.size(), size);

  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(v[i].GetX(), i);
  }
}

TEST(VectorTest, 1noncopiableinsert) {
  const size_t size = 5;
  bmstu::vector<X> v;
  for (size_t i = 0; i < size; ++i) {
    v.push_back(X(i));
  }

  // в начало
  v.insert(v.begin(), X(size + 1));
  ASSERT_EQ(v.size(), size + 1);
  ASSERT_EQ(v.begin()->GetX(), size + 1);
  // в конец
  v.insert(v.end(), X(size + 2));
  ASSERT_EQ(v.size(), size + 2);
  ASSERT_EQ((v.end() - 1)->GetX(), size + 2);
  // в середину
  v.insert(v.begin() + 3, X(size + 3));
  ASSERT_EQ(v.size(), size + 3);
  ASSERT_EQ((v.begin() + 3)->GetX(), size + 3);
}

TEST(VectorTest, 1erasenoncopy) {
  const size_t size = 3;

  bmstu::vector<X> v;
  for (size_t i = 0; i < size; ++i) {
    v.push_back(X(i));
  }

  auto it = v.erase(v.begin());
  assert(it->GetX() == 1);
}

TEST(VectorTest, 1test_new_push) {
  bmstu::vector<int> v;
  ASSERT_EQ(v.capacity(), 0);
  ASSERT_EQ(v.size(), 0);
  v.push_back(1);
  ASSERT_EQ(v.capacity(), 1);
  ASSERT_EQ(v.size(), 1);
  v.push_back(2);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
}

TEST(VectorTest, 1Disability) {
  uint8_t *ptr = new uint8_t[sizeof(WithoutDefaultConstructor) * 10];
  WithoutDefaultConstructor *wdc = new(ptr) WithoutDefaultConstructor(1);
  std::cout << ptr << " " << wdc;
  int b = 5;
}
