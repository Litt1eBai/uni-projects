#pragma once
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

// File locations ====================================================
char FLOC_FILEFOLDER[70] = {
    "/home/jensen/Documents/code/ElectricityBillingSystem/testdata/"};
string FLOC_USERBASICINFO =
    "/home/jensen/Documents/code/ElectricityBillingSystem/testdata/"
    "userbasicinfo.dat";
string FLOC_EDITUSERINFO_TEMP =
    "/home/jensen/Documents/code/ElectricityBillingSystem/testdata/"
    "temp_userbasicinfo.dat";
string FLOC_BILLDETAIL =
    "/home/jensen/Documents/code/ElectricityBillingSystem/testdata/"
    "bill_detail.dat";
string FLOC_MRINFO =
    "/home/jensen/Documents/code/ElectricityBillingSystem/testdata/mrinfo.dat";
string FLOC_EDITMRINFO_TEMP =
    "/home/jensen/Documents/code/ElectricityBillingSystem/testdata/"
    "temp_mrinfo.dat";
string FLOC_RATE =
    "/home/jensen/Documents/code/ElectricityBillingSystem/testdata/rate.dat";
string FLOC_REPORTFORM =
    "/home/jensen/Documents/code/ElectricityBillingSystem/testdata/reportform.csv";
// Global Veriables =========================================================
int usercount[9];
const int N = 6;
// Structures =========================================================
typedef struct address {
  char city[32];
  char district[32];  // Town
  char street[32];    // County
  char estate[32];    // Village
  char unit[32];      // Unit
  int level;
  int room;
} add;
typedef struct date {
  int sec;
  int min;
  int h;
  int d;
  int m;
  int y;
} date;
typedef struct deviceinfo {
  int model;
  int serialNo;
  int perchaseTime;
} device;
typedef struct userinfo {
  double balance;
  bool powercut;
  // Read
  date last_read;
  bool read_now;
  int last_month_usage;
  // basic
  int No;
  char name[32];
  char id[19];
  int type;
  add address;
  char password[32];
  double voltage;
} userinfo;
typedef struct userbill {
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
  double fee;
  bool payment;
  date payment_date;
} userbill;
typedef struct MRdef {
  int No;
  char name[32];
  float progress;
} MRdef;
typedef struct rateRecord {
  int rateNo;
  date createTime;
  double ent[N][N];
  double urban[N][N];
  double rural[N][N];
} rateRecord;
typedef struct estateUserInfoNode {
  userinfo info;
  struct estateUserInfoNode* next;
} estateUserInfoNode;
typedef struct unreadRegionInfoNode {
  add region;
  int users;
  int unread;
  int total_usage;
  int total_arrears;
  struct unreadRegionInfoNode* next;
} unreadRegionInfoNode;
typedef struct userBillHistoryNode {
  userbill bill;
  struct userBillHistoryNode* next;
} userBillHistoryNode;
// Functions ===========================================================
rateRecord getCurrentRate() {
  rateRecord current;
  fstream file;
  file.open(FLOC_RATE, ios::binary | ios::in);
  float size = sizeof(rateRecord);
  file.seekg(-size, ios::end);
  file.read((char*)&current, sizeof(rateRecord));
  file.close();
  return current;
}
void getTotalUser() {
  for (int i = 0; i < 9; i++) {
    usercount[i] = 0;
  }
  fstream file;
  userinfo user;
  file.open(FLOC_USERBASICINFO, ios::binary | ios::in);
  while (1) {
    file.read((char*)&user, sizeof(userinfo));
    if (file.eof())
      break;
    usercount[user.type]++;
    usercount[0]++;
  }
  file.close();
}
userinfo getUserInfo(int username) {
  userinfo use;
  fstream temp;
  temp.open(FLOC_USERBASICINFO, ios::binary | ios::in);
  while (temp.read((char*)&use, sizeof(userinfo))) {
    if (use.No == username) {
      temp.close();
      break;
    }
  }
  return use;
}
int genUserNo() {
  fstream tmpf;
  userinfo tmp;
  tmpf.open(FLOC_USERBASICINFO, ios::in | ios::app | ios::binary);
  int size = sizeof(userinfo);
  tmpf.seekg(-size, ios::end);
  tmpf.read((char*)&tmp, sizeof(userinfo));
  return (tmp.No + 1);
}
void changeUserInfo(userinfo use) {
  userinfo tempUserInfo;
  fstream origin;
  fstream temp;
  origin.open(FLOC_USERBASICINFO, ios::binary | ios::in);
  temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::out);
  while (origin.read((char*)&tempUserInfo, sizeof(userinfo))) {
    if (tempUserInfo.No == use.No)
      temp.write((char*)&use, sizeof(userinfo));
    else
      temp.write((char*)&tempUserInfo, sizeof(userinfo));
  }
  temp.close();
  origin.close();
  origin.open(FLOC_USERBASICINFO, ios::binary | ios::out);
  temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::in);
  while (temp.read((char*)&tempUserInfo, sizeof(userinfo))) {
    origin.write((char*)&tempUserInfo, sizeof(userinfo));
  }
  temp.close();
  origin.close();
}
date getCurrentTime() {
  time_t current = time(NULL);
  tm* tm_local = localtime(&current);
  date currentTime;
  currentTime.y = tm_local->tm_year + 1900;
  currentTime.m = tm_local->tm_mon + 2;
  currentTime.d = tm_local->tm_mday;
  currentTime.h = tm_local->tm_hour;
  currentTime.min = tm_local->tm_min;
  currentTime.sec = tm_local->tm_sec;
  return currentTime;
}
void getString(char* s) {
  int n = 0;
  cin.get();
  while (cin.peek() != '\n') {
    cin.get(s[n]);
    n++;
  }
  s[n] = '\0';
}
void getString(string& s) {
  cin.get();
  getline(cin, s);
}
bool samestr(char* s1, char* s2) {
  if (strlen(s1) != strlen(s2)) return false;
  for (int i = 0; i < strlen(s1); i++) {
    if (s1[i] != s2[i]) return false;
  }
  return true;
}
bool sameMonth(date current, date comp) {
  if (current.y == comp.y && current.m == comp.m) return 1;
  return 0;
}
bool eleInArr(string arr[], string ele, int n) {
  for (int i = 0; i < n; i++) {
    if (arr[i] == ele) return true;
  }
  return false;
}
void dotDotDot(int n) {
  for (int i = 0; i < n; i++) {
    cout << '.';
    sleep(1);
  }
}
// System =====================================================
void defineUnread() {
  date current_time = getCurrentTime();
  userinfo info;
  fstream file;
  file.open(FLOC_USERBASICINFO, ios::binary | ios::in | ios::out);
  file.seekg(0, ios::beg);
  while (file.read((char*)&info, sizeof(userinfo))) {
    if (!sameMonth(current_time, info.last_read)) {
      info.read_now = false;
      int size = sizeof(userinfo);
      file.seekp(-size, ios::cur);
      file.write((char*)&info, sizeof(userinfo));
    }
    if (sameMonth(current_time, info.last_read)) {
      info.read_now = true;
      int size = sizeof(userinfo);
      file.seekp(-size, ios::cur);
      file.write((char*)&info, sizeof(userinfo));
    }
  }
  file.close();
}
int getUnread() {
  int unread = 0;
  userinfo basicInfo;
  fstream user;
  user.open(FLOC_USERBASICINFO, ios::binary | ios::in);
  while (user.read((char*)&basicInfo, sizeof(userinfo))) {
    if (basicInfo.read_now == false) {
      unread++;
    }
  }
  user.close();
  return unread;
}
int genCaseNo() {
  fstream file;
  userbill bill;
  file.open(FLOC_BILLDETAIL, ios::binary | ios::in);
  int size = sizeof(userbill);
  file.seekg(-size, ios::end);
  file.read((char*)&bill, sizeof(userbill));
  return (bill.caseNo + 1);
}
// System settings - reset =====================================
void resetDatabase_Rate() {
	rateRecord defaultRate;
	defaultRate.createTime = getCurrentTime();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			defaultRate.urban[i][j] = -1;
			defaultRate.rural[i][j] = -1;
			defaultRate.ent[i][j] = -1;
    	}
	}
  defaultRate.rateNo = 0;
  // Urban ==========================
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
  // Rural ===========================
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
  // Enterprise =====================
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
void resetDatabase_UserBasicInfo() {
  userinfo rootUser;
  rootUser.No = 0;
  strcpy(rootUser.name, "root");
  strcpy(rootUser.id, "0");
  rootUser.type = 1;
  rootUser.powercut = true;
  rootUser.last_month_usage = 0;
  rootUser.voltage = 220;
  rootUser.read_now = true;
  rootUser.powercut = false;
  rootUser.last_read = getCurrentTime();
  strcpy(rootUser.password, "root");
  rootUser.balance = 10000;
  strcpy(rootUser.address.city, "default");
  strcpy(rootUser.address.district, "default");
  strcpy(rootUser.address.street, "default");
  strcpy(rootUser.address.estate, "default");
  strcpy(rootUser.address.unit, "0");
  rootUser.address.level = 0;
  rootUser.address.room = 0;
  fstream resetFile;
  resetFile.open(FLOC_USERBASICINFO, ios::binary | ios::out);
  resetFile.write((char*)&rootUser, sizeof(userinfo));
  resetFile.close();
  getTotalUser();
}
void resetDatabase_UserBill() {
  userinfo rootUserInfo = getUserInfo(0);
  userbill rootUser;
  rootUser.caseNo = 0;
  rootUser.user_record = rootUserInfo;
  rootUser.rateNo = 0;
  rootUser.last_month_usage = 0;
  rootUser.current_usage = 0;
  rootUser.read = true;
  rootUser.fee = 0;
  rootUser.payment = true;
  rootUser.payment_date = rootUser.read_date = getCurrentTime();
  fstream rootBill;
  rootBill.open(FLOC_BILLDETAIL, ios::binary | ios::out);
  rootBill.write((char*)&rootUser, sizeof(userbill));
}
void resetDatabase() {
  resetDatabase_UserBasicInfo();
  resetDatabase_UserBill();
  resetDatabase_Rate();
}
void userInfoImport(string location) {
  fstream fromfile;
  fromfile.open(location, ios::binary | ios::in);
  if (!fromfile) {
    cout << "Can't find the file in the location provided." << endl;
    fromfile.close();
    sleep(1);
  } else {
    fstream tofile;
    userinfo former;
    former.No = genUserNo();
    former.No--;
    tofile.open(FLOC_USERBASICINFO, ios::binary | ios::app | ios::out);
    userinfo user;
    while (fromfile.read((char*)&user, sizeof(userinfo))) {
      user.No = former.No + 1;
      tofile.write((char*)&user, sizeof(userinfo));
      former.No = user.No;
    }
    cout << "Success" << endl;
    getTotalUser();
    sleep(1);
  }
}