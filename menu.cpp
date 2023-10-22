#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

const char ESCAPE = 27, UP = 72, DOWN = 80, ENTER = 13; // константи необхідних клавіш

using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x, y });

}
void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void main()
{
    SetConsoleTitle(L"Serokurow");  //Заголовок 
    string menu[]{ "New game", "Load game", "Settings", "Exit" }; // теми меню
    int active_menu = 0;
    setlocale(0, "");
    char ch;

    while (true)
    {
        ConsoleCursorVisible(false, 100); //Приховання курсору
        system("CLS"); // для очистки вікна після змінення його розміру 
        // Розрахунок координат центру консолі в залежності від її розміру на екрані 
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hStdOut, &consoleInfo);
        int width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
        int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        // розміри меню
        int menuWidth = 10;
        int menuHeight = size(menu);
        // розрахунки для виводу меню по центру   
        int x = (width - menuWidth) / 2;
        int y = (height - menuHeight) / 2;

        GoToXY(x, y);

        for (int i = 0; i < size(menu); i++)
        {
            if (i == active_menu)

                SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN); // колір активної теми меню

            else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE); // стандартний колір

            GoToXY(x, y++);
            cout << menu[i] << endl;
        }
        ch = _getch();
        if (ch == -32) ch = _getch();

        switch (ch)
        {

        case ESCAPE:
            exit(0);
        case UP:
            if (active_menu > 0)

                active_menu--;
            else                  // перехід з "New game" до "Exit""
                active_menu = 3;
            break;
        case DOWN:
            if (active_menu < size(menu) - 1)

                active_menu++;
            else                 // перехід з "Exit" до "New game"
                active_menu = 0;
            break;
        case ENTER:
            switch (active_menu)
            {
            case 1:
            case 2:
            case 0:
                system("CLS");
                GoToXY(x, y);
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN |

                    FOREGROUND_INTENSITY);

                cout << "User selected\"" << menu[active_menu] << "\"";
                _getch();
                system("CLS");
                break;

            case 3:
                exit(0);
            }
            break;
            /* case 75:
                 cout << "Left, Код " << (int)ch << endl;
                 break;
             case 77:
                 cout << "Right, Код " << (int)ch << endl;
                 break;*/
        default:
            cout << "Код " << (int)ch << endl;

        }

    }
}
/*
клавіша "0" - 48                                    клавіша "Enter," - 13
клавіша "1" - 49                                    клавіша "Home" - 71
клавіша "2" - 48                                    клавіша "End" - 79
клавіша "Пробіл" - 32
клавіша "ESC" - 27
*/