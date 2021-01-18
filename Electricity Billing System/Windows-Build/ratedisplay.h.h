#pragma once
#include "headerfiles.h"
using namespace std;

// Urban
void adminEditRate_Urban_editDetail(int row, int col, rateRecord& current) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	double input;
	do {
		system("cls");
		if (row == 0) {
			cout << "RATE - URBAN" << endl;
			cout
				<< "================================================================="
				<< endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "You are changing data of row 0, col " << row << endl;
			cout
				<< "-----------------------------------------------------------------"
				<< endl;
			cout << endl;
#pragma region display2
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++)  // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;

			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 15);
			if (current.urban[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				if (i == col)
					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				else
					SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.urban[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				if (i == row) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;
			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[N - 1][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else if (row == 5) {
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "==========================================================="
				<< endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------"
				<< endl;
			cout << endl;
			if (col == 0) {
#pragma region display
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++)  // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;

				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.urban[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;
				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.urban[N - 1][0];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
			else {
#pragma region diaplay3
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++)  // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;

				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.urban[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;
				}

				// Last line

				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.urban[N - 1][0] << " kWh";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				for (int j = 1; j < N; j++) {
					if (j == col)
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					else
						SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.urban[N - 1][0];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
		}
		else {
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "==========================================================="
				<< endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------"
				<< endl;
			cout << endl;
			if (col == 0) {
#pragma region display
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++)  // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;

				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.urban[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					if (i == row)
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					else
						SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;
				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[N - 1][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
			else {
#pragma region diaplay3
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++)  // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;

				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.urban[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.urban[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					if (i == row) {
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(4) << "row" << setw(2) << i << " ";  // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.urban[i][0] << " kWh";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						for (int j = 1; j < N; j++) {
							if (j == col)
								SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
							else
								SetConsoleTextAttribute(hConsole, 15);
							if (current.urban[i][j] == -1)
								wcout << setw(9) << " ";
							else
								wcout << setw(9) << current.urban[i][j];
							SetConsoleTextAttribute(hConsole, 8);
							wcout << L"│";
						}
					}
					else {
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(4) << "row" << setw(2) << i << " ";  // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.urban[i][0] << " kWh";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						for (int j = 1; j < N; j++) {
							SetConsoleTextAttribute(hConsole, 15);
							if (current.urban[i][j] == -1)
								wcout << setw(9) << " ";
							else
								wcout << setw(9) << current.urban[i][j];
							SetConsoleTextAttribute(hConsole, 8);
							wcout << L"│";
						}
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;
				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[N - 1][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
		}
		cout << "Input -2 to exit, input -1 to remove data" << endl;

		if (row != 0 && col != 0) {
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "You've selected row " << row << " col " << col
				<< ", the detail is as follows: " << endl;
			cout << "Rate Type: "
				<< "Urban E-" << row << " Tier " << col << endl;
			cout << "Voltage Interval: " << current.urban[0][col - 1] << " - "
				<< current.urban[0][col] << endl;
			cout << "Energy Interval: " << current.urban[row - 1][0] << " - "
				<< current.urban[row][0] << endl;
			cout << "Rate: " << current.urban[row][col] << endl;
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "Change rate to: ";
			cin >> input;
			if (input != -2) {
				current.urban[row][col] = input;
			}
			else {
				return;
			}
		}
		else if (row == 0) {
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "You've selected row " << row << " col " << col
				<< ", the detail is as follows: " << endl;
			cout << "Voltage Interval: " << current.urban[0][col - 1] << " - "
				<< current.urban[0][col] << endl;
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "Change the interval to: " << current.urban[0][col - 1] << " - ";
			cin >> input;
			if (input != -2) {
				current.urban[row][col] = input;
			}
			else {
				return;
			}
		}
		else {
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "You've selected row " << row << " col " << col
				<< ", the detail is as follows: " << endl;
			cout << "Energy Interval: " << current.urban[row - 1][0] << " - "
				<< current.urban[row][0] << endl;
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "Change the interval to: " << current.urban[row - 1][0] << " - ";
			cin >> input;
			if (input != -2) {
				current.urban[row][col] = input;
			}
			else {
				return;
			}
		}
	} while (input != -2);
}
void adminEditRate_Urban_colSelect(int row, rateRecord& current) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int col;
	do {
		system("cls");
		if (row == 0) {
			cout << "RATE - URBAN" << endl;
			cout
				<< "================================================================="
				<< endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "You are changing data of row 0" << endl;
			cout
				<< "-----------------------------------------------------------------"
				<< endl;
			cout << endl;
#pragma region display2
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++)  // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;

			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
			if (current.urban[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.urban[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.urban[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				if (i == row) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;
			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[N - 1][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else if (row == 5) {
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "==========================================================="
				<< endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------"
				<< endl;
			cout << endl;
#pragma region diaplay3
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++)  // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;

			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.urban[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << i << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[i][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.urban[i][0] << " kWh";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][j] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.urban[i][j];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;
			}

			// Last line

			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[N - 1][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else {
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "==========================================================="
				<< endl;
			cout << "Here is the current rate for urban users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------"
				<< endl;
			cout << endl;
#pragma region diaplay3
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++)  // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;

			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				SetConsoleTextAttribute(hConsole, 6);
				if (current.urban[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.urban[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				if (i == row) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.urban[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.urban[i][0] << " kWh";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.urban[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.urban[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;
			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[N - 1][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.urban[N - 1][0] << " kWh";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		cout << endl;
		cout << "---------------------------------------------------------------"
			<< endl;
		cout << "col: ";
		cin >> col;
		if (row == 0 && col == 0) {
			cout << "You cannot change the data of row 0, col 0" << endl;
			Sleep(1000);
		}
		else if (col != -1) {
			adminEditRate_Urban_editDetail(row, col, current);
		}
		else {
			return;
		}
	} while (col != -1);
}
void adminEditRate_Urban_rowSelect(rateRecord& current) {
	int row;
	do {
		system("cls");

		cout << "RATE - URBAN" << endl;
		cout << "==========================================================="
			<< endl;
		cout << "Here is the current rate for urban users" << endl;
		cout << "Select the row you want to change" << endl;
		cout << "-----------------------------------------------------------"
			<< endl;
		cout << endl;
#pragma region display1
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		_setmode(_fileno(stdout), _O_U16TEXT);

		wcout << setw(10) << " ";
		for (int i = 0; i < N; i++)  // col
		{
			SetConsoleTextAttribute(hConsole, 9);
			wcout << "col " << setw(6) << left << i;
		}
		wcout << endl;

		// Upper Line
		SetConsoleTextAttribute(hConsole, 8);
		wcout << setw(7) << right << " ";
		wcout << L"┌─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
		wcout << L"┬─────────┐" << endl;

		// 0,0
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[0][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[0][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		// Line 1
		for (int i = 1; i < N; i++) {
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[0][i] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(6) << current.urban[0][i] << " KV";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}
		wcout << endl;

		// Middle Line
		SetConsoleTextAttribute(hConsole, 6);
		wcout << setw(7) << " ";  // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

		// Content
		for (int i = 1; i < N - 1; i++) {
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << i << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[i][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[i][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[i][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[i][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;
		}
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		for (int j = 1; j < N; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[N - 1][0] << "kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(7) << " ";  // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"└─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
		wcout << L"┴─────────┘" << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		cout << endl;
		cout << "Input -1 to go back" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "Change row: ";
		cin >> row;

		//				system("cls");
		//				if (row == 0)
		//				{
		//					cout << "RATE - URBAN" << endl;
		//					cout <<
		//"=================================================================" <<
		//endl; 					cout << "Here is the current rate for urban users" << endl; 					cout <<
		//"You are changing data of row 0" << endl; 					cout <<
		//"-----------------------------------------------------------------" <<
		//endl; 					cout << endl; #pragma region display2 					_setmode(_fileno(stdout),
		//_O_U16TEXT); 					wcout << setw(3) << " "; 					for (int i = 0; i < N; i++)
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//3); 						wcout << "col " << setw(6) << left << i;
		//					}
		//					wcout << endl;
		//
		//
		//					// Upper Line
		//					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << L"┌─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┬─────────";
		//					wcout << L"┬─────────┐" << endl;
		//					wcout << L"│";
		//					SetConsoleTextAttribute(hConsole, 6);
		//
		//
		//					// 0,0
		//					SetConsoleTextAttribute(hConsole, BACKGROUND_RED |
		//7); 					if (current.urban[0][0] == -1) 						wcout << setw(9) << " "; 					else 						wcout <<
		//setw(9) << current.urban[0][0]; 					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << L"│";
		//
		//					// Line 1
		//					for (int i = 1; i < N; i++)
		//					{
		//						SetConsoleTextAttribute(hConsole, BACKGROUND_RED |
		//7); 						if (current.urban[0][i] == -1) 							wcout << setw(9) << right << " "; 						else
		//							wcout << setw(6) << right << current.urban[0][i] << "
		//KV"; 						SetConsoleTextAttribute(hConsole, 8); 						wcout << L"│";
		//					}
		//					wcout << endl;
		//
		//					// Middle Line
		//					wcout << L"├─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┼─────────";
		//					wcout << L"┼─────────┤" << endl;
		//
		//					// Content
		//					for (int i = 1; i < N - 1; i++)
		//					{
		//						wcout << L"│";
		//						SetConsoleTextAttribute(hConsole,
		//6); 						if (current.urban[i][0] == -1) 							wcout << setw(9) << " "; 						else 							wcout <<
		//setw(5) << current.urban[i][0] << " kWh";
		//						SetConsoleTextAttribute(hConsole,
		//8); 						wcout << L"│"; 						for (int j = 1; j < N; j++)
		//						{
		//							SetConsoleTextAttribute(hConsole,
		//15); 							if (current.urban[i][j] == -1) 								wcout << setw(9) << " "; 							else 								wcout <<
		//setw(9) << current.urban[i][j]; 							SetConsoleTextAttribute(hConsole, 8);
		//							wcout << L"│";
		//						}
		//
		//						wcout << endl;
		//						wcout << L"├─────────";
		//						for (int i = 1; i < N - 1; i++)
		//							wcout << L"┼─────────";
		//						wcout << L"┼─────────┤" << endl;
		//
		//					}
		//
		//					wcout << L"│";
		//					SetConsoleTextAttribute(hConsole, 6);
		//					if (current.urban[N - 1][0] == -1)
		//						wcout << setw(9) << " ";
		//					else
		//						wcout << setw(9) << current.urban[N -
		//1][0]; 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//
		//
		//					for (int j = 1; j < N; j++)
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//15); 						if (current.urban[N - 1][0] == -1) 							wcout << setw(9) << " "; 						else
		//							wcout << setw(9) << current.urban[N -
		//1][0]; 						SetConsoleTextAttribute(hConsole, 8); 						wcout << L"│";
		//					}
		//
		//
		//					wcout << endl;
		//					wcout << L"└─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┴─────────";
		//					wcout << L"┴─────────┘" << endl;
		//					_setmode(_fileno(stdout), _O_TEXT);
		//					SetConsoleTextAttribute(hConsole, 15);
		//#pragma endregion
		//				}
		//
		//				else
		//				{
		//					system("cls");
		//
		//					cout << "RATE - URBAN" << endl;
		//					cout <<
		//"===========================================================" << endl;
		//					cout << "Here is the current rate for urban users" <<
		//endl; 					cout << "Change data on row " << row << endl; 					cout <<
		//"-----------------------------------------------------------" << endl;
		//					cout << endl;
		//#pragma region diaplay3
		//					_setmode(_fileno(stdout), _O_U16TEXT);
		//					wcout << setw(10) << " ";
		//					for (int i = 0; i < N; i++) // col
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//9); 						wcout << "col " << setw(6) << left << i;
		//					}
		//					wcout << endl;
		//
		//					// Upper Line
		//					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << setw(7) << right << " ";
		//					wcout << L"┌─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┬─────────";
		//					wcout << L"┬─────────┐" << endl;
		//
		//
		//
		//					// 0,0
		//					SetConsoleTextAttribute(hConsole, 9);
		//					wcout << setw(4) << "row" << setw(2) << 0 << " "; //
		//row 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//					SetConsoleTextAttribute(hConsole, 6);
		//					if (current.urban[0][0] == -1)
		//						wcout << setw(9) << " ";
		//					else
		//						wcout << setw(9) <<
		//current.urban[0][0]; 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//
		//					// Line 1
		//					for (int i = 1; i < N; i++)
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//6); 						if (current.urban[0][i] == -1) 							wcout << setw(9) << " "; 						else 							wcout <<
		//setw(6) << current.urban[0][i] << " KV"; 						SetConsoleTextAttribute(hConsole,
		//8); 						wcout << L"│";
		//					}
		//					wcout << endl;
		//
		//					// Middle Line
		//					SetConsoleTextAttribute(hConsole, 6);
		//					wcout << setw(7) << " "; // row
		//					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << L"├─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┼─────────";
		//					wcout << L"┼─────────┤" << endl;
		//
		//					// Content
		//					for (int i = 1; i < N - 1; i++)
		//					{
		//						if (i == row)
		//						{
		//							SetConsoleTextAttribute(hConsole,
		//9); 							wcout << setw(4) << "row" << setw(2) << i << " "; // row
		//							SetConsoleTextAttribute(hConsole,
		//8); 							wcout << L"│"; 							SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
		//							if (current.urban[i][0] ==
		//-1) 								wcout << setw(9) << " "; 							else 								wcout << setw(5) << current.urban[i][0]
		//<< " kWh"; 							SetConsoleTextAttribute(hConsole, 8); 							wcout << L"│"; 							for (int j
		//= 1; j < N; j++)
		//							{
		//								SetConsoleTextAttribute(hConsole, BACKGROUND_RED |
		//7); 								if (current.urban[i][j] == -1) 									wcout << setw(9) << " "; 								else 									wcout <<
		//setw(9) << current.urban[i][j]; 								SetConsoleTextAttribute(hConsole, 8);
		//								wcout << L"│";
		//							}
		//						}
		//						else
		//						{
		//							SetConsoleTextAttribute(hConsole,
		//9); 							wcout << setw(4) << "row" << setw(2) << i << " "; // row
		//							SetConsoleTextAttribute(hConsole,
		//8); 							wcout << L"│"; 							SetConsoleTextAttribute(hConsole, 15); 							if
		//(current.urban[i][0] == -1) 								wcout << setw(9) << " "; 							else 								wcout << setw(5)
		//<< current.urban[i][0] << " kWh"; 							SetConsoleTextAttribute(hConsole, 8);
		//							wcout << L"│";
		//							for (int j = 1; j < N;
		//j++)
		//							{
		//								SetConsoleTextAttribute(hConsole,
		//15); 								if (current.urban[i][j] == -1) 									wcout << setw(9) << " "; 								else 									wcout <<
		//setw(9) << current.urban[i][j]; 								SetConsoleTextAttribute(hConsole, 8);
		//								wcout << L"│";
		//							}
		//						}
		//						wcout << endl;
		//						SetConsoleTextAttribute(hConsole,
		//9); 						wcout << setw(7) << " "; // row 						SetConsoleTextAttribute(hConsole, 8);
		//						wcout << L"├─────────";
		//						for (int i = 1; i < N - 1; i++)
		//							wcout << L"┼─────────";
		//						wcout << L"┼─────────┤" << endl;
		//
		//					}
		//					SetConsoleTextAttribute(hConsole, 9);
		//					wcout << setw(4) << "row" << setw(2) << N - 1 << " "; //
		//row 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//					SetConsoleTextAttribute(hConsole, 6);
		//					if (current.urban[N - 1][0] == -1)
		//						wcout << setw(9) << " ";
		//					else
		//						wcout << setw(9) << current.urban[N -
		//1][0]; 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//
		//
		//					for (int j = 1; j < N; j++)
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//15); 						if (current.urban[N - 1][0] == -1) 							wcout << setw(9) << " "; 						else
		//							wcout << setw(9) << current.urban[N -
		//1][0]; 						SetConsoleTextAttribute(hConsole, 8); 						wcout << L"│";
		//					}
		//
		//					wcout << endl;
		//					SetConsoleTextAttribute(hConsole, 9);
		//					wcout << setw(7) << " "; // row
		//					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << L"└─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┴─────────";
		//					wcout << L"┴─────────┘" << endl;
		//					_setmode(_fileno(stdout), _O_TEXT);
		//					SetConsoleTextAttribute(hConsole, 15);
		//#pragma endregion
		//				}
		if (row != -1) {
			adminEditRate_Urban_colSelect(row, current);
		}
		else {
			return;
		}
	} while (row != -1);
}
void adminEditRate_Urban_Overview(rateRecord& current) {
	int opt;
	do {
		system("cls");
		cout << "RATE - URBAN" << endl;
		cout << "==========================================================="
			<< endl;
		cout << "Here is the current rate for urban users" << endl;
		cout << "-----------------------------------------------------------"
			<< endl;
		cout << endl;
#pragma region display0
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		_setmode(_fileno(stdout), _O_U16TEXT);

		// Upper Line
		SetConsoleTextAttribute(hConsole, 12);
		wcout << "Urban" << endl;
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"┌─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
		wcout << L"┬─────────┐" << endl;

		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);

		// 0,0
		if (current.urban[0][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[0][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		// Line 1
		for (int i = 1; i < N; i++) {
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[0][i] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(6) << current.urban[0][i] << " KV";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}
		wcout << endl;

		// Middle Line
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

		// Content
		for (int i = 1; i < N - 1; i++) {
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.urban[i][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[i][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.urban[i][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.urban[i][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;
		}

		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.urban[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		for (int j = 1; j < N; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (current.urban[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.urban[N - 1][0] << " kWh";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"└─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
		wcout << L"┴─────────┘" << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		cout << endl;
		cout << "---------------------------------------------------------------"
			<< endl;
		cout << "1. Start to edit" << endl;
		cout << "0. Go back" << endl;
		cin >> opt;
		if (opt == 1) {
			adminEditRate_Urban_rowSelect(current);
		}
		else if (opt == 0) {
			return;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	} while (opt != 0);
}
// Rural
void adminEditRate_Rural_editDetail(int row, int col, rateRecord& current)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	double input;
	do {
		system("cls");
		if (row == 0) {
			cout << "RATE - URBAN" << endl;
			cout << "=================================================================" << endl;
			cout << "Here is the current rate for rural users" << endl;
			cout << "You are changing data of row 0, col " << row << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << endl;
#pragma region display2
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++) // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;



			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 15);
			if (current.rural[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.rural[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				if (i == col)
					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				else
					SetConsoleTextAttribute(hConsole, 15);
				if (current.rural[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.rural[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				if (i == row) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.rural[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.rural[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.rural[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.rural[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 15);
			if (current.rural[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.rural[N - 1][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";


			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.rural[N - 1][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[N - 1][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else if (row == 5) {
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "===========================================================" << endl;
			cout << "Here is the current rate for rural users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << endl;
			if (col == 0) {
#pragma region display
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++) // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;



				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.rural[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.rural[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.rural[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.rural[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.rural[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;

				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.rural[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.rural[N - 1][0] << " Ver";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";


				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[N - 1][j] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.rural[N - 1][j];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion 
			}
			else {
#pragma region diaplay3
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++) // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;



				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.rural[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.rural[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.rural[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.rural[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.rural[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;

				}

				// Last line

				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 15);
				if (current.rural[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.rural[N - 1][0] << " Ver";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";


				for (int j = 1; j < N; j++) {
					if (j == col)
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					else
						SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[N - 1][j] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.rural[N - 1][j];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
		}
		else {
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "===========================================================" << endl;
			cout << "Here is the current rate for rural users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << endl;
			if (col == 0) {
#pragma region display
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++) // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;



				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.rural[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.rural[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.rural[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					if (i == row)
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					else
						SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.rural[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.rural[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;

				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.rural[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.rural[N - 1][0] << " Ver";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";


				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[N - 1][j] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.rural[N - 1][j];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion 
			}
			else {
#pragma region diaplay3
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++) // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;



				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.rural[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.rural[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.rural[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					if (i == row) {
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(4) << "row" << setw(2) << i << " "; // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.rural[i][0] << " Ver";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						for (int j = 1; j < N; j++) {
							if (j == col)
								SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
							else
								SetConsoleTextAttribute(hConsole, 15);
							if (current.rural[i][j] == -1)
								wcout << setw(9) << " ";
							else
								wcout << setw(9) << current.rural[i][j];
							SetConsoleTextAttribute(hConsole, 8);
							wcout << L"│";
						}
					}
					else {
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(4) << "row" << setw(2) << i << " "; // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.rural[i][0] << " Ver";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						for (int j = 1; j < N; j++) {
							SetConsoleTextAttribute(hConsole, 15);
							if (current.rural[i][j] == -1)
								wcout << setw(9) << " ";
							else
								wcout << setw(9) << current.rural[i][j];
							SetConsoleTextAttribute(hConsole, 8);
							wcout << L"│";
						}
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++)
						wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;

				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.rural[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.rural[N - 1][0] << " Ver";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";


				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.rural[N - 1][j];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
		}
		cout << "Input -2 to exit, input -1 to remove data" << endl;

		if (row != 0 && col != 0) {
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "You've selected row " << row << " col " << col << ", the detail is as follows: " << endl;
			cout << "Rate Type: " << "Rural E-" << row << " Tier " << col << endl;
			cout << "Voltage Interval: " << current.rural[0][col - 1] << " - " << current.rural[0][col] << endl;
			cout << "Rate: " << current.rural[row][col] << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "Change rate to: ";
			cin >> input;
			if (input != -2) {
				current.rural[row][col] = input;
			}
			else {
				return;
			}
		}
		else if (row == 0) {
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "You've selected row " << row << " col " << col << ", the detail is as follows: " << endl;
			cout << "Voltage Interval: " << current.rural[0][col - 1] << " - " << current.rural[0][col] << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "Change the interval to: " << current.rural[0][col - 1] << " - ";
			cin >> input;
			if (input != -2) {
				current.rural[row][col] = input;
			}
			else {
				return;
			}
		}
		else {
			cout << "------------------------------------------------------------------------------------" << endl;
			cout << "You cannot change the number for version" << endl;
			Sleep(1000);
			return;
		}
	} while (input != -2);
}
void adminEditRate_Rural_colSelect(int row, rateRecord& current)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int col;
	do {
		system("cls");
		if (row == 0) {
			cout << "RATE - URBAN" << endl;
			cout << "=================================================================" << endl;
			cout << "Here is the current rate for rural users" << endl;
			cout << "You are changing data of row 0" << endl;
			cout << "-----------------------------------------------------------------" << endl;
			cout << endl;
#pragma region display2
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++) // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;



			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
			if (current.rural[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.rural[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.rural[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.rural[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				if (i == row) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.rural[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.rural[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.rural[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.rural[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.rural[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.rural[N - 1][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";


			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.rural[N - 1][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[N - 1][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else if (row == 5) {
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "===========================================================" << endl;
			cout << "Here is the current rate for rural users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << endl;
#pragma region diaplay3
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++) // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;



			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.rural[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.rural[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				SetConsoleTextAttribute(hConsole, 6);
				if (current.rural[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.rural[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << i << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 15);
				if (current.rural[i][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.rural[i][0] << " Ver";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[i][j] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.rural[i][j];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

			}

			// Last line

			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
			if (current.rural[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.rural[N - 1][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";


			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.rural[N - 1][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[N - 1][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else {
			system("cls");

			cout << "RATE - URBAN" << endl;
			cout << "===========================================================" << endl;
			cout << "Here is the current rate for rural users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << endl;
#pragma region diaplay3
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++) // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;



			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.rural[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.rural[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				SetConsoleTextAttribute(hConsole, 6);
				if (current.rural[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.rural[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				if (i == row) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					if (current.rural[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.rural[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
						if (current.rural[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.rural[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " "; // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.rural[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.rural[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.rural[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.rural[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " "; // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++)
					wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 15);
			if (current.rural[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.rural[N - 1][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";


			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.rural[N - 1][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[N - 1][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		cout << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "col: ";
		cin >> col;
		if (row == 0 && col == 0) {
			cout << "You cannot change the data of row 0, col 0" << endl;
			Sleep(1000);
		}
		else if (col != -1) {
			adminEditRate_Rural_editDetail(row, col, current);
		}
		else {
			return;
		}
	} while (col != -1);
}
void adminEditRate_Rural_rowSelect(rateRecord& current)
{
	int row;
	do {
		system("cls");

		cout << "RATE - URBAN" << endl;
		cout << "===========================================================" << endl;
		cout << "Here is the current rate for rural users" << endl;
		cout << "Select the row you want to change" << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << endl;
#pragma region display1
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		_setmode(_fileno(stdout), _O_U16TEXT);



		wcout << setw(10) << " ";
		for (int i = 0; i < N; i++) // col
		{
			SetConsoleTextAttribute(hConsole, 9);
			wcout << "col " << setw(6) << left << i;
		}
		wcout << endl;

		// Upper Line
		SetConsoleTextAttribute(hConsole, 8);
		wcout << setw(7) << right << " ";
		wcout << L"┌─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┬─────────";
		wcout << L"┬─────────┐" << endl;



		// 0,0
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(4) << "row" << setw(2) << 0 << " "; // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[0][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.rural[0][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		// Line 1
		for (int i = 1; i < N; i++) {
			SetConsoleTextAttribute(hConsole, 6);
			if (current.rural[0][i] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(6) << current.rural[0][i] << " KV";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}
		wcout << endl;

		// Middle Line
		SetConsoleTextAttribute(hConsole, 6);
		wcout << setw(7) << " "; // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

		// Content
		for (int i = 1; i < N - 1; i++) {
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << i << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.rural[i][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.rural[i][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.rural[i][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[i][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " "; // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

		}
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(4) << "row" << setw(2) << N - 1 << " "; // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.rural[N - 1][0] << " Ver";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";


		for (int j = 1; j < N; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (current.rural[N - 1][j] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.rural[N - 1][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(7) << " "; // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"└─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┴─────────";
		wcout << L"┴─────────┘" << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		SetConsoleTextAttribute(hConsole, 15);
#pragma endregion 
		cout << endl;
		cout << "Input -1 to go back" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "Change row: ";
		cin >> row;
		if (row != -1) {
			adminEditRate_Rural_colSelect(row, current);
		}
		else {
			return;
		}
	} while (row != -1);
}
void adminEditRate_Rural_Overview(rateRecord& current)
{
	int opt;
	do {
		system("cls");
		cout << "RATE - URBAN" << endl;
		cout << "===========================================================" << endl;
		cout << "Here is the current rate for rural users" << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << endl;
#pragma region display0
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		_setmode(_fileno(stdout), _O_U16TEXT);


		// Upper Line
		SetConsoleTextAttribute(hConsole, 12);
		wcout << "Rural" << endl;
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"┌─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┬─────────";
		wcout << L"┬─────────┐" << endl;

		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);

		// 0,0
		if (current.rural[0][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.rural[0][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		// Line 1
		for (int i = 1; i < N; i++) {
			SetConsoleTextAttribute(hConsole, 6);
			if (current.rural[0][i] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(6) << current.rural[0][i] << " KV";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}
		wcout << endl;

		// Middle Line
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

		// Content
		for (int i = 1; i < N - 1; i++) {
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.rural[i][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.rural[i][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.rural[i][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.rural[i][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++)
				wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

		}

		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.rural[N - 1][0] << " Ver";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";


		for (int j = 1; j < N; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (current.rural[N - 1][j] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.rural[N - 1][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}


		wcout << endl;
		wcout << L"└─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┴─────────";
		wcout << L"┴─────────┘" << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		cout << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "1. Start to edit" << endl;
		cout << "0. Go back" << endl;
		cin >> opt;
		if (opt == 1) {
			adminEditRate_Rural_rowSelect(current);
		}
		else if (opt == 0) {
			return;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	} while (opt != 0);
}
// Enterprise
void adminEditRate_Enterprise_editDetail(int row, int col, rateRecord& current) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	double input;
	do {
		system("cls");
		if (row == 0) {
			cout << "RATE - ENTERPRISE" << endl;
			cout
				<< "================================================================="
				<< endl;
			cout << "Here is the current rate for Enterprise users" << endl;
			cout << "You are changing data of row 0, col " << row << endl;
			cout
				<< "-----------------------------------------------------------------"
				<< endl;
			cout << endl;
#pragma region display2
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++)  // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;

			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 15);
			if (current.ent[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.ent[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				if (i == col)
					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				else
					SetConsoleTextAttribute(hConsole, 15);
				if (current.ent[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.ent[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				if (i == row) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.ent[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.ent[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;
			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.ent[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.ent[N - 1][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.ent[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else if (row == 5) {
			system("cls");

			cout << "RATE - ENTERPRISE" << endl;
			cout << "==========================================================="
				<< endl;
			cout << "Here is the current rate for Enterprise users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------"
				<< endl;
			cout << endl;
			if (col == 0) {
#pragma region display
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++)  // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;

				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.ent[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.ent[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.ent[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.ent[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;
				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.ent[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.ent[N - 1][0];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
			else {
#pragma region diaplay3
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++)  // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;

				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.ent[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.ent[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.ent[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.ent[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;
				}

				// Last line

				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 15);
				if (current.ent[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.ent[N - 1][0] << " Ver";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				for (int j = 1; j < N; j++) {
					if (j == col)
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					else
						SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.ent[N - 1][0];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
		}
		else {
			system("cls");

			cout << "RATE - ENTERPRISE" << endl;
			cout << "==========================================================="
				<< endl;
			cout << "Here is the current rate for Enterprise users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------"
				<< endl;
			cout << endl;
			if (col == 0) {
#pragma region display
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++)  // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;

				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.ent[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.ent[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.ent[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					if (i == row)
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					else
						SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.ent[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;
				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.ent[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[N - 1][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
			else {
#pragma region diaplay3
				_setmode(_fileno(stdout), _O_U16TEXT);
				wcout << setw(10) << " ";
				for (int i = 0; i < N; i++)  // col
				{
					SetConsoleTextAttribute(hConsole, 9);
					wcout << "col " << setw(6) << left << i;
				}
				wcout << endl;

				// Upper Line
				SetConsoleTextAttribute(hConsole, 8);
				wcout << setw(7) << right << " ";
				wcout << L"┌─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
				wcout << L"┬─────────┐" << endl;

				// 0,0
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.ent[0][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[0][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				// Line 1
				for (int i = 1; i < N; i++) {
					SetConsoleTextAttribute(hConsole, 6);
					if (current.ent[0][i] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(6) << current.ent[0][i] << " KV";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;

				// Middle Line
				SetConsoleTextAttribute(hConsole, 6);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;

				// Content
				for (int i = 1; i < N - 1; i++) {
					if (i == row) {
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(4) << "row" << setw(2) << i << " ";  // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.ent[i][0] << " Ver";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						for (int j = 1; j < N; j++) {
							if (j == col)
								SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
							else
								SetConsoleTextAttribute(hConsole, 15);
							if (current.ent[i][j] == -1)
								wcout << setw(9) << " ";
							else
								wcout << setw(9) << current.ent[i][j];
							SetConsoleTextAttribute(hConsole, 8);
							wcout << L"│";
						}
					}
					else {
						SetConsoleTextAttribute(hConsole, 9);
						wcout << setw(4) << "row" << setw(2) << i << " ";  // row
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][0] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(5) << current.ent[i][0] << " Ver";
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
						for (int j = 1; j < N; j++) {
							SetConsoleTextAttribute(hConsole, 15);
							if (current.ent[i][j] == -1)
								wcout << setw(9) << " ";
							else
								wcout << setw(9) << current.ent[i][j];
							SetConsoleTextAttribute(hConsole, 8);
							wcout << L"│";
						}
					}
					wcout << endl;
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(7) << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"├─────────";
					for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
					wcout << L"┼─────────┤" << endl;
				}
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 6);
				if (current.ent[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";

				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[N - 1][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[N - 1][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}

				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"└─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
				wcout << L"┴─────────┘" << endl;
				_setmode(_fileno(stdout), _O_TEXT);
				SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
			}
		}
		cout << "Input -2 to exit, input -1 to remove data" << endl;

		if (row != 0 && col != 0) {
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "You've selected row " << row << " col " << col
				<< ", the detail is as follows: " << endl;
			cout << "Rate Type: "
				<< "Enterprise E-" << row << " Tier " << col << endl;
			cout << "Voltage Interval: " << current.ent[0][col - 1] << " - "
				<< current.ent[0][col] << endl;
			cout << "Rate: " << current.ent[row][col] << endl;
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "Change rate to: ";
			cin >> input;
			if (input != -2) {
				current.ent[row][col] = input;
			}
			else {
				return;
			}
		}
		else if (row == 0) {
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "You've selected row " << row << " col " << col
				<< ", the detail is as follows: " << endl;
			cout << "Voltage Interval: " << current.ent[0][col - 1] << " - "
				<< current.ent[0][col] << endl;
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "Change the interval to: " << current.ent[0][col - 1] << " - ";
			cin >> input;
			if (input != -2) {
				current.ent[row][col] = input;
			}
			else {
				return;
			}
		}
		else {
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "You've selected row " << row << " col " << col
				<< ", the detail is as follows: " << endl;
			cout << "Energy Interval: " << current.ent[row - 1][0] << " - "
				<< current.ent[row][0] << endl;
			cout << "----------------------------------------------------------------"
				"--------------------"
				<< endl;
			cout << "You cannot change the number for versions" << endl;
			Sleep(1000);
			return;
		}
	} while (input != -2);
}
void adminEditRate_Enterprise_colSelect(int row, rateRecord& current) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int col;
	do {
		system("cls");
		if (row == 0) {
			cout << "RATE - ENTERPRISE" << endl;
			cout
				<< "================================================================="
				<< endl;
			cout << "Here is the current rate for Enterprise users" << endl;
			cout << "You are changing data of row 0" << endl;
			cout
				<< "-----------------------------------------------------------------"
				<< endl;
			cout << endl;
#pragma region display2
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++)  // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;

			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
			if (current.ent[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.ent[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.ent[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.ent[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				if (i == row) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.ent[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.ent[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;
			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.ent[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.ent[N - 1][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.ent[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else if (row == 5) {
			system("cls");

			cout << "RATE - ENTERPRISE" << endl;
			cout << "==========================================================="
				<< endl;
			cout << "Here is the current rate for Enterprise users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------"
				<< endl;
			cout << endl;
#pragma region diaplay3
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++)  // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;

			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.ent[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.ent[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				SetConsoleTextAttribute(hConsole, 6);
				if (current.ent[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.ent[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(4) << "row" << setw(2) << i << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				SetConsoleTextAttribute(hConsole, 15);
				if (current.ent[i][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.ent[i][0] << " Ver";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
				for (int j = 1; j < N; j++) {
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[i][j] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(9) << current.ent[i][j];
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;
			}

			// Last line

			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
			if (current.ent[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.ent[N - 1][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
				if (current.ent[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[N - 1][0];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		else {
			system("cls");

			cout << "RATE - ENTERPRISE" << endl;
			cout << "==========================================================="
				<< endl;
			cout << "Here is the current rate for Enterprise users" << endl;
			cout << "Change data on row " << row << endl;
			cout << "-----------------------------------------------------------"
				<< endl;
			cout << endl;
#pragma region diaplay3
			_setmode(_fileno(stdout), _O_U16TEXT);
			wcout << setw(10) << " ";
			for (int i = 0; i < N; i++)  // col
			{
				SetConsoleTextAttribute(hConsole, 9);
				wcout << "col " << setw(6) << left << i;
			}
			wcout << endl;

			// Upper Line
			SetConsoleTextAttribute(hConsole, 8);
			wcout << setw(7) << right << " ";
			wcout << L"┌─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
			wcout << L"┬─────────┐" << endl;

			// 0,0
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.ent[0][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.ent[0][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			// Line 1
			for (int i = 1; i < N; i++) {
				SetConsoleTextAttribute(hConsole, 6);
				if (current.ent[0][i] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(6) << current.ent[0][i] << " KV";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}
			wcout << endl;

			// Middle Line
			SetConsoleTextAttribute(hConsole, 6);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;

			// Content
			for (int i = 1; i < N - 1; i++) {
				if (i == row) {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
					if (current.ent[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
						if (current.ent[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.ent[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				else {
					SetConsoleTextAttribute(hConsole, 9);
					wcout << setw(4) << "row" << setw(2) << i << " ";  // row
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					SetConsoleTextAttribute(hConsole, 15);
					if (current.ent[i][0] == -1)
						wcout << setw(9) << " ";
					else
						wcout << setw(5) << current.ent[i][0] << " Ver";
					SetConsoleTextAttribute(hConsole, 8);
					wcout << L"│";
					for (int j = 1; j < N; j++) {
						SetConsoleTextAttribute(hConsole, 15);
						if (current.ent[i][j] == -1)
							wcout << setw(9) << " ";
						else
							wcout << setw(9) << current.ent[i][j];
						SetConsoleTextAttribute(hConsole, 8);
						wcout << L"│";
					}
				}
				wcout << endl;
				SetConsoleTextAttribute(hConsole, 9);
				wcout << setw(7) << " ";  // row
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"├─────────";
				for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
				wcout << L"┼─────────┤" << endl;
			}
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.ent[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.ent[N - 1][0];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";

			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.ent[N - 1][0] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(5) << current.ent[N - 1][0] << " Ver";
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"└─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
			wcout << L"┴─────────┘" << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		}
		cout << endl;
		cout << "---------------------------------------------------------------"
			<< endl;
		cout << "col: ";
		cin >> col;
		if (row == 0 && col == 0) {
			cout << "You cannot change the data of row 0, col 0" << endl;
			Sleep(1000);
		}
		else if (col != -1) {
			adminEditRate_Enterprise_editDetail(row, col, current);
		}
		else {
			return;
		}
	} while (col != -1);
}
void adminEditRate_Enterprise_rowSelect(rateRecord& current) {
	int row;
	do {
		system("cls");

		cout << "RATE - ENTERPRISE" << endl;
		cout << "==========================================================="
			<< endl;
		cout << "Here is the current rate for Enterprise users" << endl;
		cout << "Select the row you want to change" << endl;
		cout << "-----------------------------------------------------------"
			<< endl;
		cout << endl;
#pragma region display1
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		_setmode(_fileno(stdout), _O_U16TEXT);

		wcout << setw(10) << " ";
		for (int i = 0; i < N; i++)  // col
		{
			SetConsoleTextAttribute(hConsole, 9);
			wcout << "col " << setw(6) << left << i;
		}
		wcout << endl;

		// Upper Line
		SetConsoleTextAttribute(hConsole, 8);
		wcout << setw(7) << right << " ";
		wcout << L"┌─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
		wcout << L"┬─────────┐" << endl;

		// 0,0
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(4) << "row" << setw(2) << 0 << " ";  // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.ent[0][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.ent[0][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		// Line 1
		for (int i = 1; i < N; i++) {
			SetConsoleTextAttribute(hConsole, 6);
			if (current.ent[0][i] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(6) << current.ent[0][i] << " KV";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}
		wcout << endl;

		// Middle Line
		SetConsoleTextAttribute(hConsole, 6);
		wcout << setw(7) << " ";  // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

		// Content
		for (int i = 1; i < N - 1; i++) {
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(4) << "row" << setw(2) << i << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.ent[i][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.ent[i][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.ent[i][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[i][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			SetConsoleTextAttribute(hConsole, 9);
			wcout << setw(7) << " ";  // row
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;
		}
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(4) << "row" << setw(2) << N - 1 << " ";  // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.ent[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.ent[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		for (int j = 1; j < N; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (current.ent[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.ent[N - 1][0] << "Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		SetConsoleTextAttribute(hConsole, 9);
		wcout << setw(7) << " ";  // row
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"└─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
		wcout << L"┴─────────┘" << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		cout << endl;
		cout << "Input -1 to go back" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "Change row: ";
		cin >> row;

		//				system("cls");
		//				if (row == 0)
		//				{
		//					cout << "RATE - ENTERPRISE" << endl;
		//					cout <<
		//"=================================================================" <<
		//endl; 					cout << "Here is the current rate for Enterprise users" << endl; 					cout <<
		//"You are changing data of row 0" << endl; 					cout <<
		//"-----------------------------------------------------------------" <<
		//endl; 					cout << endl; #pragma region display2 					_setmode(_fileno(stdout),
		//_O_U16TEXT); 					wcout << setw(3) << " "; 					for (int i = 0; i < N; i++)
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//3); 						wcout << "col " << setw(6) << left << i;
		//					}
		//					wcout << endl;
		//
		//
		//					// Upper Line
		//					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << L"┌─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┬─────────";
		//					wcout << L"┬─────────┐" << endl;
		//					wcout << L"│";
		//					SetConsoleTextAttribute(hConsole, 6);
		//
		//
		//					// 0,0
		//					SetConsoleTextAttribute(hConsole, BACKGROUND_RED |
		//7); 					if (current.ent[0][0] == -1) 						wcout << setw(9) << " "; 					else 						wcout <<
		//setw(9) << current.ent[0][0]; 					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << L"│";
		//
		//					// Line 1
		//					for (int i = 1; i < N; i++)
		//					{
		//						SetConsoleTextAttribute(hConsole, BACKGROUND_RED |
		//7); 						if (current.ent[0][i] == -1) 							wcout << setw(9) << right << " "; 						else
		//							wcout << setw(6) << right << current.ent[0][i] << "
		//KV"; 						SetConsoleTextAttribute(hConsole, 8); 						wcout << L"│";
		//					}
		//					wcout << endl;
		//
		//					// Middle Line
		//					wcout << L"├─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┼─────────";
		//					wcout << L"┼─────────┤" << endl;
		//
		//					// Content
		//					for (int i = 1; i < N - 1; i++)
		//					{
		//						wcout << L"│";
		//						SetConsoleTextAttribute(hConsole,
		//6); 						if (current.ent[i][0] == -1) 							wcout << setw(9) << " "; 						else 							wcout <<
		//setw(5) << current.ent[i][0] << " Ver";
		//						SetConsoleTextAttribute(hConsole,
		//8); 						wcout << L"│"; 						for (int j = 1; j < N; j++)
		//						{
		//							SetConsoleTextAttribute(hConsole,
		//15); 							if (current.ent[i][j] == -1) 								wcout << setw(9) << " "; 							else 								wcout <<
		//setw(9) << current.ent[i][j]; 							SetConsoleTextAttribute(hConsole, 8);
		//							wcout << L"│";
		//						}
		//
		//						wcout << endl;
		//						wcout << L"├─────────";
		//						for (int i = 1; i < N - 1; i++)
		//							wcout << L"┼─────────";
		//						wcout << L"┼─────────┤" << endl;
		//
		//					}
		//
		//					wcout << L"│";
		//					SetConsoleTextAttribute(hConsole, 6);
		//					if (current.ent[N - 1][0] == -1)
		//						wcout << setw(9) << " ";
		//					else
		//						wcout << setw(9) << current.ent[N -
		//1][0]; 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//
		//
		//					for (int j = 1; j < N; j++)
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//15); 						if (current.ent[N - 1][0] == -1) 							wcout << setw(9) << " "; 						else
		//							wcout << setw(9) << current.ent[N -
		//1][0]; 						SetConsoleTextAttribute(hConsole, 8); 						wcout << L"│";
		//					}
		//
		//
		//					wcout << endl;
		//					wcout << L"└─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┴─────────";
		//					wcout << L"┴─────────┘" << endl;
		//					_setmode(_fileno(stdout), _O_TEXT);
		//					SetConsoleTextAttribute(hConsole, 15);
		//#pragma endregion
		//				}
		//
		//				else
		//				{
		//					system("cls");
		//
		//					cout << "RATE - ENTERPRISE" << endl;
		//					cout <<
		//"===========================================================" << endl;
		//					cout << "Here is the current rate for Enterprise users" <<
		//endl; 					cout << "Change data on row " << row << endl; 					cout <<
		//"-----------------------------------------------------------" << endl;
		//					cout << endl;
		//#pragma region diaplay3
		//					_setmode(_fileno(stdout), _O_U16TEXT);
		//					wcout << setw(10) << " ";
		//					for (int i = 0; i < N; i++) // col
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//9); 						wcout << "col " << setw(6) << left << i;
		//					}
		//					wcout << endl;
		//
		//					// Upper Line
		//					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << setw(7) << right << " ";
		//					wcout << L"┌─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┬─────────";
		//					wcout << L"┬─────────┐" << endl;
		//
		//
		//
		//					// 0,0
		//					SetConsoleTextAttribute(hConsole, 9);
		//					wcout << setw(4) << "row" << setw(2) << 0 << " "; //
		//row 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//					SetConsoleTextAttribute(hConsole, 6);
		//					if (current.ent[0][0] == -1)
		//						wcout << setw(9) << " ";
		//					else
		//						wcout << setw(9) <<
		//current.ent[0][0]; 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//
		//					// Line 1
		//					for (int i = 1; i < N; i++)
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//6); 						if (current.ent[0][i] == -1) 							wcout << setw(9) << " "; 						else 							wcout <<
		//setw(6) << current.ent[0][i] << " KV"; 						SetConsoleTextAttribute(hConsole,
		//8); 						wcout << L"│";
		//					}
		//					wcout << endl;
		//
		//					// Middle Line
		//					SetConsoleTextAttribute(hConsole, 6);
		//					wcout << setw(7) << " "; // row
		//					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << L"├─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┼─────────";
		//					wcout << L"┼─────────┤" << endl;
		//
		//					// Content
		//					for (int i = 1; i < N - 1; i++)
		//					{
		//						if (i == row)
		//						{
		//							SetConsoleTextAttribute(hConsole,
		//9); 							wcout << setw(4) << "row" << setw(2) << i << " "; // row
		//							SetConsoleTextAttribute(hConsole,
		//8); 							wcout << L"│"; 							SetConsoleTextAttribute(hConsole, BACKGROUND_RED | 7);
		//							if (current.ent[i][0] ==
		//-1) 								wcout << setw(9) << " "; 							else 								wcout << setw(5) << current.ent[i][0]
		//<< " Ver"; 							SetConsoleTextAttribute(hConsole, 8); 							wcout << L"│"; 							for (int j
		//= 1; j < N; j++)
		//							{
		//								SetConsoleTextAttribute(hConsole, BACKGROUND_RED |
		//7); 								if (current.ent[i][j] == -1) 									wcout << setw(9) << " "; 								else 									wcout <<
		//setw(9) << current.ent[i][j]; 								SetConsoleTextAttribute(hConsole, 8);
		//								wcout << L"│";
		//							}
		//						}
		//						else
		//						{
		//							SetConsoleTextAttribute(hConsole,
		//9); 							wcout << setw(4) << "row" << setw(2) << i << " "; // row
		//							SetConsoleTextAttribute(hConsole,
		//8); 							wcout << L"│"; 							SetConsoleTextAttribute(hConsole, 15); 							if
		//(current.ent[i][0] == -1) 								wcout << setw(9) << " "; 							else 								wcout << setw(5)
		//<< current.ent[i][0] << " Ver"; 							SetConsoleTextAttribute(hConsole, 8);
		//							wcout << L"│";
		//							for (int j = 1; j < N;
		//j++)
		//							{
		//								SetConsoleTextAttribute(hConsole,
		//15); 								if (current.ent[i][j] == -1) 									wcout << setw(9) << " "; 								else 									wcout <<
		//setw(9) << current.ent[i][j]; 								SetConsoleTextAttribute(hConsole, 8);
		//								wcout << L"│";
		//							}
		//						}
		//						wcout << endl;
		//						SetConsoleTextAttribute(hConsole,
		//9); 						wcout << setw(7) << " "; // row 						SetConsoleTextAttribute(hConsole, 8);
		//						wcout << L"├─────────";
		//						for (int i = 1; i < N - 1; i++)
		//							wcout << L"┼─────────";
		//						wcout << L"┼─────────┤" << endl;
		//
		//					}
		//					SetConsoleTextAttribute(hConsole, 9);
		//					wcout << setw(4) << "row" << setw(2) << N - 1 << " "; //
		//row 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//					SetConsoleTextAttribute(hConsole, 6);
		//					if (current.ent[N - 1][0] == -1)
		//						wcout << setw(9) << " ";
		//					else
		//						wcout << setw(9) << current.ent[N -
		//1][0]; 					SetConsoleTextAttribute(hConsole, 8); 					wcout << L"│";
		//
		//
		//					for (int j = 1; j < N; j++)
		//					{
		//						SetConsoleTextAttribute(hConsole,
		//15); 						if (current.ent[N - 1][0] == -1) 							wcout << setw(9) << " "; 						else
		//							wcout << setw(9) << current.ent[N -
		//1][0]; 						SetConsoleTextAttribute(hConsole, 8); 						wcout << L"│";
		//					}
		//
		//					wcout << endl;
		//					SetConsoleTextAttribute(hConsole, 9);
		//					wcout << setw(7) << " "; // row
		//					SetConsoleTextAttribute(hConsole, 8);
		//					wcout << L"└─────────";
		//					for (int i = 1; i < N - 1; i++)
		//						wcout << L"┴─────────";
		//					wcout << L"┴─────────┘" << endl;
		//					_setmode(_fileno(stdout), _O_TEXT);
		//					SetConsoleTextAttribute(hConsole, 15);
		//#pragma endregion
		//				}
		if (row != -1) {
			adminEditRate_Enterprise_colSelect(row, current);
		}
		else {
			return;
		}
	} while (row != -1);
}
void adminEditRate_Enterprise_Overview(rateRecord& current) {
	int opt;
	do {
		system("cls");
		cout << "RATE - ENTERPRISE" << endl;
		cout << "==========================================================="
			<< endl;
		cout << "Here is the current rate for Enterprise users" << endl;
		cout << "-----------------------------------------------------------"
			<< endl;
		cout << endl;
#pragma region display0
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		_setmode(_fileno(stdout), _O_U16TEXT);

		// Upper Line
		SetConsoleTextAttribute(hConsole, 12);
		wcout << "Enterprise" << endl;
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"┌─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
		wcout << L"┬─────────┐" << endl;

		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);

		// 0,0
		if (current.ent[0][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.ent[0][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		// Line 1
		for (int i = 1; i < N; i++) {
			SetConsoleTextAttribute(hConsole, 6);
			if (current.ent[0][i] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(6) << current.ent[0][i] << " KV";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}
		wcout << endl;

		// Middle Line
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

		// Content
		for (int i = 1; i < N - 1; i++) {
			wcout << L"│";
			SetConsoleTextAttribute(hConsole, 6);
			if (current.ent[i][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.ent[i][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
			for (int j = 1; j < N; j++) {
				SetConsoleTextAttribute(hConsole, 15);
				if (current.ent[i][j] == -1)
					wcout << setw(9) << " ";
				else
					wcout << setw(9) << current.ent[i][j];
				SetConsoleTextAttribute(hConsole, 8);
				wcout << L"│";
			}

			wcout << endl;
			wcout << L"├─────────";
			for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
			wcout << L"┼─────────┤" << endl;
		}

		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.ent[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.ent[N - 1][0];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";

		for (int j = 1; j < N; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (current.ent[N - 1][0] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(5) << current.ent[N - 1][0] << " Ver";
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"└─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
		wcout << L"┴─────────┘" << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
		cout << endl;
		cout << "---------------------------------------------------------------"
			<< endl;
		cout << "1. Start to edit" << endl;
		cout << "0. Go back" << endl;
		cin >> opt;
		if (opt == 1) {
			adminEditRate_Enterprise_rowSelect(current);
		}
		else if (opt == 0) {
			return;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	} while (opt != 0);
}
// Index
void adminEditRate_Index(rateRecord& current) {
	int opt;
	do {
		system("cls");
		cout << "RATE OverView" << endl;
		cout << "===========================================================" << endl;
		cout << "Which class do you want to change?" << endl;
		cout << "The current rule is on its " << getRateEdition() << " edition." << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << endl;
		cout << "1. Urban Users" << endl;
		cout << "2. Rural Users" << endl;
		cout << "3. Enterprise Users" << endl;
		cout << "0. Save & Go back" << endl;
		cout << "-1. Go back without saving" << endl;
 		cout << "-----------------------------------------------------------" << endl;
		cin >> opt;
		fstream ratefile;
		switch (opt) {
		case 1: 
			adminEditRate_Urban_Overview(current);
			break;
		case 2: 
			adminEditRate_Rural_Overview(current);
			break;
		case 3:
			adminEditRate_Enterprise_Overview(current);
				break;
		case 0:
			ratefile.open(FLOC_RATE, ios::binary | ios::out | ios::app);
			current.rateNo = current.rateNo + 1;
			ratefile.write((char*)&current, sizeof(rateRecord));
			ratefile.close();
			return;
		case -1:
			return;
		default: cout << "Invalid input, please try again" << endl;
		}
	} while (opt > 0);
}
void MRShowRate(rateRecord current = getCurrentRate()) {
	system("cls");
	cout << "RATE OverView" << endl;
	cout << "===========================================================" << endl;
	cout << "The current rule is on its " << getRateEdition() << " edition." << endl;
	cout << "-----------------------------------------------------------" << endl;
#pragma region display0
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Urban" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.urban[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.urban[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++) {
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.urban[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++) {
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.urban[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.urban[i][0] << " kWh";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (current.urban[i][j] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.urban[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;
	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.urban[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.urban[N - 1][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	for (int j = 1; j < N; j++) {
		SetConsoleTextAttribute(hConsole, 15);
		if (current.urban[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.urban[N - 1][0] << " kWh";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}

	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;
	_setmode(_fileno(stdout), _O_TEXT);
	SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
#pragma region display0
	_setmode(_fileno(stdout), _O_U16TEXT);


	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Rural" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.rural[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.rural[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++) {
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.rural[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++) {
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.rural[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.rural[i][0] << " Ver";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (current.rural[i][j] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.rural[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++)
			wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;

	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.rural[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(5) << current.rural[N - 1][0] << " Ver";
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";


	for (int j = 1; j < N; j++) {
		SetConsoleTextAttribute(hConsole, 15);
		if (current.rural[N - 1][j] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(9) << current.rural[N - 1][j];
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}


	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++)
		wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;
	_setmode(_fileno(stdout), _O_TEXT);
	SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
#pragma region display0
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Upper Line
	SetConsoleTextAttribute(hConsole, 12);
	wcout << "Enterprise" << endl;
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"┌─────────";
	for (int i = 1; i < N - 1; i++) wcout << L"┬─────────";
	wcout << L"┬─────────┐" << endl;

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);

	// 0,0
	if (current.ent[0][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.ent[0][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	// Line 1
	for (int i = 1; i < N; i++) {
		SetConsoleTextAttribute(hConsole, 6);
		if (current.ent[0][i] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(6) << current.ent[0][i] << " KV";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}
	wcout << endl;

	// Middle Line
	wcout << L"├─────────";
	for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
	wcout << L"┼─────────┤" << endl;

	// Content
	for (int i = 1; i < N - 1; i++) {
		wcout << L"│";
		SetConsoleTextAttribute(hConsole, 6);
		if (current.ent[i][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.ent[i][0] << " Ver";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
		for (int j = 1; j < N; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (current.ent[i][j] == -1)
				wcout << setw(9) << " ";
			else
				wcout << setw(9) << current.ent[i][j];
			SetConsoleTextAttribute(hConsole, 8);
			wcout << L"│";
		}

		wcout << endl;
		wcout << L"├─────────";
		for (int i = 1; i < N - 1; i++) wcout << L"┼─────────";
		wcout << L"┼─────────┤" << endl;
	}

	wcout << L"│";
	SetConsoleTextAttribute(hConsole, 6);
	if (current.ent[N - 1][0] == -1)
		wcout << setw(9) << " ";
	else
		wcout << setw(9) << current.ent[N - 1][0];
	SetConsoleTextAttribute(hConsole, 8);
	wcout << L"│";

	for (int j = 1; j < N; j++) {
		SetConsoleTextAttribute(hConsole, 15);
		if (current.ent[N - 1][0] == -1)
			wcout << setw(9) << " ";
		else
			wcout << setw(5) << current.ent[N - 1][0] << " Ver";
		SetConsoleTextAttribute(hConsole, 8);
		wcout << L"│";
	}

	wcout << endl;
	wcout << L"└─────────";
	for (int i = 1; i < N - 1; i++) wcout << L"┴─────────";
	wcout << L"┴─────────┘" << endl;
	_setmode(_fileno(stdout), _O_TEXT);
	SetConsoleTextAttribute(hConsole, 15);
#pragma endregion
	system("pause");
}