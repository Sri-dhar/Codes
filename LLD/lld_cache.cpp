#include <bits/stdc++.h>
using namespace std;

class StorageException;
class Storage;
class EvictionPolicy;
template <typename T>
struct Node;
template <typename T>
class DoublyLinkedList;

class StorageException : public exception
{
private:
	string message;

public:
	StorageException(const string &msg) : message(msg) {}
	const char *what() const noexcept override
	{
		return message.c_str();
	}
};

class Storage
{
	int capacity;

public:
	map<string, string> storage;
	Storage(int capacity) : capacity(capacity) {}
	void setCapacity(int capacity) { this->capacity = capacity; }
	int getCapacity() const { return capacity; }
	int updateCapacity(int capacity)
	{
		if (capacity < storage.size())
		{
			throw StorageException("Cannot reduce capacity below current storage size.");
			// cout << "Cannot reduce capacity below current storage size.\n";
			return -1;
		}
		this->capacity = capacity;
		return capacity;
	}
	void addData(const string &key, const string &value)
	{
		if (storage.size() >= capacity)
		{
			throw StorageException("Storage is full. Cannot add more data.");
			// cout << "Storage is full. Cannot add more data.\n";
			return;
		}
		storage[key] = value;
	}
	void removeData(const string &key)
	{
		if (storage.find(key) == storage.end())
		{
			throw StorageException("Key not found in storage.");
			// cout << "Key not found in storage.\n";
			return;
		}
		storage.erase(key);
	}
	string getData(const string &key) const
	{
		if (storage.find(key) == storage.end())
		{
			throw StorageException("Key not found in storage.");
			// cout << "Key not found in storage.\n";
			return "";
		}
		return storage.at(key);
	}
};

template <typename T>
struct Node
{
	T data;
	Node *prev;
	Node *next;
	Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList
{
private:
	Node<T> *head;
	Node<T> *tail;
	size_t size;

public:
	DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	~DoublyLinkedList()
	{
		while (head)
		{
			Node<T> *temp = head; // Change from Node* temp
			head = head->next;
			delete temp;
		}
	}

	void pushFront(const T &value)
	{
		Node<T> *newNode = new Node<T>(value);
		if (!head)
		{
			head = tail = newNode;
		}
		else
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		size++;
	}

	T detachNode(const T &value)
	{
		Node<T> *temp = head;
		while (temp != nullptr)
		{
			if (temp->data == value)
			{
				if (temp->prev)
				{
					temp->prev->next = temp->next;
				}
				else
				{
					head = temp->next;
				}
				if (temp->next)
				{
					temp->next->prev = temp->prev;
				}
				else
				{
					tail = temp->prev;
				}
				size--;
				return temp->data;
			}
			temp = temp->next;
		}
		return NULL;
	}

	void moveHead()
	{
		if (head == NULL)
		{
			return;
		}
		Node<T> *temp = head;
		head = head->next;
		if (head)
		{
			head->prev = NULL;
		}
		else
		{
			tail = NULL;
		}
		delete temp;
		size--;
	}

	void pushBack(const T &value)
	{
		Node<T> *newNode = new Node(value);
		if (!tail)
		{
			head = tail = newNode;
		}
		else
		{
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}

	Node<T> *frontNode()
	{
		return head;
	}

	void popFront()
	{
		if (!head)
			return;
		Node<T> *temp = head;
		head = head->next;
		if (head)
		{
			head->prev = nullptr;
		}
		else
		{
			tail = nullptr;
		}
		delete temp;
		size--;
	}

	void popBack()
	{
		if (!tail)
			return;
		Node<T> *temp = tail;
		tail = tail->prev;
		if (tail)
		{
			tail->next = nullptr;
		}
		else
		{
			head = nullptr;
		}
		delete temp;
		size--;
	}

	size_t getSize() const
	{
		return size;
	}

	bool empty() const
	{
		return size == 0;
	}

	T &front()
	{
		if (!head)
			throw std::runtime_error("List is empty");
		return head->data;
	}

	T &back()
	{
		if (!tail)
			throw std::runtime_error("List is empty");
		return tail->data;
	}
};

class EvictionPolicy
{
	DoublyLinkedList<string> lru;
	map<string, Node<string> *> keyToNode;

public:
	EvictionPolicy()
	{
		this->lru = DoublyLinkedList<string>();
		keyToNode.clear();
	}

	void keyAccessed(string key)
	{
		if (keyToNode.find(key) != keyToNode.end())
		{
			lru.detachNode(key);
		}
		lru.pushFront(key);
		keyToNode[key] = lru.frontNode();
	}

	void evictKey()
	{
		if (!lru.empty())
		{
			string key = lru.front();
			keyToNode.erase(key);
			lru.popFront();
		}
	}
};

class Cache
{
private:
	Storage storage;
	EvictionPolicy evictionPolicy;

public:
	Cache(int capacity) : storage(capacity) {}

	void put(const string &key, const string &value)
	{
		try
		{
			storage.addData(key, value);
			evictionPolicy.keyAccessed(key);
		}
		catch (const StorageException &e)
		{
			string evictedKey = storage.storage.begin()->first; 
			storage.removeData(evictedKey);						
			storage.addData(key, value);						
			evictionPolicy.evictKey();							
			evictionPolicy.keyAccessed(key);					
		}
	}

	string get(const string &key)
	{
		try
		{
			string value = storage.getData(key);
			evictionPolicy.keyAccessed(key);
			return value;
		}
		catch (const StorageException &e)
		{
			return "";
		}
	}

	void remove(const string &key)
	{
		try
		{
			storage.removeData(key);
			evictionPolicy.evictKey();
		}
		catch (const StorageException &e)
		{
			// Key not found, do nothing
			throw e;
		}
	}

	int getCapacity() const
	{
		return storage.getCapacity();
	}

	void updateCapacity(int newCapacity)
	{
		storage.updateCapacity(newCapacity);
	}
};

int main()
{
	Cache cache(3);

	cache.put("1", "one");
	cache.put("2", "two");
	cache.put("3", "three");

	cout << "Get 1: " << cache.get("1") << endl;

	cache.put("4", "four");
	cout << "Get 1 after eviction: " << cache.get("1") << endl;
	cout << "Get 4: " << cache.get("4") << endl;

	try
	{
		cache.remove("2");
		cout << "Removed 2" << endl;
	}
	catch (const StorageException &e)
	{
		cout << "Error: " << e.what() << endl;
	}

	try
	{
		cache.updateCapacity(2);
		cout << "Updated capacity to 2" << endl;
	}
	catch (const StorageException &e)
	{
		cout << "Error updating capacity: " << e.what() << endl;
	}

	return 0;
}