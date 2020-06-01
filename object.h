#ifndef _OBJECT_H
#define _OBJECT_H

#include<iostream>
#include<string.h>
#include<windows.h>
#include<fstream>
#include "graph.h"
#define MAXLIST 300
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define BACKSPACE 8
using namespace std;

// ==================== NGAY ==========================
struct Ngay
{
	int ngay;
	int thang;
	int nam;
};
// ========================= KHACH HANG =====================
struct KhachHang
{
	int SoCMND;
	string HoTen;
	bool GioiTinh; // 0: nu, 1: nam
};
// ========================== NODE KHACH HANG ======================
struct nodeKhachHang
{
	KhachHang khachhang;
	nodeKhachHang *left = NULL;
	nodeKhachHang *right = NULL;
};
// ======================== LIST KHACH HANG ======================== 
struct listKhachHang
{
	nodeKhachHang *root = NULL;
};
// ==================== VE ==================================
struct Ve
{
	KhachHang *ticket = NULL;
};
// ====================== MAY BAY ===========================
struct MayBay
{
	string SoHieu;
	string Loai;
	int socho;
};
// ======================== DANH SACH MAY BAY ===========================
struct listMayBay
{
	MayBay *list[MAXLIST] = {NULL};
	int n = 0;
};
// ====================== CHUYEN BAY =============================
struct ChuyenBay
{
	string MaCB;
	string SoHieu;
	Ngay NgayKhoiHanh;
	string Den;
	int trangthai; // 0: huy , 1: con ve, 2: het ve, 3: hoan tat
	Ve *ticket = NULL; 
};
// ========================== NODE CHUYEN BAY ==========================
struct nodeChuyenBay
{
	ChuyenBay chuyenbay;
	nodeChuyenBay *next = NULL;
};
// ============================ DANH SACH CHUYEN BAY =====================
struct listChuyenBay
{
	nodeChuyenBay *Head = NULL;
};




