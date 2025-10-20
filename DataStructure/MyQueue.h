#pragma once
#include<iostream>
#include<stdexcept>

/**
 * @brief 一个基于动态数组实现的队列类，支持泛型类型T。
 * 使用 frontIndex 和 backIndex 指针来追踪队首和队尾位置。
 * 通过 resize 操作在必要时扩展数组容量，并在 clear 和 shrink_to_fit 中管理内存。
 *
 * @tparam T 队列中存储的元素类型
 */
template<typename T>
class MyQueue
{
private:
    T* data;           // 指向存储队列元素的动态数组的指针
    size_t capacity;   // 当前分配的数组容量
    size_t frontIndex; // 指向队首元素的索引（用于 dequeue 操作）
    size_t backIndex;  // 指向队尾 *后一个位置* 的索引（用于 enqueue 操作）
    size_t currentSize; // 当前队列中的元素数量

    /**
     * @brief 计算满足最小容量要求的新容量。
     * 采用倍增策略，确保新容量不小于 minRequiredCapacity。
     *
     * @param minRequiredCapacity 最小需要的容量
     * @return size_t 计算出的新容量
     */
    size_t getNextCapacity(size_t minRequiredCapacity) const {
        if (capacity == 0) return 1; // 初始容量为1
        size_t newCap = capacity;
        // 循环加倍容量，直到满足要求
        while (newCap < minRequiredCapacity) {
            newCap *= 2; // 倍增策略，也可以考虑 1.5 倍等其他策略
        }
        return newCap;
    }

    /**
     * @brief 重新分配内部数组的大小。
     * 将当前队列中的元素按顺序移动到新的、更大的数组中，
     * 并重置 frontIndex 为 0，backIndex 为 currentSize。
     *
     * @param newCapacityReq 如果为0，则按当前大小+1计算新容量；否则按此值计算。
     */
    void resize(size_t newCapacityReq = 0);

public:
    // --- 构造、析构、拷贝、移动 ---

    /**
     * @brief 默认构造函数。
     * 初始化队列，分配容量为1的初始数组。
     */
    MyQueue();

    /**
     * @brief 析构函数。
     * 释放内部动态分配的数组内存。
     */
    ~MyQueue();

    /**
     * @brief 拷贝构造函数。
     * 创建一个新队列，其内容与 other 队列相同。
     *
     * @param other 要拷贝的源队列
     */
    MyQueue(const MyQueue& other);

    /**
     * @brief 移动构造函数。
     * 将 other 队列的资源（data指针、容量、大小等）转移给新对象。
     * 标记为 noexcept，表示此操作不会抛出异常。
     *
     * @param other 要移动的源队列（将被置为有效但未指定的状态）
     */
    MyQueue(MyQueue&& other)noexcept;

    /**
     * @brief 拷贝赋值操作符。
     * 将当前队列的内容替换为 other 队列的内容。
     *
     * @param other 源队列
     * @return MyQueue& 引用自身
     */
    MyQueue& operator=(const MyQueue& other);

    /**
     * @brief 移动赋值操作符。
     * 将 other 队列的资源转移给当前队列。
     * 标记为 noexcept。
     *
     * @param other 要移动的源队列（将被置为有效但未指定的状态）
     * @return MyQueue& 引用自身
     */
    MyQueue& operator=(MyQueue&& other) noexcept;

    // --- 队列基本操作 ---

    /**
     * @brief 将元素添加到队列末尾（入队）。
     * 如果队列容量不足，则先进行扩容。
     *
     * @param item 要添加的常量引用元素
     */
    void enqueue(const T& item);

    /**
     * @brief 将元素（通过右值引用）添加到队列末尾（入队）。
     * 如果队列容量不足，则先进行扩容。
     * 利用移动语义，避免不必要的拷贝。
     *
     * @param item 要添加的右值引用元素
     */
    void enqueue(T&& item);

    /**
     * @brief 移除并返回队列首部的元素（出队）。
     * 如果队列为空，抛出 runtime_error 异常。
     *
     * @return T 从队首移除的元素（通过移动返回）
     */
    T dequeue();

    /**
     * @brief 返回队列首部元素的常量引用，但不移除它。
     * 如果队列为空，抛出 runtime_error 异常。
     *
     * @return const T& 队首元素的常量引用
     */
    const T& peek() const;

    /**
     * @brief 检查队列是否为空。
     *
     * @return true 如果队列中没有元素
     * @return false 如果队列中有元素
     */
    bool isEmpty() const;

    /**
     * @brief 返回队列中当前元素的数量。
     *
     * @return size_t 当前元素数量
     */
    size_t size() const;

    /**
     * @brief 清空队列，移除所有元素并释放内部数组内存。
     * 队列将变为空，容量归零。
     */
    void clear();

    /**
     * @brief 尝试释放队列中未使用的内存空间。
     * 如果当前大小小于容量，会重新分配一个刚好容纳当前元素的数组。
     * 如果队列为空，则调用 clear() 释放所有内存。
     */
    void shrink_to_fit();
};

// --- 成员函数定义 ---

template<typename T>
MyQueue<T>::MyQueue(MyQueue<T>&& other)noexcept
    : data(other.data), capacity(other.capacity), currentSize(other.currentSize), frontIndex(other.frontIndex), backIndex(other.backIndex)
{
    // 将 other 的资源转移过来，并将 other 置为有效但未指定的状态
    other.data = nullptr;
    other.capacity = 0;
    other.currentSize = 0;
    other.frontIndex = 0;
    other.backIndex = 0;
}

