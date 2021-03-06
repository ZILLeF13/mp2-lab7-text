#pragma once

class TTextLink
{
	TTextLink* pNext, * pDown;
	char str[80];
public:
	TTextLink(char* s = NULL, TTextLink* pN = NULL, TTextLink* pD = NULL)
	{
		pNext = pN;
		pDown = pD;
		if (s)
		{
			str.cpy(str, s);
		}
		else str[0] = '\0';
	}
	~TTextLink()
	{}

};

class TText
{
	TTextLink* pFirst, *pCurr;
	TStack<TTextLink*> st;
public:
	void GoFirst()
	{
		pCurr = pFirst;
		st.ClearStack();
	}
	void GoNextLink()
	{
		if (pCurr->pNext != NULL)
		{
			st.Push(pCurr);
			pCurr = pCurr->pNext;
		}
	}
};
