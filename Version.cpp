#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <iomanip>
#include <Windows.h>
using namespace std;


// Basic definiations and functions
int totalUser = 0;
char FLOC_FILEFOLDER[18] = { "D:\\Billing System" };
string FLOC_USERBASICINFO = "D:\\Billing System\\userbasicinfo.dat";
string FLOC_EDITUSERINFO_TEMP = "D:\\Billing System\\temp_userbasicinfo.dat";
string FLOC_SYSSET = "D:\\Billing System\\SystemSettings.dat";
string FLOC_BILLDETAIL = "D:\\Billing System\\bill_detail.dat";
string FLOC_MRINFO = "D:\\Billing System\\bill_detail.dat";
string FLOC_EDITMRINFO_TEMP = "D:\\Billing System\\temp_mrinfo.dat";
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
	char id[19];
	int type;
	add address;
	char password[32];
}userinfo;
typedef struct userbill
{
	bool star;
	bool read;
	int case_no;
	userinfo user_record;
	date date_record;
	date date_pay;
	int bill_amount;
	bool payment;
}userbill;
typedef struct MRdef
{
	int No;
	char name[32];
	add address_responsible;
}MRdef;



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
void getString(string& s)
{
	cin.get();
	getline(cin, s);
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
void dotDotDot(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << '.';
		Sleep(0700);
	}
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
	while (temp.read((char*)&use, sizeof(userinfo)))
	{
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
	case 4: typ = "Enterprise User"; break;
	case 5: typ = "Urban User"; break;
	case 6: typ = "Common Rural User"; break;
	case 7: typ = "Rural User in Poverty"; break;
	}
	return typ;
}
int getUserType(int username)
{
	userinfo user;
	user = getUserInfo(username);
	return user.type;
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
	userinfo tempUserInfo;
	fstream origin;
	fstream temp;
	origin.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::out);
	while (origin.read((char*)&tempUserInfo, sizeof(userinfo)))
	{
		if (tempUserInfo.No == use.No)
			temp.write((char*)&use, sizeof(userinfo));
		else
			temp.write((char*)&tempUserInfo, sizeof(userinfo));
	}
	temp.close();
	origin.close();
	origin.open(FLOC_USERBASICINFO, ios::binary | ios::out);
	temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::in);
	while (temp.read((char*)&tempUserInfo, sizeof(userinfo)))
	{
		origin.write((char*)&tempUserInfo, sizeof(userinfo));
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
	while (origin.read((char*)&tmpInfo, sizeof(userinfo)))
	{
		if (tmpInfo.No == use.No)
			continue;
		else
			temp.write((char*)&tmpInfo, sizeof(userinfo));
	}
	temp.close();
	origin.close();
	origin.open(FLOC_USERBASICINFO, ios::binary | ios::out);
	temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::in);
	while (temp.read((char*)&tmpInfo, sizeof(userinfo)))
	{
		origin.write((char*)&tmpInfo, sizeof(userinfo));
	}
	temp.close();
	origin.close();
}

// System
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
	strcpy_s(rootUser.address.unit, "0");
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
	floc.open("E:\\Billing System\\SystemSettings.dat", ios::binary | ios::in);
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
void userInfoImport(string location)
{
	fstream fromfile;
	fromfile.open(location, ios::binary | ios::in);
	if (!fromfile)
	{
		cout << "Can't find the file in the location provided." << endl;
		fromfile.close();
		Sleep(1000);
	}
	else
	{
		fstream tofile;
		userinfo former;
		former.No = genUserNo();
		former.No--;
		tofile.open(FLOC_USERBASICINFO, ios::binary | ios::app | ios::out);
		userinfo user;
		while(fromfile.read((char*)&user, sizeof(userinfo)))
		{
			user.No = former.No + 1;
			tofile.write((char*)&user, sizeof(userinfo));
			former.No = user.No;
		}
		cout << "Success" << endl;
		getTotalUser();
		Sleep(1000);
	}
}




