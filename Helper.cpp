#include "Library.h";
//This helper file is for additional common functions that will help us in other functions. 

int Helper::StringLenght(char* str){
	//This function finds length of char pointer and return the lenght as integer.
	int length = 0;
	for(int i = 0; str[i] != '\0'; i++){
		length++;
	}
	return length;
}

char* Helper::GetStringFromBuffer(char* str){
	//This function allocates only required memory for char pointer and return the pointer.
	int length = StringLenght(str);
	char* strNew = 0;
	strNew = new char[length+1];
	int temp = 0;
	for(int i = 0; str[i]  != '\0'; i++){
		strNew[temp] = str[i];
		temp++;
	}
	strNew[temp] = '\0';
	return strNew;
}

bool Helper::SearchString(char* strNew, char* searchStr){
	//This bool function returns true if a sub string is found in a larger string. 
	int length_1 = StringLenght(searchStr);
	int length_2 = StringLenght(strNew);
	if(length_1 != length_2){
		return false;
	}
	else{
		for(int i = 0; i < length_2; i++){
			if(strNew[i] != searchStr[i]){
				return false;
			}
		}
	}
	return true;
}
