#include "Library.h"

int Library::noOfBooks = 0;
int Library::noOfMembers = 0;

Library::Library(){

	userID = 0;
	password = 0;
	memberData = 0;
	bookRecord = 0;
	CurrentUser = 0;
}

Library::~Library(){

	if(userID){
		delete[] userID;
		userID = 0;
	}
	if(password){
		delete[] password;
		password = 0;
	}
	if(memberData){
		for(int i=0; i< noOfMembers; i++){
			memberData[i]=0;
		}
		delete[]memberData;
		memberData=0;
	}
	if(bookRecord){
		for(int i=0; i< noOfBooks; i++){
			bookRecord[i]=0;
		}
		delete[] bookRecord;
		bookRecord=0;
	}
}

void Library::LoadData(){

	InputLibrarian();
	InputBookRecord();
	InputMemberRecord();
}

void Library::InputLibrarian(){

	ifstream inputlibrarian_("Librarian.txt");
	char temp[20];
	inputlibrarian_.getline(temp,20);
	userID = Helper::GetStringFromBuffer(temp);
	inputlibrarian_.getline(temp,20);
	password = Helper::GetStringFromBuffer(temp);
}

void Library::InputBookRecord(){

	ifstream inputBooks("Books.txt");
	inputBooks>>noOfBooks;
	inputBooks.ignore();
	bookRecord = new Books*[noOfBooks];

	for(int i = 0; i < noOfBooks; i++){
		bookRecord[i] = new Books;
		bookRecord[i] -> InputData(inputBooks);		
	}

}

void Library::MemberSearch(){
	bool check=true;
	while(1){
		check=true;
		cout<<"Enter ID of the Member: ";
		char temp[10];
		cin.getline(temp,10);
		system("CLS");
		for(int i=0; i< noOfMembers; i++){
			char* id = memberData[i] -> GetID();
			if(Helper::SearchString(id,temp)){
				memberData[i] -> Print();
				cout<<"1) Search a Different Member\n2) Return to Menu\n\n";
				switch (getch()){
					case '1':
						system("CLS");
						check=false;
						break;
					case '2':
						system("CLS");
						return;
					default:
						system("CLS");
						cout<<"Invalid input. Enter again." <<endl<<endl;
						break;
				}
				system("CLS");
			}
		}
		if(check==true){
			cout<<"No Result Found\n"<<endl;
			cout<<"1) Try Again\n2) Return to menu\n";
			switch (getch()){
				case '1':
					system("CLS");
					break;
				case '2':
					system("CLS");
					return;
				default:
					system("CLS");
					cout<<"Invalid input. Enter again." <<endl<<endl;
					break;
			}
		}
	}
}

void Library::InputMemberRecord() {

	ifstream inputMembers("Members.txt");
	inputMembers>>noOfMembers;

	memberData = new Member*[noOfMembers];

	for(int i = 0; i < noOfMembers; i++){
		memberData[i] = new Member;
		memberData[i] -> InputData(inputMembers);	
		int numOfIssuedBooks = 0;
		inputMembers>>numOfIssuedBooks;
		Books** addresses = new Books*[numOfIssuedBooks];
		int index = 0;
		for(int j = 0; j < numOfIssuedBooks; j++){
			char temp[10];
			inputMembers>>temp;
			for(int k = 0; k < noOfBooks; k++){
				char* id = bookRecord[k]->GetIDBook();
				if(Helper::SearchString(temp, id)){
					addresses[index] = bookRecord[k];
					index++;
				}
			}
		}
		memberData[i] -> LoadIssuedBooks(addresses, numOfIssuedBooks);
	}

}

