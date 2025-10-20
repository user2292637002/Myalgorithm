#pragma once
#include<iostream>
#include<stdexcept>

/**
 * @brief 一个基于动态数组实现的栈类，支持泛型类型T。
 * 提供了标准的栈操作，如 push, pop, top, isEmpty 等。
 *
 * @tparam T 栈中存储的元素类型
 */
template<typename T>
class MyStack
{
private:
    T* data;          // 指向存储栈元素的动态数组的指针
    size_t capacity;  // 当前分配的数组容量
    size_t currentSize; // 当前栈中元素的数量

    /**
     * @brief 重新分配内部数组的大小。
     * 将当前栈中的元素按顺序移动到新的、更大的数组中。
     * 如果当前容量为0，则新容量为1；否则新容量为当前容量的2倍。
     */
    void resize();

public:
    // --- 构造、析构、拷贝、移动 ---

    /**
     * @brief 默认构造函数。
     * 初始化栈，分配容量为1的初始数组。
     */
    MyStack();

    /**
     * @brief 析构函数。
     * 释放内部动态分配的数组内存。
     */
    ~MyStack();

    /**
     * @brief 拷贝构造函数。
     * 创建一个新栈，其内容与 other 栈相同。
     *
     * @param other 要拷贝的源栈
     */
    MyStack(const MyStack& other);

    /**
     * @brief 移动构造函数。
     * 将 other 栈的资源（data指针、容量、大小等）转移给新对象。
     * 标记为 noexcept，表示此操作不会抛出异常。
     *
     * @param other 要移动的源栈（将被置为有效但未指定的状态）
     */
    MyStack(MyStack&& other)noexcept;

    /**
     * @brief 拷贝赋值操作符。
     * 将当前栈的内容替换为 other 栈的内容。
     *
     * @param other 源栈
     * @return MyStack& 引用自身
     */
    MyStack& operator=(const MyStack& other);

    /**
     * @brief 移动赋值操作符。
     * 将 other 栈的资源转移给当前栈。
     * 标记为 noexcept。
     *
     * @param other 要移动的源栈（将被置为有效但未指定的状态）
     * @return MyStack& 引用自身
     */
    MyStack& operator=(MyStack&& other)noexcept;

    // --- 栈基本操作 ---

    /**
     * @brief 将元素添加到栈顶（入栈）。
     * 如果栈容量不足，则先进行扩容。
     *
     * @param item 要添加的常量引用元素
     */
    void push(const T& item);

    /**
     * @brief 将元素（通过右值引用）添加到栈顶（入栈）。
     * 如果栈容量不足，则先进行扩容。
     * 利用移动语义，避免不必要的拷贝。
     *
     * @param item 要添加的右值引用元素
     */
    void push(T&& item);

    /**
     * @brief 移除并返回栈顶的元素（出栈）。
     * 如果栈为空，抛出 runtime_error 异常。
     *
     * @return T 从栈顶移除的元素（通过移动返回）
     */
    T pop();

    /**
     * @brief 返回栈顶元素的常量引用，但不移除它。
     * 如果栈为空，抛出 runtime_error 异常。
     *
     * @return const T& 栈顶元素的常量引用
     */
    const T& top() const;

    /**
     * @brief 检查栈是否为空。
     *
     * @return true 如果栈中没有元素
     * @return false 如果栈中有元素
     */
    bool isEmpty() const;

    /**
     * @brief 返回栈中当前元素的数量。
     *
     * @return size_t 当前元素数量
     */
    size_t size() const;

    /**
     * @brief 清空栈，移除所有元素。
     * 仅重置元素计数器，不释放内部数组内存。
     * 栈将变为空，但保留当前容量。
     */
    void clear();
};

// --- 成员函数定义 ---

/**
 * @brief 定义移动赋值操作符的实现。
 * 此实现放在 public 声明之后，private 定义之前，虽然在技术上可行，
 * 但通常建议将所有成员函数的定义放在类声明之后。
 *
 * @tparam T 栈元素类型
 * @param other 要移动的源栈
 * @return MyStack<T>& 引用自身
 */
template<typename T>
MyStack<T>& MyStack<T>::operator=(MyStack<T>&& other)noexcept
{
    if (this != &other) // 自赋值检查：防止将对象赋值给自己
    {
        delete[] data; // 释放当前对象的旧内存

        // 转移 other 的资源
        data = other.data;
        capacity = other.capacity;
        currentSize = other.currentSize;

        // 将 other 置为有效但未指定的状态（清空其指针和计数器）
        other.data = nullptr;
        other.capacity = 0;
        other.currentSize = 0;
    }
    return *this; // 返回自身引用，支持链式赋值
}

