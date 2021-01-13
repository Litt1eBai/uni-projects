#include "headerfiles.h"
#include "user.h"
using namespace std;

// Get Reginal Info
void showList(estateUserInfoNode* head) {
  estateUserInfoNode* p = head->next;
  while (1) {
    if (p == NULL) {
      break;
    }
    cout << p->info.id << " " << p->info.read_now << endl;
    p = p->next;
  }
  return;
}
void showList_district(unreadRegionInfoNode* head) {
  unreadRegionInfoNode* p = head->next;
  while (1) {
    if (p == NULL) {
      break;
    }
    cout << p->region.district << " " << p->unread << endl;
    p = p->next;
  }
  return;
}
void showList_street(unreadRegionInfoNode* head) {
  unreadRegionInfoNode* p = head->next;
  while (1) {
    if (p == NULL) {
      cout << "No user unread in this region";
      break;
    }
    cout << p->region.street << " " << p->unread << endl;
    p = p->next;
  }
  return;
}
// Meter Reader_Menu
void MRListUnread() {
  system("clear");
  cout << "USER MANAGEMENT - USER LIST" << endl;
  cout << "===================================================================="
          "=================================================================="
       << endl;
  cout << "Number                Name	                                   "
          "Address                                                             "
          "    "
       << endl;
  cout << "--------------------------------------------------------------------"
          "------------------------------------------------------------------"
       << endl;
  userinfo user;
  fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
  while (readUser.read((char*)&user, sizeof(userinfo))) {
    if (user.read_now == false && user.type >= 3)
      cout << setw(11) << right << setfill('0') << user.No << '\t' << setw(25)
           << left << setfill(' ') << user.name << setw(20) << left << user.id
           << '\t' << setw(5) << right << setfill(' ') << user.address.unit
           << '-' << setw(3) << right << setfill('0') << user.address.level
           << '-' << setw(4) << right << setfill('0') << user.address.room
           << ", " << setw(15) << setfill(' ') << user.address.estate << ", "
           << setw(25) << user.address.street << ", " << setw(15)
           << user.address.district << ", " << setw(15) << user.address.city
           << endl;
  }
}
void MRListUsers() {
  system("clear");
  cout << "USER MANAGEMENT - USER LIST" << endl;
  cout << "======================================================================================================================================"
       << endl;
  cout << "Number                Name	               Balance  Status    Usage      Read Status             "
       << endl;
  cout << "--------------------------------------------------------------------------------------------------------------------------------------"
       << endl;
  userinfo user;
  fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
  while (1) {
    readUser.read((char*)&user, sizeof(userinfo));
    if (readUser.eof())
      break;
    // if (user.read_now == false)
    cout << setw(11) << right << setfill('0') << user.No << '\t' << setw(25)
         << left << setfill(' ') << user.name << '\t' << setw(4) << user.balance << "\t";
    if (user.powercut == true)
      cout << setw(6) << right << "cut" << '\t';
    else
      cout << setw(6) << left << "using" << '\t';
    cout << setw(6) << left << user.last_month_usage << "\t";

    if (user.read_now)
      cout << setw(6) << left << "read" << '\t';
    else
      cout << setw(6) << left << "Unread" << '\t';
    cout << user.last_read.h << ":" << user.last_read.min << ":"
         << user.last_read.sec << " " << user.last_read.d << "/"
         << user.last_read.m << "/" << user.last_read.y << endl;
  }
  readUser.close();
  char ch;
  cin >> ch;
}
void MRInput(char* district, char* street, char* estate) {
  int read = 0;
  int unread = 0;
  estateUserInfoNode* head = getEstateUserUnread(district, street, estate, read, unread);
  showList(head);  // test
  estateUserInfoNode* p = head;
  int usage = 0;
  while (usage != -1) {
    if (p->next == NULL) {
      system("clear");
      cout << "You've completed inputting, thank you" << endl;
      break;
    }
    p = p->next;
    system("clear");
    cout << "BILL INPUT" << endl;
    cout << "=====================================================" << endl;
    cout << "You are inputting bill information of:" << endl;
    cout << p->info.address.estate << ", " << p->info.address.street << ", "
         << p->info.address.district << ", " << p->info.address.city << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Information for: " << p->info.address.room << ", "
         << p->info.address.unit << ", " << p->info.address.estate << ", "
         << p->info.address.street << endl;
    cout << endl;
    cout << "User: " << p->info.name << endl;
    cout << "User No. " << p->info.No << endl;
    cout << "User ID: " << p->info.id << endl;
    cout << "Balance: " << p->info.balance << endl;
    cout << "Power Status: ";
    if (p->info.powercut == false) {
      cout << "Using";
    } else {
      cout << "Cut";
    }
    cout << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Your progress:" << endl;
    cout << "Read: " << read << "/" << unread << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Input -1 to exit" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Usage: ";
    cin >> usage;
    // pushToHistory(p->info.No, currentUsage);
    read++;
  }
}
void MROverview_estate(int username, char* district, char* street) {
  MRdef mywork;
  mywork = getMRDetail(username);
  char estate[32];
  do {
    unreadRegionInfoNode* estateListHead = getUnreadRegions_estates(district, street);
    system("clear");
    cout << "BILL INPUT - ESTATE OVERVIEW" << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << "Unread estates in " << street << ", " << district << " district" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Estate" << '\t'  << "Unread" << endl;
    cout << "-----------------------------------------------" << endl;
    unreadRegionInfoNode* p = estateListHead->next;
    while (1) {
      if (p == NULL) {
        break;
      }
      cout << left << setw(15) << p->region.estate << '\t' << right << p->unread << endl;
      p = p->next;
    }
    cout << "----------------------------------------------" << endl;
    cout << "You wish to input: ";
    getString(estate);
    if (samestr(estate, (char*)"-1"))
      break;
    MRInput(district, street, estate);
  } while (!samestr(estate, (char*)"-1"));
}
void MROverview_street(int username, char* district) {
  MRdef mywork;
  mywork = getMRDetail(username);
  char street[32];
  do {
    int userread = 0;
    int userunread = 10;
    unreadRegionInfoNode* streetListHead = getUnreadRegions_streets(district);
    system("clear");
    cout << "BILL INPUT - STREET OVERVIEW" << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << "Unread streets in " << district << " district" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Street                      Unread" << endl;
    cout << "----------------------------------------------" << endl;
    unreadRegionInfoNode* p = streetListHead->next;
    while (1) {
      if (p == NULL) {
        break;
      }
      cout << left << setw(25) << p->region.street << '\t' << right << p->unread << endl;
      p = p->next;
    }
    cout << "----------------------------------------------" << endl;
    cout << "You wish to input: ";
    getString(street);
    if (samestr(street, (char*)"-1"))
      break;
    MROverview_estate(username, district, street);
  } while (!samestr(district, (char*)"-1"));
}
void MROverview_district(int username) {
  MRdef mywork;
  mywork = getMRDetail(username);
  char district[32];
  do {
    int userread = 0;
    int userunread = 10;
    unreadRegionInfoNode* districtListHead = getUnreadRegions_districts();
    system("clear");
    cout << "METER READER INPUT - DISTRICT OVERVIEW" << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << "Districts unread" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "District      Unread" << endl;
    cout << "----------------------------------------------" << endl;
    unreadRegionInfoNode* p = districtListHead->next;
    while (1) {
      if (p == NULL) {
        break;
      }
      cout << left << setw(15) << p->region.district << '\t' << right << p->unread << endl;
      p = p->next;
    }
    cout << "----------------------------------------------" << endl;
    cout << "You wish to input: ";
    getString(district);
    if (samestr(district, (char*)"-1"))
      break;
    MROverview_street(username, district);
  } while (!samestr(district, (char*)"-1"));
}
void MRDash(int username) {
  userinfo me;
  MRdef mywork;
  mywork = getMRDetail(username);
  me = getUserInfo(username);
  int userread = getUnread();
  int totaluser_local = totalUser;
  int opt;
  do {
    system("clear");
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
    cout << "3. Show Current Rate Rules" << endl;
    cout << "0. Logout" << endl;
    cin >> opt;
    switch (opt) {
      case 1:
        MROverview_district(username);
        break;
      case 2:
        MRListUsers();
        break;
      case 3:
        showRate();
        break;
      case 0:
        system("clear");
        cout << "Thanks!" << endl;
        cout << endl;
        cout << "Logging out";
        dotDotDot(3);
        return;
      default:
        cout << "Invalid input, please try again" << endl;
    }
  } while (opt != 0);
  system("clear");
  cout << "Thanks!" << endl;
  cout << endl;
  cout << "Exiting";
  dotDotDot(3);
}
// Charger_Menu ===============================================
void showAllBillList() {
  fstream file;
  userbill bill;
  file.open(FLOC_BILLDETAIL, ios::binary | ios::in);
  while (file.read((char*)&bill, sizeof(userbill))) {
    cout << "Case No.: " << bill.caseNo << endl
        << "User No.: "<< bill.user_record.No << endl
        << "User Name: " << bill.user_record.name << endl 
        << "Read: " << bill.read << endl
        << "Current Usage: " << bill.current_usage << endl
        << "Last Month Usage: " << bill.last_month_usage << endl
        << "Read Date: "
        << bill.read_date.y << "-" << bill.read_date.m <<"-" << bill.read_date.d << " "<< bill.pay << endl
        << "Address: " << bill.user_record.address.street << endl
        <<"------------------------------------------------------------------" << endl;
  }
  file.close();
}
void chargerDash(int username) {
  userinfo me;
  me = getUserInfo(username);
  int opt;
  do {
    system("clear");
    cout << "DASHBOARD" << endl;
    cout << "==============================================" << endl;
    cout << me.name << ", greetings!" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Total users: " << totalUser << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Menu:" << endl;
    cout << "1. Show Bill List" << endl;
    cout << "2. " << endl;
    cout << "3. " << endl;
    cout << "0. Logout" << endl;
    cin >> opt;
    switch(opt) {
    case 1: showAllBillList();
      break;
    }
  } while (opt != 0);
}
// Admin Features =============================================
void setdefaultPassword(char id[], char passput[]) {
  int i;
  for (i = 0; i < 6; i++) {
    passput[i] = id[17 - i];
  }
  passput[i] = '\0';
}
// System Settings ============================================
void adminSystemSettings_menu() {
  int opt;
  do {
    system("clear");
    cout << "SYSTEM SETTINGS" << endl;
    cout << "==============================================" << endl;
    cout << "Menu:" << endl;
    cout << "1. Change password" << endl;
    cout << "2. Import user basic information from file" << endl;
    cout << "3. Reset database" << endl;
    cout << "0. Exit" << endl;
    cin >> opt;
    string fileLocation;
    switch (opt) {
      case 1:
        break;
      case 2:
        system("clear");
        cout << "SYSTEM SETTINGS - IMPORT USER INFORMATION" << endl;
        cout << "==============================================" << endl;
        cout << "You wish to import from:" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Location: ";
        getString(fileLocation);
        system("clear");
        cout << "SYSTEM SETTINGS - IMPORT USER INFORMATION" << endl;
        cout << "==============================================" << endl;
        cout << "You wish to import from:" << fileLocation << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Are you sure to store it" << endl;
        cout << "y/n: ";
        char opt;
        cin >> opt;
        if (opt == 'y' || opt == 'Y') {
          userInfoImport(fileLocation);
          break;
        } else {
          cout << "cancelled";
          sleep(1);
        }
      case 3:
        system("clear");
        cout << "ARE YOU SURE?" << endl;
        cout << "This will wipe out all user data" << endl;
        cout << "y/n : ";
        char opt1;
        cin >> opt1;
        if (opt1 == 'y' || opt1 == 'Y') resetDatabase();
        break;
      case 0:
        return;
      default:
        cout << "Invalid input, please try again" << endl;
    }
  } while (opt != 0);
}
// Admin_Menu =================================================
void MRManage() {
  system("clear");
  cout << "USER MANAGEMENT - MATER READER MANAGEMENT" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "Have a glance of how Meter Readers are doing: " << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "Number                Name	          Progress" << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  fstream readMR(FLOC_MRINFO, ios::in | ios::binary);
  MRdef mr;
  while (readMR.read((char*)&mr, sizeof(MRdef))) {
    cout << setw(11) << right << setfill('0') << mr.No << '\t' << setw(25)
         << left << setfill(' ') << mr.name << setw(6) << left << fixed
         << setprecision(3) << mr.progress << "%" << endl;
  }
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  system("clear");
}
void generateUser() {
  userinfo newUser;
  newUser.No = genUserNo();

  system("clear");
  int typchoice;
  cout << "USER USER REGISTRATION - NAME" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating an user" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "Name:";
  getString(newUser.name);

  system("clear");
  cout << "USER REGISTRATION - USER TYPE" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating: " << newUser.name << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "user type:" << endl;
  cout << "--------------------------------------------------------------"<< endl;
  cout << "|  1.Administrator       2.Meter Reader      3.Charger       |"<< endl;
  cout << "|  4.Enterprise User(E1)       5. Enterprise User(E2)        |"<< endl;
  cout << "|  6.Urban User                7.Common Rural User           |"<< endl;
  cout << "|  8.Rural User in Poverty                                   |"<< endl;
  cout << "--------------------------------------------------------------"<< endl;
  cout << "User type: ";
  cin >> typchoice;
  string type;
  while (!(typchoice >= 1 && typchoice <= 8)) {
    cout << "Invalid Input" << endl;
    cin >> typchoice;
  }
  switch (typchoice) {
    case 1:
      type = "Administrator";
      newUser.type = 1;
      break;
    case 2:
      type = "Meter Reader";
      newUser.type = 2;
      break;
    case 3:
      type = "Charger";
      newUser.type = 3;
      break;
    case 4:
      type = "Enterprise User (E1)";
      newUser.type = 4;
      break;
    case 5:
      type = "Enterprise User (E2)";
      newUser.type = 5;
      break;
    case 6:
      type = "Urban User";
      newUser.type = 6;
      break;
    case 7:
      type = "Common Rural User";
      newUser.type = 7;
      break;
    case 8:
      type = "Rural User in Poverty";
      newUser.type = 8;
      break;
  }

  system("clear");
  cout << "USER REGISTRATION - ADDRESS" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating: " << newUser.name << "; " << type << "("
       << newUser.type << ")" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "City: ";
  getString(newUser.address.city);
  while (strlen(newUser.address.city) >= 32) {
    cout << "Invalid city name" << endl;
    cout << "city: ";
    getString(newUser.address.city);
  }

  system("clear");
  cout << "USER REGISTRATION - ADDRESS" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating: " << newUser.name << "; " << type << "("
       << newUser.type << ")" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "Address: " << newUser.address.city << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  if (newUser.type == 7 || newUser.type == 8)
    cout << "Town: ";
  else
    cout << "District: ";
  getString(newUser.address.district);
  while (strlen(newUser.address.district) >= 32) {
    cout << "Invalid district name" << endl;
    cout << "district: ";
    getString(newUser.address.district);
  }

  system("clear");
  cout << "USER REGISTRATION - ADDRESS" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating: " << newUser.name << "; " << type << "("
       << newUser.type << ")" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "Address: " << newUser.address.district << ", "
       << newUser.address.city << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  if (newUser.type == 7 || newUser.type == 8)
    cout << "County: ";
  else
    cout << "Street: ";
  getString(newUser.address.street);
  while (strlen(newUser.address.street) >= 32) {
    cout << "Invalid street name" << endl;
    cout << "street: ";
    getString(newUser.address.street);
  }

  system("clear");
  cout << "USER REGISTRATION - ADDRESS" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating: " << newUser.name << "; " << type << "("
       << newUser.type << ")" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "Address: " << newUser.address.street << ", "
       << newUser.address.district << ", " << newUser.address.city << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  if (newUser.type == 7 || newUser.type == 8)
    cout << "Village: ";
  else
    cout << "Estate: ";
  getString(newUser.address.estate);
  while (strlen(newUser.address.estate) >= 32) {
    cout << "Invalid estate name" << endl;
    cout << "Estate: ";
    getString(newUser.address.estate);
  }

  system("clear");
  cout << "USER REGISTRATION - ADDRESS" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating: " << newUser.name << "; " << type << "("
       << newUser.type << ")" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "Address: " << newUser.address.estate << ", "
       << newUser.address.street << ", " << newUser.address.district << ", "
       << newUser.address.city << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "Unit: ";
  getString(newUser.address.unit);
  while (strlen(newUser.address.unit) >= 32) {
    cout << "Invalid unit name" << endl;
    cout << "unit: ";
    getString(newUser.address.unit);
  }

  system("clear");
  cout << "USER REGISTRATION - ADDRESS" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating: " << newUser.name << "; " << type << "("
       << newUser.type << ")" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "Address: " << newUser.address.unit << " " << newUser.address.estate
       << ", " << newUser.address.street << ", " << newUser.address.district
       << ", " << newUser.address.city << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "Level: ";
  cin >> newUser.address.level;
  while (!cin) {
    cout << "Invalid level" << endl;
    cout << "level: ";
    cin >> newUser.address.level;
  }

  system("clear");
  cout << "USER REGISTRATION - ADDRESS" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating: " << newUser.name << "; " << type << "("
       << newUser.type << ")" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "Address: " << newUser.address.level << "-" << newUser.address.level
       << " " << newUser.address.estate << ", " << newUser.address.street
       << ", " << newUser.address.district << ", " << newUser.address.city
       << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "Room: ";
  cin >> newUser.address.room;
  while (!cin) {
    cout << "Invalid room" << endl;
    cout << "Room: ";
    cin >> newUser.address.room;
  }

  system("clear");
  cout << "USER REGISTRATION - ID" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "You are creating: " << newUser.name << "; " << type << "("
       << newUser.type << ")" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "Address: " << newUser.address.unit << "-" << newUser.address.level
       << "-" << newUser.address.room << " " << newUser.address.estate << ", "
       << newUser.address.street << ", " << newUser.address.district << ", "
       << newUser.address.city << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "User's National ID: ";
  cin >> newUser.id;
  while (strlen(newUser.id) != 18) {
    cout << "Invalid ID" << endl;
    strcpy(newUser.password, "set default password error");
    cout << "User's National ID: ";
    cin >> newUser.id;
  }

  setdefaultPassword(newUser.id, newUser.password);
  newUser.balance = 100;
  newUser.powercut = false;
  newUser.voltage = 220;
  newUser.last_read = getCurrentTime();
  newUser.read_now = true;
  newUser.last_month_usage = 0;

  system("clear");
  cout << "USER REGISTRATION - FINISH" << endl;
  cout << "===================================================================="
          "=="
       << endl;
  cout << "*************************Congratulations!***************************"
          "**"
       << endl;
  cout << "You have created a new user, here is the detail" << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "Name: " << newUser.name << endl;
  cout << "Type: " << type << "(" << newUser.type << ")" << endl;
  cout << "User number: " << newUser.No << endl;
  cout << "National ID: " << newUser.id << endl;
  cout << "Balance: " << newUser.balance << " CNY" << endl;
  cout << " Address: " << newUser.address.unit << "-" << newUser.address.level
       << "-" << newUser.address.room << " " << newUser.address.estate << ", "
       << newUser.address.street << ", " << newUser.address.district << ", "
       << newUser.address.city << endl;
  cout << "Default password: " << newUser.password << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "Are you sure to store it" << endl;
  cout << "y/n: ";
  char opt;
  cin >> opt;
  if (opt == 'y' || opt == 'Y') {
    fstream userBasicInfo;
    userBasicInfo.open(FLOC_USERBASICINFO, ios::binary | ios::app | ios::out);
    if (!userBasicInfo) {
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
    userBillInfo.open(FLOC_BILLDETAIL, ios::binary | ios:: app | ios::out);
    userBillInfo.write((char*)&newUserBill, sizeof(userbill));
    userBillInfo.close();

    if (newUser.type == 2) {
      MRdef MRinfo;
      MRinfo.No = newUser.No;
      strcpy(MRinfo.name, newUser.name);
      MRinfo.progress = 0;
      fstream MRfile;
      MRfile.open(FLOC_MRINFO, ios::binary | ios::app);
      MRfile.write((char*)&MRinfo, sizeof(MRdef));
      MRfile.close();
    }

    getTotalUser();
    cout << endl;
    cout << "Successful" << endl;
    sleep(1);
  } else {
    cout << endl;
    cout << "Cancelled" << endl;
    sleep(1);
  }
}
void adminEditUser_Detail(int username) {
  int opt;
  do {
    userinfo user;
    user = getUserInfo(username);
    system("clear");
    getTotalUser();
    cout << "USER MANAGEMENT - EDIT USER DETAIL" << endl;
    cout << "=================================================================="
            "===="
         << endl;
    cout << "Detail of " << user.name << endl;
    cout << endl;
    cout << "1. Name: " << user.name << endl;
    cout << "2. Type: " << rtnType(user.type) << "(" << user.type << ")"
         << endl;
    cout << "3.  User Number: " << user.No << endl;
    cout << "4. ID: " << user.id << endl;
    cout << "#. Balance: " << user.balance << " CNY" << endl;
    cout << "5. Address: " << user.address.unit << "-" << user.address.level
         << "-" << user.address.room << " " << user.address.estate << ", "
         << user.address.street << ", " << user.address.district << ", "
         << user.address.city << endl;
    cout << "6. Password: " << user.password << endl;
    cout << "------------------------------------------------------------------"
            "----"
         << endl;
    cout << "What do you want to change about the user " << user.name << endl;
    cout << "1 - 6 Change the corresponding information" << endl;
    cout << "7.    Remove user" << endl;
    cout << "0.    Exit" << endl;
    cin >> opt;
    if (opt == 1) {
      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - NAME EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the name of " << user.name << endl;
      cout << endl;
      cout << "Name: " << user.name << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Change to: ";
      char newname[32];
      getString(newname);
      cout << "Are you sure to store it?" << endl;
      char choice1;
      cin >> choice1;
      if (choice1 == 'y' || choice1 == 'Y') {
        strcpy(user.name, newname);
        changeUserInfo(user);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 2) {
      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - USER TYPE EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the name of " << user.name << endl;
      cout << endl;
      cout << "Type: " << rtnType(user.type) << "(" << user.type << ")" << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Choose the type below" << endl;
      cout << "--------------------------------------------------------------"
           << endl;
      cout << "|  1.Administrator       2.Meter Reader      3.Charger       |"
           << endl;
      cout << "|  4.Enterprise User(E1)       5. Enterprise User(E2)        |"
           << endl;
      cout << "|  6.Urban User                7.Common Rural User           |"
           << endl;
      cout << "|  8.Rural User in Poverty                                   |"
           << endl;
      cout << "--------------------------------------------------------------"
           << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Change to: ";
      int user_typ;
      cin >> user_typ;
      while (!(user_typ >= 1 && user_typ <= 8)) {
        cout << "Invalid Input" << endl;
        cout << "User type: ";
        cin >> user_typ;
      }

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - USER TYPE EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "The new user type of" << user.name
           << " is: " << rtnType(user_typ) << "(" << user_typ << ")" << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << endl;
      cout << "Are you sure to store it?" << endl;
      char choice2;
      cin >> choice2;
      if (choice2 == 'y' || choice2 == 'Y') {
        user.type = user_typ;
        changeUserInfo(user);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 3) {
      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - NUMBER EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the number of " << user.name << endl;
      cout << endl;
      cout << "Number: " << user.No << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Change to: ";
      int newNo;
      cin >> newNo;

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - NUMBER EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "The new type of" << user.name << " is: " << newNo << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Are you sure to store it?" << endl;
      char choice3;
      cin >> choice3;
      if (choice3 == 'y' || choice3 == 'Y') {
        user.No = newNo;
        changeUserInfo(user);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 4) {
      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ID EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the ID of " << user.name << endl;
      cout << endl;
      cout << "ID: " << user.id << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Change to: ";
      char newID[18];
      getString(newID);
      while (strlen(newID) != 18) {
        cout << "Invalid ID" << endl;
        cout << "ID: ";
        getString(newID);
      }
      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ID EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "The new ID of" << user.name << " is: " << newID << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Are you sure to store it?" << endl;
      char choice3;
      cin >> choice3;
      if (choice3 == 'y' || choice3 == 'Y') {
        strcpy(user.id, newID);
        changeUserInfo(user);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 5) {
      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the address of " << user.name << endl;
      cout << endl;
      cout << "Original Address: " << user.address.unit << "-"
           << user.address.level << "-" << user.address.room << " "
           << user.address.estate << ", " << user.address.street << ", "
           << user.address.district << ", " << user.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "City: ";
      getString(user.address.city);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the address of " << user.name << endl;
      cout << endl;
      cout << "Address: " << user.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "District: ";
      getString(user.address.district);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the address of " << user.name << endl;
      cout << endl;
      cout << "Address: " << user.address.district << ", " << user.address.city
           << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Street: ";
      getString(user.address.street);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the address of " << user.name << endl;
      cout << endl;
      cout << "Address: " << user.address.street << ", "
           << user.address.district << ", " << user.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Estate: ";
      getString(user.address.estate);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the address of " << user.name << endl;
      cout << endl;
      cout << "Address: "
           << " " << user.address.estate << ", " << user.address.street << ", "
           << user.address.district << ", " << user.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Unit: ";
      getString(user.address.unit);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the address of " << user.name << endl;
      cout << endl;
      cout << "Address: " << user.address.unit << "-"
           << " " << user.address.estate << ", " << user.address.street << ", "
           << user.address.district << ", " << user.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Level: ";
      cin >> user.address.level;

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the address of " << user.name << endl;
      cout << endl;
      cout << "Address: " << user.address.unit << "-" << user.address.level
           << " " << user.address.estate << ", " << user.address.street << ", "
           << user.address.district << ", " << user.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Room: ";
      cin >> user.address.room;
      cout << "Are you sure to store it?" << endl;
      char choice4;
      cin >> choice4;
      if (choice4 == 'y' || choice4 == 'Y') {
        changeUserInfo(user);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }

    } else if (opt == 6) {
      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - PASSWORD CHANGE" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Editing the name of " << user.name << endl;
      cout << endl;
      cout << "Password: " << user.password << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Change to: ";
      char newPassword[32];
      getString(newPassword);
      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - PASSWORD CHANGE" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "The new password of" << user.name << " is: " << newPassword
           << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Are you sure to store it?" << endl;
      char choice4;
      cin >> choice4;
      if (choice4 == 'y' || choice4 == 'Y') {
        strcpy(user.password, newPassword);
        changeUserInfo(user);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 7) {
      system("clear");
      cout << "USER MANAGEMENT - REMOVE USER" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are removing user: " << user.name
           << "; user number: " << user.No << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Are you sure?" << endl;
      char choice6;
      cin >> choice6;
      if (choice6 == 'y' || choice6 == 'Y') {
        deleteUserInfo(user);
        cout << "Successful" << endl;
        sleep(1);
        return;
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 0) {
      return;
    }
  } while (opt != 0);
}
void adminEditUsers() {
  int userno;
  do {
    system("clear");
    cout << "USER MANAGEMENT - USER LIST" << endl;
    cout << "=================================================================="
            "=================================================================="
            "=================================================================="
            "======"
         << endl;
    cout << "Number                Name	                Type                   "
            "   ID                                         Address             "
            "                                                       Password"
         << endl;
    cout << "------------------------------------------------------------------"
            "------------------------------------------------------------------"
            "------------------------------------------------------------------"
            "------"
         << endl;
    userinfo user;
    fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
    while (readUser.read((char*)&user, sizeof(userinfo))) {
      string type;
      type = rtnType(user.type);
      cout << setw(11) << right << setfill('0') << user.No << '\t' << setw(25)
           << left << setfill(' ') << user.name << setw(25) << left << type
           << setw(20) << left << user.id << '\t' << setw(5) << right
           << setfill(' ') << user.address.unit << '-' << setw(3) << right
           << setfill('0') << user.address.level << '-' << setw(4) << right
           << setfill('0') << user.address.room << ", " << setw(15)
           << setfill(' ') << user.address.estate << ", " << setw(25)
           << user.address.street << ", " << setw(15) << user.address.district
           << ", " << setw(15) << user.address.city << '\t' << setw(16) << right
           << user.password << endl;
    }
    cout << "------------------------------------------------------------------"
            "------------------------------------------------------------------"
            "------------------------------------------------------------------"
            "-----"
         << endl;
    cout << "Input the user's serial number that you wish to see in detail "
            "(Input -1 to exit)"
         << endl;
    cout << "No. ";
    cin >> userno;
    if (userno == -1) {
      return;
    } else if (validUser(userno)) {
      adminEditUser_Detail(userno);
    } else {
      cout << "Invalid number, please try again";
      sleep(1);
    }
  } while (userno != -1);
}
void adminListUsers() {
  system("clear");
  cout << "USER MANAGEMENT - USER LIST" << endl;
  cout << "===================================================================="
          "===================================================================="
          "========================================================="
       << endl;
  cout << "Number                Name	                Type                   "
          "   ID                                         Address               "
          "                                              Read"
       << endl;
  cout << "--------------------------------------------------------------------"
          "--------------------------------------------------------------------"
          "---------------------------------------------------------"
       << endl;
  userinfo user;
  fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
  while (readUser.read((char*)&user, sizeof(userinfo))) {
    string type;
    type = rtnType(user.type);
    cout << setw(11) << right << setfill('0') << user.No << '\t' << setw(25)
         << left << setfill(' ') << user.name << setw(25) << left << type
         << setw(20) << left << user.id << '\t' << setw(5) << right
         << setfill(' ') << user.address.unit << '-' << setw(3) << right
         << setfill('0') << user.address.level << '-' << setw(4) << right
         << setfill('0') << user.address.room << ", " << setw(15)
         << setfill(' ') << user.address.estate << ", " << setw(25)
         << user.address.street << ", " << setw(15) << user.address.district
         << ", " << setw(15) << user.address.city << '\t' << setw(4) << right
         << user.read_now << endl;
  }
  cout << "--------------------------------------------------------------------"
          "--------------------------------------------------------------------"
          "---------------------------------------------------------"
       << endl;
  system("clear");
}
void userManage() {
  int opt;
  do {
    system("clear");
    getTotalUser();
    cout << "USER MANAGEMENT" << endl;
    cout << "=================================================================="
            "===="
         << endl;
    cout << "Total users: " << totalUser << endl;
    cout << "------------------------------------------------------------------"
            "----"
         << endl;
    cout << "Menu: " << endl;
    cout << "1. Edit user information" << endl;
    cout << "2. List users" << endl;
    cout << "3. Meter Reader Management" << endl;
    cout << "0. Exit" << endl;
    cin >> opt;
    switch (opt) {
      case 1:
        adminEditUsers();
        break;
      case 2:
        adminListUsers();
        break;
      case 3:
        MRManage();
        break;
      case 0:
        return;
      default:
        cout << "Invalid Input" << endl;
    }
  } while (opt != 0);
}
void AdminDash(int username) {
  userinfo me;
  me = getUserInfo(username);
  int opt;
  do {
    system("clear");
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
    switch (opt) {
      case 1:
        userManage();
        break;
      case 2:
        generateUser();
        break;
      case 3:
        adminSystemSettings_menu();
        break;
      case 0:
        system("clear");
        cout << "Thanks!" << endl;
        cout << endl;
        cout << "Logging out";
        dotDotDot(3);
        return;
      default:
        cout << "Invalid input, please try again" << endl;
    }
  } while (opt != 0);
}
// User_Menu ===================================================
void userEditBasicInfo(int username) {
  int opt;
  do {
    userinfo me;
    me = getUserInfo(username);
    system("clear");
    getTotalUser();
    cout << "USER SETTINGS - BASIC INFORMATION EDIT" << endl;
    cout << "=================================================================="
            "===="
         << endl;
    cout << "Hi, " << me.name << ", Here are things about you:" << endl;
    cout << endl;
    cout << "1. Name: " << me.name << endl;
    cout << "#. Type: " << rtnType(me.type) << "(" << me.type << ")" << endl;
    cout << "#. User Number: " << me.No << endl;
    cout << "2. ID: " << me.id << endl;
    cout << "#. Balance" << me.balance << endl;
    cout << "3. Address: " << me.address.unit << "-" << me.address.level << "-"
         << me.address.room << " " << me.address.estate << ", "
         << me.address.street << ", " << me.address.district << ", "
         << me.address.city << endl;
    cout << "4. Password: " << me.password << endl;
    cout << "------------------------------------------------------------------"
            "----"
         << endl;
    cout << "What do you want to change about you: " << endl;
    cout << "1 - 4 Change the corresponding information" << endl;
    cout << "5.    Deactivate account" << endl;
    cout << "0.    Exit" << endl;
    cin >> opt;
    if (opt == 1) {
      system("clear");
      cout << "USER SETTINGS - BASIC INFORMATION EDIT - NAME EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing the name from:" << me.name << endl;
      cout << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "To: ";
      char newname[32];
      getString(newname);
      cout << "Are you sure to store it?" << endl;
      char choice1;
      cin >> choice1;
      if (choice1 == 'y' || choice1 == 'Y') {
        strcpy(me.name, newname);
        changeUserInfo(me);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 2) {
      system("clear");
      cout << "USER SETTINGS - EDIT BASIC INFORMATION - ID EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing your ID from: " << me.id << endl;
      cout << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "To: ";
      char newID[18];
      getString(newID);
      while (strlen(newID) != 18) {
        cout << "Invalid ID" << endl;
        cout << "ID: ";
        getString(newID);
      }
      system("clear");
      cout << "USER SETTINGS - EDIT BASIC INFORMATION - ID EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Your new ID is: " << newID << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Are you sure to store it?" << endl;
      char choice3;
      cin >> choice3;
      if (choice3 == 'y' || choice3 == 'Y') {
        strcpy(me.id, newID);
        changeUserInfo(me);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 3) {
      system("clear");
      cout << "USER SETTINGS - EDIT BASIC INFORMATION - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing your address: " << endl;
      cout << endl;
      cout << "Original Address: " << me.address.unit << "-" << me.address.level
           << "-" << me.address.room << " " << me.address.estate << ", "
           << me.address.street << ", " << me.address.district << ", "
           << me.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "City: ";
      getString(me.address.city);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing your address: " << endl;
      cout << endl;
      cout << "Address: " << me.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "District: ";
      getString(me.address.district);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing your address: " << endl;
      cout << endl;
      cout << "Address: " << me.address.district << ", " << me.address.city
           << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Street: ";
      getString(me.address.street);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing your address: " << endl;
      cout << endl;
      cout << "Address: " << me.address.street << ", " << me.address.district
           << ", " << me.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Estate: ";
      getString(me.address.estate);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing your address: " << endl;
      cout << endl;
      cout << "Address: "
           << " " << me.address.estate << ", " << me.address.street << ", "
           << me.address.district << ", " << me.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Unit: ";
      getString(me.address.unit);

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing your address: " << endl;
      cout << endl;
      cout << "Address: " << me.address.unit << "-"
           << " " << me.address.estate << ", " << me.address.street << ", "
           << me.address.district << ", " << me.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Level: ";
      cin >> me.address.level;

      system("clear");
      cout << "USER MANAGEMENT - EDIT USER DETAIL - ADDRESS EDIT" << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing your address: " << endl;
      cout << endl;
      cout << "Address: " << me.address.unit << "-" << me.address.level << " "
           << me.address.estate << ", " << me.address.street << ", "
           << me.address.district << ", " << me.address.city << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Room: ";
      cin >> me.address.room;
      cout << "Are you sure to store it?" << endl;
      char choice4;
      cin >> choice4;
      if (choice4 == 'y' || choice4 == 'Y') {
        changeUserInfo(me);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }

    } else if (opt == 4) {
      system("clear");
      cout << "USER SETTINGS - EDIT BASIC INFORMATION - PASSWORD CHANGE"
           << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You are changing your password" << endl;
      cout << endl;
      cout << "Password: " << me.password << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Change to: ";
      char newPassword[32];
      getString(newPassword);
      system("clear");
      cout << "USER SETTINGS - EDIT BASIC INFORMATION - PASSWORD CHANGE"
           << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "Your new password"
           << " is: " << newPassword << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Are you sure to store it?" << endl;
      char choice4;
      cin >> choice4;
      if (choice4 == 'y' || choice4 == 'Y') {
        strcpy(me.password, newPassword);
        changeUserInfo(me);
        cout << "Successful" << endl;
        sleep(1);
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 5) {
      system("clear");
      cout << "USER SETTINGS - EDIT BASIC INFORMATION - DEACTIVATE ACCOUNT"
           << endl;
      cout << "================================================================"
              "======"
           << endl;
      cout << "You account will be removed permanently" << endl;
      cout << "----------------------------------------------------------------"
              "------"
           << endl;
      cout << "Are you sure?" << endl;
      char choice6;
      cin >> choice6;
      if (choice6 == 'y' || choice6 == 'Y') {
        deleteUserInfo(me);
        cout << "Successful" << endl;
        sleep(1);
        return;
      } else {
        cout << endl;
        cout << "Cancelled" << endl;
        sleep(1);
      }
    } else if (opt == 0) {
      return;
    } else {
      cout << "Invalid Input" << endl;
    }
  } while (opt != 0);
}
void userDash(int username) {
  userinfo me;
  me = getUserInfo(username);
  int opt;
  do {
    system("clear");
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
    cout << "Power Status: ";
    if (me.powercut == false) {
      cout << "Using" << endl;
    } else {
      cout << "Cut" << endl;
    }
    cout << "Current Usage: ";
    if (me.read_now == true) {
      cout << me.last_month_usage << endl;
    } else {
      cout << "Unread" << endl;
    }
    cout << "ID: " << me.id << endl;
    cout << "Address: " << me.address.unit << "-" << me.address.level << "-"
         << me.address.room << " " << me.address.estate << ", "
         << me.address.street << ", " << me.address.district << ", "
         << me.address.city << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Menu:" << endl;
    cout << "1. Edit information" << endl;
    cout << "2. Billing history" << endl;
    cout << "0. Logout" << endl;
    cin >> opt;
    switch (opt) {
      case 1:
        userEditBasicInfo(me.No);
        break;
      case 2:
        cout << "Not available" << endl;
        break;
      case 0:
        system("clear");
        cout << "Thanks!" << endl;
        cout << endl;
        cout << "Logging out";
        dotDotDot(3);
        return;
      default:
        cout << "Invalid input, please try again" << endl;
    }
  } while (opt != 0);
}
// Login ======================================================
int validPassword(int username, char userPass[]) {
  userinfo user;
  user = getUserInfo(username);
  if (samestr(user.password, userPass)) return 1;
  return 0;
}
void loginGuide(int username) {
  userinfo user;
  user = getUserInfo(username);
  switch (user.type) {
    case 1:
      AdminDash(username);
      break;
    case 2:
      MRDash(username);
      break;
    case 3:
      chargerDash(username);
      break;
    case 4:
    case 5:
    case 6:
      userDash(username);
      break;
    case 7:
      break;
  }
}
void login() {	
  int username;
  do {
    system("clear");
    cout << "SYSTEM - LOGIN" << endl;
    cout << "=================================================" << endl;
    cout << "To start, please login" << endl;
    cout << endl;
    cout << "Username: ";
    cin >> username;
    if (validUser(username)) {
      cout << "Password: ";
      char userPass[32];
      cin >> userPass;
      if (validPassword(username, userPass)) {
        loginGuide(username);
      } else {
        system("clear");
        cout << "SYSTEM - LOGIN ERROR" << endl;
        cout << "==============================================" << endl;
        cout << endl;
        cout << "**********************************************" << endl;
        cout << "*     Invalid password, Please try again     *" << endl;
        cout << "**********************************************" << endl;
        sleep(1);
      }
    } else {
      system("clear");
      cout << "SYSTEM - LOGIN ERROR" << endl;
      cout << "==============================================" << endl;
      cout << endl;
      cout << "**********************************************" << endl;
      cout << "*     Invalid username, Please try again     *" << endl;
      cout << "**********************************************" << endl;
      sleep(1);
    }
  } while (username >= 0);
}
void checkAndGenerate() {
  fstream userinfofile;
  userinfofile.open(FLOC_USERBASICINFO, ios::binary | ios::in);
  if (!userinfofile) {
    system("mkdir -p /home/jensen/Documents/code/ElectricityBillingSystem/");
    resetDatabase();
    cout << "*************************************************" << endl;
    cout << "* Hi, Welcome to the electricity billing         *" << endl;
    cout << "*************************************************" << endl;
    sleep(1);
    system("clear");
    cout << "*************************************************" << endl;
    cout << "*      We are setting up everything for you     *" << endl;
    cout << "*************************************************" << endl;
    sleep(1);
    system("clear");
    cout << "*************************************************" << endl;
    cout << "*                  Almost done                  *" << endl;
    cout << "*************************************************" << endl;
    sleep(1);
    system("clear");
    cout << "***********************************************************************"<< endl;
    cout << "* You are the administrator, use the following information to sign in *"<< endl;
    cout << "* Username: 0                                                         *"<< endl;
    cout << "* Password: root                                                      *"<< endl;
    cout << "***********************************************************************"<< endl;
    system("clear");
    system("clear");
    cout << "*********************************************" << endl;
    cout << "*                  Thanks!                  *" << endl;
    cout << "*********************************************" << endl;
    sleep(1);
    system("clear");
    cout << "*********************************************" << endl;
    cout << "*                   Enjoy!                  *" << endl;
    cout << "*********************************************" << endl;
    sleep(1);
  } else {
    cout << "welcome to electricity billing" << endl;
    system("clear");
    sleep(1);
  }
}
//Main ============================================================
int main() {
  checkAndGenerate();
  getTotalUser();
  defineUnread();
  //MRListUsers();
  //login();
  //MRDash(6);
}