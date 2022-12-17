/* ================================================================ */
// header files and namespace
#include <iostream>
using namespace std;

// global type definition representing a coordinate in a 2D Array conceptualizing rows and columns
struct Position {
    int row;
    int column;
};

// global function prototypes
void PrintHeading();
void Game(char table[][3]);
    void PrintBoard(char table[][3]);
    void UpdateBoard(char currentTurn, int positionNum, int &numRounds, bool &invalidSpot, char table[][3]);
        Position GetPosition(int position);
    bool CheckForWinner(char &currentTurn, char table[][3]);
bool PlayAgain();
void ResetBoard(char table[][3]);
void PrintOutro();

/* ================================================================ */

int main() {
    char table[][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    bool createGame = true;

    PrintHeading();

    // while loop to create a Game until the user does not want to play again
    while(createGame) {
        // create a single Game
        Game(table);

        // check if the user wants to play another game
        createGame = PlayAgain();

        ResetBoard(table);
    }

    PrintOutro();

    return 0;
}

/* ================================================================ */

/*
    PrintHeading prints the introductory output.
*/

void PrintHeading() {
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "         Welcome to TicTacToe!         " << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}

/* ================================================================ */

/*
    Game will create a single TicTacToe game that contains the functionality of updating the TicTacToe game board
    every round until a winner is found or is a tie based on the current board X and O placements.
    Parameters:
        table: the empty 2D array TicTacToe game board
*/

void Game(char table[][3]) {
    char currentTurn = 'X';
    int positionNum;
    int numRounds = 0;
    bool gameFinished = false;
    bool invalidSpot;

    // while the game is not finished, each iteration represents one round of the game
    while(!gameFinished) {
        numRounds++;

        cout << endl << "          Current Turn: " << currentTurn << endl << endl;

        PrintBoard(table);

        // prompt the user to enter their position to play
        cout << endl << "         Play Position: ";
        cin >> positionNum;

        // update the game board then check for a winner
        UpdateBoard(currentTurn, positionNum, numRounds, invalidSpot, table);
        gameFinished = CheckForWinner(currentTurn, table);

        // if the game resulted in a winner being found within 9 rounds of plays the game is over
        if(gameFinished) {
            cout << endl << "         " << currentTurn << " has won the game!" << endl << endl;
            PrintBoard(table);
        }

        // if the game results in no winner within 9 rounds of plays the game is a tie
        if(!gameFinished && numRounds == 9) {
            cout << endl << "        The game was a tie!" << endl;
            PrintBoard(table);
            gameFinished = true;
        }

        // change the currentTurn to the next player's turn
        if(!invalidSpot && currentTurn == 'X')
            currentTurn = 'O';
        else if(!invalidSpot && currentTurn == 'O')
            currentTurn = 'X';
    }
}

/* ================================================================ */

/*
    PrintBoard prints the current game board's X and O placements.
*/

void PrintBoard(char table[][3]) {
    cout << "         " << "    |   " << "    |   " << endl;
    cout << "         " << table[0][0] << "   |   " << table[0][1] << "   |   " << table[0][2] << endl;
    cout << "         " << "    |   " << "    |   " << endl;
    cout << "      -----------------------" << endl;
    cout << "         " << "    |   " << "    |   " << endl;
    cout << "         " << table[1][0] << "   |   " << table[1][1] << "   |   " << table[1][2] << endl;
    cout << "         " << "    |   " << "    |   " << endl;
    cout << "      -----------------------" << endl;
    cout << "         " << "    |   " << "    |   " << endl;
    cout << "         " << table[2][0] << "   |   " << table[2][1] << "   |   " << table[2][2] << endl;
    cout << "         " << "    |   " << "    |   " << endl;
}

/* ================================================================ */

/*
    UpdateBoard updates the current game board based on whether the turn is X or O and the position the user
    requested to make a play. This function performs error checking on if the requested position is a valid
    placement to make a play.
    Parameters:
        currentTurn: The current turn of X or O
        positionNum: The requested play position the user chose (1 - 9 based on the 3x3 2D game board)
        numRounds: The number of rounds the game has currently lasted (each play is one round)
        invalidSpot: Flag to check whether a requested play position resulted in an invalid placement
        table: the current 2D array TicTacToe game board
*/

void UpdateBoard(char currentTurn, int positionNum, int &numRounds, bool &invalidSpot, char table[][3]) {
    Position currentPos = {GetPosition(positionNum)};
    invalidSpot = false;

    // if the player's requested position is the same as a spot that is already occupied, the spot is invalid
    if(table[currentPos.row][currentPos.column] == 'X' || table[currentPos.row][currentPos.column] == 'O')
        invalidSpot = true;

    // if the player's requested position is not 1 - 9 based on the 3x3 2D game board, the spot is invalid
    if(positionNum < 1 || positionNum > 9)
        invalidSpot = true;

    // if the spot is not invalid the user's play position is confirmed
    if(!invalidSpot)
        table[currentPos.row][currentPos.column] = currentTurn;
    // else if the spot is invalid display an error message to the user and decrease rounds by 1
    else {
        cout << endl << "Error: You may not choose that position!" << endl;
        numRounds--;
    }
}

/* ================================================================ */

/*
    GetPosition will locate the row and column number that corresponds to the 2D array TicTacToe game board based
    on the play position the user requested.
    Parameters:
        positionNum: The requested play position the user chose (1 - 9 based on the 3x3 2D game board)
    Return Value: Position struct that represents a row and column coordinate
*/

Position GetPosition(int positionNum) {
    Position currentPos = {};
    
    switch (positionNum) {
        case 1:
            currentPos.row = 0, currentPos.column = 0;
            break;
        case 2:
            currentPos.row = 0, currentPos.column = 1;
            break;
        case 3:
            currentPos.row = 0, currentPos.column = 2;
            break;
        case 4:
            currentPos.row = 1, currentPos.column = 0;
            break;
        case 5:
            currentPos.row = 1, currentPos.column = 1;
            break;
        case 6:
            currentPos.row = 1, currentPos.column = 2;
            break;
        case 7:
            currentPos.row = 2, currentPos.column = 0;
            break;
        case 8:
            currentPos.row = 2, currentPos.column = 1;
            break;
        case 9:
            currentPos.row = 2, currentPos.column = 2;
            break;
        default:
            break;
    }

    return currentPos;
}

/* ================================================================ */

/*
    CheckForWinner runs after each turn in a game to check if a winner was found. This function contains three
    main code blocks that check if a winner was found in any of the rows, columns, or diagonals.
    Parameters:
        currentTurn: the current turn of X or O
        table: the current 2D array TicTacToe game board
    Return Value: true if a winner was found in the current game board
                  false if a winner was not found in the current game board
*/

bool CheckForWinner(char &currentTurn, char table[][3]) {
    bool winnerFound = false;
    int decrementColumn = 2;
    int numSpots = 0;

    // block checks if there was a win in any of the three rows
    for(int row = 0; row < 3; row++) {
        for(int column = 0; column < 3; column++)
            if(currentTurn == table[row][column])
                numSpots++;

        if(numSpots != 3)
            numSpots = 0;
    }

    // block checks if there was a win in any of the three columns
    if(numSpots != 3) {
        for(int row = 0; row < 3; row++) {
            for(int column = 0; column < 3; column++)
                if(currentTurn == table[column][row])
                    numSpots++;

            if(numSpots != 3)
                numSpots = 0;
        }
    }

    // block checks if there was a win diagonally
    if(numSpots != 3) {
        for(int i = 0; i < 3; i++)
            if(currentTurn == table[i][i])
                numSpots++;

        if(numSpots != 3) {
            numSpots = 0;

            for(int row = 0; row < 3; row++)
                if(currentTurn == table[row][decrementColumn--])
                    numSpots++;
        }
    }

    if(numSpots == 3)
        winnerFound = true;

    return winnerFound;
}

/* ================================================================ */

/*
    PlayAgain prompts the user if they would like to play another game of TicTacToe.
    Return Value: true if the user wants to play again
                  false if the user does not want to play again
*/

bool PlayAgain() {
    bool playAgain = true;
    char choice;

    // prompt the user if they want to play again
    cout << endl << "Would you like to play again? (Y/N): ";
    cin >> choice;

    // while the user does not enter a valid choice option
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        // clear cin buffer to prevent unnecessary looping
        cin.ignore(256, '\n');

        // print error message and prompt the user if they want to play again
        cout << endl << "Error: You must enter a 'Y' or 'N' value." << endl;
        cout << endl << "Would you like to play again? (Y/N): ";
        cin >> choice;
    }

    if(choice == 'N' || choice == 'n')
        playAgain = false;

    return playAgain;
}

/* ================================================================ */

/*
    ResetBoard resets the game board to empty positions.
    Parameters:
        table: the current 2D array TicTacToe game board
*/

void ResetBoard(char table[][3]) {
    for(int row = 0; row < 3; row++)
        for(int column = 0; column < 3; column++)
            table[row][column] = ' ';
}

/* ================================================================ */

/*
    PrintOutro prints the outro output.
*/

void PrintOutro() {
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "          Thanks for playing!          " << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}