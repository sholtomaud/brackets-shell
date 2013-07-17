#pragma once
/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2013 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/
#include <windows.h>
#include <winuser.h>
#include <Shellapi.h>

class cef_window;
class cef_menu;

// Helpers
static __inline int RectWidth(const RECT &r) { return r.right - r.left; }
static __inline int RectHeight(const RECT &r) { return r.bottom - r.top; }

class cef_window
{
public:
    cef_window(void);
    virtual ~cef_window(void);

    BOOL Create(LPCTSTR szClass, LPCTSTR szWindowTitle, DWORD dwStyles, int x, int y, int width, int height, cef_window* parent = NULL, cef_menu* menu = NULL);
    bool SubclassWindow (HWND hWnd);

    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT DefaultWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

    HWND GetSafeWnd() 
    { return (this != NULL) ? mWnd : NULL; }

    HMENU GetMenu() 
    { return ::GetMenu(mWnd); }

    BOOL UpdateWindow()
    { return ::UpdateWindow(mWnd); }

    BOOL GetWindowPlacement(LPWINDOWPLACEMENT wp)
    { return ::GetWindowPlacement(mWnd, wp); }

    BOOL SetWindowPlacement(LPWINDOWPLACEMENT wp)
    { return ::SetWindowPlacement(mWnd, wp); }

    BOOL GetWindowRect(LPRECT r)
    { return ::GetWindowRect(mWnd, r); }

    BOOL GetClientRect(LPRECT r)
    { return ::GetClientRect(mWnd, r); }

    HDC BeginPaint(PAINTSTRUCT* ps)
    { return ::BeginPaint(mWnd, ps); }

    BOOL EndPaint(PAINTSTRUCT* ps) 
    { return ::EndPaint(mWnd, ps); }

    BOOL DestroyWindow()
    { return ::DestroyWindow(mWnd); }

    BOOL SetProp(LPCWSTR lpString, HANDLE hData)
    { return ::SetProp(mWnd, lpString, hData); }

    HANDLE GetProp(LPCWSTR lpString)
    { return ::GetProp(mWnd, lpString); }

    HANDLE RemoveProp(LPCWSTR lpString)
    { return ::RemoveProp(mWnd, lpString); }

    LONG GetWindowLongPtr(int nIndex) 
    { return ::GetWindowLongPtr(mWnd, nIndex); }

    LONG SetWindowLongPtr(int nIndex, LONG dwNewLong) 
    { return ::SetWindowLongPtr(mWnd, nIndex, dwNewLong); }

    LONG GetClassLongPtr(int nIndex)
    { return ::GetClassLongPtr(mWnd, nIndex); }

    BOOL GetWindowInfo (PWINDOWINFO pwi) 
    { return ::GetWindowInfo (mWnd, pwi); }

    void DragAcceptFiles(BOOL fAccept)
    { return ::DragAcceptFiles(mWnd, fAccept); }

    BOOL ShowWindow(int nCmdShow)
    { return ::ShowWindow(mWnd, nCmdShow); }

    HDC GetDCEx(HRGN hrgnClip, DWORD dwFlags)
    { return ::GetDCEx(mWnd, hrgnClip, dwFlags); }

    HDC GetWindowDC()
    { return ::GetWindowDC(mWnd); }

    HDC GetDC()
    { return ::GetDC(mWnd); }

    int ReleaseDC(HDC dc)
    { return ::ReleaseDC(mWnd, dc); }

    BOOL SetWindowPos(cef_window* insertAfter, int x, int y, int cx, int cy, UINT uFlags) 
    { return ::SetWindowPos(mWnd, insertAfter->GetSafeWnd(), x, y, cx, cy, uFlags); }

    int GetWindowText(LPWSTR lpString, int nMaxCount) 
    { return ::GetWindowTextW(mWnd, lpString, nMaxCount); }

    int GetWindowTextLength() 
    { return ::GetWindowTextLengthW(mWnd); }

    BOOL InvalidateRect(LPRECT lpRect, BOOL bErase = FALSE)
    { return ::InvalidateRect(mWnd, lpRect, bErase); }

protected:
    HWND mWnd;
    WNDPROC mSuperWndProc;

    BOOL HandleNonClientDestroy();
    virtual void PostNonClientDestory();

    void ComputeLogicalClientRect(RECT& rectClient);
    void ScreenToNonClient(RECT& rect);
};
