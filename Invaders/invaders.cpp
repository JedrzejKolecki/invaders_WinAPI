// invaders.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "invaders.h"
#include <list>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

												// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_INVADERS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INVADERS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INVADERS));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_INVADERS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


void RysujStatek(HDC hdc, HDC hdcBmp, int x, int y, int frame)
{
	BitBlt(hdc, x, y, 193, 83, hdcBmp, 31, 339, SRCCOPY);
}


class Obcy
{
public:
	int X;
	int Y;
	RECT RC;
	float speed;
	int id;

	Obcy(int x, int y, RECT rc, float speed, int index)
	{
		this->X = x;
		this->Y = y;
		this->RC = rc;
		this->speed = speed;
		this->id = index;
	}

	void Predkosc()
	{
		//if (X > RC.right - (100*id) || X < RC.left + (10*id))
		if (X > RC.right - 100 || X < RC.left + 10)
			speed *= -1;
		X += speed;
	}

	void RysujUfo1(HDC hdc, HDC hdcBmp, int frame)
	{
		if (frame % 2)
			BitBlt(hdc, X, Y, 64, 64, hdcBmp, 40, 30, SRCCOPY);
		else
			BitBlt(hdc, X, Y, 64, 64, hdcBmp, 142, 30, SRCCOPY);
	}

	void RysujUfo2(HDC hdc, HDC hdcBmp, int frame)
	{
		if (frame % 2)
			BitBlt(hdc, X, Y, 89, 64, hdcBmp, 26, 130, SRCCOPY);
		else
			BitBlt(hdc, X, Y, 89, 64, hdcBmp, 131, 134, SRCCOPY);
	}

	void RysujUfo3(HDC hdc, HDC hdcBmp, int frame)
	{
		if (frame % 2)
			BitBlt(hdc, X, Y, 97, 65, hdcBmp, 13, 241, SRCCOPY);
		else
			BitBlt(hdc, X, Y, 97, 65, hdcBmp, 128, 242, SRCCOPY);
	}

	void ZniszczUfo(HDC hdc, HDC hdcBmp, int frame) //cos co zamieni na czarny
	{
		if (id == 1)
		{
			BitBlt(hdc, X, Y, 64, 64, hdcBmp, 40, 30, SRCCOPY);
		}

		if (id == 2)
		{
			BitBlt(hdc, X, Y, 89, 64, hdcBmp, 40, 30, SRCCOPY);
		}

		if (id == 3)
		{
			BitBlt(hdc, X, Y, 97, 65, hdcBmp, 40, 30, SRCCOPY);
		}
	}
};

class Pocisk
{
public:
	int X;
	int Y;
	RECT RC;
	int speed = 5;

	Pocisk(int x, int y, RECT rc)
	{
		this->X = x;
		this->Y = y;
		this->RC = rc;
	}

	void RysujPocisk(HDC hdc, HDC hdcBmp, int frame)
	{
		BitBlt(hdc, X, Y, 8, 17, hdcBmp, 14, 257, SRCCOPY);
	}

	void RysujPociskObcego(HDC hdc, HDC hdcBmp, int frame)
	{
		BitBlt(hdc, X, Y, 8, 17, hdcBmp, 14, 257, SRCCOPY);
	}

	void ZniszczPocisk(HDC hdc, HDC hdcBmp, int frame)
	{
		BitBlt(hdc, X, Y, 8, 17, hdcBmp, 4, 377, SRCCOPY);
	}

	void Predkosc()
	{
		Y -= speed;
	}

};

#define ID_TIMER1 1

//--------------------------------------------------------------pREDKOSC
float szybkosc = 2.0;
float szybkoscStatku = 600.0;
float szybkoscPocisku = 5.0;
static int moveLeftFlag = 1;
static int moveRightFlag = 1;

int orderFlag = 0;

//iteratory po listach
std::list<Pocisk*>::iterator itPocisk, itPociskPamietaj;
std::list<Obcy*>::iterator itObcy, itObcyPamietaj;

