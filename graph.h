#ifndef _GRAPH_H
#define _GRAPH_H

#include<iostream>
#include<windows.h>
#include "mylib.h"
#define doc (char)179
#define ngang (char)196
#define traitren (char)218
#define phaitren (char)191
#define traiduoi (char)192
#define phaiduoi (char)217
#define docphai (char)195
#define doctrai (char)180
#define ngangxuong (char)194
#define nganglen (char) 193
using namespace std;

//============================= VE KHUNG ===========================
void veKhung(int dai, int rong)
{
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
	 		if (i == 0) // i = 0
			{
				if (j == 0)
				{
					cout << traitren;
					continue;
				}
				if (j == rong-1)
				{
					cout << phaitren;
					continue;
				}
				cout << ngang;
				continue;
			}
			if (i == dai-1) // i cuoi
			{
				if (j == 0)
				{
					cout << traiduoi;
					continue;
				}
				if (j == rong-1)
				{
					cout << phaiduoi;
					continue;
				}
				cout << ngang;
				continue;
			}
			if (j == 0 || j == rong-1)
			{
				cout << doc;
				continue;
			}
			cout << " ";
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}
// =========================== VE KHUNG MAY BAY =====================================
void veKhungMB(int dai, int rong)
{
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
	 		if (i == 0) // i = 0
			{
				if (j == 0)
				{
					cout << traitren;
					continue;
				}
				if (j == rong-1)
				{
					cout << phaitren;
					continue;
				}
				if (j % (rong/3) == 0)
				{
					cout << ngangxuong;
					continue;
				}
				cout << ngang;
				continue;
			}
			if (i == dai-1) // i cuoi
			{
				if (j == 0)
				{
					cout << traiduoi;
					continue;
				}
				if (j == rong-1)
				{
					cout << phaiduoi;
					continue;
				}
				if (j % (rong/3) == 0)
				{
					cout << nganglen;
					continue;
				}
				cout << ngang;
				continue;
			}
			if (j == 0 || j == rong-1)
			{
				cout << doc;
				continue;
			}
			if (j % (rong/3) == 0)
			{
				cout << doc;
				continue;
			}
			cout << " ";
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}

#endif
