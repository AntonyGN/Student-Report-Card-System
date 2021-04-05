
#include<iostream> //header file for input and output
#include<fstream> //header file to record and write binary files
#include<iomanip> //header file to input characters
#include<stdlib.h> //header file to navigate through the system
using namespace std; //standard library

// CLASSES USED IN THE PROJECT

class student
{
	int rollno; //unique indetifier 
	char name[50]; //characters input to the system should not exceed 50 characters
	int oop_marks, p_marks, c_marks, os_marks, d_marks, s_marks; //marks calculated for each unit
	double per;
	char grade;
	void calculate();	//function to calculate grade

// PUBLIC CLASS

public:
	void getdata();		//function to accept data from user
	void showdata() const;	//function to show data on screen
	void show_tabular() const;
	int retrollno() const;
}; //class ends here


// METHOD TO CALCULATE GRADE

void student::calculate()
{
	per=(oop_marks+p_marks+c_marks+os_marks+d_marks+s_marks)/6.0;
	if(per>=75)
		grade='A';
	else if(per>=60)
		grade='B';
	else if(per>=50)
		grade='C';
	else
		grade='F';
}


// METHOD TO GET DATA FROM THE USER

void student::getdata()
{
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in OOP 1 out of 100 : ";
	cin>>oop_marks;
	cout<<"\nEnter The marks in Probability and ststistics out of 100 : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in Calculus out of 100 : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in Operating Systems out of 100 : ";
	cin>>os_marks;
	cout<<"\nEnter The marks in Digital Systems out of 100 : ";
	cin>>d_marks;
	cout<<"\nEnter The marks in System Analysis & Design out of 100 : ";
	cin>>s_marks;
	calculate();
}


// METHOD TO SHOW DATA

void student::showdata() const
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in OOP 1 : "<<oop_marks;
	cout<<"\nMarks in Probability and statistics : "<<p_marks;
	cout<<"\nMarks in Calculus : "<<c_marks;
	cout<<"\nMarks in Operating System : "<<os_marks;
	cout<<"\nMarks in Digital Systems :"<<d_marks;
	cout<<"\nMarks in Systems :"<<s_marks;
	cout<<"\nPercentage of student is  :"<<per;
	cout<<"\nGrade of student is :"<<grade;
}

void student::show_tabular() const
{
	cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<oop_marks<<setw(4)<<p_marks<<setw(4)<<c_marks<<setw(4)
		<<os_marks<<setw(4)<<d_marks<<setw(4)<<s_marks<<setw(8)<<per<<setw(6)<<grade<<endl;
}

int  student::retrollno() const
{
	return rollno;
}

//    	function declaration

void write_student();	//write the record in binary file
void display_all();	//read all records from binary file
void display_sp(int);	//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();	//display all records in tabular format from binary file
void result();		//display result menu
void intro();		//display welcome screen
void entry_menu();	//display entry menu on screen
void Check_Pin(ifstream &read); //validate the pin and write in binary

struct Box //class Box
{
    int Pin;
};
Box get_Data1(ifstream &read)
{
   Box obj;
   read >> obj.Pin;

   return obj;
}


void Check_Pin(ifstream &read)
{
    int Pin;
    int attempts = 1;
    cout << "  Enter Pin:" << endl;
    ofstream write("temp.txt");
    Box s;

    s = get_Data1(read);

    while (!read.eof() && attempts <= 3)
    {

        cin >> Pin;
        attempts++;
        if (s.Pin == Pin)
        {

            cout <<"now you can proceed!"<< endl;
            entry_menu();
            exit(0);
        }
        else if (s.Pin != Pin && attempts >3)
        {
            cout << "  WRONG USER!!!:"<< endl;

        }
        else
        {
            cout << "   WRONG PIN!!! \n\n  Try again..."<< endl;
        }
    }
}

//    	THE MAIN FUNCTION OF PROGRAM
int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. (Administration use only) ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': {ifstream read("record.txt", ios::in);
                      Check_Pin( read);}//entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}


//    	function to write in file


void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata(); // calling the get data method 
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get(); 
}


//    	function to read all records from file


void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata(); // calling the show data method
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


//    	function to read specific record from file


void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n) //User searches the specific record by the roll no.
		{
	  		 st.showdata(); // Calling the show data method to display the record
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nRecord does not exist"<< endl; //if the record does not exist 
		cout << "Click enter to go back to main menu"<< endl;
		
	cin.ignore();
	cin.get();
}


//    	function to modify record of file


void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out); //open the binary file
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n) //get the record to modify by searching using the roll no
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}


//    	function to delete record of file


void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}


//    	function to display all students grade report


void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"============================================================\n";
	cout<<"R.No         Name           OOP 1 P   C   OS  D   S    %age    Grade"<<endl;
	cout<<"============================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}


//    	function to display result menu


void result()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}


//    	INTRODUCTION FUNCTION


void intro()
{
	cout<<"\n\n\n\t\t*********************************";
	cout<<"\n\n\n\t\t   STUDENT REPORT CARD SYSTEM";
	cout<<"\n\n\t\tPROGRAMMED BY : ANTONY GITHENDU";
	cout<<"\n\n\n\tSCHOOL : ZETECH UNIVERSITY";
	cin.get();
}



//    	ENTRY / EDIT MENU FUNCTION


void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
