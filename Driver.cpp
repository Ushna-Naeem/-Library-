#include "Library.h"
 HANDLE colour=GetStdHandle(STD_OUTPUT_HANDLE); 

void main(){
	//This is the main function to run the whole library mangement system 
	Library Lb;
	Lb.LoadData();
	//Below is the start menu that will be showed on the screen and present the viewer with the options
	while(1){
		SetConsoleTextAttribute(colour, 10);
		cout<<"----------------------------------------------------------------------\n"<<endl;
		SetConsoleTextAttribute(colour, 6);
		cout<<"\t\tWelcome to Library Management System!"<<endl;
		SetConsoleTextAttribute(colour, 11);
		cout<<endl<<" ~~ Kindly choose one of the following options: "<<endl;
		cout<<"1) Enter the librarian domain.\n2) Enter the member domain.\n3) Quit the program."<<endl;
		SetConsoleTextAttribute(colour, 5);
		cout<<endl<<"Enter your choice: ";
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
				SetConsoleTextAttribute(colour, 10);
				cout<<"-----------------------------------------------------------"<<endl;
				SetConsoleTextAttribute(colour, 5);
				cout<<endl<<"You are exiting the Library Management System!\n      Thank you for your visit!\n\t";
				SetConsoleTextAttribute(colour, 6);
				cout<<"Have a blessed day! :)"<<endl<<endl;
				SetConsoleTextAttribute(colour, 10);
				cout<<"-----------------------------------------------------------"<<endl;
				system("pause");
				return;
			default:
				system("CLS");
				cout<<"Invalid input :( Enter again!" <<endl<<endl;
				break;
		}
	}
}
