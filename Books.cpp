#include "Library.h"

Books::Books(){

	ID = 0;
	Name = 0;
	Genre = 0;
	Author = 0;
	availability = 0;
}

Books::~Books(){

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
	cout<<endl<<"ID: "<<ID<<"\nName: "<<Name<<"\nAuthor: "<<Author<<"\nGenre: "<<Genre<<"\nAvailability: "<<availability<<endl<<endl;
}

char* Books::GetIDBook(){
	return ID;
}

char* Books::GetAvailability(){
	return availability;
}

void Books::SetAvailability(char*& avail){
	availability = Helper::GetStringFromBuffer(avail);
}

void Books::NewBook(char* id_, char* name_, char* author_, char* genre_){

	ID = Helper::GetStringFromBuffer(id_);
	Name = Helper::GetStringFromBuffer(name_);
	Author = Helper::GetStringFromBuffer(author_);
	Genre = Helper::GetStringFromBuffer(genre_);
	availability = Helper::GetStringFromBuffer("available");
}

Books& Books::operator=(const Books& rhs){

	if(&rhs != this){

		ID = Helper::GetStringFromBuffer(rhs.ID);
		Name = Helper::GetStringFromBuffer(rhs.Name);
		Author = Helper::GetStringFromBuffer(rhs.Author);
		Genre = Helper::GetStringFromBuffer(rhs.Genre);
	}

	return *this;
}

void Books::SaveBooks(ofstream& Books_Output){
	Books_Output<<ID<<endl;
	Books_Output<<Name<<endl;
	Books_Output<<Author<<endl;
	Books_Output<<Genre<<endl;
	Books_Output<<availability<<endl;
}

void Books::EditBookName(char* temp){
	delete[] Name;
	Name = 0;
	Name=Helper::GetStringFromBuffer(temp);
}

void Books::EditBookID(char* temp){
	delete[] ID;
	ID = 0;
	ID=Helper::GetStringFromBuffer(temp);
}

void Books::EditBookAuthor(char* temp){
	delete[] Author;
	Author = 0;
	Author=Helper::GetStringFromBuffer(temp);
}

void Books::EditBookGenre(char* temp){
	delete[] Genre;
	Genre = 0;
	Genre=Helper::GetStringFromBuffer(temp);
}

void Books::ChangeAvailability(){
	if(Helper::SearchString(availability,"available")){
		availability = Helper::GetStringFromBuffer("unavailable");
	}
	else if(Helper::SearchString(availability,"unavailable")){
		availability = Helper::GetStringFromBuffer("available");
	}
		
}

char* Books::GetName(){
	return Name;
}