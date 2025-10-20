#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <utility>  // std::pair
#include <functional> // std::hash
#include <stdexcept>


template<typename K,typename V>
class HashMap
{
private:
	using KeyValuePair = std::pair<K, V>;
	std::vector<std::list<KeyValuePair>> buckets;
	size_t size; //��ǰԪ�ظ���
	static constexpr float LOAD_FACTOR_THRESHOLD = 0.75; //������ֵ�����������ӳ�����ֵ�Ƕ�̬����

	size_t hash(const K& key) const 
	{
		std::hash<K> hasher;
		return hasher(key) % buckets.size();
	}

	void rehash()
	{
		size_t new_capacity = buckets.size() * 2;
		std::vector<std::list<KeyValuePair>> new_buckets(new_capacity);

		for (auto& bucket : buckets)
		{
			for (auto& kv : bucket)
			{
				size_t index = std::hash<K>{}(kv.first) % new_capacity;
				new_buckets[index].push_back(kv);
			}
		}

		buckets = std::move(new_buckets); //�ƶ���ֵ��ת����Դ����Ȩ
	}

public:

	explicit HashMap(size_t initial_capacity = 16)
		:buckets(initial_capacity),size(0)
	{
	}

	void insert(const K& key, const V& value)
	{
		if (static_cast<float>(size) / buckets.size() >= LOAD_FACTOR_THRESHOLD)
		{
			rehash();
		}

		size_t index = hash(key);
		auto& bucket = buckets[index];

		for (auto& kv : bucket)
		{
			if (kv.first == key)
			{
				kv.second = value;
				return;
			}
		}

		bucket.push_back({ key,value });
		++size;
	}

	V* find(const K& key)
	{
		size_t index = hash(key);
		auto& bucket = buckets[index];

		for (auto& kv : bucket)
		{
			if (kv.first == key)
			{
				return &kv.second;
			}
		}
		return nullptr;
	}

	bool remove(const K& key)
	{
		size_t index = hash(key);
		auto& bucket = buckets[index];

		for (auto it = bucket.begin(); it != bucket.end(); ++it)
		{
			if (it->first == key)
			{
				bucket.erase(it);
				--size;
				return true;
			}
		}
		return false;
	}

	// ��ȡ��ǰԪ������
	size_t getSize() const {
		return size;
	}

	// ��ȡͰ������
	size_t getBucketCount() const {
		return buckets.size();
	}

	// ��ӡ���ڵ��ԣ��Ǳ��裩
	void debugPrint() const {
		for (size_t i = 0; i < buckets.size(); ++i) {
			std::cout << "Bucket " << i << ": ";
			for (const auto& kv : buckets[i]) {
				std::cout << "[" << kv.first << "=>" << kv.second << "] ";
			}
			std::cout << std::endl;
		}
	}
};

