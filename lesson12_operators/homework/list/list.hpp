#pragma once

#include <cstddef> // для std::size_t
#include <cstdint> // std::types
#include <initializer_list>
#include <iostream>

namespace my_containers {
  template <typename T>
  struct Node {
    Node* next;
    Node* prev;
    T data;

    Node(const T value) 
      : next{nullptr}
      , prev{nullptr}
      , data{value} {}

    ~Node() {}
  };
  
  template <typename T>
  class list_iterator {
  public:
      // === Обязательные typedef для совместимости с STL ===
      using iterator_category = std::bidirectional_iterator_tag; // Категория итератора
      using value_type        = T;
      using difference_type   = std::ptrdiff_t;
      using pointer           = T*;
      using reference         = T&;

      // Конструктор
      list_iterator() : node_{nullptr} {}
      explicit list_iterator(Node<T>* node) : node_(node) {}

      // Разыменование (доступ к значению)
      reference operator*() const { return node_->data; }
      
      // Доступ к членам объекта (если T - это класс/структура)
      pointer operator->() const { return &(node_->data); }

      // Операторы декремента (перемещение назад)
      list_iterator& operator--() {  // Префиксный --it
          node_ = node_->prev;
          return *this;
      }

      list_iterator operator--(int) {  // Постфиксный it--
          list_iterator temp = *this;
          node_ = node_->prev;
          return temp;
      }

      // Префиксный инкремент (++it) - возвращает ссылку на себя
      list_iterator& operator++() {
        node_ = node_->next;
        return *this;
      }

      // Постфиксный инкремент (it++) - возвращает копию старого состояния
      list_iterator operator++(int) {
          list_iterator tmp = *this;
          ++(*this); // Вызываем префиксный инкремент
          return tmp;
      }

      Node<T>* get() { return node_; }

      // Операторы сравнения
      friend bool operator==(const list_iterator& a, const list_iterator& b) {
          return a.node_ == b.node_;
      }
      friend bool operator!=(const list_iterator& a, const list_iterator& b) {
          return a.node_ != b.node_;
      }

    private:
        Node<T>* node_; // Внутренний указатель на текущий элемент
  };

  template <typename T>
  class List {
    public:
      List();
      explicit List(const T& value);
      explicit List(const T& value, size_t size);
      explicit List(std::initializer_list<T> values);

      ~List() { clear(); }

      List(const List<T>& src);
      List(List<T>&& src);

      List<T>& operator=(const List<T>& src);
      List<T>& operator=(List<T>&& src);
    
      void clear();

      void push_back(const T& value);
      void push_front(const T& value);

      using iterator = list_iterator<T>;
      iterator begin();
      iterator end();

      iterator insert(iterator pos, const T& value);
      iterator erase(iterator pos);

      std::size_t size() const { return size_; }
      bool empty() const { return size_ == 0; }

      // Тут надо реализовать перебор по указателю, пока не достигнешь нужного, по счету, у настоящего листа нет такого
      T* operator[](const size_t idx) { return T{}; }
    private:
      Node<T>* head_;
      Node<T>* tail_;
      size_t size_;
  };
}