// Apple changes - meter reader info
void storeMRInfo(MRdef mr)
{
	MRdef mrtmp;
	fstream temp;
	temp.open(FLOC_MRINFO, ios::binary | ios::app | ios::out);
	temp.write((char*)&mr, sizeof(MRdef));
	temp.close();
}
void changeMRInfo(MRdef mr)
{
	MRdef mrtmp;
	fstream origin;
	fstream temp;
	origin.open(FLOC_MRINFO, ios::binary | ios::in);
	temp.open(FLOC_EDITMRINFO_TEMP, ios::binary | ios::out);
	while (origin.read((char*)&mrtmp, sizeof(MRdef)))
	{
		if (mrtmp.No == mr.No)
			temp.write((char*)&mr, sizeof(MRdef));
		else
			temp.write((char*)&mrtmp, sizeof(MRdef));
	}
	temp.close();
	origin.close();
	origin.open(FLOC_USERBASICINFO, ios::binary | ios::out);
	temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::in);
	while (temp.read((char*)&mrtmp, sizeof(MRdef)))
	{
		origin.write((char*)&mrtmp, sizeof(MRdef));
	}
	temp.close();
	origin.close();
}
void deleteMRInfo(MRdef mr)
{
	MRdef mrtmp;
	fstream origin;
	fstream temp;
	origin.open(FLOC_MRINFO, ios::binary | ios::in);
	temp.open(FLOC_EDITMRINFO_TEMP, ios::binary | ios::out);
	while (origin.read((char*)&mrtmp, sizeof(MRdef)))
	{
		if (mrtmp.No == mr.No)
			continue;
		else
			temp.write((char*)&mrtmp, sizeof(userinfo));
	}
	temp.close();
	origin.close();
	origin.open(FLOC_MRINFO, ios::binary | ios::out);
	temp.open(FLOC_EDITMRINFO_TEMP, ios::binary | ios::in);
	while (temp.read((char*)&mrtmp, sizeof(MRdef)))
	{
		origin.write((char*)&mrtmp, sizeof(MRdef));
	}
	temp.close();
	origin.close();
}


// Meter Reader Features
int genCaseNo()
{
	fstream tmpf;
	userbill tmp;
	tmpf.open(FLOC_BILLDETAIL, ios::in | ios::app | ios::binary);
	int size = sizeof(userinfo);
	tmpf.seekg(-size, ios::end);
	tmpf.read((char*)&tmp, sizeof(userinfo));
	return (tmp.case_no + 1);
}