void Library::ChangePassword(){
	char temp[20];
	bool check = false;
	while(check != true){
		cout<<"Enter current password: ";
		cin.getline(temp,20);
		char* currentPass = Helper::GetStringFromBuffer(temp);
		if(!Helper::SearchString(currentPass, password)){
			cout<<"Incorrect Current Password!!\n"<<endl;
			check = false;
		}
		else{
			check = true;
			bool check2 = false;
			while(check2 != true){
				system("CLS");
				cout<<"Enter New Password (Minimum of 8 characters): ";
				char temp2[20];
				cin.getline(temp2,20);
				char* newPass = Helper::GetStringFromBuffer(temp2);
				if(Helper::StringLenght(newPass) < 8){
					cout<<"Invalid Password!!\n"<<endl;
					check2 = false;
				}
				else{
					check2 = true;
					if(Helper::SearchString(newPass,password)){
						cout<<"Enter a Different Password!!\n"<<endl;
						check2 = false;
					}
					else{
						check2 = true;
						password = Helper::GetStringFromBuffer(newPass);
						cout<<"Password was changed.\n\nPress 0 to return to Menu: ";
						switch (getch()){
							case '0':
								system("CLS");
								return;
							default:
								system("CLS");
								cout<<"Invalid input. Enter again." <<endl<<endl;
								break;
						}
						break;
					}
				}
			}
		}
	}

}

void Library::ChangeUsername(){
	bool check=true;
	cout<<"Enter New Username: ";
	char name_[30];
	cin.getline(name_,30);
	while(1){
		if(Helper::SearchString(name_,userID)){
			cout<<"Enter a different username(Can't use the previous one): ";
			cin.getline(name_,30);
		}
		else
			break;
	}
	while(1){
		system("CLS");
		cout<<"Enter your password to confirm the change: ";
		char tempPass[20];
		cin.getline(tempPass,20);
		if(Helper::SearchString(tempPass,password)){
			userID = Helper::GetStringFromBuffer(name_);
			cout<<"Username has been changed...Press 0 to return to Menu: ";
			switch (getch()){
				case '0':
					system("CLS");
					return;
				default:
					system("CLS");
					cout<<"Invalid input. Enter again." <<endl<<endl;
					break;
			}
			system("CLS");
			return;
		}	
		else{
			system("CLS");
			cout<<"Incorrect Password!!\n\n1) Try Again\n2) Return to Menu\n\n";
			switch (getch()){
				case '1':
					system("CLS");
					break;
				case '2':
					return;
				default:
					system("CLS");
					cout<<"Invalid input. Enter again." <<endl<<endl;
					break;
			}
			
		}
	}
}

void Library::AddBook(){
	char name[30];
	char id[10];
	char author[30];
	char genre[30];
	bool check = false;

	while(check != true){
		cout<<"Enter ID for the Book: ";
		cin.getline(id,10);
		for(int i = 0; i < noOfBooks; i++){
			char* tempId = bookRecord[i] -> GetIDBook();
			if(Helper::SearchString(tempId,id)){
				cout<<"ID already exists!!"<<endl;
				check = false;
				break;
			}else{
				check = true;
			}
		}
	}
	cout<<"Title of the Book: ";
	cin.getline(name,30);
	cout<<"Author: ";
	cin.getline(author,30);
	cout<<"Genre: ";
	cin.getline(genre,30);

	Books** temp = new Books*[noOfBooks];
	for(int i = 0; i < noOfBooks; i++){
		temp[i] = bookRecord[i];
	}
	delete[] bookRecord;
	noOfBooks++;
	bookRecord = new Books*[noOfBooks];
	for(int i = 0; i < noOfBooks-1; i++){
		bookRecord[i] = temp[i];
	}
	bookRecord[noOfBooks-1] = new Books;
	bookRecord[noOfBooks-1] -> NewBook(id,name,author,genre);
	system("CLS");
	cout<<"Book was Added in the system.\n\nPress 0 to return to Menu: ";
	switch (getch()){
		case '0':
			system("CLS");
			return;
		default:
			system("CLS");
			cout<<"Invalid input. Enter again." <<endl<<endl;
			break;
	}
	system("CLS");

}

