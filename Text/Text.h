#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
#include "stack.h"

class TText;

class TTextLink;

struct TMem
{
	TTextLink* pFirst, * pLast, * pFree;
};

class TTextLink
{
	//TTextLink* pNext, * pDown;
	//char str[80];
public:
	TTextLink* pNext, * pDown;
	char str[80];
	bool flag;
	TTextLink(const char* s = NULL, TTextLink* pN = NULL, TTextLink* pD = NULL)
	{
		/*pNext = pN;
		pDown = pD;
		if (s)
		{
			strcpy_s(str, s);
		}
		else str[0] = '\0';*/
		if (s == NULL)
			str[0] = '\0';
		else
		{
			int i = 0;
			do
			{
				str[i] = s[i];
				i++;
			} while (s[i - 1] != '\0');
		}
		pNext = pN;
		pDown = pD;
	}
	~TTextLink()
	{}
	static TMem mem;
	static void InitMem(int size = 100);
	void* operator new(std::size_t n);
	void operator delete(void* p); 
	static void PrintFree();
	static void Clean(TText& t);
};

class TText
{
	//TTextLink* pFirst, *pCurr;
	//Stack<TTextLink*> st;
	//int level;
public:
	Stack<TTextLink*> st;
	int level;
	TTextLink* pFirst, * pCurr;

	void GoFirst()
	{
		pCurr = pFirst;
		if(!st.Empty())
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
		if (pCurr->pDown != NULL)
		{
			st.Push(pCurr);
			pCurr = pCurr->pDown;
		}
	}
	void GoPrevLink()
	{
		if (!st.Empty())
		{
			pCurr = st.Top();
	    	st.Pop();
	    }
	} 
	void InsNextLine(const char* s)
	{
		TTextLink* t;
		t = new TTextLink(s, pCurr->pNext,NULL);
		pCurr->pNext = t;
	}
	void InsNextSection(const char* s)
	{
		TTextLink* t;
		t= new TTextLink(s, NULL, pCurr->pNext);
		pCurr->pNext = t;
	}
	void InsDownSection(const char* s)
	{
		TTextLink* t;
		t = new TTextLink(s, pCurr->pDown,NULL);
		pCurr->pDown = t;
	}
	void InsDownLine(const char* s)
	{
		TTextLink* t;
		t = new TTextLink(s, pCurr->pDown,NULL);
		pCurr->pDown = t;
	}
	void DelNextLine()
	{
		if (pCurr->pNext)
		{
			TTextLink* t = pCurr->pNext;
			pCurr->pNext = t->pNext;
			TTextLink:: operator delete (t);
		}
	}
	void DelDownLine()
	{
		if (pCurr->pDown)
		{
			TTextLink* t = pCurr->pDown;
			pCurr->pDown = t->pNext;
			TTextLink:: operator delete (t);
		}
	}
	void Print()
	{
		level = 0;
		PrintRec(pFirst);
	}
	void PrintRec(TTextLink *t)
	{
		if (t != NULL)
		{
			for (int i = 0; i < level; i++)
			{
				std::cout << ' ';
			}
			std::cout << t->str << '\n';
			level++;
			PrintRec(t->pDown);
			level--;
			PrintRec(t->pNext);
		}
	}
	void Save(const char* fn)
	{
		std::ofstream ost(fn);
		SaveRec(pFirst, ost);
		ost.close();
	}
	void SaveRec(TTextLink* t, std::ofstream& ost)
	{
		if (t != NULL)
		{
			ost << t->str << std::endl;
			if (t->pDown != NULL)
			{
				ost << '{' << std::endl;
				SaveRec(t->pDown, ost);
				ost << '}' << std::endl;
			}
			if (t->pNext != NULL)
				SaveRec(t->pNext, ost);
		}
	}
	void Read(const char* fn)
	{
		std::ifstream ifs(fn);
		pFirst = ReadRec(ifs);
		ifs.close();
	}
	TTextLink* ReadRec(std::ifstream& ifs)
	{
		TTextLink* pF = NULL, *pC = NULL;
		char Buff[80];
		while (ifs.eof() == false)
		{
			ifs.getline(Buff, 80, '\n');
			if (Buff[0] == '}')
			{
				break;
			}
			else
				if (Buff[0] == '{')
					pC->pDown = ReadRec(ifs);
				else
				{
					//TTextLink* tmp = new TTextLink(Buff);
					if (pC == NULL)
					{
						TTextLink* tmp = (TTextLink*)TTextLink::operator new(1);
						strcpy_s(tmp->str, Buff);
						tmp->pDown = NULL;
						tmp->pNext = NULL;
						pF = pC = tmp;
					}
					else
					{
						TTextLink* tmp = (TTextLink*)TTextLink::operator new(1);
						strcpy_s(tmp->str, Buff);
						tmp->pDown = NULL;
						tmp->pNext = NULL;
						pC->pNext = tmp;
						pC = tmp;
					}
				}
		}
		return pF;
	}
	void Reset()
	{
		if (pFirst!=NULL)
		{
			st.Clear_Stack();
		}
			pCurr = pFirst;
			st.Push(pFirst);
			if (pFirst->pNext)
				st.Push(pFirst->pNext);
			if (pFirst->pDown)
				st.Push(pFirst->pDown);
	}
	void GoNext()
	{
		pCurr = st.Pop();
		if (pCurr != pFirst)
		{
			if (pCurr->pNext)
				st.Push(pCurr->pNext);
			if (pCurr->pDown)
				st.Push(pCurr->pDown);
		}
	}
	bool IsEnd()
	{
		return st.Empty();
	}
	TTextLink* GetCurr()
	{
		return pCurr;
	}

};



