#pragma once

#include <cstddef>     // size_t
#include <stdexcept>   // std::out_of_range
#include <utility>     // std::move
#include <new>         // ::operator new, ::operator delete

template<typename T>
class MyStack {
public:
    // ���졢��������������
    MyStack();
    ~MyStack();
    MyStack(const MyStack& other);
    MyStack& operator=(const MyStack& other);
    MyStack(MyStack&& other) noexcept;
    MyStack& operator=(MyStack&& other) noexcept;

    // ջ����
    void push(const T& value);
    void push(T&& value);                // ��ֵ���ð汾
    void pop();
    T& top();
    const T& top() const;

    bool empty() const;
    size_t size() const;
    size_t capacity() const; // ��ѡ���鿴��ǰ����

private:
    T* data;           // ָ��̬���������
    size_t sz;         // ��ǰԪ�ظ���
    size_t cap;        // ��ǰ����

    void reserve(size_t new_cap); // ���ݺ���
};

// ------------------------ ��Ա����ʵ�� ------------------------

template<typename T>
MyStack<T>::MyStack() : data(nullptr), sz(0), cap(0) {
    reserve(4); // ��ʼ����Ϊ 4
}

template<typename T>
MyStack<T>::~MyStack() {
    // �ֶ�����ÿ��Ԫ�ص���������
    for (size_t i = 0; i < sz; ++i) {
        data[i].~T();
    }
    ::operator delete(data); // �ͷ��ڴ棨�� ::operator new ��ԣ�
}

// ��������
template<typename T>
MyStack<T>::MyStack(const MyStack& other) : data(nullptr), sz(0), cap(0) {
    reserve(other.cap);
    for (size_t i = 0; i < other.sz; ++i) {
        ::new (data + i) T(other.data[i]); // ��λ new ����
    }
    sz = other.sz;
}

// ������ֵ��ʹ�ÿ���-�������÷���
template<typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack& other) {
    if (this != &other) {
        MyStack temp(other); // ����
        std::swap(data, temp.data);
        std::swap(sz, temp.sz);
        std::swap(cap, temp.cap);
    }
    return *this;
}

// �ƶ�����
template<typename T>
MyStack<T>::MyStack(MyStack&& other) noexcept
    : data(other.data), sz(other.sz), cap(other.cap) {
    other.data = nullptr;
    other.sz = 0;
    other.cap = 0;
}

// �ƶ���ֵ
template<typename T>
MyStack<T>& MyStack<T>::operator=(MyStack&& other) noexcept {
    if (this != &other) {
        // ����ǰ��Դ
        for (size_t i = 0; i < sz; ++i) {
            data[i].~T();
        }
        ::operator delete(data);

        // ת����Դ
        data = other.data;
        sz = other.sz;
        cap = other.cap;

        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }
    return *this;
}

// ����
template<typename T>
void MyStack<T>::reserve(size_t new_cap) {
    if (new_cap <= cap) return;

    T* new_block = static_cast<T*>(::operator new(new_cap * sizeof(T)));
    size_t i = 0;
    try {
        for (; i < sz; ++i) {
            ::new (new_block + i) T(std::move(data[i])); // �ƶ�����
        }
    }
    catch (...) {
        // ����ʧ�ܣ������ѹ���Ķ���
        for (size_t j = 0; j < i; ++j) {
            (new_block + j)->~T();
        }
        ::operator delete(new_block);
        throw;
    }

    // �����ɶ����ͷ��ڴ�
    for (size_t j = 0; j < sz; ++j) {
        data[j].~T();
    }
    ::operator delete(data);

    data = new_block;
    cap = new_cap;
}

// ��ջ
template<typename T>
void MyStack<T>::push(const T& value) {
    if (sz == cap) {
        reserve(cap ? cap * 2 : 4);
    }
    ::new (data + sz) T(value); // ��λ new ����
    ++sz;
}

template<typename T>
void MyStack<T>::push(T&& value) {
    if (sz == cap) {
        reserve(cap ? cap * 2 : 4);
    }
    ::new (data + sz) T(std::move(value)); // �ƶ�����
    ++sz;
}

// ��ջ
template<typename T>
void MyStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("MyStack::pop(): empty stack");
    }
    --sz;
    data[sz].~T(); // �ֶ�����
}

// ����ջ��
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

// ״̬��ѯ
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