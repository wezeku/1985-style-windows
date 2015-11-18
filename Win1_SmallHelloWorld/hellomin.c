/* hellomin.c
 * Minimal Windows API Hello World.
 *
 *
 * Programming like it's 1985!
 *
 * Windows 1.0 was released on the 20th November 1985.
 * To commemorate its 30th birthday, I've written a shorter 
 * version of the infamously long "Hello World" sample.
 *
 * The name of this file honours the eighties 8+3 character limit
 * for filename+extension.
 */ 


#undef UNICODE  /* Because we're in 1985 :-) */
#include "windows.h"

char *szAppName     = "MinimalHelloWorld";
char *szWindowTitle = "Minimal Hello Windows 1985-style!";

int HelloInit(HINSTANCE);
long FAR PASCAL HelloWndProc(HWND, unsigned, WORD, LONG);


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
    MSG   msg;
    HWND  hWnd;

    if (!hPrevInstance)
        if (!HelloInit(hInstance))
            return FALSE;

    hWnd = CreateWindow(
        szAppName,
        szWindowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
        );

    ShowWindow(hWnd, cmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    exit(msg.wParam);
}


int HelloInit(HINSTANCE hInstance)
{
    PWNDCLASS pHelloClass;

    pHelloClass = LocalAlloc(LPTR, sizeof(WNDCLASS));

    pHelloClass->hCursor = LoadCursor(NULL, IDC_ARROW);
    pHelloClass->hIcon = NULL;
    pHelloClass->lpszMenuName = NULL;
    pHelloClass->lpszClassName = szAppName;
    pHelloClass->hbrBackground = GetStockObject(WHITE_BRUSH);
    pHelloClass->hInstance = hInstance;
    pHelloClass->style = CS_HREDRAW | CS_VREDRAW;
    pHelloClass->lpfnWndProc = (WNDPROC)HelloWndProc;

    if (!RegisterClass(pHelloClass))
        return FALSE;

    LocalFree(pHelloClass);
    return TRUE;
}


long FAR PASCAL HelloWndProc(HWND hWnd, unsigned message, WORD wParam, LONG lParam)
{
    PAINTSTRUCT paintStruct;
    char *szWindowText = "The 80's called and wanted its monolithic switch/case message parsing back.";

    switch (message) {
    case WM_PAINT:
        BeginPaint(hWnd, &paintStruct);
        TextOut(paintStruct.hdc, 10, 10, szWindowText, strlen(szWindowText));
        EndPaint(hWnd, &paintStruct);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0L;
}
