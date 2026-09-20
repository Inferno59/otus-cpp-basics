#pragma once
#include <cstddef> // для std::size_t
#include <cstdint> // std::types
#include <initializer_list>
#include <iostream>

namespace  my_containers{

  template <typename T>
  class vector_iterator {
  public:
      // === Обязательные typedef для совместимости с STL ===
      using iterator_category = std::forward_iterator_tag; // Категория итератора
      using value_type        = T;
      using difference_type   = std::ptrdiff_t;
      using pointer           = T*;
      using reference         = T&;

      // Конструктор
      explicit vector_iterator(T* p) : ptr(p) {}

      // Разыменование (доступ к значению)
      reference operator*() const { return *ptr; }
      
      // Доступ к членам объекта (если T - это класс/структура)
      pointer operator->() const { return ptr; }

      // Префиксный инкремент (++it) - возвращает ссылку на себя
      vector_iterator& operator++() {
          ++ptr;
          return *this;
      }

      T* get() { return ptr; }

      // Постфиксный инкремент (it++) - возвращает копию старого состояния
      vector_iterator operator++(int) {
          vector_iterator tmp = *this;
          ++(*this); // Вызываем префиксный инкремент
          return tmp;
      }

      size_t operator-(const vector_iterator& b) const {
        return ptr - b.ptr;
      }

      // Операторы сравнения
      friend bool operator==(const vector_iterator& a, const vector_iterator& b) {
          return a.ptr == b.ptr;
      }
      friend bool operator!=(const vector_iterator& a, const vector_iterator& b) {
          return a.ptr != b.ptr;
      }

      bool operator>(const vector_iterator& b) {
          return ptr > b.ptr;
      }
      bool operator<(const vector_iterator& b) {
          return ptr < b.ptr;
      }      
    private:
        T* ptr; // Внутренний указатель на текущий элемент
  };

  template <typename T>
  class Vector {
    public:
      Vector();
      explicit Vector(const T& value);
      explicit Vector(const T& value, size_t size);
      explicit Vector(std::initializer_list<T> values);

      ~Vector();
      Vector(const Vector<T>& src);
      Vector(Vector<T>&& src);

      Vector<T>& operator=(const Vector<T>& src);
      Vector<T>& operator=(Vector<T>&& src);

      void push_back(const T& value);
      void pop_back();

      using iterator = vector_iterator<T>;
      iterator insert(iterator& pos, const T& value);
      void insert(size_t pos, const T& value);
      iterator erase(iterator& pos);
      void erase(size_t pos);

      void reserved(size_t size);
      void resize(size_t size);
      void clear();

      std::size_t max_size() const;
      std::size_t size() const;

      iterator begin() { return iterator{data_}; }
      iterator end() {return iterator{data_ + size_}; };

      T& operator[](const T pos) {
        return data_[pos];
      }

      const T& operator[](const T pos) const {
        return data_[pos];
      }      
    private:
      static constexpr uint16_t kDefaultSize = 10;
      static constexpr uint16_t kDefaultFactor = 2;

      void shift_to_right_from_idx(int idx);
      void shift_to_left_from_idx(int idx);

      void clear_internal_memory();
      T* allocate(size_t size);
      size_t get_max_size(size_t size) {
        return size > kDefaultSize ? size * kDefaultFactor : kDefaultSize;
      }

      size_t size_;
      size_t max_size_;
      T* data_;
  };

  template <typename T>
  std::ostream& operator<<(std::ostream& os, const Vector<T>& src) {
    const size_t kVecSize = src.size();
    for (size_t i = 0; i < kVecSize; ++i) {
      os << src[i];
      if ((i + 1) < kVecSize)
        os << ", ";
    }

    return os;
  }
}

#include "vector.impl"

