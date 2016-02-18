#include <stdlib.h>
#include <string.h>

class Brackets
{
	const int DEFAULT = -1;

	const int TRUE = 1;
	const int FALSE = 0;

	const int CLOSED = -1;
	const int OPEN_S = 0;
	const int OPEN_M = 1;
	const int OPEN_L = 2;
	const int CLOSE_S = 3;
	const int CLOSE_M = 4;
	const int CLOSE_L = 5;

	int GettypeDoor(char c)
	{
		int returnValue = DEFAULT;
		switch (c)
		{
		case '(':
			returnValue = OPEN_S; break;
		case '{':
			returnValue = OPEN_M; break;
		case '[':
			returnValue = OPEN_L; break;
		case ')':
			returnValue = CLOSE_S; break;
		case '}':
			returnValue = CLOSE_M; break;
		case ']':
			returnValue = CLOSE_L; break;
		}
		return returnValue;
	}

	int IsOpenedAndLastest(int typeClose, int* D)
	{
		int typeOpen = typeClose - 3;

		int typeLastest = DEFAULT, pos = -1;
		for (int i = OPEN_S; i <= OPEN_L; i++)
		{
			if (CLOSED != D[i] && pos < D[i]) {
				typeLastest = i; pos = D[i];
			}
		}

		if (typeLastest != typeOpen || DEFAULT == typeLastest)
		{
			return FALSE;
		}

		return TRUE;
	}
	int IsTypeOpen(int typeD) { return (typeD == OPEN_S || typeD == OPEN_M || typeD == OPEN_L); }
	int IsTypeClose(int typeD) { return (typeD == CLOSE_S || typeD == CLOSE_M || typeD == CLOSE_L); }

	void SetOpen(int typeD, int pos, int* D) { D[typeD] = pos; }
	void SetClose(int typeD, int* D) { D[typeD] = CLOSED; D[typeD - 3] = CLOSED; }
	void SetOpenOrClose(int typeD, int pos, int* D)
	{
		if (TRUE == IsTypeOpen(typeD))
		{
			SetOpen(typeD, pos, D);
		}
		else
		{
			SetClose(typeD, D);
		}
	}

	int IsValidateD(int typeD, int* D)
	{
		return (FALSE == IsTypeClose(typeD) || TRUE == IsOpenedAndLastest(typeD, D));
	}

public:
	int solution(char *S)
	{
		if (strlen(S) == 0)
		{
			return TRUE;
		}

		int ReturnValue = TRUE;

		int* D = (int*)malloc(sizeof(int) * 6);
		for (int i = 0; i < 6; ++i)
		{
			D[i] = CLOSED;
		}

		char c = S[0];
		for (int i = 0; c != '\0'; ++i)
		{
			c = *(S++);
			int typeD = GettypeDoor(c);
			if (DEFAULT != typeD)
			{
				if (FALSE == IsValidateD(typeD, D))
				{
					//printf("FALSE == IsValidateD//typeD(%c/%d)", c, typeD);
					ReturnValue = FALSE;
					break;
				}

				SetOpenOrClose(typeD, i, D);
			}
		}

		free(D);

		return ReturnValue;
	}
};

