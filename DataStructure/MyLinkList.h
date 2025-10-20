#include <iostream>
#include <stdexcept>
#include <initializer_list>

// �ڵ�ṹ�壬���ڴ洢�����е����ݺ�ָ����һ���ڵ��ָ��
template<typename T>
struct ListNode {
    T data;              // �ڵ�洢������
    ListNode* next;      // ָ����һ���ڵ��ָ��

    // ���캯������ʼ�����ݺ���һ���ڵ�ָ��
    ListNode(const T& value, ListNode* nextNode = nullptr);
    ListNode(T&& value, ListNode* nextNode = nullptr);
};

// ��������������
template<typename T>
class MyLinkList {
private:
    ListNode<T>* head;      // ָ�������һ���ڵ��ָ��
    size_t currentSize;     // ��¼����ǰԪ������

public:
    // --- ���졢�������������ƶ� ---

    // Ĭ�Ϲ��캯��������һ��������
    MyLinkList();

    // �����������ͷ����������нڵ�ռ�õ��ڴ�
    ~MyLinkList();

    // �������캯���������һ������
    MyLinkList(const MyLinkList& other);

    // �ƶ����캯����ת����һ���������Դ
    MyLinkList(MyLinkList&& other) noexcept;

    // ������ֵ������
    MyLinkList& operator=(const MyLinkList& other);

    // �ƶ���ֵ������
    MyLinkList& operator=(MyLinkList&& other) noexcept;

    // ��ʼ���б��캯��
    MyLinkList(std::initializer_list<T> init);

    // --- ����������� ---

    // ������ͷ������һ��Ԫ��
    void push_front(const T& item);
    void push_front(T&& item);

    // ������β������һ��Ԫ��
    void push_back(const T& item);
    void push_back(T&& item);

    // ɾ������������ͷ����Ԫ��
    T pop_front();

    // ɾ������������β����Ԫ��
    T pop_back();

    // ��������ͷ��Ԫ�ص����ã����Ƴ���
    const T& front() const;

    // ��������β��Ԫ�ص����ã����Ƴ���
    const T& back() const;

    // ��������Ƿ�Ϊ��
    bool isEmpty() const;

    // ����������Ԫ�ص�����
    size_t size() const;

    // �������ɾ�����нڵ�
    void clear();

    // ��ָ��λ�ò���Ԫ�أ�������0��ʼ��
    void insert(size_t index, const T& item);

    // ɾ��ָ��λ�õ�Ԫ�أ�������0��ʼ��
    void erase(size_t index);

    // ����Ԫ���������еĵ�һ����������������ڷ���-1
    int find(const T& item) const;
};

// ListNode ���캯��ʵ��
template<typename T>
ListNode<T>::ListNode(const T& value, ListNode* nextNode) : data(value), next(nextNode) {}

template<typename T>
ListNode<T>::ListNode(T&& value, ListNode* nextNode) : data(std::move(value)), next(nextNode) {}

// MyLinkList ���졢�������������ƶ�ʵ��

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
        push_back(current->data); // ������Ԫ�ص�������ĩβ
        current = current->next;
    }
}

template<typename T>
MyLinkList<T>::MyLinkList(MyLinkList&& other) noexcept : head(other.head), currentSize(other.currentSize) {
    other.head = nullptr; // ��ԭ������Ϊ��
    other.currentSize = 0;
}

template<typename T>
MyLinkList<T>& MyLinkList<T>::operator=(const MyLinkList& other) {
    if (this != &other) { // ��ֹ�Ը�ֵ
        clear(); // ����յ�ǰ����
        ListNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data); // ������Ԫ�ص���ǰ����ĩβ
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
MyLinkList<T>& MyLinkList<T>::operator=(MyLinkList&& other) noexcept {
    if (this != &other) { // ��ֹ�Ը�ֵ
        clear(); // ��յ�ǰ����
        head = other.head; // �ӹ���Դ
        currentSize = other.currentSize;
        other.head = nullptr; // ��ԭ������Ϊ��
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

// MyLinkList �����������ʵ��

template<typename T>
void MyLinkList<T>::push_front(const T& item) {
    head = new ListNode<T>(item, head); // �����½ڵ㣬��nextָ��ԭhead
    ++currentSize;
}

template<typename T>
void MyLinkList<T>::push_front(T&& item) {
    head = new ListNode<T>(std::move(item), head);
    ++currentSize;
}

template<typename T>
void MyLinkList<T>::push_back(const T& item) {
    if (head == nullptr) { // �������Ϊ��
        head = new ListNode<T>(item);
    }
    else {
        ListNode<T>* current = head;
        // ����������ĩβ
        while (current->next != nullptr) {
            current = current->next;
        }
        // ��ĩβ�����½ڵ�
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
    ListNode<T>* oldHead = head; // ����ԭͷ�ڵ�ָ��
    T data = std::move(head->data); // ��ȡ���ݣ�ʹ���ƶ����壩
    head = head->next; // ͷָ��ָ����һ���ڵ�
    delete oldHead; // �ͷ�ԭͷ�ڵ��ڴ�
    --currentSize;
    return data;
}

template<typename T>
T MyLinkList<T>::pop_back() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty! Cannot pop from an empty list.");
    }
    if (head->next == nullptr) { // ���ֻ��һ���ڵ�
        T data = std::move(head->data);
        delete head;
        head = nullptr;
        --currentSize;
        return data;
    }

    // �ҵ������ڶ����ڵ�
    ListNode<T>* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    // ��ȡ���һ���ڵ������
    T data = std::move(current->next->data);
    // ɾ�����һ���ڵ�
    delete current->next;
    current->next = nullptr; // �������ڶ����ڵ���Ϊ�µ�β�ڵ�
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
    if (index > size()) { // ����λ�ò��ܳ�����ǰ��С
        throw std::out_of_range("Index out of range for insertion.");
    }
    if (index == 0) { // ��ͷ������
        push_front(item);
        return;
    }

    ListNode<T>* current = head;
    for (size_t i = 0; i < index - 1; ++i) { // �ҵ�����λ�õ�ǰһ���ڵ�
        current = current->next;
    }
    // �����½ڵ㣬��nextָ��current����һ���ڵ㣬Ȼ��current��nextָ���½ڵ�
    current->next = new ListNode<T>(item, current->next);
    ++currentSize;
}

template<typename T>
void MyLinkList<T>::erase(size_t index) {
    if (index >= size()) { // ɾ��λ�ò��ܳ�������ڵ�ǰ��С
        throw std::out_of_range("Index out of range for erasure.");
    }
    if (index == 0) { // ɾ��ͷ���ڵ�
        pop_front();
        return;
    }

    ListNode<T>* current = head;
    for (size_t i = 0; i < index - 1; ++i) { // �ҵ�Ҫɾ���ڵ��ǰһ���ڵ�
        current = current->next;
    }
    ListNode<T>* nodeToDelete = current->next; // Ҫɾ���Ľڵ�
    current->next = nodeToDelete->next; // ����Ҫɾ���Ľڵ�
    delete nodeToDelete; // �ͷ��ڴ�
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
    return -1; // δ�ҵ�
}