//
// Created by fleurs on 14.10.23.
//

#ifndef HW_2_STRING_HW_2_H_
#define HW_2_STRING_HW_2_H_

#include <iostream>
#include <cstddef>
#include <string>  // for cpplint, as it wants.

namespace bmstu {
class string {
 public:
/// Шаблонная реализация
  template<typename A>
  void construct(const A &input) {
    size_ = len_(input);
    data_ = new char[size_ + 1];
    copy_data_(input);
  }
/// Перегрузим функцию ??? для конструктора по умолчанию
  void construct() {
    size_ = 0;
    data_ = new char[size_ + 1];
    copy_data_("");
  }
/// Конструктор по умолчанию
  string() {
    construct();
  }
/// Конструктор с параметром "cи строкой"
  explicit string(const char *c_str) {
    construct(c_str);
  }
/// Копирующий конструктор
  string(const string &other) {
    construct(other);
  }
/// Конструктор перемещения
  string(string &&dying) noexcept {
    data_ = dying.data_;
    size_ = dying.size_;
    dying.data_ = nullptr;
    dying.size_ = 0;
  }
/// Деструктор
  ~string() {
    clean_();
  }
/// Геттер на си-строку
  [[nodiscard]] const char *c_str() const {
    return data_;
  }
/// Геттер на размер
  [[nodiscard]] size_t size() const {
    return size_;
  }
/// Оператор копирующего присваивания
  string &operator=(const string &other) {
    if (*this == other) {
      return *this;
    } else {
      clean_();
      size_ = other.size_;
      data_ = new char[size_ + 1];
      copy_data_(other);
      data_[size_] = '\0';
      return *this;
    }
  }
/// Оператор перемещающего присваивания
  string &operator=(string &&other) noexcept {
    if (this == &other) {
      return *this;
    } else {
      size_ = other.size_;
      data_ = other.data_;
      other.data_ = nullptr;
      other.size_ = 0;
      return *this;
    }
  }
/// Оператор присваивания си строки
  string &operator=(const char *c_str) {
    construct(c_str);
    return *this;
  }
/// Оператор конкатенации строк в новую строку
  friend bmstu::string operator+(const string &left, const string &right) {
    string result;
    result.size_ = left.size_ + right.size_;
    result.data_ = new char[result.size_ + 1];
    result.copy_data_(left);
    for (size_t i = 0; i < right.size_; ++i) {
      result.data_[i + left.size_] = right.data_[i];
    }
    return result;
  }
/// Оператор вывода
  friend std::ostream &operator<<(std::ostream &os, const string &obj) {
    os << obj.c_str();
    return os;
  }
/// Оператор ввода
  friend std::istream &operator>>(std::istream &is, string &obj) {
    is >> std::noskipws;  // флаг игнорирования пробелов
    obj = "";
    char symbol = 1;
    for (size_t i = 0; symbol != '\0'; ++i) {
      symbol = 0;
      is >> symbol;
      if (symbol != '\0') {
        obj += symbol;
      }
    }
    return is;
  }
/// Оператор конкатенации строки и строки
  string &operator+=(const string &other) {
    *this = (*this + other);
    return *this;
  }
/// Оператор конкатенации строки и символа
  string &operator+=(const char symbol) {
    char *prev_data = data_;
    ++size_;
    data_ = new char[size_ + 1];
    copy_data_(prev_data);
    delete[] prev_data;
    data_[size_ - 1] = symbol;
    data_[size_] = '\0';
    return *this;
  }
  // Оператор равенства двух строк
  bool operator==(const string &input) const {
    if (input.size_ != size_) return false;
    if (input.data_ == data_) return true;
    for (size_t i = 0; i < input.size_; ++i) { if (data_[i] != input[i]) { return false; }}
    return true;
  }
/// Значение по индексу
  char &operator[](const size_t index) const {
    if (index <= size_) {
      return data_[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }
/// А тут уже приваточка, не всем можно так сказать...
 private:
  size_t size_ = 0;
  char *data_ = nullptr;
/// Получаем длину
  static size_t len_(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') { ++len; }
    return len;
  }
/// Перегруженно получаем длину!
  static size_t len_(const string &input) {
    return input.size_;
  }
/// Подчищаем нашу строчку, ну прям чтоб наверняка...
  void clean_() {
    size_ = 0;
    delete[] data_;
  }
/// Транслируем данные из одной A, в другую...
  template<typename A>
  void copy_data_(const A &other) const {
    for (size_t i = 0; i < len_(other); ++i) { data_[i] = other[i]; }
    data_[size_] = '\0';
  }
};
}  // namespace bmstu
#endif  // HW_2_STRING_HW_2_H_
