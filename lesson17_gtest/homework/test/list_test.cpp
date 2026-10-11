#include <gtest/gtest.h>
#include <type_traits>
#include <iostream>

#include "mock/checker.hpp"

// Cписок типов
using MyTestTypes = ::testing::Types<int, double, std::string>;

// Создаем шаблонную фикстуру
template <typename T>
class ListTest : public ::testing::Test {
public:
    virtual ~ListTest() = default;
    
    template <typename U>
    T ConvertNumTo(const U num) {
      if constexpr (std::is_same_v<T, std::string>)
        return std::to_string(num);
      else
        return static_cast<T>(num);
    }
protected:
    MockList<T> list;

    void SetUp() override {}
    void TearDown() override {}
};

TYPED_TEST_SUITE(ListTest, MyTestTypes);

TYPED_TEST(ListTest, Create) {
  EXPECT_EQ(this->list.GetCtorCnt(), 1);  
}

TYPED_TEST(ListTest, PushBack) {
  static constexpr size_t kListMax = 100000;
  for (size_t i = 0; i < kListMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);

    this->list.push_back(value);
    EXPECT_EQ(this->list.size(), i + 1);
  }

  size_t pos = 0;
  for (auto& el : this->list) {
    const TypeParam value = this->template ConvertNumTo<size_t>(pos++);
    EXPECT_EQ(el, value);
  }
}

TYPED_TEST(ListTest, PushFront) {
  static constexpr size_t kListMax = 1000;
  for (size_t i = 0; i < kListMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);

    this->list.insert(this->list.begin(), value);
    EXPECT_EQ(this->list.size(), i + 1);
  }

  size_t pos = kListMax - 1;
  for (auto& el : this->list) {
    const TypeParam value = this->template ConvertNumTo<size_t>(pos--);
    EXPECT_EQ(el, value);
  }  
}

TYPED_TEST(ListTest, PushMiddle) {
  static constexpr size_t kListMax = 1000;
  for (size_t i = 0; i < kListMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);

    auto it = this->list.begin();
    std::advance(it, i / 2);
    this->list.insert(it, value);
    EXPECT_EQ(this->list.size(), i + 1);
  }  
}

TYPED_TEST(ListTest, EraseBack) {
  static constexpr size_t kListMax = 1000;

  for (size_t i = 0; i < kListMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);
    
    this->list.push_back(value);
    EXPECT_EQ(this->list.size(), i + 1);
  }

  size_t pos = 0;
  for (auto& el : this->list) {
    const TypeParam value = this->template ConvertNumTo<size_t>(pos++);
    EXPECT_EQ(el, value);
  }
  
  for (size_t i = 0; i < kListMax; ++i) {
    this->list.erase(this->list.begin());
    EXPECT_EQ(this->list.size(), (kListMax - 1) - i);
  }

  EXPECT_EQ(this->list.size(), 0);
}

TEST(List, MoveOperator) {
  MockList<int> list;
  MockList<int> list2;
  list = std::move(list2);

  EXPECT_EQ(list.GetMoveCnt(), 1);
  list2 = std::move(list);
  EXPECT_EQ(list2.GetMoveCnt(), 2);
}

// Copy
TYPED_TEST(ListTest, CopyCtor) {
  static constexpr size_t kListMax = 100000;
  my_containers::List<TypeParam> list1;
  for (size_t i = 0; i < kListMax; ++i) {
    const TypeParam value = this->template ConvertNumTo<size_t>(i);
  
    list1.push_back(value);
    EXPECT_EQ(list1.size(), i + 1);
  }

  my_containers::List<TypeParam> list2{list1};

  ASSERT_EQ(list2.size(), list1.size());

  bool equal = true;
  auto it1 = list1.begin();
  auto it2 = list2.begin();
  while(it1 != list1.end()) {
    if (*it1 != *it2) {
      equal = false;
      break;
    }
    ++it1;
    ++it2;
  }

  EXPECT_EQ(equal, true);
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

TEST(List, ObjDtor) {  
  TestObj::ClearCnts();
  static constexpr size_t kListMax = 100000;
  size_t dtor_before_delete = 0;

  // Создаем область локальную видимости
  {
    my_containers::List<TestObj> list;
    for (size_t i = 0; i < kListMax; ++i) {
      list.push_back({}); // Добавялем пустые объекты
    }
    dtor_before_delete = TestObj::GetDtorCnt();
  }

  // После заполнения проверяем, что все kListMax объектов были освобождены
  EXPECT_EQ(TestObj::GetDtorCnt() - dtor_before_delete, kListMax);
}

TEST(List, ObjDtorWithReserved) {
  TestObj::ClearCnts();
  static constexpr size_t kListMax = 100000;
  static constexpr size_t kCtorDtorMax = 100001; // kListMax + 1 временный объект

  // Создаем область локальную видимости
  {
    my_containers::List<TestObj> my_list({}, kListMax);
    EXPECT_EQ(TestObj::GetCtorCnt(), kCtorDtorMax);
    EXPECT_EQ(my_list.size(), kListMax);
  }

  EXPECT_EQ(TestObj::GetDtorCnt(), kCtorDtorMax);
}

// Exceptions
TEST(List, OutOfRange) {
  TestObj::ClearCnts();
  static constexpr size_t kListMax = 100000;

  my_containers::List<TestObj> my_list({}, kListMax);
  EXPECT_EQ(my_list.size(), kListMax);

  EXPECT_NO_THROW(my_list[kListMax + 100]);
  EXPECT_EQ(my_list[kListMax + 100], nullptr);

  EXPECT_THROW((my_list.erase(my_list.end())), std::out_of_range);
  EXPECT_EQ(my_list.size(), kListMax);
}