#pragma once
template <class T>
class Stack 
{
	int Size, MaxSize;
	T* mas;
public:
	Stack(int _MaxSize=10);
	Stack(const Stack<T>& m);
	~Stack();
	Stack<T>& operator =(const Stack<T>& m);
	int operator == (const Stack<T>& s);
	int operator != (const Stack<T>& s);
	bool Empty();
	bool Full();
	void Push(T a);
	void Clear_Stack() { Size = 0; }
	T Pop();
	T Top();
	int size() { return Size; }
};

template <class T>
Stack<T>::Stack(int _MaxSize)
{
	MaxSize = _MaxSize;
	mas = new T[MaxSize];
Size = 0;
}

template <class T>
Stack<T>::Stack(const Stack<T>& m)
{
	MaxSize = m.MaxSize;
	Size = m.Size;
	mas = new T[MaxSize];
	for (int i = 0; i < Size; i++)
	{
		mas[i] = m.mas[i];
	}
}

template<class T>
Stack<T>::~Stack()
{
	delete[] mas;
}

template <class T>
Stack<T>& Stack<T>:: operator =(const Stack<T>& m)
{
	Size = m.Size;
	if (MaxSize != m.MaxSize);
	{
		MaxSize = m.MaxSize;
		delete[] mas;
		mas = new T[MaxSize];
	}
	for (int i = 0; i < Size; i++)
	{
		mas[i] = m.mas[i];
	}
	return *this;
}

template <class T>
bool Stack<T> ::Empty()
{
	if (Size == 0)
	{
		return true;
	}
	return false;
}

template <class T>
bool Stack<T> ::Full()
{
	if (Size == MaxSize)
	{
		return true;
	}
	return false;
}

template <class T>
void Stack<T> ::Push(T a)
{
	if (Full() == true)
	{
		throw "Push";
	}
	mas[Size] = a;
	Size++;
}

template <class T>
T Stack<T> ::Pop()
{
	if (Empty() == true)
	{
		throw "Pop";
	}
	Size--;
	return mas[Size];
}

template <class T>
T Stack<T> ::Top()
{
	if (Empty() == true)
	{
		throw "Top";
	}
	return mas[Size - 1];
}

template <class T>
int Stack<T> :: operator ==(const Stack<T>& m)
{
	if (this != &m)
	{
		if ((MaxSize != m.MaxSize) || (Size != m.Size))
		{
			return -1;
		}
		for (int i = 0; i < Size; i++)
		{
			if (mas[i] != m.mas[i])
			{
				return -1;
			}
		}
	}
	return 1;
}

template <class T>
int Stack<T> :: operator !=(const Stack<T>& m)
{
	return !(*this == m);
}