void* TTextLink::operator new(std::size_t n)
{
	TTextLink* pC = mem.pFree;
	if (mem.pFree->pNext != NULL)
	{
		mem.pFree = mem.pFree->pNext;
	}
	return pC;
}

void TTextLink::operator delete(void* p)
{
	TTextLink* pC = (TTextLink*)p;
	pC->pNext = mem.pFree;
	mem.pFree = pC;
}

void TTextLink::InitMem(int size)
{
	int Size = sizeof(TTextLink) * size;
	mem.pFirst = mem.pFree = (TTextLink*)malloc(Size);
	mem.pLast = mem.pFirst + (size - 1);
	TTextLink* tmp = mem.pFree; //first
	while (tmp != mem.pLast)
	{
		tmp->pNext = tmp + 1;
		tmp->flag = false; //true
		tmp->str[0] = '\0';
		tmp = tmp->pNext;
	}
	tmp->pNext = NULL;
	tmp->flag = true;
	tmp->str[0] = '\0';
}

void TTextLink::PrintFree()
{
	TTextLink* tmp = mem.pFree;
	bool flag = false;
	while (tmp != mem.pLast)
	{
		if (tmp->str[0] != '\0')
		{
			std::cout << tmp->str << ' ' << std::endl;
			flag = true;
		}
		tmp = tmp->pNext;
	}
	/*if (tmp->str[0] != '\0')
		std::cout << tmp->str << ' ';*/
	
	if (tmp->str[0] == '\0' && flag==false)
		std::cout << "?????" << std::endl;
	std::cout << std::endl;

}

void TTextLink::Clean(TText& t) 
{
	/*TTextLink* tmp = mem.pFree;
	while (tmp != NULL)
	{
		tmp->flag = 1;
		tmp = tmp->pNext;
	}
	for (t.Reset(); t.IsEnd(); t.GoNext())
	{
		t.pCurr->flag = 1;
	}
	tmp = mem.pFirst;
	while (tmp <= mem.pLast)
	{
		if (tmp->flag)
			tmp->flag = false;
		else
			delete tmp;
	}*/
	TTextLink* tmp = mem.pFree;
	while (tmp != mem.pLast)
	{
		tmp->flag = true; 
		tmp = tmp->pNext;
	} 
	tmp->flag = true; //false
	for (t.Reset(); !t.IsEnd(); t.GoNext())
	{
		t.GetCurr()->flag = true;  //false
	}
	tmp = mem.pFirst;
	while (tmp <= mem.pLast) //!=
	{
		if (tmp->flag)
			tmp->flag = false;
		else
		    delete(tmp);
		tmp++;
	}
	if (tmp->flag)
		tmp->flag = false;
	else
		delete(tmp);
}