#include <windows.h>
#include <windowsx.h>
#include "Sight.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� ��������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Figure Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200,200,400,400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Sight
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������
Sight sight;
Square square;
Figure* pnt = &sight;
LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch(msg)
	{
	case WM_PAINT:						// ��������� ��������� WM_PAINT ������������ ������ ���, ����� ��������� ��������� ��� ����������� �����������
		{
			HDC dc = GetDC(hWnd);		// ������� GetDC ���������� �������� ����������, � ������� �������� ���������� � ���, � ����� ���� ������������ �����, ������ ������� ������� ������� ���� hWnd, � ����� ����� ������ ��������� ������ ��������� ������� ������� � �.�.
			pnt->Clear(dc);
			pnt->Draw(dc);
			ReleaseDC(hWnd, dc);		// ������� ReleaseDC �������� �������, ��� ��������� � ����� hWnd �������� dc ������ �� �����
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_LEFT:
				{
					pnt->Move(-2, 0);
					break;
				}
			case VK_RIGHT:
				{
					pnt->Move(2, 0);
					break;
				}
			case VK_UP:
				{
				pnt->Move(0, -2);
				break;
				}
			case VK_DOWN:
				{
				pnt->Move(0, 2);
				break;
				}
			case VK_OEM_PLUS:
				{
				pnt->PlusSize();
				break;
				}
			case VK_OEM_MINUS:
			{
				pnt->MinusSize();
				break;
			}
			case VK_SHIFT:
			{
				Figure* pntt = pnt;
				if (pnt == &sight)
					pnt = &square;
				else
					pnt = &sight;
				pnt->SwitchTo(pntt->GetSize(), pntt->GetOffsetX(), pntt->GetOffsetY());
			}
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			pnt->MoveTo(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			if(pnt->InnerPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))
				pnt->StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			if (pnt->IsDragging())
			{
				pnt->Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				InvalidateRect(hWnd, nullptr, false);
			}
			return 0;
		}
	case WM_LBUTTONUP:
		{
			pnt->StopDragging();
			return 0;
		}
	case WM_SIZE:
		{
			InvalidateRect(hWnd, nullptr, false);	// ������� InvalidateRect ��������� ������� ������� ���� hWnd ��������� �����������, � ���������� ���� ������������ ��������� ��������� WM_PAINT
			return 0;								// ����� ������� �� ���������� ����, ��� ����������� ���������� � ��� ���������� �������� ����
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	default:
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
	return 0;
}
