#include "headerfiles.h"
using namespace std;

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