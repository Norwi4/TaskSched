#include "FuncHeader.h"

//toTXT - ÇÀÏÈÑÜ Â TXT ÂÂÅÄÅÍÛÕ ÏÎËÜÇÎÂÀÒÅËÅÌ ÄÀÍÍÛÕ!!!
void toTXT(wchar_t* Adress, wchar_t* Date, wchar_t* Time, wchar_t* Title) {
    wfstream file;

    file.imbue(std::locale(file.getloc(),
        new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::consume_header>));

    file.open(ADRESS_TXT, ios::app);


    wstring s_date = Date;
    int d, m, y;
    wchar_t ch_date;
    std::_stscanf(s_date.c_str(), _T("%d%c%d%c%d"), &d, &ch_date, &m, &ch_date, &y);
    wchar_t year_wchar[256];
    swprintf_s(year_wchar, L"%d", y);


    wstring s_time = Time;
    int hour = -1, min = -1, sec = -1;
    wchar_t ch_time;
    std::_stscanf(s_time.c_str(), _T("%d%c%d%c%d"), &hour, &ch_time, &min, &ch_time, &sec);


    file << setw(2) << setfill(L'0') << d << '.' << setw(2) << setfill(L'0') << m << '.';
    file << setw(4) << year_wchar;
    file << SEPARATOR << setw(2) << setfill(L'0') << hour << ':' << setw(2) << setfill(L'0') << min << ':' << setw(2) << setfill(L'0') << sec
        << SEPARATOR << Adress << SEPARATOR << Title << L"\n";

    file.close();
}

//valid_date - Äëÿ ïðîâåðêè äàòû ïðè ââåäåíèè. ÑÎÊÐÀÙÀÅÒ ÊÎÄ
bool valid_date(int _Year, int _Month, int _DayNo)
{
    int days_in_month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    if (_Year % 4 == 0)
        days_in_month[2] = 29;

    if ((_Month < 1) || (_Month > 12))
        return false;

    if ((_DayNo < 1) || (_DayNo > days_in_month[_Month]))
        return false;

    return true;
}

//valid_time - Äëÿ ïðîâåðêè âðåìåíè ïðè ââåäåíèè. ÑÎÊÐÀÙÀÅÒ ÊÎÄ
bool valid_time(int _Hour, int _Minute, int _Second)
{

    if ((_Hour < 0) || (_Hour > 23))
        return false;

    if ((_Minute < 0) || (_Minute > 59))
        return false;

    if ((_Second < 0) || (_Second > 59))
        return false;

    return true;
}

//error_msgbox - ìåñåäæ áîêñ ñ äàííûìè êîòîðûå íóæíî âûâåñòè â ïàðàìåòðå. ÄËß ÒÅÑÒÈÐÎÂÀÍÈß
void error_msgbox(const wchar_t* Date) {
    MessageBox(NULL, Date, L"", MB_ICONINFORMATION);
}

//valid_NOW_date - Ïðîâåðêà äàòû. èñïîëüçóåòñÿ â äðóãèõ ôóíêöèÿõ. ÏÐÎÑÒÎ ÑÎÊÐÀÙÀÅÒ ÊÎÄ
bool valid_NOW_date(int y, int m, int d, int CURyear,int CURmonth, int CURday)
{

    if (valid_date(y, m, d)) {
        if (y > CURyear) {
            return true;
        }
        else {
            if (y == CURyear) {
                if (m > CURmonth) {
                    return true;
                }
                else {
                    if (m == CURmonth) {
                        if (d >= CURday) {
                            return true;
                        }
                        else {
                            //error_msgbox(L"Invalid date");
                            return false;
                        }
                    }
                }
            }
        }
    }

    return false;

}

//valid_NOW_time - Ïðîâåðêà âðåìåíè. èñïîëüçóåòñÿ â äðóãèõ ôóíêöèÿõ. ÏÐÎÑÒÎ ÑÎÊÐÀÙÀÅÒ ÊÎÄ
bool valid_NOW_time(int hour, int min, int sec, int CURhour, int CURminute, int CURsecond)
{
    if (hour > CURhour) {
        return true;
    }
    else {
        if (hour == CURhour) {
            if (min > CURminute) {
                return true;
            }
            else {
                if (min == CURminute) {
                    if (sec >= CURsecond) {
                        return true;
                    }
                    else {

                        return false;
                    }
                }
            }
        }
    }
    return false;
}

