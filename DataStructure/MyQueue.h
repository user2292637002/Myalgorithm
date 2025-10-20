#pragma once
#include<iostream>
#include<stdexcept>

/**
 * @brief һ�����ڶ�̬����ʵ�ֵĶ����֧࣬�ַ�������T��
 * ʹ�� frontIndex �� backIndex ָ����׷�ٶ��׺Ͷ�βλ�á�
 * ͨ�� resize �����ڱ�Ҫʱ��չ�������������� clear �� shrink_to_fit �й����ڴ档
 *
 * @tparam T �����д洢��Ԫ������
 */
template<typename T>
class MyQueue
{
private:
    T* data;           // ָ��洢����Ԫ�صĶ�̬�����ָ��
    size_t capacity;   // ��ǰ�������������
    size_t frontIndex; // ָ�����Ԫ�ص����������� dequeue ������
    size_t backIndex;  // ָ���β *��һ��λ��* ������������ enqueue ������
    size_t currentSize; // ��ǰ�����е�Ԫ������

    /**
     * @brief ����������С����Ҫ�����������
     * ���ñ������ԣ�ȷ����������С�� minRequiredCapacity��
     *
     * @param minRequiredCapacity ��С��Ҫ������
     * @return size_t �������������
     */
    size_t getNextCapacity(size_t minRequiredCapacity) const {
        if (capacity == 0) return 1; // ��ʼ����Ϊ1
        size_t newCap = capacity;
        // ѭ���ӱ�������ֱ������Ҫ��
        while (newCap < minRequiredCapacity) {
            newCap *= 2; // �������ԣ�Ҳ���Կ��� 1.5 ������������
        }
        return newCap;
    }

    /**
     * @brief ���·����ڲ�����Ĵ�С��
     * ����ǰ�����е�Ԫ�ذ�˳���ƶ����µġ�����������У�
     * ������ frontIndex Ϊ 0��backIndex Ϊ currentSize��
     *
     * @param newCapacityReq ���Ϊ0���򰴵�ǰ��С+1���������������򰴴�ֵ���㡣
     */
    void resize(size_t newCapacityReq = 0);

public:
    // --- ���졢�������������ƶ� ---

    /**
     * @brief Ĭ�Ϲ��캯����
     * ��ʼ�����У���������Ϊ1�ĳ�ʼ���顣
     */
    MyQueue();

    /**
     * @brief ����������
     * �ͷ��ڲ���̬����������ڴ档
     */
    ~MyQueue();

    /**
     * @brief �������캯����
     * ����һ���¶��У��������� other ������ͬ��
     *
     * @param other Ҫ������Դ����
     */
    MyQueue(const MyQueue& other);

    /**
     * @brief �ƶ����캯����
     * �� other ���е���Դ��dataָ�롢��������С�ȣ�ת�Ƹ��¶���
     * ���Ϊ noexcept����ʾ�˲��������׳��쳣��
     *
     * @param other Ҫ�ƶ���Դ���У�������Ϊ��Ч��δָ����״̬��
     */
    MyQueue(MyQueue&& other)noexcept;

    /**
     * @brief ������ֵ��������
     * ����ǰ���е������滻Ϊ other ���е����ݡ�
     *
     * @param other Դ����
     * @return MyQueue& ��������
     */
    MyQueue& operator=(const MyQueue& other);

    /**
     * @brief �ƶ���ֵ��������
     * �� other ���е���Դת�Ƹ���ǰ���С�
     * ���Ϊ noexcept��
     *
     * @param other Ҫ�ƶ���Դ���У�������Ϊ��Ч��δָ����״̬��
     * @return MyQueue& ��������
     */
    MyQueue& operator=(MyQueue&& other) noexcept;

    // --- ���л������� ---

    /**
     * @brief ��Ԫ����ӵ�����ĩβ����ӣ���
     * ��������������㣬���Ƚ������ݡ�
     *
     * @param item Ҫ��ӵĳ�������Ԫ��
     */
    void enqueue(const T& item);

