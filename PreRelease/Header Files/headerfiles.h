#pragma once
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

char FLOC_FILEFOLDER[18] = { "C:\\Billing System" };
string FLOC_USERBASICINFO = "C:\\Billing System\\userbasicinfo.dat";
string FLOC_EDITUSERINFO_TEMP = "C:\\Billing System\\temp_userbasicinfo.dat";
string FLOC_SYSSET = "C:\\BillingSystem\\SystemSettings.dat";
string FLOC_BILLDETAIL = "C:\\Billing System\\bill_detail.dat";
string FLOC_MRINFO = "C:\\Billing System\\mrinfo.dat";
string FLOC_EDITMRINFO_TEMP = "C:\\Billing System\\temp_mrinfo.dat";
string FLOC_RATE = "C:\\Billing System\\rate.dat";

int totalUser = 0;
const int N = 6;

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
typedef struct rateRecord
{
	double ent[N][N];
	double urban[N][N];
	double rural[N][N];
}rateRecord;