// Get work process
int getStreetRead(int username, char* st)
{
	fstream tmp;
	userbill user;
	int unread = 0;
	tmp.open(FLOC_BILLDETAIL, ios::binary | ios::app | ios::in);
	while (tmp.read((char*)&user, sizeof(userbill)))
	{
		if (samestr(user.user_record.address.street, st))
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
	while (tmp.read((char*)&user, sizeof(userbill)))
	{
		if (samestr(user.user_record.address.street, street))
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
	while (tmp.read((char*)&user, sizeof(userbill)))
	{
		if (samestr(user.user_record.address.estate, est))
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
	while (tmp.read((char*)&user, sizeof(userbill)))
	{
		if (samestr(user.user_record.address.estate, est))
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
	while (tmp.read((char*)&user, sizeof(userbill)))
	{
		if (samestr(user.user_record.address.unit, unit))
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
	while (tmp.read((char*)&user, sizeof(userbill)))
	{
		if (samestr(user.user_record.address.unit, unit))
		{
			unread++;
		}
	}
	tmp.close();
	return unread;
}


// Meter Reader_Menu
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
	string place;
	do
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
		getString(place);
		cout << "not available" << endl;
	} while (place != "-1");

}
void MRDash(int username)
{
	userinfo me;
	me = getUserInfo(username);
	int userread = 0;
	int totaluser = 10;
	int opt;
	do
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
		cout << "0. Logout" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: MROverview();  break;
		case 2:; break;
		case 0: 			
			system("cls");
			cout << "Thanks!" << endl;
			cout << endl;
			cout << "Logging out";
			dotDotDot(3);
			return;
		default: cout << "Invalid input, please try again" << endl;
		}
	} while (opt != 0);
	system("cls");
	cout << "Thanks!" << endl;
	cout << endl;
	cout << "Exiting";
	dotDotDot(3);
}



// Admin Features
void setdefaultPassword(char id[], char passput[])
{
	int i;
	for (i = 0; i < 6; i++)
	{
		passput[i] = id[17 - i];
	}
	passput[i] = '\0';
}


// System Settings
void adminSystemSettings_StorageSettings_menu()
{
	int opt;
	do
	{
		system("cls");
		cout << "SYSTEM SETTINGS - STORAGE SETTINGS" << endl;
		cout << "==============================================" << endl;
		cout << "Menu:" << endl;
		cout << "1. Change temp file location" << endl;
		cout << "2. Change user basic info location" << endl;
		cout << "0. Exit" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1:
			system("cls");
			cout << "SYSTEM SETTINGS - STORAGE SETTINGS" << endl;
			cout << "==============================================" << endl;
			cout << "You are changing the temp file location" << endl;
			cout << "Current: temp file is stored in: ";
			cout << FLOC_EDITUSERINFO_TEMP << endl;
			cout << "----------------------------------------------" << endl;
			cout << "Enter your new file path:" << endl;
			cin >> FLOC_EDITUSERINFO_TEMP;
			system("cls");
			cout << "SYSTEM SETTINGS - STORAGE SETTINGS" << endl;
			cout << "==============================================" << endl;
			cout << "Path changed" << endl;
			cout << "Current: temp file is stored in: ";
			cout << FLOC_EDITUSERINFO_TEMP << endl;
			cout << "----------------------------------------------" << endl;
			break;
		case 2:
			system("cls");
			cout << "SYSTEM SETTINGS - STORAGE SETTINGS" << endl;
			cout << "==============================================" << endl;
			cout << "You are changing the user basic info file location" << endl;
			cout << "Current: temp file is stored in: ";
			cout << FLOC_USERBASICINFO << endl;
			cout << "----------------------------------------------" << endl;
			cout << "Enter your new file path:" << endl;
			cin >> FLOC_USERBASICINFO;
			system("cls");
			cout << "SYSTEM SETTINGS - STORAGE SETTINGS" << endl;
			cout << "==============================================" << endl;
			cout << "Path changed" << endl;
			cout << "Current: temp file is stored in: ";
			cout << FLOC_USERBASICINFO << endl;
			cout << "----------------------------------------------" << endl;
			break;
		case 0:
			return;
		default: cout << "Invalid input, please try again" << endl;
			cin >> opt;
		}
	} while (opt != 0);
}
void adminSystemSettings_menu()
{
	int opt;
	do
	{
		system("cls");
		cout << "SYSTEM SETTINGS" << endl;
		cout << "==============================================" << endl;
		cout << "Menu:" << endl;
		cout << "1. Change password" << endl;
		cout << "2. Change file location" << endl;
		cout << "3. Import user basic information from file" << endl;
		cout << "4. Reset database" << endl;
		cout << "0. Exit" << endl;
		cin >> opt;
		string fileLocation;
		switch (opt)
		{
		case 1:
			break;
		case 2:
			adminSystemSettings_StorageSettings_menu();
			break;
		case 3:
			system("cls");
			cout << "SYSTEM SETTINGS - IMPORT USER INFORMATION" << endl;
			cout << "==============================================" << endl;
			cout << "You wish to import from:" << endl;
			cout << "----------------------------------------------" << endl;
			cout << "Location: ";
			getString(fileLocation);
			system("cls");
			cout << "SYSTEM SETTINGS - IMPORT USER INFORMATION" << endl;
			cout << "==============================================" << endl;
			cout << "You wish to import from:" << fileLocation << endl;
			cout << "----------------------------------------------" << endl;
			cout << "Are you sure to store it" << endl;
			cout << "y/n: ";
			char opt;
			cin >> opt;
			if (opt == 'y' || opt == 'Y')
			{
				userInfoImport(fileLocation);
				break;
			}
			else
			{
				cout << "cancelled";
				Sleep(1000);
			}
		case 4:
			system("cls");
			cout << "ARE YOU SURE?" << endl;
			cout << "This will wipe out all user data" << endl;
			cout << "y/n : ";
			char opt1;
			cin >> opt1;
			if (opt1 == 'y' || opt1 == 'Y')
				resetDatabase();
			break;
		case 0: return;
		default: cout << "Invalid input, please try again" << endl;
		}
	} while (opt != 0);
}


