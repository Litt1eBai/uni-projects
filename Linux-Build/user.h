#pragma once
#include "headerfiles.h"
using namespace std;

void changePasswordTo(int username, char* passput) {
  userinfo user;
  user = getUserInfo(username);
  strcpy(user.password, passput);
  changeUserInfo(user);
}
bool findUser(int username) {
  userinfo use;
  fstream temp;
  temp.open(FLOC_USERBASICINFO, ios::binary | ios::in);
  while (!temp.eof()) {
    temp.read((char*)&use, sizeof(userinfo));
    if (use.No == username) {
      return true;
    }
  }
  return false;
}
bool validUser(int username) {
  userinfo use;
  use = getUserInfo(username);
  if (use.No == username) return true;
  return false;
}
string rtnType(int typenum) {
  string typ;
  switch (typenum) {
    case 1:
      typ = "Administrator";
      break;
    case 2:
      typ = "Meter Reader";
      break;
    case 3:
      typ = "Charger";
      break;
    case 4:
      typ = "Enterprise User (E1)";
      break;
    case 5:
      typ = "Enterprise User (E2)";
      break;
    case 6:
      typ = "Urban User";
      break;
    case 7:
      typ = "Common Rural User";
      break;
    case 8:
      typ = "Rural User in Poverty";
      break;
  }
  return typ;
}
int getUserType(int username) {
  userinfo user;
  user = getUserInfo(username);
  return user.type;
}
MRdef getMRDetail(int username) {
  MRdef mr;
  fstream temp;
  temp.open(FLOC_MRINFO, ios::binary | ios::in);
  while (temp.read((char*)&mr, sizeof(userinfo))) {
    if (mr.No == username) {
      temp.close();
      break;
    }
  }
  return mr;
}
// Meter Reader-specific ====================================================
void showRate(rateRecord current = getCurrentRate()) {
  cout << "Urban Rate Overview" << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << setw(9) << current.urban[i][j] << " ";
    }
    cout << endl;
  }
  cout << "------------------------------------" << endl;
  cout << "Rural Rate Overview" << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << setw(9) << current.rural[i][j] << " ";
    }
    cout << endl;
  }
  cout << "-------------------------------------" << endl;
  cout << "Enterprise Rate Overview" << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << setw(9) << current.ent[i][j] << " ";
    }
    cout << endl;
  }
}
void storeMRInfo(MRdef mr) {
  MRdef mrtmp;
  fstream temp;
  temp.open(FLOC_MRINFO, ios::binary | ios::app | ios::out);
  temp.write((char*)&mr, sizeof(MRdef));
  temp.close();
}
int getRateEdition() {
  fstream file;
  file.open(FLOC_RATE, ios::binary | ios::in);
  file.seekg(0, ios::beg);
  double head = file.tellg();
  file.seekg(-(sizeof(rateRecord), ios::end));
  double end = file.tellg();
  return end - head;
}
int genRateNo(int type, int row, int col) {
  date currentTime = getCurrentTime();
  int rateNo = 0;
  rateNo = getRateEdition();
  rateNo = rateNo * 10 + type;
  rateNo = rateNo * 10 + row;
  rateNo = rateNo * 10 + col;
  return rateNo;
}
void chargeFeedback(int username, int lastUsage, int currentUsage, int& rateNo, double& fee) {
  rateRecord rate = getCurrentRate();
  userinfo user = getUserInfo(username);
  int row = 0;
  int col = 0;
  user.voltage = user.voltage / 1000;
  cout << "voltage: " << user.voltage << endl;
  cout << "Current Use: " << currentUsage << endl;
  cout << "Used : " << currentUsage - lastUsage << endl;
  if (user.type == 6) {
    for (row = 0; rate.urban[row][0] != -1; row++) {
      if (currentUsage >= rate.urban[row][0] &&
          currentUsage < rate.urban[row + 1][0]) {
        break;
      } else if (currentUsage > rate.urban[row][0] &&
                 rate.urban[row + 1][0] == -1) {
        break;
      }
    }
    for (col = 0; rate.urban[0][col] != -1; col++) {
      if (user.voltage >= rate.urban[0][col] &&
          user.voltage < rate.urban[0][col + 1]) {
        col++;
        break;
      } else if (rate.urban[0][col + 1] == -1 &&
                 user.voltage > rate.urban[0][col]) {
        break;
      }
    }
    fee = (currentUsage - lastUsage) * rate.urban[row][col];
  } else if (user.type == 7) {
    for (col = 0; rate.rural[0][col] != -1; col++) {
      if (user.voltage >= rate.rural[0][col] &&
          currentUsage < rate.rural[0][col + 1]) {
        col++;
        break;
      } else if (rate.rural[0][col + 1] == -1 &&
                 currentUsage >= rate.rural[0][col]) {
        break;
      }
    }
    fee = (currentUsage - lastUsage) * rate.rural[1][col];
  } else if (user.type == 4) {
    for (col = 0; rate.ent[0][col] != -1; col++) {
      if (user.voltage >= rate.ent[0][col] &&
          user.voltage < rate.ent[0][col + 1]) {
        col++;
        break;
      } else if (rate.ent[0][col + 1] == -1 &&
                 user.voltage >= rate.ent[0][col]) {
        break;
      }
    }
    fee = (currentUsage - lastUsage) * rate.ent[1][col];
  } else if (user.type == 5) {
    for (col = 0; rate.ent[0][col] != -1; col++) {
      if (currentUsage >= rate.ent[0][col] &&
          currentUsage < rate.ent[1][col + 1]) {
        col++;
        break;
      } else if (rate.ent[0][col + 1] == -1 &&
                 currentUsage >= rate.ent[0][col]) {
        break;
      }
      fee = (currentUsage - lastUsage) * rate.ent[2][col];
    }
  }
  cout << endl;
  cout << "row: " << row << " col: " << col << endl;
  cout << "rate: " << rate.urban[row][col] << endl;
  cout << "fee: " << fee << endl;
}
void updateUserReadStatus(int username, int currentUsage, int fee) {
  fstream file;
  file.open(FLOC_USERBASICINFO, ios::binary | ios::in | ios::out | ios::app);
  while (1) {
    userinfo currentUser;
    file.read((char*)&currentUser, sizeof(userinfo));
    if (file.eof()) {
      file.close();
      cout << "Cannot find the user" << endl;
      return;
    }
    if (currentUser.No == username) {
      currentUser.last_month_usage = currentUsage;
      currentUser.balance = currentUser.balance - fee;
      file.seekg(-(sizeof(userinfo), ios::cur));
      file.write((char*)&currentUser, sizeof(userinfo));
      file.close();
    }
  }
}
void pushReadToHistory(int username, int lastUsage, int currentUsage, int rateNo, double fee) {
  userinfo user = getUserInfo(username);
  userbill bill;
  bill.caseNo = genCaseNo();
  bill.user_record = user;
  bill.last_month_usage = user.last_month_usage;
  bill.read_date = getCurrentTime();
  bill.read = true;
  chargeFeedback(username, lastUsage, currentUsage, bill.rateNo, fee);
  fstream file;
  file.open(FLOC_BILLDETAIL, ios::binary | ios::out | ios::app);
  file.write((char*)&bill, sizeof(userbill));
  file.close();
}
// end of update=============================
void changeMRInfo(MRdef mr) {
  MRdef mrtmp;
  fstream origin;
  fstream temp;
  origin.open(FLOC_MRINFO, ios::binary | ios::in);
  temp.open(FLOC_EDITMRINFO_TEMP, ios::binary | ios::out);
  while (origin.read((char*)&mrtmp, sizeof(MRdef))) {
    if (mrtmp.No == mr.No)
      temp.write((char*)&mr, sizeof(MRdef));
    else
      temp.write((char*)&mrtmp, sizeof(MRdef));
  }
  temp.close();
  origin.close();
  origin.open(FLOC_USERBASICINFO, ios::binary | ios::out);
  temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::in);
  while (temp.read((char*)&mrtmp, sizeof(MRdef))) {
    origin.write((char*)&mrtmp, sizeof(MRdef));
  }
  temp.close();
  origin.close();
}
void deleteMRInfo(MRdef mr) {
  MRdef mrtmp;
  fstream origin;
  fstream temp;
  origin.open(FLOC_MRINFO, ios::binary | ios::in);
  temp.open(FLOC_EDITMRINFO_TEMP, ios::binary | ios::out);
  while (origin.read((char*)&mrtmp, sizeof(MRdef))) {
    if (mrtmp.No == mr.No)
      continue;
    else
      temp.write((char*)&mrtmp, sizeof(userinfo));
  }
  temp.close();
  origin.close();
  origin.open(FLOC_MRINFO, ios::binary | ios::out);
  temp.open(FLOC_EDITMRINFO_TEMP, ios::binary | ios::in);
  while (temp.read((char*)&mrtmp, sizeof(MRdef))) {
    origin.write((char*)&mrtmp, sizeof(MRdef));
  }
  temp.close();
  origin.close();
}
// Commom ===================================================================
void storeUserInfo(userinfo use) {
  fstream temp;
  temp.open(FLOC_USERBASICINFO, ios::binary | ios::app | ios::out);
  temp.write((char*)&use, sizeof(userinfo));
  temp.close();
}
void deleteUserInfo(userinfo use) {
  userinfo tmpInfo;
  fstream origin;
  fstream temp;
  origin.open(FLOC_USERBASICINFO, ios::binary | ios::in);
  temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::out);
  while (origin.read((char*)&tmpInfo, sizeof(userinfo))) {
    if (tmpInfo.No == use.No)
      continue;
    else
      temp.write((char*)&tmpInfo, sizeof(userinfo));
  }
  temp.close();
  origin.close();
  origin.open(FLOC_USERBASICINFO, ios::binary | ios::out);
  temp.open(FLOC_EDITUSERINFO_TEMP, ios::binary | ios::in);
  while (temp.read((char*)&tmpInfo, sizeof(userinfo))) {
    origin.write((char*)&tmpInfo, sizeof(userinfo));
  }
  temp.close();
  origin.close();
}