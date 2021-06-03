#pragma once
#include "MainHeader.h"
#include "ClassHeader.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// 
// 
// 



////////////////////////////////////////////////////////////////////////////////
//�������:



//toTXT - ������ � TXT �������� ������������� ������!!!
void toTXT(wchar_t* Adress, wchar_t* Date, wchar_t* Time, wchar_t* Title);

//valid_date - ��� �������� ���� ��� ��������. ��������� ���
bool valid_date(int _Year, int _Month, int _DayNo);

//valid_time - ��� �������� ������� ��� ��������. ��������� ���
bool valid_time(int _Hour, int _Minute, int _Second);

//error_msgbox - ������ ���� � ������� ������� ����� ������� � ���������. ��� ������������
void error_msgbox(const wchar_t* Date);

//valid_NOW_date - �������� ����. ������������ � ������ ��������. ������ ��������� ���
bool valid_NOW_date(int y, int m, int d);

//check_DATE_TIME_ADRESS - �������� ��������� ������ ������. ��������������� ����� ������� �����. (������ ������������ � ��������)
bool check_DATE_TIME_ADRESS(wchar_t* Date, wchar_t* Time, wchar_t* Adress, wchar_t* Title);

//check_dt_for_launch - �������� ���� � ����� ��� �������. ������ �� ��� ������� ������ "Create task" � ��� ����� ������ ����������. (�� ������ ������������)
//������������ toTXT_REWRITE
bool check_dt_for_launch(int y, int m, int d, int hour, int min, int sec);

// ReadTXT - ������ TXT. ������� ������ TXT ��� �������� � ������.
int ReadTXT(vector<Time_And_Path>& arr);

// StringCountTXT - ������� ����� ����� ��� �������.
int StringCountTXT();

// LaunchTimer - ������ �������. �������� - ����� ��������, �� ������ � �������.
void LaunchTimer(long TSleep, HWND MainHandle);

// ThreadSleep_Update - ��������� ������� �� ���������� ������� (� ������������)
int ThreadSleep_Update(HWND MainHandle);

// GetMinTime_Update - ��������� ������� ���������� �������
int GetMinTime_Update(HWND MainHandle, vector<Time_And_Path>& MyArr);

// toTXT_REWRITE - �������� ���������� ����� �� TXT ��� ���������� txt � ��������� �� ���� 
//(����� ��� ������� ����� ������� ���������� �.�. ����� ��� ������� � ����� ������� �� ������)
bool toTXT_REWRITE();

bool toTXT_AFTER_DELETE(vector<Time_And_Path>& MyArr);

//���������� ���� ����
void SetListBox(HWND MainHandle, HWND listbox, HWND label);

//�������� ���� ����
/*
void GetListBox(HWND MainHandle, HWND listbox, HWND label);
*/

//������� ������� ���� ����� �� �������
void DeleteItem_BY_INDEX(vector<Time_And_Path>& arr, int index);


//void CheckForTask();

void LauchTask(HWND hwnd, HWND hWnd, HWND hLabelmain, HWND hListboxMAIN);