//valid_NOW_DATETIME - Ïðîâåðêà âñåãî âðåìåíè. èñïîëüçóåòñÿ â äðóãèõ ôóíêöèÿõ. ÏÐÎÑÒÎ ÑÎÊÐÀÙÀÅÒ ÊÎÄ
bool valid_NOW_DATETIME(int y, int m, int d, int hour, int min, int sec,
    int CURyear, int CURmonth, int CURday, int CURhour, int CURminute, int CURsecond)
{
    if (valid_NOW_date(y, m, d,CURyear, CURmonth,CURday)) {

        if (valid_time(hour, min, sec)) {
            if ((y == CURyear) && (m == CURmonth) && (d == CURday)) {
                if (valid_NOW_time(hour, min, sec, CURhour, CURminute, CURsecond)) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return true;
            }
        }
        return false;
    }
    else {
        return false;
    }
}

//check_DATE_TIME_ADRESS - ÏÐÎÂÅÐÊÀ ÂÂÅÄÅÍÍÛÕ ÞÇÅÐÎÌ ÄÀÍÍÛÕ. Íåïîñðåäñòâåííî ïåðåä çàïèñüþ ôàéëà. (âûäàåò ìåññåäæáîêñû ñ îøèáêàìè)
bool check_DATE_TIME_ADRESS(wchar_t* Date, wchar_t* Time, wchar_t* Adress, wchar_t* Title) {

    SYSTEMTIME st;
    GetLocalTime(&st);

    int CURyear = st.wYear;
    int CURmonth = st.wMonth;
    int CURday = st.wDay;

    int CURhour = st.wHour;
    int CURminute = st.wMinute;
    int CURsecond = st.wSecond;


    wstring s_date = Date;
    int d = -1, m = -1, y = -1;
    wchar_t ch_date;
    std::_stscanf(s_date.c_str(), _T("%d%c%d%c%d"), &d, &ch_date, &m, &ch_date, &y);


    wstring s_time = Time;
    int hour = -1, min = -1, sec = -1;
    wchar_t ch_time;
    std::_stscanf(s_time.c_str(), _T("%d%c%d%c%d"), &hour, &ch_time, &min, &ch_time, &sec);


    if (Adress[0] == NULL) {
        error_msgbox(L"Choose the file");
        return false;
    }

    if (Title[0] == NULL) {
        error_msgbox(L"Enter the title for the task");
        return false;
    }

    if (valid_NOW_DATETIME(y, m, d, hour, min, sec, CURyear, CURmonth, CURday, CURhour, CURminute, CURsecond)){
        return true;
    }
    else {
        error_msgbox(L"Invalid date or time");
        return false;
    }
    return false;
}

//check_dt_for_launch - Ïðîâåðêà äàòû è âðåìÿ ÄËß ÇÀÏÓÑÊÀ. Òîåñòü íå ïðè íàæàòèè êíîïêè "Create task" à ïðè ñàìîé ðàáîòå ïðèëîæåíèÿ. (ÍÅ âûäàåò ìåññåäæáîêñû)
//Èñïîëüçóåòñÿ toTXT_REWRITE
bool check_dt_for_launch(int y, int m, int d, int hour, int min, int sec) {

    SYSTEMTIME st;
    GetLocalTime(&st);

    int CURyear = st.wYear;
    int CURmonth = st.wMonth;
    int CURday = st.wDay;

    int CURhour = st.wHour;
    int CURminute = st.wMinute;
    int CURsecond = st.wSecond;

    if (valid_NOW_DATETIME(y, m, d, hour, min, sec, CURyear, CURmonth, CURday, CURhour, CURminute, CURsecond)) {
        return true;
    }
}

// ReadTXT - ×ÒÅÍÈÅ TXT. Îáû÷íîå ÷òåíèå TXT áåç ïðîâåðîê â âåêòîð.
int ReadTXT(vector<Time_And_Path>& arr) {
    wstring h, sec, min, d, m, y;
    wstring p, title;

    wfstream file(ADRESS_TXT);
    file.imbue(std::locale(file.getloc(),
        new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::consume_header>));

    int index = 0;
    if (file.is_open())
    {
        while (getline(file, d, L'.')) {

            getline(file, m, L'.');
            getline(file, y, SEPARATORchar);

            getline(file, h, L':');
            getline(file, min, L':');
            getline(file, sec, SEPARATORchar);

            getline(file, p, SEPARATORchar);

            getline(file, title, L'\n');


            arr[index].set_time(h, sec, min, d, m, y);
            arr[index].set_path(p);
            arr[index].set_title(title);
            index++;

        }

        file.close();
        return index;

    }

}

