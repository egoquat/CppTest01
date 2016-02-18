class Brackets
{
public:
	const static int TRUE = 1;
	const static int FALSE = 0;
	
	class Stack
	{
	private:
		struct Node
		{
			void* t;
			Node* pre;

			Node()
			{
				pre = nullptr;
			}
		};

		int cnt = 0;
		Node* last = nullptr;

	public:
		int IsEmpty()
		{
			return (cnt == 0)?TRUE:FALSE;
		}

		void push(void* t)
		{
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->t = t;
			if (nullptr == last)
			{
				last = newNode;
			}
			else
			{
				newNode->pre = last;
				last = newNode;
			}
			cnt++;
		}

		void* Pop()
		{
			if (nullptr == last)
			{
				return NULL;
			}
			else
			{
				cnt--;
				void* t = last->t;
				Node* del = last;
				last = last->pre;

				free(del->t);
				free(del);

				return t;
			}
		}
	};

	int IsBracket(char c)
	{
		if ('{' == c || '}' == c
			|| '(' == c || ')' == c
			|| '[' == c || ']' == c)
		{
			return TRUE;
		}
		
		return FALSE;
	}

	int IsCloseBracket(char c)
	{
		if ('}' == c || ')' == c || ']' == c)
		{
			return TRUE;
		}

		return FALSE;
	}

	int IsPair(char open, char close)
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
	}

	int solution(char *S)
	{		
		int L = strlen(S);
		if (L <= 1)
		{
			return FALSE;
		}

		int isValidate = TRUE;

		Stack brackets;
		for (int i = 0; i < L; ++i)
		{
			char c = S[i];
			if (TRUE == IsBracket(c))
			{
				if (TRUE == IsCloseBracket(c))
				{
					if (TRUE == brackets.IsEmpty())
					{
						isValidate = FALSE;
						break;
					}

					char o = *(char*)brackets.Pop();
					
					if (FALSE == IsPair(o, c))
					{
						isValidate = FALSE;
						break;
					}
				}
				else
				{
					brackets.push(&c);
				}
			}
		}

		return isValidate;
	}
};

