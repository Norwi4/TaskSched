#pragma once
#include "MainHeader.h"


// Time_And_Path - �������� ����� ��� �������� ������ �� TXT �� ����� �������� ���������.
class Time_And_Path {
public:

    void showDATA(HWND bruhHWND);

    void set_time(wstring h, wstring  sec, wstring  min, wstring  d, wstring  m, wstring  y);

    void set_path(wstring p);

    void set_title(wstring t);

    void set_index(int i);

    void set_ThreadSleep(long sleep);

    /////////
    
    int get_hour();

    int get_second();

    int get_minute();

    int get_day();

    int get_month();

    int get_year();

    wstring get_path();

    wstring get_title();

    int get_index();

    long get_ThreadSleep();

    ////////

    



    //Time_And_Path(); // ����������� �� ��������� 


private:
    // �������� ����
    int hour, second, minute, day, month, year;

    wstring path;

    wstring title;

    int index;

    long ThreadSleep;
};

