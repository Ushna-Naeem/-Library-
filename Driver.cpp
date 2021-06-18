#include "Library.h"

void main(){

	Library Lb;
	Lb.LoadData();
	int choice = 0;

	while(1){
		cout<<"\t\tWelcome to Library"<<endl;
		int option = 0;
		cout<<"1) Librarian\n2) Member\n3) Quit"<<endl;
		cout<<"\nYour Choice: ";
		cin>>option;
		cin.ignore();
		system("CLS");
		if(option == 1){
			Lb.librarianLogin();
			system("CLS");
			while(1){
				system("CLS");
				cout<<"\t\tMenu\n1)  Add Book\n2)  Remove Book\n3)  Change Password\n4)  Change Username\n5)  View Member's List\n6)  View Book List\n7)  Edit Book\n8)  Search Book\n9)  Search Member\n10) Return to Main Menu\n"<<endl;
				int c;
				cout<<"Your Choice: ";
				cin>>c;
				cin.ignore();
				system("CLS");
				if(c==1)
					Lb.AddBook();
				if(c==2)
					Lb.RemoveBook();
				if(c==3)
					Lb.ChangePassword();
				if(c==4)
					Lb.ChangeUsername();
				if(c==5)
					Lb.ViewMembers();
				if(c==6)
					Lb.ViewBookList();
				if(c==7)
					Lb.EditBook();
				if(c==8)
					Lb.BookInfo();
				if(c==9)
					Lb.MemberSearch();
				if(c==10)
					break;

				Lb.SaveData();
			}
		}
		else if(option == 2){
			system("CLS");
			while(1){
				system("CLS");
				cout<<"\t\tWelcome to Members' Portal"<<endl;
				cout<<"1) Log in\n2) Sign up\n3) Return to Main Menu\n"<<endl;
				choice = 0; 
				cout<<"Your Choice: ";
				cin>>choice;
				cin.ignore();
				if(choice==1){
					Lb.MemberLogin();
					system("CLS");
					while(1){
						system("CLS");	
						cout<<"\t\tMenu\n1) Issue Book\n2) Return Book\n3) View your Account Information\n4) Edit your Account Information\n5) Search a Book\n6) View Book List\n7) Log out and Return to Main Menu\n"<<endl;
						int c;
						cout<<"Your Choice: ";
						cin>>c;
						cin.ignore();
						system("CLS");
						if(c==1)
							Lb.IssueBook();
						if(c==2)
							Lb.ReturnBook();
						if(c==3)
							Lb.MemberCurrentInfo();
						if(c==4)
							Lb.ChangeMemberInfo();
						if(c==5)
							Lb.BookInfo();
						if(c==6)
							Lb.ViewBookList();
						if(c==7)
							break;
						}
					}
					if(choice==2)
						Lb.NewMember();
					if(choice==3)
						break;
			}
			Lb.SaveData();
			system("CLS");
		}
		if(option==3){
			system("CLS");
			cout<<"You are Exiting!! THANK YOU for your visit!!\n\tHave a Great Day! :)"<<endl;
			system("pause");
			return;
		}
	}
}