//lista obiektow
std::list<Obcy*> rzadPierwszy;
std::list<Obcy*> rzadDrugi;
std::list<Obcy*> rzadTrzeci;
std::list<Pocisk*> pociski;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HBITMAP hbmp, oldBmp;
	static HDC hdcBmp;
	static int statek_x = 600, statek_y = 600;

	//PROSTOKAT
	RECT rc;
	GetClientRect(hWnd, &rc);

	switch (message)
	{
	case WM_CREATE:
	{
		hbmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
		if (hbmp == NULL) MessageBox(hWnd, TEXT("Blad czytania bitmapy"), TEXT(""), MB_OK);

		HDC hdc = GetDC(hWnd);
		hdcBmp = CreateCompatibleDC(hdc);
		oldBmp = (HBITMAP)SelectObject(hdcBmp, hbmp);
		ReleaseDC(hWnd, hdc);

		GetClientRect(hWnd, &rc);

		//RZAD 1 

		rzadPierwszy.push_back(new Obcy(500, 10, rc, 1.0, 1));
		rzadPierwszy.push_back(new Obcy(600, 10, rc, 1.0, 2));
		rzadPierwszy.push_back(new Obcy(700, 10, rc, 1.0, 3));
		rzadPierwszy.push_back(new Obcy(800, 10, rc, 1.0, 4));
		rzadPierwszy.push_back(new Obcy(900, 10, rc, 1.0, 5));

		//RZAD 2 

		rzadDrugi.push_back(new Obcy(500, 100, rc, 2.0, 1));
		rzadDrugi.push_back(new Obcy(600, 100, rc, 2.0, 2));
		rzadDrugi.push_back(new Obcy(700, 100, rc, 2.0, 3));
		rzadDrugi.push_back(new Obcy(800, 100, rc, 2.0, 4));
		rzadDrugi.push_back(new Obcy(900, 100, rc, 2.0, 5));

		//RZAD 3

		rzadTrzeci.push_back(new Obcy(500, 200, rc, 3.0, 1));
		rzadTrzeci.push_back(new Obcy(600, 200, rc, 3.0, 2));
		rzadTrzeci.push_back(new Obcy(700, 200, rc, 3.0, 3));
		rzadTrzeci.push_back(new Obcy(800, 200, rc, 3.0, 4));
		rzadTrzeci.push_back(new Obcy(900, 200, rc, 3.0, 5));

		orderFlag = 1;

		SetTimer(hWnd, ID_TIMER1, 10, NULL);
	}

	break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

		// DZIALANIE GRY
	case WM_TIMER:
	{
		if (orderFlag == 1) //zeby wejsc najpierw do WM_CREATE
		{
			bool trafionyPierwszy = false; 
			bool trafionyDrugi = false;
			bool trafionyTrzeci = false;
			bool trafionyPocisk = false; 

			static int time = 0;

			//-------------------------------------------------------STEROWANIE STATKIEM

			if (statek_x > rc.right - 201)
			{
				moveRightFlag = 0;
				moveLeftFlag = 1;
			}

			else if (statek_x < rc.left + 10) //ZGADZA SIE +10 
			{
				moveRightFlag = 1;
				moveLeftFlag = 0;
			}

			else
			{
				moveRightFlag = 1;
				moveLeftFlag = 1;
			}

			statek_x = szybkoscStatku;

			//--------------------------------------------------------

			HDC hdc = GetDC(hWnd);
			FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));

			for (Obcy *a : rzadPierwszy)
			{
				a->Predkosc(); //przesuwanie
				a->RysujUfo1(hdc, hdcBmp, time / 10); //rysowanie w nowym miejscu
			}

			for (Obcy *b : rzadDrugi)
			{
				b->Predkosc(); //przesuwanie
				b->RysujUfo2(hdc, hdcBmp, time / 10); //rysowanie w nowym miejscu
			}

			for (Obcy *c : rzadTrzeci)
			{
				c->Predkosc();
				c->RysujUfo3(hdc, hdcBmp, time / 10); //rysowanie w nowym miejscu
			}

			RysujStatek(hdc, hdcBmp, statek_x, statek_y, time / 10);

			for (Pocisk *p : pociski)
			{
				p->Predkosc();//przesuwanie
				p->RysujPocisk(hdc, hdcBmp, time / 10); //rysowanie w nowym miejscu
			}

			for (itPocisk = pociski.begin(); itPocisk != pociski.end(); itPocisk++) //iteraotor po liscie obiektow Pocisk 
			{
				Pocisk *p = *itPocisk;

				if (p->Y < rc.top)
				{
					itPociskPamietaj = itPocisk;
				}

				if (p->Y == 200) //kolizja z trzecim rzedem
				{
					//jesli bedzie na wysokosci 200 to sprawdz czy x nie pokrywa sie z jakims kosmita 
					//rozmiar w trzecim: 97x65

					for (itObcy = rzadTrzeci.begin(); itObcy != rzadTrzeci.end(); itObcy++)
					{
						Obcy *c = *itObcy;
						if (p->X >= c->X && p->X <= c->X + 97) //rysowana bitmapa zaczyna sie w punkcie X i Y i rysuje rejon 97x65
						{
							//zamaluj na czarno
							c->ZniszczUfo(hdc, hdcBmp, time / 10); //zniszcz ufo zaczynajac od pozycji gdzie zaczelo rysowac 
							p->ZniszczPocisk(hdc, hdcBmp, time / 10);

							trafionyTrzeci = true;
							trafionyPocisk = true;

							itPociskPamietaj = itPocisk;
							itObcyPamietaj = itObcy;
						}
					}
				}

				if (p->Y == 100) //kolizja z drugim rzedem
				{
					//jesli bedzie na wysokosci 100 to sprawdz czy x nie pokrywa sie z jakims kosmita 
					//rozmiar w drugim: 89x64
					for (itObcy = rzadDrugi.begin(); itObcy != rzadDrugi.end(); itObcy++)
					{
						Obcy *b = *itObcy;
						if (p->X >= b->X && p->X <= b->X + 89) //rysowana bitmapa zaczyna sie w punkcie X i Y i rysuje rejon 97x65
						{
							//zamaluj na czarno
							b->ZniszczUfo(hdc, hdcBmp, time / 10); //zniszcz ufo zaczynajac od pozycji gdzie zaczelo rysowac 
							p->ZniszczPocisk(hdc, hdcBmp, time / 10);

							trafionyDrugi = true;
							trafionyPocisk = true;

							itPociskPamietaj = itPocisk;
							itObcyPamietaj = itObcy;
						}
					}

				}

				if (p->Y == 10) //kolizja z pierwszym rzedem
				{
					//jesli bedzie na wysokosci 200 to sprawdz czy x nie pokrywa sie z jakims kosmita 
					//rozmiar w pierwszym: 64x64
					for (itObcy = rzadPierwszy.begin(); itObcy != rzadPierwszy.end(); itObcy++)
					{
						Obcy *a = *itObcy;
						if (p->X >= a->X && p->X <= a->X + 64) //rysowana bitmapa zaczyna sie w punkcie X i Y i rysuje rejon 97x65
						{
							//zamaluj na czarno
							a->ZniszczUfo(hdc, hdcBmp, time / 10); //zniszcz ufo zaczynajac od pozycji gdzie zaczelo rysowac 
							p->ZniszczPocisk(hdc, hdcBmp, time / 10);

							trafionyPierwszy = true; 
							trafionyPocisk = true; 

							itPociskPamietaj = itPocisk;
							itObcyPamietaj = itObcy;
						}
					}
				}
			}

			if (trafionyPierwszy)
				rzadPierwszy.erase(itObcyPamietaj);
			if (trafionyDrugi)
				rzadDrugi.erase(itObcyPamietaj);
			if (trafionyTrzeci)
				rzadTrzeci.erase(itObcyPamietaj);
			if (trafionyPocisk)
				pociski.erase(itPociskPamietaj);

			ReleaseDC(hWnd, hdc);
			time++;
		}
	}

	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
	}
	break;

	//------------------------------------------------------------------------------STEROWANIE
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{

			if (moveLeftFlag == 1)
				szybkoscStatku -= 10.0;
		}
		if (wParam == VK_RIGHT)
		{
			if (moveRightFlag == 1)
				szybkoscStatku += 10.0;
		}

		if (wParam == VK_SPACE)
		{
				pociski.push_back(new Pocisk(statek_x + 90, statek_y - 25, rc));
		}


		break;
	case WM_DESTROY:
		SelectObject(hdcBmp, oldBmp);
		DeleteObject(hbmp);
		ReleaseDC(hWnd, hdcBmp);

		KillTimer(hWnd, ID_TIMER1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

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
