#include "MainHeader.h"
#include "ClassHeader.h"
#include "FuncHeader.h"

//#include "Functions.cpp"

#define GetStockFont(ANSI_FIXED_FONT) ((HFONT)GetStockObject(ANSI_FIXED_FONT))
#define SelectFont(hdc, hfont) \ ((HFONT)SelectObject((hdc), (HGDIOBJ)(HFONT)(hfont)))

//AddWindow - Ñîçäàíèå äî÷åðíåãî îêíà
static pair<bool, HWND> AddWindow(const wstring&& winClass, const wstring&& title, HWND hParentWnd, const WNDPROC callback)
{
    UnregisterClass(winClass.c_str(), GetModuleHandle(nullptr));
    WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; // Ýòà ñòðóêòóðà îòâå÷àåò çà íåêèå õ-êè îêíà (â ôèãóðíûõ ñêîáêàõ ðàçìåðû).Èñï. àãðåãàòíàÿ èíèöèàëèçàöèÿ.
    HWND hWindow{};
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    wc.lpfnWndProc = callback;
    wc.lpszClassName = winClass.c_str();
    wc.style = CS_VREDRAW | CS_HREDRAW;

    const auto create_window = [&hWindow, &winClass, &title, &hParentWnd]() -> pair<bool, HWND> {
        if (hWindow = CreateWindow(winClass.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, 100, 100, 600, 270, hParentWnd, nullptr, nullptr, nullptr); !hWindow)
            return { false,nullptr };
        ShowWindow(hWindow, SW_SHOWDEFAULT); // ïîêàç îêíà
        UpdateWindow(hWindow);
        return { true,hWindow };
    };

    if (!RegisterClassEx(&wc))
        return create_window();

    return create_window();
}


