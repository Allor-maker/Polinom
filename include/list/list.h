#pragma once
#include <iostream>
#include "polinom.h"

template <class T>
class List
{
public:
	class Iterator;
private:
	template <class T>

	class Node
	{
		friend class List<T>::Iterator;
		friend class List<T>;
		Node* next;
		T m;

	public:
		Node(T m, Node* next = nullptr) : m(m), next(next) {}
	};

	Node<T>* Head;

public:
	class Iterator
	{
		Node<T>* Head_it = nullptr;
		Node<T>* curr1;
	public:
		Iterator() :curr1(Head_it) {}
		Iterator(Node<T>* Head) : Head_it(Head) { curr1 = Head; }

		T& operator*()
		{
			return curr1->m;
		}
		Node<T>* operator->()
		{
			return curr1;
		}
		void set_curr(Node<T>* c)
		{
			curr1 = c;
		}
		Node<T>* Iterator::get_curr()
		{
			return curr1;
		}
		Iterator& operator++()
		{
			curr1 = curr1->next;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator cp = *this;
			curr1 = curr1->next;
			return cp;
		}
		Iterator operator+(int j) const
		{
			Iterator a(Head_it);
			a.curr1 = curr1;
			Node<T>* curr = curr1;
			while (j > 0)
			{
				a.curr1 = curr->next;
				curr = curr->next;
				j--;
			}
			return a;
		}
		bool operator==(const Iterator& it) const
		{
			if (Head_it != it.Head_it) throw 0;
			return (curr1 == it.curr1);
		}
		bool operator!=(const Iterator& it) const
		{
			return (curr1 != it.curr1);
		}
	};
public:

	Iterator begin() const
	{
		Iterator it(Head);
		it.set_curr(Head->next);
		return it;
	}
	Iterator end() const
	{
		return Iterator(Head);
	}
	List(int n = 0)
	{
		if (n < 0) throw 0;

		Head = new Node<T>(T());
		Head->next = Head;
		if (n == 0) return;
		Node<T>* curr = Head;
		while (n > 0)
		{
			Node<T>* temp = new Node<T>(T(), Head);
			curr->next = temp;
			curr = curr->next;
			n--;
		}
	}
	~List()
	{
		Node<T>* curr = Head->next;
		while (curr != Head)
		{
			Node<T>* tmp = curr;
			curr = curr->next;
			delete tmp;
		}
		delete Head;
		Head = nullptr;
	}
	List(const List& other)
	{
		if (!other.Head)
		{
			Head = nullptr;
			return;
		}

		Head = new Node<T>(T());

		Node<T>* curr = other.Head->next;
		Node<T>* curr2 = Head;
		while (curr != other.Head)
		{
			Node<T>* new_curr = new Node<T>(curr->m);
			curr2->next = new_curr;
			curr2 = curr2->next;
			curr = curr->next;
		}
		curr2->next = Head;

	}

	List& operator=(const List& other)
	{
		if (this == &other) return *this;

		clear();

		Head = new Node<T>(T());
		Node<T>* curr = other.Head->next;
		Node<T>* curr2 = Head;
		while (curr != other.Head)
		{
			Node<T>* new_curr = new Node<T>(curr->m);
			curr2->next = new_curr;
			curr2 = curr2->next;
			curr = curr->next;
		}
		curr2->next = Head;
		return *this;
	}
	bool operator==(const List& other) const noexcept
	{
		if (size() != other.size()) return false;

		Node<T>* curr1 = Head->next;
		Node<T>* curr2 = other.Head->next;
		while (curr1 != Head)
		{
			if (curr1->m != curr2->m) return false;
			curr1 = curr1->next;
			curr2 = curr2->next;
		}
		return true;
	}

