#include "headerfiles.h"
#include "ratedisplay.h"
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
	system("cls");
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
	system("cls");
	cout << "USER MANAGEMENT - USER LIST" << endl;
	cout << "===================================================================="
		"=================================================================="
		<< endl;
	cout << "Number                Name	               Balance  Status    "
		"Usage      Read Status             "
		<< endl;
	cout << "--------------------------------------------------------------------"
		"------------------------------------------------------------------"
		<< endl;
	userinfo user;
	fstream readUser(FLOC_USERBASICINFO, ios::in | ios::binary);
	while (1) {
		readUser.read((char*)&user, sizeof(userinfo));
		if (readUser.eof()) break;
		// if (user.read_now == false)
		cout << setw(11) << right << setfill('0') << user.No << '\t' << setw(25)
			<< left << setfill(' ') << user.name << '\t' << setw(4) << user.balance
			<< "\t";
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
void MRInput_Urban(char* district, char* street, char* estate) {
	int read = 0;
	int unread = 0;
	estateUserInfoNode* head =
		getEstateUserUnread(district, street, estate, read, unread);
	showList(head);  // test
	estateUserInfoNode* p = head;
	int usage = 0;
	while (usage != -1) {
		if (p->next == NULL) {
			system("cls");
			cout << "You've completed inputting, thank you" << endl;
			break;
		}
		p = p->next;
		system("cls");
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
		}
		else {
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
		pushReadToHistory(p->info.No, p->info.last_month_usage, usage);
		read++;
	}
}
void MRInput_Rural(char* district, char* street, char* estate) {
	int read = 0;
	int unread = 0;
	estateUserInfoNode* head =
		getEstateUserUnread(district, street, estate, read, unread);
	showList(head);  // test
	estateUserInfoNode* p = head;
	int usage1 = 0;
	int usage2 = 0;
	while (usage1 != -1) {
		if (p->next == NULL) {
			system("cls");
			cout << "You've completed inputting, thank you" << endl;
			break;
		}
		p = p->next;
		system("cls");
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
		}
		else {
			cout << "Cut";
		}
		cout << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "Your progress:" << endl;
		cout << "Read: " << read << "/" << unread << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "Input -1 to exit" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "Common Usage: ";
		cin >> usage1;
		cout << "Algricultural Irrigation Usage: ";
		cin >> usage2;
		// pushToHistory(p->info.No, currentUsage);
		read++;
	}
}
void MROverview_estate(int username, char* district, char* street) {
	MRdef mywork;
	mywork = getMRDetail(username);
	char estate[32];
	do {
		unreadRegionInfoNode* estateListHead =
			getUnreadRegions_estates(district, street);
		system("cls");
		cout << "BILL INPUT - ESTATE OVERVIEW" << endl;
		cout << "==============================================" << endl;
		cout << endl;
		cout << "Unread estates in " << street << ", " << district << " district"
			<< endl;
		cout << "-----------------------------------------------" << endl;
		cout << "Estate" << '\t' << "Unread" << endl;
		cout << "-----------------------------------------------" << endl;
		unreadRegionInfoNode* p = estateListHead->next;
		while (1) {
			if (p == NULL) {
				break;
			}
			cout << left << setw(15) << p->region.estate << '\t' << right << p->unread
				<< endl;
			p = p->next;
		}
		cout << "----------------------------------------------" << endl;
		cout << "You wish to input: ";
		getString(estate);
		if (samestr(estate, (char*)"-1")) break;
		MRInput_Urban(district, street, estate);
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
		system("cls");
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
			cout << left << setw(25) << p->region.street << '\t' << right << p->unread
				<< endl;
			p = p->next;
		}
		cout << "----------------------------------------------" << endl;
		cout << "You wish to input: ";
		getString(street);
		if (samestr(street, (char*)"-1")) break;
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
		system("cls");
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
			cout << left << setw(15) << p->region.district << '\t' << right
				<< p->unread << endl;
			p = p->next;
		}
		cout << "----------------------------------------------" << endl;
		cout << "You wish to input: ";
		getString(district);
		if (samestr(district, (char*)"-1")) break;
		MROverview_street(username, district);
	} while (!samestr(district, (char*)"-1"));
}
void MRDash(int username) {
	userinfo me;
	MRdef mywork;
	mywork = getMRDetail(username);
	me = getUserInfo(username);
	int userread = getUnread();
	int totaluser_local = usercount[0];
	int opt;
	do {
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
		cout << "3. Show Current Rate Rules" << endl;
		cout << "4. Change Profile Information" << endl;
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
			system("cls");
			cout << "Thanks!" << endl;
			cout << endl;
			cout << "Logging out";
			dotDotDot(3);
			return;
		default:
			cout << "Invalid input, please try again" << endl;
		}
	} while (opt != 0);
	system("cls");
	cout << "Thanks!" << endl;
	cout << endl;
	cout << "Exiting";
	dotDotDot(3);
}
// Charger_Menu ===============================================

