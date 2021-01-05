#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <iomanip>
#include <ctime>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>
using namespace std;


// Basic definiations and functions
int totalUser = 0;
char FLOC_FILEFOLDER[18] = { "D:\\Billing System" };
string FLOC_USERBASICINFO = "D:\\Billing System\\userbasicinfo.dat";
string FLOC_EDITUSERINFO_TEMP = "D:\\Billing System\\temp_userbasicinfo.dat";
string FLOC_SYSSET = "D:\\Billing System\\SystemSettings.dat";
string FLOC_BILLDETAIL = "D:\\Billing System\\bill_detail.dat";
string FLOC_MRINFO = "D:\\Billing System\\mrinfo.dat";
string FLOC_EDITMRINFO_TEMP = "D:\\Billing System\\temp_mrinfo.dat";
string FLOC_RATE = "D:\\Billing System\\rate.dat";

typedef struct fLoc_sysSet
{
	string userBasicInfo;
	string editUserBasicInfo_tmp;
}fLoc_sysSet;
typedef struct address
{
	int room;
	int level;
	char unit[32]; // Unit
	char estate[32]; // Village
	char street[32]; // County
	char district[32]; // Town
	char city[32];
}add;
typedef struct date
{
	int sec;
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
	int balance;
	bool powercut;

	// Read
	date last_read;
	bool read_now;
	int last_month_usage;

	//basic
	int No;
	char name[32];
	char id[19];
	int type;
	add address;
	char password[32];
	int voltage;
}userinfo;
typedef struct userbill
{
	// General
	int caseNo;
	userinfo user_record;
	int rateNo;

	// Usage
	int last_month_usage;
	int current_usage;

	// Read status
	bool read;
	date read_date;

	// Pay Status
	int pay;
	bool payment;
	date payment_date;
}userbill;
typedef struct MRdef
{
	int No;
	char name[32];
	float progress;
}MRdef;
const int N = 6;
typedef struct rateRecord
{
	double ent[N][N];
	double urban[N][N];
	double rural[N][N];
}rateRecord;


// Rate
rateRecord getCurrentRate()
{
	rateRecord current;
	fstream file;
	file.open(FLOC_RATE, ios::in);
	float size = sizeof(rateRecord);
	file.seekg(-size, ios::end);
	file.read((char*)&current, sizeof(rateRecord));
	file.close();
	return current;
}
void showRate(rateRecord current = getCurrentRate())
{
	cout << "Urban Rate Overview" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(9) << current.urban[i][j] << " ";
		}
		cout << endl;
	}
	cout << "------------------------------------" << endl;
	cout << "Rural Rate Overview" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(9) << current.rural[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------------------------" << endl;
	cout << "Enterprise Rate Overview" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setw(9) << current.ent[i][j] << " ";
		}
		cout << endl;
	}
}


// Functions ===============================================
date getCurrentTime()
{
	time_t now = time(0);
	tm nowLocal;
	localtime_s(&nowLocal, &now);
	date currentTime;
	currentTime.y = nowLocal.tm_year + 1900;
	currentTime.m = nowLocal.tm_mon + 2;
	currentTime.d = nowLocal.tm_mday;
	currentTime.h = nowLocal.tm_hour;
	currentTime.min = nowLocal.tm_min;
	currentTime.sec = nowLocal.tm_sec;
	return currentTime;
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
bool sameMonth(date current, date comp)
{
	if (current.y == comp.y && current.m == comp.m) return 1;
	return 0;
}
bool eleInArr(string arr[], string ele, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == ele)
			return true;
	}
	return false;
}
void dotDotDot(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << '.';
		Sleep(0700);
	}
}


// Find user and get info ===================================
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
	case 4: typ = "Enterprise User (E1)"; break;
	case 5: typ = "Enterprise User (E2)"; break;
	case 6: typ = "Urban User"; break;
	case 7: typ = "Common Rural User"; break;
	case 8: typ = "Rural User in Poverty"; break;
	}
	return typ;
}
int getUserType(int username)
{
	userinfo user;
	user = getUserInfo(username);
	return user.type;
}
MRdef getMRDetail(int username)
{
	MRdef mr;
	fstream temp;
	temp.open(FLOC_MRINFO, ios::binary | ios::in);
	while (temp.read((char*)&mr, sizeof(userinfo)))
	{
		if (mr.No == username)
		{
			temp.close();
			break;
		}
	}
	return mr;
}


