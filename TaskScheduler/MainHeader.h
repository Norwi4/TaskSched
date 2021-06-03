#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma warning(disable: 4996)
#include <Windows.h>
#include <string>
#include <codecvt>
#include "commctrl.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include "ATLComTime.h"








#include <algorithm>
#include "ShellAPI.h"
#include <iostream>
#include <sstream>

#include <locale>

#include <tchar.h>

#include <cstdio>

#include <sstream>
 

#include < stdio.h >
#include < stdlib.h >

#include <time.h>
#include "strsafe.h"
#include <iterator>


//дефайн адресса TXTишника
#define ADRESS_TXT L"C:\\Users\\abaev\\OneDrive\\Desktop\\data.txt"

//дефайны сепаратора для раздела в txt даты, времени и адресса файла
#define SEPARATOR L"/"
#define SEPARATORchar L'/'

using namespace std;