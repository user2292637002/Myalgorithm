/**
 * @file HashMap.h
 * @brief 哈希表（HashMap）实现，使用链地址法解决哈希冲突
 * 
 * 实现特性：
 * - 使用模板支持任意类型的键值对
 * - 采用链地址法（开散列）处理哈希冲突
 * - 支持动态扩容，当负载因子超过阈值时自动扩容
 * - 提供插入、查找、删除等基本操作
 */

#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <utility>  // std::pair
#include <functional> // std::hash
#include <stdexcept>

/**
 * @class HashMap
 * @brief 哈希表模板类
 * 
 * 使用链地址法（Separate Chaining）解决哈希冲突：
 * - 每个桶（bucket）是一个链表，存储哈希值相同的键值对
 * - 当负载因子（元素数/桶数）超过阈值时，自动扩容并重新哈希
 * 
 * @tparam K 键（Key）的类型，必须支持 std::hash 和相等比较
 * @tparam V 值（Value）的类型
 * 
 * 时间复杂度：
 * - 插入、查找、删除：平均 O(1)，最坏 O(n)（所有元素都在同一个桶中）
 */
template<typename K,typename V>
class HashMap
{
private:
	using KeyValuePair = std::pair<K, V>;  // 键值对类型别名

	std::vector<std::list<KeyValuePair>> buckets;  // 桶数组，每个桶是一个链表
	size_t size;  // 当前存储的元素个数
	static constexpr float LOAD_FACTOR_THRESHOLD = 0.75f;  // 负载因子阈值，超过此值触发扩容
	std::hash<K> hasher;
	/**
	 * @brief 计算键的哈希值并映射到桶索引
	 * 
	 * 使用 std::hash 计算键的哈希值，然后对桶数取模得到索引
	 * 
	 * @param key 要哈希的键
	 * @return 键对应的桶索引（0 到 buckets.size()-1）
	 */
	size_t hash(const K& key) const 
	{
		return hasher(key) & (buckets.size() - 1);
	}

	/**
	 * @brief 重新哈希，扩容并重新分配所有元素
	 * 
	 * 当负载因子超过阈值时调用此函数：
	 * 1. 创建容量为原来2倍的新桶数组
	 * 2. 遍历所有旧桶中的元素
	 * 3. 根据新的桶数重新计算每个元素的哈希索引
	 * 4. 将元素插入到新桶中
	 * 5. 使用移动语义转移资源所有权，避免不必要的拷贝
	 * 
	 * 时间复杂度：O(n)，其中 n 是元素总数
	 */
	void rehash()
	{
		size_t new_capacity = buckets.size() * 2;
		std::vector<std::list<KeyValuePair>> new_buckets(new_capacity);

		// 遍历所有旧桶
		for (auto& bucket : buckets)
		{
			// 遍历桶中的每个键值对
			for (auto& kv : bucket)
			{
				// 使用新的容量重新计算哈希索引
				size_t index = std::hash<K>{}(kv.first) % new_capacity;
				new_buckets[index].push_back(kv);
			}
		}

		// 使用移动赋值，转移资源所有权，避免拷贝
		buckets = std::move(new_buckets);
	}

public:

	/**
	 * @brief 构造函数，创建指定初始容量的哈希表
	 * 
	 * @param initial_capacity 初始桶的数量，默认为16
	 * 
	 * 使用 explicit 关键字防止隐式类型转换
	 */
	explicit HashMap(size_t initial_capacity = 16)
		:buckets(std::max<size_t>(1,initial_capacity)),size(0)
	{
	}

	/**
	 * @brief 插入或更新键值对
	 * 
	 * 插入逻辑：
	 * 1. 检查负载因子，如果超过阈值则先扩容
	 * 2. 计算键的哈希值，找到对应的桶
	 * 3. 在桶中查找是否已存在相同的键
	 *    - 如果存在，更新对应的值
	 *    - 如果不存在，在桶的末尾插入新的键值对
	 * 
	 * @param key 要插入或更新的键
	 * @param value 对应的值
	 * 
	 * 时间复杂度：平均 O(1)，最坏 O(n)（需要扩容时）
	 */
	void insert(const K& key, const V& value)
	{
		// 检查负载因子，如果超过阈值则扩容
		if (static_cast<float>(size) / buckets.size() >= LOAD_FACTOR_THRESHOLD)
		{
			rehash();
		}

		// 计算键的哈希索引
		size_t index = hash(key);
		auto& bucket = buckets[index];

		// 在桶中查找是否已存在相同的键
		for (auto& kv : bucket)
		{
			if (kv.first == key)
			{
				// 键已存在，更新值
				kv.second = value;
				return;
			}
		}

		// 键不存在，插入新的键值对
		bucket.push_back({ key,value });
		++size;
	}

	/**
	 * @brief 查找指定键对应的值
	 * 
	 * 查找过程：
	 * 1. 计算键的哈希值，找到对应的桶
	 * 2. 在桶的链表中线性查找匹配的键
	 * 3. 如果找到，返回值的指针；否则返回 nullptr
	 * 
	 * @param key 要查找的键
	 * @return 如果找到，返回指向值的指针；否则返回 nullptr
	 * 
	 * 时间复杂度：平均 O(1)，最坏 O(n)（所有元素都在同一个桶中）
	 * 
	 * 注意：返回的指针在哈希表结构发生变化（如扩容）后可能失效
	 */
	const V* find(const K& key) const
	{
		size_t index = hash(key);
		auto& bucket = buckets[index];

		// 在桶的链表中查找匹配的键
		for (auto& kv : bucket)
		{
			if (kv.first == key)
			{
				return &kv.second;
			}
		}
		return nullptr;
	}

	/**
	 * @brief 删除指定键的键值对
	 * 
	 * 删除过程：
	 * 1. 计算键的哈希值，找到对应的桶
	 * 2. 在桶的链表中查找匹配的键
	 * 3. 如果找到，使用迭代器删除该元素，并更新元素计数
	 * 
	 * @param key 要删除的键
	 * @return true 如果成功删除，false 如果键不存在
	 * 
	 * 时间复杂度：平均 O(1)，最坏 O(n)（所有元素都在同一个桶中）
	 */
	bool remove(const K& key)
	{
		size_t index = hash(key);
		auto& bucket = buckets[index];

		// 使用迭代器遍历桶的链表
		for (auto it = bucket.begin(); it != bucket.end(); ++it)
		{
			if (it->first == key)
			{
				// 找到匹配的键，删除该元素
				bucket.erase(it);
				--size;
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief 获取当前哈希表中存储的元素数量
	 * @return 元素数量
	 */
	size_t getSize() const {
		return size;
	}

	/**
	 * @brief 获取当前桶（bucket）的数量
	 * 
	 * 桶的数量决定了哈希表的容量，当负载因子超过阈值时会自动扩容
	 * 
	 * @return 桶的数量
	 */
	size_t getBucketCount() const {
		return buckets.size();
	}

	/**
	 * @brief 打印哈希表的所有内容，用于调试
	 * 
	 * 输出格式：
	 * Bucket 0: [key1=>value1] [key2=>value2] ...
	 * Bucket 1: [key3=>value3] ...
	 * ...
	 * 
	 * 每个桶占一行，显示该桶中所有的键值对
	 */
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