// ===========================================================================================================================================
// ================================= MENU ==================================
int mainMenu()
{
	changeColor(15);
	system("cls");
	int cur = 0;
	char c;
	bool kytu;
	string menu[11];
	menu[0] = "THEM MAY BAY";
	menu[1] = "XOA MAY BAY";
	menu[2] = "CHINH SUA MAY BAY";
	menu[3] = "THEM CHUYEN BAY";
	menu[4] = "HIEU CHINH CHUYEN BAY";
	menu[5] = "DAT VE";
	menu[6] = "HUY VE";
	menu[7] = "DANH SACH HANH KHACH THUOC CHUYEN BAY";
	menu[8] = "DANH SACH CHUYEN BAY KHOI HANH";
	menu[9] = "DANH SACH GHE TRONG CUA CHUYEN BAY";
	menu[10] = "THONG KE LUOT THUC HIEN CUA MAY BAY";
	for (int i = 1; i < 11; i++)
	{
		gotoxy(0,2*i);
		cout << menu[i];
	}
	changeColor(240);
	gotoxy(0,0);
	cout << menu[0];
	changeColor(15);
	anConTro();
	pressKey(c,kytu);
	while (c != 27)
	{
		if (c == UP && !kytu) // UP
		{
			if (cur > 0)
			{
				changeColor(15);
				gotoxy(0,2*cur);
				cout << menu[cur];
				cur--;
				changeColor(240);
				gotoxy(0,2*cur);
				cout << menu[cur];
				changeColor(15);
			}
		}
		if (c == DOWN && !kytu)
		{
			if (cur < 10)
			{
				changeColor(15);
				gotoxy(0,2*cur);
				cout << menu[cur];
				cur++;
				changeColor(240);
				gotoxy(0,2*cur);
				cout << menu[cur];
				changeColor(15);
			}
		}
		if (c == ENTER) return cur;
		pressKey(c,kytu);
	}
	return -1;
}
// ==================================== LOAD FILE MAY BAY ====================================
bool loadFileMB(listMayBay &ds)
{
	ifstream infile;
	infile.open("DSMB.txt", ios::in);
	if (infile.fail()) return 0;
	string SoHieu;
	string Loai;
	int socho;
	while (!infile.eof())
	{
		infile >> SoHieu;
		infile >> Loai;
		infile >> socho;
		ds.list[ds.n] = new MayBay;
		ds.list[ds.n]->SoHieu = SoHieu;
		ds.list[ds.n]->Loai = Loai;
		ds.list[ds.n]->socho = socho;
		ds.n++;
	}
	infile.close();
	return 1;
}
// ==================================== LOAD FILE CHUYEN BAY ====================================
bool loadFileCB(listChuyenBay &ds)
{
	ifstream infile;
	infile.open("DSCB.txt", ios::in);
	if (infile.fail()) return 0;
	string MaChuyen;
	string SoHieu;
	Ngay date;
	string den;
	int trangthai;
	while (!infile.eof())
	{
		infile >> MaChuyen;
		infile >> SoHieu;
		infile >> date.ngay;
		infile >> date.thang;
		infile >> date.nam;
		infile >> den;
		infile >> trangthai;
		if (ds.Head == NULL)
		{
			ds.Head = new nodeChuyenBay;
			ds.Head->chuyenbay.SoHieu = SoHieu;
			ds.Head->chuyenbay.MaCB = MaChuyen;
			ds.Head->chuyenbay.NgayKhoiHanh = date;
			ds.Head->chuyenbay.Den = den;
			ds.Head->chuyenbay.trangthai = trangthai;
			ds.Head->next = NULL;
		}
		else
		{
			nodeChuyenBay *p;
			for (p = ds.Head; p->next != NULL; p = p->next);
			p->next = new nodeChuyenBay;
			p = p->next;
			p->chuyenbay.SoHieu = SoHieu;
			p->chuyenbay.MaCB = MaChuyen;
			p->chuyenbay.NgayKhoiHanh = date;
			p->chuyenbay.Den = den;
			p->chuyenbay.trangthai = trangthai;
			p->next = NULL;
		}
	}
	infile.close();
	return 1;
}
// ============================================ LOAD FILE KHACH HANG =============================
bool loadFileKH(listKhachHang &ds)
{
	ifstream infile;
	infile.open("DSKH.txt",ios::in);
	if (infile.fail()) return 0;
	int CMND;
	string hoten;
	bool gioitinh; 
	while (!infile.eof())
	{
		infile >> CMND;
		infile >> hoten;
		infile >> gioitinh;
		if (ds.root == NULL)
		{
			ds.root = new nodeKhachHang;
			ds.root->khachhang.SoCMND = CMND;
			ds.root->khachhang.HoTen = hoten;
			ds.root->khachhang.GioiTinh = gioitinh;
			ds.root->left = ds.root->right = NULL;
		}
		else
		{
			nodeKhachHang *p = ds.root;
			while (1)
			{
				if (CMND < p->khachhang.SoCMND)
				{
					if (p->left != NULL)
					{
						p = p->left;
						continue;
					}
					p->left = new nodeKhachHang;
					p = p->left;
					p->khachhang.SoCMND = CMND;
					p->khachhang.HoTen = hoten;
					p->khachhang.GioiTinh = gioitinh;
					p->left = NULL;
					p->right = NULL;
					break;
				}
				if (CMND > p->khachhang.SoCMND)
				{
					if (p->right != NULL)
					{
						p = p->right;
						continue;
					}
					p->right = new nodeKhachHang;
					p = p->right;
					p->khachhang.SoCMND = CMND;
					p->khachhang.HoTen = hoten;
					p->khachhang.GioiTinh = gioitinh;
					p->left = NULL;
					p->right = NULL;
					break;
				}
			}
		}
	}
	infile.close();
	return 1;
}
// ========================= SHOW DANH SACH MAY BAY ========================
void showDSMB(listMayBay &ds, int page,int x, int y,int maxpage)
{
	anConTro();
	changeColor(15);
	veKhungMB(24,60);
	gotoxy(x+1+10-4,y+1);
	cout << "So hieu";
	gotoxy(x+21+10-2,y+1);
	cout << "Loai";
	gotoxy(x+41+10-3,y+1);
	cout << "So cho";
	for (int i = (page-1)*10; i < page*10; i++)
	{
		if (ds.list[i] == NULL) break;
		gotoxy(x+1+10-ds.list[i]->SoHieu.length()/2,y+3+2*(i-(page-1)*10));
		cout << ds.list[i]->SoHieu;
		gotoxy(x+21+10-ds.list[i]->Loai.length()/2,y+3+2*(i-(page-1)*10));
		cout << ds.list[i]->Loai;
		gotoxy(x+41+10-chieuDaiSoDuong(ds.list[i]->socho)/2,y+3+2*(i-(page-1)*10));
		cout << ds.list[i]->socho;
	}
	gotoxy(x+30-(6+1+chieuDaiSoDuong(page)+chieuDaiSoDuong(maxpage))/2,y+24+1);
	cout << "---" << page << "/" << maxpage << "---";
}
// ============================ CHECK MA MAY BAy ============================
bool isExistMB(listMayBay &ds,string SoHieu)
{
	for (int i = 0; i < ds.n; i++)
	{
		if (ds.list[i]->SoHieu == SoHieu) return 1;
	}
	return 0;
}
// ================================ THEM MAY BAY ===========================
void themMayBay(listMayBay &ds)
{
	if (ds.n == 300)
	{
		cout << "Danh sach day!";
		return;
	}
	
	int maxpage;
	int curpage = 1;
	if (ds.n % 10 == 0) maxpage = ds.n/10;
	else maxpage = ds.n/10 + 1;
	
	string SoHieu;
	string Loai;
	string socho;
	gotoxy(50,0);
	showDSMB(ds,1,50,0,maxpage);
	gotoxy(0,8);
	cout << "So hieu: ";
	gotoxy(0,11);
	cout << "Loai: ";
	gotoxy(0,14);
	cout << "So cho: ";
	gotoxy(25-2,20);
	cout << "LUU";
	gotoxy(10+SoHieu.length(),8);
	hienConTro();

	int cur = 0;	
	char c;
	bool kytu;
	pressKey(c,kytu);
	if (c == 27 && !isExit(c,kytu))
	{
		gotoxy(0,8);
		cout << "So hieu: ";
		gotoxy(0,11);
		cout << "Loai: ";
		gotoxy(0,14);
		cout << "So cho: ";
		gotoxy(25-2,20);
		cout << "LUU";
		gotoxy(10+SoHieu.length(),8);
		hienConTro();
	}
	while (c != 27)
	{
		if (c == UP && !kytu) // UP
		{
			if (cur > 0)
			{
				cur--;
				switch(cur)
				{
					case 0: // So hieu
						{
							gotoxy(10+SoHieu.length(),8);
							break;
						}
					case 1: // Loai
						{
							gotoxy(7+Loai.length(),11);
							break;
						}
					case 2: // So cho
						{
							anConTro();
							gotoxy(25-2,20);
							changeColor(15);
							cout << "LUU";
							gotoxy(9+socho.length(),14);
							hienConTro();
							break;
						}
				}
			}
		}
		if (c == DOWN && !kytu) // DOWN
		{
			if (cur < 3)
			{
				cur++;
				switch(cur)
				{
					case 1: // Loai
						{
							gotoxy(7+Loai.length(),11);
							hienConTro();
							break;
						}
					case 2: // So cho
						{
							gotoxy(9+socho.length(),14);
							hienConTro();
							break;
						}
					case 3: // LUU
						{
							anConTro();
							gotoxy(25-2,20);
							changeColor(12);
							cout << "LUU";
							break;
						}
				}
			}
		}
		if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) && kytu) // a->z, A->Z
		{
			switch (cur)
			{
				case 0: // Khong qua 7 ky tu
					{
						if (SoHieu.length() < 7)
						{
							cout << inHoa(c);
							SoHieu = SoHieu + inHoa(c);
						}
						break;
					}
				case 1: // Khong qua 7 ky tu
					{
						if (Loai.length() < 10)
						{
							cout << inHoa(c);
							Loai = Loai + inHoa(c);
						}
						break;
					}
			}
		}
		if ((c >= 48 && c <= 57) && kytu)
		{
			switch (cur)
			{
				case 0:
					{
						if (SoHieu.length() < 7)
						{
							cout << c;
							SoHieu = SoHieu + c;
						}
						break;
					}
				case 1:
					{
						if (Loai.length() < 10)
						{
							cout << c;
							Loai = Loai + c;
						}
						break;
					}
				case 2:
					{
						if (c == 48)
						{
							if (!(convertToInt(socho) == 0 || socho.length() == 0))
							{
								if (socho.length() < 4)
								{
									cout << c;
									socho = socho + c;
								}
							}
						}
						else
						{
							if (socho.length() < 3)
								{
									cout << c;
									socho = socho + c;
								}
						}
						break;
					}
			}
		}
		if (c == BACKSPACE) // Backspace
		{
			switch (cur)
			{
				case 0:
					{
						if (SoHieu.length() > 0)
						{
							anConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							SoHieu.erase(SoHieu.length()-1);
							gotoxy(wherex()-1,wherey());
							hienConTro();
						}
						break;
					}
				case 1:
					{
						if (Loai.length() > 0)
						{
							anConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							Loai.erase(Loai.length()-1);
							gotoxy(wherex()-1,wherey());
							hienConTro();
						}
						break;
					}
				case 2:
					{
						if (socho.length() > 0)
						{
							anConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							socho.erase(socho.length()-1);
							gotoxy(wherex()-1,wherey());
							hienConTro();
						}
						break;
					}
			}
		}
		if (c == ENTER) // Enter
		{
			if (cur == 3)
			{
				if (SoHieu.length() == 0)
				{
					anConTro();
					changeColor(15);
					gotoxy(0,30);
					cout << "Khong de trong So Hieu";
					Sleep(1500);
					gotoxy(0,30);
					cout << "                      ";
					
					gotoxy(25-2,20);
					changeColor(15);
					cout << "LUU";
					
					gotoxy(10,8);
					hienConTro();
					cur = 0;
				}
				else
				{
					if (isExistMB(ds,SoHieu))
					{
						anConTro();
						gotoxy(0,30);
						changeColor(15);
						cout << "So hieu trung. Vui long kiem tra lai";
						Sleep(1500);
						gotoxy(0,30);
						cout << "                                    ";
						
						gotoxy(25-2,20);
						changeColor(15);
						cout << "LUU";
						
						gotoxy(10+SoHieu.length(),8);
						hienConTro();
						cur = 0;
					}
					else // check Loai
					{
						if (Loai.length() == 0)
						{
							anConTro();
							gotoxy(0,30);
							changeColor(15);
							cout << "Khong de trong loai may bay";
							Sleep(1500);
							gotoxy(0,30);
							cout << "                           ";
							
							gotoxy(25-2,20);
							changeColor(15);
							cout << "LUU";
							
							gotoxy(7,11);
							hienConTro();
							cur = 1;
						}
						else // check so cho
						{
							if (socho.length() == 0)
							{
								anConTro();
								gotoxy(0,30);
								changeColor(15);
								cout << "Khong de trong so cho";
								Sleep(1500);
								gotoxy(0,30);
								cout << "                     ";
								
								gotoxy(25-2,20);
								changeColor(15);
								cout << "LUU";
								
								gotoxy(9,14);
								hienConTro();
								cur = 2;
							}
							else
							{
								if (convertToInt(socho) < 20)
								{
									anConTro();
									gotoxy(0,30);
									changeColor(15);
									cout << "So cho phai lon hon 20";
									Sleep(1500);
									gotoxy(0,30);
									cout << "                      ";
									
									gotoxy(25-2,20);
									changeColor(15);
									cout << "LUU";
									
									gotoxy(9+socho.length(),14);
									hienConTro();
									cur = 2;
									
								}
								else // LUU
								{
									ds.list[ds.n] = new MayBay;
									ds.list[ds.n]->SoHieu = SoHieu;
									ds.list[ds.n]->Loai = Loai;
									ds.list[ds.n]->socho = convertToInt(socho);
									ds.n++;
									
									if (ds.n % 10 == 0) maxpage = ds.n/10;
									else maxpage = ds.n/10 + 1;
									gotoxy(50,0);
									showDSMB(ds,maxpage,50,0,maxpage);
									
									anConTro();
									gotoxy(25-2,20);
									cout << "LUU";
									
									SoHieu = "";
									Loai = "";
									socho = "";
									gotoxy(10,8);
									cout << "         ";
									gotoxy(7,11);
									cout << "            ";
									gotoxy(9,14);
									cout << "     ";
									gotoxy(10,8);
									hienConTro();
									cur = 0;
									
								}	
							}
						}
					}
				}
			}
		}
		pressKey(c,kytu);
		if (c == 27)
		{
			if (!isExit(c,kytu))
			{
				switch (cur)
				{
					case 0:
						{
							gotoxy(10+SoHieu.length(),8);
							hienConTro();
							break;
						}
					case 1:
						{
							gotoxy(7+Loai.length(),11);
							hienConTro();
							break;
						}
					case 2:
						{
							gotoxy(9+socho.length(),14);
							hienConTro();
							break;
						}
				}
			}
			else return;
		}
	}
}
#endif
