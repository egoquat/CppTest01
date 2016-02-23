#pragma once

template<typename T> class Stack
{
private:
	struct Node
	{
		T* t = nullptr;
		Node* pre = nullptr;

		void Init(T t_)
		{
			pre = nullptr;
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
	Node* last = nullptr;
	Node* current = nullptr;

private:
	Node* ClearNode()
	{
		if (nullptr == last) return nullptr;

		Node* del = last;
		last = last->pre;

		del->Clear();
		delete del;
		del = nullptr;
		return last;
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
		if (nullptr == current) return nullptr;
		return current->t;
	}

	void Push(T t)
	{
		Node* newNode = new Node();
		newNode->Init(t);
		if (nullptr == current)
		{
			last = current = newNode;
		}
		else
		{
			newNode->pre = current;
			last = current = newNode;
		}
		cnt++;
	}

	T* Pop()
	{
		if (nullptr == current || cnt <= 0)
		{
			return nullptr;
		}
		else
		{
			T* t = current->t;
			current = current->pre;
			cnt--;
			return t;
		}
	}
}; //Stack
