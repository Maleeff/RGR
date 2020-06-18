#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string>
//#define _WIN32_WINNT 0x0500

using namespace std;

void createaGraph(int a, int b ,POINT &op , HDC &hDC, int i);
void drawlines(POINT &op , HDC &hDC,int fromx1,int fromy1,int tox2,int toy2);
int searchPoints(int m, int n);
void draw(POINT &op , HDC &hDC ,int koord[][2],int svyazi[][2], int sv,int SIZE);
const int maxV=1000;
int i, j;
int n=5;
int GR[maxV][maxV];
void FU(int D[][maxV], int V);



int main(){
    int SIZE = 5; //Число вершин

    int koord[SIZE][2] = {{5,10},{2,7},{4,2},{1,9},{2,3}}; //Инициализация точек
    int sv = 3; //Число связей
    int svyazi[sv][2] = {{1,5},{5,4},{3,2}};
    int m1,n1;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("cls");

      // По умолчанию 0
  for (int i = 0; i<SIZE; i++)
  {
    for (int j = 0; j<SIZE; j++)
      GR[i][j] = 0;
  }

 // Инициализация матрицы связей
for (int i = 0; i<sv; i++)
{
    GR[svyazi[i][0]-1][svyazi[i][1]-1] = 1;
    GR[svyazi[i][1]-1][svyazi[i][0]-1] = 1;
}



  cout<<"Компьютерная сеть"<<"\n"<<"\n"<<"\n"<<"\n"<<"\n"<<"\n"<<"\n";

  // Вывод матрицы связей
cout<<"Матрица смежности:"<<endl;
  for (int i = 0; i<SIZE; i++)
  {
    for (int j = 0; j<SIZE; j++)
      printf("%5d ", GR[i][j]);
    printf("\n");
  }

cout<<"Матрица кратчайших путей:"<<endl;
FU(GR, n);

cout<<"Введите две вершины для поиска кратчайшего пути M и N:"<<endl;
cin >> m1 >> n1 ;
cout<<"Кратчайший путь  между "<<m1 << " и " << n1 << " равен: "<<searchPoints(m1, n1) <<endl;

    POINT op;
    HWND hWnd=GetConsoleWindow(); //Получаем дескриптор окна консоли
    HDC hDC=GetDC(hWnd); //Получаем контекст устройства по полученному дескриптору

draw(op,hDC,koord,svyazi,sv, SIZE);

    int iKey = 1;
    while (iKey != 27) { // Задержка и выход по клавише ESC
        if (_kbhit()) {
            iKey = _getch();
            switch (iKey)
            {
                case 112: case 80: case 167: case 135:
                draw(op,hDC,koord,svyazi,sv,SIZE); // перерисовка консоли по клавише 'p'
                break;
            }
        }
    }


    // Вывод матрицы кратчайших путей
    for (int i = 0; i<SIZE; i++)
    {
    for (int j = 0; j<SIZE; j++)
        printf("%5d ", GR[i][j]);
        printf("\n");
    }

     ReleaseDC(hWnd,hDC); //"Освобождаем" контекст
    std::cin.get();
    return 0;
}

void createaGraph(int a, int b ,POINT &op , HDC &hDC, int i){
    int x = a;
    int y = b;
    int number_graph = i;

    string str(to_string(number_graph));
    char * cstr = new char [str.length()+1];
    strcpy (cstr, str.c_str());

    x = x * 10;
    y = y * 10;

    Ellipse(hDC, x-5  , y+5  , x+5  , y-5 );
    TextOut(hDC, x-5 ,y+5, cstr,1);
}

int searchPoints(int m, int n){
    int minPath = GR[m][n];
    return minPath;
}

void drawlines(POINT &op , HDC &hDC,int fromx1,int fromy1,int tox2,int toy2){
    int x1 = fromx1 * 10;
    int y1 = fromy1 * 10;

    int x2 = tox2 * 10;
    int y2 = toy2 * 10;

    MoveToEx(hDC,x1,y1,&op); //Ставим текущую точку в координаты x1,y1
    LineTo(hDC,x2,y2); //Рисуем линию из текущей точки в точку x2, y2
}

//алгоритм Флойда-Уоршелла
void FU(int D[][maxV], int V)
{
    int k;
    for (i=0; i<V; i++) D[i][i]=0;

    for (k=0; k<V; k++)
    for (i=0; i<V; i++)
    for (j=0; j<V; j++)
    if (D[i][k] && D[k][j] && i!=j)
    if (D[i][k]+D[k][j]<D[i][j] || D[i][j]==0)
    D[i][j]=D[i][k]+D[k][j];

    for (i=0; i<V; i++)
    {
        for (j=0; j<V; j++) cout<<D[i][j]<<"\t";
        cout<<endl;
    }
}

void draw(POINT &op , HDC &hDC,int koord[][2],int svyazi[][2],int sv,int SIZE){

    SelectObject(hDC,GetStockObject(WHITE_PEN)); //Выбираем перо WHITE_PEN в контекст

    for(int i=0; i<SIZE; i++){
        createaGraph(koord[i][0],koord[i][1], op , hDC, i);
    }

    for(int i=0;i<sv;i++){
        drawlines(op , hDC,koord[svyazi[i][0]-1][0],koord[svyazi[i][0]-1][1],koord[svyazi[i][1]-1][0],koord[svyazi[i][1]-1][1]);
    }
}