template<typename T>
void MyQueue<T>::resize(size_t newCapacityReq)
{
    // 计算新的容量，确保它至少能容纳 newCapacityReq 或当前大小+1
    size_t newCapacity = getNextCapacity(newCapacityReq > 0 ? newCapacityReq : currentSize + 1);

    // 分配新的数组
    T* newData = new T[newCapacity];

    // 将旧数组中的元素按逻辑顺序（从 frontIndex 开始）移动到新数组的开头
    for (size_t i = 0; i < currentSize; ++i)
    {
        newData[i] = std::move(data[(frontIndex + i) % capacity]);
    }

    // 释放旧数组内存
    delete[] data;

    // 更新成员变量
    data = newData;
    capacity = newCapacity;
    frontIndex = 0;         // 新数组中，队首总是从索引0开始
    backIndex = currentSize; // 队尾索引更新为当前大小（即最后一个元素之后的位置）
}

template<typename T>
MyQueue<T> ::MyQueue() :data(nullptr), capacity(0), currentSize(0), frontIndex(0), backIndex(0)
{
    resize(1); // 初始化时分配容量为1的数组
}

template<typename T>
MyQueue<T>::~MyQueue()
{
    delete[] data; // 释放动态分配的数组
}

template<typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& other)
    : data(new T[other.capacity]), capacity(other.capacity), currentSize(other.currentSize), frontIndex(0), backIndex(other.currentSize)
{
    // 复制 other 队列中的所有元素到新分配的数组
    for (size_t i = 0; i < currentSize; i++)
    {
        data[i] = other.data[other.frontIndex + i]; // 从 other 的 frontIndex 开始顺序复制
    }
}



template<typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue<T>& other)
{
    if (this != &other) // 自赋值检查
    {
        delete[] data; // 释放当前对象的旧内存

        // 重新分配内存并复制内容
        capacity = other.capacity;
        currentSize = other.currentSize;
        frontIndex = 0; // 新数组中，队首从0开始
        backIndex = other.currentSize; // 队尾索引为当前大小
        data = new T[capacity];
        for (size_t i = 0; i < currentSize; i++)
        {
            data[i] = other.data[other.frontIndex + i]; // 从 other 的 frontIndex 开始顺序复制
        }
    }
    return *this;
}

template<typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue<T>&& other)noexcept
{
    if (this != &other) // 自赋值检查
    {
        delete[] data; // 释放当前对象的旧内存

        // 转移 other 的资源
        data = other.data;
        capacity = other.capacity;
        currentSize = other.currentSize;
        frontIndex = other.frontIndex;
        backIndex = other.backIndex;

        // 将 other 置为有效但未指定的状态
        other.data = nullptr;
        other.capacity = 0;
        other.currentSize = 0;
        other.frontIndex = 0;
        other.backIndex = 0;
    }
    return *this;
}

template<typename T>
void MyQueue<T>::enqueue(const T& item)
{
    if (currentSize >= capacity) // 检查是否需要扩容
        resize();
    // 将新元素放入 backIndex 位置
    data[backIndex] = item;
    ++backIndex; // 移动 backIndex 指针
    ++currentSize; // 增加元素计数
}

template<typename T>
void MyQueue<T>::enqueue(T&& item)
{
    if (currentSize >= capacity) // 检查是否需要扩容
        resize();
    // 将新元素（通过移动）放入 backIndex 位置
    data[backIndex] = std::move(item);
    ++backIndex; // 移动 backIndex 指针
    ++currentSize; // 增加元素计数
}

template<typename T>
T MyQueue<T>::dequeue()
{
    if (isEmpty()) // 检查队列是否为空
    {
        throw std::runtime_error("Queue is empty! Cannot dequeue from an empty queue.");
    }
    // 获取队首元素（通过移动）
    T frontElement = std::move(data[frontIndex]);
    ++frontIndex; // 移动 frontIndex 指针
    --currentSize; // 减少元素计数
    return frontElement; // 返回被移除的元素
}

template<typename T>
const T& MyQueue<T>::peek() const
{
    if (isEmpty()) // 检查队列是否为空
    {
        throw std::runtime_error("Queue is empty! Cannot peek at an empty queue.");
    }
    // 返回队首元素的常量引用
    return data[frontIndex];
}

template<typename T>
bool MyQueue<T>::isEmpty() const
{
    // 如果当前大小为0，则队列为空
    return currentSize == 0;
}

template<typename T>
size_t MyQueue<T>::size() const
{
    // 返回当前元素数量
    return currentSize;
}

template<typename T>
void MyQueue<T>::clear()
{
    delete[] data; // 释放数组内存
    // 重置所有成员变量
    capacity = 0;
    currentSize = 0;
    frontIndex = 0;
    backIndex = 0;
    data = nullptr;
}

template<typename T>
void MyQueue<T>::shrink_to_fit() {
    if (currentSize == 0) {
        clear(); // 如果为空，直接清空释放内存
    }
    else if (currentSize < capacity) {
        // 如果当前大小小于容量，重新分配一个刚好容纳当前元素的数组
        resize(currentSize);
    }
    // 如果 currentSize == capacity，则无需操作
}