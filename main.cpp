#include<iostream>
#include "object.h"
using namespace std;
int main()
{
	fullscreen();
	listMayBay maybay;
	listChuyenBay chuyenbay;
	listKhachHang khachhang;
	if (!loadFileMB(maybay))
	{
		cout << "Khong the load file danh sach may bay! Vui long kiem tra lai" << endl;
		system("pause");
		return 0;
	}
	if (!loadFileCB(chuyenbay))
	{
		cout << "Khong the load file danh sach chuyen bay! Vui long kiem tra lai" << endl;
		system("pause");
		return 0;
	}
	if (!loadFileKH(khachhang))
	{
		cout << "Khong the load file danh sach khach hang! Vui long kiem tra lai" << endl;
		system("pause");
		return 0;
	}
	while (1)
	{
		switch(mainMenu())
		{
			case 0: // Them may bay
				{
					changeColor(15);
					system("cls");
					themMayBay(maybay);
					break;
				}
			case 1: // Xoa may bay
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case 2: // Sua may bay
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case 3:
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case 4:
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case 5:
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case 6:
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case 7:
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case 8:
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case 9:
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case 10:
				{
					changeColor(15);
					system("cls");
					system("pause");
					break;
				}
			case -1:
				{
					changeColor(15);
					system("cls");
					return 0;
				}
		}
	}
}
