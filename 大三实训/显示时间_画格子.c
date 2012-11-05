/*------------------------------------------------------------------------
   	HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
		      (c) Charles Petzold, 1998
 -----------------------------------------------------------------------*/

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT ("HelloWin") ;
    HWND	 hwnd ;  //窗口句柄
    MSG 	msg ;   //消息结构
    WNDCLASS	wndclass ;   //窗口类别结构

    wndclass.style		  = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc  = WndProc;
    wndclass.cbClsExtra	  = 0 ;
    wndclass.cbWndExtra	  = 0 ;
    wndclass.hInstance	  = hInstance ;
    wndclass.hIcon		  = LoadIcon (NULL, IDI_HAND) ;
    wndclass.hCursor	  = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName	= NULL ;
    wndclass.lpszClassName	= szAppName ;

    if (!RegisterClass (&wndclass))
    {
        MessageBox (	NULL, TEXT ("This program requires Windows NT!"),
                        TEXT("DFDFDFD"), MB_ICONERROR) ;
        return 0 ;
    }
    hwnd = CreateWindow( szAppName,	// window class name
                         TEXT ("The Hello Program"),	// window caption
                         WS_OVERLAPPEDWINDOW,	// window style
                         CW_USEDEFAULT,	// initial x position
                         CW_USEDEFAULT,	// initial y position
                         CW_USEDEFAULT,	// initial x size
                         CW_USEDEFAULT,	// initial y size
                         NULL,			// parent window handle
                         NULL,	        // window menu handle
                         hInstance,	    // program instance handle
                         NULL) ; 	    // creation parameters

    ShowWindow (hwnd, iCmdShow) ;
    UpdateWindow (hwnd) ;

    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }
    return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC			hdc ;  //设备句柄
    PAINTSTRUCT ps ;    //绘图结构
    RECT		rect,rc ; //矩形结构
    static TCHAR time[100];
    HBRUSH hBrush;   //刷子
    HPEN hpen;       //笔
    SYSTEMTIME tm;   //系统时间
    int i,xgap,ygap;
    static TCHAR *DAYS[7] = {"星期一","星期二",
    "星期三","星期四","星期五","星期六","星期天"};


    switch (message)
    {
    case WM_CREATE:
        SetTimer(hwnd,1,1000,NULL);
        GetLocalTime(&tm);
        wsprintf(time,"%d-%.2d-%.2d %.2d:%.2d:%.2d",tm.wYear,tm.wMonth,tm.wDay,tm.wHour,tm.wMinute,tm.wSecond);

        return 0 ;

    case WM_PAINT:
        hdc = BeginPaint (hwnd, &ps) ;
        GetClientRect (hwnd, &rect) ;
        rc.left=rect.left+200;
        rc.top=rect.top+200;
        rc.right=rect.right-200;
        rc.bottom=rect.bottom-200;
        hBrush=CreateSolidBrush(RGB(126,48,127));
        FillRect(hdc,&rc,hBrush);
        SetBkMode(hdc,TRANSPARENT);
        SetTextColor(hdc,RGB(0,0,255));
        DrawText (hdc,time, -1,
                  &rc,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        xgap = (int)((rect.right - rect.left) / 7);
        ygap = (int)((rect.bottom - rect.top) / 7);
        for(i = 0; i < 7; i++)
        {
            MoveToEx(hdc,rect.left,i*ygap,NULL);
            LineTo(hdc,rect.right,i*ygap);
        }
        for(i = 0; i < 7; i++)
        {
            MoveToEx(hdc,i*xgap,rect.top,NULL);
            LineTo(hdc,i*xgap,rect.bottom);
        }
        for(i = 0; i < sizeof DAYS; i++)
        {
            rc.left = rect.left + i*xgap;
            rc.top = rect.top;
            rc.right = rc.left + xgap;
            rc.bottom = rc.top + ygap;
            DrawText (hdc,DAYS[i], -1,
                  &rc,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }

        EndPaint (hwnd, &ps) ;
        return 0 ;

    case WM_TIMER:
        hdc=GetDC(hwnd);
        GetClientRect (hwnd, &rc) ;
        GetLocalTime(&tm);
        wsprintf(time,"%d-%.2d-%.2d %.2d:%.2d:%.2d",tm.wYear,tm.wMonth,tm.wDay,tm.wHour,tm.wMinute,tm.wSecond);

        InvalidateRect (hwnd, NULL, TRUE) ;
        ReleaseDC(hwnd,hdc);

        return 0;
    case WM_DESTROY:
        PostQuitMessage (0) ;
        return 0 ;
    }
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}
