#ifndef _MYLIB_H // 1 man hinh dai 210, rong 52
#define _MYLIB_H

#include<windows.h>
#include<iostream>
#include<conio.h>
using namespace std;
// ==================== FULL SCREEN ==========================
void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
//=============================HAM GOTOXY==========================
void gotoxy(int x, int y) // Di chuyen toa do con tro trong he toa do De-cat
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
//=====================TRA VE VI TRI X CUA CON TRO==============================
int wherex()
{
HANDLE hConsoleOutput;
hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
return screen_buffer_info.dwCursorPosition.X;
}
//=========================TRA VE VI TRI Y CUA CON TRO============================
int wherey( void )
{
HANDLE hConsoleOutput;
hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
return screen_buffer_info.dwCursorPosition.Y;
}
//==============================AN CO TRO MAN HINH CONSOLE=======================
void anConTro()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
//==============================HIEN CON TRO MAN HINH CONSOLE================
void hienConTro()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
// ============= DOI MAU CHU ================
void changeColor(int k)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, k);
}
// ================== PHIM DA NHAN =======================
void pressKey(char &c,bool &kytu)
{
	c = getch();
	if (c == -32 || c == 0)
	{
		c = getch();
		kytu = 0;
	}
	else kytu = 1;
}
// ==================== CHIEU DAI SO DUONG =======================
int chieuDaiSoDuong(int x)
{
	int len = 1;
	if (x/10 > 0)
	{
		len++;
		x = x/10;
	}
	return len;
}
// =========================== IN HOA =============================
char inHoa(char x)
{
	if (x >= 97 && x <= 122) return (x-32);
	return x;
}
// ===================== CONVERT STRING SANG INTEGER ================================
int convertToInt(string x)
{
	if (x.length() == 0) return -1;
	int res = 0;
	for (int i = 0; i < x.length(); i++)
	{
		res = res*10 + (int)(x[i] - 48);
	}
	return res;
}
// ===================== 	CONVERT INTEGER SANG STRING ===========================
string convertToString(int x)
{
	string res;
	while (x != 0)
	{
		res = (char)(x%10 + 48) + res;
		x = x/10;
	}
	return res;
}
// ====================== KIEM TRA THOAT ===============================
bool isExit(char &c, bool &kytu)
{
	gotoxy(0,30);
	anConTro();
	cout << "Ban co muon thoat ma khong LUU?" << endl;
	cout << "Nhan Y de THOAT hoac nhan phim BAT KY de HUY";
	pressKey(c,kytu);
	if (inHoa(c) == 89 && kytu)
	{
		c = 27;
		return 1;
	}
	gotoxy(0,30);
	cout << "                                              " << endl;
	cout << "                                              " << endl;
	c = 0;
	kytu = 0;
	return 0;
}

#endif
