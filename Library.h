#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<conio.h>

using namespace std;

class Books;

class Helper{

public:

	static int StringLenght(char*);
	static char* GetStringFromBuffer(char*);
	static bool SearchString(char*, char*);
};

class Member{

	char* ID;
	char* Name;
	char* password;
	int noOfIssuedBooks;
	Books** issuedBooks;

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

class Books{

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

class Library{
	char* userID;
	char* password;
	Member** memberData;
	Books** bookRecord;
	static int noOfBooks;
	static int noOfMembers;
	
public:
	Member* CurrentUser;
	Library();
	~Library();
	void LoadData();		//To Load library data includng record of books and members
	void InputBookRecord();	//Input Books' data from file
	void InputMemberRecord(); //Input Members' data from fie
	void InputLibrarian();
	void ChangePassword();
	void ChangeUsername();
	void MemberLogin();
	void librarianLogin();
	bool Permission(char*, Books*&);	//Availabiliy of any book
	void IssueBook();
	void ReturnBook();
	void NewMember();	//Addition of new member
	void AddBook();		//Addition of new book
	void RemoveBook();	//Removal
	void SaveData();
	void EditBook();
	void ViewBookList();
	void ViewMembers();
	void ChangeMemberInfo();
	void BookInfo();
	void MemberSearch();
	void MemberCurrentInfo();
};