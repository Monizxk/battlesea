//підключення заголовних файлів
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>

//директива яка вказує компілятору використовувати простір імен std
using namespace std;

//визначає розмір ігрового поля
const int BOARD_SIZE = 10;
//визначає кількість кораблів
const int NUM_SHIPS = 5;
//символ кораблів
const char SHIP_SYMBOL = 254;
//символ попадання у кораблів
const char HIT_SYMBOL = 'X';
//позначає промах у стрільбі
const char MISS_SYMBOL = 'O';
//порожнє місце на ігровому полі
const char EMPTY_SYMBOL = '.';

//представлення гравців у грі
struct Player {
    string name;
    char board[BOARD_SIZE][BOARD_SIZE];
};

//встановлює клітинки на ігровому полі гравця в символ, щоб підготувати поле перед початком гри
void initializeBoard(Player& player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            player.board[i][j] = EMPTY_SYMBOL;
        }
    }
}

//виведення ігрового поля в консолі
void printBoard(const char board[BOARD_SIZE][BOARD_SIZE], bool showShips = true) {
    cout << "  ";//виводить пробіли перед нумерацією стовпців
    //цикл що виводить пробіли перед нумерацією стовпців
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
    }
    cout << "       ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            char symbol = board[i][j];
            cout << symbol << " ";
        }
        cout << "     ";
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            char symbol = board[i][j];
            if (symbol == SHIP_SYMBOL && !showShips) {
                symbol = EMPTY_SYMBOL;
            }
            if (symbol == HIT_SYMBOL || symbol == MISS_SYMBOL) {
                cout << symbol << " ";
            } else {
                cout << EMPTY_SYMBOL << " ";
            }
        }
        cout << endl;
    }
}

//розміщення кораблів на ігровому полі випадковим чином
void placeShips(Player& player) {
    for (int i = 0; i < NUM_SHIPS; i++) {
        int size = i + 1;
        int x, y;
        bool placed = false;
        while (!placed) {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
            bool canPlace = true;
            for (int j = 0; j < size; j++) {
                if (x + j >= BOARD_SIZE || player.board[x + j][y] != EMPTY_SYMBOL) {
                    canPlace = false;
                    break;
                }
            }
            if (canPlace) {
                for (int j = 0; j < size; j++) {
                    player.board[x + j][y] = SHIP_SYMBOL;
                }
                placed = true;
            }
        }
    }
}

//метод що здійснює постріл у гру
bool makeShoot(Player* currentPlayer, Player* otherPlayer, int x, int y) { 
    if (otherPlayer->board[x][y] == SHIP_SYMBOL) {
        otherPlayer->board[x][y] = HIT_SYMBOL;
        return true;
    } else {
        otherPlayer->board[x][y] = MISS_SYMBOL;
        return false;
    }
}

//функція перевіряє стан дошки гравців та перевіраяє чи є символ корабля на будь яких із клітинок
bool isGameOver(const Player& player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (player.board[i][j] == SHIP_SYMBOL) {
                return false;
            }
        }
    }
    return true;
}

//перевіря ведення гравця дійсним числом у ведення координат на дошку
bool isNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

//виведення інструкції для користувача
void ShowInstruction () {
	cout << "\t\t\t===========================Battle Ship Game==========================\n" << endl;
	cout <<"\t\t\t1. Use x and y axis to shoot at the point on the axis you see fit.\n" << endl;
	cout <<"\t\t\t2. Don't peep on another player!\n" << endl;
	cout <<"\t\t\t3. Enjoy the game! UwU\n" << endl;
}

//функція завершення програми
void ExitMessage () {
	cout << "Exiting the game. Bye!!!" << endl;
}

int main() {
	//генератор випадкових чисел
    srand(time(0));

    Player player1, player2;
    
    initializeBoard(player1);
    initializeBoard(player2);
		
    placeShips(player1);
    placeShips(player2);
    				
    Player* currentPlayer = &player1;
	Player* otherPlayer = &player2;
    
    int MenuChoice;
    
    	while (true) {
    		cout << "\t\t\t===============================Menu=================================\n" << endl;
    		cout << "\t\t\t\t\t\t1. Start the game\n" << endl;
    		cout <<"\t\t\t\t\t\t2. Instruction\n" << endl;
    		cout <<"\t\t\t\t\t\t3. Exit\n" << endl;
    		cout <<"Enter your choice" << endl;
    		//вибір параметру меню
    		cin >> MenuChoice;
    		
    		switch (MenuChoice) {
    			case 1: {
    				cout << "Enter name for Player 1: ";
    				//ведення імя гравців
    				cin >> player1.name;
    				cout << "Enter name for Player 2: ";
    				cin >> player2.name;
    
    				cout << currentPlayer->name << " goes first." << endl;

    while (true) {
    	//передача ходу гравцям
        cout << currentPlayer->name << "'s turn" << endl;
        cout << "Board showing ships and opponent's shots:" << endl;
        printBoard(currentPlayer->board, false);

        int x, y;
        do {
        	//введення координатів
            string input;
            cout << "Enter coordinates (x y): ";
            cin >> input;
            if (!isNumber(input)) 
			//перевіряє дійсні числа веденних координат
			 {
                cout << "Invalid input. Please enter numbers only." << endl;
                continue;
            }
            x = stoi(input);
            cin >> input;
            if (!isNumber(input)) {
                cout << "Invalid input. Please enter numbers only." << endl;
                continue;
            }
            y = stoi(input);
            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
                cout << "Invalid move. Try again." << endl;
            }
        } while (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE);
        
		 //перевіряє чи попав гравець у корабель
        bool isHit = makeShoot(currentPlayer, otherPlayer, x, y);
        	if (isHit) {
            cout << "Hit!" << endl;
        	} 
			else {
            	cout << "Missed!" << endl;
            	swap(currentPlayer, otherPlayer);
        }
			//гра закінчена?
        	if (isGameOver(*otherPlayer)) {
            cout << currentPlayer->name << " wins the battle!" << endl;
            break;
        }
    }
    
    //виведення результатів
    cout << "Final boards:" << endl;
    cout << player1.name << "'s board:" << endl;
    printBoard(player1.board, true);
    cout << player2.name << "'s board:" << endl;
	    
    printBoard(player2.board, true);
    				
					break;
				}
			case 2:
				ShowInstruction();
				break;
			case 3:
				ExitMessage();
				return 0;
			}
		}
	return 0;
}
   
