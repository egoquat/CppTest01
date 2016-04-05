#pragma once

template<typename T> class LinkedList
{
private:
	struct Node
	{
		T* t = nullptr;
		Node* next = nullptr;
		Node* previous = nullptr;

		void Init(T t_)
		{
			next = nullptr;
			t = new T();
			*t = t_;
		}

		void Clear()
		{
			if (nullptr != t)
			{
				delete t;
			}
		}
	};

	int cnt = 0;
	Node* first = nullptr;
	Node* last = nullptr;

private:
	Node* ClearNode()
	{
		if (nullptr == first) return nullptr;

		Node* del = first;
		first = first->next;

		del->Clear();
		delete del;
		del = nullptr;
		return first;
	}

public:
	int Count()
	{
		return cnt;
	}

	bool IsEmpty()
	{
		return (cnt == 0) ? true : false;
	}

	void Clear()
	{
		while (nullptr != ClearNode()){}

		cnt = 0;
	}

	T* First()
	{
		if (0 == cnt) return nullptr;
		return first->t;
	}

	T* Last()
	{
		if (0 == cnt) return nullptr;
		return last->t;
	}

	void SetCurrent(int seq)
	{

	}

	void Push(T t)
	{
		Node* newNode = new Node();
		newNode->Init(t);
		if (nullptr == last)
		{
			first = last = newNode;
		}
		else
		{
			last->next = newNode;
			newNode->previous = last;
			last = newNode;
		}
		cnt++;
	}
}; //Queue
