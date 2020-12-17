#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;

// Basic definiations and functions
int totalUser = 0;
string FLOC_USERBASICINFO = "E:\\Billing System\\userbasicinfo.dat";
string FLOC_EDITUSERINFO_TEMP = "E:\\Billing System\\temp_userbasicinfo.dat";
string FLOC_SYSSET = "E:\\Billing System\\SystemSettings.dat";
typedef struct fLoc_sysSet
{
	string userBasicInfo;
	string editUserBasicInfo_tmp;
}fLoc_sysSet;
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
	char id[19]; // one for '\0'
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
// Initialising
void getTotalUser()
{
	totalUser = 0;
	fstream tmp;
	tmp.open(FLOC_USERBASICINFO, ios::in | ios::binary);
	tmp.seekg(0, ios::beg);
	int begin;
	begin = tmp.tellg();
	tmp.seekg(0, ios::end);
	int endFile;
	endFile = tmp.tellg();
	totalUser = (endFile - begin) / sizeof(userinfo);
}
void getFileLocation()
{
	fstream floc;
	floc.open(FLOC_SYSSET, ios::binary | ios::out);
	fLoc_sysSet location;
	floc.seekg(0, ios::beg);
	floc.read((char*)&location, sizeof(fLoc_sysSet));
	FLOC_USERBASICINFO = location.userBasicInfo;
	FLOC_EDITUSERINFO_TEMP = location.editUserBasicInfo_tmp;
	floc.close();
}


// Functions
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

// System settings - reset
void resetDatabase_UserBasicInfo()
{
	userinfo rootUser;
	rootUser.No = 0;
	strcpy_s(rootUser.name, "root");
	strcpy_s(rootUser.id, "0");
	rootUser.type = 1;
	strcpy_s(rootUser.password, "root");
	strcpy_s(rootUser.address.city, "default");
	strcpy_s(rootUser.address.district, "default");
	strcpy_s(rootUser.address.street, "default");
	strcpy_s(rootUser.address.estate, "default");
	strcpy_s(rootUser.address.unit, "default");
	rootUser.address.level = 0;
	rootUser.address.room = 0;
	fstream resetFile;
	resetFile.open(FLOC_USERBASICINFO, ios::binary | ios::out);
	resetFile.write((char*)&rootUser, sizeof(userinfo));
	resetFile.close();
	getTotalUser();
}
void resetSystemFileLocation()
{
	fstream floc;
	fLoc_sysSet location;
	floc.open("E:\\Billing System\\SystemSettings.dat", ios::binary | ios::out);
	location.userBasicInfo = "E:\\Billing System\\temp_userbasicinfo.dat";
	location.userBasicInfo = "E:\\Billing System\\userbasicinfo.dat";
	floc.write((char*)&location, sizeof(fLoc_sysSet));
	floc.close();
	getFileLocation();
}
void resetDatabase()
{
	//resetSystemFileLocation();
	resetDatabase_UserBasicInfo();
}




