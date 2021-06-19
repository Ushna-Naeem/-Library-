#include "Library.h"

void main(){

	Library Lb;
	Lb.LoadData();
	while(1){
		cout<<"\t\tWelcome to Library"<<endl;
		cout<<"1) Librarian\n2) Member\n3) Quit"<<endl;
		switch (getch()){
			case '1':
				system("CLS");
				Lb.RunLibrarian();
				break;
			case '2':
				system("CLS");
				Lb.RunMember();
				break;
			case '3':
				system("CLS");
				Lb.SaveData();
				cout<<"You are Exiting!! THANK YOU for your visit!!\n\tHave a Great Day! :)"<<endl;
				system("pause");
				return;
			default:
				system("CLS");
				cout<<"Invalid input. Enter again." <<endl<<endl;
				break;
		}
	}
}
