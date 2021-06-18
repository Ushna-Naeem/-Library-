#include "Library.h"

Member::Member(){

	ID = 0;
	Name = 0;
	password = 0;
	noOfIssuedBooks = 0;
	issuedBooks = 0;
}

Member::~Member(){

	if(ID){
		delete[] ID;
		ID = 0;
	}
	if(Name){
		delete[] Name;
		Name = 0;
	}
	if(password){
		delete[] password;
		password = 0;
	}
}

void Member::InputData(ifstream& inputMembers){

	char temp[50];

	inputMembers.ignore();

	inputMembers.getline(temp, 50);
	ID = Helper::GetStringFromBuffer(temp);

	inputMembers.getline(temp, 50);
	password = Helper::GetStringFromBuffer(temp);

	inputMembers.getline(temp, 50);
	Name = Helper::GetStringFromBuffer(temp);
	
 }

void Member::LoadIssuedBooks(Books**& _issuedBooks, int& size){

	noOfIssuedBooks = size;
	issuedBooks = new Books*[noOfIssuedBooks];
	for(int i = 0; i < noOfIssuedBooks; i++){
		issuedBooks[i] = _issuedBooks[i];
	}
}

void Member::IssueBook(Books* &address){
	Books** temp = new Books*[noOfIssuedBooks];
	for(int i = 0; i < noOfIssuedBooks; i++)
		temp[i] = issuedBooks[i];
	noOfIssuedBooks++;
	issuedBooks = new Books*[noOfIssuedBooks];
	for(int i = 0; i < noOfIssuedBooks-1; i++)
		issuedBooks[i] = temp[i];
	issuedBooks[noOfIssuedBooks-1] = new Books;
	issuedBooks[noOfIssuedBooks-1] = address;
}

void Member::ReturnBook(Books* &address){
	
	int index = 0;
	Books** temp = new Books*[noOfIssuedBooks];
	for(int i = 0; i < noOfIssuedBooks;i++){
		if(issuedBooks[i] == address){
			index = i;
		}
		temp[i] = issuedBooks[i];
	}
	noOfIssuedBooks--;
	issuedBooks = new Books*[noOfIssuedBooks];
	for(int i = 0, j=0; i < noOfIssuedBooks+1; i++){
		if(i == index){
			continue;
		}
		issuedBooks[j] = temp[i];
		j++;
	}
}

char* Member::GetID(){
	return ID;
}

char* Member::GetPass(){
	return password;
}

Member& Member::operator=(const Member& rhs){

	if(&rhs != this){

		ID = Helper::GetStringFromBuffer(rhs.ID);
		Name = Helper::GetStringFromBuffer(rhs.Name);
		password = Helper::GetStringFromBuffer(rhs.password);
		noOfIssuedBooks = rhs.noOfIssuedBooks;
		issuedBooks = new Books*[noOfIssuedBooks];
		for(int i = 0; i < noOfIssuedBooks; i++){
			issuedBooks[i] = rhs.issuedBooks[i];
		}
	}

	return *this;
}

void Member::NewMember(char* name_, char* Id_, char* pass_){
	Name = Helper::GetStringFromBuffer(name_);
	ID = Helper::GetStringFromBuffer(Id_);
	password = Helper::GetStringFromBuffer(pass_);
	noOfIssuedBooks = 0;
	issuedBooks = 0;
}

void Member::SaveMembers(ofstream& Members_Output){
	Members_Output<<ID<<endl;
	Members_Output<<password<<endl;
	Members_Output<<Name<<endl;
	Members_Output<<noOfIssuedBooks<<" ";
	for(int i = 0; i < noOfIssuedBooks; i++){
		char* bookID = issuedBooks[i] -> GetIDBook();
		if(i < noOfIssuedBooks-1)
			Members_Output<<bookID<<" ";
		else
			Members_Output<<bookID;
	}
	Members_Output<<endl;

}

void Member::Print(){
	cout<<endl<<endl<<"ID: "<<ID<<"\tName: "<<Name<<"\nBooks Issued:\n";
	if(noOfIssuedBooks == 0)
		cout<<"None"<<endl<<endl;
	else{
		for(int i = 0; i < noOfIssuedBooks; i++){
			char* name_ = issuedBooks[i] -> GetName();
			if(i<noOfIssuedBooks-1)
				cout<<i+1<<") "<<name_<<"\n";
			else
				cout<<i+1<<") "<<name_;
		}
		cout<<endl;
		cout<<"------------------------------\n";
	}
}

void Member::ChangePassword(){
	bool check = false;
	while(check != true){
		cout<<"Enter current password: ";
		char temp[20];
		cin.getline(temp,20);
		char* currentPass = Helper::GetStringFromBuffer(temp);
		if(!Helper::SearchString(currentPass, password)){
			cout<<"Incorrect Current Password!!"<<endl;
			check = false;
		}
		else{
			check = true;
			bool check2 = false;
			while(check2 != true){
				cout<<"Enter New Password (Minimum of 8 characters): ";
				char temp2[20];
				cin.getline(temp2,20);
				char* newPass = Helper::GetStringFromBuffer(temp2);
				if(Helper::StringLenght(newPass) < 8){
					cout<<"Invalid Password!!"<<endl;
					check2 = false;
				}
				else{
					check2 = true;
					if(Helper::SearchString(newPass,password)){
						cout<<"Enter a Different Password!!"<<endl;
						check2 = false;
					}
					else{
						check2 = true;
						password = Helper::GetStringFromBuffer(newPass);
						break;
					}
				}
			}
		}
	}
}

void Member::ChangeName(){
	char newName[25];
	cout<<"Enter New Name: ";
	cin.getline(newName,25);
	Name = Helper::GetStringFromBuffer(newName);
}
