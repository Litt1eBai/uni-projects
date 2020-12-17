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
string FLOC_BILLDETAIL = "E:\\Billing System\\bill_detail.dat";
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
}add;
typedef struct date
{
	int min;
	int h;
	int d;
	int m;
	int y;

}date;
typedef struct deviceinfo
{
	int model;
	int serialNo;
	int perchaseTime;
}device;
typedef struct userinfo
{
	int No;
	char name[32];
	char id[19]; // one for '\0'
	int type;
	add address;
	char password[32];
}userinfo;
typedef struct userbill
{
	bool read;
	int case_no;
	userinfo user_record;
	date date_record;
	date date_pay;
	int bill_amount;
	bool payment;
}userbill;



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



// Find user and get info
bool findUser(int username)
{
	userinfo use;
	fstream temp;
	temp.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	while (!temp.eof())
	{
		temp.read((char*)&use, sizeof(userinfo));
		if (use.No == username)
		{
			return true;
		}
	}
	return false;
}
userinfo getUserInfo(int username)
{
	userinfo use;
	fstream temp;
	temp.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	while (!temp.eof())
	{
		temp.read((char*)&use, sizeof(userinfo));
		if (use.No == username)
		{
			temp.close();
			break;
		}
	}
	return use;
}

bool validUser(int username)
{
	userinfo use;
	use = getUserInfo(username);
	if (use.No == username)
		return true;
	return false;
}
string rtnType(int typenum)
{
	string typ;
	switch (typenum)
	{
	case 1: typ = "Administrator"; break;
	case 2: typ = "Meter Reader";  break;
	case 3: typ = "Charger"; break;
	case 4: typ = "Enterprice User"; break;
	case 5: typ = "Urban User"; break;
	case 6: typ = "Common Rural User"; break;
	case 7: typ = "Rural User in Poverty"; break;
	}
	return typ;
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





// Apply changes - user basic info
void storeUserInfo(userinfo use)
{
	userinfo user;
	fstream temp;
	temp.open(FLOC_USERBASICINFO, ios::binary | ios::app | ios::out);
	temp.write((char*)&use, sizeof(userinfo));
	temp.close();
}
void changeUserInfo(userinfo use)
{
	userinfo tmpInfo;
	fstream origin;
	fstream temp;
	origin.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::out);
	while (!origin.eof())
	{
		origin.read((char*)&tmpInfo, sizeof(userinfo));
		if (tmpInfo.No == use.No)
			temp.write((char*)&use, sizeof(userinfo));
		else
			temp.write((char*)&tmpInfo, sizeof(userinfo));
	}
	temp.close();
	origin.close();
	origin.open(FLOC_USERBASICINFO, ios::binary | ios::out);
	temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::in);
	while (!temp.eof())
	{
		temp.read((char*)&tmpInfo, sizeof(userinfo));
		origin.write((char*)&tmpInfo, sizeof(userinfo));
	}
	temp.close();
	origin.close();
}
void deleteUserInfo(userinfo use)
{
	userinfo tmpInfo;
	fstream origin;
	fstream temp;
	origin.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::out);
	while (!origin.eof())
	{
		origin.read((char*)&tmpInfo, sizeof(userinfo));
		if (tmpInfo.No == use.No)
			continue;
		else
			temp.write((char*)&tmpInfo, sizeof(userinfo));
	}
	temp.close();
	origin.close();
	origin.open(FLOC_USERBASICINFO, ios::binary | ios::out);
	temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::in);
	while (!temp.eof())
	{
		temp.read((char*)&tmpInfo, sizeof(userinfo));
		origin.write((char*)&tmpInfo, sizeof(userinfo));
	}
	temp.close();
	origin.close();
}


// Meter Reader Features

