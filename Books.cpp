#include "Library.h"
//This is the cpp for the Books class

Books::Books(){
	//These are the varaibles used for attributes of Books
	ID = 0; //Book ID
	Name = 0; //Book Name
	Genre = 0; //Book Genre
	Author = 0; //Book Author
	availability = 0; //Book Availability 
}
Books::~Books(){
	//This is the destructor for the Books.
	if(ID){
		delete[] ID;
		ID = 0;
	}
	if(Name){
		delete[] Name;
		Name = 0;
	}
	if(Genre){
		delete[] Genre;
		Genre = 0;
	}
	if(Author){
		delete[] Author;
		Author = 0;
	}
}
void Books::InputData(ifstream& inputBooks){
	//This function inputs the data of the books from tyhe .txt files and stores it in the variables.
	char temp[50];
	inputBooks.getline(temp, 50);
	ID = Helper::GetStringFromBuffer(temp);

	inputBooks.getline(temp, 50);
	Name = Helper::GetStringFromBuffer(temp);

	inputBooks.getline(temp, 50);
	Author = Helper::GetStringFromBuffer(temp);

	inputBooks.getline(temp, 50);
	Genre = Helper::GetStringFromBuffer(temp);

	inputBooks.getline(temp, 50);
	availability = Helper::GetStringFromBuffer(temp);
}
void Books::Print(){
	//This function prints the attributes of books.
	cout<<endl<<"ID: "<<ID<<"\nName: "<<Name<<"\nAuthor: "<<Author<<"\nGenre: "<<Genre<<"\nAvailability: "<<availability<<endl<<endl;
}
char* Books::GetIDBook(){
	//This function returns the Book ID.
	return ID;
}
char* Books::GetAvailability(){
	//This function return the Book's availability
	return availability;
}
void Books::SetAvailability(char*& avail){
	//This function sets the book's avalibilty with the help oh helper function 
	availability = Helper::GetStringFromBuffer(avail);
}
void Books::NewBook(char* id_, char* name_, char* author_, char* genre_){
	//This function defines the attributes of Book variables.
	ID = Helper::GetStringFromBuffer(id_);
	Name = Helper::GetStringFromBuffer(name_);
	Author = Helper::GetStringFromBuffer(author_);
	Genre = Helper::GetStringFromBuffer(genre_);
	availability = Helper::GetStringFromBuffer("available");
}
Books& Books::operator=(const Books& rhs){
	//Operator overload function
	if(&rhs != this){
		ID = Helper::GetStringFromBuffer(rhs.ID);
		Name = Helper::GetStringFromBuffer(rhs.Name);
		Author = Helper::GetStringFromBuffer(rhs.Author);
		Genre = Helper::GetStringFromBuffer(rhs.Genre);
	}
	return *this;
}
void Books::SaveBooks(ofstream& Books_Output){
	//This function saves the bgook data in the txt file
	Books_Output<<ID<<endl;
	Books_Output<<Name<<endl;
	Books_Output<<Author<<endl;
	Books_Output<<Genre<<endl;
	Books_Output<<availability<<endl;
}
void Books::EditBookName(char* temp){
	//Sets theb Book's names
	delete[] Name;
	Name = 0;
	Name=Helper::GetStringFromBuffer(temp);
}
void Books::EditBookID(char* temp){
	//Sets the book's ID
	delete[] ID;
	ID = 0;
	ID=Helper::GetStringFromBuffer(temp);
}
void Books::EditBookAuthor(char* temp){
	//Sets the Book's Author
	delete[] Author;
	Author = 0;
	Author=Helper::GetStringFromBuffer(temp);
}
void Books::EditBookGenre(char* temp){
	//Sets the Book's Genre
	delete[] Genre;
	Genre = 0;
	Genre=Helper::GetStringFromBuffer(temp);
}
void Books::ChangeAvailability(){
	//This function checks the avalability of a book and updates it accordingley
	if(Helper::SearchString(availability,"available")){
		availability = Helper::GetStringFromBuffer("unavailable");
	}
	else if(Helper::SearchString(availability,"unavailable")){
		availability = Helper::GetStringFromBuffer("available");
	}	
}
char* Books::GetName(){
	//This function sets the Name of the book.
	return Name;
}
