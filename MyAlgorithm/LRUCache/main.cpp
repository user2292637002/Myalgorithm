#include<iostream>
#include<unordered_map>
using namespace std;

struct  Node
{
	int value;
	int key;
	Node* next;
	Node* prev;
	Node(int k, int v) :key(k), value(v), next(nullptr), prev(nullptr) {}
};

class LRUCache
{
public:
	LRUCache(int capacity) 
	{
		this->capacity = capacity;
		head = new Node(0, 0);
		tail = new Node(0, 0);
		head->next = tail;
		tail->prev = head;
	};
	~LRUCache() 
	{
		Node* curr = head;
		while (curr != nullptr)
		{
			Node* next = curr->next;
			delete curr;
			curr = next;
		}
	};

	int get(int key)
	{
		if (cache.find(key) == cache.end())
		{
			return -1;
		}
		Node* node = cache[key];
		moveToHead(node);
		return node->value;
	}

	void put(int key, int value)
	{
		if (cache.find(key) != cache.end())
		{
			Node* node = cache[key];
			node->value = value;
			moveToHead(node);
		}
		else
		{
			Node* node = new Node(key, value);
			cache[key] = node;
			addToHead(node);
			if (cache.size() > capacity)
			{
				Node* tailNode = removeTail();
				cache.erase(tailNode->key);
				delete tailNode;
			}
		}
	}

private:
	int capacity;
	unordered_map<int, Node*> cache;
	// 虚拟头结点（最常用）
	Node* head;
	// 虚拟尾结点（最不常用）
	Node* tail;
	void moveToHead(Node* node)
	{
		removeNode(node);
		addToHead(node);
	}

	void removeNode(Node* node)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	void addToHead(Node* node)
	{
		node->next = head->next;
		node->prev = head;
		head->next->prev = node;
		head->next = node;
	}

	Node* removeTail()
	{
		Node* node = tail->prev;
		removeNode(node);
		return node;
	}
};




int main()
{
	return 0;
}