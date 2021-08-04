#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <iomanip>

#define tab cout<<"\t\t\t";
#define ns cout<<"\n";

using namespace std;

bool Strike_Player_One = false;
bool Streke_Player_Two = false;
bool Player_Win = false;

int red = 12; 
int yellow = 6;
int Set_Num = 1;

string menu[3] = {
	"1.Play",
	"2.Author",
	"3.Quit"
};

struct Field
{
	char map[16][19] = {
"..................",
"...x12345678910...",
"..y+----------+...",
"..1|          |...",
"..2|          |...",
"..3|          |...",
"..4|          |...",
"..5|          |...",
"..6|          |...",
"..7|          |...",
"..8|          |...",
"..9|          |...",
".10|          |...",
"...+----------+...",
"..................",
"..................",
	};
	string Name = "";
};

// Функции логов
void Set_Ships();
void Input_Ship_Point_xy(Field & player);
void Set_One_Ship(Field& player);
void Set_Two_Ship(Field& player);
void Set_Three_Ship(Field& player);
void Set_Four_Ship(Field& player);
bool Check_Ship_Around(int x,int y, int Ship_Count, int position,const Field& player);
void Set_Ships_Console_Text();
void Set_Ship_Posishion_Button();

// Функции интерфейса
struct Field;

void Console_Window_Size();
void Console_Output_Field(const Field& f);
void Build_Name_Two_Players(Field& a, Field& b); // Записываем имя в поля игроков 
void String_Color(string vibor, int color); // цвет строки
void Char_Color(char vibor, int color); // цвет символа
void Menu_Output(); // меню
void Log_Menu(); // обработка нажаний клавиш
void Log_Menu_Output(int num); // обработка цвета 
void String_Size();
void Author_Logo();

Field Player1;
	Field Player2;
	Field Temp_Field1;
	Field Temp_Field2;

int main() {
	setlocale(LC_ALL, "russian");
	Console_Window_Size();
	String_Size();
	//system("mode con cols=50 lines=50");
	Menu_Output();
	Log_Menu(); 
	Set_Ships();
	return 0;
}

void Console_Output_Field(const Field& f) {  // Вывод поля на экран
	
	cout << "\t\t"; String_Color(f.Name, 6);ns
	for (int i = 0; i < 16; i++) {
		for (int k = 0; k < 19; ++k) {
			if (f.map[i][k] == 'x' || f.map[i][k] == 'y') {
				Char_Color(f.map[i][k], 4);
				cout << " ";
			}
			else if (f.map[i][k] != 'x' &&
				f.map[i][k] != 'y'
				&& f.map[i][k] != '.') {
				Char_Color(f.map[i][k], 10);

				cout << " ";
			}
			else if(static_cast<int>(f.map[i][k])==4){
				Char_Color(f.map[i][k], red);
				cout << " ";
			}
			else  {
				Char_Color(f.map[i][k], 9);
				cout << " ";
			}
		}
		ns
			
	}
}

void Build_Name_Two_Players(Field& a, Field& b) {
	string player1, player2;
	String_Color("Player name", 13);
	ns
	cin >> player1;
	a.Name = player1;
	ns
	b.Name = "Bot";ns

}

void Console_Window_Size() { // Размер окна консоли и его отображение
	HWND window_header = GetConsoleWindow();
	SetWindowPos(window_header, HWND_TOP, 400, 400, 1200, 1000, NULL);
}

void String_Color(string vibor, int color) {  // Окрашивание меню
	HANDLE consoleOutput;

	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleOutput, color); //Перед строкой для выделения текста цветом
	cout << vibor;
	SetConsoleTextAttribute(consoleOutput, 15); //Возвращаем назад цвет
}

void Char_Color(char vibor, int color) {  // Окрашивание меню
	HANDLE consoleOutput;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleOutput, color); //Перед строкой для выделения текста цветом
	cout << vibor;
	SetConsoleTextAttribute(consoleOutput, 15); //Возвращаем назад цвет
}

