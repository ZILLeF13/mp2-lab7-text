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
	return 0;
}