void Library::RemoveBook(){
	bool check_=true;
	bool check2=true;
	while (true){
		check_=true;
		check2=true;
		cout<<"Enter ID of Book you want to remove: ";
		char id[10];
		cin.getline(id,10);
		for(int i = 0; i < noOfBooks; i++){
			char* idList = bookRecord[i] -> GetIDBook();
			if(Helper::SearchString(id, idList)){
				check_=false;
				char check[13] = "unavailable";
				char* availability_ = bookRecord[i] -> GetAvailability();
				if(Helper::SearchString(availability_, check)){
					system("CLS");
					cout<<"Book cannot be Removed at the moment!\n";
					cout<<"\n1) Try Again\n2) Return to Menu\n";
					switch (getch()){
						case '1':
							check2=false;
							system("CLS");
							break;
						case '2':
							return;
						default:
							system("CLS");
							cout<<"Invalid input. Enter again." <<endl<<endl;
							break;
					}
				}
			
				if(check2==true){
					Books** tempBooks = new Books*[noOfBooks];
					for(int j = 0; j < noOfBooks; j++){
						tempBooks[j] = bookRecord[j];
					}
					noOfBooks--;
					bookRecord = new Books*[noOfBooks];
					for(int j = 0,k=0; j <= noOfBooks; j++){
						char* idList_ = tempBooks[j] -> GetIDBook();
						if(Helper::SearchString(idList_, id))
							continue;
						else{
							bookRecord[k] = tempBooks[j];
							k++;
						}
					}
					cout<<"Book was removed from system.\n\nPress 0 to return to Menu: ";
					switch (getch()){
						case '0':
							system("CLS");
							return;
						default:
							system("CLS");
							cout<<"Invalid input. Enter again." <<endl<<endl;
							break;
					}
					system("CLS");
				}
			}
		}
		if(check_==true){
			system("CLS");
			cout<<"No Book with this ID exists\n"<<endl;
			cout<<"\n1) Try Again\n2) Return to Menu\n";
			switch (getch()){
				case '1':
					system("CLS");
					break;
				case '2':
					return;
				default:
					system("CLS");
					cout<<"Invalid input. Enter again." <<endl<<endl;
					break;
			}
			system("CLS");
		}
	}
}

