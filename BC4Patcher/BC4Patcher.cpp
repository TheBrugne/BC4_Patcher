// BC4Patcher.cpp : Defines the entry point for the application.
//

#include <algorithm>

#include "Windows.h"
//#include <Commdlg.h>
#include "framework.h"
#include "BC4Patcher.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>
#include "resource.h"
#include <Mmsystem.h>
#include <mciapi.h>
#include <atlstr.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LPCWSTR path = L"";
std::string myVarS_G;
DWORD WINAPI myThread(LPVOID lpParameter)
{
    PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE);
    return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BC4PATCHER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BC4PATCHER));

    unsigned int myCounter = 0;
    DWORD myThreadID;
    HANDLE myHandle = CreateThread(0, 0, myThread, &myCounter, 0, &myThreadID);


    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
       // if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      //  {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
       // }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
   // wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.hbrBackground = CreatePatternBrush(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BC4PATCHER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON3));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

inline bool exists_test0(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}
#define PATH_ID 10009
#define CREDIT_ID 10010
#define CREDIT_ID2 10011

HWND hWndEdit;
HWND hWndStatus;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable
    RECT rect;
    GetClientRect(GetDesktopWindow(), &rect);
    rect.left = (rect.right / 2) - (300 / 2);
    rect.top = (rect.bottom / 2) - (300 / 2);

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
        rect.left, rect.top, 300, 300, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }
 
   //SetWindowText(hWnd, TEXT("Control string"));

   if (true == exists_test0("C:\\Program Files\\Beyond Compare 4\\BCompare.exe"))
   {
       myVarS_G = "C:\\Program Files\\Beyond Compare 4\\BCompare.exe";
       path = L"C:/Program Files/Beyond Compare 4/BCompare.exe";
   }

    hWndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), path,
       WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 30, 270,
       20, hWnd, (HMENU)PATH_ID, NULL, NULL);

   HFONT hFont = CreateFont(14, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
   SendMessage(hWndEdit, WM_SETFONT, WPARAM(hFont), TRUE);

   HWND hWndCredits = CreateWindowW(L"STATIC",L"Patched by Brugne",
       WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 240, 200,
       20, hWnd, (HMENU)CREDIT_ID, NULL, NULL);

   hWndStatus = CreateWindowW(L"STATIC", L"",
       WS_CHILD | WS_VISIBLE | ES_READONLY, 50, 160, 250,
       20, hWnd, (HMENU)CREDIT_ID, NULL, NULL);



   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

void select_file(HWND hWnd)
{
    OPENFILENAME ofn = {0};

    USES_CONVERSION_EX;

    std::string file_s = "";
    LPWSTR lp = A2W_EX(file_s.c_str(), file_s.length());

    wchar_t fileBuffer[MAX_PATH] = { 0 };


    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = fileBuffer;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 2048;
    ofn.lpstrFilter = L".exe\0*.exe";
    ofn.nFilterIndex = 1;
    if (GetOpenFileName(&ofn))
    {
        std::wstring ws(ofn.lpstrFile);
        myVarS_G = std::string(ws.begin(), ws.end());
        path = ws.c_str();
        SetWindowTextA(hWndEdit, myVarS_G.c_str());
        ShowWindow(hWndEdit, SW_HIDE);
        ShowWindow(hWndEdit, SW_SHOW);

     
    }
}


int isSubArray(int A[], int B[], int n, int m)
{
    // Two pointers to traverse the arrays
    int i = 0, j = 0;

    // Traverse both arrays simultaneously
    while (i < n && j < m) {

        // If element matches
        // increment both pointers
        if (A[i] == B[j]) {

            i++;
            j++;

            // If array B is completely
            // traversed
            if (j == m)
                return (i - 7);
        }
        // If not,
        // increment i and reset j
        else {
            i = i - j + 1;
            j = 0;
        }
    }

    return n+1;
}

#define BUTTON_PATCH_ID 10005
#define BUTTON_SEL_ID   10006
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        UINT ID = GetWindowLong((HWND)lParam, GWL_ID);
   
      if (ID == PATH_ID)
      {
            SetTextColor((HDC)wParam, RGB(255, 208, 153));
      }
      else if ((ID == CREDIT_ID) || (ID == CREDIT_ID2))
      {
          SetTextColor((HDC)wParam, RGB(255, 255, 255));
      }
        SetBkMode(hdcStatic, TRANSPARENT);
        return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
    }
    break;
    case WM_CREATE:
        {


        HWND button_patch = CreateWindow(TEXT("button"), TEXT("PATCH PROGRAM"),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 95, 180, 110, 40, hWnd, (HMENU)BUTTON_PATCH_ID, NULL, NULL);
        HWND button_sel = CreateWindow(TEXT("button"), TEXT("SELECT FILE"), WS_VISIBLE | WS_CHILD, 190, 60, 90, 20, hWnd, (HMENU)BUTTON_SEL_ID, NULL, NULL);

     
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:

 
            switch (wmId)
            {
                case (BUTTON_PATCH_ID):
                {
                    int cSize = WideCharToMultiByte(CP_ACP, 0, path, wcslen(path), NULL, 0, NULL, NULL);
                    std::string output(static_cast<size_t>(cSize), '\0');
                    WideCharToMultiByte(CP_ACP, 0, path, wcslen(path),
                        reinterpret_cast<char*>(&output[0]), cSize, NULL, NULL);
                    if (myVarS_G.find(".exe") != std::string::npos)
                    {
                        std::wstring temp = std::wstring(myVarS_G.begin(), myVarS_G.end());

                        // Applying c_str() method on temp
                        path = temp.c_str();
                        

                        std::string s = "Validating exe...";
                        SetWindowTextA(hWndStatus, s.c_str());
                        ShowWindow(hWndStatus, SW_HIDE);
                        ShowWindow(hWndStatus, SW_SHOW);
                        UpdateWindow(hWnd);


                        
                        int orig[7] = { 116,62,72,139,133,176,4 };
                        int mod[7] = { 117,62,72,139,133,176,4 };
                        long size;
                        std::wstring ws(path);
                        std::string myVarS = std::string(ws.begin(), ws.end());
                        std::ifstream input(myVarS, std::ios::binary);

                        input.seekg(0, std::ios::end);
                        size = input.tellg();
                        int* buffer = new int[size];
                        input.close();
                        std::ifstream input1(myVarS, std::ios::binary);
                        int i = 0;
                        while (!input1.eof())
                        {
                            buffer[i]=input1.get();
                            i++;
                        }

                        int idx = isSubArray(buffer, mod, size, 7);
                        if (idx <= size)
                        {
                            std::string s = "File has already been patched!!";
                            SetWindowTextA(hWndStatus, s.c_str());
                            ShowWindow(hWndStatus, SW_HIDE);
                            ShowWindow(hWndStatus, SW_SHOW);
                        }
                        else
                        {
                            idx = isSubArray(buffer, orig, size, 7);
                            if (idx >= size + 1)
                            {
                                std::string s = "not a valid BC4 exe file";
                                SetWindowTextA(hWndStatus, s.c_str());
                                ShowWindow(hWndStatus, SW_HIDE);
                                ShowWindow(hWndStatus, SW_SHOW);
                            }
                            else
                            {
                                buffer[idx] = 117;
                                i = 0;


                                std::ofstream out(myVarS, std::ios::binary);
                                if (!out.is_open())
                                {
                                    std::string t_s = "Not enough privileges to write into " + myVarS + "\nRestart patcher in admin mode";
                                    std::wstring temp = std::wstring(t_s.begin(), t_s.end());

                                    // Applying c_str() method on temp
                                    LPCWSTR wideString = temp.c_str();
                                    LPCWSTR str = wideString;


                                    MessageBox(hWnd, str, TEXT(""), 0);

                                    std::string s = "Restart in Admin Mode";
                                    SetWindowTextA(hWndStatus, s.c_str());
                                    ShowWindow(hWndStatus, SW_HIDE);
                                    ShowWindow(hWndStatus, SW_SHOW);
                                    UpdateWindow(hWnd);
                                }
                                else
                                {

                                    i = 0;
                                    while (i < size)
                                        out.put(buffer[i++]);

                                    input1.close();
                                    out.close();

                                    std::string t_s = "Patched successfully :)";
                                    std::wstring temp = std::wstring(t_s.begin(), t_s.end());

                                    // Applying c_str() method on temp
                                    LPCWSTR wideString = temp.c_str();
                                    LPCWSTR str = wideString;


                                    MessageBox(hWnd, str, TEXT(""), 0);

                                    std::string s = "Patched successfully :)";
                                    SetWindowTextA(hWndStatus, s.c_str());
                                    ShowWindow(hWndStatus, SW_HIDE);
                                    ShowWindow(hWndStatus, SW_SHOW);
                                    UpdateWindow(hWnd);
                                }
                            }
                        }
                    }
                    else
                    {
                        MessageBox(hWnd, TEXT("select a valid .exe"), TEXT(""), 0);
                    }
                       

                   
                }
                break;
                case (BUTTON_SEL_ID):
                {
                    select_file(hWnd);
                }
          //  case IDM_ABOUT:
             //   DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            //    break;
           // case IDM_EXIT:
            //    DestroyWindow(hWnd);
            //    break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_DRAWITEM:
        {
            int wmId = LOWORD(wParam);
            if (wParam == BUTTON_PATCH_ID)
            {
                LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;

                SetDCBrushColor(lpDIS->hDC, RGB(255, 0, 0));

                SelectObject(lpDIS->hDC, GetStockObject(DC_BRUSH));

                RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top,
                    lpDIS->rcItem.right, lpDIS->rcItem.bottom, 5, 5);

                SetDCBrushColor(lpDIS->hDC, RGB(0, 0, 0));
                SetBkMode(lpDIS->hDC, TRANSPARENT);
                DrawTextA(lpDIS->hDC, "Patch Program", -1, &lpDIS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                return TRUE;
            }
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
