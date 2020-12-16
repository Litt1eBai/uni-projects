#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;


// Basic definiations and functions
int totalUser = 0;
string FILELOCATION_USERINFO = "E:\\UserBaiscInfo.dat";

typedef struct address
{
	int room;
	int level;
	char unit[32];
	char estate[32];
	char street[32];
	char district[32];
	char city[32];
}
add;

typedef struct deviceinfo
{
	int model;
	int serialNo;
	int perchaseTime;
}
device;

typedef struct userinfo
{
	int No;
	char name[32];
	char id[32];
	int type;
	add address;
	char password[32];
}
userinfo;

typedef struct userbill
{
	int No;
	int currentUse;
	int currentBill;
}
userbill;

void getTotalUser()
{
	totalUser = 0;
	fstream tmp;
	tmp.open(FILELOCATION_USERINFO, ios::in | ios::binary);
	tmp.seekg(0, ios::beg);
	int begin;
	begin = tmp.tellg();
	tmp.seekg(0, ios::end);
	int endFile;
	endFile = tmp.tellg();
	totalUser = (endFile - begin) / sizeof(userinfo) - 1;
}
void getString(char* s)
{
	int n = 0;
	cin.get();
	while (cin.peek() != '\n')
	{
		cin.get(s[n]);
		n++;
	}
	s[n] = '\0';
}
void resetUserInfo()
{
	userinfo rootUser;
	rootUser.No = 0;
	strcpy_s(rootUser.name, "root");
	strcpy_s(rootUser.id, "0");
	rootUser.type = 1;
	strcpy_s(rootUser.address.city, "default");
	strcpy_s(rootUser.address.district, "default");
	strcpy_s(rootUser.address.street, "default");
	strcpy_s(rootUser.address.estate, "default");
	strcpy_s(rootUser.address.unit, "default");
	rootUser.address.level = 0;
	rootUser.address.room = 0;
	fstream resetFile;
	resetFile.open(FILELOCATION_USERINFO, ios::binary | ios::out);
	resetFile.write((char*)&rootUser, sizeof(userinfo));
	resetFile.close();
	getTotalUser();
}
int genUserNo()
{
	fstream tmpf;
	userinfo tmp;
	tmpf.open(FILELOCATION_USERINFO, ios::in | ios::app |ios::binary);
	int size = sizeof(userinfo);
	tmpf.seekg(-size,ios::end);
	tmpf.read((char*)&tmp, sizeof(userinfo));
	return (tmp.No + 1);
}
void dotDotDot(int n)
{
	for (int i = 0; i < n; i++)
	{

		cout << '.';
		Sleep(0700);
	}
}



void generateUser()
{
	userinfo newUser;
	newUser.No = genUserNo();

	system("cls");
	int typchoice;
	cout << "USER MANAGEMENT" << endl;
	cout << "==============================================" << endl;
	cout << "You are creating an user" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Name:";
	getString(newUser.name);


	system("cls");
	cout << "USER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "user type:" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "|  1.Administrator     2.Meter Reader  3.Charger             |" << endl;
	cout << "|  4.Enterprice User   5.Urban User    6.Common Rural User   |" << endl;
	cout << "|  7.Rural User in Poverty                                   |" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "User type: ";
	cin >> typchoice;
	string type;
	switch (typchoice)
	{
	case 1: type = "Administrator"; newUser.type = 1; break;
	case 2: type = "Meter Reader"; newUser.type = 2; break;
	case 3: type = "Charger"; newUser.type = 3; break;
	case 4: type = "Enterprice User"; newUser.type = 4; break;
	case 5: type = "Urban User"; newUser.type = 5; break;
	case 6: type = "Common Rural User"; newUser.type = 6; break;
	case 7: type = "Rural User in Poverty"; newUser.type = 7; break;
	}

	system("cls");
	cout << "USER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Address:" << endl;
	cout << "City: ";
	getString(newUser.address.city);
	cout << "District: ";
	getString(newUser.address.district);
	cout << "Street: ";
	getString(newUser.address.street);
	cout << "Estate: ";
	getString(newUser.address.estate);
	cout << "Unit: ";
	getString(newUser.address.unit);
	cout << "Level: ";
	cin >> newUser.address.level;
	cout << "Room: ";
	cin >> newUser.address.room;


	system("cls");
	cout << "USER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "Address: " << newUser.address.unit << "-" << newUser.address.level << "-" << newUser.address.room
		<< " " << newUser.address.estate << ", " << newUser.address.street << ", " << newUser.address.district << ", " << newUser.address.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "User's National ID: ";
	cin >> newUser.id;

	//system("cls");
	//cout << "USER MANAGEMENT" << endl;
	//cout << "======================================================================" << endl;
	//cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	//cout << "National ID: " << newUser.id << endl;
	//cout << " Address: " << newUser.address.unit << "-" << newUser.address.level << "-" << newUser.address.room
	//	<< " " << newUser.address.estate << ", " << newUser.address.street << ", " << newUser.address.district << ", " << newUser.address.city << endl;
	//cout << "----------------------------------------------------------------------" << endl;
	//cout << "User Number: ";
	//cin >> newUser.No;

	system("cls");
	cout << "USER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "Congratulations! You have done creating an new user, here is the detail" << endl;
	cout << "Name: " << newUser.name << endl;
	cout << "Type: " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "National ID: " << newUser.id << endl;
	cout << " Address: " << newUser.address.unit << "-" << newUser.address.level << "-" << newUser.address.room
		<< " " << newUser.address.estate << ", " << newUser.address.street << ", " << newUser.address.district << ", " << newUser.address.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Are you sure to store it" << endl;
	cout << "y/n: ";
	char opt;
	cin >> opt;
	if (opt == 'y' || opt == 'Y')
	{
		fstream userBasicInfo;
		userBasicInfo.open(FILELOCATION_USERINFO, ios::binary | ios::app | ios::out);
		if (!userBasicInfo)
		{
			cout << "Error opening or creating file!";
		}
		userBasicInfo.write((char*)&newUser, sizeof(userinfo));
		userBasicInfo.close();
		getTotalUser();
		cout << endl;
		cout << "Sucessful" << endl;
	}
	else
	{
		cout << endl;
		cout << "Cancelled" << endl;
	}



	system("pause");
}