    /**
     * @brief ��Ԫ�أ�ͨ����ֵ���ã���ӵ�����ĩβ����ӣ���
     * ��������������㣬���Ƚ������ݡ�
     * �����ƶ����壬���ⲻ��Ҫ�Ŀ�����
     *
     * @param item Ҫ��ӵ���ֵ����Ԫ��
     */
    void enqueue(T&& item);

    /**
     * @brief �Ƴ������ض����ײ���Ԫ�أ����ӣ���
     * �������Ϊ�գ��׳� runtime_error �쳣��
     *
     * @return T �Ӷ����Ƴ���Ԫ�أ�ͨ���ƶ����أ�
     */
    T dequeue();

    /**
     * @brief ���ض����ײ�Ԫ�صĳ������ã������Ƴ�����
     * �������Ϊ�գ��׳� runtime_error �쳣��
     *
     * @return const T& ����Ԫ�صĳ�������
     */
    const T& peek() const;

    /**
     * @brief �������Ƿ�Ϊ�ա�
     *
     * @return true ���������û��Ԫ��
     * @return false �����������Ԫ��
     */
    bool isEmpty() const;

    /**
     * @brief ���ض����е�ǰԪ�ص�������
     *
     * @return size_t ��ǰԪ������
     */
    size_t size() const;

    /**
     * @brief ��ն��У��Ƴ�����Ԫ�ز��ͷ��ڲ������ڴ档
     * ���н���Ϊ�գ��������㡣
     */
    void clear();

    /**
     * @brief �����ͷŶ�����δʹ�õ��ڴ�ռ䡣
     * �����ǰ��СС�������������·���һ���պ����ɵ�ǰԪ�ص����顣
     * �������Ϊ�գ������ clear() �ͷ������ڴ档
     */
    void shrink_to_fit();
};

// --- ��Ա�������� ---

template<typename T>
MyQueue<T>::MyQueue(MyQueue<T>&& other)noexcept
    : data(other.data), capacity(other.capacity), currentSize(other.currentSize), frontIndex(other.frontIndex), backIndex(other.backIndex)
{
    // �� other ����Դת�ƹ��������� other ��Ϊ��Ч��δָ����״̬
    other.data = nullptr;
    other.capacity = 0;
    other.currentSize = 0;
    other.frontIndex = 0;
    other.backIndex = 0;
}

template<typename T>
void MyQueue<T>::resize(size_t newCapacityReq)
{
    // �����µ�������ȷ�������������� newCapacityReq ��ǰ��С+1
    size_t newCapacity = getNextCapacity(newCapacityReq > 0 ? newCapacityReq : currentSize + 1);

    // �����µ�����
    T* newData = new T[newCapacity];

    // ���������е�Ԫ�ذ��߼�˳�򣨴� frontIndex ��ʼ���ƶ���������Ŀ�ͷ
    for (size_t i = 0; i < currentSize; ++i)
    {
        newData[i] = std::move(data[(frontIndex + i) % capacity]);
    }

    // �ͷž������ڴ�
    delete[] data;

    // ���³�Ա����
    data = newData;
    capacity = newCapacity;
    frontIndex = 0;         // �������У��������Ǵ�����0��ʼ
    backIndex = currentSize; // ��β��������Ϊ��ǰ��С�������һ��Ԫ��֮���λ�ã�
}

template<typename T>
MyQueue<T> ::MyQueue() :data(nullptr), capacity(0), currentSize(0), frontIndex(0), backIndex(0)
{
    resize(1); // ��ʼ��ʱ��������Ϊ1������
}

template<typename T>
MyQueue<T>::~MyQueue()
{
    delete[] data; // �ͷŶ�̬���������
}