void changePasswordTo(int usernumber, char* passget, char* passput)
{
	userinfo change_userinfo;
	for (int i = 0; passget[i] != '\0'; i++)
	{
		change_userinfo.password[i] = passget[i];
	}
	fstream origin;
	fstream tmp;
	userinfo temp_userinfo;
	tmp.open(FLOC_EDITUSERINFO_TEMP, ios::out | ios::binary | ios::app);
	tmp.write((char*)&change_userinfo, sizeof(userinfo));
	while (origin.read((char*)&temp_userinfo, sizeof(userinfo)))
	{
		if (temp_userinfo.No != usernumber)
		{
			tmp.write((char*)&temp_userinfo, sizeof(userinfo));
		}
	}
	while (tmp.read((char*)&temp_userinfo, sizeof(userinfo)))
	{
		origin.write((char*)&temp_userinfo, sizeof(userinfo));
	}
}
int genUserNo()
{
	fstream tmpf;
	userinfo tmp;
	tmpf.open(FLOC_USERBASICINFO, ios::in | ios::app |ios::binary);
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
void setdefaultPassword(char id[], char passput[])
{
	int i;
	for (i = 0; i < 6; i++)
	{
		passput[i] = id[17 - i];
	}
	passput[i] = '\0';
}






// Management Process
void generateUser()
{
	userinfo newUser;
	newUser.No = genUserNo();

	system("cls");
	int typchoice;
	cout << "USER USER REGESTRATION - NAME" << endl;
	cout << "==============================================" << endl;
	cout << "You are creating an user" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Name:";
	getString(newUser.name);


	system("cls");
	cout << "USER REGESTRATION - USER TYPE" << endl;
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
	while (!(typchoice >= 1 && typchoice <= 7))
	{
		cout << "Invalid Input" << endl;
		cin >> typchoice;
	}
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
	cout << "USER REGESTRATION - ADDRESS" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "City: ";
	getString(newUser.address.city);
	while (strlen(newUser.address.city) >= 32)
	{
		cout << "Invalid city name" << endl;
		cout << "city: ";
		getString(newUser.address.city);
	}
	
	system("cls");
	cout << "USER REGESTRATION - ADDRESS" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "Address: " << newUser.address.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "District: ";
	getString(newUser.address.district);
	while (strlen(newUser.address.district) >= 32)
	{
		cout << "Invalid district name" << endl;
		cout << "district: ";
		getString(newUser.address.district);
	}

	system("cls");
	cout << "USER REGESTRATION - ADDRESS" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "Address: " << newUser.address.district << ", " << newUser.address.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Street: ";
	getString(newUser.address.street);
	while (strlen(newUser.address.street) >= 32)
	{
		cout << "Invalid street name" << endl;
		cout << "street: ";
		getString(newUser.address.street);
	}

	system("cls");
	cout << "USER REGESTRATION - ADDRESS" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "Address: " << newUser.address.street << ", " << newUser.address.district << ", " 
		<< newUser.address.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Estate: ";
	getString(newUser.address.estate);
	while (strlen(newUser.address.estate) >= 32)
	{
		cout << "Invalid estate name" << endl;
		cout << "Estate: ";
		getString(newUser.address.estate);
	}

	system("cls");
	cout << "USER REGESTRATION - ADDRESS" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "Address: " << newUser.address.estate << ", " << newUser.address.street << ", " 
		<< newUser.address.district << ", " << newUser.address.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Unit: ";
	getString(newUser.address.unit);
	while (strlen(newUser.address.unit) >= 32)
	{
		cout << "Invalid unit name" << endl;
		cout << "unit: ";
		getString(newUser.address.unit);
	}
	
	system("cls");
	cout << "USER REGESTRATION - ADDRESS" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "Address: " << newUser.address.unit  << " " <<  newUser.address.estate << ", "
		<< newUser.address.street << ", " << newUser.address.district << ", " << newUser.address.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Level: ";
	cin >> newUser.address.level;
	while (!cin)
	{
		cout << "Invalid level" << endl;
		cout << "level: ";
		cin >> newUser.address.level;
	}

	system("cls");
	cout << "USER REGESTRATION - ADDRESS" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "Address: " << newUser.address.level << "-" << newUser.address.level
		<< " " << newUser.address.estate << ", " << newUser.address.street << ", " << newUser.address.district << ", " << newUser.address.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Room: ";
	cin >> newUser.address.room;
	while (!cin)
	{
		cout << "Invalid room" << endl;
		cout << "Room: ";
		cin >> newUser.address.room;
	}

	system("cls");
	cout << "USER REGESTRATION - ID" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "Address: " << newUser.address.unit << "-" << newUser.address.level << "-" << newUser.address.room
		<< " " << newUser.address.estate << ", " << newUser.address.street << ", " << newUser.address.district << ", " << newUser.address.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "User's National ID: ";
	cin >> newUser.id;
	while (strlen(newUser.id) != 18)
	{
		cout << "Invalid ID" << endl;
		strcpy_s(newUser.password, "set default password error");
		cout << "User's National ID: ";
		cin >> newUser.id;
	}

	setdefaultPassword(newUser.id, newUser.password);

	system("cls");
	cout << "USER REGESTRATION - FINISH" << endl;
	cout << "======================================================================" << endl;
	cout << "*************************Congratulations!*****************************" << endl;
	cout << "You have created a new user, here is the detail" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Name: " << newUser.name << endl;
	cout << "Type: " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "National ID: " << newUser.id << endl;
	cout << " Address: " << newUser.address.unit << "-" << newUser.address.level << "-" << newUser.address.room
		<< " " << newUser.address.estate << ", " << newUser.address.street << ", " << newUser.address.district << ", " << newUser.address.city << endl;
	cout << "Default password: " << newUser.password << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Are you sure to store it" << endl;
	cout << "y/n: ";
	char opt;
	cin >> opt;
	if (opt == 'y' || opt == 'Y')
	{
		fstream userBasicInfo;
		userBasicInfo.open(FLOC_USERBASICINFO, ios::binary | ios::app | ios::out);
		if (!userBasicInfo)
		{
			cout << "Error opening or creating file!";
		}
		userBasicInfo.write((char*)&newUser, sizeof(userinfo));
		userBasicInfo.close();
		getTotalUser();
		cout << endl;
		cout << "Sucessful" << endl;
		Sleep(1000);
	}
	else
	{
		cout << endl;
		cout << "Cancelled" << endl;
		Sleep(1000);
	}
	
}




// System Settings
void adminSystemSettings_StorageSettings_menu()
{
	int exitflag = 0;
	while (!exitflag)
	{
		system("cls");
		cout << "SYSTEM SETTINGS - STORAGE SETTIGNS" << endl;
		cout << "==============================================" << endl;
		cout << "Menu:" << endl;
		cout << "1. Change temp file location" << endl;
		cout << "2. Change user basic info location" << endl;
		cout << "0. Exit" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1:
			system("cls");
			cout << "SYSTEM SETTINGS - STORAGE SETTIGNS" << endl;
			cout << "==============================================" << endl;
			cout << "You are changing the temp file location" << endl;
			cout << "Current: temp file is stored in: ";
			cout << FLOC_EDITUSERINFO_TEMP << endl;
			cout << "----------------------------------------------" << endl;
			cout << "Enter your new file path:" << endl;
			cin >> FLOC_EDITUSERINFO_TEMP;
			system("cls");
			cout << "SYSTEM SETTINGS - STORAGE SETTIGNS" << endl;
			cout << "==============================================" << endl;
			cout << "Path changed" << endl;
			cout << "Current: temp file is stored in: ";
			cout << FLOC_EDITUSERINFO_TEMP << endl;
			cout << "----------------------------------------------" << endl;
			break;
		case 2:
			system("cls");
			cout << "SYSTEM SETTINGS - STORAGE SETTIGNS" << endl;
			cout << "==============================================" << endl;
			cout << "You are changing the user basic info file location" << endl;
			cout << "Current: temp file is stored in: ";
			cout << FLOC_USERBASICINFO << endl;
			cout << "----------------------------------------------" << endl;
			cout << "Enter your new file path:" << endl;
			cin >> FLOC_USERBASICINFO;
			system("cls");
			cout << "SYSTEM SETTINGS - STORAGE SETTIGNS" << endl;
			cout << "==============================================" << endl;
			cout << "Path changed" << endl;
			cout << "Current: temp file is stored in: ";
			cout << FLOC_USERBASICINFO << endl;
			cout << "----------------------------------------------" << endl;
			break;
		case 0:
			exitflag = 1;
			break;
		default: cout << "Invalid input, please try again" << endl;
			cin >> opt;
		}
	}
}
void adminSystemSettings_menu()
{
	int exitflag = 0;
	while (!exitflag)
	{
		system("cls");
		cout << "SYSTEM SETTINGS" << endl;
		cout << "==============================================" << endl;
		cout << "Menu:" << endl;
		cout << "1. Change password" << endl;
		cout << "2. Change file location" << endl;
		cout << "3. Reset database" << endl;
		cout << "0. Exit" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1: 
			
			break;
		case 2: 
			adminSystemSettings_StorageSettings_menu();
			break;
		case 3:
			system("cls");
			cout << "ARE YOU SURE?" << endl;
			cout << "This will wipe out all user data" << endl;
			cout << "y/n : ";
			char opt1;
			cin >> opt1;
			if (opt1 == 'y' || opt1 == 'Y')
				resetDatabase();
			break;
		case 0: exitflag = 1; break;
		default: cout << "Invalid input, please try again" << endl;
			cin >> opt;
		}
	}
}


// Menu
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
	cout << "=====================================================================================================================================================================================" << endl;
	cout << "Number                   Name	             Type                      ID                Address                                                          Password" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout << endl;
	userinfo user;
	fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
	//readUser.seekg(sizeof(userinfo), ios::beg);
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
			<< ", " << user.address.city  << setw(32) << user.password << endl;
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
		cout << "0. Exit" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1: adminListUsers(); break;
		case 0: exitflag = 1;
			break;
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
		cout << "Administrator" << ", greetings!" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Total users: " << totalUser << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Menu:" << endl;
		cout << "1. Manage current users" << endl;
		cout << "2. User Regestration" << endl;
		cout << "3. System Settings" << endl;
		cout << "0. Exit" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1: userManage(); break;
		case 2: generateUser(); break;
		case 3: adminSystemSettings_menu(); break;
		case 0: exitflag = 1;
			break;
		default: cout << "Invalid input, please try again" << endl;
			cin >> opt;
		}
	}
}


int main()
{
	//getFileLocation();

	//system("pause");
	getTotalUser();

	AdminDash();
}