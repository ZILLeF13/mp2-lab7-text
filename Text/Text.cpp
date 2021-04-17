#include <iostream>
#include "Text.h"
#include <fstream>
#include <string.h>

TMem TTextLink::mem;

int main()
{
	setlocale(LC_ALL, "Russian");
	TTextLink::InitMem(100);
	TText text;
    text.Read("text.txt");
	text.Print();
	std::cout << std::endl;
	std::cout << std::endl << "Печать мусора : "<<std::endl;
	TTextLink::Clean(text);
	TTextLink::PrintFree();
	std::cout << std::endl;
	for (text.Reset(); !text.IsEnd(); text.GoNext())
	{
		if (!strcmp(text.GetCurr()->str , "Title_1"))
		{
			text.DelNextLine();
			break;
		}
	}
	std::cout << "Удаление Title_2 :" << std::endl;
	text.Print();
	std::cout << std::endl << "Печать мусора : " << std::endl;
	TTextLink::Clean(text);
	TTextLink::PrintFree();
	std::cout << std::endl;
	std::cout << "Добавление Title_2_new и Line_3.2_new" << std::endl;
	for (text.Reset(); !text.IsEnd(); text.GoNext())
	{
		if (!strcmp(text.GetCurr()->str, "Title_1"))
		{
			text.InsNextLine("Title_2_new");
		}
		if (!strcmp(text.GetCurr()->str, "Line_3.1"))
		{
			text.InsNextLine("Line_3.2_new");
			break;
		}
	}
	text.Print();
	std::cout << std::endl;

	while (true)
	{
		std::cout << "Введите номер строки, на которую хотите перейти :";
		int i = 0, n;
		std::cin >> n;
		for (text.Reset(); !text.IsEnd(); text.GoNext(), i++)
		{
			if (n == i)
			{
				std::cout << text.GetCurr()->str << std::endl;
				std::cout << "Выберите действие :" << std::endl;
				std::cout << "1. InsNextLine." << std::endl;
				std::cout << "2. InsNextSection" << std::endl;
				std::cout << "3. InsDownLine" << std::endl;
				std::cout << "4. InsDownSection." << std::endl;
				std::cout << "5. DelNextLine" << std::endl;
				int n1;
				std::cin >> n1;
				if (n1 == 1)
				text.InsNextLine("NEW_Line");
				if (n1 == 4)
					text.InsDownSection("NEW_Title");
				if (n1 == 3)
					text.InsDownLine("NEW_Line");
				if (n1 == 2)
					text.InsNextSection("NEW_Title");
				if (n1 == 5)
				{
					text.DelDownLine();
					i++;//text.GoNext();
					TTextLink::Clean(text);
					TTextLink::PrintFree();
				}
				text.Print();
			}
		}
		std::cout << "1. Продолжить" << std::endl;
		std::cout << "2. Выход" << std::endl;
		std::cin >> n;
		if (n == 2)
			return 0;
	}
	return 0;
}