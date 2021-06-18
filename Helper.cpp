#include "Library.h";

int Helper::StringLenght(char* str)
{//Finds length of char pointer
	
	int length = 0;
	for(int i = 0; str[i] != '\0'; i++)
	{
		length++;
	}
		return length;
}

char* Helper::GetStringFromBuffer(char* str)
{//Allocates only required memory for char pointer

	int length = StringLenght(str);
	char* strNew = 0;
	strNew = new char[length+1];
	int temp = 0;

	for(int i = 0; str[i]  != '\0'; i++)
	{
		strNew[temp] = str[i];
		temp++;
	}
	strNew[temp] = '\0';

	return strNew;
}

bool Helper::SearchString(char* strNew, char* searchStr)
{
	int length_1 = StringLenght(searchStr);
	int length_2 = StringLenght(strNew);

	if(length_1 != length_2)
	{
		return false;
	}
	else{
		for(int i = 0; i < length_2; i++)
		{
			if(strNew[i] != searchStr[i])
			{
				return false;
			}
		}
	}
	return true;
}