// Get work process
int getStreetRead(int username, char* st)
{
	fstream tmp;
	userbill user;
	int unread = 0;
	tmp.open(FLOC_BILLDETAIL, ios::binary | ios::app | ios::in);
	while (!tmp.eof())
	{
		tmp.read((char*)&user, sizeof(userbill));
		if (strcmp(user.user_record.address.street, st))
		{
			if (user.read == true)
			{
				unread++;
			}
		}
	}
	tmp.close();
	return unread;
}
int getStreetTotal(int username, char* street)
{
	fstream tmp;
	userbill user;
	int unread = 0;
	tmp.open(FLOC_BILLDETAIL, ios::binary | ios::app | ios::in);
	while (!tmp.eof())
	{
		tmp.read((char*)&user, sizeof(userbill));
		if (strcmp(user.user_record.address.street, street))
		{
			unread++;
		}
	}
	return unread;
}
int getEstateRead(int username, char* est)
{
	fstream tmp;
	userbill user;
	int unread = 0;
	tmp.open(FLOC_BILLDETAIL, ios::binary | ios::app | ios::in);
	while (!tmp.eof())
	{
		tmp.read((char*)&user, sizeof(userbill));
		if (strcmp(user.user_record.address.estate, est))
		{
			if (user.read == true)
			{
				unread++;
			}
		}
	}
	tmp.close();
	return unread;
}
int getEstateTotal(int username, char* est)
{
	fstream tmp;
	userbill user;
	int unread = 0;
	tmp.open(FLOC_BILLDETAIL, ios::binary | ios::app | ios::in);
	while (!tmp.eof())
	{
		tmp.read((char*)&user, sizeof(userbill));
		if (strcmp(user.user_record.address.estate, est))
		{
			unread++;
		}
	}
	tmp.close();
	return unread;
}
int getUnitRead(int username, char* unit)
{
	fstream tmp;
	userbill user;
	int unread = 0;
	tmp.open(FLOC_BILLDETAIL, ios::binary | ios::app | ios::in);
	while (!tmp.eof())
	{
		tmp.read((char*)&user, sizeof(userbill));
		if (strcmp(user.user_record.address.unit, unit))
		{
			if (user.read == true)
			{
				unread++;
			}
		}
	}
	tmp.close();
	return unread;
}
int getReadTotal(int username, char* unit)
{
	fstream tmp;
	userbill user;
	int unread = 0;
	tmp.open(FLOC_BILLDETAIL, ios::binary | ios::app | ios::in);
	while (!tmp.eof())
	{
		tmp.read((char*)&user, sizeof(userbill));
		if (strcmp(user.user_record.address.unit, unit))
		{
			unread++;
		}
	}
	tmp.close();
	return unread;
}


void MRInput()
{
	int userread = 0;
	int userunread = 10;
	double fee = 0;
	while (cin)
	{
		system("cls");
		cout << "Bill Input" << endl;
		cout << "=====================================================" << endl;
		cout << "You are inputting bill information of:" << endl;
		cout << "Xinhua Yuan, N. Shapingba St., Shapingba, Chongqing" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "Your progress:" << endl;
		cout << "Read: " << userread << "/" << userunread << endl;
		cout << "Progress: " << (userread / userunread) * 100 << "%" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "Information for: " << "1-2 Xinhua Yuan" << endl;
		cout << "User: " << "username" << ", " << 1 << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "Useage: ";
		cin >> fee;
	}
}
void MROverview()
{
	int exitflag = 0;
	while (!exitflag)
	{
		int userread = 0;
		int userunread = 10;
		system("cls");
		cout << "DASHBOARD" << endl;
		cout << "==============================================" << endl;
		cout << "Your are responsible for: " << endl;
		cout << "Shapingba District, Chongqing" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Your progress: (Shapingba District)";
		cout << "Read: " << userread << "/" << userunread << endl;
		cout << "Progress: " << (userread / userunread) * 100 << "%" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "Overview:" << endl;
		cout << "N. Shapingba St.\t"
			<< "Read: " << userread << "/" << userunread
			<< " Progress: " << (userread / userunread) * 100 << "%" << endl;
		cout << "Central Shapingba St.:\t"
			<< "Read: " << userread << "/" << userunread
			<< " Progress: " << (userread / userunread) * 100 << "%" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "You wish to input: ";
		string place;
		cin >> place;

	}

}
void MRDash(int username)
{
	userinfo me;
	me = getUserInfo(username);
	int userread = 0;
	int totaluser = 10;
	int exitflag = 0;
	while (!exitflag)
	{
		system("cls");
		cout << "DASHBOARD" << endl;
		cout << "==============================================" << endl;
		cout << me.name << ", greetings!" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Your progress: " << endl;
		cout << "Read: " << userread << "/" << totaluser << endl;
		cout << "Progress: " << (userread / totaluser) * 100 << "%" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Menu:" << endl;
		cout << "1. Start Inputing" << endl;
		cout << "2. Edit bill" << endl;
		cout << "0. Exit" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1: MROverview();  break;
		case 2:; break;
		case 0: exitflag = 1;
			break;
		default: cout << "Invalid input, please try again" << endl;
			cin >> opt;
		}
	}
}



