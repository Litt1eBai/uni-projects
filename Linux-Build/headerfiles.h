#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
//#include <direct.h>
#include <iomanip>
#include <ctime>
//#include <io.h>
#include <fcntl.h>
//#include <Windows.h>
#include <unistd.h>
using namespace std;

char FLOC_FILEFOLDER[70] = { "/home/jensen/Documents/Code/ElectricityBillingSystem/testdata/"};
string FLOC_USERBASICINFO = "/home/jensen/Documents/Code/ElectricityBillingSystem/testdata/userbasicinfo.dat";
string FLOC_EDITUSERINFO_TEMP = "/home/jensen/Documents/Code/ElectricityBillingSystem/testdata/temp_userbasicinfo.dat";
string FLOC_BILLDETAIL = "/home/jensen/Documents/Code/ElectricityBillingSystem/testdata/bill_detail.dat";
string FLOC_MRINFO = "/home/jensen/Documents/Code/ElectricityBillingSystem/testdata/mrinfo.dat";
string FLOC_EDITMRINFO_TEMP = "/home/jensen/Documents/Code/ElectricityBillingSystem/testdata/temp_mrinfo.dat";
string FLOC_RATE = "/home/jensen/Documents/Code/ElectricityBillingSystem/testdata/rate.dat";

int totalUser = 0;
const int N = 6;

typedef struct fLoc_sysSet
{
	string userBasicInfo;
	string editUserBasicInfo_tmp;
}fLoc_sysSet;
typedef struct address
{
	char city[32];
	char district[32]; // Town
	char street[32]; // County
	char estate[32]; // Village
	char unit[32]; // Unit
	int level;
	int room;
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
	double balance;
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
	double voltage;
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
typedef struct rateRecord
{
	date createTime;
	double ent[N][N];
	double urban[N][N];
	double rural[N][N];
}rateRecord;
typedef struct estateUserInfoNode{
	userinfo info;
	struct estateUserInfoNode* next;
}estateUserInfoNode;

rateRecord getCurrentRate()
{
	rateRecord current;
	fstream file;
	file.open(FLOC_RATE, ios::binary | ios::in);
	float size = sizeof(rateRecord);
	file.seekg(-size, ios::end);
	file.read((char*)&current, sizeof(rateRecord));
	file.close();
	return current;
}
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