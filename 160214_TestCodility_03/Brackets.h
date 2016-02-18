#define CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )   // #include <new.h>등으로 operator new나 malloc을 
// Derived해서 정의 한 경우, 사용 할 수 없다.
#endif


#include <string>

using namespace std;

class Brackets
{
public:
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
	};

	bool IsBracket(char c)
	{
		if ('{' == c || '}' == c
			|| '(' == c || ')' == c
			|| '[' == c || ']' == c)
		{
			return true;
		}

		return false;
	}

	bool IsCloseBracket(char c)
	{
		if ('}' == c || ')' == c || ']' == c)
		{
			return true;
		}

		return false;
	}

	bool IsPair(char open, char close)
	{
		switch (close)
		{
		case ')':
		{
			return '(' == open;
		}
			break;
		case '}':
		{
			return '{' == open;
		}
			break;
		case ']':
		{
			return '[' == open;
		}
			break;
		}
		return false;
	}

	int solution(string& S)
	{
		int L = S.length();
		if (L < 0) { return false; }
		if (L == 0)	{ return true; }
		if (L == 1)	{ return false; }

		bool isValidate = true;

		Stack<char> brackets;
		for (int i = 0; i < L; ++i)
		{
			char c = S[i];
			if (true == IsBracket(c))
			{
				if (true == IsCloseBracket(c))
				{
					if (true == brackets.IsEmpty())
					{
						isValidate = false;
						break;
					}

					char o = *(char*)brackets.Pop();

					if (false == IsPair(o, c))
					{
						isValidate = false;
						break;
					}
				}
				else
				{
					brackets.Push(c);
				}
			}
		}

		if (brackets.Count() > 0) isValidate = false;

		brackets.Clear();

		return isValidate;
	}
};