// StringCountTXT - ÏÎÄÑ×ÅÒ ÑÒÐÎÊ ÔÀÉËÀ äëÿ èíäåêñà.
int StringCountTXT() {
    //try {
    wfstream file(ADRESS_TXT);
    file.imbue(std::locale(file.getloc(),
        new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::consume_header>));
    wstring currentLine;
    int counter = 0;
    while (getline(file, currentLine))//÷èòàåì ïîêà ÷òåíèå èç ôàéëà ïî ñòðîêàì âîçìîæíî
    {
        counter++;
    }
    file.close();//"çàêðûâàåì " ôàéë
    return counter;
    // }
    // catch(int a){
         //error_msgbox(L"bru");
   //  }
}

// LaunchTimer - ÇÀÏÓÑÊ ÒÀÉÌÅÐÀ. Ïàðàìåòð - âðåìÿ çàäåðæêè, åå ðàñ÷åò â àïäåéòå.û
void LaunchTimer(long TSleep, HWND MainHandle) {
    UINT uResult = SetTimer(MainHandle,
        1337,
        TSleep,
        (TIMERPROC)NULL);
}

// ThreadSleep_Update - ïîëó÷åíèå ÂÐÅÌÅÍÈ ÄÎ áëèæàéøåãî çàäàíèÿ (â ìèëèñåêóíäàõ)
int ThreadSleep_Update(HWND MainHandle) {
    int N = StringCountTXT();
    vector<Time_And_Path> MyArr(N);
    int index = ReadTXT(MyArr);

    SYSTEMTIME st;
    GetLocalTime(&st);

    for (int i = 0; i < MyArr.size(); i++) {

        COleDateTime  dt(MyArr[i].get_year(), MyArr[i].get_month(), MyArr[i].get_day(), MyArr[i].get_hour(), MyArr[i].get_minute(), MyArr[i].get_second());

        COleDateTime timeNow;
        timeNow = COleDateTime::GetCurrentTime();

        COleDateTimeSpan ts = dt - timeNow;

        MyArr[i].set_ThreadSleep(1000 * ts.GetTotalSeconds());


    }


    for (int i = 0; i < MyArr.size(); i++) {
   
            bool check = check_dt_for_launch(MyArr[i].get_year(), MyArr[i].get_month(), MyArr[i].get_day(), MyArr[i].get_hour(), MyArr[i].get_minute(), MyArr[i].get_second());
            if (check == false) {

                //int_del[i] = i;
                MyArr.erase(MyArr.begin() + i);

                i--;

                if (MyArr.empty()) {
                    break;
                    //return 0;
                }

                if (i == -1) {
                    break;
                    //return 0;
                }


            }

            if (MyArr.empty()) {
                break;

            }
    }


    long max = MyArr[0].get_ThreadSleep();
    long min = MyArr[0].get_ThreadSleep();

    int min_index = 0;

    for (int i = 1; i < MyArr.size(); i++)
    {
        if (max < MyArr[i].get_ThreadSleep()) max = MyArr[i].get_ThreadSleep();

        if (min > MyArr[i].get_ThreadSleep()) {
            min = MyArr[i].get_ThreadSleep();
            min_index = i;
        }

    }

    //MyArr[0].ThreadSleep = min;
    return min;

}

int GetMinTime_Update(HWND MainHandle, vector<Time_And_Path>& MyArr) {


    SYSTEMTIME st;
    GetLocalTime(&st);

    for (int i = 0; i < MyArr.size(); i++) {

        COleDateTime  dt(MyArr[i].get_year(), MyArr[i].get_month(), MyArr[i].get_day(), MyArr[i].get_hour(), MyArr[i].get_minute(), MyArr[i].get_second());

        COleDateTime timeNow;
        timeNow = COleDateTime::GetCurrentTime();

        COleDateTimeSpan ts = dt - timeNow;

        MyArr[i].set_ThreadSleep(1000 * ts.GetTotalSeconds());


    }

    long max = MyArr[0].get_ThreadSleep();
    long min = MyArr[0].get_ThreadSleep();

    int min_index = 0;

    for (int i = 1; i < MyArr.size(); i++)
    {
        if (max < MyArr[i].get_ThreadSleep()) max = MyArr[i].get_ThreadSleep();

        if (min > MyArr[i].get_ThreadSleep()) {
            min = MyArr[i].get_ThreadSleep();
            min_index = i;
        }

    }



    return min_index;

}

