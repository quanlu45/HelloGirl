// hello.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "hello.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[]=_T("Hello,girl!");				// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HBITMAP Fire,Love,Flower; 
HDC hdc,mdc,mdc1,mdc2;
int i,j,count[6];
DWORD pretime,nowtime;
char str[]="from quan";

struct Font {

	int x;
	int y;
	int vx;
	int vy;
	
}f;
struct fireball
{
 int x;
 int y;
 int vx;
 int vy;
 int lasted;
 int color;
 bool exist;
};
struct Love
{
 int x;
 int y;
 int exist;
};
struct Flower{

	int x;
	int y;
	int wx;
	int wy;
}flower[7];


struct fireball fire[7][100];
struct Love love[6];


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void MyPaint(HDC hdc);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_HELLO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HELLO));

	// ����Ϣѭ��:
    GetMessage(&msg, NULL, 0, 0);
	while(msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else

		{
			nowtime=GetTickCount();
			if(nowtime-pretime>=25)
				MyPaint(hdc);
		}
	}

	return (int) msg.wParam;
}



 ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW| CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HELLO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(0);
	wcex.lpszMenuName	=NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   HBITMAP bmp,bmp1;
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   MoveWindow(hWnd,0,0,800,640,true);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //��ʼ��DC
   hdc=GetDC(hWnd);
   mdc=CreateCompatibleDC(hdc);
   mdc1=CreateCompatibleDC(hdc);
   mdc2=CreateCompatibleDC(hdc);
   bmp=CreateCompatibleBitmap(hdc,800,640);
   bmp1=CreateCompatibleBitmap(hdc,800,640);
   SelectObject(mdc,bmp);
   SelectObject(mdc2,bmp1);

   //����ͼƬ
   Fire=(HBITMAP)LoadImageA(NULL,"Fire.bmp",IMAGE_BITMAP,1200,5,LR_LOADFROMFILE);
   Love=(HBITMAP)LoadImageA(NULL,"love.bmp",IMAGE_BITMAP,102,79,LR_LOADFROMFILE);
   Flower=(HBITMAP)LoadImageA(NULL,"flower.bmp",IMAGE_BITMAP,143,164,LR_LOADFROMFILE);

 	//��ʼ��love
	for(i=0;i<6;i++)
	{
		love[i].exist=true;
		love[i].x=rand()%800;
		love[i].y=rand()%80+550;
	}
    //��ʼ���ʻ�
	int last=0;
	for(i=0;i<7;i++)
	{
		flower[i].wx=143;
		flower[i].wy=164;
		flower[i].x=i*rand()%200+last;
		last=flower[i].x;
		flower[i].y=460+rand()%50;
	}


	//��ʼ��count
	for(i=0;i<7;i++)
		count[i]=0;
	HFONT font;
	font=CreateFontA(40,40,5,5,1000,TRUE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,"����");
	SelectObject(mdc,font);

	
	f.x=0;
	f.y=0;
	f.vx=1;
	f.vy=1;
	SetTextColor(mdc,RGB(200,200,200));
	SetBkColor(mdc,RGB(0,0,0));
    
	 MyPaint(hdc);

   // ���ű�������
	mciSendStringA( "open ./bk.mp3 alias bk", 0, 0, 0 );
	mciSendStringA( "play bk repeat", 0, 0, 0 );
	
   DeleteObject(bmp);
   DeleteObject(bmp1);
   DeleteObject(font);
   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		if(wParam==VK_ESCAPE)
			PostQuitMessage(WM_DESTROY);
	    break;
	case WM_DESTROY:
		ReleaseDC(hWnd,hdc);
		DeleteDC(mdc);
		DeleteDC(mdc1);
		DeleteDC(mdc2);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void MyPaint(HDC hdc)
{   
	SelectObject(mdc1,Love);
	BitBlt(mdc,0,0,800,640,mdc1,0,0,BLACKNESS);
	
	//����
	TextOutA(mdc,f.x,f.y,str,strlen(str));
	f.x+=f.vx;
	f.y+=f.vy;
	if((f.x>=630&&f.vx>0)||(f.x<10&&f.vx<0))
		f.vx=-f.vx;
	if((f.y>460&&f.vy>0)||(f.y<10&&f.vy<0))
		f.vy=-f.vy;


	//����õ��
	SelectObject(mdc1,Flower);
	for(i=0;i<7;i++)
		BitBlt(mdc,flower[i].x,flower[i].y,flower[i].wx,flower[i].wy,mdc1,0,0,SRCPAINT);

	//���ϰ���
	SelectObject(mdc1,Love);
	for(i=0;i<6;i++)
		if(love[i].exist)
		{
			BitBlt(mdc,love[i].x,love[i].y,102,79,mdc1,0,0,SRCPAINT);
			if(love[i].y<=0) 
				{   if(rand()%10%2==0)
					  love[i].y=rand()%80+400;
				    else  love[i].y=rand()%100+300;
					love[i].x=rand()%800;
			     }
			else 	love[i].y-=2;
			if(love[i].y%2==0) love[i].x-=1;
			else love[i].x+=1;
		}
		
		//�ͷ��̻�
		SelectObject(mdc2,Fire);
		for(i=0;i<7;i++)
		if(!count[i])
		{
			int X,Y;
			X=rand()%800;
			Y=rand()%640;
			for(j=0;j<100;j++)
			{

				fire[i][j].x=X;
				fire[i][j].y=Y;
				fire[i][j].lasted=0;
				if(j%2==1) 
				{
					fire[i][j].vx+=rand()%10;
					fire[i][j].vy+=rand()%10;
				}
				if(j%2==2) 
				{
					fire[i][j].vx+=rand()%10;
					fire[i][j].vy-=rand()%10;
				}
				if(j%4==3) 
				{
					fire[i][j].vx-=rand()%10;
					fire[i][j].vy+=rand()%10;
				}
				if(j%2==1) 
				{
					fire[i][j].vx-=rand()%10;
					fire[i][j].vy-=rand()%10;
				}
				fire[i][j].exist=true;
			}
			count[i]=100;
		}
		
		//ˢ���̻�
		for(i=0;i<7;i++)
		 for(j=0;j<100;j++)
			 if(fire[i][j].exist)
			 {
			  BitBlt(mdc,fire[i][j].x,fire[i][j].y,4,4,mdc2,rand()%1200,0,SRCCOPY);
			  fire[i][j].x+=fire[i][j].vx;
			  fire[i][j].y+=fire[i][j].vy;
			  fire[i][j].lasted++;
			  if(fire[i][j].lasted>=50||fire[i][j].x<=2||fire[i][j].y<=2||fire[i][j].x>=796||fire[i][j].y>=636)
			  {
				  fire[i][j].exist=false;
				  count[i]--;
			  }
			 }
 
	BitBlt(hdc,0,0,800,640,mdc,0,0,SRCCOPY);
	pretime=GetTickCount();
}
