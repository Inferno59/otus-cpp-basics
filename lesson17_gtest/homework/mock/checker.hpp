#pragma once

#include <cstddef> // для std::size_t
#include <utility> // для std::move

#include "vector/vector.hpp"

template <typename T>
class MockVector : public my_containers::Vector<T> {
public:
  MockVector()
    : my_containers::Vector<T>{}
    , ctor_cnt_{0}
    , move_cnt_{0} {
      ++ctor_cnt_;
    }

  virtual ~MockVector() = default;

  MockVector<T>& operator=(MockVector<T>&& src) {
    if (this != &src) {
      my_containers::Vector<T>::operator=(std::move(src));
      move_cnt_ = src.move_cnt_ + 1;
    }

    return *this;
  }

  std::size_t GetMoveCnt() const {
    return move_cnt_; 
  }

  std::size_t GetCtorCnt() const {
    return ctor_cnt_; 
  }
private:
  std::size_t ctor_cnt_;
  std::size_t move_cnt_;
};