// Admin Features
void changePasswordTo(int username, char* passput)
{
	userinfo user;
	user = getUserInfo(username);
	strcpy_s(user.password, passput);
	changeUserInfo(user);
}

int genUserNo()
{
	fstream tmpf;
	userinfo tmp;
	tmpf.open(FLOC_USERBASICINFO, ios::in | ios::app | ios::binary);
	int size = sizeof(userinfo);
	tmpf.seekg(-size, ios::end);
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
	cout << "USER USER REGISTRATION - NAME" << endl;
	cout << "==============================================" << endl;
	cout << "You are creating an user" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Name:";
	getString(newUser.name);


	system("cls");
	cout << "USER REGISTRATION - USER TYPE" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "user type:" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "|  1.Administrator     2.Meter Reader  3.Charger             |" << endl;
	cout << "|  4.Enterprise User   5.Urban User    6.Common Rural User   |" << endl;
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
	case 4: type = "Enterprise User"; newUser.type = 4; break;
	case 5: type = "Urban User"; newUser.type = 5; break;
	case 6: type = "Common Rural User"; newUser.type = 6; break;
	case 7: type = "Rural User in Poverty"; newUser.type = 7; break;
	}

	system("cls");
	cout << "USER REGISTRATION - ADDRESS" << endl;
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
	cout << "USER REGISTRATION - ADDRESS" << endl;
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
	cout << "USER REGISTRATION - ADDRESS" << endl;
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
	cout << "USER REGISTRATION - ADDRESS" << endl;
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
	cout << "USER REGISTRATION - ADDRESS" << endl;
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
	cout << "USER REGISTRATION - ADDRESS" << endl;
	cout << "======================================================================" << endl;
	cout << "You are creating: " << newUser.name << "; " << type << "(" << newUser.type << ")" << endl;
	cout << "User number: " << newUser.No << endl;
	cout << "Address: " << newUser.address.unit << " " << newUser.address.estate << ", "
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
	cout << "USER REGISTRATION - ADDRESS" << endl;
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
	cout << "USER REGISTRATION - ID" << endl;
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
	cout << "USER REGISTRATION - FINISH" << endl;
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
		cout << "Successful" << endl;
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