bool Library::Permission(char* id_, Books*& newBook){

	char check[10] = "available";
	for(int i = 0; i < noOfBooks; i++){
		char* idOfBook = bookRecord[i] -> GetIDBook();
		if(Helper::SearchString(id_, idOfBook)){
			char* availability_ = bookRecord[i] -> GetAvailability();
			if(Helper::SearchString(availability_, check)){
				newBook = bookRecord[i];
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

void Library::MemberLogin(){
	system("CLS");
	while(1){
		cout<<"Enter your ID: ";
		char id[10];
		cin.getline(id,10);
		bool check = false;
		for(int i = 0; i < noOfMembers; i++){
			char* Id_ = memberData[i] -> GetID();
			if(Helper::SearchString(id,Id_)){
				CurrentUser = memberData[i];
				while(check == false){
					cout<<"Enter your password: ";
					char password[50];
					cin.getline(password, 50);
					char* pass_ = CurrentUser -> GetPass();
					if(Helper::SearchString(pass_,password)){
						system("CLS");
						cout<<"Login Successful!!"<<endl;
						check = true;
						return;
					}
					else{
						system("CLS");
						cout<<"Incorrect Password!! Try Again"<<endl;
						check = false;
					}
				}
			}
		}
		cout<<"Invalid ID!!\n"<<endl;
	}

	return;
}

void Library::IssueBook(){
	cout<<"Enter Book ID: ";
	char temp[10];
	cin.getline(temp,10);
	Books* newBook = 0;
	if(Permission(temp,newBook)){
		CurrentUser->IssueBook(newBook);
		char* avail = newBook -> GetAvailability();
		char tempAvail[10] = "available";
		char* _avail = Helper::GetStringFromBuffer(tempAvail);
		char tempUn[13] = "unavailable";
		char* UN_avail = Helper::GetStringFromBuffer(tempUn);
		if(Helper::SearchString(avail, tempAvail))
			newBook -> SetAvailability(UN_avail);
		else
			newBook -> SetAvailability(_avail);
		system("CLS");
		cout<<"Book has been issued. Press 0 to return to Menu: ";
		switch (getch()){
			case '0':
				system("CLS");
				return;
			default:
				system("CLS");
				cout<<"Invalid input. Enter again." <<endl<<endl;
				break;
		}
	}
	else{
		system("CLS");
		cout<<"Book Unavailable\n"<<endl;
		cout<<"1) Issue different book\n2) Return to Menu\n";
		switch (getch()){
			case '1':
				system("CLS");
				break;
			case '2':
				return;
			default:
				system("CLS");
				cout<<"Invalid input. Enter again." <<endl<<endl;
				break;
		}
	}
}

void Library::ReturnBook(){
	bool check=false;
	while(1){
		check=false;
		system("CLS");
		cout<<"Enter Book ID: ";
		char temp[10];
		cin.getline(temp,10);
		for(int i = 0; i < noOfBooks;i++){
			char* tempId = bookRecord[i] -> GetIDBook();
			if(Helper::SearchString(tempId, temp)){
				char* avail = bookRecord[i] -> GetAvailability();
				char tempAvail[13] = "unavailable";
				if(Helper::SearchString(avail,tempAvail)){
					CurrentUser -> ReturnBook(bookRecord[i]);
					char temp2[10] = "available";
					char* check = Helper::GetStringFromBuffer(temp2);
					bookRecord[i] -> SetAvailability(check);
					system("CLS");
					cout<<"Book has been recieved by the Library. Press 0 to return to Menu: ";
					switch (getch()){
						case '0':
							system("CLS");
							return;
						default:
							system("CLS");
							cout<<"Invalid input. Enter again." <<endl<<endl;
							break;
					}
				}
				else{
					system("CLS");
					cout<<"Invalid ID!!\n\n1)Try Again\n2)Return to Menu\n\n";
					switch (getch()){
						case '1':
							system("CLS");
							check=true;
							break;
						case '2':
							system("CLS");
							return;
						default:
							system("CLS");
							cout<<"Invalid input. Enter again." <<endl<<endl;
							break;
					}
				}
				if(check==true)
					break;
			}
		}
	}
}

void Library::librarianLogin(){
	while(1){
		cout<<"		Login Page\n";
		cout<<"Enter your ID: ";
		char id[25];
		cin>>id;
		bool check = false;
		cin.ignore();
		if(Helper::SearchString(id, userID)){
			while(check == false){
				cout<<"Enter your Password: ";
				char pass[50];
				cin.getline(pass,50);
				if(Helper::SearchString(pass,password)){
					system("CLS");
					cout<<"Login Successful!!"<<endl;
					return;
				}
				else{
					system("CLS");
					cout<<"Incorrect Password!!"<<endl;
					check = false;
				}
			}
		}
		system("CLS");
		cout<<"Incorrect ID!!\n\n1)Try Again\n2)Return to Menu"<<endl;
		switch (getch()){
			case '1':
				system("CLS");
				check=true;
				break;
			case '2':
				system("CLS");
				return;
			default:
				system("CLS");
				cout<<"Invalid input. Enter again." <<endl<<endl;
				break;
		}
	}
	return;
}

void Library::NewMember(){
	system("CLS");
	Member** temp = 0;
	temp =new Member*[noOfMembers];

	for(int i = 0; i < noOfMembers; i++){
		temp[i] = new Member;
		temp[i] = memberData[i];
	}
	noOfMembers++;
	memberData = new Member*[noOfMembers];
	for(int i = 0; i < noOfMembers; i++){
		memberData[i] = new Member;
		memberData[i] = temp[i];
	}

	bool check = false;
	bool check2 = true;
	char tempnew[10];

	while(check == false){
		system("CLS");
		cout<<"Set your User ID (For eg M1): ";
		cin.getline(tempnew,10);
		for(int i = 0; i < noOfMembers-1; i++){
			char* tempID = memberData[i] -> GetID();
			if(Helper::SearchString(tempID, tempnew))
				check2 = false;
		}
		system("CLS");
		if(check2 == true)
			check = true;
		else
			cout<<"This ID is already taken!! Try Different One..."<<endl;
	}
	system("CLS");
	check2 = false;
	char* newPass = 0;
	while(check2 != true){
		system("CLS");
		cout<<"Enter New Password (Minimum of 8 characters): ";
		char temp2[20];
		cin.getline(temp2,20);
		newPass = Helper::GetStringFromBuffer(temp2);
		if(Helper::StringLenght(newPass) < 8){
			system("CLS");
			cout<<"Invalid Password!!"<<endl;
			check2 = false;
		}
		else{
			check2 = true;
			break;
		}
	}
	system("CLS");
	cout<<"Enter your Name: ";
	char name_[30];
	cin.getline(name_,30);
	memberData[noOfMembers] = new Member;
	memberData[noOfMembers] -> NewMember(name_, newPass, tempnew);
	cout<<"Member was added. Press 0 to return to Menu: ";
	switch (getch()){
		case '0':
			system("CLS");
			return;
		default:
			system("CLS");
			cout<<"Invalid input. Enter again." <<endl<<endl;
			break;
	}
}

void Library::SaveData(){

	ofstream librarian_output("Librarian.txt");
	librarian_output<<userID<<endl;
	librarian_output<<password;
	librarian_output.close();

	ofstream Books_Output("Books.txt");
	Books_Output<<noOfBooks<<endl;
	for(int i = 0; i < noOfBooks; i++){
		bookRecord[i] -> SaveBooks(Books_Output);
	}
	Books_Output.close();

	ofstream Members_Output("Members.txt");
	Members_Output<<noOfMembers<<endl;
	for(int i = 0; i < noOfMembers; i++){
		memberData[i] -> SaveMembers(Members_Output);
	}
	 Members_Output.close();
}

void Library::EditBook(){
	bool check_=true;
	char newID[10];
	char newName[30];
	char newAuthor[25];
	char newGenre[25];
	system("CLS");
	while(1){
		check_=true;
		bool check = true;
		system("CLS");
		cout<<"Enter the ID of the Book: ";
		char temp[10];
		cin.getline(temp,10);
		for(int i = 0; i < noOfBooks; i++){
			char* tempID = bookRecord[i] -> GetIDBook();
			if(Helper::SearchString(temp,tempID)){
				check_=false;
				while(1){
					system("CLS");
					cout<<"1) ID\n2) Name\n3) Author Name\n4) Genre\n5) Change Status\n6) Return to Menu\n\n";
					switch (getch()){
						case '1':
							check = true;
							while(check == true){
								system("CLS");
								cout<<"Enter new ID: ";
								cin.getline(newID,10);
								for(int j = 0; j < noOfBooks; j++){
									char* tempID_ = bookRecord[j] -> GetIDBook();
									if(Helper::SearchString(newID,tempID_)){
										system("CLS");
										cout<<"This ID is already in use"<<endl;
										check = true;
										break;
									}
								}
								check = false;
								bookRecord[i] -> EditBookID(newID);
								system("CLS");
								cout<<"ID was changed. Press 0 to continue: ";
								switch (getch()){
									case '0':
										system("CLS");
										return;
									default:
										system("CLS");
										cout<<"Invalid input. Enter again." <<endl<<endl;
										break;
								}
							}
							break;
						case '2':
							system("CLS");
							cout<<"Enter New Name: ";
							cin.getline(newName,30);
							bookRecord[i] -> EditBookName(newName);
							system("CLS");
							cout<<"Name was changed\n. Press 0 to continue: ";
							switch (getch()){
								case '0':
									system("CLS");
									return;
								default:
									system("CLS");
									cout<<"Invalid input. Enter again." <<endl<<endl;
									break;
							}
							break;
						case '3':
							system("CLS");
							cout<<"Enter New Name for Author: ";
							cin.getline(newAuthor,25);
							bookRecord[i] -> EditBookAuthor(newAuthor);
							system("CLS");
							cout<<"Author was changed\n. Press 0 to continue: ";
							switch (getch()){
								case '0':
									system("CLS");
									return;
								default:
									system("CLS");
									cout<<"Invalid input. Enter again." <<endl<<endl;
									break;
							}
							break;
						case '4':
							system("CLS");
							cout<<"Enter New Genre: ";
							cin.getline(newGenre,25);
							bookRecord[i] -> EditBookGenre(newGenre);
							system("CLS");
							cout<<"Genre was changed\n. Press 0 to continue: ";
							switch (getch()){
								case '0':
									system("CLS");
									return;
								default:
									system("CLS");
									cout<<"Invalid input. Enter again." <<endl<<endl;
									break;
							}
							break;
						case '5':
							system("CLS");
							bookRecord[i] -> ChangeAvailability();
							cout<<"Status has been Changed!. Press 0 to continue: ";
							switch (getch()){
								case '0':
									system("CLS");
									return;
								default:
									system("CLS");
									cout<<"Invalid input. Enter again." <<endl<<endl;
									break;
							}
							break;
						case '6':
							system("CLS");
							return;
						default:
							system("CLS");
							cout<<"Invalid input. Enter again." <<endl<<endl;
							break;
					}
				}
			}
		}
		if(check_==true){
			system("CLS");
			cout<<"Invalid ID"<<endl;
			cout<<"\n\n1) Try Again\n2)Return to Menu\n";
			switch (getch()){
				case '1':
					system("CLS");
					break;
				case '2':
					system("CLS");
					return;
				default:
					system("CLS");
					cout<<"Invalid input. Enter again." <<endl<<endl;
					break;
			}
		}
	}
}

void Library::ChangeMemberInfo(){
	system("CLS");
	cout<<"1: Change Name\n2: Change Password";
	switch (getch()){
		case '1':
			CurrentUser -> ChangeName();
			break;
		case '2':
			CurrentUser -> ChangePassword();
			return;
		default:
			system("CLS");
			cout<<"Invalid input. Enter again." <<endl<<endl;
			break;
	}
	cout<<"Your Information was updated. Press 0 to return to Menu: ";
	switch (getch()){
		case '0':
			system("CLS");
			return;
		default:
			system("CLS");
			cout<<"Invalid input. Enter again." <<endl<<endl;
			break;
	}
	return;
}

void Library::BookInfo(){
	system("CLS");
	while(1){
		cout<<"Enter Book ID: ";
		char book[10];
		cin.getline(book,10);
		for(int i=0; i<noOfBooks; i++){
			char* id = bookRecord[i] -> GetIDBook();
			if(Helper::SearchString(book,id)){
				bookRecord[i] -> Print();
				cout<<"Press 0 to return to Menu: ";
				switch (getch()){
					case '0':
						system("CLS");
						return;
					default:
						system("CLS");
						cout<<"Invalid input. Enter again." <<endl<<endl;
						break;
				}
			}
		}
		cout<<"No Book Found"<<endl<<endl;
		cout<<"1) Try again\n2) Return to Menu";
		switch (getch()){
			case '1':
				system("CLS");
				break;
			case '2':
				system("CLS");
				return;
			default:
				system("CLS");
				cout<<"Invalid input. Enter again." <<endl<<endl;
				break;
		}
	}
}

void Library::ViewBookList(){
	system("CLS");
	for(int i=0; i<noOfBooks; i++)
		bookRecord[i] -> Print();
	cout<<"\nPress 0 to return to Menu: ";
	switch (getch()){
		case '0':
			system("CLS");
			return;
		default:
			system("CLS");
			cout<<"Invalid input. Enter again." <<endl<<endl;
			break;
	}
}

void Library::ViewMembers(){
	for(int i=0; i<noOfMembers; i++)
		memberData[i] -> Print();

	cout<<"\nPress 0 to return to Menu: ";
	switch (getch()){
		case '0':
			system("CLS");
			return;
		default:
			system("CLS");
			cout<<"Invalid input. Enter again." <<endl<<endl;
			break;
	}
}

void Library::MemberCurrentInfo(){
	system("CLS");
	CurrentUser -> Print();
	cout<<"\nPress 0 to return to Menu: ";
	switch (getch()){
		case '0':
			system("CLS");
			return;
		default:
			system("CLS");
			cout<<"Invalid input. Enter again." <<endl<<endl;
			break;
	}
}

void Library::RunLibrarian(){
	librarianLogin();
	system("CLS");
	while(1){
		system("CLS");
		cout<<"\t\tMenu\n1)  Add Book\n2)  Remove Book\n3)  Change Password\n4)  Change Username\n5)  View Member's List\n6)  View Book List\n7)  Edit Book\n8)  Search Book\n9)  Search Member\n10) Return to Main Menu (Press 0)\n"<<endl;
		switch (getch()){
			case '1':
				system("CLS");
				AddBook();
				break;
			case '2':
				system("CLS");
				RemoveBook();
				break;
			case '3':
				system("CLS");
				ChangePassword();
				break;
			case '4':
				system("CLS");
				ChangeUsername();
				break;
			case '5':
				system("CLS");
				ViewMembers();
				break;
			case '6':
				system("CLS");
				ViewBookList();
				break;
			case '7':
				system("CLS");
				EditBook();
				break;
			case '8':
				system("CLS");
				BookInfo();
				break;
			case '9':
				system("CLS");
				MemberSearch();
				break;
			case '0':
				system("CLS");
				SaveData();
				return;
			default:
				system("CLS");
				cout<<"Invalid input. Enter again." <<endl<<endl;
				break;
		}
	}
}

void Library::RunMember(){
	system("CLS");
	bool check = true;
	while(1){
		system("CLS");
		cout<<"\t\tWelcome to Members' Portal"<<endl;
		cout<<"1) Log in\n2) Sign up\n3) Return to Main Menu\n"<<endl;
		switch (getch()){
			system("CLS");
			case '1':
				MemberLogin();
				check = true;
				while(check==true){
					cout<<"\t\tMenu\n1) Issue Book\n2) Return Book\n3) View your Account Information\n4) Edit your Account Information\n5) Search a Book\n6) View Book List\n7) Log out and Return to Menu\n"<<endl;
					switch (getch()){
						case '1':
							system("CLS");
							IssueBook();
							system("CLS");
							break;
						case '2':
							system("CLS");
							ReturnBook();
							system("CLS");
							break;
						case '3':
							system("CLS");
							MemberCurrentInfo();
							system("CLS");
							break;
						case '4':
							system("CLS");
							ChangeMemberInfo();
							system("CLS");
							break;
						case '5':
							system("CLS");
							BookInfo();
							system("CLS");
							break;
						case '6':
							system("CLS");
							ViewBookList();
							break;
						case '7':
							system("CLS");
							check = false;
							SaveData();
							system("CLS");
							break;
						default:
							system("CLS");
							cout<<"Invalid input. Enter again." <<endl<<endl;
							break;
					}
				}
				break;
			case '2':
				system("CLS");
				NewMember();
				break;
			case '3':
				system("CLS");
				SaveData();
				return;
			default:
				system("CLS");
				cout<<"Invalid input. Enter again." <<endl<<endl;
				break;
		}
	}
	SaveData();
	system("CLS");
}
