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
	int gio = 0;
	int ngay = 0;
	int thang = 0;
	int nam = 0;
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
	int n = 0;
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
// ============================== SO CHO MAY BAY ===========================================
int soChoMayBay(listMayBay &ds, string SoHieu)
{
	for (int i = 0; i  < ds.n; i++)
	{
		if (ds.list[i]->SoHieu == SoHieu) return ds.list[i]->socho;
	}
	return 0;
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
bool loadFileCB(listChuyenBay &ds, listMayBay dsmb)
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
		infile >> date.gio;
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
			ds.Head->chuyenbay.ticket = new Ve[soChoMayBay(dsmb,SoHieu)];
			ds.Head->next = NULL;
			ds.n++;
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
			p->chuyenbay.ticket = new Ve[soChoMayBay(dsmb,SoHieu)];
			p->next = NULL;
			ds.n++;
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
	showDSMB(ds,maxpage,50,0,maxpage);
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
// ============================= GIAI PHONG BO NHO TRONG DANH SACH MAY BAY ==========================
void deleteMB(listMayBay &ds, int vitri)
{
/*	if (vitri == ds.n-1)
	{
		delete ds.list[vitri];
		ds.list[vitri] = 0;
		ds.n--;
		return;
	} */
	delete ds.list[vitri];
	ds.list[vitri] = NULL;
	for (int i = vitri; i < ds.n - 1; i++)
	{
		ds.list[i] = ds.list[i+1];
	}
	ds.list[ds.n-1] = NULL;
	ds.n--;
	return;
}
// ================================= XOA MAY BAY ====================================
void xoaMayBay(listMayBay &ds) // con thieu chuyen bay
{
	if(ds.n == 0) return;
	anConTro();
	gotoxy(10,0);
	int maxpage;
	if (ds.n % 10 == 0) maxpage = ds.n/10;
	else maxpage = ds.n/10 + 1;
	showDSMB(ds,1,10,0,maxpage);
	gotoxy(7,3);
	cout << "->";
	int cur = 0;
	char c;
	bool kytu;
	pressKey(c,kytu);
	while (c != 27)
	{
		if (c == UP && !kytu) // UP
		{
			if (cur > 0)
			{
				gotoxy(7,2*(cur%10)+3);
				cout << "  ";
				if(cur%10 == 0) 
				{
					gotoxy(10,0);
					showDSMB(ds,(cur-1)/10+1,10,0,maxpage);
				}
				cur--;
				gotoxy(7,2*(cur%10)+3);
				cout << "->";
			}
		}
		if (c == DOWN && !kytu) // DOWN
		{
			if (cur < ds.n-1)
			{
				gotoxy(7,2*(cur%10)+3);
				cout << "  ";
				if (cur%10 == 9) 
				{
					gotoxy(10,0);
					showDSMB(ds,(cur+1)/10+1,10,0,maxpage);
				}
				cur++;
				gotoxy(7,2*(cur%10)+3);
				cout << "->";
			}
		}
		if (c == ENTER)
		{
			gotoxy(0,30);
			cout << "Ban co chac chan muon xoa may bay co ma la: " << ds.list[cur]->SoHieu << "?" << endl;
			cout << "Nhan Y de XAC NHAN hoac nhan phim BAT KY de HUY";
			pressKey(c,kytu);
			if (inHoa(c) == 89 && kytu)
			{
				deleteMB(ds,cur);
				if (ds.n % 10 == 0) maxpage = ds.n/10;
				else maxpage = ds.n/10 + 1;
				gotoxy(7,2*(cur%10)+3);
				cout << "  ";
				cur = 0;
				gotoxy(10,0);
				showDSMB(ds,1,10,0,maxpage);
				gotoxy(7,3);
				cout << "->";
			}
			gotoxy(0,30);
			cout << "                                                           " << endl;
			cout << "                                                           ";
		}
		if(ds.n == 0) return;
		pressKey(c,kytu);
	}
}
// ================================ CHINH SUA MAY BAY ==========================
void chinhSuaMayBay(listMayBay &ds, int vitri) // thieu ds chuyen bay de cap nhat
{
	// sao chep thong tin goc
	MayBay *temp = new MayBay;
	temp->SoHieu = ds.list[vitri]->SoHieu;
	temp->Loai = ds.list[vitri]->Loai;
	temp->socho = ds.list[vitri]->socho;
	
	int maxpage;
	int curpage = 1;
	if (ds.n % 10 == 0) maxpage = ds.n/10;
	else maxpage = ds.n/10 + 1;
	
	string socho = convertToString(temp->socho);
	gotoxy(50,0);
	showDSMB(ds,maxpage,50,0,maxpage);
	gotoxy(0,8);
	cout << "So hieu:  " << temp->SoHieu;
	gotoxy(0,11);
	cout << "Loai:  " << temp->Loai;
	gotoxy(0,14);
	cout << "So cho:  " << temp->socho;
	gotoxy(25-2,20);
	cout << "LUU";
	gotoxy(10+temp->SoHieu.length(),8);
	hienConTro();

	int cur = 0;	
	char c;
	bool kytu;
	pressKey(c,kytu);
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
							gotoxy(10+temp->SoHieu.length(),8);
							break;
						}
					case 1: // Loai
						{
							gotoxy(7+temp->Loai.length(),11);
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
							gotoxy(7+temp->Loai.length(),11);
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
						if (temp->SoHieu.length() < 7)
						{
							cout << inHoa(c);
							temp->SoHieu = temp->SoHieu + inHoa(c);
						}
						break;
					}
				case 1: // Khong qua 7 ky tu
					{
						if (temp->Loai.length() < 10)
						{
							cout << inHoa(c);
							temp->Loai = temp->Loai + inHoa(c);
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
						if (temp->SoHieu.length() < 7)
						{
							cout << c;
							temp->SoHieu = temp->SoHieu + c;
						}
						break;
					}
				case 1:
					{
						if (temp->Loai.length() < 10)
						{
							cout << c;
							temp->Loai = temp->Loai + c;
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
						if (temp->SoHieu.length() > 0)
						{
							anConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							temp->SoHieu.erase(temp->SoHieu.length()-1);
							gotoxy(wherex()-1,wherey());
							hienConTro();
						}
						break;
					}
				case 1:
					{
						if (temp->Loai.length() > 0)
						{
							anConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							temp->Loai.erase(temp->Loai.length()-1);
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
				if (temp->SoHieu.length() == 0)
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
					if (isExistMB(ds,temp->SoHieu) && temp->SoHieu != ds.list[vitri]->SoHieu)
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
						
						gotoxy(10+temp->SoHieu.length(),8);
						hienConTro();
						cur = 0;
					}
					else // check Loai
					{
						if (temp->Loai.length() == 0)
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
									temp->socho = convertToInt(socho);
									delete ds.list[vitri];
									ds.list[vitri] = temp;
									gotoxy(0,30);
									cout << "Sua thong tin thanh cong!";
									Sleep(1500);
									return;
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
							gotoxy(10+temp->SoHieu.length(),8);
							hienConTro();
							break;
						}
					case 1:
						{
							gotoxy(7+temp->Loai.length(),11);
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
// ========================= CHON MAY BAY DE CHINH SUA ======================
void chonChinhSua(listMayBay &ds)
{
	changeColor(15);
	anConTro();
	system("cls");
	if (ds.n == 0)
	{
		cout << "Danh sach rong !" << endl;
		system("pause");
		return;
	}
	int maxpage;
	if (ds.n%10 == 0) maxpage = ds.n/10;
	else maxpage = ds.n/10 + 1;
	
	gotoxy(10,0);
	showDSMB(ds,1,10,0,maxpage);
	gotoxy(7,3);
	cout << "->";
	char c;
	bool kytu;
	pressKey(c,kytu);
	int vitri = 0;
	while (c != 27)
	{
		if (c == UP && !kytu)
		{
			if (vitri > 0)
			{
				gotoxy(7,2*(vitri%10) + 3);
				cout << "  ";
				if (vitri%10 == 0)
				{
					gotoxy(10,0);
					showDSMB(ds,vitri/10,10,0,maxpage);
				}
				vitri--;
				gotoxy(7,2*(vitri%10) + 3);
				cout << "->";
			}
		}
		if (c == DOWN && !kytu)
		{
			if (vitri < ds.n-1)
			{
				gotoxy(7,2*(vitri%10) + 3);
				cout << "  ";
				if (vitri%10 == 9)
				{
					gotoxy(10,0);
					showDSMB(ds,(vitri+1)/10 + 1,10,0,maxpage);
				}
				vitri++;
				gotoxy(7,2*(vitri%10) + 3);
				cout << "->";
			}
		}
		if (c == ENTER)
		{
			system("cls");
			chinhSuaMayBay(ds,vitri);
			system("cls");
			
			gotoxy(10,0);
			showDSMB(ds,vitri/10+1,10,0,maxpage);
			gotoxy(7,2*(vitri%10) + 3);
			cout << "->";
		}
		pressKey(c,kytu);
	}
}
// ============================ IN DANH SACH CHUYEN BAY ======================================
void showDSCB(listChuyenBay &ds, int page, int x, int y, int maxpage)
{
	changeColor(15);
	gotoxy(x,y);
	veKhungCB(30,100);
	gotoxy(x+10-7,y+1);
	cout << "Ma chuyen bay";
	gotoxy(x+30-4,y+1);
	cout << "So hieu";
	gotoxy(x+50-7,y+1);
	cout << "Ngay khoi hanh";
	gotoxy(x+70-2,y+1);
	cout << "Den";
	gotoxy(x+90-5,y+1);
	cout << "Trang thai";
	
	int k = 0;
	string ngay;
	string thang;
	string nam;
	for (nodeChuyenBay *p = ds.Head; p != NULL; p = p->next)
	{
		if (k/10 + 1 < page) continue;
		if (k/10 + 1 > page) break;
		gotoxy(x+10-p->chuyenbay.MaCB.length()/2,2*k+3);
		cout << p->chuyenbay.MaCB;
		gotoxy(x+30-p->chuyenbay.SoHieu.length()/2,2*k+3);
		cout << p->chuyenbay.SoHieu;
		ngay = convertToString(p->chuyenbay.NgayKhoiHanh.ngay);
		thang = convertToString(p->chuyenbay.NgayKhoiHanh.thang);
		nam = convertToString(p->chuyenbay.NgayKhoiHanh.nam);
		gotoxy(x+50-(ngay.length()+thang.length()+nam.length()+2+4)/2,2*k+3);
		if (p->chuyenbay.NgayKhoiHanh.gio < 10) cout << "0";
		cout << p->chuyenbay.NgayKhoiHanh.gio << "h " << ngay << "/" << thang << "/" << nam;
		gotoxy(x+70-p->chuyenbay.Den.length()/2,2*k+3);
		for (int i = 0; i < p->chuyenbay.Den.length(); i++)
		{
			if (p->chuyenbay.Den[i] != '-') cout << p->chuyenbay.Den[i];
			else cout << " ";
		}
		switch (p->chuyenbay.trangthai)
		{
			case 0:
				{
					gotoxy(x+90-5,2*k+3);
					cout << "Huy chuyen";
					break;
				}
			case 1:
				{
					gotoxy(x+90-3,2*k+3);
					cout << "Con ve";
					break;
				}
			case 2:
				{
					gotoxy(x+90-3,2*k+3);
					cout << "Het ve";
					break;
				}
			case 3:
				{
					gotoxy(x+90-4,2*k+3);
					cout << "Hoan tat";
					break;
				}
		}
		k++;
	}
	gotoxy(x+50-(6+3)/2,y+31);
	cout << "---" << page << "/" << maxpage << "---";
}
// ============================== THEM CHUYEN BAY ===================================
void themChuyenBay(listChuyenBay &ds, listMayBay mb)
{
	int maxpage;
	if (ds.n%10 == 0) maxpage = ds.n/10;
	else maxpage = ds.n/10 + 1;
	anConTro();
	showDSCB(ds,maxpage,50,0,maxpage);
	
	int maxpageMB;
	int curpage = 1;
	if (mb.n%10 == 0) maxpageMB = mb.n/10;
	else maxpageMB = mb.n/10+1;
	anConTro();
	gotoxy(150,0);
	showDSMB(mb,1,150,0,maxpageMB);
	
	gotoxy(0,1);
	cout << "Ma chuyen bay: ";
	gotoxy(0,5);
	cout << "So hieu: ";
	gotoxy(0,9);
	cout << "Ngay khoi hanh: " << "00h 00/00/0";
	gotoxy(3,11);
	cout << "Gio: " << "00";
	gotoxy(3,13);
	cout << "Ngay: " << "00";
	gotoxy(3,15);
	cout << "Thang: " << "00";
	gotoxy(3,17);
	cout << "Nam: " << "0";
	gotoxy(0,21);
	cout << "Noi den: ";
	gotoxy(0,25);
	cout << "Trang thai: 1"; 
	gotoxy(23,29);
	cout << "LUU";
	gotoxy(16,1);
	int cur = 0;
	hienConTro();
	
	string MaChuyen;
	string SoHieu;
	Ngay date;
	string NoiDen;
	int trangthai = 1;
	char c;
	bool kytu;
	pressKey(c,kytu);
	while (c != 27) // Escap
	{
		if (c == UP && !kytu) // UP 
		{
			if (cur > 0)
			{
				cur--;
				switch(cur)
				{
					case 0: // Ma chuyen
						{
							gotoxy(16+MaChuyen.length(),1);
							break;
						}
					case 1: // So hieu
						{
							gotoxy(9+SoHieu.length(),5);
							break;
						}
					case 2: // Gio
						{
							gotoxy(5+3+2,11);
							break;
						}
					case 3: // Ngay
						{
							gotoxy(6+3+2,13);
							break;
						}
					case 4: // Thang
						{
							gotoxy(7+3+2,15);
							break;
						}
					case 5: // Nam
						{
							gotoxy(5+3+chieuDaiSoDuong(date.nam),17); 
							break;
						}
					case 6: // Noi den
						{
							gotoxy(9+NoiDen.length(),21);
							break;
						}
					case 7: // Trang thai
						{
							anConTro();
							changeColor(15);
							gotoxy(23,29);
							cout << "LUU";
							gotoxy(12+1,25);
							hienConTro();
							break;
						}
				}
			}
		}
		if (c == DOWN && !kytu)
		{
			if (cur < 8)
			{
				cur++;
				switch(cur)
				{
					case 8: // Ma chuyen
						{
							anConTro();
							changeColor(12);
							gotoxy(23,29);
							cout << "LUU";
							break;
						}
					case 1: // So hieu
						{
							gotoxy(9+SoHieu.length(),5);
							break;
						}
					case 2: // Gio
						{
							gotoxy(5+3+2,11);
							break;
						}
					case 3: // Ngay
						{
							gotoxy(6+3+2,13);
							break;
						}
					case 4: // Thang
						{
							gotoxy(7+3+2,15);
							break;
						}
					case 5: // Nam
						{
							gotoxy(5+3+chieuDaiSoDuong(date.nam),17); 
							break;
						}
					case 6: // Noi den
						{
							gotoxy(9+NoiDen.length(),21);
							break;
						}
					case 7: // Trang thai
						{
							gotoxy(12+1,25);
							break;
						}
				}
			}
		}
		if (c == LEFT && !kytu)
		{
			if (curpage > 1)
			{
				anConTro();
				curpage--;
				gotoxy(150,0);
				showDSMB(mb,curpage,150,0,maxpageMB);
				hienConTro();
				switch(cur)
				{
					case 0: // Ma chuyen
						{
							gotoxy(16+MaChuyen.length(),1);
							break;
						}
					case 1: // So hieu
						{
							gotoxy(9+SoHieu.length(),5);
							break;
						}
					case 2: // Gio
						{
							gotoxy(5+3+2,11);
							break;
						}
					case 3: // Ngay
						{
							gotoxy(6+3+2,13);
							break;
						}
					case 4: // Thang
						{
							gotoxy(7+3+2,15);
							break;
						}
					case 5: // Nam
						{
							gotoxy(5+3+chieuDaiSoDuong(date.nam),17); 
							break;
						}
					case 6: // Noi den
						{
							gotoxy(9+NoiDen.length(),21);
							break;
						}
					case 7: // Trang thai
						{
							gotoxy(12+1,25);
							hienConTro();
							break;
						}
					case 8: // Ma chuyen
						{
							anConTro();
							changeColor(12);
							gotoxy(23,29);
							cout << "LUU";
							break;
						}	
				}
			}
		}
		if (c == RIGHT && !kytu)
		{
			if (curpage < maxpageMB)
			{
				anConTro();
				curpage++;
				gotoxy(150,0);
				showDSMB(mb,curpage,150,0,maxpageMB);
				hienConTro();
				switch(cur)
				{
					case 0: // Ma chuyen
						{
							gotoxy(16+MaChuyen.length(),1);
							break;
						}
					case 1: // So hieu
						{
							gotoxy(9+SoHieu.length(),5);
							break;
						}
					case 2: // Gio
						{
							gotoxy(5+3+2,11);
							break;
						}
					case 3: // Ngay
						{
							gotoxy(6+3+2,13);
							break;
						}
					case 4: // Thang
						{
							gotoxy(7+3+2,15);
							break;
						}
					case 5: // Nam
						{
							gotoxy(5+3+chieuDaiSoDuong(date.nam),17); 
							break;
						}
					case 6: // Noi den
						{
							gotoxy(9+NoiDen.length(),21);
							break;
						}
					case 7: // Trang thai
						{
							gotoxy(12+1,25);
							hienConTro();
							break;
						}
					case 8: // Ma chuyen
						{
							anConTro();
							changeColor(12);
							gotoxy(23,29);
							cout << "LUU";
							break;
						}	
				}
			}
		}
		pressKey(c,kytu);
	}
}
#endif
