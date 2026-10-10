#include <gtest/gtest.h>
#include <type_traits>
#include <iostream>

#include "mock/checker.hpp"

// Cписок типов
using MyTestTypes = ::testing::Types<int, double, std::string>;

// Создаем шаблонную фикстуру
template <typename T>
class VectorTest : public ::testing::Test {
public:
    virtual ~VectorTest() = default;
    
    template <typename U>
    T ConvertNumTo(const U num) {
      if constexpr (std::is_same_v<T, std::string>)
        return std::to_string(num);
      else
        return static_cast<T>(num);
    }
protected:
    MockVector<T> vec;

    void SetUp() override {}
    void TearDown() override {}
};

TYPED_TEST_SUITE(VectorTest, MyTestTypes);

TYPED_TEST(VectorTest, Create) {
  EXPECT_EQ(this->vec.GetCtorCnt(), 1);  
}

TYPED_TEST(VectorTest, PushBack) {
  static constexpr size_t kVectorMax = 100000;
  for (size_t i = 0; i < kVectorMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);

    this->vec.push_back(value);
    EXPECT_EQ(this->vec[this->vec.size() - 1], value);
    EXPECT_EQ(this->vec.size(), i + 1);
  }
}

TYPED_TEST(VectorTest, PushFront) {
  static constexpr size_t kVectorMax = 1000;
  for (size_t i = 0; i < kVectorMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);

    this->vec.insert(0, value);
    EXPECT_EQ(this->vec.size(), i + 1);
    EXPECT_EQ(this->vec[0], value);
  }
}

TYPED_TEST(VectorTest, PushMiddle) {
  static constexpr size_t kVectorMax = 1000;
  for (size_t i = 0; i < kVectorMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);

    this->vec.insert(i/2, value);
    EXPECT_EQ(this->vec.size(), i + 1);
    EXPECT_EQ(this->vec[i/2], value);
  }
}

TYPED_TEST(VectorTest, EraseBack) {
  static constexpr size_t kVectorMax = 1000;

  for (size_t i = 0; i < kVectorMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);
    
    this->vec.push_back(value);
    EXPECT_EQ(this->vec.size(), i + 1);
    EXPECT_EQ(this->vec[this->vec.size() - 1], value);
  }

  for (size_t i = kVectorMax; i > 0; --i) {
    this->vec.erase(i);
    EXPECT_EQ(this->vec.size(), i - 1);
  }

  EXPECT_EQ(this->vec.size(), 0);
}

TEST(Vector, CheckMove) {
  MockVector<int> vector;
  MockVector<int> vector2;
  vector = std::move(vector2);

  EXPECT_EQ(vector.GetMoveCnt(), 1);
  vector2 = std::move(vector);
  EXPECT_EQ(vector2.GetMoveCnt(), 2);
}