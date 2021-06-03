#pragma once
#include "MainHeader.h"
#include "ClassHeader.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// 
// 
// 



////////////////////////////////////////////////////////////////////////////////
//ФУНКЦИИ:



//toTXT - ЗАПИСЬ В TXT ВВЕДЕНЫХ ПОЛЬЗОВАТЕЛЕМ ДАННЫХ!!!
void toTXT(wchar_t* Adress, wchar_t* Date, wchar_t* Time, wchar_t* Title);

//valid_date - Для проверки даты при введении. СОКРАЩАЕТ КОД
bool valid_date(int _Year, int _Month, int _DayNo);

//valid_time - Для проверки времени при введении. СОКРАЩАЕТ КОД
bool valid_time(int _Hour, int _Minute, int _Second);

//error_msgbox - меседж бокс с данными которые нужно вывести в параметре. ДЛЯ ТЕСТИРОВАНИЯ
void error_msgbox(const wchar_t* Date);

//valid_NOW_date - Проверка даты. используется в других функциях. ПРОСТО СОКРАЩАЕТ КОД
bool valid_NOW_date(int y, int m, int d);

//check_DATE_TIME_ADRESS - ПРОВЕРКА ВВЕДЕННЫХ ЮЗЕРОМ ДАННЫХ. Непосредственно перед записью файла. (выдает месседжбоксы с ошибками)
bool check_DATE_TIME_ADRESS(wchar_t* Date, wchar_t* Time, wchar_t* Adress, wchar_t* Title);

//check_dt_for_launch - Проверка даты и время ДЛЯ ЗАПУСКА. Тоесть не при нажатии кнопки "Create task" а при самой работе приложения. (НЕ выдает месседжбоксы)
//Используется toTXT_REWRITE
bool check_dt_for_launch(int y, int m, int d, int hour, int min, int sec);

// ReadTXT - ЧТЕНИЕ TXT. Обычное чтение TXT без проверок в вектор.
int ReadTXT(vector<Time_And_Path>& arr);

// StringCountTXT - ПОДСЧЕТ СТРОК ФАЙЛА для индекса.
int StringCountTXT();

// LaunchTimer - ЗАПУСК ТАЙМЕРА. Параметр - время задержки, ее расчет в апдейте.
void LaunchTimer(long TSleep, HWND MainHandle);

// ThreadSleep_Update - получение ВРЕМЕНИ ДО ближайшего задания (в милисекундах)
int ThreadSleep_Update(HWND MainHandle);

// GetMinTime_Update - получение ИНДЕКСА ближайшего задания
int GetMinTime_Update(HWND MainHandle, vector<Time_And_Path>& MyArr);

// toTXT_REWRITE - УДАЛЕНИЕ ЗАПУЩЕННЫХ ЗАДАЧ ИЗ TXT или перезапись txt с проверкой на даты 
//(нужно для апдейта после запуска приложений т.к. время уже прошлое и нужно удалять из списка)
bool toTXT_REWRITE();

bool toTXT_AFTER_DELETE(vector<Time_And_Path>& MyArr);

//Установить лист бокс
void SetListBox(HWND MainHandle, HWND listbox, HWND label);

//Получить лист бокс
/*
void GetListBox(HWND MainHandle, HWND listbox, HWND label);
*/

//Удалить элемент лист бокса ПО ИНДЕКСУ
void DeleteItem_BY_INDEX(vector<Time_And_Path>& arr, int index);


//void CheckForTask();

void LauchTask(HWND hwnd, HWND hWnd, HWND hLabelmain, HWND hListboxMAIN);