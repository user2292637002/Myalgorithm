#pragma once
#include<iostream>
#include<stdexcept>

/**
 * @brief һ�����ڶ�̬����ʵ�ֵ�ջ�֧࣬�ַ�������T��
 * �ṩ�˱�׼��ջ�������� push, pop, top, isEmpty �ȡ�
 *
 * @tparam T ջ�д洢��Ԫ������
 */
template<typename T>
class MyStack
{
private:
    T* data;          // ָ��洢ջԪ�صĶ�̬�����ָ��
    size_t capacity;  // ��ǰ�������������
    size_t currentSize; // ��ǰջ��Ԫ�ص�����

    /**
     * @brief ���·����ڲ�����Ĵ�С��
     * ����ǰջ�е�Ԫ�ذ�˳���ƶ����µġ�����������С�
     * �����ǰ����Ϊ0����������Ϊ1������������Ϊ��ǰ������2����
     */
    void resize();

public:
    // --- ���졢�������������ƶ� ---

    /**
     * @brief Ĭ�Ϲ��캯����
     * ��ʼ��ջ����������Ϊ1�ĳ�ʼ���顣
     */
    MyStack();

    /**
     * @brief ����������
     * �ͷ��ڲ���̬����������ڴ档
     */
    ~MyStack();

    /**
     * @brief �������캯����
     * ����һ����ջ���������� other ջ��ͬ��
     *
     * @param other Ҫ������Դջ
     */
    MyStack(const MyStack& other);

    /**
     * @brief �ƶ����캯����
     * �� other ջ����Դ��dataָ�롢��������С�ȣ�ת�Ƹ��¶���
     * ���Ϊ noexcept����ʾ�˲��������׳��쳣��
     *
     * @param other Ҫ�ƶ���Դջ��������Ϊ��Ч��δָ����״̬��
     */
    MyStack(MyStack&& other)noexcept;

    /**
     * @brief ������ֵ��������
     * ����ǰջ�������滻Ϊ other ջ�����ݡ�
     *
     * @param other Դջ
     * @return MyStack& ��������
     */
    MyStack& operator=(const MyStack& other);

    /**
     * @brief �ƶ���ֵ��������
     * �� other ջ����Դת�Ƹ���ǰջ��
     * ���Ϊ noexcept��
     *
     * @param other Ҫ�ƶ���Դջ��������Ϊ��Ч��δָ����״̬��
     * @return MyStack& ��������
     */
    MyStack& operator=(MyStack&& other)noexcept;

    // --- ջ�������� ---

    /**
     * @brief ��Ԫ����ӵ�ջ������ջ����
     * ���ջ�������㣬���Ƚ������ݡ�
     *
     * @param item Ҫ��ӵĳ�������Ԫ��
     */
    void push(const T& item);

    /**
     * @brief ��Ԫ�أ�ͨ����ֵ���ã���ӵ�ջ������ջ����
     * ���ջ�������㣬���Ƚ������ݡ�
     * �����ƶ����壬���ⲻ��Ҫ�Ŀ�����
     *
     * @param item Ҫ��ӵ���ֵ����Ԫ��
     */
    void push(T&& item);

    /**
     * @brief �Ƴ�������ջ����Ԫ�أ���ջ����
     * ���ջΪ�գ��׳� runtime_error �쳣��
     *
     * @return T ��ջ���Ƴ���Ԫ�أ�ͨ���ƶ����أ�
     */
    T pop();

    /**
     * @brief ����ջ��Ԫ�صĳ������ã������Ƴ�����
     * ���ջΪ�գ��׳� runtime_error �쳣��
     *
     * @return const T& ջ��Ԫ�صĳ�������
     */
    const T& top() const;

    /**
     * @brief ���ջ�Ƿ�Ϊ�ա�
     *
     * @return true ���ջ��û��Ԫ��
     * @return false ���ջ����Ԫ��
     */
    bool isEmpty() const;

    /**
     * @brief ����ջ�е�ǰԪ�ص�������
     *
     * @return size_t ��ǰԪ������
     */
    size_t size() const;

    /**
     * @brief ���ջ���Ƴ�����Ԫ�ء�
     * ������Ԫ�ؼ����������ͷ��ڲ������ڴ档
     * ջ����Ϊ�գ���������ǰ������
     */
    void clear();
};

// --- ��Ա�������� ---

/**
 * @brief �����ƶ���ֵ��������ʵ�֡�
 * ��ʵ�ַ��� public ����֮��private ����֮ǰ����Ȼ�ڼ����Ͽ��У�
 * ��ͨ�����齫���г�Ա�����Ķ������������֮��
 *
 * @tparam T ջԪ������
 * @param other Ҫ�ƶ���Դջ
 * @return MyStack<T>& ��������
 */
