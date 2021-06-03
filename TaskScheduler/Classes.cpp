#include "MainHeader.h"
#include "ClassHeader.h"

// Time_And_Path - îñíîâíîé êëàññ äëÿ ÕĞÀÍÅÍÈß ÄÀÍÍÛÕ ÈÇ TXT ÂÎ ÂĞÅÌß ÄÅÉÑÒÂÈß ÏĞÎÃĞÀÌÌÛ.

void Time_And_Path::showDATA(HWND bruhHWND) {
    ShellExecute(bruhHWND, L"open", path.data(), NULL, NULL, SW_RESTORE);
}


void Time_And_Path::set_time(wstring h, wstring  sec, wstring  min, wstring  d, wstring  m, wstring  y) {
    hour = stoi(h);
    second = stoi(sec);
    minute = stoi(min);
    day = stoi(d);
    month = stoi(m);
    year = stoi(y);
}

void Time_And_Path::set_path(wstring p) {
    path = p.data();
}

void Time_And_Path::set_title(wstring t) {
    title = t.data();
}


void Time_And_Path::set_index(int i) {
    index = i;
}


void Time_And_Path::set_ThreadSleep(long sleep) {
    ThreadSleep = sleep;
}
////////////////////

int Time_And_Path::get_hour() {
    return hour;
}

int Time_And_Path::get_second() {
    return second;
}

int Time_And_Path::get_minute() {
    return minute;
}

int Time_And_Path::get_day() {
    return day;
}

int Time_And_Path::get_month() {
    return month;
}

int Time_And_Path::get_year() {
    return year;
}

wstring Time_And_Path::get_path() {
    return path;
}

wstring Time_And_Path::get_title() {
    return title;
}

int Time_And_Path::get_index() {
    return index;
}

long Time_And_Path::get_ThreadSleep() {
    return ThreadSleep;
}

///////////////////






/*
Time_And_Path::Time_And_Path() // êîíñòğóêòîğ ïî óìîë÷àíèş 
{
    index = 0;
}
*/