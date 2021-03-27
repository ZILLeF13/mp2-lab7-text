#pragma once
#include <iostream>
#include<string.h>
#include "stack.h"
class TTextLink
{
	//TTextLink* pNext, * pDown;
	char str[80];
public:
	TTextLink* pNext, * pDown;
	TTextLink(char* s = NULL, TTextLink* pN = NULL, TTextLink* pD = NULL)
	{
		pNext = pN;
		pDown = pD;
		if (s)
		{
			strcpy(str,s);
		}
		else str[0] = '\0';
	}
	~TTextLink()
	{}

};

class TText
{
	//TTextLink* pFirst, *pCurr;
	Stack<TTextLink*> st;
public:
	TTextLink* pFirst, * pCurr;
	void GoFirst()
	{
		pCurr = pFirst;
		st.Clear_Stack();
	}
	void GoNextLink()
	{
		if (pCurr->pNext != NULL)
		{
			st.Push(pCurr);
			pCurr = pCurr->pNext;
		}
	}
	void GoDownLink()
	{

	}
	void GoPrevLink()
	{
		if (pFirst != pCurr)
			pCurr = st.Pop();
	}
	void InsNextLine(char* s)
	{
		TTextLink* t;
		t = new TTextLink(s, pCurr->pNext);
		pCurr->pNext;
	}
	void InsNextSection(char* s)
	{
		TTextLink* t;
		TTextLink(s, NULL, pCurr->pNext);
		pCurr->pNext = t;
	}
};