template<typename T>
void MyStack<T>::resize()
{
    // 计算新容量：如果当前容量为0，则新容量为1；否则为当前容量的2倍
    size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;

    // 分配新的数组
    T* newdata = new T[newCapacity];

    // 将旧数组中的所有元素移动到新数组
    // std::move 用于转移元素的资源，提高性能（尤其对复杂对象）
    for (size_t i = 0; i < currentSize; ++i)
    {
        newdata[i] = std::move(data[i]);
    }

    // 释放旧数组内存
    delete[] data;

    // 更新成员变量
    data = newdata;
    capacity = newCapacity;
}

template<typename T>
MyStack<T>::MyStack() :data(nullptr), capacity(0), currentSize(0)
{
    resize(); // 调用resize函数，分配初始容量（1）
}

template<typename T>
MyStack<T>::~MyStack()
{
    delete[] data; // 释放动态分配的数组内存
}

template<typename T>
MyStack<T>::MyStack(const MyStack<T>& other)
    :data(new T[other.capacity]), capacity(other.capacity), currentSize(other.currentSize)
{
    // 复制 other 栈中的所有元素到新分配的数组
    for (size_t i = 0; i < currentSize; ++i)
    {
        data[i] = other.data[i]; // 逐个复制元素
    }
}

template<typename T>
MyStack<T>::MyStack(MyStack<T>&& other)noexcept
    :data(other.data), capacity(other.capacity), currentSize(other.currentSize)
{
    // 将 other 的资源转移过来，并将 other 置为有效但未指定的状态
    other.data = nullptr;
    other.capacity = 0;
    other.currentSize = 0;
}

template<typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& other)
{
    if (this != &other) // 自赋值检查
    {
        delete[] data; // 释放当前对象的旧内存

        // 重新分配内存并复制内容
        capacity = other.capacity;
        currentSize = other.currentSize;
        data = new T[capacity]; // 分配新数组

        // 复制 other 栈中的所有元素
        for (size_t i = 0; i < currentSize; i++)
        {
            data[i] = other.data[i]; // 逐个复制元素
        }
    }
    return *this; // 返回自身引用
}

// --- 栈操作函数定义 ---

template<typename T>
void MyStack<T>::push(const T& item)
{
    if (currentSize >= capacity) // 检查是否需要扩容
        resize(); // 如果容量不足，调用resize函数
    data[currentSize] = item; // 将新元素放入当前大小索引的位置（栈顶）
    ++currentSize; // 增加元素计数器
}

template<typename T>
void MyStack<T>::push(T&& item)
{
    if (currentSize >= capacity) // 检查是否需要扩容
        resize(); // 如果容量不足，调用resize函数
    data[currentSize] = std::move(item); // 将新元素（通过移动）放入当前大小索引的位置（栈顶）
    ++currentSize; // 增加元素计数器
}

template<typename T>
T MyStack<T>::pop()
{
    if (isEmpty()) // 检查栈是否为空
    {
        throw std::runtime_error("Stack is empty! Cannot pop from an empty Stack.");
    }
    --currentSize; // 先将元素计数器减一，指向待移除的栈顶元素
    T topElement = std::move(data[currentSize]); // 获取栈顶元素（通过移动）
    // 注意：元素仍存在于数组中，但在下次push或析构时会被覆盖或释放
    return topElement; // 返回被移除的元素
}

template<typename T>
const T& MyStack<T>::top() const
{
    if (isEmpty()) // 检查栈是否为空
    {
        throw std::runtime_error("Stack is empty! Cannot pop from an empty Stack.");
    }
    // 返回数组中最后一个有效元素（currentSize - 1）的常量引用
    return data[currentSize - 1];
}

template<typename T>
bool MyStack<T>::isEmpty() const
{
    // 如果当前大小为0，则栈为空
    return currentSize == 0;
}

template<typename T>
size_t MyStack<T>::size() const
{
    // 返回当前元素数量
    return currentSize;
}

template<typename T>
void MyStack<T>::clear()
{
    // 仅重置元素计数器，不释放内存
    // 这样可以避免频繁的内存分配/释放，提高性能
    currentSize = 0;
}