//------------------------------------------------------------------------------------------------
//Создание главного окна
int CALLBACK  wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
    static MSG msg{};                             
    static HWND hwnd{}, hChildWnd{}, hChildWnd_EDIT{}, hEditMAIN1{}, hListboxMAIN{}, hLabelmain{}, hChildDatePick{}, hChildTimePick{}, hChildEdit1{}, hChildEdit2{}, hChildEditName{}, hChildButton2{}, hChildButton1{}, hChildLabel1{}, hChildLabel_EDIT1{}, hChildLabel_EDIT2{}, hChildLabelName{};
    WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; 
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hInstance = hInstance;
   
    wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        
        switch (uMsg)
        {
            //Ñîçäàíèå êîíòðîëîâ íà ðîäèòåëüñêîì îêíå
            case WM_CREATE:
            {

                HWND hListbox = CreateWindow(
                    L"LISTBOX", NULL,
                    WS_CHILD | WS_VISIBLE | LBS_STANDARD |
                    LBS_WANTKEYBOARDINPUT,
                    30, 30, 200, 210,
                    hWnd, reinterpret_cast<HMENU>(5051), nullptr, nullptr
                );
                hListboxMAIN = hListbox;

                HWND hLabelSTATICmain = CreateWindow(
                    L"static",
                    L"",
                    WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                    240, 30, 200, 200,
                    hWnd, reinterpret_cast<HMENU>(1234), nullptr, nullptr
                );
                hLabelmain = hLabelSTATICmain;

                HWND hButtonCHANGE = CreateWindow(
                    L"BUTTON",
                    L"Изменит задачу",
                    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                    240, 250, 200, 40, hWnd, reinterpret_cast<HMENU>(2222), nullptr, nullptr
                );

                HWND hButtonDELETE = CreateWindow(
                    L"BUTTON",
                    L"Удалить задачу",
                    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                    240, 300, 200, 40, hWnd, reinterpret_cast<HMENU>(3333), nullptr, nullptr
                );

                HWND hButton = CreateWindow(
                    L"BUTTON",
                    L"Создать задачу",
                    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                    30, 250, 200, 90, hWnd, reinterpret_cast<HMENU>(10), nullptr, nullptr
                );


                

                HFONT hFont1 = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Segoe UI"));
                SendMessage(hListbox, WM_SETFONT, (WPARAM)hFont1, NULL);
                SendMessage(hLabelSTATICmain, WM_SETFONT, (WPARAM)hFont1, NULL);
                SendMessage(hButtonCHANGE, WM_SETFONT, (WPARAM)hFont1, NULL);
                SendMessage(hButtonDELETE, WM_SETFONT, (WPARAM)hFont1, NULL);
                SendMessage(hButton, WM_SETFONT, (WPARAM)hFont1, NULL);

                //LauchTask(hwnd, hWnd, hLabelmain, hListboxMAIN);
                if (toTXT_REWRITE()) {
                    //KillTimer(hwnd, 1337);
                    int thread = ThreadSleep_Update(hWnd);
                    LaunchTimer(thread, hWnd);

                    //error_msgbox(to_wstring(thread).c_str());

                    SetWindowText(hLabelmain, L"");
                    SendMessage(hListboxMAIN, LB_RESETCONTENT, 0, 0);
                    SetListBox(hwnd, hListboxMAIN, hLabelmain);
                }

            }
            return 0;


            //Ñðàáàòûâàíèå òàéìåðà
            case WM_TIMER:
                {
                    //error_msgbox(L"nig moment");
                    KillTimer(hwnd, 1337);
      
                    int N = StringCountTXT();
                    vector<Time_And_Path> MyArr(N);
                    int index = ReadTXT(MyArr);
                    int min_index = GetMinTime_Update(hWnd, MyArr);

                    wstring buff;

                    for (int i = 0; i < MyArr.size(); i++)
                    {
                        int t = MyArr[i].get_ThreadSleep();

                        if (t == 0)
                        {
                            buff = MyArr[i].get_path();
                            ShellExecute(0, L"open", buff.c_str(), NULL, NULL, SW_SHOWNORMAL);
                            DeleteItem_BY_INDEX(MyArr,i);
                        }
                        
                    }
                    SendMessage(hListboxMAIN, LB_RESETCONTENT, 0, 0);
                    SetListBox(hwnd, hListboxMAIN, hLabelmain);
                    SetWindowText(hLabelmain, L"");
                    
                    if (toTXT_REWRITE()) {
                        
                        int thread = ThreadSleep_Update(hWnd);
                        LaunchTimer(thread, hwnd);
                    }
                    else {
                        error_msgbox(L"Все задачи выполнены");
                    }
                    

                    
                    
                    //SendMessage(hListboxMAIN, LB_RESETCONTENT, 0, 0);
                    //LauchTask(hwnd, hWnd, hLabelmain, hListboxMAIN);
                }
            return 0;

            //Îáðàáîòêà íàæàòèÿ êîíòðîëëîâ ãëàâíîãî îêíà
            case WM_COMMAND:
            {
                switch (LOWORD(wParam))
                {
                    /////////////////// ÊÅÉÑ ÎÊÍÀ ÑÎÇÄÀÍÈß ÇÀÄÀ×È!!!!!!!! ÂÀÆÍÎ!
                    case 10: 
                    {
                        EnableWindow(hwnd, FALSE);
                        if (hChildWnd) {
                            DestroyWindow(hChildWnd);
                        }
                            
                        const auto [flag, hChild] = AddWindow(L"TaskWindow", L"Создание здачи", hWnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
                            switch (uMsg) {

                                //ÊÎÍÒÐÎËÛ ÄÎ×ÅÐÍÅÃÎ ÎÊÍÀ
                                case WM_CREATE:
                                {
                                    HWND hLabelEDIT1 = CreateWindow(
                                        L"static",
                                        L"Дата:",
                                        WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                        30, 10, 45, 25,
                                        hWnd, reinterpret_cast<HMENU>(9), nullptr, nullptr
                                    );
                                    hChildLabel_EDIT1 = hLabelEDIT1;
                                    //SetWindowText(hChildLabel_EDIT1, L"");
                                   
                                    HWND DatePicker = CreateWindowEx(
                                        0,
                                        DATETIMEPICK_CLASS,
                                        L"GUI_TIMER2_LABEL",
                                        (WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT),
                                        80, 10, 150, 25,
                                        hWnd,
                                        reinterpret_cast<HMENU>(22888),
                                        NULL,
                                        NULL);
                                    hChildDatePick = DatePicker;
                                    
                                    HWND hLabelEDIT2 = CreateWindow(
                                        L"static",
                                        L"Время:",
                                        WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                        30, 45, 45, 25,
                                        hWnd, reinterpret_cast<HMENU>(99), nullptr, nullptr
                                    );
                                    hChildLabel_EDIT2 = hLabelEDIT2;
                                    //SetWindowText(hChildLabel_EDIT2, L"Time:");
                                    
                                    HWND TimePicker = CreateWindowEx(
                                        0,
                                        DATETIMEPICK_CLASS,
                                        L"GUI_TIMER2_LABEL",
                                        (WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT),
                                        80, 45, 150, 25,
                                        hWnd,
                                        reinterpret_cast<HMENU>(228882),
                                        NULL,
                                        NULL);
                                    hChildTimePick = TimePicker;


                                    /////////////////// Êíîïêà è ëåéáë äëÿ ÂÛÁÎÐÀ ÔÀÉËÀ
                                    HWND hButtonCHOOSE = CreateWindow(
                                        L"BUTTON",
                                        L"Выбрать файл",
                                        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                        30, 80, 200, 40, hWnd, reinterpret_cast<HMENU>(1011), nullptr, nullptr
                                    );
                                    hChildButton2 = hButtonCHOOSE;

                                    HWND hLabelCHOOSE = CreateWindow(
                                        L"static",
                                        L"",
                                        WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                        240, 80, 350, 120,
                                        hWnd, reinterpret_cast<HMENU>(10111), nullptr, nullptr
                                    );
                                    hChildLabel1 = hLabelCHOOSE;
                                   //SetWindowText(hChildLabel1, L"");





                                    /////////////////// Ëåéáë è ýäèò äëÿ ÍÀÇÂÀÍÈß
                                    HWND hEditName = CreateWindow(
                                        L"EDIT",
                                        L"",
                                        WS_CHILD | WS_BORDER | WS_VISIBLE,
                                        80, 130, 150, 25, hWnd, reinterpret_cast<HMENU>(1100), nullptr, nullptr
                                    );
                                    hChildEditName = hEditName;

                                    HWND hLabelName = CreateWindow(
                                        L"static",
                                        L"Имя:",
                                        WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                        30, 130, 45, 25,
                                        hWnd, reinterpret_cast<HMENU>(9999), nullptr, nullptr
                                    );
                                    hChildLabelName = hLabelName;
                                    //SetWindowText(hChildLabelName, L"Title:");





                                    /////////////////// Êíîïêà äëÿ çàïèñè è ïðîâåðêè ðåçóëüòàòà è çàêðûòèÿ îêíà çàäà÷è
                                    HWND hButtonOK = CreateWindow(
                                        L"BUTTON",
                                        L"OK",
                                        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                        30, 165, 200, 40, hWnd, reinterpret_cast<HMENU>(1010), nullptr, nullptr
                                    );
                                    hChildButton1 = hButtonOK;




                                    HFONT hFont1 = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Segoe UI"));
                                    

                                    //SendMessage(TimePicker, WM_SETFONT, (WPARAM)hFont1, NULL);
                                    SendMessage(hLabelEDIT1, WM_SETFONT, (WPARAM)hFont1, NULL);
                                    SendMessage(DatePicker, WM_SETFONT, (WPARAM)hFont1, NULL);
                                    SendMessage(hLabelEDIT2, WM_SETFONT, (WPARAM)hFont1, NULL);
                                    SendMessage(TimePicker, WM_SETFONT, (WPARAM)hFont1, NULL);
                                    SendMessage(hButtonCHOOSE, WM_SETFONT, (WPARAM)hFont1, NULL);
                                    SendMessage(hLabelCHOOSE, WM_SETFONT, (WPARAM)hFont1, NULL);
                                    SendMessage(hEditName, WM_SETFONT, (WPARAM)hFont1, NULL);
                                    SendMessage(hLabelName, WM_SETFONT, (WPARAM)hFont1, NULL);
                                    SendMessage(hButtonOK, WM_SETFONT, (WPARAM)hFont1, NULL);
                                }
                                return 0;

                                case WM_CTLCOLORSTATIC:
                                {
                                    RedrawWindow(hChildLabel1, NULL, NULL, RDW_ERASE);
                                    SetBkMode((HDC)wParam, RGB(255, 255, 255));
                                    return (LONG)GetStockObject(RGB(255, 255, 255));
                                }

                                //ËÎÂËß ÊÎÍÒÐÎËÎÂ. ââîä äàòû âðåìåíè àäðåññà ïîëüçîâàòåëåì
                                case WM_COMMAND:
                                {
                                    
                                    switch (LOWORD(wParam))
                                    {
 
                                        /////////////////// Êåéñ äëÿ êíîïêè âûáîðà ôàéëà (ïóòü â ofn.lpstrFile)
                                        case 1011:
                                        {
                                            //SetWindowText(hChildLabel1, NULL);
                                            //RedrawWindow(hChildLabel1, NULL, NULL, RDW_INVALIDATE);
                                            LPWSTR filebuff = new wchar_t[256];
                                            OPENFILENAME open = { 0 };
                                            open.lStructSize = sizeof(OPENFILENAME);
                                            open.hwndOwner = hWnd; //Handle to the parent window
                                            //open.lpstrFilter = "Image Files(.jpg|.png|.bmp|.jpeg)\0*.jpg;*.png;*.bmp;*.jpeg\0\0";
                                            open.lpstrCustomFilter = NULL;
                                            open.lpstrFile = filebuff;
                                            open.lpstrFile[0] = '\0';
                                            open.nMaxFile = 256;
                                            open.nFilterIndex = 1;
                                            open.lpstrInitialDir = NULL;
                                            open.lpstrTitle = L"Select a File\0";
                                            open.nMaxFileTitle = strlen("Select a file\0");
                                            open.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
                                            GetOpenFileName(&open);

                                            
                                            //error_msgbox(L"ag");
                                            SetWindowText(hChildLabel1, open.lpstrFile);
    
                                        }
                                        return 0;



                                        /////////////////// Êåéñ äëÿ êíîïêè ÎÊ
                                        case 1010:
                                        {


                                            wchar_t buffADRESS[1000];
                                            buffADRESS[0] = NULL;
                                            SendMessage(GetDlgItem(hWnd, 10111), WM_GETTEXT, 1000, (LPARAM)buffADRESS);

                                            wchar_t buffDATE[15];
                                            SendMessage(GetDlgItem(hWnd, 22888), WM_GETTEXT, 15, (LPARAM)buffDATE);

                                            wchar_t buffTIME[15];
                                            SendMessage(GetDlgItem(hWnd, 228882), WM_GETTEXT, 15, (LPARAM)buffTIME);

                                            wchar_t buffNAME[255];
                                            SendMessage(GetDlgItem(hWnd, 1100), WM_GETTEXT, 255, (LPARAM)buffNAME);


                                            if (check_DATE_TIME_ADRESS(buffDATE, buffTIME, buffADRESS, buffNAME)) {
                                                toTXT(buffADRESS, buffDATE, buffTIME, buffNAME);
                                                
                                            

                                                LauchTask(hwnd, hWnd, hLabelmain, hListboxMAIN);

                                                SendMessage(hChildWnd, WM_CLOSE, 0, 0);
                                                EnableWindow(hwnd, TRUE);
                                                ShowWindow(hChildWnd, SW_PARENTCLOSING); 
                                                

                                            }

                                            

                                                
                                        }
                                        break;
                                        
                                    }
                                }
                                return 0;

                                case WM_DESTROY:
                                {

                                    EnableWindow(hwnd, TRUE);
                                }
                                return 0;
                            }
                            
                            return DefWindowProc(hWnd, uMsg, wParam, lParam);
                        });
                        hChildWnd = hChild;
                        
                    }
                    
                    break;
                    

                    
                    case 5051:
                    {
                        switch (HIWORD(wParam))
                        {
                            case LBN_SELCHANGE:
                            {
                                try {
                                    SetWindowText(hLabelmain, L"");
                                    int N = StringCountTXT();
                                    vector<Time_And_Path> MyArr(N);
                                    int index = ReadTXT(MyArr);


                                    int lbItem = (int)SendMessage(hListboxMAIN, LB_GETCURSEL, 0, 0);

                                    // Get item data.
                                    int i = (int)SendMessage(hListboxMAIN, LB_GETITEMDATA, lbItem, 0);

                                    if (i < MyArr.size()) {
                                        wstring buff = L"Дата: " + to_wstring(MyArr[i].get_day()) + L"." + to_wstring(MyArr[i].get_month()) + L"." + to_wstring(MyArr[i].get_year()) +
                                            L"\nВремя: " + to_wstring(MyArr[i].get_hour()) + L":" + to_wstring(MyArr[i].get_minute()) + L":" + to_wstring(MyArr[i].get_second()) +
                                            L"\nПуть: " + MyArr[i].get_path();



                                        SetWindowText(hLabelmain, buff.c_str());
                                    }
                                    
                                    return TRUE;
                                }
                                catch (int e) {

                                }
                                
                            }
                        }
                    }
                    return TRUE;


                    //Óäàëåíèå çàäà÷è
                    case 3333:
                    {
                        int N = StringCountTXT();
                        vector<Time_And_Path> MyArr(N);
                        int index = ReadTXT(MyArr);

                        int lbItem = (int)SendMessage(hListboxMAIN, LB_GETCURSEL, 0, 0);

                        // Get item data.
                        int i = (int)SendMessage(hListboxMAIN, LB_GETITEMDATA, lbItem, 0);

                        if (i < MyArr.size()) {
                            DeleteItem_BY_INDEX(MyArr, i);
                            SetWindowText(hLabelmain, L"");
                            SendMessage(hListboxMAIN, LB_RESETCONTENT, 0, 0);
                            SetListBox(hwnd, hListboxMAIN, hLabelmain);

                        }
                        LauchTask(hwnd, hWnd, hLabelmain, hListboxMAIN);

                    }
                    break;
                    

                    //ÅÙÅ ÎÄÍÎ ÄÎ×ÅÐÍÅÅÅÅ!!!! ÄËß ÈÇÌÅÍÅÍÈß ÇÀÄÀ×È
                    case 2222:
                    {
                        int N1 = StringCountTXT();
                        vector<Time_And_Path> MyArr1(N1);
                        int index1 = ReadTXT(MyArr1);

                        int lbItem1 = (int)SendMessage(hListboxMAIN, LB_GETCURSEL, 0, 0);

                        // Get item data.
                        int i1 = (int)SendMessage(hListboxMAIN, LB_GETITEMDATA, lbItem1, 0);

                        if (i1 > MyArr1.size()) {
                            return 0;
                        }
                        else {
                        

                            EnableWindow(hwnd, FALSE);
                            if (hChildWnd) {

                                DestroyWindow(hChildWnd);
                                //error_msgbox(L"lol");
                            }
                            const auto [flag, hChild] = AddWindow(L"TaskWindow", L"Create Task", hWnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
                                switch (uMsg) {

                                        //ÊÎÍÒÐÎËÛ ÄÎ×ÅÐÍÅÃÎ ÎÊÍÀ
                                    case WM_CREATE:
                                    {
                                        int N = StringCountTXT();
                                        vector<Time_And_Path> MyArr(N);
                                        int index = ReadTXT(MyArr);

                                        int lbItem = (int)SendMessage(hListboxMAIN, LB_GETCURSEL, 0, 0);

                                        // Get item data.
                                        int i = (int)SendMessage(hListboxMAIN, LB_GETITEMDATA, lbItem, 0);

                                
                                       
                                        HWND hLabelEDIT1 = CreateWindow(
                                            L"static",
                                            L"Дата:",
                                            WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                            30, 10, 45, 25,
                                            hWnd, reinterpret_cast<HMENU>(9), nullptr, nullptr
                                        );
                                        hChildLabel_EDIT1 = hLabelEDIT1;
                                        //SetWindowText(hChildLabel_EDIT1, L"");

                                        HWND DatePicker = CreateWindowEx(
                                            0,
                                            DATETIMEPICK_CLASS,
                                            L"GUI_TIMER2_LABEL",
                                            (WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT),
                                            80, 10, 150, 25,
                                            hWnd,
                                            reinterpret_cast<HMENU>(22888),
                                            NULL,
                                            NULL);
                                        hChildDatePick = DatePicker;

                                        HWND hLabelEDIT2 = CreateWindow(
                                            L"static",
                                            L"Время:",
                                            WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                            30, 45, 45, 25,
                                            hWnd, reinterpret_cast<HMENU>(99), nullptr, nullptr
                                        );
                                        hChildLabel_EDIT2 = hLabelEDIT2;
                                        //SetWindowText(hChildLabel_EDIT2, L"Time:");

                                        HWND TimePicker = CreateWindowEx(
                                            0,
                                            DATETIMEPICK_CLASS,
                                            L"GUI_TIMER2_LABEL",
                                            (WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT),
                                            80, 45, 150, 25,
                                            hWnd,
                                            reinterpret_cast<HMENU>(228882),
                                            NULL,
                                            NULL);
                                        hChildTimePick = TimePicker;


                                        /////////////////// Êíîïêà è ëåéáë äëÿ ÂÛÁÎÐÀ ÔÀÉËÀ
                                        HWND hButtonCHOOSE = CreateWindow(
                                            L"BUTTON",
                                            L"Выбрать файл",
                                            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                            30, 80, 200, 40, hWnd, reinterpret_cast<HMENU>(1011), nullptr, nullptr
                                        );
                                        hChildButton2 = hButtonCHOOSE;

                                        HWND hLabelCHOOSE = CreateWindow(
                                            L"static",
                                            L"",
                                            WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                            240, 80, 350, 120,
                                            hWnd, reinterpret_cast<HMENU>(10111), nullptr, nullptr
                                        );
                                        hChildLabel1 = hLabelCHOOSE;
                                        //SetWindowText(hChildLabel1, L"");





                                         /////////////////// Ëåéáë è ýäèò äëÿ ÍÀÇÂÀÍÈß
                                        HWND hEditName = CreateWindow(
                                            L"EDIT",
                                            L"",
                                            WS_CHILD | WS_BORDER | WS_VISIBLE,
                                            80, 130, 150, 25, hWnd, reinterpret_cast<HMENU>(1100), nullptr, nullptr
                                        );
                                        hChildEditName = hEditName;

                                        HWND hLabelName = CreateWindow(
                                            L"static",
                                            L"Имя:",
                                            WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                            30, 130, 45, 25,
                                            hWnd, reinterpret_cast<HMENU>(9999), nullptr, nullptr
                                        );
                                        hChildLabelName = hLabelName;
                                        //SetWindowText(hChildLabelName, L"Title:");





                                        /////////////////// Êíîïêà äëÿ çàïèñè è ïðîâåðêè ðåçóëüòàòà è çàêðûòèÿ îêíà çàäà÷è
                                        HWND hButtonOK = CreateWindow(
                                            L"BUTTON",
                                            L"OK",
                                            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                            30, 165, 200, 40, hWnd, reinterpret_cast<HMENU>(1010), nullptr, nullptr
                                        );
                                        hChildButton1 = hButtonOK;




                                        HFONT hFont1 = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Segoe UI"));


                                        //SendMessage(TimePicker, WM_SETFONT, (WPARAM)hFont1, NULL);
                                        SendMessage(hLabelEDIT1, WM_SETFONT, (WPARAM)hFont1, NULL);
                                        SendMessage(DatePicker, WM_SETFONT, (WPARAM)hFont1, NULL);
                                        SendMessage(hLabelEDIT2, WM_SETFONT, (WPARAM)hFont1, NULL);
                                        SendMessage(TimePicker, WM_SETFONT, (WPARAM)hFont1, NULL);
                                        SendMessage(hButtonCHOOSE, WM_SETFONT, (WPARAM)hFont1, NULL);
                                        SendMessage(hLabelCHOOSE, WM_SETFONT, (WPARAM)hFont1, NULL);
                                        SendMessage(hEditName, WM_SETFONT, (WPARAM)hFont1, NULL);
                                        SendMessage(hLabelName, WM_SETFONT, (WPARAM)hFont1, NULL);
                                        SendMessage(hButtonOK, WM_SETFONT, (WPARAM)hFont1, NULL);


                               
                                        wstring buff;

                                        buff = MyArr[i].get_path();
                                        const wchar_t* buffPATH = buff.c_str();
                                        SetDlgItemText(hWnd, 10111, buffPATH);

                                        


                                        SYSTEMTIME st_date;
                                        GetLocalTime(&st_date);
                                        st_date.wYear = MyArr[i].get_year(); st_date.wMonth = MyArr[i].get_month(); st_date.wDay = MyArr[i].get_day();
                                        st_date.wHour = MyArr[i].get_hour(); st_date.wMinute = MyArr[i].get_minute(); st_date.wSecond = MyArr[i].get_second();
                                                       
                                        SendMessage(DatePicker, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st_date);

                                        SendMessage(TimePicker, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st_date);

                                        buff = MyArr[i].get_title();
                                        const wchar_t* buffTITLE = buff.c_str();
                                        SetDlgItemText(hWnd, 1100, buffTITLE);

                                    }
                                    return 0;


                                    case WM_CTLCOLORSTATIC:
                                    {
                                        RedrawWindow(hChildLabel1, NULL, NULL, RDW_ERASE);
                                        SetBkMode((HDC)wParam, RGB(255, 255, 255));
                                        return (LONG)GetStockObject(RGB(255, 255, 255));
                                    }

                                    //ËÎÂËß ÊÎÍÒÐÎËÎÂ. ââîä äàòû âðåìåíè àäðåññà ïîëüçîâàòåëåì
                                    case WM_COMMAND:
                                    {

                                        switch (LOWORD(wParam))
                                        {

                                            /////////////////// Êåéñ äëÿ êíîïêè âûáîðà ôàéëà (ïóòü â ofn.lpstrFile)
                                        case 1011:
                                        {

                                            LPWSTR filebuff = new wchar_t[256];
                                            OPENFILENAME open = { 0 };
                                            open.lStructSize = sizeof(OPENFILENAME);
                                            open.hwndOwner = hWnd; //Handle to the parent window
                                            //open.lpstrFilter = "Image Files(.jpg|.png|.bmp|.jpeg)\0*.jpg;*.png;*.bmp;*.jpeg\0\0";
                                            open.lpstrCustomFilter = NULL;
                                            open.lpstrFile = filebuff;
                                            open.lpstrFile[0] = '\0';
                                            open.nMaxFile = 256;
                                            open.nFilterIndex = 1;
                                            open.lpstrInitialDir = NULL;
                                            open.lpstrTitle = L"Select a File\0";
                                            open.nMaxFileTitle = strlen("Select a file\0");
                                            open.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
                                            GetOpenFileName(&open);

                                            SetWindowText(hChildLabel1, open.lpstrFile);



                                        }
                                        return 0;



                                        /////////////////// Êåéñ äëÿ êíîïêè ÎÊ
                                        case 1010:
                                        {
                                            int N = StringCountTXT();
                                            vector<Time_And_Path> MyArr(N);
                                            int index = ReadTXT(MyArr);

                                            int lbItem = (int)SendMessage(hListboxMAIN, LB_GETCURSEL, 0, 0);

                                            // Get item data.
                                            int i = (int)SendMessage(hListboxMAIN, LB_GETITEMDATA, lbItem, 0);

                                            wchar_t buffADRESS[1000];
                                            buffADRESS[0] = NULL;
                                            SendMessage(GetDlgItem(hWnd, 10111), WM_GETTEXT, 1000, (LPARAM)buffADRESS);

                                            wchar_t buffDATE[15];
                                            SendMessage(GetDlgItem(hWnd, 22888), WM_GETTEXT, 15, (LPARAM)buffDATE);

                                            wchar_t buffTIME[15];
                                            SendMessage(GetDlgItem(hWnd, 228882), WM_GETTEXT, 15, (LPARAM)buffTIME);

                                            wchar_t buffNAME[255];
                                            SendMessage(GetDlgItem(hWnd, 1100), WM_GETTEXT, 255, (LPARAM)buffNAME);


                                            if (check_DATE_TIME_ADRESS(buffDATE, buffTIME, buffADRESS, buffNAME)) {

                                                DeleteItem_BY_INDEX(MyArr, i);

                                                toTXT(buffADRESS, buffDATE, buffTIME, buffNAME);

                                                /*
                                                if (toTXT_REWRITE()) {
                                                    KillTimer(hwnd, 1337);
                                                    int thread = ThreadSleep_Update(hWnd);
                                                    LaunchTimer(thread, hwnd);
                                                    SetWindowText(hLabelmain, L"");
                                                    SendMessage(hListboxMAIN, LB_RESETCONTENT, 0, 0);
                                                    SetListBox(hwnd, hListboxMAIN, hLabelmain);
                                                }
                                                else {
                                                    error_msgbox(L"All tasks completed");
                                                }
                                                */

                                                LauchTask(hwnd, hWnd, hLabelmain, hListboxMAIN);
                                                SendMessage(hChildWnd_EDIT, WM_CLOSE, 0, 0);
                                                EnableWindow(hChildWnd_EDIT, TRUE);
                                                ShowWindow(hChildWnd_EDIT, SW_PARENTCLOSING); // ïîêàç îêíà

                                            }
                                            
                                        }
                                        break;
                                        }
                                    }
                                    return 0;

                                    case WM_DESTROY:
                                    {
                                        /*
                                        if (toTXT_REWRITE()) {
                                            KillTimer(hwnd, 1337);
                                            int thread = ThreadSleep_Update(hWnd);
                                            LaunchTimer(thread, hwnd);
                                            SendMessage(hListboxMAIN, LB_RESETCONTENT, 0, 0);
                                            SetListBox(hwnd, hListboxMAIN, hLabelmain);
                                        }
                                        else {
                                            error_msgbox(L"All tasks completed!");
                                        }
                                        */
                                        
                                        LauchTask(hwnd, hWnd, hLabelmain, hListboxMAIN);

                                        //ShowWindow(hWnd, SW_SHOWMINIMIZED); // ïîêàç îêíà
                                        EnableWindow(hwnd, TRUE);
                                    }
                                    return 0;
                                }
                                
                                return DefWindowProc(hWnd, uMsg, wParam, lParam);
                            });
                                hChildWnd_EDIT = hChild;
                        }

                    }
                    break;
                }
            }
            return 0;

            //Çàêðûòèå ðîäèòåëüñêîãî îêíà
            case WM_DESTROY:
            {
                
                PostQuitMessage(EXIT_SUCCESS);
            }
            return 0;
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // âûçûâàåòñÿ â ñëó÷àå åñëè ñîîáùåíèå íå îáðàáàòûâàåòñÿ
    };

    wc.lpszClassName = L"MyAppClass";
    wc.lpszMenuName = nullptr;
    wc.style = CS_VREDRAW | CS_HREDRAW;


    if (!RegisterClassEx(&wc))
        return EXIT_FAILURE;

    if (hwnd = CreateWindow(wc.lpszClassName, L"Task Scheduler", WS_OVERLAPPEDWINDOW, 0, 0, 490, 410, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
        return EXIT_FAILURE;

    ShowWindow(hwnd, nCmdShow); // ïîêàç îêíà
    UpdateWindow(hwnd);         // ïåðåðèñîâêà îêíà

    while (GetMessage(&msg, nullptr, 0, 0)) // Öèêë îáðàáîòêè ñîîáùåíèé
    {
        TranslateMessage(&msg); // ôóíêöèÿ ðàñøèôðîâûâàåò ñèñòåìíîå ñîîáùåíèå
        DispatchMessage(&msg);  // ôóíêöèÿ  ïåðåäà¸ò ñîîáùåíèå â îêîííóþ ïðîöåäóðó íà îáðàáîòêó
    }

    return static_cast<int> (msg.wParam); // âîçâðàùàåìîå çíà÷åíèå òî÷êè âõîäà

}