void Log_Menu() {
	int n = _getch();
	system("cls");
	// Если нажимается Enter 
	if (n == 13 && Set_Num == 1) {
		system("cls");
		Build_Name_Two_Players(Player1, Player2);
		system("cls");
		return;
	}
	if (n == 13 && Set_Num == 2) {
		system("cls");
		Author_Logo();
	}
	if (n == 13 && Set_Num == 3) {
		String_Color("Good bay :)",13);
		exit(0);
	}

	// Клавиши вверх вниз
	if (n == 80) {
		Set_Num++;
	}
	if (n == 72) {
		Set_Num--;
	}
	if (n == 77 || n == 75) {
		Set_Num = 1;
	}

	if (Set_Num > 3) {
		Set_Num = 1;
	}
	if (Set_Num < 1) {
		Set_Num = 3;
	}
	Log_Menu_Output(Set_Num);
}

void Log_Menu_Output(int num) {
	if (num == 1) {
		system("cls");
		tab
			String_Color(menu[0], yellow); ns
			tab
			String_Color(menu[1], red); ns
			tab
			String_Color(menu[2], red); ns
			Log_Menu();
	}

	else if (num==2) {
		system("cls");
		tab
			String_Color(menu[0], red); ns
			tab
			String_Color(menu[1], yellow); ns
			tab
			String_Color(menu[2], red); ns
			Log_Menu();
	}
	else {
		system("cls");
		tab
			String_Color(menu[0], red); ns
			tab
			String_Color(menu[1], red); ns
			tab
			String_Color(menu[2], yellow); ns
			Log_Menu();
	}
}

void Menu_Output() {
	    tab
		String_Color(menu[0], yellow); ns
		tab
		String_Color(menu[1], red); ns
		tab
		String_Color(menu[2], red); ns
}

void String_Size() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   
	cfi.dwFontSize.Y = 20;                  
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); 
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Input_Ship_Pointxy() {





















































}

void Author_Logo() {// Функция отображения автора
	char author[5][70] = {

"	&&&&&&&   &&&&&&&  &&&    &&  &&  &&&&&&&    ",
"	&&    &&  &&       && &   &&  &&  &&         ",
"	&&    &&  &&&&&&&  &&  &  &&  &&  &&&&&&&    ",
"	&&    &&  &&       &&   & &&  &&       &&    ",
"	&&&&&&&   &&&&&&&  &&    &&&  &&  &&&&&&&    " };

	HANDLE consoleOutput;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	ns ns 
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 70; j++) {
			SetConsoleTextAttribute(consoleOutput, 11); //Перед строкой для выделения текста цветом
			
			cout << author[i][j];
			
			SetConsoleTextAttribute(consoleOutput, 15); //Возвращаем назад цвет
		}
		cout << endl;
		
	}
	ns ns
	String_Color("Press Esc to back....", 14); ns

			while (true) {
				int n = _getch();
				if (n == 27) {
					break;
				}
			}
	Log_Menu();
}

void Input_Ship_Point_xy(Field& player) {
	
	cout << "Введите координаты трехпалубного корабля";
	cout << "Введите координаты двух палубного корабля";
	cout << "Введите координаты однoпалубного корабля";


cout << "1.Установить вертикально |сверху вниз|";
	cout << "2.Установить горизонтально  |справа на лево|";
	
};

void Set_Four_Ship(Field& player) {
	system("cls");
	Console_Output_Field(Player1);
	cout << "Установка четырехпалубного корабля"; ns
	Set_Ships_Console_Text();
	int position;
	while (true) {
		position = _getch();
		if (position == 49 || position == 50)
		{
			break;
		}
	}
	A:
	cout << "Введите координаты четырехпалубного корабля (x:y)"; ns
    int x;
	int y;
	cin >> y>>x ;
	if (x < 1 || x>10 || y < 1 || y>10) {
		goto A;
	}
	bool check_around = Check_Ship_Around(x, y, 4, position, Player1);
	if (check_around == false) {
		goto A;
	}
	x = x + 2;
	y = y + 3;

	if (position == 49) {// Button 1 ghorisontal
		if (x>9) {
			goto A;
		}
		for (int i = 0; i < 4; ++i) {
			player.map[x][y] = char(4);
			x++;
		}
	}

	if (position == 50) { // Button 2 vertical
		if (y > 10) {
			goto A;
		}
		for (int i = 0; i < 4; ++i) {
			player.map[x][y] = char(4);
			y++;
		}
	}
	system("cls");
	Console_Output_Field(Player1);

}

