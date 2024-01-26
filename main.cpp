#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int COLS = 7, ROWS = 6;

string getName(int player) {
    string name;
    cout << "player " << player << " : Enter your name\t";
    cin >> name;
    return name;
}

int start(string names[]) {
    int turn = rand() % 2 + 1;
    cout << "\n" << names[turn] << " starts !\n\n";
    return turn;
}

int menu() {
    int choice = 0;
    cout << "\n\t\t **** Welcome to Connect 4 **** \n";
    cout << "\nMenu Options :\n";
    cout << "\tTo play vs player, enter 1\n\tTo play vs computer, enter 2 \n\t";
    cin >> choice;
    if ((choice != 1 && choice != 2) || cin.fail()) {
        cout << "Invalid input. Please enter 1 or 2.\n\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return menu();
    }
    return choice;
}

void printBoard(int square[ROWS][COLS]) {
    cout << "\n";
    for (int i = 0; i < ROWS; i++) {
        cout << "\t";
        for (int j = 0; j < COLS; j++)
            cout << square[i][j] << "  ";
        cout << "\n";
    }
    cout << "\n";
}

void play(int square[ROWS][COLS], int *player, string names[], int gameMode) {
    int choice;
    if (*player != 0) {
        while (true) {
            cout << names[*player] << " : Choose a column\t";
            cin >> choice;
            if (choice < 0 || choice >= COLS || cin.fail()) {
                cout << "\t\tYou should enter correct values\n\n";
                cin.clear();
                cin.ignore(10000, '\n');
            } else if (square[0][choice] != 0) {
                cout << "This column is full. Try another one\n\n";
                cin.clear();
                cin.ignore(10000, '\n');
            } else
                break;
        }
        for (int i = ROWS - 1; i >= 0; i--)
            if (square[i][choice] == 0) {
                square[i][choice] = *player;
                break;
            }
        printBoard(square);
        if (gameMode == 1)
            *player = (*player % 2) + 1;
        else
            *player = 0;
    } else {
        choice = rand() % COLS;
        cout << names[*player] << " 's turn\t";
        while (true) {
            if (square[0][choice] != 0) {
                choice = rand() % COLS;
            } else
                break;
        }
        for (int i = ROWS - 1; i >= 0; i--)
            if (square[i][choice] == 0) {
                square[i][choice] = 2;
                break;
            }
        printBoard(square);
        *player = (*player % 2) + 1;
    }
}

int checkWinner(int square[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS - 3; j++)
            if (square[i][j] != 0 && square[i][j] == square[i][j + 1] && square[i][j] == square[i][j + 2] &&
                square[i][j] == square[i][j + 3])
                return square[i][j];
    for (int i = 0; i < ROWS - 3; i++)
        for (int j = 0; j < COLS; j++)
            if (square[i][j] != 0 && square[i][j] == square[i + 1][j] && square[i][j] == square[i + 2][j] &&
                square[i][j] == square[i + 3][j])
                return square[i][j];
    for (int i = 0; i < ROWS - 3; i++)
        for (int j = 0; j < COLS - 3; j++)
            if (square[i][j] != 0 && square[i][j] == square[i + 1][j + 1] && square[i][j] == square[i + 2][j + 2] &&
                square[i][j] == square[i + 3][j + 3])
                return square[i][j];
    for (int i = 0; i < ROWS - 3; i++)
        for (int j = COLS - 1; j >= 3; j--)
            if (square[i][j] != 0 && square[i][j] == square[i + 1][j - 1] && square[i][j] == square[i + 2][j - 2] &&
                square[i][j] == square[i + 3][j - 3])
                return square[i][j];
    return -1;
}

void win(const string &winner) {
    cout << "\t\t************\n " << winner << " WINS !!!!!!";
}

int main() {
    srand(time(nullptr));
    int square[ROWS][COLS] = {};
    int gameMode = menu();
    string names[3];
    names[0] = names[2] = "Computer";
    names[1] = getName(1);
    if (gameMode == 1)
        names[2] = getName(2);
    printBoard(square);
    int player = start(names);
    while (checkWinner(square) == -1)
        play(square, &player, names, gameMode);
    win(names[checkWinner(square)]);
    return 0;
}
