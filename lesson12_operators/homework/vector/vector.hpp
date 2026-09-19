#pragma once
#include <cstddef> // для std::size_t
#include <cstdint> // std::types
#include <initializer_list>
#include <iostream>
#include <vector>

namespace  my_containers{

  template <typename T>
  class Vector {
    public:
      Vector();
      explicit Vector(const T& value);
      explicit Vector(const T& value, size_t size);
      explicit Vector(std::initializer_list<T> values);

      ~Vector();
      Vector(const Vector& src);
      Vector(Vector&& src);

      Vector& operator=(const Vector& src);
      Vector& operator=(Vector&& src);

      class Iterator {

      };

      void push_back(const T& value);
      void pop_back();

      Iterator insert(Iterator pos, const T& value);
      void insert(size_t pos, const T& value);
      Iterator erase(Iterator pos);
      void erase(size_t pos);

      void reserved(size_t size);
      void resize(size_t size);
      void clear();

      std::size_t max_size() const;
      std::size_t size() const;

      Iterator begin();
      Iterator end();

      T& operator[](const T pos) {
        return data[pos];
      }

      const T& operator[](const T pos) const {
        return data[pos];
      }      
    private:
      static constexpr uint16_t kDefaultSize = 10;
      static constexpr uint16_t kDefaultFactor = 2;
      size_t get_max_size(size_t size) {
        return size > kDefaultSize ? size * kDefaultFactor : kDefaultSize;
      }

      size_t size_;
      size_t max_size_;
      T* data;
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

