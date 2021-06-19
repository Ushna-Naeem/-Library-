#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>

using namespace std;

//This header file defines the Helper class, the Books class, the Library class and the Member class plus their respective functions.
//The respective functioning of each function is defined in their .cpp files. 
class Helper{
	//This function contains extra functions which are needed in other functions of other classes
public:
	static int StringLenght(char*);
	static char* GetStringFromBuffer(char*);
	static bool SearchString(char*, char*);
};
class Books{
	//This class defines all of the attributes of the books in the library.
	//It defines the books ID, its name, genre, availability and the author's name.
	char* ID;
	char* Name;
	char* Genre;
	char* Author;
	char* availability;
public:
	Books();
	~Books();
	void InputData(ifstream&);
	void Print();
	void NewBook(char*,char*,char*,char*);
	Books& operator=(const Books&);
	char* GetIDBook();
	char* GetName();
	char* GetAvailability();
	void SetAvailability(char*&);
	void SaveBooks(ofstream&);
	void EditBookName(char*);
	void EditBookAuthor(char*);
	void EditBookID(char*);
	void EditBookGenre(char*);
	void ChangeAvailability();
};
class Member{
	//This class defines the attributes of the members who use the library
	//It defines their names, IDs, Passwords, issued books, their ids and name.
	char* ID;
	char* Name;
	char* password;
	int noOfIssuedBooks;
	Books** issuedBooks; //This calss has an association with the Book class
public:
	Member();
	~Member();
	void InputData(ifstream&);
	void ChangePassword();
	void Print();
	void LoadIssuedBooks(Books**&, int&);
	char* GetID();
	char* GetPass();
	void IssueBook(Books*&);
	void ReturnBook(Books*&);
	Member& operator=(const Member& rhs);
	void NewMember(char*, char*, char*);
	void SaveMembers(ofstream&);
	void ChangeName();
};
class Library{
	//This class defines the attributes of the librarian and give them the access to all of the data of the members and the books so they can be manipulated accordingly. 
	char* userID;
	char* password;
	Member** memberData; //This class has an association with the Member class
	Books** bookRecord; //This class has an association with the Book class.
	static int noOfBooks;
	static int noOfMembers;
public:
	Member* CurrentUser;
	Library();
	~Library();
	void LoadData();		
	void InputBookRecord();	
	void InputMemberRecord(); 
	void InputLibrarian();
	void ChangePassword();
	void ChangeUsername();
	void MemberLogin();
	bool librarianLogin();
	bool Permission(char*, Books*&);	
	void IssueBook();
	void ReturnBook();
	void NewMember();	
	void AddBook();		
	void RemoveBook();	
	void SaveData();
	void EditBook();
	void ViewBookList();
	void ViewMembers();
	void ChangeMemberInfo();
	void BookInfo();
	void MemberSearch();
	void MemberCurrentInfo();
	void RunLibrarian();
	void RunMember();
};