// toTXT_REWRITE - ÓÄÀËÅÍÈÅ ÇÀÏÓÙÅÍÍÛÕ ÇÀÄÀ× ÈÇ TXT èëè ïåðåçàïèñü txt ñ ïðîâåðêîé íà äàòû 
//(íóæíî äëÿ àïäåéòà ïîñëå çàïóñêà ïðèëîæåíèé ò.ê. âðåìÿ óæå ïðîøëîå è íóæíî óäàëÿòü èç ñïèñêà)
bool toTXT_REWRITE() {
    int N = StringCountTXT();
    vector<Time_And_Path> MyArr(N);

    int index = ReadTXT(MyArr);

    for (int i = 0; i < MyArr.size(); i++) {

        bool check = check_dt_for_launch(MyArr[i].get_year(), MyArr[i].get_month(), MyArr[i].get_day(), MyArr[i].get_hour(), MyArr[i].get_minute(), MyArr[i].get_second());
        if (check == false) {

            MyArr.erase(MyArr.begin() + i);

            i--;

        }
    }


    //çàïèñü â txt
    wfstream file;
    file.imbue(std::locale(file.getloc(),
        new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::consume_header>));

    file.open(ADRESS_TXT, std::ios::out | std::ios::trunc);



    if (file.is_open())
    {
        for (int i = 0; i < MyArr.size(); i++) {
            file << MyArr[i].get_day() << '.' << MyArr[i].get_month() << '.' << MyArr[i].get_year() << SEPARATOR << MyArr[i].get_hour() << ':' << MyArr[i].get_minute() << ':' << MyArr[i].get_second()
                << SEPARATOR << MyArr[i].get_path() << SEPARATOR << MyArr[i].get_title() << L"\n";

        }
    }
    file.close();

    if (MyArr.empty()) {
        return false;

    }

    return true;
}

bool toTXT_AFTER_DELETE(vector<Time_And_Path>& MyArr) {



    //çàïèñü â txt
    wfstream file;
    file.imbue(std::locale(file.getloc(),
        new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::consume_header>));

    file.open(ADRESS_TXT, std::ios::out | std::ios::trunc);



    if (file.is_open())
    {
        for (int i = 0; i < MyArr.size(); i++) {
            file << MyArr[i].get_day() << '.' << MyArr[i].get_month() << '.' << MyArr[i].get_year() << SEPARATOR << MyArr[i].get_hour() << ':' << MyArr[i].get_minute() << ':' << MyArr[i].get_second()
                << SEPARATOR << MyArr[i].get_path() << SEPARATOR << MyArr[i].get_title() << L"\n";

        }
    }
    file.close();

    if (MyArr.empty()) {
        return false;

    }

    return true;
}

//Óñòàíîâèòü ëèñò áîêñ
void SetListBox(HWND MainHandle, HWND listbox, HWND label) {
    int N = StringCountTXT();
    vector<Time_And_Path> MyArr(N);
    int index = ReadTXT(MyArr);

    for (int i = 0; i < MyArr.size(); i++)
    {
        //error_msgbox(MyArr[i].title.c_str());
        int pos = (int)SendMessage(listbox, LB_ADDSTRING, 0, (LPARAM)MyArr[i].get_title().c_str());
        SendMessage(listbox, LB_SETITEMDATA, pos, (LPARAM)i);
        //SendMessage(listbox, LB_SETITEMDATA, pos, (LPARAM)i);
    }
}


//Óäàëèòü ýëåìåíò ëèñò áîêñà ÏÎ ÈÍÄÅÊÑÓ
void DeleteItem_BY_INDEX(vector<Time_And_Path>& arr, int index) {
    arr.erase(arr.begin() + index);
    toTXT_AFTER_DELETE(arr);
}

void LauchTask(HWND hwnd, HWND hWnd, HWND hLabelmain, HWND hListboxMAIN) {
    if (toTXT_REWRITE()) {
        KillTimer(hwnd, 1337);
        int thread = ThreadSleep_Update(hWnd);
        LaunchTimer(thread, hwnd);
        SetWindowText(hLabelmain, L"");
        SendMessage(hListboxMAIN, LB_RESETCONTENT, 0, 0);
        SetListBox(hwnd, hListboxMAIN, hLabelmain);
    }
    else {
        SetWindowText(hLabelmain, L"");
        error_msgbox(L"All tasks completed");
    }
}
