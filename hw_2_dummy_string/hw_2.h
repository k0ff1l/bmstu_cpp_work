// Copyright 2023 <fleurs>

#pragma once

#include <iostream>

namespace bmstu {
template<typename T>
class dummy_basic_string;  // объявление класс шаблонной строки


typedef dummy_basic_string<char> dummy_string;
typedef dummy_basic_string<wchar_t> wstring;
typedef dummy_basic_string<char8_t> u8string;
typedef dummy_basic_string<char16_t> u16string;
typedef dummy_basic_string<char32_t> u32string;

template<typename T>
class dummy_basic_string {
 public:
/// Шаблонная реализация
  dummy_basic_string() {
    size_ = 0;
    data_ = new T[1];
    data_[0] = 0;
  }

  explicit dummy_basic_string(size_t size) {
    size_ = size;
    data_ = new T[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = ' ';
    }
    data_[size_] = 0;
  }

  dummy_basic_string(std::initializer_list<T> list) {
    size_ = list.size();
    data_ = new T[size_ + 1];
    size_t i = 0;
    for (auto &item : list) {
      data_[i] = item;
      ++i;
    }
    data_[size_] = 0;
  }

/// Конструктор с параметром "cи строкой"
  explicit dummy_basic_string(const T *c_str) {
    size_ = len_(c_str);
    data_ = new T[size_ + 1];
    copy_data_(c_str);
  }

/// Копирующий конструктор
  dummy_basic_string(const dummy_basic_string &other) {
    size_ = other.size_;
    data_ = new T[size_ + 1];
    copy_data_(other.c_str());
  }

/// Конструктор перемещения
  dummy_basic_string(dummy_basic_string &&dying)

  noexcept {
    data_ = dying.data_;
    size_ = dying.size_;
    dying.data_ = nullptr;
    dying.size_ = 0;
  }

/// Деструктор
  ~dummy_basic_string() {
    clean_();
  }

/// Геттер на си-строку
  [[nodiscard]] const T *c_str() const {
    return (data_ != nullptr) ? data_ : reinterpret_cast<const T *>("");
  }

/// Геттер на размер
  [[nodiscard]] size_t size() const {
    return size_;
  }

/// Оператор копирующего присваивания
  dummy_basic_string &operator=(const dummy_basic_string &other) {
    if (*this == other) {
      return *this;
    } else {
      clean_();
      size_ = other.size_;
      data_ = new T[size_ + 1];
      copy_data_(other.c_str());
      data_[size_] = 0;
      return *this;
    }
  }

/// Оператор перемещающего присваивания
  dummy_basic_string &operator=(dummy_basic_string &&other)

  noexcept {
    if (this == &other) {
      return *this;
    } else {
      delete[] data_;
      size_ = other.size_;
      data_ = other.data_;
      other.data_ = nullptr;
      other.size_ = 0;
      return *this;
    }
  }

/// Оператор присваивания си строки
  dummy_basic_string &operator=(const T *c_str) {
    clean_();
    size_ = len_(c_str);
    data_ = new T[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = c_str[i];
    }
    data_[size_] = 0;
    return *this;
  }

/// Оператор конкатенации строк в новую строку
  friend bmstu::dummy_basic_string<T> operator+(const dummy_basic_string &left,
                                                const dummy_basic_string &right) {
    dummy_basic_string result;
    result.size_ = left.size_ + right.size_;
    result.data_ = new T[result.size_ + 1];
    result.copy_data_(left.c_str());
    for (size_t i = 0; i < right.size_; ++i) {
      result.data_[i + left.size_] = right.data_[i];
    }
    return result;
  }

/// Оператор вывода, тоже д. б. шаблонный, т.е. basic_ostream
  friend std::basic_ostream<T> &operator<<(std::basic_ostream<T> &os,
                                           const dummy_basic_string &obj) {
    os << obj.c_str();
    return os;
  }

/// Оператор ввода
  friend std::basic_istream<T> &operator>>(std::basic_istream<T> &is,
                                           dummy_basic_string &obj) {
    is >> std::noskipws;  // флаг игнорирования пробелов
    T symbol = 1;
    for (size_t i = 0; symbol != 0; ++i) {
      symbol = 0;
      is >> symbol;
      if (symbol != 0) {
        obj += symbol;
      }
    }
    return is;
  }

/// Оператор конкатенации строки и строки
  dummy_basic_string &operator+=(const dummy_basic_string &other) {
    *this = (*this + other);
    return *this;
  }

/// Оператор конкатенации строки и символа
  dummy_basic_string &operator+=(const T symbol) {
    T *prev_data = data_;
    ++size_;
    data_ = new T[size_ + 1];
    copy_data_(prev_data);
    delete[] prev_data;
    data_[size_ - 1] = symbol;
    data_[size_] = 0;
    return *this;
  }

  // Оператор равенства двух строк
  bool operator==(const dummy_basic_string &input) const {
    if (input.size_ != size_) return false;
    if (input.data_ == data_) return true;
    for (size_t i = 0; i < input.size_; ++i) {
      if (data_[i] != input[i]) { return false; }
    }
    return true;
  }

/// Значение по индексу
  T &operator[](const size_t index) const {
    if (index <= size_) {
      return data_[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }
/// А тут уже приваточка, не всем можно так сказать...
 private:
  size_t size_ = 0;
  T *data_ = nullptr;
/// Получаем длину
  static size_t len_(const T *str) {
    size_t len = 0;
    while (str[len] != 0) { ++len; }
    return len;
  }

/// Перегруженно получаем длину!
  static size_t len_(const dummy_basic_string &input) {
    return input.size_;
  }

/// Подчищаем нашу строчку, ну прям чтоб наверняка...
  void clean_() {
    size_ = 0;
    delete[] data_;
  }

///// Транслируем данные из одной A, в другую...
//        void copy_data_(const dummy_basic_string &other) {
//            for (size_t i = 0; i < len_(other); ++i) { data_[i] = other[i]; }
//            data_[size_] = 0;
//        }
  void copy_data_(const T *str) {
    for (size_t i = 0; i < len_(str); ++i) {
      data_[i] = str[i];
    }
    data_[size_] = 0;
  }
};
}  // namespace bmstu