void makePayment(int username, double amount) {
	userinfo user = getUserInfo(username);
	userpay pay;
	pay.amount = amount;
	pay.payNo = genPayNo();
	pay.userNo = user.No;
	strcpy_s(pay.name, user.name);
	pay.address = user.address;
	pay.balance_before = user.balance;
	pay.payDate = getCurrentTime();
	user.balance = user.balance + amount;
	fstream userfile;
	userfile.open(FLOC_USERBASICINFO, ios::binary | ios::in | ios::out);
	userinfo temp;
	while (1) {
		userfile.read((char*)&temp, sizeof(userinfo));
		if (userfile.eof())
			break;
		if (temp.No == username) {
			int size = sizeof(userinfo);
			userfile.seekg(-size, ios::cur);
			userfile.write((char*)&user, sizeof(userinfo));
			break;
		}
	}
	userfile.close();
	fstream payfile;
	payfile.open(FLOC_PAYMENT, ios::binary | ios::out | ios::app);
	payfile.write((char*)&pay, sizeof(userpay));
	payfile.close();
}
void ReportFormGenerate() {
	fstream readfile;
	fstream reportform;
	readfile.open(FLOC_BILLDETAIL, ios::binary | ios::in);

	reportform << "Address" << '\t' << "Total Usage" << '\t' << "Unread Users"
		<< '\t' << "Total Arrears" << endl;
}
void showAllBillList() {
	fstream file;
	userbill bill;
	file.open(FLOC_BILLDETAIL, ios::binary | ios::in);
	while (file.read((char*)&bill, sizeof(userbill))) {
		cout << "Case No.: " << bill.caseNo << endl
			<< "User No.: " << bill.user_record.No << endl
			<< "User Name: " << bill.user_record.name << endl
			<< "Read: " << bill.read << endl
			<< "Current Usage: " << bill.current_usage << endl
			<< "Last Month Usage: " << bill.last_month_usage << endl
			<< "rate" << decodeRateNoforBill(bill.rateNo) << endl
			<< "Read Date: " << bill.read_date.y << "-" << bill.read_date.m << "-"
			<< bill.read_date.d << " " << bill.fee << endl
			<< "Address: " << bill.user_record.address.street << endl
			<< "------------------------------------------------------------------"
			<< endl;
	}
	file.close();
	system("pause");
}
void userPaymentMake() {
	system("cls");
	cout << "MAKE PAYMENT" << endl;
	cout << "==============================================" << endl;
	cout << endl;
	cout << "Input username" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Username: ";
	int username;
	cin >> username;
	userinfo user = getUserInfo(username);
	system("cls");
	cout << "MAKE PAYMENT" << endl;
	cout << "==============================================" << endl;
	cout << "You are now operating on " << user.name << "'s billing information: " << endl;
	cout << "Name: " << user.name << endl;
	cout << "Type: " << rtnType(user.type) << "(" << user.type << ")" << endl;
	cout << "Username: " << user.No << endl;
	cout << "ID: " << user.id << endl;
	cout << "Balance" << user.balance << endl;
	cout << "3. Address: " << user.address.unit << "-" << user.address.level << "-"
		<< user.address.room << " " << user.address.estate << ", "
		<< user.address.street << ", " << user.address.district << ", "
		<< user.address.city << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Input the amount of money" << endl;
	cout << "Pay: ";
	double amount;
	cin >> amount;
	makePayment(username, amount);
	
}
void showPaymentList() {
	system("cls");
	cout << "PAYMENT LIST" << endl;
	cout << "==============================================" << endl;
	fstream file;
	file.open(FLOC_PAYMENT, ios::binary | ios::in);
	userpay payment;
	file.seekg(sizeof(userpay), ios::beg);
	while (1) {
		file.read((char*)&payment, sizeof(userpay));
		if (file.eof())
			break;
		cout << setfill('0') << setw(2) << payment.payDate.h << ":" << setw(2) << payment.payDate.min << ":"
			<< setw(2) << payment.payDate.sec << " " << setw(2) << payment.payDate.d << "/" << setw(2) << payment.payDate.m
			<< "/" << setw(2) << payment.payDate.y << '\t' << setfill(' ') << payment.name << " " << payment.userNo
			<< setw(5) << payment.balance_before << '\t' << setw(5) << payment.amount << '\t'
			<< payment.address.unit << "-" << payment.address.level << "-" << payment.address.room << " "
			<< payment.address.estate << ", " << payment.address.street << ", " << payment.address.district << ", "
			<< payment.address.city << endl;
	}
	file.close();
	system("pause");
}
void chargerDash(int username) {
	userinfo me;
	me = getUserInfo(username);
	int opt;
	do {
		system("cls");
		cout << "DASHBOARD" << endl;
		cout << "==============================================" << endl;
		cout << me.name << ", greetings!" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Urban Users: " << usercount[6] << endl;
		cout << "Rural Users: " << usercount[7] << endl;
		cout << "Rural Users in poverty: " << usercount[8] << endl;
		cout << "Enterprise E1 Users: " << usercount[4] << endl;
		cout << "Enterprise E2 Users: " << usercount[5] << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Menu:" << endl;
		cout << "1. Make Payment" << endl;
		cout << "2. Show Bill History" << endl;
		cout << "3. Show Payment History" << endl;
		cout << "4. Report Form Generate" << endl;
		cout << "0. Logout" << endl;
		cin >> opt;
		switch (opt) {
		case 1:
			userPaymentMake();
			break;
		case 2:
			showPaymentList();
			break;
		case 3:
			showPaymentList();
			break;
		default:
			cout << "Invalid Input" << endl;
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
		switch (opt) {
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
			if (opt == 'y' || opt == 'Y') {
				userInfoImport(fileLocation);
				break;
			}
			else {
				cout << "cancelled";
				Sleep(1);
			}
		case 3:
			system("cls");
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
	system("cls");
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
	system("cls");
}
void generateUser() {
	userinfo newUser;
	newUser.No = genUserNo();

	system("cls");
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

	system("cls");
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

	system("cls");
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

	system("cls");
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

	system("cls");
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

	system("cls");
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

	system("cls");
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

	system("cls");
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

	system("cls");
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

	system("cls");
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
		strcpy_s(newUser.password, "set default password error");
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

	system("cls");
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
		newUserBill.read_date = getCurrentTime();
		newUserBill.user_record = newUser;
		if (newUser.type == 5)
			newUserBill.rateNo = genRateNoforBill(newUser.type, 2, 1);
		else if (newUser.type <= 3)
			newUserBill.rateNo = 0;
		else
			newUserBill.rateNo = genRateNoforBill(newUser.type, 1, 1);

		newUserBill.rateNo = genRateNoforBill(newUser.type, 1, 1);
		newUserBill.last_month_usage = 0;
		newUserBill.current_usage = 0;
		newUserBill.fee = 0;
		newUserBill.read = true;

		fstream userBillInfo;
		userBillInfo.open(FLOC_BILLDETAIL, ios::binary | ios::app | ios::out);
		userBillInfo.write((char*)&newUserBill, sizeof(userbill));
		userBillInfo.close();

		if (newUser.type == 2) {
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
		Sleep(1);
	}
	else {
		cout << endl;
		cout << "Cancelled" << endl;
		Sleep(1);
	}
}
void adminEditUser_Detail(int username) {
	int opt;
	do {
		userinfo user;
		user = getUserInfo(username);
		system("cls");
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
			system("cls");
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
				strcpy_s(user.name, newname);
				changeUserInfo(user);
				cout << "Successful" << endl;
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 2) {
			system("cls");
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

			system("cls");
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
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 3) {
			system("cls");
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

			system("cls");
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
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 4) {
			system("cls");
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
			system("cls");
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
				strcpy_s(user.id, newID);
				changeUserInfo(user);
				cout << "Successful" << endl;
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 5) {
			system("cls");
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

			system("cls");
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

			system("cls");
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

			system("cls");
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

			system("cls");
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

			system("cls");
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

			system("cls");
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
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}

		}
		else if (opt == 6) {
			system("cls");
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
			system("cls");
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
				strcpy_s(user.password, newPassword);
				changeUserInfo(user);
				cout << "Successful" << endl;
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 7) {
			system("cls");
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
				Sleep(1);
				return;
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 0) {
			return;
		}
	} while (opt != 0);
}
void adminEditUsers() {
	int userno;
	do {
		system("cls");
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
		}
		else if (validUser(userno)) {
			adminEditUser_Detail(userno);
		}
		else {
			cout << "Invalid number, please try again";
			Sleep(1);
		}
	} while (userno != -1);
}
void adminListUsers() {
	system("cls");
	cout << "USER MANAGEMENT - USER LIST" << endl;
	cout << "================================================================================================================================================================================================="<< endl;
	cout << "Number                Name	                Type                      ID                                         Address                                                             Read"<< endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<< endl;
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
	system("cls");
}
void userManage() {
	int opt;
	do {
		system("cls");
		getTotalUser();
		cout << "USER MANAGEMENT" << endl;
		cout << "=================================================================="
			"===="
			<< endl;
		cout << "Total users: " << usercount[0] << endl;
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
		system("cls");
		cout << "DASHBOARD" << endl;
		cout << "==============================================" << endl;
		cout << me.name << ", greetings!" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Total users: " << usercount[0] << endl;
		cout << "Administrators: " << usercount[1] << endl;
		cout << "Meter Readers: " << usercount[2] << endl;
		cout << "Chargers: " << usercount[3] << endl;
		cout << "Enterprise E1 Users: " << usercount[4] << endl;
		cout << "Enterprise E2 Users: " << usercount[5] << endl;
		cout << "Urban Users: " << usercount[6] << endl;
		cout << "Rural Users: " << usercount[7] << endl;
		cout << "Poverty Rural Users: " << usercount[8] << endl;
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
			system("cls");
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
void showBillDetail(int caseNo) {
	userbill bill = getBill(caseNo);
	system("cls");
	cout << "BILL DETAIL" << endl;
	cout << "========================================" << endl;
	cout << "Detail of this bill" << endl;
	cout << endl;
	cout << "-----------------General----------------" << endl;
	cout << "Case No.: " << bill.caseNo << endl;
	cout << "User No.: " << bill.user_record.No << endl;
	cout << "User Name: " << bill.user_record.name << endl;
	cout << "Address: " << bill.user_record.address.unit << "-"
		<< bill.user_record.address.level << "-" << bill.user_record.address.room
		<< " " << bill.user_record.address.estate << ", "
		<< bill.user_record.address.street << ", "
		<< bill.user_record.address.district << ", "
		<< bill.user_record.address.city << endl;
	cout << endl;
	cout << "--------------Bill Detail---------------" << endl;
	if (bill.read) {
		cout << "Month Before: " << bill.last_month_usage << " kWh" << endl;
		cout << "Then: " << bill.current_usage << " kWh" << endl;
		cout << "Fee: " << bill.fee << " CNY" << endl;
		cout << "Rate: " << decodeRateNoforBill(bill.rateNo) << "(" << bill.rateNo
			<< ")" << endl;
		cout << "Read Date: " << bill.read_date.h << ":" << bill.read_date.m << ":"
			<< bill.read_date.sec << " " << bill.read_date.d << "/"
			<< bill.read_date.m << "/" << bill.read_date.y << endl;
	}
	else {
		cout << "Not read" << endl;
	}
	char ch;
	cin >> ch;
}
void userShowHistory(int username) {
	userBillHistoryNode* head = getUserBillHistory(username);
	int caseNo;
	do {
		userBillHistoryNode* p = head;
		system("cls");
		cout << "BILL HISTORY" << endl;
		cout << "========================================================" << endl;
		cout << "Date     Case No.  Before Then  Read   Fee   Rate No." << endl;
		cout << "--------------------------------------------------------" << endl;
		while (1) {
			p = p->next;
			if (p == NULL) break;
			cout << setfill('0') << setw(2) << p->bill.read_date.m << "/" << setw(4)
				<< p->bill.read_date.y << '\t' << setfill(' ') << setw(5)
				<< p->bill.caseNo << '\t' << right << setfill(' ') << setw(5)
				<< p->bill.last_month_usage << '\t' << setw(5)
				<< p->bill.current_usage << '\t';
			if (p->bill.read == true)
				cout << "Read" << '\t';
			else
				cout << "Not " << '\t';
			cout << right << setw(5) << p->bill.fee << '\t' << setw(5)
				<< p->bill.rateNo << endl;
		}
		cout << right << "---------------------------------------------------------"
			<< endl;
		cout << "Input -1 to exit" << endl;
		cout << "Input the the number of case of which you want to see in detail"
			<< endl;
		cout << "CaseNo. : ";
		cin >> caseNo;
		showBillDetail(caseNo);
	} while (caseNo != -1);
}
void userEditBasicInfo(int username) {
	int opt;
	do {
		userinfo me;
		me = getUserInfo(username);
		system("cls");
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
			system("cls");
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
				strcpy_s(me.name, newname);
				changeUserInfo(me);
				cout << "Successful" << endl;
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 2) {
			system("cls");
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
			system("cls");
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
				strcpy_s(me.id, newID);
				changeUserInfo(me);
				cout << "Successful" << endl;
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 3) {
			system("cls");
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

			system("cls");
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

			system("cls");
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

			system("cls");
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

			system("cls");
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

			system("cls");
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

			system("cls");
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
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}

		}
		else if (opt == 4) {
			system("cls");
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
			system("cls");
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
				strcpy_s(me.password, newPassword);
				changeUserInfo(me);
				cout << "Successful" << endl;
				Sleep(1);
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 5) {
			system("cls");
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
				Sleep(1);
				return;
			}
			else {
				cout << endl;
				cout << "Cancelled" << endl;
				Sleep(1);
			}
		}
		else if (opt == 0) {
			return;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	} while (opt != 0);
}
void userDash(int username) {
	userinfo me;
	me = getUserInfo(username);
	int opt;
	do {
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
		cout << "Power Status: ";
		if (me.powercut == false) {
			cout << "Using" << endl;
		}
		else {
			cout << "Cut" << endl;
		}
		cout << "Current Usage: ";
		if (me.read_now == true) {
			cout << me.last_month_usage << endl;
		}
		else {
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
			userShowHistory(me.No);
			break;
		case 0:
			system("cls");
			cout << "Thanks!" << endl;
			cout << endl;
			cout << "Logging out";
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
		system("cls");
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
			}
			else {
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
		else {
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
void checkAndGenerate() {
	fstream userinfofile;
	userinfofile.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	if (!userinfofile) {
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
		cout << "******************************************************************"
			"*****"
			<< endl;
		cout << "* You are the administrator, use the following information to "
			"sign in *"
			<< endl;
		cout << "* Username: 0                                                     "
			"    *"
			<< endl;
		cout << "* Password: root                                                  "
			"    *"
			<< endl;
		cout << "******************************************************************"
			"*****"
			<< endl;
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
	else {
		cout << "welcome to electricity billing system" << endl;
		Sleep(0500);
	}
}
// Main ============================================================
int main() {
	// userDash(0);
	checkAndGenerate();
	getTotalUser();
	defineUnread();
	login();
	// showAllBillList();
	// MRListUsers();
	// showBillDetail(1);
	// userShowHistory(1);
	// showRate();
	// while (1) {
	//  int lastusage;
	//  int currentusage;
	//  int rateno;
	//  double fee;
	//  cin >> lastusage >> currentusage;
	//  chargeFeedback(1, lastusage, currentusage, rateno, fee);
	//  cout << "rate no. " << rateno << endl;
	//  cout << decodeRateNoforBill(rateno) << endl;
	//}
}