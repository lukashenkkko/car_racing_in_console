#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>

//template<typename T1, typename T2>

//функции подсчета времени для положения препядствий
int ClockBox1(bool FlagBox1,int timer,int SpeedCoefficient,int timerl)
{
    int TimeBox1=0;
    if (FlagBox1==1) {
        TimeBox1 = (timerl / SpeedCoefficient)-timer;
    }
    return (TimeBox1);
}
int ClockBox2(bool FlagBox2,int timer, int SpeedCoefficient,int timerl)
{
    int TimeBox2 = 0;
    if (FlagBox2 == 1) {
        TimeBox2 = (timerl / SpeedCoefficient) - timer;
    }
    return (TimeBox2);
}
int ClockBox3(bool FlagBox3,int timer, int SpeedCoefficient,int timerl)
{
    int TimeBox3 = 0;
    if (FlagBox3 == 1) {
        TimeBox3 = (timerl / SpeedCoefficient) - timer;
    }
    return (TimeBox3);
}

void spacebar()
{
    std::cout << " ";
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL,"");
    //переменные
    const int BackgroundHeight = 28, BackgroundWidth = 40;
    char CarControlButton = 's';
    int CarPosition = 1;
    int TimerBox1= 0;
    int TimerBox2 = 0;
    int TimerBox3 = 0;
    bool FlagBox1 = 0;
    bool FlagBox2 = 0;
    bool FlagBox3 = 0;
    bool FlagGameOver = 0;//флажок для запуска меню окончания игры
    int ChanseBoxPrint;
    int FLagTimer1=0;
    int FLagTimer2=0;
    int FLagTimer3=0;
    int SpeedCoefficient = 1000;
    int timer=0;
    int n = 0;
    int x = 0;
    //создание массива
    char Background[BackgroundHeight][BackgroundWidth];
    //Массив машинки
    std::string Car[6]{
    { "  **  " },
    { "******" },
    { "  **  " },
    { "  **  " },
    { "******" },
    { "  **  " }
    };
    //Массив препядствия
    std::string Box[4]{
   { "******" },
   { "******" },
   { "******" },
   { "******" }
    };

    //заполнение массива
    for (int t = 0; t < BackgroundHeight; t++)
    {
        for (int g = 0; g < BackgroundWidth; g++)
        {
            if (t == 0)Background[t][g] = '*';
            if (t == (BackgroundHeight - 1))Background[t][g] = '*';
            else if (g != 0 && g != (BackgroundWidth - 1)) continue;
            Background[t][g] = '*';
        }

    }

    for (;;) {
        if (FlagGameOver == 1)
        {
            break;
        }
        //ускорение времени
        timer = (clock()) / 1;

        //std::cout << timer<<" ";
        if(SpeedCoefficient>100) SpeedCoefficient-=0.1;
        //std::cout << SpeedCoefficient<<" ";

        //Управление нажатием
        CarControlButton = 's';
        if (_kbhit()) {
            CarControlButton = _getch();//чтение нажатой клавиши
            switch (CarControlButton) {
            case 'a' : if (CarPosition != 0)CarPosition--;
                break;
            case 'd' :if (CarPosition != 2)CarPosition++;
                break;
            case -28: if (CarPosition != 0)CarPosition--;
                break;
            case -94:if (CarPosition != 2)CarPosition++;
            }
            //std::cout << (int)CarControlButton;
        }
        int KeyForCar = 0;//переменная для вывода этажей машинки
        int KeyForBox = 0;//переменная для вывода этажей препядствия
        int BoxPosition1=0;//позиция ящика N1
        int BoxPosition2=0;//позиция ящика N2
        int BoxPosition3=0;//позиция ящика N3
        clock();
        //вывод на экран
        for (int t = 0; t < BackgroundHeight; t++)
        {
            //сброс флажков боксов для повторного их выведения
            if (BoxPosition1 > 27) { FLagTimer1 = 0; TimerBox1 = 0; FlagBox1 = 0; BoxPosition1 = 0;}
            if (BoxPosition2 > 27) { FLagTimer2 = 0; TimerBox2 = 0; FlagBox2 = 0; BoxPosition2 = 0;}
            if (BoxPosition3 > 27) { FLagTimer3 = 0; TimerBox3 = 0; FlagBox3 = 0; BoxPosition3 = 0;}

            ////рандомвйзер боксов
            ChanseBoxPrint = rand() % 300;//шанс появления бокса
            switch (ChanseBoxPrint)
            {
                case 1:  FlagBox1 = 1; if (FLagTimer1 == 0) { TimerBox1 = timer / SpeedCoefficient; FLagTimer1 = 1; };
                    break;
                case 2:  FlagBox2 = 1; if (FLagTimer2 == 0) { TimerBox2 = timer / SpeedCoefficient; FLagTimer2 = 1; };
                    break;
                case 3:  FlagBox3 = 1; if (FLagTimer3 == 0) { TimerBox3 = timer / SpeedCoefficient; FLagTimer3 = 1; };
                    break;
                }
           //функции которые задают положение коробкам
            BoxPosition1 = (ClockBox1(FlagBox1,TimerBox1,SpeedCoefficient,timer))-4;
            BoxPosition2 = (ClockBox2(FlagBox2,TimerBox2,SpeedCoefficient,timer))-4;
            BoxPosition3 = (ClockBox3(FlagBox3,TimerBox3,SpeedCoefficient,timer))-4;
           // std::cout << BoxPosition1;
            //проверка на спавн не больше двух коробок
            if (BoxPosition1 > -4 && BoxPosition2 > -4 && BoxPosition1<25 && BoxPosition2<25) { FlagBox3 = 0; FLagTimer3 = 0; }
            else if (BoxPosition1 > -4 && BoxPosition3 > -4 && BoxPosition1 < 25 && BoxPosition3 < 25) { FlagBox2 = 0; FLagTimer2 = 0; }
            else if (BoxPosition2 > -4 && BoxPosition3 > -4 && BoxPosition2 < 25 && BoxPosition3 < 25) { FlagBox1 = 0; FLagTimer1 = 0; }

            for (int g = 0; g < BackgroundWidth; g++)
            {
                if (Background[t][g] == '*')
                {
                    std::cout << Background[t][g];
                }
                //Вивод коробок
                else if (g == ((BackgroundWidth / 4) - 3) && t > BoxPosition1 && t < BoxPosition1+5)//левая коробка
                {
                    if (KeyForBox == 3) KeyForBox = 0;
                    std::cout<<Box[KeyForBox];
                    KeyForBox++;
                    g += 5;
                }
                else if (g == ((BackgroundWidth / 2) - 3) && t > BoxPosition2 && t < BoxPosition2 + 5)//средняя коробка
                {
                    if (KeyForBox == 3) KeyForBox = 0;
                    std::cout << Box[KeyForBox];
                    KeyForBox++;
                    g += 5;
                }
                else if (g == (BackgroundWidth -13)  && t > BoxPosition3 && t < BoxPosition3 + 5)//правая коробка
                {
                    if (KeyForBox == 3) KeyForBox = 0;
                    std::cout << Box[KeyForBox];
                    KeyForBox++;
                    g += 5;
                }
                
                //вывод машинки
                else if (g == ((BackgroundWidth / 4) - 3) && t > 18 && t < 25 && CarPosition == 0)//условие для вывода машинки слева
                {
                    if (KeyForCar == 5) KeyForCar = 0;
                    std::cout << Car[KeyForCar];
                    KeyForCar++;
                    g += 5;
                }
                else if (g == ((BackgroundWidth / 2) - 3) && t > 18 && t < 25 && CarPosition == 1)//условие для вывода машинки посредине
                {
                    if (KeyForCar == 5) KeyForCar = 0;
                    std::cout << Car[KeyForCar];
                    KeyForCar++;
                    g += 5;
                }
                else if (g == ((BackgroundWidth - 13)) && t > 18 && t < 25 && CarPosition == 2)//условие для вывода машинки справа
                {
                    if (KeyForCar == 5) KeyForCar = 0;
                    std::cout << Car[KeyForCar];
                    KeyForCar++;
                    g += 5;
                }
                else spacebar();

                //проверка столкновения с ящиком
                if (BoxPosition1 >= 15 && BoxPosition1 <= 23 && CarPosition == 0) { FlagGameOver = 1; break;}//колизия левого ящика
                if (BoxPosition2 >= 15 && BoxPosition2 <= 23 && CarPosition == 1) { FlagGameOver = 1; break; }//колизия среднего ящика
                if (BoxPosition3 >= 15 && BoxPosition3 <= 23 && CarPosition == 2) { FlagGameOver = 1; break; }//колизия правого ящика
            }
            std::cout << std::endl;
        }
        system("cls");
    }
   //вывод меню поражения
    x = clock();
    while ((x/= 10) > 0)
    {
        n++;
        std::cout << n;
    }
    for (int t = 0; t < BackgroundHeight; t++)
    {
        for (int g = 0; g < BackgroundWidth; g++)
        {
            if (Background[t][g] == '*')
            {
                std::cout << Background[t][g];
            }
            else if(g == ((BackgroundWidth / 2) - 5) && t==5)
            {
                std::cout << "GAME OVER";
                g += 8;
            }
            else if (g == ((BackgroundWidth / 2) - 5) && t == 6)
            {
                std::cout << "GAME OVER";
                g += 8;
            }
            else if (g == ((BackgroundWidth / 2) - 5) && t == 7)
            {
                std::cout << "GAME OVER";
                g += 8;
            }
            else if (g == ((BackgroundWidth / 2) - 6) && t == 9)
            {
                std::cout << "YOUR SCORE:";
                g += 10;
            }
            else if (g == ((BackgroundWidth / 2) - n) && t == 10)
            {
                std::cout << clock();
                g += n;
            }
            else spacebar();
        }
        std::cout << std::endl;
    }
}