template<typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& other)
    : data(new T[other.capacity]), capacity(other.capacity), currentSize(other.currentSize), frontIndex(0), backIndex(other.currentSize)
{
    // ���� other �����е�����Ԫ�ص��·��������
    for (size_t i = 0; i < currentSize; i++)
    {
        data[i] = other.data[other.frontIndex + i]; // �� other �� frontIndex ��ʼ˳����
    }
}



template<typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue<T>& other)
{
    if (this != &other) // �Ը�ֵ���
    {
        delete[] data; // �ͷŵ�ǰ����ľ��ڴ�

        // ���·����ڴ沢��������
        capacity = other.capacity;
        currentSize = other.currentSize;
        frontIndex = 0; // �������У����״�0��ʼ
        backIndex = other.currentSize; // ��β����Ϊ��ǰ��С
        data = new T[capacity];
        for (size_t i = 0; i < currentSize; i++)
        {
            data[i] = other.data[other.frontIndex + i]; // �� other �� frontIndex ��ʼ˳����
        }
    }
    return *this;
}

template<typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue<T>&& other)noexcept
{
    if (this != &other) // �Ը�ֵ���
    {
        delete[] data; // �ͷŵ�ǰ����ľ��ڴ�

        // ת�� other ����Դ
        data = other.data;
        capacity = other.capacity;
        currentSize = other.currentSize;
        frontIndex = other.frontIndex;
        backIndex = other.backIndex;

        // �� other ��Ϊ��Ч��δָ����״̬
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
    if (currentSize >= capacity) // ����Ƿ���Ҫ����
        resize();
    // ����Ԫ�ط��� backIndex λ��
    data[backIndex] = item;
    ++backIndex; // �ƶ� backIndex ָ��
    ++currentSize; // ����Ԫ�ؼ���
}

template<typename T>
void MyQueue<T>::enqueue(T&& item)
{
    if (currentSize >= capacity) // ����Ƿ���Ҫ����
        resize();
    // ����Ԫ�أ�ͨ���ƶ������� backIndex λ��
    data[backIndex] = std::move(item);
    ++backIndex; // �ƶ� backIndex ָ��
    ++currentSize; // ����Ԫ�ؼ���
}

template<typename T>
T MyQueue<T>::dequeue()
{
    if (isEmpty()) // �������Ƿ�Ϊ��
    {
        throw std::runtime_error("Queue is empty! Cannot dequeue from an empty queue.");
    }
    // ��ȡ����Ԫ�أ�ͨ���ƶ���
    T frontElement = std::move(data[frontIndex]);
    ++frontIndex; // �ƶ� frontIndex ָ��
    --currentSize; // ����Ԫ�ؼ���
    return frontElement; // ���ر��Ƴ���Ԫ��
}

template<typename T>
const T& MyQueue<T>::peek() const
{
    if (isEmpty()) // �������Ƿ�Ϊ��
    {
        throw std::runtime_error("Queue is empty! Cannot peek at an empty queue.");
    }
    // ���ض���Ԫ�صĳ�������
    return data[frontIndex];
}

template<typename T>
bool MyQueue<T>::isEmpty() const
{
    // �����ǰ��СΪ0�������Ϊ��
    return currentSize == 0;
}

template<typename T>
size_t MyQueue<T>::size() const
{
    // ���ص�ǰԪ������
    return currentSize;
}

template<typename T>
void MyQueue<T>::clear()
{
    delete[] data; // �ͷ������ڴ�
    // �������г�Ա����
    capacity = 0;
    currentSize = 0;
    frontIndex = 0;
    backIndex = 0;
    data = nullptr;
}

template<typename T>
void MyQueue<T>::shrink_to_fit() {
    if (currentSize == 0) {
        clear(); // ���Ϊ�գ�ֱ������ͷ��ڴ�
    }
    else if (currentSize < capacity) {
        // �����ǰ��СС�����������·���һ���պ����ɵ�ǰԪ�ص�����
        resize(currentSize);
    }
    // ��� currentSize == capacity�����������
}