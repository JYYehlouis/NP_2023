#include <iostream>
#include "TCPIP_Sync.h"
#include <windows.h> //for gotoxy()
#include <conio.h>

#define W 52	  //棋盤寬
#define H 32	  //棋盤高
int T[W][H] = {}; //紀錄棋盤狀態， 0x00:未下子

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void Check3()
{
	int x, y, z, n, m, p, ax, ay;
	int T1[2] = { 'O', 'X' };
	int V[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	int count = 0;
	for (z = 0; z < 2; z++)
		for (y = 0; y < H; y += 2)
			for (x = 0; x < W; x += 2)
				for (m = 0; m < 4; m++)
				{
					n = 0;
					ax = x + V[m][0] * n;
					ay = y + V[m][1] * n;
					if ((ax < 0) || (ax >= W) || (ay < 0) || (ay >= W) || (T[ax][ay] != 0))
						continue;
					for (n = 2; n < 8; n += 2)
					{
						ax = x + V[m][0] * n;
						ay = y + V[m][1] * n;
						if ((ax < 0) || (ax >= W) || (ay < 0) || (ay >= W) || (T[ax][ay] != T1[z]))
							break;
					}
					if (n == 8)
					{
						ax = x + V[m][0] * n;
						ay = y + V[m][1] * n;
						if ((ax < 0) || (ax >= W) || (ay < 0) || (ay >= W) || (T[ax][ay] != 0))
							continue;
						count++;
					}
				}
	if (count >= 1)
	{
		gotoxy(0, H);
		printf("%c:活三", T1[z]);
	}
}
void Check4()
{
	int x, y, z, n, m, p, ax, ay;
	int T1[2] = { 'O', 'X' };
	int V[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	int count = 0;
	for (z = 0; z < 2; z++)
		for (y = 0; y < H; y += 2)
			for (x = 0; x < W; x += 2)
				for (m = 0; m < 4; m++)
				{
					n = 0;
					ax = x + V[m][0] * n;
					ay = y + V[m][1] * n;
					if ((ax < 0) || (ax >= W) || (ay < 0) || (ay >= W) || (T[ax][ay] != 0))
						continue;
					for (n = 2; n < 10; n += 2)
					{
						ax = x + V[m][0] * n;
						ay = y + V[m][1] * n;
						if ((ax < 0) || (ax >= W) || (ay < 0) || (ay >= W) || (T[ax][ay] != T1[z]))
							break;
					}
					if (n == 10)
					{
						ax = x + V[m][0] * n;
						ay = y + V[m][1] * n;
						if ((ax < 0) || (ax >= W) || (ay < 0) || (ay >= W) || (T[ax][ay] != 0))
							continue;
						count++;
					}
				}
	if (count >= 1)
	{
		gotoxy(0, H);
		printf("%c:活四", T1[z]);
	}

}
void Check5()
{
	int x, y, z, n, m, p, ax, ay;
	int T1[2] = { 'O', 'X' };
	int V[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

	for (z = 0; z < 2; z++)
		for (y = 0; y < H; y += 2)
			for (x = 0; x < W; x += 2)
				for (m = 0; m < 4; m++)
				{
					for (n = 0; n < 10; n += 2)
					{
						ax = x + V[m][0] * n;
						ay = y + V[m][1] * n;
						if ((ax < 0) || (ax >= W) || (ay < 0) || (ay >= W) || (T[ax][ay] != T1[z]))
							break;
					}
					if (n >= 10)
					{
						gotoxy(0, H);
						printf("%c:五子棋連線", T1[z]);
					}
				}
}

void Check() {
	Check3();
	Check4();
	Check5();
}
SOCKET SSock, CSock, Sock;
int F = 0; // 0:Ready, 1:Client, 2:Server

void SFun(PVOID p)
{ // Server Mode:處理遠端連入
	sockaddr_in Addr;
	char S1[2000];
	int i, x, y, Len = sizeof(sockaddr);
	Sock = accept(SSock, (sockaddr*)&Addr, &Len);
	F = 2; //接受連線
	gotoxy(0, H);
	printf("遠端(%s)連入", inet_ntoa(Addr.sin_addr));
	while (1)
	{
		i = recv(Sock, S1, sizeof(S1) - 1, 0);
		if (i > 0)
		{
			S1[i] = 0;
			i = sscanf_s(S1, "(%d-%d)", &x, &y); //解析下棋位置
			if (i == 2)
			{
				gotoxy(x, y);
				printf("X");
				T[x][y] = 'X';
				Check();
			}
			else if (i < 0)
			{
				gotoxy(0, H);
				printf("遠端離線");
				break;
			}
		}
	}
}

void CFun(PVOID p)
{ // Client Mode:處理遠端連入
	sockaddr Addr;
	char S1[2000];
	int i, x, y, Len = sizeof(sockaddr);
	while (1)
	{
		i = recv(CSock, S1, sizeof(S1) - 1, 0);
		if (i > 0)
		{
			S1[i] = 0;							 // gotoxy(0, H);
			i = sscanf_s(S1, "(%d-%d)", &x, &y); //解析下棋位置
			if (i == 2)
			{
				gotoxy(x, y);
				printf("X");
				T[x][y] = 'X';
				Check();
			}
			else if (i < 0)
			{
				gotoxy(0, H);
				printf("遠端離線");
				break;
			}
		}
	}
}

int main()
{
	int x, y, z, x1, y1, t;
	char IP[100], S1[50];
	// 1.繪製遊戲框
	for (y = 0; y < H; y++)
		for (x = 0; x < W; x++)
		{
			gotoxy(x, y);
			x1 = x % 2;
			y1 = y % 2;
			if (x1 && y1)
				printf("+");
			else if ((!x1) && y1)
				printf("-");
			else if (x1 && (!y1))
				printf("|");
		}
	// 2.啟動TCP Server(等待遠端連入，Thread)
	Start_TCP_Server(&SSock, 6000);
	_beginthread(SFun, 0, 0); //處理接待客人連入
	// 3.讀取鍵盤，處理:連線、下棋、分析、顯示...
	unsigned char c;
	int cx = W / 2, cy = H / 2; //游標初始位置(中央)
	do
	{
		gotoxy(cx, cy);
		c = _getch();
		// 1.移動游標
		if (c == 0x48)
			cy -= 2; //上
		else if (c == 0x50)
			cy += 2; //下
		else if (c == 0x4b)
			cx -= 2; //左
		else if (c == 0x4d)
			cx += 2; //右
		if (cx < 0)
			cx = W - 2;
		else if (cx >= W)
			cx = 0;
		if (cy < 0)
			cy = H - 2;
		else if (cy >= H)
			cy = 0;
		// 2.下棋
		if (c == 0x0d)
		{
			printf("O"); // Enter
			T[cx][cy] = 'O';
			sprintf_s(S1, "(%d-%d)", cx, cy);
			send(Sock, S1, strlen(S1), 0); //送出下棋位置
		}
		// 3.找人玩
		else if ((c == 'c') || (c == 'C'))
		{
			gotoxy(0, H);
			printf("IP=");
			scanf_s("%s", IP, 99);
			Start_TCP_Client(&CSock, 6000, IP);
			F = 1;
			_beginthread(CFun, 0, 0);
			Sock = CSock;
		}
		// 4.
		Check();
	} while ((c != 'q') && (c != 'Q'));
	gotoxy(0, H);
	printf("遊戲結束\n");
	closesocket(SSock);
	if (F >= 1)
		closesocket(Sock); //關閉終端連線
}

