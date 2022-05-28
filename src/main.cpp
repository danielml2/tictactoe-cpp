#include <iostream>
#include <string.h>
#include <tuple>

using namespace std;


void printBoard();
tuple<int, int> getInput();
int getValidInput();
tuple<int, int> convertToBoardValues(int place);
bool isSpotTaken(int spot);
bool isBoardFull();
bool checkWinner(char player);

char GAME_BOARD[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

int main()
{

    string playerName;
    char playerCharacter;

    bool playerOneTurn = true;
    bool win = false;

    while (!isBoardFull() && !win)
    {
        // Change the player name based on whos's turn is it along with the character to play.
        playerName = playerOneTurn ? "Player 1 (x)" : "Player 2 (o)";
        playerCharacter = playerOneTurn ? PLAYER1 : PLAYER2;

        printBoard();
        cout << playerName << "'s Turn." << endl;

        tuple<int, int> selectedPos = getInput();
        int row, col;
        tie(row, col) = selectedPos;

        GAME_BOARD[row][col] = playerCharacter;

        if (checkWinner(playerCharacter))
            win = true;
        playerOneTurn = !playerOneTurn; // Flip the turn to the other person.
    }

    printBoard();
    if (win)
        cout << playerName << " Wins!" << endl;
    else
        cout << "Tie!" << endl;
}

// Prints the board
void printBoard()
{

    for (int i = 0; i < 3; i++)
    {
        cout << "-------------" << endl;
        cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            cout << GAME_BOARD[i][j] << " | ";
        }
        cout << endl;
    }
    cout << "-------------" << endl;
}

// Gets a valid input and converts it to board placement.
tuple<int, int> getInput()
{
    return convertToBoardValues(getValidInput());
}

// Recurses until a valid input for the game is recieved
int getValidInput()
{
    int num;
    cout << "Please enter a board position: ";
    cin >> num;
    // If the input is invalid for the Tic Tac Toe game
    if (cin.fail() || num > 9)
    {
        cin.clear();
        cin.ignore(2);
        num = getValidInput();
    }
    // If specifically in that time of the game, the spot is simply full and from there invalid
    else if (isSpotTaken(num))
    {
        cout << "That spot is already full!" << endl;
        num = getValidInput();
    }
    return num;
}


/*
    Converts game place to the board row and column indexes.

    Place represents the point from top-left to bottom right,
    e.g.:
            0   1   2
        0 | 1 | 2 | 3 |
        1 | 4 | 5 | 6 |
        2 | 7 | 8 | 9 |
*/
tuple<int, int> convertToBoardValues(int place)
{
    
    tuple<int, int> boardPoints(0, 0);
    if (place <= 3)
        get<1>(boardPoints) = place - 1;
    else if (place % 3 > 0)
    {
        get<0>(boardPoints) = place / 3;
        get<1>(boardPoints) = place % 3 - 1;
    }
    else
    {
        get<0>(boardPoints) = place / 3 - 1;
        get<1>(boardPoints) = 2;
    }

    return boardPoints;
}

bool checkWinner(char player)
{

    bool horizontalWin = false;
    for (int i = 0; i < 3 && !horizontalWin; i++)
        horizontalWin = GAME_BOARD[i][0] == player && GAME_BOARD[i][1] == player && GAME_BOARD[i][2] == player;

    bool verticalWin = false;
    for (int i = 0; i < 3 && !verticalWin; i++)
        verticalWin = GAME_BOARD[0][i] == player && GAME_BOARD[1][i] == player && GAME_BOARD[2][i] == player;

    bool leftDiagonal = GAME_BOARD[0][0] == player && GAME_BOARD[1][1] == player && GAME_BOARD[2][2] == player;
    bool rightDiagonal = GAME_BOARD[0][2] == player && GAME_BOARD[1][1] == player && GAME_BOARD[2][0] == player;

    return horizontalWin || verticalWin || leftDiagonal || rightDiagonal;
}

bool isBoardFull()
{
    for (int i = 1; i <= 9; i++)
        if (!isSpotTaken(i))
            return false;
    return true;
}

bool isSpotTaken(int spot)
{
    int row, col;
    tie(row, col) = convertToBoardValues(spot);

    return GAME_BOARD[row][col] == PLAYER1 || GAME_BOARD[row][col] == PLAYER2;
}