	void clear()
	{
		Node<T>* curr = Head->next;
		while (curr != Head)
		{
			Node<T>* tmp = curr;
			curr = curr->next;
			delete tmp;
		}
		Head->next = Head;
	}
	bool operator!=(const List& other) const noexcept
	{
		return !(*this == other);
	}
	size_t size() const
	{
		size_t sz = 0;
		Node<T>* curr = Head->next;
		while (curr != Head)
		{
			sz++;
			curr = curr->next;
		}
		return sz;
	}
	List(List&& other)
	{
		this->Head = other.Head;
		other.Head = nullptr;
	}
	Monom operator[](int i) const
	{
		if (i < 0 || i > size())
		{
			throw 0;
		}

		Node<T>* curr = Head->next;
		int count = 0;
		while (curr != Head)
		{
			if (count == i)
				return curr->m;
			curr = curr->next;
			count++;
		}
		throw 0;
	}
	T operator[](Iterator it) const
	{
		Node<T>* curr = Head->next;
		Iterator it2 = begin();
		while (curr != Head)
		{
			if (it2 == it)
				return curr->m;
			curr = curr->next;
			it2++;
		}
		throw 0;
	}
	Node<T>* insert_after(const T& m, Node<T>* prev)
	{
		if (prev == nullptr) throw 0;

		Node<T>* tmp = new Node<T>(m, prev->next);
		prev->next = tmp;
		return tmp;
	}
	Node<T>* insert_front(const T& m)
	{
		return(Head->next = new Node<T>(m, Head->next));
	}
	void erase_after(Node<T>* prev)
	{
		if (prev->next == Head) throw 0;
		Node<T>* tmp = prev->next;
		prev->next = prev->next->next;
		delete tmp;
	}
	void erase_front()
	{
		if (Head->next == Head)
			throw 0;
		Node<T>* tmp = Head->next;
		Head->next = Head->next->next;
		delete tmp;
	}
	Iterator find(const T& m)
	{
		Node<T>* curr = Head->next;
		while (curr != Head)
		{
			if (curr->m == m)
				return Iterator(curr);
			curr = curr->next;
		}
		return Head;
	}
	Node<T>* merge_sort(Node<T>* start, Node<T>* end)
	{
		if (start->next == end) return start;

		Node<T>* mid = get_mid(start, end);
		Node<T>* next_mid = mid->next;

		Node<T>* left = merge_sort(start, mid->next);

		Node<T>* right = merge_sort(next_mid, end);

		mid = get_mid(left, end);
		return merge(left, right, mid->next, end);
	}

	Node<T>* get_mid(Node<T>* start, Node<T>* end)
	{
		if (start->next->next == end) return start;

		Node<T>* slow = start;
		Node<T>* fast = start;

		while (fast->next != end && fast->next->next != end)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	Node<T>* merge(Node<T>* left, Node<T>* right, Node<T>* end1, Node<T>* end2)
	{
		if (left == end1)
		{
			Node<T>* curr = right;
			while (curr->next != end2)
			{
				curr = curr->next;
			}
			curr->next = end1;
			return right;
		}
		if (right == end2)
		{
			Node<T>* curr = left;
			while (curr->next != end1)
			{
				curr = curr->next;
			}
			curr->next = end2;

			return left;
		}
		if (left->m.get_value() <= right->m.get_value())
		{
			left->next = merge(left->next, right, end1, end2);
			return left;
		}
		else
		{
			right->next = merge(left, right->next, end1, end2);
			return right;
		}
	}
	void sort()
	{
		Head->next = merge_sort(Head->next, Head);
	}
	void del_similar()
	{
		Node<T>* curr = Head->next;
		while (curr->next != Head)
		{
			if (curr->m.get_value() == curr->next->m.get_value())
			{
				curr->m.set_k(curr->m.get_k() + curr->next->m.get_k());
				Node<T>* tmp = curr->next;
				curr->next = tmp->next;
				delete tmp;
			}
			curr = curr->next;
		}
	}
	friend std::ostream& operator<<(std::ostream& ostr, const List& m)
	{

		for (List::Iterator it = m.begin(); it != m.end(); it++)
		{
			ostr << "k = " << (*it).get_k() << " ";
			ostr << "pow = " << (*it).get_value() << std::endl;
		}
		return ostr;
	}
};
