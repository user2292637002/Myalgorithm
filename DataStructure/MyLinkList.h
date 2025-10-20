#include <iostream>
#include <stdexcept>
#include <initializer_list>

// 节点结构体，用于存储链表中的数据和指向下一个节点的指针
template<typename T>
struct ListNode {
    T data;              // 节点存储的数据
    ListNode* next;      // 指向下一个节点的指针

    // 构造函数：初始化数据和下一个节点指针
    ListNode(const T& value, ListNode* nextNode = nullptr);
    ListNode(T&& value, ListNode* nextNode = nullptr);
};

// 单向链表类声明
template<typename T>
class MyLinkList {
private:
    ListNode<T>* head;      // 指向链表第一个节点的指针
    size_t currentSize;     // 记录链表当前元素数量

public:
    // --- 构造、析构、拷贝、移动 ---

    // 默认构造函数：创建一个空链表
    MyLinkList();

    // 析构函数：释放链表中所有节点占用的内存
    ~MyLinkList();

    // 拷贝构造函数：深拷贝另一个链表
    MyLinkList(const MyLinkList& other);

    // 移动构造函数：转移另一个链表的资源
    MyLinkList(MyLinkList&& other) noexcept;

    // 拷贝赋值操作符
    MyLinkList& operator=(const MyLinkList& other);

    // 移动赋值操作符
    MyLinkList& operator=(MyLinkList&& other) noexcept;

    // 初始化列表构造函数
    MyLinkList(std::initializer_list<T> init);

    // --- 链表基本操作 ---

    // 在链表头部插入一个元素
    void push_front(const T& item);
    void push_front(T&& item);

    // 在链表尾部插入一个元素
    void push_back(const T& item);
    void push_back(T&& item);

    // 删除并返回链表头部的元素
    T pop_front();

    // 删除并返回链表尾部的元素
    T pop_back();

    // 返回链表头部元素的引用（不移除）
    const T& front() const;

    // 返回链表尾部元素的引用（不移除）
    const T& back() const;

    // 检查链表是否为空
    bool isEmpty() const;

    // 返回链表中元素的数量
    size_t size() const;

    // 清空链表，删除所有节点
    void clear();

    // 在指定位置插入元素（索引从0开始）
    void insert(size_t index, const T& item);

    // 删除指定位置的元素（索引从0开始）
    void erase(size_t index);

    // 查找元素在链表中的第一个索引，如果不存在返回-1
    int find(const T& item) const;
};

// ListNode 构造函数实现
template<typename T>
ListNode<T>::ListNode(const T& value, ListNode* nextNode) : data(value), next(nextNode) {}

template<typename T>
ListNode<T>::ListNode(T&& value, ListNode* nextNode) : data(std::move(value)), next(nextNode) {}

// MyLinkList 构造、析构、拷贝、移动实现

template<typename T>
MyLinkList<T>::MyLinkList() : head(nullptr), currentSize(0) {}

template<typename T>
MyLinkList<T>::~MyLinkList() {
    clear();
}

template<typename T>
MyLinkList<T>::MyLinkList(const MyLinkList& other) : head(nullptr), currentSize(0) {
    ListNode<T>* current = other.head;
    while (current != nullptr) {
        push_back(current->data); // 逐个添加元素到新链表末尾
        current = current->next;
    }
}

template<typename T>
MyLinkList<T>::MyLinkList(MyLinkList&& other) noexcept : head(other.head), currentSize(other.currentSize) {
    other.head = nullptr; // 将原链表置为空
    other.currentSize = 0;
}

