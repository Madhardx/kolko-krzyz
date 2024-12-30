#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Funkcja do rysowania planszy w układzie numerycznym
void drawBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "Kółko-krzyżyk\n\n";
    std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n";
    std::cout << "---+---+---\n";
    std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n";
    std::cout << "---+---+---\n";
    std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n";
}

// Funkcja do sprawdzenia, czy ktoś wygrał
bool checkWin(const std::vector<std::vector<char>>& board, char player) {
    // Sprawdzamy wiersze
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    // Sprawdzamy kolumny
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    // Sprawdzamy przekątne
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

// Funkcja do sprawdzenia, czy plansza jest pełna
bool isBoardFull(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Funkcja do wykonania ruchu
bool makeMove(std::vector<std::vector<char>>& board, int move, char player) {
    int row = 2 - (move - 1) / 3; // Mapujemy numer na wiersz
    int col = (move - 1) % 3; // Mapujemy numer na kolumnę

    if (move < 1 || move > 9 || board[row][col] != ' ') {
        return false; // Błędny ruch, pole już zajęte
    }
    board[row][col] = player;
    return true;
}

// Funkcja do wyboru ruchu komputera
void computerMove(std::vector<std::vector<char>>& board) {
    srand(time(0)); // Inicjalizacja generatora liczb losowych
    int move;
    do {
        move = rand() % 9 + 1; // Losowy ruch między 1 a 9
    } while (!makeMove(board, move, 'O')); // Wybiera losowy wolny ruch
}

// Funkcja do wyboru trybu gry
void gameMode(std::vector<std::vector<char>>& board) {
    int choice;
    std::cout << "Wybierz tryb gry:\n";
    std::cout << "1. Gra 1 gracz (vs komputer)\n";
    std::cout << "2. Gra 2 graczy\n";
    std::cout << "3. Wyjście\n";
    std::cout << "Wybór: ";
    std::cin >> choice;

    if (choice == 1) {
        bool playerTurn = true; // Zaczyna gracz
        while (true) {
            drawBoard(board);
            int move;
            if (playerTurn) {
                std::cout << "Tura gracza (X)\n";
                std::cout << "Podaj numer pola (7-9, 4-6, 1-3): ";
                std::cin >> move;
                if (!makeMove(board, move, 'X')) {
                    std::cout << "Błędny ruch, spróbuj ponownie.\n";
                    continue;
                }
                if (checkWin(board, 'X')) {
                    drawBoard(board);
                    std::cout << "Gratulacje! Wygrałeś!\n";
                    break;
                }
                playerTurn = false; // Zmiana tury na komputer
            } else {
                computerMove(board);
                std::cout << "Tura komputera (O)\n";
                if (checkWin(board, 'O')) {
                    drawBoard(board);
                    std::cout << "Komputer wygrał!\n";
                    break;
                }
                playerTurn = true; // Zmiana tury na gracza
            }
            if (isBoardFull(board)) {
                drawBoard(board);
                std::cout << "Remis!\n";
                break;
            }
        }
    } else if (choice == 2) {
        bool playerTurn = true; // Zaczyna gracz
        while (true) {
            drawBoard(board);
            int move;
            if (playerTurn) {
                std::cout << "Tura gracza (X)\n";
                std::cout << "Podaj numer pola (7-9, 4-6, 1-3): ";
                std::cin >> move;
                if (!makeMove(board, move, 'X')) {
                    std::cout << "Błędny ruch, spróbuj ponownie.\n";
                    continue;
                }
                if (checkWin(board, 'X')) {
                    drawBoard(board);
                    std::cout << "Gratulacje! Wygrałeś!\n";
                    break;
                }
                playerTurn = false; // Zmiana tury na drugiego gracza
            } else {
                std::cout << "Tura gracza (O)\n";
                std::cout << "Podaj numer pola (7-9, 4-6, 1-3): ";
                std::cin >> move;
                if (!makeMove(board, move, 'O')) {
                    std::cout << "Błędny ruch, spróbuj ponownie.\n";
                    continue;
                }
                if (checkWin(board, 'O')) {
                    drawBoard(board);
                    std::cout << "Gratulacje! Wygrałeś!\n";
                    break;
                }
                playerTurn = true; // Zmiana tury na pierwszego gracza
            }
            if (isBoardFull(board)) {
                drawBoard(board);
                std::cout << "Remis!\n";
                break;
            }
        }
    } else if (choice == 3) {
        std::cout << "Dziękujemy za grę! Do zobaczenia!\n";
        exit(0);
    }
}

// Funkcja resetująca planszę
void resetBoard(std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

int main() {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));
    while (true) {
        gameMode(board);
        std::cout << "Chcesz zagrać ponownie? (t/n): ";
        char playAgain;
        std::cin >> playAgain;
        if (playAgain == 'n' || playAgain == 'N') {
            break; // Zakończenie gry
        } else {
            resetBoard(board); // Reset planszy
        }
    }
    return 0;
}