// Admin_Menu
void adminEditUser_Detail(int username)
{
	userinfo user;
	user = getUserInfo(username);
	int exit = 0;
	while (!exit)
	{
		system("cls");
		getTotalUser();
		cout << "USER MANAGEMENT - EDIT USER DETAIL" << endl;
		cout << "======================================================================" << endl;
		cout << "Detail of " << user.name << endl;
		cout << endl;
		cout << "1. Name: " << user.name << endl;
		cout << "2. Type: " << rtnType(user.type) << "(" << user.type << ")" << endl;
		cout << "   User Number: " << user.No << endl;
		cout << "3. ID: " << user.id << endl;
		cout << "4. Address" << user.address.unit << "-" << user.address.level << "-" << user.address.room
			<< " " << user.address.estate << ", " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
		cout << "5. Password: " << user.password << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "What do you want to change about the user: " << endl;
		cout << "1 - 5 Change the corresponding information" << endl;
		cout << "6.    Remove user" << endl;
		cout << "0.    Exit" << endl;
		int opt;
		cin >> opt;
		if (opt == 1)
		{
			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - NAME EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the name of " << user.name << endl;
			cout << endl;
			cout << "Name: " << user.name << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Change to: ";
			char newname[32];
			cin >> newname;
			cout << "Are you sure to store it?" << endl;
			char choice1;
			cin >> choice1;
			if (choice1 == 'y' || choice1 == 'Y')
			{
				strcpy_s(user.name, newname);
				storeUserInfo(user);
				cout << "Successful" << endl;
				Sleep(1000);
			}
			else
			{
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1000);
			}
		}
		else if (opt == 2)
		{
			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - USER TYPE EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the name of " << user.name << endl;
			cout << endl;
			cout << "Type: " << rtnType(user.type) << "(" << user.type << ")" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Choose the type below" << endl;
			cout << "--------------------------------------------------------------" << endl;
			cout << "|  1.Administrator     2.Meter Reader  3.Charger             |" << endl;
			cout << "|  4.Enterprice User   5.Urban User    6.Common Rural User   |" << endl;
			cout << "|  7.Rural User in Poverty                                   |" << endl;
			cout << "--------------------------------------------------------------" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Change to: ";
			int user_tpy;
			while (!(user_tpy >= 1 && user_tpy <= 7))
			{
				cout << "Invalid Input" << endl;
				cout << "User type: ";
				cin >> user_tpy;
			}

			cout << "USER MANAGEMENT - EDIT USER DETAIL - USER TYPE EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "The new user type of" << user.name << " is: " << rtnType(user.type) << "(" << user.type << ")" << endl;
			cout << endl;
			cout << "Are you sure to store it?" << endl;
			char choice2;
			cin >> choice2;
			if (choice2 == 'y' || choice2 == 'Y')
			{
				user.type = user_tpy;
				storeUserInfo(user);
				cout << "Successful" << endl;
				Sleep(1000);
			}
			else
			{
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1000);
			}
		}
		else if (opt == 3)
		{
			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ID EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the ID of " << user.name << endl;
			cout << endl;
			cout << "ID: " << user.name << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Change to: ";
			char newID[18];
			cin >> newID;
			while (strlen(newID) != 18)
			{
				cout << "Invalid ID" << endl;
				cout << "ID: ";
				cin >> newID;
			}
			cout << "Are you sure to store it?" << endl;
			char choice3;
			cin >> choice3;
			if (choice3 == 'y' || choice3 == 'Y')
			{
				strcpy_s(user.id, newID);
				storeUserInfo(user);
				cout << "Successful" << endl;
				Sleep(1000);
			}
			else
			{
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1000);
			}
		}
		else if (opt == 4)
		{
			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the ID of " << user.name << endl;
			cout << endl;
			cout << "Original Address: " << user.address.unit << "-" << user.address.level << "-" << user.address.room
				<< " " << user.address.estate << ", " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "City: ";
			cin >> user.address.city;

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the ID of " << user.name << endl;
			cout << endl;
			cout << "Address: " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "District: ";
			cin >> user.address.district;

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the ID of " << user.name << endl;
			cout << endl;
			cout << "Address: " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Street: ";
			cin >> user.address.street;

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the ID of " << user.name << endl;
			cout << endl;
			cout << "Address: " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Estate: ";
			cin >> user.address.estate;

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the ID of " << user.name << endl;
			cout << endl;
			cout << "Address: "<< " " << user.address.estate << ", " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Unit: ";
			cin >> user.address.unit;

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the ID of " << user.name << endl;
			cout << endl;
			cout << "Address: " << user.address.unit << "-" << " " << user.address.estate << ", "
			<< user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Level: ";
			cin >> user.address.level;

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the ID of " << user.name << endl;
			cout << endl;
			cout << "Address: " << user.address.unit << "-" << user.address.level 
				<< " " << user.address.estate << ", " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Room: ";
			cin >> user.address.room;
			cout << "Are you sure to store it?" << endl;
			char choice4;
			cin >> choice4;
			if (choice4 == 'y' || choice4 == 'Y')
			{
				storeUserInfo(user);
				cout << "Successful" << endl;
				Sleep(1000);
			}
			else
			{
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1000);
			}
			
		}
	}
}
void adminEditUsers()
{
	int exit = 0;
	while (!exit)
	{
		system("cls");
		getTotalUser();
		cout << "USER MANAGEMENT" << endl;
		cout << "======================================================================" << endl;
		cout << "Total users: " << totalUser << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "Input the user's serial number that you wish to see in detail" << endl;
		cout << "No. ";
		int userno;
		cin >> userno;
		if (validUser(userno))
		{
			adminEditUser_Detail(userno);
		}
		else
		{
			cout << "Invalid number, please try again";
			Sleep(0100);
		}
	}
}
void adminListUsers()
{
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
		cout << setw(16) << user.No << " " << setw(16) << user.name << "  " << setw(21) << type << " " << setw(18) << user.id << '\t'
			<< user.address.unit << '-' << user.address.level << '-' << user.address.room
			<< ", " << user.address.estate << ", " << user.address.street << ", " << user.address.district
			<< ", " << user.address.city << setw(32) << user.password << endl;	
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
		cout << "3. Assign Meter Reader tasks" << endl;
		cout << "0. Exit" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1: adminListUsers(); break;
		case 2: adminEditUsers(); break;
		case 0: exitflag = 1;
			break;
		}
	}
}
void AdminDash(int username)
{
	userinfo me;
	me = getUserInfo(username);
	int exitflag = 0;
	while (!exitflag)
	{
		system("cls");
		cout << "DASHBOARD" << endl;
		cout << "==============================================" << endl;
		cout << me.name << ", greetings!" << endl;
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





bool samestr(char* s1, char* s2)
{
	if (strlen(s1) != strlen(s2))
		return false;
	for (int i = 0; i < strlen(s1); i++)
	{
		if (s1[i] != s2[i])
			return false;
	}
	return true;
}

// Login
int validPassword(int username, char userPass[])
{
	userinfo user;
	user = getUserInfo(username);
	if (samestr(user.password, userPass))
		return 1;
	return 0;
}
int getUserType(int username)
{
	userinfo user;
	user = getUserInfo(username);
	return user.type;
}
void loginGuide(int username)
{
	userinfo user;
	user = getUserInfo(username);
	switch(user.type)
	{
	case 1: AdminDash(username); break;
	case 2: MRDash(username); break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7: break;
	}
}
void login()
{
	int exit = 0;
	while (!exit)
	{
		system("cls");
		cout << "WELCOME TO ELECTRICITY BILLING SYSTEM" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "To start, please login" << endl;
		cout << "Username: ";
		int username;
		cin >> username;
		cout << "Password: ";
		char userPass[32];
		cin >> userPass;
		if (validUser(username))
		{
			if (validPassword(username, userPass))
			{
				exit = 1;
				loginGuide(username);
			}
			else
			{
				system("cls");
				cout << "WELCOME TO ELECTRICITY BILLING SYSTEM" << endl;
				cout << "----------------------------------------------" << endl;
				cout << "**********************************************" << endl;
				cout << "*     Invalid password, Please try again     *" << endl;
				cout << "**********************************************" << endl;
				Sleep(1000);
			}
		}
		else
		{
			system("cls");
			cout << "WELCOME TO ELECTRICITY BILLING SYSTEM" << endl;
			cout << "----------------------------------------------" << endl;
			cout << "**********************************************" << endl;
			cout << "*     Invalid username, Please try again     *" << endl;
			cout << "**********************************************" << endl;
			Sleep(1000);
		}
	}
}

int main()
{
	login();
}