// Apply changes - user basic info ===========================
void storeUserInfo(userinfo use)
{
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

// System =====================================================
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
void defineUnread()
{
	date current_time = getCurrentTime();
	userinfo info;
	fstream file;
	file.open(FLOC_USERBASICINFO, ios::binary | ios::in | ios::out);
	while (file.read((char*)&info, sizeof(userinfo)))
	{
		if (!sameMonth(current_time, info.last_read))
		{
			info.read_now = false;
			int size = sizeof(userinfo);
			int now = file.tellg();
			file.seekp(-size, ios::cur);
			file.write((char*)&info, sizeof(userinfo));
			file.seekp(now, ios::beg);
			file.seekp(now, ios::beg);
		}
		if (sameMonth(current_time, info.last_read))
		{
			info.read_now = true;
			int size = sizeof(userinfo);
			int now = file.tellg();
			file.seekp(-size, ios::cur);
			file.write((char*)&info, sizeof(userinfo));
			file.seekp(now, ios::beg);
			file.seekp(now, ios::beg);
		}
	}
	file.close();
}
int getUnread()
{
	int unread = 0;
	userinfo basicInfo;
	fstream user;
	user.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	while (user.read((char*)&basicInfo, sizeof(userinfo)))
	{
		if (basicInfo.read_now == false)
		{
			unread++;
		}
	}
	user.close();
	return unread;
}

// System settings - reset =====================================
void resetDatabase_Rate()
{
	rateRecord defaultRate;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			defaultRate.urban[i][j] = -1;
			defaultRate.rural[i][j] = -1;
			defaultRate.ent[i][j] = -1;
		}
	}

	//Urban ==========================
	defaultRate.urban[0][0] = 0;
	defaultRate.urban[0][1] = 1;
	defaultRate.urban[0][2] = 10;
	defaultRate.urban[0][0] = 0;
	defaultRate.urban[1][0] = 2400;
	defaultRate.urban[2][0] = 4800;

	defaultRate.urban[1][1] = 0.52;
	defaultRate.urban[1][2] = 0.51;
	defaultRate.urban[2][1] = 0.57;
	defaultRate.urban[2][2] = 0.56;
	defaultRate.urban[3][1] = 0.82;
	defaultRate.urban[3][2] = 0.81;
	//Rural ===========================
	defaultRate.rural[0][0] = 0;
	defaultRate.rural[0][1] = 1;
	defaultRate.rural[0][2] = 10;
	defaultRate.rural[0][3] = 35;
	defaultRate.rural[0][4] = 110;
	defaultRate.rural[1][0] = 1;
	defaultRate.rural[2][0] = 2;

	defaultRate.rural[1][1] = 0.568;
	defaultRate.rural[1][2] = 0.553;
	defaultRate.rural[1][3] = 0.538;
	defaultRate.rural[2][1] = 0.3324;
	defaultRate.rural[2][2] = 0.3192;
	defaultRate.rural[2][3] = 0.3042;
	//Enterprise =====================
	defaultRate.ent[0][0] = 0;
	defaultRate.ent[0][1] = 1;
	defaultRate.ent[0][2] = 10;
	defaultRate.ent[0][3] = 35;
	defaultRate.ent[0][4] = 110;
	defaultRate.ent[1][0] = 1;
	defaultRate.ent[2][0] = 2;

	defaultRate.ent[1][1] = 0.6578;
	defaultRate.ent[1][2] = 0.6328;
	defaultRate.ent[1][3] = 0.6178;
	defaultRate.ent[1][4] = 0.60278;
	defaultRate.ent[2][1] = 0.6057;
	defaultRate.ent[2][2] = 0.5807;
	defaultRate.ent[2][3] = 0.5658;
	defaultRate.ent[2][4] = 0.5557;

	fstream file;
	file.open(FLOC_RATE, ios::binary | ios::out);
	file.write((char*)&defaultRate, sizeof(rateRecord));
	file.close();
}
void resetDatabase_UserBasicInfo()
{
	userinfo rootUser;
	rootUser.No = 0;
	strcpy_s(rootUser.name, "root");
	strcpy_s(rootUser.id, "0");
	rootUser.type = 1;
	rootUser.powercut = true;
	rootUser.last_month_usage = 0;
	rootUser.voltage = 220;
	rootUser.read_now = true;
	rootUser.powercut = false;
	rootUser.last_read = getCurrentTime();
	strcpy_s(rootUser.password, "root");
	rootUser.balance = 10000;
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
void resetDatabase_UserBill()
{
	userinfo rootUserInfo = getUserInfo(0);
	userbill rootUser;
	rootUser.caseNo = 0;
	rootUser.user_record = rootUserInfo;
	rootUser.rateNo = 0;
	rootUser.last_month_usage = 0;
	rootUser.current_usage = 0;
	rootUser.read = true;
	rootUser.pay = 0;
	rootUser.payment = true;
	rootUser.payment_date = rootUser.read_date = getCurrentTime();
	fstream rootBill;
	rootBill.open(FLOC_BILLDETAIL, ios::binary | ios::out);
	rootBill.write((char*)&rootUser, sizeof(userbill));
}
void resetDatabase()
{
	resetDatabase_UserBasicInfo();
	resetDatabase_UserBill();
	resetDatabase_Rate();
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
		while (fromfile.read((char*)&user, sizeof(userinfo)))
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


// Apple changes - meter reader info ===========================
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


// Meter Reader Features ======================================
int genCaseNo()
{
	fstream tmpf;
	userbill tmp;
	tmpf.open(FLOC_BILLDETAIL, ios::in | ios::app | ios::binary);
	int size = sizeof(userinfo);
	tmpf.seekg(-size, ios::end);
	tmpf.read((char*)&tmp, sizeof(userinfo));
	return (tmp.caseNo + 1);
}

// Get Reginal Info
int getReignalInfo_district(string districts[]) {
	int n = 0;
	userinfo user;
	fstream temp;
	temp.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	while (temp.read((char*)&user, sizeof(userinfo))) {
		if (!eleInArr(districts, user.address.district, n)) {
			districts[n + 1] = user.address.district;
			n++;
		}
	}
	return n;
}
int getReignalInfo_street(string streets[]) {
	int n = 0;
	userinfo user;
	fstream temp;
	temp.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	while (temp.read((char*)&user, sizeof(userinfo))) {
		if (!eleInArr(streets, user.address.street, n)) {
			streets[n + 1] = user.address.street;
			n++;
		}
	}
	return n;
}
int getReignalInfo_estate(string estates[]) {
	int n = 0;
	userinfo user;
	fstream temp;
	temp.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	while (temp.read((char*)&user, sizeof(userinfo))) {
		if (!eleInArr(estates, user.address.estate, n)) {
			estates[n + 1] = user.address.estate;
			n++;
		}
	}
	return n;
}





// Meter Reader_Menu
void MRListUnread(int username)
{
	system("cls");
	cout << "USER MANAGEMENT - USER LIST" << endl;
	cout << "======================================================================================================================================" << endl;
	cout << "Number                Name	                                   Address                                                                 " << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;
	userinfo user;
	fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
	while (readUser.read((char*)&user, sizeof(userinfo)))
	{
		if (user.read_now == false && user.type >= 3)
			cout << setw(11) << right << setfill('0') << user.No << '\t'
			<< setw(25) << left << setfill(' ') << user.name
			<< setw(20) << left << user.id << '\t'
			<< setw(5) << right << setfill(' ') << user.address.unit << '-'
			<< setw(3) << right << setfill('0') << user.address.level << '-'
			<< setw(4) << right << setfill('0') << user.address.room << ", "
			<< setw(15) << setfill(' ') << user.address.estate << ", "
			<< setw(25) << user.address.street << ", "
			<< setw(15) << user.address.district << ", "
			<< setw(15) << user.address.city << endl;
	}
	system("pause");
}
void MRListUsers()
{
	system("cls");
	cout << "USER MANAGEMENT - USER LIST" << endl;
	cout << "======================================================================================================================================" << endl;
	cout << "Number                Name	               Balance  Status    Usage      Read Status             " << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;
	userinfo user;
	fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (readUser.read((char*)&user, sizeof(userinfo)))
	{
		if (user.read_now == false)
			SetConsoleTextAttribute(hConsole, 7);
		cout << setw(11) << right << setfill('0') << user.No << '\t'
			<< setw(25) << left << setfill(' ') << user.name << '\t' << setw(4) << fixed << setprecision(3) << user.balance << "\t";
		if (user.powercut == true)
			cout << setw(6) << right << "cut" << '\t';
		else
			cout << setw(6) << left << "using" << '\t';
		cout << setw(6) << left << user.last_month_usage << "\t";

		if (user.read_now)
			cout << setw(6) << left << "read" << '\t';
		else
			cout << setw(6) << left << "Unread" << '\t';
		cout << user.last_read.h << ":" << user.last_read.min << ":" << user.last_read.sec << " "
			<< user.last_read.d << "/" << user.last_read.m << "/" << user.last_read.y << endl;
		SetConsoleTextAttribute(hConsole, 8);
	}
	SetConsoleTextAttribute(hConsole, 15);
	readUser.close();
	system("pause");
}
void MRInput(int username)
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
		cout << "Usage: ";
		cin >> fee;
	}
}
void MRInputRural(int username)
{

}
void MROverview(int username)
{
	MRdef mywork;
	mywork = getMRDetail(username);
	string place;
	do
	{
		int userread = 0;
		int userunread = 10;
		system("cls");
		cout << "DASHBOARD" << endl;
		cout << "==============================================" << endl;
		cout << "Your progress: ";
		cout << "Read: " << userread << "/" << userunread << endl;
		cout << "Progress: " << (userread / userunread) * 100 << "%" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "Overview:" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "You wish to input: ";
		getString(place);
		cout << "not available" << endl;
	} while (place != "-1");

}
void MRWork(int username)
{
	system("cls");

}
void MRDash(int username)
{
	userinfo me;
	MRdef mywork;
	mywork = getMRDetail(username);
	me = getUserInfo(username);
	int userread = getUnread();
	int totaluser_local = totalUser;
	int opt;
	do
	{
		system("cls");
		cout << "DASHBOARD" << endl;
		cout << "==============================================" << endl;
		cout << me.name << ", greetings!" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Your progress: " << endl;
		cout << "Unread: " << userread << "/" << totaluser_local << endl;
		cout << "Progress: " << mywork.progress << "%" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Menu:" << endl;
		cout << "1. Start Inputting" << endl;
		cout << "2. Overview" << endl;
		cout << "3. Show assigned tasks" << endl;
		cout << "0. Logout" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: MROverview(username);  break;
		case 2: MRListUsers(); break;
		case 3: MRWork(username);
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

// Charger_Menu ===============================================
void chargerDash(int username)
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
	} while (opt != 0);
}


