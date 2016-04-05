#pragma once

template<typename T> class Queue
{
private:
	struct Node
	{
		T* t = nullptr;
		Node* next = nullptr;

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

	T* Top()
	{
		if (nullptr == first) return nullptr;
		return first->t;
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
			last = newNode;
		}
		cnt++;
	}

	T* Pop()
	{
		if (nullptr == first || cnt <= 0)
		{
			return nullptr;
		}
		else
		{
			T* t = first->t;
			first = first->next;
			cnt--;
			return t;
		}
	}
}; //Queue
