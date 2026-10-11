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

TEST(Vector, MoveOperator) {
  MockVector<int> vector;
  MockVector<int> vector2;
  vector = std::move(vector2);

  EXPECT_EQ(vector.GetMoveCnt(), 1);
  vector2 = std::move(vector);
  EXPECT_EQ(vector2.GetMoveCnt(), 2);
}

// Copy
TYPED_TEST(VectorTest, CopyCtor) {
  static constexpr size_t kVectorMax = 100000;
  my_containers::Vector<TypeParam> vector1;
  for (size_t i = 0; i < kVectorMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);
  
    vector1.push_back(value);
    EXPECT_EQ(vector1[vector1.size() - 1], value);
    EXPECT_EQ(vector1.size(), i + 1);
  }

  my_containers::Vector<TypeParam> vector2{vector1};

  ASSERT_EQ(vector2.size(), vector1.size());

  for(size_t i = 0; i < vector2.size(); ++i) {
    EXPECT_EQ(vector1[i], vector2[i]);
  }
}

// Obj dtor
class TestObj final {
public:
  static size_t GetCtorCnt() {
    return сtor_cnt_;
  }

  static size_t GetDtorCnt() {
    return dtor_cnt_;
  }

  TestObj() {
    ++сtor_cnt_;
  }

  ~TestObj() {
    ++dtor_cnt_;
  }

  TestObj(const TestObj& src) {
    ++сtor_cnt_;
  }

  static void ClearCnts() {
    сtor_cnt_ = 0;
    dtor_cnt_ = 0;
  }

private:
  inline static size_t сtor_cnt_ = 0;
  inline static size_t dtor_cnt_ = 0;
};

TEST(Vector, ObjDtor) {  
  TestObj::ClearCnts();
  static constexpr size_t kVectorMax = 100000;
  size_t dtor_before_delete = 0;

  // Создаем область локальную видимости
  {
    my_containers::Vector<TestObj> vector;
    for (size_t i = 0; i < kVectorMax; ++i) {
      vector.push_back({}); // Добавялем пустые объекты
    }
    dtor_before_delete = TestObj::GetDtorCnt();
  }

  // После заполнения проверяем, что все kVectorMax объектов были освобождены
  EXPECT_EQ(TestObj::GetDtorCnt() - dtor_before_delete, kVectorMax);
}

TEST(Vector, ObjDtorWithReserved) {
  TestObj::ClearCnts();
  static constexpr size_t kVectorMax = 100000;
  static constexpr size_t kCtorDtorMax = 100001; // kVectorMax + 1 временный объект

  // Создаем область локальную видимости
  {
    my_containers::Vector<TestObj> vector({}, kVectorMax);
    EXPECT_EQ(vector.max_size(), kVectorMax * 2);
    EXPECT_EQ(TestObj::GetCtorCnt(), kCtorDtorMax);
  }

  EXPECT_EQ(TestObj::GetDtorCnt(), kCtorDtorMax);
}

// Exceptions
TEST(Vector, OutOfRange) {
  TestObj::ClearCnts();
  static constexpr size_t kVectorMax = 100000;

  my_containers::Vector<TestObj> vector({}, kVectorMax);
  EXPECT_EQ(vector.max_size(), kVectorMax * 2);

  EXPECT_THROW((vector[kVectorMax]), std::out_of_range);
  EXPECT_THROW((vector[kVectorMax + 1]), std::out_of_range);

  EXPECT_THROW((vector.insert(kVectorMax + 1, {})), std::out_of_range);

  EXPECT_NO_THROW(vector.insert(kVectorMax, {}));
  EXPECT_EQ(vector.size(), kVectorMax + 1);

  EXPECT_THROW((vector.erase(kVectorMax + 2)), std::out_of_range);

  EXPECT_NO_THROW(vector.erase(kVectorMax + 1));
  EXPECT_EQ(vector.size(), kVectorMax);  
}