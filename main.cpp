#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include "Resource.h"
#include <time.h>
#include <math.h>

void OnTimer(HWND hwnd);
int bird(HWND hwnd,int x,int y,int wing,int xO);
void OnCreate(HWND hwnd);
void OnDestroy(HWND hwnd);
void OnLButton(HWND hwnd);
void OnTimer2(HWND hwnd);
void pipe(HWND hwnd,int len,int di,int x);
int MOD(int,int);
void OnPaint(HWND hwnd,int x0,int y0,int x1,int y1);
int check(int b_pos,int rec_x,int rec_len,int rec_di);


#define BRUSH(x,y,z) { hbr = CreateSolidBrush ( RGB (x, y, z ) ) ;\
 holdbr = SelectObject ( hdc, hbr ) ;\
}
#define DEL_BRUSH { SelectObject ( hdc, holdbr ) ;\
 DeleteObject ( hbr ) ;\
}

#define DEGREE *3.14/180
#define g 0.03
#define S_SIZE 700
#define S_WIDTH 800
#define b_wid 40
#define b_hi 17*2
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    extern HINSTANCE hInst;
    hInst=hThisInstance;
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1000,                 /* The programs width */
           1000,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            OnCreate(hwnd);
            break;
        case WM_LBUTTONDOWN:
            OnLButton(hwnd);
            break;
   //     case WM_PAINT:
     //       OnPaint(hwnd);
       //     break;
        case WM_TIMER:
    //        if(wParam==2)
      //          OnTimer2(hwnd);
      //      else
            OnTimer(hwnd);
            break;
        case WM_DESTROY:
            OnDestroy(hwnd);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

float F=0;

void OnLButton(HWND hwnd)
{
    F=7*g; //10

}

void OnDestroy(HWND hwnd)
{
    KillTimer(hwnd,1);
    PostQuitMessage (0);
}


void OnCreate(HWND hwnd)
{
    extern int len;



    SetTimer(hwnd,1,100,NULL);

    srand ( time ( NULL ) *time(NULL)*time(NULL)*time(NULL)*time(NULL)) ;

    len=rand()%650;
  //  SetTimer(hwnd,2,1000,NULL);
}

//void OnTimer2(HWND hwnd)/
//{
  //  amp=20;
//}

void OnPaint(HWND hwnd,int x0,int y0,int x1,int y1)
{
 extern HINSTANCE hInst;
 HDC hdc ;
 HBITMAP hbmp ;
 HBRUSH hbr;
 HPEN hpen ;
 HGDIOBJ holdpen ;
 //HDC hmemdc ;
 HGDIOBJ holdbmp ;
// PAINTSTRUCT ps ;


 hdc = GetDC(hwnd) ;

 hbmp = LoadBitmap ( hInst, MAKEINTRESOURCE ( IDB_BITMAP1 ) ) ;
 hbr=CreatePatternBrush(hbmp);
 //hmemdc = CreateCompatibleDC ( hdc ) ;
 holdbmp = SelectObject ( hdc, hbr ) ;

 //BitBlt ( hdc, x0, y0, x1,y1, hmemdc, 0, 0, SRCCOPY ) ;




hpen = CreatePen ( PS_NULL, 0, RGB ( 255, 255, 255 ) ) ;
holdpen = SelectObject ( hdc, hpen ) ;














    Rectangle(hdc,x0,y0,x1,y1);

// EndPaint ( hwnd, &ps ) ;

 ReleaseDC(hwnd,hdc);
 SelectObject ( hdc, holdbmp ) ;
 DeleteObject ( hbr ) ;
 DeleteObject(hbmp);

SelectObject ( hdc, holdpen ) ;
DeleteObject ( hpen ) ;


 //DeleteDC ( hmemdc ) ;

 }