template<typename T>
MyStack<T>& MyStack<T>::operator=(MyStack<T>&& other)noexcept
{
    if (this != &other) // �Ը�ֵ��飺��ֹ������ֵ���Լ�
    {
        delete[] data; // �ͷŵ�ǰ����ľ��ڴ�

        // ת�� other ����Դ
        data = other.data;
        capacity = other.capacity;
        currentSize = other.currentSize;

        // �� other ��Ϊ��Ч��δָ����״̬�������ָ��ͼ�������
        other.data = nullptr;
        other.capacity = 0;
        other.currentSize = 0;
    }
    return *this; // �����������ã�֧����ʽ��ֵ
}

template<typename T>
void MyStack<T>::resize()
{
    // �����������������ǰ����Ϊ0����������Ϊ1������Ϊ��ǰ������2��
    size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;

    // �����µ�����
    T* newdata = new T[newCapacity];

    // ���������е�����Ԫ���ƶ���������
    // std::move ����ת��Ԫ�ص���Դ��������ܣ�����Ը��Ӷ���
    for (size_t i = 0; i < currentSize; ++i)
    {
        newdata[i] = std::move(data[i]);
    }

    // �ͷž������ڴ�
    delete[] data;

    // ���³�Ա����
    data = newdata;
    capacity = newCapacity;
}

template<typename T>
MyStack<T>::MyStack() :data(nullptr), capacity(0), currentSize(0)
{
    resize(); // ����resize�����������ʼ������1��
}

template<typename T>
MyStack<T>::~MyStack()
{
    delete[] data; // �ͷŶ�̬����������ڴ�
}

template<typename T>
MyStack<T>::MyStack(const MyStack<T>& other)
    :data(new T[other.capacity]), capacity(other.capacity), currentSize(other.currentSize)
{
    // ���� other ջ�е�����Ԫ�ص��·��������
    for (size_t i = 0; i < currentSize; ++i)
    {
        data[i] = other.data[i]; // �������Ԫ��
    }
}

template<typename T>
MyStack<T>::MyStack(MyStack<T>&& other)noexcept
    :data(other.data), capacity(other.capacity), currentSize(other.currentSize)
{
    // �� other ����Դת�ƹ��������� other ��Ϊ��Ч��δָ����״̬
    other.data = nullptr;
    other.capacity = 0;
    other.currentSize = 0;
}

template<typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& other)
{
    if (this != &other) // �Ը�ֵ���
    {
        delete[] data; // �ͷŵ�ǰ����ľ��ڴ�

        // ���·����ڴ沢��������
        capacity = other.capacity;
        currentSize = other.currentSize;
        data = new T[capacity]; // ����������

        // ���� other ջ�е�����Ԫ��
        for (size_t i = 0; i < currentSize; i++)
        {
            data[i] = other.data[i]; // �������Ԫ��
        }
    }
    return *this; // ������������
}

// --- ջ������������ ---

template<typename T>
void MyStack<T>::push(const T& item)
{
    if (currentSize >= capacity) // ����Ƿ���Ҫ����
        resize(); // ����������㣬����resize����
    data[currentSize] = item; // ����Ԫ�ط��뵱ǰ��С������λ�ã�ջ����
    ++currentSize; // ����Ԫ�ؼ�����
}

template<typename T>
void MyStack<T>::push(T&& item)
{
    if (currentSize >= capacity) // ����Ƿ���Ҫ����
        resize(); // ����������㣬����resize����
    data[currentSize] = std::move(item); // ����Ԫ�أ�ͨ���ƶ������뵱ǰ��С������λ�ã�ջ����
    ++currentSize; // ����Ԫ�ؼ�����
}

template<typename T>
T MyStack<T>::pop()
{
    if (isEmpty()) // ���ջ�Ƿ�Ϊ��
    {
        throw std::runtime_error("Stack is empty! Cannot pop from an empty Stack.");
    }
    --currentSize; // �Ƚ�Ԫ�ؼ�������һ��ָ����Ƴ���ջ��Ԫ��
    T topElement = std::move(data[currentSize]); // ��ȡջ��Ԫ�أ�ͨ���ƶ���
    // ע�⣺Ԫ���Դ����������У������´�push������ʱ�ᱻ���ǻ��ͷ�
    return topElement; // ���ر��Ƴ���Ԫ��
}

template<typename T>
const T& MyStack<T>::top() const
{
    if (isEmpty()) // ���ջ�Ƿ�Ϊ��
    {
        throw std::runtime_error("Stack is empty! Cannot pop from an empty Stack.");
    }
    // �������������һ����ЧԪ�أ�currentSize - 1���ĳ�������
    return data[currentSize - 1];
}

template<typename T>
bool MyStack<T>::isEmpty() const
{
    // �����ǰ��СΪ0����ջΪ��
    return currentSize == 0;
}

template<typename T>
size_t MyStack<T>::size() const
{
    // ���ص�ǰԪ������
    return currentSize;
}

template<typename T>
void MyStack<T>::clear()
{
    // ������Ԫ�ؼ����������ͷ��ڴ�
    // �������Ա���Ƶ�����ڴ����/�ͷţ��������
    currentSize = 0;
}
