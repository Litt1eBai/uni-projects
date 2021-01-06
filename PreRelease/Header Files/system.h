#pragma once
#include "headerfiles.h"
using namespace std;

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