#pragma once

template <class T>
class Node
{
public:
	Node<T>() 
	{
		data = nullptr;
	}
	~Node<T>()
	{
		if (data != nullptr)
			delete data;
	}
	T* data;
	Node* next = nullptr;
};

template <class T>
class LinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;

	void DeleteNextNode(Node<T>* node)
	{
		if (node->next != nullptr)
			DeleteNextNode(node->next);
		delete node;
	}
public:
	class Iterator
	{
	private:
		Node<T>* node;
		Node<T>* prevNode;

		friend class LinkedList;
	public:
		T* Data()
		{
			return (node->data);
		}

		void operator++()
		{
			prevNode = node;
			node = node->next;
		}

		bool operator!=(Iterator rhs)
		{
			return (this->node != rhs.node);
		}
	};

	int count;

	LinkedList() : count(0), head(nullptr) { }
	~LinkedList()
	{
		if (head != nullptr)
		{
			Node<T>* temp = head;
			DeleteNextNode(temp);
		}
	}

	Iterator Begin()
	{
		Iterator iter;
		iter.node = head;
		return iter;
	}

	Iterator End()
	{
		Iterator iter;
		iter.node = nullptr;
		iter.prevNode = tail;
		return iter;
	}

	T* Front()
	{
		return head->data;
	}

	T* Back()
	{
		return tail->data;
	}

	void PushBack(T* data)
	{
		if (head == nullptr)
		{
			head = new Node<T>;
			head->data = std::move(data);
			head->next = nullptr;
			tail = head;
		}
		else
		{
			Node<T>* node = new Node<T>;
			node->data = std::move(data);

			node->next = nullptr;
			tail->next = node;
			tail = node;
		}
		count++;
	}

	void Remove(Iterator* iter)
	{
		Node<T>* nodeToRemove = iter->node;
		Node<T>* prevNode = iter->prevNode;
		prevNode->next = nodeToRemove->next;
		iter->node = prevNode;
		count--;
		delete nodeToRemove;
	}

	T* At(unsigned int index)
	{
		if (index >= count)
		{
			printf("index larger than Linked List count");
			return nullptr;
		}
		Iterator iter = Begin();
		for (int i = 0; i < index; i++)
		{
			++iter;
		}
		return iter.Data();
	}
};