void OnTimer(HWND hwnd)
{
    HDC hdc=GetDC(hwnd);
    static int i=1;//i0=0;
    //static int pos=0;
  //  static int k=-1;
    static float x=0,xO=0;
    static float u=0;
    extern int len;
    static int p2=0, len2=0,p3=0,len3=0,p4=0,len4=0;
    static int start=0;
    extern int p_wid;
    int x1,x2,x3,x4;
    static float speed=0;

    if(i==1)
        OnPaint(hwnd,0,0,S_WIDTH+100+120, S_SIZE);

 //   Rectangle(hdc,0,0,1000,1000);
 //   OnPaint(hwnd,0,0,S_WIDTH+100, S_SIZE);

    u=u+(g-F)*10;
    x=x+u*10+g/2*100;

    if(x<-300)x=-299,u=0;

    if(F!=0)
        F/=2;


    bird(hwnd,500,300+x,i,300+xO);

    if(i==S_WIDTH/5+20)
        srand (time(NULL)*time(NULL)) , len=rand()%(S_SIZE-200);

    x1=MOD((S_WIDTH-(i-20)*5),S_WIDTH+1);
    pipe(hwnd,20+len,start,x1);
    if((500+b_wid>x1&&500+b_wid<x1+p_wid)||(500-b_wid>x1&&500-b_wid<x1+p_wid))
            if(check(300+x,x1,20+len,start)==1)
                KillTimer(hwnd,1);

    if(i==S_WIDTH/5+60)
        srand (time(NULL)*time(NULL)) , len2=rand()%(S_SIZE-200);

    if(i%60==0||p2==1){
        x2=MOD((S_WIDTH-(i-60)*5),S_WIDTH+1);
        pipe(hwnd,40+len2,start+1,x2),p2=1;
        if((500+b_wid>x2&&500+b_wid<x2+p_wid)||(500-b_wid>x2&&500-b_wid<x2+p_wid))
            if(check(300+x,x2,40+len2,start+1)==1)
                KillTimer(hwnd,1);
    }
    else
        srand (time(NULL)*time(NULL)) , len2=rand()%(S_SIZE-200);

    if(i==S_WIDTH/5+100)
        srand (time(NULL)*time(NULL)) , len3=rand()%(S_SIZE-200);

    if(i%100==0||p3==1){
        x3=MOD((S_WIDTH-(i-100)*5),S_WIDTH+1);
        pipe(hwnd,40+len3,start,x3),p3=1;
        if((500+b_wid>x3&&500+b_wid<x3+p_wid)||(500-b_wid>x3&&500-b_wid<x3+p_wid))
            if(check(300+x,x3,40+len3,start)==1)
                KillTimer(hwnd,1);
    }
    else
        srand (time(NULL)*time(NULL)) , len3=rand()%(S_SIZE-200);

    if(i==S_WIDTH/5+140)
        srand (time(NULL)*time(NULL)) , len4=rand()%(S_SIZE-200);

    if(i%140==0||p4==1){
        x4=MOD((S_WIDTH-(i-140)*5),S_WIDTH+1);
        pipe(hwnd,40+len4,start+1,x4),p4=1;
        if((500+b_wid>x4&&500+b_wid<x4+p_wid)||(500-b_wid>x4&&500-b_wid<x4+p_wid))
            if(check(300+x,x4,40+len4,start+1)==1)
                KillTimer(hwnd,1);
    }
    else
        srand (time(NULL)*time(NULL)) , len4=rand()%(S_SIZE-200);


    xO=x;

    //printf("%d %d %d %d\n",,check(300+x,MOD((S_WIDTH-(i-50)*5),S_WIDTH+1),40+len2,start+1),check(300+x,MOD((S_WIDTH-(i-100)*5),S_WIDTH+1),40+len3,start),check(300+x,MOD((S_WIDTH-(i-140)*5),S_WIDTH+1),40+len4,start+1));
    printf("\n");
    i+=1+speed;
    //if(i%4==0)
        speed+=0.01;
    if(speed>=2)
        speed=2;
    ReleaseDC(hwnd,hdc);

}

int bird(HWND hwnd,int x,int y,int wing,int yO)
{
    HDC hdc=GetDC(hwnd);
    HBRUSH hbr;
    HGDIOBJ holdbr;
    //extern int wid=40,hi=17*2;



    OnPaint(hwnd,x-b_wid/2-b_wid/8,yO-b_hi/2-2,x+b_wid/2+b_wid/6+2,yO+b_hi/2+2);

    BRUSH(0,150,200)

    Ellipse(hdc,x-b_wid/2,y-b_hi/2,x+b_wid/2,y+b_hi/2);  //body

    DEL_BRUSH

    BRUSH(255,255,255)

    Ellipse(hdc,x,y-b_hi/2,x+b_wid/2-b_wid/10,y);            //aakh
    Ellipse(hdc,x+b_wid/4-2,y-b_hi/4-2,x+b_wid/4+2,y-b_hi/4+2);  //andh k ander ka dot

    DEL_BRUSH

    BRUSH(255,0,0)

    Ellipse(hdc,x,y+b_wid/6-2,x+b_wid/2+b_wid/6,y+b_wid/3);       //lip
    Ellipse(hdc,x,y,x+b_wid/2+b_wid/6,y+b_wid/6+2);

    DEL_BRUSH

    BRUSH(255,255,255)

    POINT points[]={{x-b_wid/2-b_wid/8,y-b_hi/3+wing%(b_hi/4)},{x-b_wid/8,y-b_hi/3+wing%(b_hi/4)},{x,y},{x-b_wid/2,y}};

    Polygon(hdc,points,4);                //wing

    DEL_BRUSH

    ReleaseDC(hwnd,hdc);

    if(y+b_hi/2>=S_SIZE)
        KillTimer(hwnd,1);

    return 0;
}

void pipe(HWND hwnd,int len,int di,int x)
{
    HDC hdc=GetDC(hwnd);
    HBRUSH hbr;
    HGDIOBJ holdbr;
    extern int p_wid;
    p_wid=60;

    OnPaint(hwnd,0,0,p_wid+7,S_SIZE);

    BRUSH(0,200,140)
        if(di==0) //UP
        {
            OnPaint(hwnd,x+p_wid,0,x+p_wid+p_wid,len+1);
            if(x>p_wid)
                Rectangle(hdc,x,0,x+p_wid,len);
        }
        else
        {
            OnPaint(hwnd,x+p_wid,S_SIZE-len,x+p_wid+p_wid,S_SIZE);
            if(x>p_wid)
                Rectangle(hdc,x,S_SIZE-len,x+p_wid,S_SIZE);
        }
    DEL_BRUSH

    OnPaint(hwnd,0,0,p_wid+7,S_SIZE);

    ReleaseDC(hwnd,hdc);
}

int MOD(int a,int b)
{
    while(a<0)
        a+=b;
    return a;
}

int check(int b_pos,int rec_x,int rec_len,int rec_di)
{

    extern int p_wid;
    int frot=500+b_wid/2 + b_wid/6;
    int bak =500-b_wid/2-b_wid/8;
    int top=b_pos-b_hi/2;
    int bottom=b_pos+b_hi/2;
    if(rec_x>frot){ //printf("bird behind ");
        return 0;}
    else if(rec_x+p_wid<bak){ //printf("Bird is aage ");
        return 0;}
    else if(rec_di==0&&top>rec_len){ //printf("Bird is niche ");
        return 0;}
    else if(rec_di!=0&&bottom<S_SIZE-rec_len){ //printf("Bird is upar ");
        return 0;}
   // printf("Bird is caught");
    return 1; //Touch
}

HINSTANCE hInst;
int len;
int p_wid;
