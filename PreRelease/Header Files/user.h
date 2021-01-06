#pragma once
#include "headerfiles.h";
using namespace std;

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