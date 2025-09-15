#pragma once
#include <algorithm>
#include <cstddef>
#include <cassert>
#include <memory>
#include <utility> // std::move, std::swap

template<typename T>
class MyVector
{
public:
    // Ĭ�Ϲ��캯��
    MyVector();
    // ��������
    ~MyVector();
    // �������캯��
    MyVector(const MyVector& other);
    // ��ֵ���������
    MyVector& operator=(const MyVector& other);

    void reserve(size_t n);
    void push_back(const T& val);
    void push_back(T&& val); // ֧����ֵ����

    // []���������
    T& operator[](size_t i);
    const T& operator[](size_t i) const;

    size_t size() const;
    size_t capacity() const;

private:
    T* data = nullptr;
    size_t sz = 0;
    size_t cap = 0;
};

template<typename T>
MyVector<T>::MyVector()
{
    reserve(4);
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other)
{
    reserve(other.cap);
    sz = other.sz;
    for (size_t i = 0; i < sz; ++i) {
        ::new (data + i) T(other.data[i]); // �ֶ�����
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
    if (this != &other) {
        MyVector<T> temp(other); // ���ƹ��죨�쳣��ȫ��
        std::swap(data, temp.data);
        std::swap(sz, temp.sz);
        std::swap(cap, temp.cap);
    }
    return *this;
}

template<typename T>
MyVector<T>::~MyVector()
{
    // �ֶ��������ж���
    for (size_t i = 0; i < sz; ++i) {
        data[i].~T();
    }
    // �ͷ��ڴ�
    ::operator delete(data);
}

template<typename T>
void MyVector<T>::reserve(size_t n)
{
    if (n <= cap) return;

    T* new_block = static_cast<T*>(::operator new(n * sizeof(T)));
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

    // �ɹ����죬�����ɶ����ͷ��ڴ�
    for (size_t j = 0; j < sz; ++j) {
        data[j].~T(); // �����ɶ���
    }
    ::operator delete(data); // �ͷž��ڴ�

    data = new_block;
    cap = n;
}

template<typename T>
void MyVector<T>::push_back(const T& val)
{
    if (sz == cap) {
        reserve(cap ? cap * 2 : 4);
    }
    ::new (data + sz) T(val); // �ֶ�����
    ++sz;
}

template<typename T>
void MyVector<T>::push_back(T&& val)
{
    if (sz == cap) {
        reserve(cap ? cap * 2 : 4);
    }
    ::new (data + sz) T(std::move(val)); // �ƶ�����
    ++sz;
}

template<typename T>
size_t MyVector<T>::size() const { return sz; }

template<typename T>
size_t MyVector<T>::capacity() const { return cap; }

template<typename T>
T& MyVector<T>::operator[](size_t i) { return data[i]; }

template<typename T>
const T& MyVector<T>::operator[](size_t i) const { return data[i]; }