// Admin_Menu
void MRSetup(int username)
{
	userinfo newMRinfo;
	newMRinfo = getUserInfo(username);
	MRdef newMR;
	newMR.No = newMRinfo.No;
	system("cls");
	cout << "USER SETUP - MATER READER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "You just set up a new meter reader, please initialise the settings " << endl;
	cout << "Name: " << newMRinfo.name << endl;
	cout << "User Number: " << newMRinfo.No << endl;
	cout << endl;
	cout << "Region responsible: " << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "City: ";
	getString(newMR.address_responsible.city);

	system("cls");
	cout << "USER SETUP - MATER READER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "You just set up a new meter reader, please initialise the settings " << endl;
	cout << "Name: " << newMRinfo.name << endl;
	cout << "User Number: " << newMRinfo.No << endl;
	cout << endl;
	cout << "Region responsible: " << newMR.address_responsible.city << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "District: ";
	getString(newMR.address_responsible.district);

	system("cls");
	cout << "USER SETUP - MATER READER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "You just set up a new meter reader, please initialise the settings" << endl;
	cout << "Name: " << newMRinfo.name << endl;
	cout << "User Number: " << newMRinfo.No << endl;
	cout << endl;
	cout << "Region responsible: " << newMR.address_responsible.city << newMR.address_responsible.district << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Street: ";
	getString(newMR.address_responsible.street);

	system("cls");
	cout << "USER SETUP - MATER READER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "You have set up a new meter reader, there is the derail: " << endl;
	cout << "Name: " << newMRinfo.name << endl;
	cout << "User Number: " << newMRinfo.No << endl;
	cout << endl;
	cout << "Region responsible: " << newMR.address_responsible.city << newMR.address_responsible.district << newMR.address_responsible.street << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Are you sure to store it" << endl;
	cout << "y/n: ";
	char opt;
	cin >> opt;
	if (opt == 'y' || opt == 'Y')
	{
		storeMRInfo(newMR);
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
	if (newUser.type == 2)
	{
		MRSetup(newUser.No);
	}

}
void adminEditUser_Detail(int username)
{
	int opt;
	do
	{
		userinfo user;
		user = getUserInfo(username);
		system("cls");
		getTotalUser();
		cout << "USER MANAGEMENT - EDIT USER DETAIL" << endl;
		cout << "======================================================================" << endl;
		cout << "Detail of " << user.name << endl;
		cout << endl;
		cout << "1. Name: " << user.name << endl;
		cout << "2. Type: " << rtnType(user.type) << "(" << user.type << ")" << endl;
		cout << "3.  User Number: " << user.No << endl;
		cout << "4. ID: " << user.id << endl;
		cout << "5. Address: " << user.address.unit << "-" << user.address.level << "-" << user.address.room
			<< " " << user.address.estate << ", " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
		cout << "6. Password: " << user.password << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "What do you want to change about the user " << user.name << endl;
		cout << "1 - 6 Change the corresponding information" << endl;
		cout << "7.    Remove user" << endl;
		cout << "0.    Exit" << endl;
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
			getString(newname);
			cout << "Are you sure to store it?" << endl;
			char choice1;
			cin >> choice1;
			if (choice1 == 'y' || choice1 == 'Y')
			{
				strcpy_s(user.name, newname);
				changeUserInfo(user);
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
			int user_typ;
			cin >> user_typ;
			while (!(user_typ >= 1 && user_typ <= 7))
			{
				cout << "Invalid Input" << endl;
				cout << "User type: ";
				cin >> user_typ;
			}

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - USER TYPE EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "The new user type of" << user.name << " is: " << rtnType(user_typ) << "(" << user_typ << ")" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << endl;
			cout << "Are you sure to store it?" << endl;
			char choice2;
			cin >> choice2;
			if (choice2 == 'y' || choice2 == 'Y')
			{
				user.type = user_typ;
				changeUserInfo(user);
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
			cout << "USER MANAGEMENT - EDIT USER DETAIL - NUMBER EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the number of " << user.name << endl;
			cout << endl;
			cout << "Number: " << user.No << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Change to: ";
			int newNo;
			cin >> newNo;
			
			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - NUMBER EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "The new type of" << user.name << " is: " << newNo << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Are you sure to store it?" << endl;
			char choice3;
			cin >> choice3;
			if (choice3 == 'y' || choice3 == 'Y')
			{
				user.No = newNo;
				changeUserInfo(user);
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
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ID EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the ID of " << user.name << endl;
			cout << endl;
			cout << "ID: " << user.id << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Change to: ";
			char newID[18];
			getString(newID);
			while (strlen(newID) != 18)
			{
				cout << "Invalid ID" << endl;
				cout << "ID: ";
				getString(newID);
			}
			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ID EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "The new ID of" << user.name << " is: " << newID << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Are you sure to store it?" << endl;
			char choice3;
			cin >> choice3;
			if (choice3 == 'y' || choice3 == 'Y')
			{
				strcpy_s(user.id, newID);
				changeUserInfo(user);
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
		else if (opt == 5)
		{
			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the address of " << user.name << endl;
			cout << endl;
			cout << "Original Address: " << user.address.unit << "-" << user.address.level << "-" << user.address.room
				<< " " << user.address.estate << ", " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "City: ";
			getString(user.address.city);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the address of " << user.name << endl;
			cout << endl;
			cout << "Address: " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "District: ";
			getString(user.address.district);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the address of " << user.name << endl;
			cout << endl;
			cout << "Address: " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Street: ";
			getString(user.address.street);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the address of " << user.name << endl;
			cout << endl;
			cout << "Address: " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Estate: ";
			getString(user.address.estate);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the address of " << user.name << endl;
			cout << endl;
			cout << "Address: "<< " " << user.address.estate << ", " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Unit: ";
			getString(user.address.unit);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the address of " << user.name << endl;
			cout << endl;
			cout << "Address: " << user.address.unit << "-" << " " << user.address.estate << ", "
			<< user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Level: ";
			cin >> user.address.level;

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Editing the address of " << user.name << endl;
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
				changeUserInfo(user);
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
		else if(opt == 6)
		{
		system("cls");
		cout << "USER MANAGEMENT - EDIT USER DETAIL - PASSWORD CHANGE" << endl;
		cout << "======================================================================" << endl;
		cout << "Editing the name of " << user.name << endl;
		cout << endl;
		cout << "Password: " << user.password << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "Change to: ";
		char newPassword[32];
		getString(newPassword);
		system("cls");
		cout << "USER MANAGEMENT - EDIT USER DETAIL - PASSWORD CHANGE" << endl;
		cout << "======================================================================" << endl;
		cout << "The new password of" << user.name << " is: " << newPassword << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "Are you sure to store it?" << endl;
		char choice4;
		cin >> choice4;
		if (choice4 == 'y' || choice4 == 'Y')
		{
			strcpy_s(user.password, newPassword);
			changeUserInfo(user);
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
		else if (opt == 7)
		{
			cout << "USER MANAGEMENT - REMOVE USER" << endl;
			cout << "======================================================================" << endl;
			cout << "You are removing user: " << user.name << "; user number: " << user.No;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Are you sure?" << endl;
			char choice6;
			cin >> choice6;
			if (choice6 == 'y' || choice6 == 'Y')
			{
				deleteUserInfo(user);
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
		else if (opt == 0)
		{
		return;
		}
	}while (opt != 0);
}
void adminEditUsers()
{
	int userno;
	do
	{
		system("cls");
		cout << "USER MANAGEMENT - USER LIST" << endl;
		cout << "============================================================================================================================================================================================================" << endl;
		cout << "Number                Name	                Type                      ID                                         Address                                                                    Password" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		userinfo user;
		fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
		while (readUser.read((char*)&user, sizeof(userinfo)))
		{
			string type;
			type = rtnType(user.type);
			cout << setw(11) << right << setfill('0') << user.No << '\t'
				<< setw(25) << left << setfill(' ') << user.name
				<< setw(25) << left << type
				<< setw(20) << left << user.id << '\t'
				<< setw(5) << right << setfill(' ') << user.address.unit << '-'
				<< setw(3) << right << setfill('0') << user.address.level << '-'
				<< setw(4) << right << setfill('0') << user.address.room << ", "
				<< setw(15) << setfill(' ') << user.address.estate << ", "
				<< setw(25) << user.address.street << ", "
				<< setw(15) << user.address.district << ", "
				<< setw(15) << user.address.city << '\t'
				<< setw(16) << right << user.password << endl;
		}
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Input the user's serial number that you wish to see in detail (Input -1 to exit)" << endl;
		cout << "No. ";
		cin >> userno;
		if (userno == -1)
		{
			return;
		}
		else if (validUser(userno))
		{
			adminEditUser_Detail(userno);
		}
		else
		{
			cout << "Invalid number, please try again";
			Sleep(0100);
		}
	} while (userno != -1);
}
void adminListUsers()
{
	system("cls");
	cout << "USER MANAGEMENT - USER LIST" << endl;
	cout << "============================================================================================================================================================================================================" << endl;
	cout << "Number                Name	                Type                      ID                                         Address                                                                    Password" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	userinfo user;
	fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
	while (readUser.read((char*)&user, sizeof(userinfo)))
	{
		string type;
		type = rtnType(user.type);
		cout << setw(11) << right << setfill('0') << user.No << '\t'
			<< setw(25) << left << setfill(' ') << user.name
			<< setw(25) << left << type
			<< setw(20) << left << user.id  << '\t'
			<< setw(5) << right << setfill(' ') << user.address.unit << '-'
			<< setw(3) << right << setfill('0') << user.address.level << '-'
			<< setw(4) << right << setfill('0') << user.address.room << ", "
			<< setw(15) << setfill(' ') << user.address.estate << ", "
			<< setw(25) << user.address.street << ", "
			<< setw(15) << user.address.district << ", "
			<< setw(15) << user.address.city << '\t'
			<< setw(16) << right << user.password << endl;
	}
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	system("pause");
}
void userManage()
{
	int opt;
	do
	{
		system("cls");
		getTotalUser();
		cout << "USER MANAGEMENT" << endl;
		cout << "======================================================================" << endl;
		cout << "Total users: " << totalUser << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "Menu: " << endl;
		cout << "1. Edit user information" << endl;
		cout << "2. List users" << endl;
		cout << "3. Assign Meter Reader tasks" << endl;
		cout << "0. Exit" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: adminEditUsers(); break;
		case 2: adminListUsers(); break;
		case 0: return;
		default: cout << "Invalid Input" << endl;
		}
	} while (opt != 0);
}
void AdminDash(int username)
{
	userinfo me;
	me = getUserInfo(username);
	int opt;
	do
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
		cout << "2. User Registration" << endl;
		cout << "3. System Settings" << endl;
		cout << "0. Logout" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: userManage(); break;
		case 2: generateUser(); break;
		case 3: adminSystemSettings_menu(); break;
		case 0:
			system("cls");
			cout << "Thanks!" << endl;
			cout << endl;
			cout << "Logging out";
			dotDotDot(3);
			return;
		default: cout << "Invalid input, please try again" << endl;
		}
	} while (opt != 0);
}
void MRManage()
{
	cout << "USER MANAGEMENT - MATER READER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "Not available" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	
}


//User_Menu
void userEditBasicInfo(int username)
{
	int opt;
	do
	{
		userinfo me;
		me = getUserInfo(username);
		system("cls");
		getTotalUser();
		cout << "USER SETTINGS - BASIC INFORMATION EDIT" << endl;
		cout << "======================================================================" << endl;
		cout << "Hi, " << me.name << ", Here are things about you:" << endl;
		cout << endl;
		cout << "1. Name: " << me.name << endl;
		cout << "#. Type: " << rtnType(me.type) << "(" << me.type << ")" << endl;
		cout << "#. User Number: " << me.No << endl;
		cout << "2. ID: " << me.id << endl;
		cout << "3. Address: " << me.address.unit << "-" << me.address.level << "-" << me.address.room
			<< " " << me.address.estate << ", " << me.address.street << ", " << me.address.district << ", " << me.address.city << endl;
		cout << "4. Password: " << me.password << endl;
		cout << "----------------------------------------------------------------------" << endl;
		cout << "What do you want to change about you: " << endl;
		cout << "1 - 4 Change the corresponding information" << endl;
		cout << "5.    Deactivate account" << endl;
		cout << "0.    Exit" << endl;
		cin >> opt;
		if (opt == 1)
		{
			system("cls");
			cout << "USER SETTINGS - BASIC INFORMATION EDIT - NAME EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing the name from:" << me.name << endl;
			cout << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "To: ";
			char newname[32];
			getString(newname);
			cout << "Are you sure to store it?" << endl;
			char choice1;
			cin >> choice1;
			if (choice1 == 'y' || choice1 == 'Y')
			{
				strcpy_s(me.name, newname);
				changeUserInfo(me);
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
			cout << "USER SETTINGS - EDIT BASIC INFORMATION - ID EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing your ID from: " << me.id << endl;
			cout << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "To: ";
			char newID[18];
			getString(newID);
			while (strlen(newID) != 18)
			{
				cout << "Invalid ID" << endl;
				cout << "ID: ";
				getString(newID);
			}
			system("cls");
			cout << "USER SETTINGS - EDIT BASIC INFORMATION - ID EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "Your new ID is: " << newID << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Are you sure to store it?" << endl;
			char choice3;
			cin >> choice3;
			if (choice3 == 'y' || choice3 == 'Y')
			{
				strcpy_s(me.id, newID);
				changeUserInfo(me);
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
			cout << "USER SETTINGS - EDIT BASIC INFORMATION - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing your address: " <<endl;
			cout << endl;
			cout << "Original Address: " << me.address.unit << "-" << me.address.level << "-" << me.address.room
				<< " " << me.address.estate << ", " << me.address.street << ", " << me.address.district << ", " << me.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "City: ";
			getString(me.address.city);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing your address: " << endl;
			cout << endl;
			cout << "Address: " << me.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "District: ";
			getString(me.address.district);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing your address: " << endl;
			cout << endl;
			cout << "Address: " << me.address.district << ", " << me.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Street: ";
			getString(me.address.street);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing your address: " << endl;
			cout << endl;
			cout << "Address: " << me.address.street << ", " << me.address.district << ", " << me.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Estate: ";
			getString(me.address.estate);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing your address: " << endl;
			cout << endl;
			cout << "Address: " << " " << me.address.estate << ", " << me.address.street << ", " << me.address.district << ", " << me.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Unit: ";
			getString(me.address.unit);

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing your address: " << endl;
			cout << endl;
			cout << "Address: " << me.address.unit << "-" << " " << me.address.estate << ", "
				<< me.address.street << ", " << me.address.district << ", " << me.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Level: ";
			cin >> me.address.level;

			system("cls");
			cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing your address: " << endl;
			cout << endl;
			cout << "Address: " << me.address.unit << "-" << me.address.level
				<< " " << me.address.estate << ", " << me.address.street << ", " << me.address.district << ", " << me.address.city << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Room: ";
			cin >> me.address.room;
			cout << "Are you sure to store it?" << endl;
			char choice4;
			cin >> choice4;
			if (choice4 == 'y' || choice4 == 'Y')
			{
				changeUserInfo(me);
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
			cout << "USER SETTINGS - EDIT BASIC INFORMATION - PASSWORD CHANGE" << endl;
			cout << "======================================================================" << endl;
			cout << "You are changing your password" << endl;
			cout << endl;
			cout << "Password: " << me.password << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Change to: ";
			char newPassword[32];
			getString(newPassword);
			system("cls");
			cout << "USER SETTINGS - EDIT BASIC INFORMATION - PASSWORD CHANGE" << endl;
			cout << "======================================================================" << endl;
			cout << "Your new password" << " is: " << newPassword << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Are you sure to store it?" << endl;
			char choice4;
			cin >> choice4;
			if (choice4 == 'y' || choice4 == 'Y')
			{
				strcpy_s(me.password, newPassword);
				changeUserInfo(me);
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
		else if (opt == 5)
		{
		system("cls");
			cout << "USER SETTINGS - EDIT BASIC INFORMATION - DEACTIVATE ACCOUNT" << endl;
			cout << "======================================================================" << endl;
			cout << "You account will be removed permanently" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Are you sure?" << endl;
			char choice6;
			cin >> choice6;
			if (choice6 == 'y' || choice6 == 'Y')
			{
				deleteUserInfo(me);
				cout << "Successful" << endl;
				Sleep(1000);
				return;
			}
			else
			{
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1000);
			}
		}
		else if (opt == 0)
		{
		return;
		}
		else
		{
		cout << "Invalid Input" << endl;
		}
	}while (opt != 0);
}
void userDash(int username)
{
	userinfo me;
	me = getUserInfo(username);
	int opt;
	do
	{
		system("cls");
		cout << "DASHBOARD" << endl;
		cout << "==============================================" << endl;
		cout << me.name << ", greetings!" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Here is your basic information: " << endl;
		cout << endl;
		cout << "Name: " << me.name << endl;
		cout << "Type: " << rtnType(me.type) << "(" << me.type << ")" << endl;
		cout << "Number: " << me.No << endl;
		cout << "ID: " << me.id << endl;
		cout << "Address: " << me.address.unit << "-" << me.address.level << "-" << me.address.room
			<< " " << me.address.estate << ", " << me.address.street << ", " << me.address.district << ", " << me.address.city << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Menu:" << endl;
		cout << "1. Edit your information" << endl;
		cout << "2. Check your bill rate" << endl;
		cout << "3. Check history usage and billing" << endl;
		cout  << endl;
		cout << "0. Logout" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: userEditBasicInfo(me.No); break;
		case 2: cout << "Not available" << endl; break;
		case 3: cout << "Not avaliable"; break;
		case 0:
			system("cls");
			cout << "Thanks!" << endl;
			cout << endl;
			cout << "Logging out";
			dotDotDot(3);
			return;
		default: cout << "Invalid input, please try again" << endl;
		}
	} while (opt != 0);
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
void loginGuide(int username)
{
	userinfo user;
	user = getUserInfo(username);
	switch(user.type)
	{
	case 1: AdminDash(username); break;
	case 2: MRDash(username); break;
	case 3: cout << "Not available" << endl; break;
	case 4:
	case 5:
	case 6:userDash(username); break;
	case 7: break;
	}
}
void login()
{
	int username;
	do
	{
		system("cls");
		cout << "SYSTEM - LOGIN" << endl;
		cout << "==============================================" << endl;
		cout << "To start, please login" << endl;
		cout << endl;
		cout << "Username: ";
		cin >> username;
		if (validUser(username))
		{
			cout << "Password: ";
			char userPass[32];
			cin >> userPass;
			if (validPassword(username, userPass))
			{
				loginGuide(username);
			}
			else
			{
				system("cls");
				cout << "SYSTEM - LOGIN ERROR" << endl;
				cout << "==============================================" << endl;
				cout << endl;
				cout << "**********************************************" << endl;
				cout << "*     Invalid password, Please try again     *" << endl;
				cout << "**********************************************" << endl;
				Sleep(1000);
			}
		}
		else
		{
			system("cls");
			cout << "SYSTEM - LOGIN ERROR" << endl;
			cout << "==============================================" << endl;
			cout << endl;
			cout << "**********************************************" << endl;
			cout << "*     Invalid username, Please try again     *" << endl;
			cout << "**********************************************" << endl;
			Sleep(1000);
		}
	} while (username >= 0);
}



void checkAndGenerate()
{
	fstream userinfofile;
	userinfofile.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	if (!userinfofile)
	{
		_mkdir(FLOC_FILEFOLDER);
		resetDatabase();
		cout << "*************************************************" << endl;
		cout << "* Hi, Welcome to the electricity billing system *" << endl;
		cout << "*************************************************" << endl;
		Sleep(1000);
		system("cls");
		cout << "*************************************************" << endl;
		cout << "*      We are setting up everything for you     *" << endl;
		cout << "*************************************************" << endl;
		Sleep(1000);
		system("cls");
		cout << "*************************************************" << endl;
		cout << "*                  Almost done                  *" << endl;
		cout << "*************************************************" << endl;
		Sleep(1000);
		system("cls");
		cout << "***********************************************************************" << endl;
		cout << "* You are the administrator, use the following information to sign in *" << endl;
		cout << "* Username: 0                                                         *" << endl;
		cout << "* Password: root                                                      *" << endl;
		cout << "***********************************************************************" << endl;
		system("pause");
		system("cls");
		cout << "*********************************************" << endl;
		cout << "*                  Thanks!                  *" << endl;
		cout << "*********************************************" << endl;
		Sleep(0700);
		system("cls");
		cout << "*********************************************" << endl;
		cout << "*                   Enjoy!                  *" << endl;
		cout << "*********************************************" << endl;
		Sleep(0700);
	}
	else
	{
		cout << "welcome to electricity billing system" << endl;
		Sleep(1000);
	}
}

int main()
{
	checkAndGenerate();
	getTotalUser();
	login();
}