void getPassword(int usernumber)
{
	fstream user;
	while(user.open(FILELOCATION_USERINFO, ios::binary | ios::in | ios::app);)
}

// Subsystems

void adminListUsers()
{
	system("cls");
	cout << "USER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << endl;
	cout << "*******************************************" << endl;
	cout << "* Input 'help' for more instruction hints *" << endl;
	cout << "*******************************************" << endl;
	cout << "Loading";
	dotDotDot(3);
	int userCount = 0;
	system("cls");
	cout << "USER MANAGEMENT - USER LIST" << endl;
	cout << "============================================================================================================" << endl;
	cout << "Number                   Name	        Type                      ID                Address  " << endl;
	cout << "------------------------------------------------------------------------------------------------------------";
	cout << endl;
	userinfo user;
	fstream readUser("E:\\UserBaiscInfo.dat", ios::in | ios::binary);
	readUser.seekg(sizeof(userinfo), ios::beg);
	while (readUser.read((char*)&user, sizeof(userinfo)))
	{
		string type;
		switch (user.type)
		{
		case 1: type = "Administrator"; break;
		case 2: type = "Meter Reader"; break;
		case 3: type = "Charger"; break;
		case 4: type = "Enterprice User"; break;
		case 5: type = "Urban User"; break;
		case 6: type = "Common Rural User"; break;
		case 7: type = "Rural User in Poverty"; break;
		}
		cout << setw(16) << user.No << " " << setw(16) <<user.name << "  " << setw(21) << type << " " << setw(18) << user.id << '\t'
			<< user.address.unit << '-' << user.address.level << '-' << user.address.room
			<< ", " << user.address.estate << ", " << user.address.street << ", " << user.address.district
			<< ", " << user.address.city << endl;
	}
	system("pause");
}
void userManage()
{
	int exitflag = 0;
	while (!exitflag)
	{
		system("cls");
		getTotalUser();
		cout << "USER MANAGEMENT" << endl;
		cout << "======================================================================" << endl;
		cout << "Total users: " << totalUser << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "Menu: " << endl;
		cout << "1. Show user" << endl;
		cout << "2. Edit user infomation" << endl;
		cout << "3. Remove user" << endl;
		cout << "4. Reset database" << endl;
		cout << "5. Exit" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1: adminListUsers(); break;
		case 4:
			system("cls");
			cout << "ARE YOU SURE?" << endl;
			cout << "This will wipe out all user data" << endl;
			cout << "y/n : ";
			char opt1;
			cin >> opt1;
			if (opt1 == 'y' || opt1 == 'Y')
				resetUserInfo();
			break;
		case 5: exitflag = 1;
		}
	}
}
void AdminDash()
{
	int exitflag = 0;
	while (!exitflag)
	{
		system("cls");
		cout << "DASHBOARD" << endl;
		cout << "==============================================" << endl;
		cout << "username" << ", greetings!" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Total users: " << totalUser << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Menu:" << endl;
		cout << "1. Manage current users" << endl;
		cout << "2. User Regestration" << endl;
		cout << "3. Exit" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1: userManage(); break;
		case 2: generateUser(); break;
		case 3: exitflag = 1;
		}
	}
}


int main()
{
	getTotalUser();
	AdminDash();
}