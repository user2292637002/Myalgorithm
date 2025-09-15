#pragma once

#include <cstddef>     // size_t
#include <stdexcept>   // std::out_of_range
#include <utility>     // std::move
#include <new>         // ::operator new, ::operator delete

template<typename T>
class MyStack {
public:
    // 构造、析构、拷贝控制
    MyStack();
    ~MyStack();
    MyStack(const MyStack& other);
    MyStack& operator=(const MyStack& other);
    MyStack(MyStack&& other) noexcept;
    MyStack& operator=(MyStack&& other) noexcept;

    // 栈操作
    void push(const T& value);
    void push(T&& value);                // 右值引用版本
    void pop();
    T& top();
    const T& top() const;

    bool empty() const;
    size_t size() const;
    size_t capacity() const; // 可选：查看当前容量

private:
    T* data;           // 指向动态分配的数组
    size_t sz;         // 当前元素个数
    size_t cap;        // 当前容量

    void reserve(size_t new_cap); // 扩容函数
};

// ------------------------ 成员函数实现 ------------------------

template<typename T>
MyStack<T>::MyStack() : data(nullptr), sz(0), cap(0) {
    reserve(4); // 初始容量为 4
}

template<typename T>
MyStack<T>::~MyStack() {
    // 手动调用每个元素的析构函数
    for (size_t i = 0; i < sz; ++i) {
        data[i].~T();
    }
    ::operator delete(data); // 释放内存（与 ::operator new 配对）
}

// 拷贝构造
template<typename T>
MyStack<T>::MyStack(const MyStack& other) : data(nullptr), sz(0), cap(0) {
    reserve(other.cap);
    for (size_t i = 0; i < other.sz; ++i) {
        ::new (data + i) T(other.data[i]); // 定位 new 构造
    }
    sz = other.sz;
}

// 拷贝赋值（使用拷贝-交换惯用法）
template<typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack& other) {
    if (this != &other) {
        MyStack temp(other); // 复制
        std::swap(data, temp.data);
        std::swap(sz, temp.sz);
        std::swap(cap, temp.cap);
    }
    return *this;
}

// 移动构造
template<typename T>
MyStack<T>::MyStack(MyStack&& other) noexcept
    : data(other.data), sz(other.sz), cap(other.cap) {
    other.data = nullptr;
    other.sz = 0;
    other.cap = 0;
}

// 移动赋值
template<typename T>
MyStack<T>& MyStack<T>::operator=(MyStack&& other) noexcept {
    if (this != &other) {
        // 清理当前资源
        for (size_t i = 0; i < sz; ++i) {
            data[i].~T();
        }
        ::operator delete(data);

        // 转移资源
        data = other.data;
        sz = other.sz;
        cap = other.cap;

        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }
    return *this;
}

// 扩容
template<typename T>
void MyStack<T>::reserve(size_t new_cap) {
    if (new_cap <= cap) return;

    T* new_block = static_cast<T*>(::operator new(new_cap * sizeof(T)));
    size_t i = 0;
    try {
        for (; i < sz; ++i) {
            ::new (new_block + i) T(std::move(data[i])); // 移动构造
        }
    }
    catch (...) {
        // 构造失败，清理已构造的对象
        for (size_t j = 0; j < i; ++j) {
            (new_block + j)->~T();
        }
        ::operator delete(new_block);
        throw;
    }

    // 析构旧对象并释放内存
    for (size_t j = 0; j < sz; ++j) {
        data[j].~T();
    }
    ::operator delete(data);

    data = new_block;
    cap = new_cap;
}

// 入栈
template<typename T>
void MyStack<T>::push(const T& value) {
    if (sz == cap) {
        reserve(cap ? cap * 2 : 4);
    }
    ::new (data + sz) T(value); // 定位 new 构造
    ++sz;
}

template<typename T>
void MyStack<T>::push(T&& value) {
    if (sz == cap) {
        reserve(cap ? cap * 2 : 4);
    }
    ::new (data + sz) T(std::move(value)); // 移动构造
    ++sz;
}

// 出栈
template<typename T>
void MyStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("MyStack::pop(): empty stack");
    }
    --sz;
    data[sz].~T(); // 手动析构
}

// 访问栈顶
template<typename T>
T& MyStack<T>::top() {
    if (empty()) {
        throw std::out_of_range("MyStack::top(): empty stack");
    }
    return data[sz - 1];
}

template<typename T>
const T& MyStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("MyStack::top(): empty stack");
    }
    return data[sz - 1];
}

// 状态查询
template<typename T>
bool MyStack<T>::empty() const {
    return sz == 0;
}

template<typename T>
size_t MyStack<T>::size() const {
    return sz;
}

template<typename T>
size_t MyStack<T>::capacity() const {
    return cap;
}