// Admin Features =============================================
void setdefaultPassword(char id[], char passput[])
{
	int i;
	for (i = 0; i < 6; i++)
	{
		passput[i] = id[17 - i];
	}
	passput[i] = '\0';
}


// System Settings ============================================
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
		cout << "2. Import user basic information from file" << endl;
		cout << "3. Reset database" << endl;
		cout << "0. Exit" << endl;
		cin >> opt;
		string fileLocation;
		switch (opt)
		{
		case 1:
			break;
		case 2:
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
		case 0: return;
		default: cout << "Invalid input, please try again" << endl;
		}
	} while (opt != 0);
}


// Admin_Menu =================================================
void showUrbanRate()
{
	rateRecord current = getCurrentRate();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_setmode(_fileno(stdout), _O_U16TEXT);
	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Urban" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.urban[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.urban[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++)
	{
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.urban[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++)
	{
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.urban[i][0] << " kWh";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++)
		{
			SetConsoleTextAttribute(hConsole, 15);
			if (current.urban[i][j] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.urban[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.urban[N - 1][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";


	for (int j = 1; j < N; j++)
	{
		SetConsoleTextAttribute(hConsole, 15);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.urban[N - 1][0] << " kWh";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}


	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;

	_setmode(_fileno(stdout), _O_TEXT);
	SetConsoleTextAttribute(hConsole, 15);
}
void showRuralRate()
{
	rateRecord current = getCurrentRate();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Rural" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.rural[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.rural[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++)
	{
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.rural[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++)
	{
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << "E-" << setw(7) << left << current.rural[i][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++)
		{
			SetConsoleTextAttribute(hConsole, 15);
			if (current.rural[i][j] == -1)
				wcout << setw(9) << right << " ";
			else
				wcout << setw(9) << right << current.rural[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.urban[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.urban[N - 1][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";


	for (int j = 1; j < N; j++)
	{
		SetConsoleTextAttribute(hConsole, 15);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}


	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;

	_setmode(_fileno(stdout), _O_TEXT);
	SetConsoleTextAttribute(hConsole, 15);
}
void showEntRate()
{
	rateRecord current = getCurrentRate();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_setmode(_fileno(stdout), _O_U16TEXT);
	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Enterprise" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.ent[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.ent[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++)
	{
		SetConsoleTextAttribute(hConsole, 6);
		if (current.ent[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.ent[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++)
	{
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.ent[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << "E-" << setw(7) << left << current.ent[i][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++)
		{
			SetConsoleTextAttribute(hConsole, 15);
			if (current.ent[i][j] == -1)
				wcout << setw(9) << right << " ";
			else
				wcout << setw(9) << right << current.ent[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.ent[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.ent[N - 1][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";


	for (int j = 1; j < N; j++)
	{
		SetConsoleTextAttribute(hConsole, 15);
		if (current.ent[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.ent[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}


	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;


	_setmode(_fileno(stdout), _O_TEXT);
	SetConsoleTextAttribute(hConsole, 15);
}
void adminShowRate()
{
	system("cls");
	rateRecord current = getCurrentRate();
	cout << "RATE OverView" << endl;
	cout << "===========================================================" << endl;
	cout << "Here is the current rate:" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_setmode(_fileno(stdout), _O_U16TEXT);


	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Urban" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.urban[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.urban[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++)
	{
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.urban[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++)
	{
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.urban[i][0] << " kWh";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++)
		{
			SetConsoleTextAttribute(hConsole, 15);
			if (current.urban[i][j] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.urban[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.urban[N - 1][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";


	for (int j = 1; j < N; j++)
	{
		SetConsoleTextAttribute(hConsole, 15);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}


	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;






	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Rural" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.rural[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.rural[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++)
	{
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.rural[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++)
	{
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << "E-" << setw(7) << left << current.rural[i][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++)
		{
			SetConsoleTextAttribute(hConsole, 15);
			if (current.rural[i][j] == -1)
				wcout << setw(9) << right << " ";
			else
				wcout << setw(9) << right << current.rural[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.urban[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.urban[N - 1][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";


	for (int j = 1; j < N; j++)
	{
		SetConsoleTextAttribute(hConsole, 15);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}


	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;




	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Enterprise" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.ent[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.ent[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++)
	{
		SetConsoleTextAttribute(hConsole, 6);
		if (current.ent[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.ent[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++)
	{
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.ent[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << "E-" << setw(7) << left << current.ent[i][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++)
		{
			SetConsoleTextAttribute(hConsole, 15);
			if (current.ent[i][j] == -1)
				wcout << setw(9) << right << " ";
			else
				wcout << setw(9) << right << current.ent[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.ent[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.ent[N - 1][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";


	for (int j = 1; j < N; j++)
	{
		SetConsoleTextAttribute(hConsole, 15);
		if (current.ent[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.ent[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}


	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;


	_setmode(_fileno(stdout), _O_TEXT);
	SetConsoleTextAttribute(hConsole, 15);
}
void adminEditRate_Ent()
{
	system("cls");
	rateRecord current = getCurrentRate();
	cout << "RATE OverView" << endl;
	cout << "===========================================================" << endl;
	cout << "Here is the current rate:" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Rural" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.rural[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.rural[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++)
	{
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.rural[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++)
	{
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << "E-" << setw(7) << left << current.rural[i][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++)
		{
			SetConsoleTextAttribute(hConsole, 15);
			if (current.rural[i][j] == -1)
				wcout << setw(9) << right << " ";
			else
				wcout << setw(9) << right << current.rural[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.urban[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.urban[N - 1][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";


	for (int j = 1; j < N; j++)
	{
		SetConsoleTextAttribute(hConsole, 15);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}


	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;
}
void adminEditRate_Urban_editDetail(rateRecord current, int row, int col)
{
	rateRecord temp = current;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	do
	{
		system("cls");
		if (row == 0)
		{
			cout << "RATE - URBAN" << endl;
			cout << "=================================================================" << endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "You are changing data of row 0, col " << row << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << endl;
#pragma region display2
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++) // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;



			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 15);
			if (current.urban[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++)
			{
				if (i == col)
					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				else
					SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.urban[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++)
			{
				if (i == row)
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[N - 1][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";


			for (int j = 1; j < N; j++)
			{
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else if (row == 5)
		{
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "===========================================================" << endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << endl;
			if (col == 0)
			{
				if (col == 0)
				{
#pragma region display
					_setmode(_fileno(stdout), _O_U16TEXT);
					wcout << setw(10) << " ";
					for (int i = 0; i < N; i++) // col
					{
						SetConsoleTextAttribute(hConsole, 9);
						wcout << "col " << setw(6) << left << i;
					}
					wcout << endl;

					// Upper Line
					SetConsoleTextAttribute(hConsole, 8);
					wcout << setw(7) << right << " ";
					wcout << L"┌─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┬─────────";
					wcout << L"┬─────────┐" << endl;



					// 0,0
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[0][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.urban[0][0];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";

					// Line 1
					for (int i = 1; i < N; i++)
					{
						SetConsoleTextAttribute(hConsole, 6);
						if (current.urban[0][i] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(6) << current.urban[0][i] << " KV";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;

					// Middle Line
					SetConsoleTextAttribute(hConsole, 6);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;

					// Content
					for (int i = 1; i < N - 1; i++)
					{
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(4) << "row" << setw(2) << i << " "; // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.urban[i][0] << " kWh";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						for (int j = 1; j < N; j++)
						{
							SetConsoleTextAttribute(hConsole, 15);
							if (current.urban[i][j] == -1)
								wcout << setw(9) << " ";
							else
								wcout << setw(9) << current.urban[i][j];
							SetConsoleTextAttribute(hConsole, 8);
							wcout << L"│";
						}
						wcout << endl;
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(7) << " "; // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"├─────────";
						for (int i = 1; i < N - 1; i++)
							wcout << L"┼─────────";
						wcout << L"┼─────────┤" << endl;

					}
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					if (current.urban[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.urban[N - 1][0];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";


					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[N - 1][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.urban[N - 1][0] << " kWh";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}

					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"└─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┴─────────";
					wcout << L"┴─────────┘" << endl;
					_setmode(_fileno(stdout), _O_TEXT);
					SetConsoleTextAttribute(hConsole, 15);
#pragma endregion 
				}
			}
			else
			{
#pragma region diaplay3
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++) // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;



				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++)
				{
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.urban[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++)
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;

				}

				// Last line

				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.urban[N - 1][0] << " kWh";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";


				for (int j = 1; j < N; j++)
				{
					if (j == col)
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					else
						SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.urban[N - 1][0];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
		}
		else
		{
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "===========================================================" << endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << endl;
			if (col == 0)
			{
#pragma region display
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++) // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;



				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++)
				{
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.urban[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++)
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					if (i == row)
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					else
						SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;

				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";


				for (int j = 1; j < N; j++)
				{
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[N - 1][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion 
			}
			else
			{
#pragma region diaplay3
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++) // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;



				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++)
				{
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.urban[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++)
				{
					if (i == row)
					{
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(4) << "row" << setw(2) << i << " "; // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.urban[i][0] << " kWh";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						for (int j = 1; j < N; j++)
						{
							if (j == col)
								SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
							else
								SetConsoleTextAttribute(hConsole, 15);
							if (current.urban[i][j] == -1)
								wcout << setw(9) << " ";
							else
								wcout << setw(9) << current.urban[i][j];
							SetConsoleTextAttribute(hConsole, 8);
							wcout << L"│";
						}
					}
					else
					{
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(4) << "row" << setw(2) << i << " "; // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.urban[i][0] << " kWh";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						for (int j = 1; j < N; j++)
						{
							SetConsoleTextAttribute(hConsole, 15);
							if (current.urban[i][j] == -1)
								wcout << setw(9) << " ";
							else
								wcout << setw(9) << current.urban[i][j];
							SetConsoleTextAttribute(hConsole, 8);
							wcout << L"│";
						}
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;

				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";


				for (int j = 1; j < N; j++)
				{
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[N - 1][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
		}
		if (row != 0 && col != 0)
		{
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "You've selected row " << row << " col " << col << ", the detail is as follows: " << endl;
			cout << "Rate Type: " << "Urban E-" << row << " Tier " << col << endl;
			cout << "Voltage Interval: " << current.urban[0][col - 1] << " - " << current.urban[0][col] << endl;
			cout << "Energy Interval: " << current.urban[row - 1][0] << " - " << current.urban[row][0] << endl;
			cout << "Rate: " << current.urban[row][col] << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "Change rate to: ";
			cin >> temp.urban[row][col];
		}
		else if(row == 0)
		{
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "You've selected row " << row << " col " << col << ", the detail is as follows: " << endl;
			cout << "Voltage Interval: " << current.urban[0][col - 1] << " - " << current.urban[0][col] << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "Change the interval to: " << current.urban[0][col - 1];
			cin >> temp.urban[row][col];
		}
		else
		{
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "You've selected row " << row << " col " << col << ", the detail is as follows: " << endl;
			cout << "Energy Interval: " << current.urban[row - 1][0] << " - " << current.urban[row][0] << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "Change the interval to: " << current.urban[row - 1][0];
			cin >> temp.urban[row][col];
		}
		return;
	}while (1);
}
void adminEditRate_Urban_colSelect(rateRecord current, int row)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int col;
	do
	{
		system("cls");
		if (row == 0)
		{
			cout << "RATE - URBAN" << endl;
			cout << "=================================================================" << endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "You are changing data of row 0" << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << endl;
#pragma region display2
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++) // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;



			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
			if (current.urban[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++)
			{
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.urban[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.urban[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++)
			{
				if (i == row)
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[N - 1][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";


			for (int j = 1; j < N; j++)
			{
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else if (row == 5)
		{
		system("cls");

		cout << "RATE - URBAN" << endl;
		cout << "===========================================================" << endl;
		cout << "Here is the current rate for urban users" << endl;
		cout << "Change data on row " << row << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << endl;
#pragma region diaplay3
		_setmode(_fileno(stdout), _O_U16TEXT);
		wcout << setw(10) << " ";
		for (int i = 0; i < N; i++) // col
		{
			SetConsoleTextAttribute(hConsole, 9);
			wcout << "col " << setw(6) << left << i;
		}
		wcout << endl;

		// Upper Line
		SetConsoleTextAttribute(hConsole, 8);
		wcout << setw(7) << right << " ";
		wcout << L"┌─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┬─────────";
		wcout << L"┬─────────┐" << endl;



		// 0,0
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[0][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[0][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		// Line 1
		for (int i = 1; i < N; i++)
		{
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[0][i] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(6) << current.urban[0][i] << " KV";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}
		wcout << endl;

		// Middle Line
		SetConsoleTextAttribute(hConsole, 6);
		wcout << setw(7) << " "; // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

		// Content
		for (int i = 1; i < N - 1; i++)
		{
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << i << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 15);
			if (current.urban[i][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[i][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			for (int j = 1; j < N; j++)
			{
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[i][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[i][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

		}

		// Last line

		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.urban[N - 1][0] << " kWh";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";


		for (int j = 1; j < N; j++)
		{
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[N - 1][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(7) << " "; // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"└─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┴─────────";
		wcout << L"┴─────────┘" << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else
		{
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "===========================================================" << endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << endl;
#pragma region diaplay3
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++) // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;



			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++)
			{
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.urban[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++)
			{
				if (i == row)
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[N - 1][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";


			for (int j = 1; j < N; j++)
			{
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.urban[N - 1][0] << " kWh";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		cout << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "col: ";
		cin >> col;
		if (row == 0 && col == 0)
		{
			cout << "You cannot change the data of row 0, col 0" << endl;
			Sleep(1000);
		}
		else if (col != -1)
		{
			adminEditRate_Urban_editDetail(current, row, col);
		}
		else
		{
			return;
		}
	}while (col != -1);
}
void adminEditRate_Urban_rowSelect()
{
	rateRecord current = getCurrentRate();
	system("cls");
	int opt;
	do
	{
		cout << "RATE - URBAN" << endl;
		cout << "===========================================================" << endl;
		cout << "Here is the current rate for urban users" << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << endl;
#pragma region display0
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		_setmode(_fileno(stdout), _O_U16TEXT);


		// Upper Line
		SetConsoleTextAttribute(hConsole, 12);
		wcout << "Urban" << endl;
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"┌─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┬─────────";
		wcout << L"┬─────────┐" << endl;

		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);

		// 0,0
		if (current.urban[0][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[0][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		// Line 1
		for (int i = 1; i < N; i++)
		{
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[0][i] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(6) << current.urban[0][i] << " KV";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}
		wcout << endl;

		// Middle Line
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

		// Content
		for (int i = 1; i < N - 1; i++)
		{
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[i][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[i][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			for (int j = 1; j < N; j++)
			{
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[i][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[i][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

		}

		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";


		for (int j = 1; j < N; j++)
		{
			SetConsoleTextAttribute(hConsole, 15);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[N - 1][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}


		wcout << endl;
		wcout << L"└─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┴─────────";
		wcout << L"┴─────────┘" << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		cout << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "1. Start to edit" << endl;
		cout << "0. Go back" << endl;

		cin >> opt;
		if (opt == 1)
		{
			int row;
			do
			{
				system("cls");

				cout << "RATE - URBAN" << endl;
				cout << "===========================================================" << endl;
				cout << "Here is the current rate for urban users" << endl;
				cout << "Select the row you want to change" << endl;
				cout << "-----------------------------------------------------------" << endl;
				cout << endl;
#pragma region display1
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				_setmode(_fileno(stdout), _O_U16TEXT);



				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++) // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;



				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++)
				{
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.urban[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++)
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++)
					{
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}

					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;

				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";


				for (int j = 1; j < N; j++)
				{
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[N - 1][0] << "kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion 
				cout << endl;
				cout << "Input -1 to go back" << endl;
				cout << "--------------------------------------------------------" << endl;
				cout << "Change row: ";
				cin >> row;

//				system("cls");
//				if (row == 0)
//				{
//					cout << "RATE - URBAN" << endl;
//					cout << "=================================================================" << endl;
//					cout << "Here is the current rate for urban users" << endl;
//					cout << "You are changing data of row 0" << endl;
//					cout << "-----------------------------------------------------------------" << endl;
//					cout << endl;
//#pragma region display2
//					_setmode(_fileno(stdout), _O_U16TEXT);
//					wcout << setw(3) << " ";
//					for (int i = 0; i < N; i++)
//					{
//						SetConsoleTextAttribute(hConsole, 3);
//						wcout << "col " << setw(6) << left << i;
//					}
//					wcout << endl;
//
//
//					// Upper Line
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << L"┌─────────";
//					for (int i = 1; i < N - 1; i++)
//						wcout << L"┬─────────";
//					wcout << L"┬─────────┐" << endl;
//					wcout << L"│";
//					SetConsoleTextAttribute(hConsole, 6);
//
//
//					// 0,0
//					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
//					if (current.urban[0][0] == -1)
//						wcout << setw(9) << " ";
//					else
//						wcout << setw(9) << current.urban[0][0];
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << L"│";
//
//					// Line 1
//					for (int i = 1; i < N; i++)
//					{
//						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
//						if (current.urban[0][i] == -1)
//							wcout << setw(9) << right << " ";
//						else
//							wcout << setw(6) << right << current.urban[0][i] << " KV";
//						SetConsoleTextAttribute(hConsole, 8);
//						wcout << L"│";
//					}
//					wcout << endl;
//
//					// Middle Line
//					wcout << L"├─────────";
//					for (int i = 1; i < N - 1; i++)
//						wcout << L"┼─────────";
//					wcout << L"┼─────────┤" << endl;
//
//					// Content
//					for (int i = 1; i < N - 1; i++)
//					{
//						wcout << L"│";
//						SetConsoleTextAttribute(hConsole, 6);
//						if (current.urban[i][0] == -1)
//							wcout << setw(9) << " ";
//						else
//							wcout << setw(5) << current.urban[i][0] << " kWh";
//						SetConsoleTextAttribute(hConsole, 8);
//						wcout << L"│";
//						for (int j = 1; j < N; j++)
//						{
//							SetConsoleTextAttribute(hConsole, 15);
//							if (current.urban[i][j] == -1)
//								wcout << setw(9) << " ";
//							else
//								wcout << setw(9) << current.urban[i][j];
//							SetConsoleTextAttribute(hConsole, 8);
//							wcout << L"│";
//						}
//
//						wcout << endl;
//						wcout << L"├─────────";
//						for (int i = 1; i < N - 1; i++)
//							wcout << L"┼─────────";
//						wcout << L"┼─────────┤" << endl;
//
//					}
//
//					wcout << L"│";
//					SetConsoleTextAttribute(hConsole, 6);
//					if (current.urban[N - 1][0] == -1)
//						wcout << setw(9) << " ";
//					else
//						wcout << setw(9) << current.urban[N - 1][0];
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << L"│";
//
//
//					for (int j = 1; j < N; j++)
//					{
//						SetConsoleTextAttribute(hConsole, 15);
//						if (current.urban[N - 1][0] == -1)
//							wcout << setw(9) << " ";
//						else
//							wcout << setw(9) << current.urban[N - 1][0];
//						SetConsoleTextAttribute(hConsole, 8);
//						wcout << L"│";
//					}
//
//
//					wcout << endl;
//					wcout << L"└─────────";
//					for (int i = 1; i < N - 1; i++)
//						wcout << L"┴─────────";
//					wcout << L"┴─────────┘" << endl;
//					_setmode(_fileno(stdout), _O_TEXT);
//					SetConsoleTextAttribute(hConsole, 15);
//#pragma endregion
//				}
//
//				else
//				{
//					system("cls");
//
//					cout << "RATE - URBAN" << endl;
//					cout << "===========================================================" << endl;
//					cout << "Here is the current rate for urban users" << endl;
//					cout << "Change data on row " << row << endl;
//					cout << "-----------------------------------------------------------" << endl;
//					cout << endl;
//#pragma region diaplay3
//					_setmode(_fileno(stdout), _O_U16TEXT);
//					wcout << setw(10) << " ";
//					for (int i = 0; i < N; i++) // col
//					{
//						SetConsoleTextAttribute(hConsole, 9);
//						wcout << "col " << setw(6) << left << i;
//					}
//					wcout << endl;
//
//					// Upper Line
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << setw(7) << right << " ";
//					wcout << L"┌─────────";
//					for (int i = 1; i < N - 1; i++)
//						wcout << L"┬─────────";
//					wcout << L"┬─────────┐" << endl;
//
//
//
//					// 0,0
//					SetConsoleTextAttribute(hConsole, 9);
//					wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << L"│";
//					SetConsoleTextAttribute(hConsole, 6);
//					if (current.urban[0][0] == -1)
//						wcout << setw(9) << " ";
//					else
//						wcout << setw(9) << current.urban[0][0];
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << L"│";
//
//					// Line 1
//					for (int i = 1; i < N; i++)
//					{
//						SetConsoleTextAttribute(hConsole, 6);
//						if (current.urban[0][i] == -1)
//							wcout << setw(9) << " ";
//						else
//							wcout << setw(6) << current.urban[0][i] << " KV";
//						SetConsoleTextAttribute(hConsole, 8);
//						wcout << L"│";
//					}
//					wcout << endl;
//
//					// Middle Line
//					SetConsoleTextAttribute(hConsole, 6);
//					wcout << setw(7) << " "; // row
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << L"├─────────";
//					for (int i = 1; i < N - 1; i++)
//						wcout << L"┼─────────";
//					wcout << L"┼─────────┤" << endl;
//
//					// Content
//					for (int i = 1; i < N - 1; i++)
//					{
//						if (i == row)
//						{
//							SetConsoleTextAttribute(hConsole, 9);
//							wcout << setw(4) << "row" << setw(2) << i << " "; // row
//							SetConsoleTextAttribute(hConsole, 8);
//							wcout << L"│";
//							SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
//							if (current.urban[i][0] == -1)
//								wcout << setw(9) << " ";
//							else
//								wcout << setw(5) << current.urban[i][0] << " kWh";
//							SetConsoleTextAttribute(hConsole, 8);
//							wcout << L"│";
//							for (int j = 1; j < N; j++)
//							{
//								SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
//								if (current.urban[i][j] == -1)
//									wcout << setw(9) << " ";
//								else
//									wcout << setw(9) << current.urban[i][j];
//								SetConsoleTextAttribute(hConsole, 8);
//								wcout << L"│";
//							}
//						}
//						else
//						{
//							SetConsoleTextAttribute(hConsole, 9);
//							wcout << setw(4) << "row" << setw(2) << i << " "; // row
//							SetConsoleTextAttribute(hConsole, 8);
//							wcout << L"│";
//							SetConsoleTextAttribute(hConsole, 15);
//							if (current.urban[i][0] == -1)
//								wcout << setw(9) << " ";
//							else
//								wcout << setw(5) << current.urban[i][0] << " kWh";
//							SetConsoleTextAttribute(hConsole, 8);
//							wcout << L"│";
//							for (int j = 1; j < N; j++)
//							{
//								SetConsoleTextAttribute(hConsole, 15);
//								if (current.urban[i][j] == -1)
//									wcout << setw(9) << " ";
//								else
//									wcout << setw(9) << current.urban[i][j];
//								SetConsoleTextAttribute(hConsole, 8);
//								wcout << L"│";
//							}
//						}
//						wcout << endl;
//						SetConsoleTextAttribute(hConsole, 9);
//						wcout << setw(7) << " "; // row
//						SetConsoleTextAttribute(hConsole, 8);
//						wcout << L"├─────────";
//						for (int i = 1; i < N - 1; i++)
//							wcout << L"┼─────────";
//						wcout << L"┼─────────┤" << endl;
//
//					}
//					SetConsoleTextAttribute(hConsole, 9);
//					wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << L"│";
//					SetConsoleTextAttribute(hConsole, 6);
//					if (current.urban[N - 1][0] == -1)
//						wcout << setw(9) << " ";
//					else
//						wcout << setw(9) << current.urban[N - 1][0];
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << L"│";
//
//
//					for (int j = 1; j < N; j++)
//					{
//						SetConsoleTextAttribute(hConsole, 15);
//						if (current.urban[N - 1][0] == -1)
//							wcout << setw(9) << " ";
//						else
//							wcout << setw(9) << current.urban[N - 1][0];
//						SetConsoleTextAttribute(hConsole, 8);
//						wcout << L"│";
//					}
//
//					wcout << endl;
//					SetConsoleTextAttribute(hConsole, 9);
//					wcout << setw(7) << " "; // row
//					SetConsoleTextAttribute(hConsole, 8);
//					wcout << L"└─────────";
//					for (int i = 1; i < N - 1; i++)
//						wcout << L"┴─────────";
//					wcout << L"┴─────────┘" << endl;
//					_setmode(_fileno(stdout), _O_TEXT);
//					SetConsoleTextAttribute(hConsole, 15);
//#pragma endregion
//				}
				if (row != -1)
				{
					adminEditRate_Urban_colSelect(current, row);
				}
				else
				{
					return;
				}
			}while (row != -1);
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
void adminEditRate_Rural()
{
	system("cls");
	rateRecord current = getCurrentRate();
	cout << "RATE RULE - RURAL USERS" << endl;
	cout << "===========================================================" << endl;
	cout << "Here is the rule for rural users" << endl;
	cout << "The current rule is on its " << 1 << " edition." << endl;
	cout << "-----------------------------------------------------------" << endl;
	showRuralRate();
	
}
void adminEditRate_1()
{
	system("cls");
	rateRecord current = getCurrentRate();
	int opt;
	do
	{
		cout << "RATE OverView" << endl;
		cout << "===========================================================" << endl;
		cout << "Which class do you want to change?" << endl;
		cout << "The current rule is on its " << 1 << " edition." << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << endl;
		cout << "1. Urban Users" << endl;
		cout << "2. Rural Users" << endl;
		cout << "3. Enterprise Users" << endl;
		cout << "4. Show Current Rule" << endl;
		cout << "0. Go back" << endl;
		cout << "-----------------------------------------------------------" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: adminEditRate_Urban_rowSelect(); break;
		case 2: adminEditRate_Rural(); break;
		case 3: adminEditRate_Ent(); break;
		case 4: adminShowRate(); break;
		case 0:
			return;
		default: cout << "Invalid input, please try again" << endl;
		}
	} while (opt != 0);
}

void adminBillRateManagement()
{

}
void adminBillingRateManage()
{
	system("cls");
	cout << "BILLING RATE MANAGEMENT - OVERVIEW" << endl;
	cout << "======================================================================" << endl;
	cout << "Chart" << endl;
	cout << " ______________________________________________________________________________________________________________________________" << endl;
	cout << "|     Enterprise      |           ";
}
void MRManage()
{
	system("cls");
	cout << "USER MANAGEMENT - MATER READER MANAGEMENT" << endl;
	cout << "======================================================================" << endl;
	cout << "Have a glance of how Meter Readers are doing: " << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "======================================================================" << endl;
	cout << "Number                Name	          Progress" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	fstream readMR(FLOC_MRINFO, ios::in | ios::binary);
	MRdef mr;
	while (readMR.read((char*)&mr, sizeof(MRdef)))
	{
		cout << setw(11) << right << setfill('0') << mr.No << '\t'
			<< setw(25) << left << setfill(' ') << mr.name
			<< setw(6) << left << fixed << setprecision(3) << mr.progress << "%" << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
	system("pause");

}
void generateUser()
{
	userinfo newUser;
	newUser.No = genUserNo();

	system("cls");
	int typchoice;
	cout << "USER USER REGISTRATION - NAME" << endl;
	cout << "======================================================================" << endl;
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
	cout << "|  1.Administrator       2.Meter Reader      3.Charger       |" << endl;
	cout << "|  4.Enterprise User(E1)       5. Enterprise User(E2)        |" << endl;
	cout << "|  6.Urban User                7.Common Rural User           |" << endl;
	cout << "|  8.Rural User in Poverty                                   |" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "User type: ";
	cin >> typchoice;
	string type;
	while (!(typchoice >= 1 && typchoice <= 8))
	{
		cout << "Invalid Input" << endl;
		cin >> typchoice;
	}
	switch (typchoice)
	{
	case 1: type = "Administrator"; newUser.type = 1; break;
	case 2: type = "Meter Reader"; newUser.type = 2; break;
	case 3: type = "Charger"; newUser.type = 3; break;
	case 4: type = "Enterprise User (E1)"; newUser.type = 4; break;
	case 5: type = "Enterprise User (E2)"; newUser.type = 5; break;
	case 6: type = "Urban User"; newUser.type = 6; break;
	case 7: type = "Common Rural User"; newUser.type = 7; break;
	case 8: type = "Rural User in Poverty"; newUser.type = 8; break;
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
	if (newUser.type == 7 || newUser.type == 8)
		cout << "Town: ";
	else
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
	if (newUser.type == 7 || newUser.type == 8)
		cout << "County: ";
	else
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
	if (newUser.type == 7 || newUser.type == 8)
		cout << "Village: ";
	else
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
	newUser.balance = 100;
	newUser.powercut = false;
	newUser.last_read = getCurrentTime();
	newUser.read_now = true;
	newUser.last_month_usage = 0;

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
	cout << "Balance: " << newUser.balance << " CNY" << endl;
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

		userbill newUserBill;
		newUserBill.caseNo = genCaseNo();
		newUserBill.user_record = newUser;
		newUserBill.rateNo = 0;
		newUserBill.last_month_usage = 0;
		newUserBill.current_usage = 0;
		newUserBill.pay = 0;
		newUserBill.read = false;
		newUserBill.payment = false;
		newUserBill.read_date = newUserBill.payment_date = getCurrentTime();

		fstream userBillInfo;
		userBillInfo.open(FLOC_BILLDETAIL, ios::binary | ios::out);
		userBillInfo.write((char*)&newUserBill, sizeof(userbill));
		userBillInfo.close();

		if (newUser.type == 2)
		{
			MRdef MRinfo;
			MRinfo.No = newUser.No;
			strcpy_s(MRinfo.name, newUser.name);
			MRinfo.progress = 0;
			fstream MRfile;
			MRfile.open(FLOC_MRINFO, ios::binary | ios::app);
			MRfile.write((char*)&MRinfo, sizeof(MRdef));
			MRfile.close();
		}

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
		cout << "#. Balance: " << user.balance << " CNY" << endl;
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
			cout << "|  1.Administrator       2.Meter Reader      3.Charger       |" << endl;
			cout << "|  4.Enterprise User(E1)       5. Enterprise User(E2)        |" << endl;
			cout << "|  6.Urban User                7.Common Rural User           |" << endl;
			cout << "|  8.Rural User in Poverty                                   |" << endl;
			cout << "--------------------------------------------------------------" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Change to: ";
			int user_typ;
			cin >> user_typ;
			while (!(user_typ >= 1 && user_typ <= 8))
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
			cout << "Address: " << " " << user.address.estate << ", " << user.address.street << ", " << user.address.district << ", " << user.address.city << endl;
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
		else if (opt == 6)
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
			system("cls");
			cout << "USER MANAGEMENT - REMOVE USER" << endl;
			cout << "======================================================================" << endl;
			cout << "You are removing user: " << user.name << "; user number: " << user.No << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Are you sure?" << endl;
			char choice6;
			cin >> choice6;
			if (choice6 == 'y' || choice6 == 'Y')
			{
				deleteUserInfo(user);
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
	} while (opt != 0);
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
	cout << "=================================================================================================================================================================================================" << endl;
	cout << "Number                Name	                Type                      ID                                         Address                                                             Read" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
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
			<< setw(4) << right << user.read_now << endl;
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
		cout << "3. Meter Reader Management" << endl;
		cout << "0. Exit" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: adminEditUsers(); break;
		case 2: adminListUsers(); break;
		case 3:MRManage(); break;
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



//User_Menu===================================================
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
		cout << "#. Balance" << me.balance << endl;
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
			cout << "You are changing your address: " << endl;
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
	} while (opt != 0);
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
		cout << "Balance: " << me.balance << " CNY" << endl;
		cout << "ID: " << me.id << endl;
		cout << "Address: " << me.address.unit << "-" << me.address.level << "-" << me.address.room
			<< " " << me.address.estate << ", " << me.address.street << ", " << me.address.district << ", " << me.address.city << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Menu:" << endl;
		cout << "1. Edit your information" << endl;
		cout << "2. Check your billing rate" << endl;
		cout << "3. Check history usage and billing" << endl;
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


// Login======================================================
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
	switch (user.type)
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
		cout << "=================================================" << endl;
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
				Sleep(0500);
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
			Sleep(0500);
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
		Sleep(0500);
	}
}


int main()
{
	//checkAndGenerate();
	//getTotalUser();
	//defineUnread();
	//login();
	resetDatabase_Rate();
	adminEditRate_1();
}