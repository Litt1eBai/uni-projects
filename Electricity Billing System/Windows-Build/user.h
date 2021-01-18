#pragma once
#include "headerfiles.h"
using namespace std;

void changePasswordTo(int username, char* passput) {
	userinfo user;
	user = getUserInfo(username);
	strcpy_s(user.password, passput);
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
// Bill
userbill getBill(int caseNo) {
	fstream file;
	userbill bill;
	file.open(FLOC_BILLDETAIL, ios::binary | ios::in);
	while (1) {
		file.read((char*)&bill, sizeof(userbill));
		if (file.eof()) break;
		if (bill.caseNo == caseNo) break;
	}
	file.close();
	return bill;
}
// Meter Reader-specific ====================================================
void storeMRInfo(MRdef mr) {
	MRdef mrtmp;
	fstream temp;
	temp.open(FLOC_MRINFO, ios::binary | ios::app | ios::out);
	temp.write((char*)&mr, sizeof(MRdef));
	temp.close();
}
// Generate Bill
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
int generateRateGen() {
	int current = getRateEdition();
	return current + 1;
}
int genRateNoforBill(int type, int row, int col) {
	int rateNo = 0;
	rateNo = getRateEdition();
	rateNo = rateNo * 10 + type;
	rateNo = rateNo * 10 + row;
	rateNo = rateNo * 10 + col;
	return rateNo;
}
rateRecord getRate(int gen) {
	fstream file;
	rateRecord rate;
	file.open(FLOC_RATE, ios::binary | ios::in);
	while (1) {
		file.read((char*)&rate, sizeof(rateRecord));
		if (file.eof()) break;
		if (rate.rateNo == gen)
			;
		break;
	}
	return rate;
}
double decodeRateNoforBill(int rateNo) {
	int col = rateNo % 10;
	rateNo = rateNo / 10;
	int row = rateNo % 10;
	rateNo = rateNo / 10;
	int type = rateNo % 10;
	rateNo = rateNo / 10;
	int rateGen = rateNo % 10;
	rateRecord rate = getRate(rateGen);
	if (type == 6)
		return rate.urban[row][col];
	else if (type == 4)
		return rate.ent[1][col];
	else if (type == 5)
		return rate.ent[2][col];
	else if (type == 7 || type == 8)
		return rate.rural[row][col];
}
// Input
unreadRegionInfoNode* getUnreadRegions_districts() {
	fstream file;
	userinfo user;
	file.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	unreadRegionInfoNode* head = new unreadRegionInfoNode;
	head->next = NULL;
	while (1) {
		file.read((char*)&user, sizeof(userinfo));
		if (file.eof()) break;
		if (user.type > 3 && !user.read_now) {
			unreadRegionInfoNode* p = new unreadRegionInfoNode;
			p->region = user.address;
			unreadRegionInfoNode* find = head->next;
			int flag = 1;
			while (find != NULL) {
				if (samestr(find->region.district, user.address.district)) {
					find->unread++;
					flag = 0;
				}
				find = find->next;
			}
			if (flag) {
				p->unread = 1;
				p->next = head->next;
				head->next = p;
			}
		}
	}
	file.close();
	return head;
}
unreadRegionInfoNode* getUnreadRegions_streets(char* district) {
	fstream file;
	userinfo user;
	file.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	unreadRegionInfoNode* head = new unreadRegionInfoNode;
	head->next = NULL;
	while (1) {
		file.read((char*)&user, sizeof(userinfo));
		if (file.eof()) break;
		if (user.type > 3 && !user.read_now &&
			samestr(user.address.district, district)) {
			unreadRegionInfoNode* p = new unreadRegionInfoNode;
			p->region = user.address;
			unreadRegionInfoNode* find = head->next;
			int flag = 1;
			while (find != NULL) {
				if (samestr(find->region.district, user.address.district) &&
					samestr(find->region.street, user.address.street)) {
					find->unread++;
					flag = 0;
				}
				find = find->next;
			}
			if (flag) {
				p->unread = 1;
				p->next = head->next;
				head->next = p;
			}
		}
	}
	file.close();
	return head;
}
unreadRegionInfoNode* getUnreadRegions_estates(char* district, char* street) {
	fstream file;
	userinfo user;
	file.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	unreadRegionInfoNode* head = new unreadRegionInfoNode;
	head->next = NULL;
	while (1) {
		file.read((char*)&user, sizeof(userinfo));
		if (file.eof()) break;
		if (user.type > 3 && !user.read_now &&
			samestr(user.address.district, district) &&
			samestr(user.address.street, street)) {
			unreadRegionInfoNode* p = new unreadRegionInfoNode;
			p->region = user.address;
			unreadRegionInfoNode* find = head->next;
			int flag = 1;
			while (find != NULL) {
				if (samestr(find->region.district, user.address.district) &&
					samestr(find->region.street, user.address.street) &&
					samestr(find->region.estate, user.address.estate)) {
					find->unread++;
					flag = 0;
				}
				find = find->next;
			}
			if (flag) {
				p->unread = 1;
				p->next = head->next;
				head->next = p;
			}
		}
	}
	file.close();
	return head;
}
estateUserInfoNode* getEstateUserUnread(char* district, char* street, char* estate, int& unread) {
	fstream fileRead;
	estateUserInfoNode* head = new estateUserInfoNode;
	head->next = NULL;
	fileRead.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	unread = 0;
	while (1) {
		estateUserInfoNode* p = new estateUserInfoNode;
		fileRead.read((char*)&(p->info), sizeof(userinfo));
		if (fileRead.eof()) {
			break;
		}
		if (p->info.type > 3 && !p->info.read_now &&
			samestr(p->info.address.district, district) &&
			samestr(p->info.address.street, street) &&
			samestr(p->info.address.estate, estate)) {
			p->next = head->next;
			head->next = p;
			unread++;
		}
	}
	return head;
}
unreadRegionInfoNode* getReportRegions_districts() {
	fstream file;
	userinfo user;
	file.open(FLOC_USERBASICINFO, ios::binary | ios::in);
	unreadRegionInfoNode* head = new unreadRegionInfoNode;
	head->next = NULL;
	while (1) {
		file.read((char*)&user, sizeof(userinfo));
		if (file.eof()) break;
		if (user.type > 3) {
			unreadRegionInfoNode* p = new unreadRegionInfoNode;
			p->region = user.address;
			unreadRegionInfoNode* find = head->next;
			int flag = 1;
			while (find != NULL) {
				if (samestr(find->region.district, user.address.district)) {
					find->unread++;
					flag = 0;
				}
				find = find->next;
			}
			if (flag) {
				p->unread = 1;
				p->next = head->next;
				head->next = p;
			}
		}
	}
	file.close();
	return head;
}
// Store
void chargeFeedback(int username, int lastUsage, int currentUsage, int& rateNo, double& fee) {
	rateRecord rate = getCurrentRate();
	userinfo user = getUserInfo(username);
	int row = 0;
	int col = 0;
	user.voltage = user.voltage / 1000;
	//cout << "voltage: " << user.voltage << endl;
	//cout << "Current Use: " << currentUsage << endl;
	//cout << "Used : " << currentUsage - lastUsage << endl;
	if (user.type == 6) {
		for (row = 0; rate.urban[row][0] != -1; row++) {
			if (currentUsage >= rate.urban[row][0] &&
				currentUsage < rate.urban[row + 1][0]) {
				row++;
				break;
			}
			else if (currentUsage > rate.urban[row][0] &&
				rate.urban[row + 1][0] == -1) {
				break;
			}
		}
		for (col = 0; rate.urban[0][col] != -1; col++) {
			if (user.voltage >= rate.urban[0][col] &&
				user.voltage < rate.urban[0][col + 1]) {
				col++;
				break;
			}
			else if (rate.urban[0][col + 1] == -1 &&
				user.voltage > rate.urban[0][col]) {
				break;
			}
		}
		fee = (currentUsage - lastUsage) * rate.urban[row][col];
	}
	else if (user.type == 7 && user.type == 8) {
		for (col = 0; rate.rural[0][col] != -1; col++) {
			if (user.voltage >= rate.rural[0][col] &&
				currentUsage < rate.rural[0][col + 1]) {
				col++;
				break;
			}
			else if (rate.rural[0][col + 1] == -1 &&
				currentUsage >= rate.rural[0][col]) {
				break;
			}
		}
		fee = (currentUsage - lastUsage) * rate.rural[1][col];
	}
	else if (user.type == 4) {
		for (col = 0; rate.ent[0][col] != -1; col++) {
			if (user.voltage >= rate.ent[0][col] &&
				user.voltage < rate.ent[0][col + 1]) {
				col++;
				break;
			}
			else if (rate.ent[0][col + 1] == -1 &&
				user.voltage >= rate.ent[0][col]) {
				break;
			}
		}
		fee = (currentUsage - lastUsage) * rate.ent[1][col];
	}
	else if (user.type == 5) {
		for (col = 0; rate.ent[0][col] != -1; col++) {
			if (currentUsage >= rate.ent[0][col] &&
				currentUsage < rate.ent[1][col + 1]) {
				col++;
				break;
			}
			else if (rate.ent[0][col + 1] == -1 &&
				currentUsage >= rate.ent[0][col]) {
				break;
			}
			fee =
				(currentUsage - lastUsage) * rate.ent[2][col] + 36 * rate.ent[0][col];
		}
	}
	//cout << endl;
	//cout << "row: " << row << " col: " << col << endl;
	//cout << "rate: " << rate.urban[row][col] << endl;
	//cout << "fee: " << fee << endl;
	rateNo = genRateNoforBill(user.type, row, col);
}
void chargeFeedback_RuralIrrigation(int username, int lastUsage, int currentUsage, int& rateNo, double& fee) {
	rateRecord rate = getCurrentRate();
	userinfo user = getUserInfo(username);
	int row = 0;
	int col = 0;
	for (col = 0; rate.rural[0][col] != -1; col++) {
		if (user.voltage >= rate.rural[0][col] &&
			currentUsage < rate.rural[0][col + 1]) {
			col++;
			break;
		}
		else if (rate.rural[0][col + 1] == -1 &&
			currentUsage >= rate.rural[0][col]) {
			break;
		}
	}
	fee = (currentUsage - lastUsage) * rate.rural[2][col];
}
void updateUserBillingStatus(int username, int currentUsage, double fee) {
	fstream file;
	file.open(FLOC_USERBASICINFO, ios::binary | ios::in | ios::out);
	while (1) {
		userinfo currentUser;
		file.read((char*)&currentUser, sizeof(userinfo));
		if (file.eof()) {
			file.close();
			return;
		}
		if (currentUser.No == username) {
			currentUser.last_month_usage = currentUsage;
			currentUser.last_read = getCurrentTime();
			currentUser.balance = currentUser.balance - fee;
			currentUser.read_now = true;
			int size = sizeof(userinfo);
			file.seekg(-size, ios::cur);
			int now = file.tellg();
			file.write((char*)&currentUser, sizeof(userinfo));
			file.seekg(now, ios::beg);
			file.close();
			return;
		}
	}
}
void pushReadToHistory(int username, int lastUsage, int currentUsage) {
	userinfo user = getUserInfo(username);
	userbill bill;
	bill.caseNo = genCaseNo();
	bill.user_record = user;
	bill.last_month_usage = user.last_month_usage;
	bill.current_usage = currentUsage;
	bill.read_date = getCurrentTime();
	bill.read = true;
	chargeFeedback(username, lastUsage, currentUsage, bill.rateNo, bill.fee);
	fstream file;
	file.open(FLOC_BILLDETAIL, ios::binary | ios::out | ios::app);
	file.write((char*)&bill, sizeof(userbill));
	file.close();
	updateUserBillingStatus(username, currentUsage, bill.fee);
}
void pushReadToHistory_RuralIrrigation(int username, int lastUsage, int currentUsage, int rateNo, double fee) {
	userinfo user = getUserInfo(username);
	userbill bill;
	bill.caseNo = genCaseNo();
	bill.user_record = user;
	bill.last_month_usage = user.last_month_usage;
	bill.read_date = getCurrentTime();
	bill.read = true;
	chargeFeedback_RuralIrrigation(username, lastUsage, currentUsage, bill.rateNo,
		fee);
	bill.rateNo = rateNo;
	bill.fee = fee;
	fstream file;
	file.open(FLOC_BILLDETAIL, ios::binary | ios::out | ios::app);
	file.write((char*)&bill, sizeof(userbill));
	file.close();
}
// User-Spesific
userBillHistoryNode* getUserBillHistory(int username) {
	fstream file;
	userbill bill;
	userBillHistoryNode* head = new userBillHistoryNode;
	head->next = NULL;
	file.open(FLOC_BILLDETAIL, ios::binary | ios::in);
	while (1) {
		file.read((char*)&bill, sizeof(userbill));
		if (file.eof()) break;
		if (bill.user_record.No == username) {
			userBillHistoryNode* p = new userBillHistoryNode;
			p->bill = bill;
			p->next = head->next;
			head->next = p;
		}
	}
	file.close();
	return head;
}
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
// Charger Sheets
// 
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