template<typename T>
MyLinkList<T>& MyLinkList<T>::operator=(const MyLinkList& other) {
    if (this != &other) { // 防止自赋值
        clear(); // 先清空当前链表
        ListNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data); // 逐个添加元素到当前链表末尾
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
MyLinkList<T>& MyLinkList<T>::operator=(MyLinkList&& other) noexcept {
    if (this != &other) { // 防止自赋值
        clear(); // 清空当前链表
        head = other.head; // 接管资源
        currentSize = other.currentSize;
        other.head = nullptr; // 将原链表置为空
        other.currentSize = 0;
    }
    return *this;
}

template<typename T>
MyLinkList<T>::MyLinkList(std::initializer_list<T> init) : head(nullptr), currentSize(0) {
    for (const auto& item : init) {
        push_back(item);
    }
}

// MyLinkList 链表基本操作实现

template<typename T>
void MyLinkList<T>::push_front(const T& item) {
    head = new ListNode<T>(item, head); // 创建新节点，其next指向原head
    ++currentSize;
}

template<typename T>
void MyLinkList<T>::push_front(T&& item) {
    head = new ListNode<T>(std::move(item), head);
    ++currentSize;
}

template<typename T>
void MyLinkList<T>::push_back(const T& item) {
    if (head == nullptr) { // 如果链表为空
        head = new ListNode<T>(item);
    }
    else {
        ListNode<T>* current = head;
        // 遍历到链表末尾
        while (current->next != nullptr) {
            current = current->next;
        }
        // 在末尾创建新节点
        current->next = new ListNode<T>(item);
    }
    ++currentSize;
}

template<typename T>
void MyLinkList<T>::push_back(T&& item) {
    if (head == nullptr) {
        head = new ListNode<T>(std::move(item));
    }
    else {
        ListNode<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new ListNode<T>(std::move(item));
    }
    ++currentSize;
}

template<typename T>
T MyLinkList<T>::pop_front() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty! Cannot pop from an empty list.");
    }
    ListNode<T>* oldHead = head; // 保存原头节点指针
    T data = std::move(head->data); // 获取数据（使用移动语义）
    head = head->next; // 头指针指向下一个节点
    delete oldHead; // 释放原头节点内存
    --currentSize;
    return data;
}

template<typename T>
T MyLinkList<T>::pop_back() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty! Cannot pop from an empty list.");
    }
    if (head->next == nullptr) { // 如果只有一个节点
        T data = std::move(head->data);
        delete head;
        head = nullptr;
        --currentSize;
        return data;
    }

    // 找到倒数第二个节点
    ListNode<T>* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    // 获取最后一个节点的数据
    T data = std::move(current->next->data);
    // 删除最后一个节点
    delete current->next;
    current->next = nullptr; // 将倒数第二个节点设为新的尾节点
    --currentSize;
    return data;
}

template<typename T>
const T& MyLinkList<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("List is empty! Cannot access front of an empty list.");
    }
    return head->data;
}

template<typename T>
const T& MyLinkList<T>::back() const {
    if (isEmpty()) {
        throw std::runtime_error("List is empty! Cannot access back of an empty list.");
    }
    ListNode<T>* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current->data;
}

template<typename T>
bool MyLinkList<T>::isEmpty() const {
    return currentSize == 0;
}

template<typename T>
size_t MyLinkList<T>::size() const {
    return currentSize;
}

template<typename T>
void MyLinkList<T>::clear() {
    while (head != nullptr) {
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
    currentSize = 0;
}

template<typename T>
void MyLinkList<T>::insert(size_t index, const T& item) {
    if (index > size()) { // 插入位置不能超过当前大小
        throw std::out_of_range("Index out of range for insertion.");
    }
    if (index == 0) { // 在头部插入
        push_front(item);
        return;
    }

    ListNode<T>* current = head;
    for (size_t i = 0; i < index - 1; ++i) { // 找到插入位置的前一个节点
        current = current->next;
    }
    // 创建新节点，其next指向current的下一个节点，然后current的next指向新节点
    current->next = new ListNode<T>(item, current->next);
    ++currentSize;
}

template<typename T>
void MyLinkList<T>::erase(size_t index) {
    if (index >= size()) { // 删除位置不能超过或等于当前大小
        throw std::out_of_range("Index out of range for erasure.");
    }
    if (index == 0) { // 删除头部节点
        pop_front();
        return;
    }

    ListNode<T>* current = head;
    for (size_t i = 0; i < index - 1; ++i) { // 找到要删除节点的前一个节点
        current = current->next;
    }
    ListNode<T>* nodeToDelete = current->next; // 要删除的节点
    current->next = nodeToDelete->next; // 跳过要删除的节点
    delete nodeToDelete; // 释放内存
    --currentSize;
}

template<typename T>
int MyLinkList<T>::find(const T& item) const {
    ListNode<T>* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->data == item) {
            return index;
        }
        current = current->next;
        ++index;
    }
    return -1; // 未找到
}