void Set_Three_Ship(Field& player) {
		system("cls");
		Console_Output_Field(Player1);

		cout << "Установка трехпалубного корабля"; ns
			Set_Ships_Console_Text();
		int position;

		while (true) {
		position = _getch();
			if (position == 49 || position == 50) {
				break;
			}
		}

	A:
		cout << "Введите координаты трехпалубного корабля (x:y)"; ns
			int x;
		int y;
		cin >> y >> x;

		if (x < 1 || x>10 || y < 1 || y>10) {
			goto A;
		}
		bool ship_around = Check_Ship_Around(y, x, 3, position, Player1);
		if (ship_around == false) {
			goto A;
		}
		x = x + 2;
		y = y + 3;

		if (position == 49) {// Button 1 

			if (x > 10) {
				goto A;
			}

			for (int i = 0; i < 3; ++i) {
				player.map[x][y] = char(4);
				x++;
			}
		}

		if (position == 50) { // Button 2
			if (y > 11) {
				goto A;
			}
			for (int i = 0; i < 3; ++i) {
				player.map[x][y] = char(4);
				y++;
			}
		}
		system("cls");
} 

void Set_Two_Ship(Field& player) {

		system("cls");
		Console_Output_Field(Player1);
			cout << "Установка двухпалубного корабля"; ns
			Set_Ships_Console_Text();
		int position;

		while (true) {
			position = _getch();
			if (position == 49 || position == 50) {
				break;
			}
		}
			A:
		cout << "Введите координаты двухпалобного корабля (x:y)"; ns
			int x;
		int y;
		cin >> y >> x;
		if (x < 1 || x>10 || y < 1 || y>10) {
			goto A;
		}
		bool check_around = Check_Ship_Around(x, y, 2, position, Player1);
		if (check_around == false) {
			goto A;
		}
		x = x + 2;
		y = y + 3;

		if (position == 49) {// Button 1 
			if (x > 11) {
				goto A;
			}
			for (int i = 0; i < 2; ++i) {
				player.map[x][y] = char(4);
				x++;
			}
		}
		if (position == 50) { // Button 2
			if (y > 12) {
				goto A;
			}
			for (int i = 0; i < 2; ++i) {
				player.map[x][y] = char(4);
				y++;
			}
		}
		system("cls");
	
}

void Set_One_Ship(Field& player){
	system("cls");
		Console_Output_Field(Player1);
		cout << "Установка однопалубного корабля"; ns
	A:
		cout << "Введите координаты однопалубного корабля (x:y)"; ns
	    int x;
		int y;
		cin >>  x>> y;
		if (x < 1 || x>10 || y < 1 || y>10) {
			goto A;
		}
		bool check_around = Check_Ship_Around(x, y,1, 1, Player1);
		if (check_around == false) {
			goto A;
		}
		x = x + 2;
		y = y + 3;

			if (x > 12 || y > 13) {
				goto A;
			}
			player.map[x][y] = char(4);
		system("cls");
}

void Set_Ships_Console_Text() {
	cout << "1.Установить вертикально |сверху вниз|";ns
	cout << "2.Установить горизонтально  |справа на лево|"; ns
		 ns
}

void Set_Ships() {
	Set_Four_Ship(Player1);
	
	Set_Three_Ship(Player1);
	Set_Three_Ship(Player1);

	Set_Two_Ship(Player1);
	Set_Two_Ship(Player1);
	Set_Two_Ship(Player1);

	Set_One_Ship(Player1);
	Set_One_Ship(Player1);
	Set_One_Ship(Player1);
	Set_One_Ship(Player1);

	Console_Output_Field(Player1);
}

bool Check_Ship_Around(int x, int y, int Ship_Count, int position, const Field& player) {
	// x, у коррдинаты
	// Ship_Count  Количество палуб
	// position Горизонтальная вертикальная позиция
	// 50 вертикальая 
	// 49 горизонтальная

	x = x + 2;
	y = y + 3;

	if (position == 49) {
		for (int i =x; i < x+3;i++) {
			for (int k = y; k < y + Ship_Count; k++) {
				if (Player1.map[i][k]== char(5)) {
					return false;
				}
			}
		}
	}

	else {
		for (int i = y; i < y + 3; i++) {
			for (int k = x; k < x + Ship_Count; k++) {
				if (Player1.map[k][i] == char(5)) {
					return false;
				}
			}
		}
	}

	return true;
}






