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
void Game();
    void PrintBoard(char table[][3]);
    void ValidatePosition(int &positionNum, Position &currentPos, char table[][3]);
    Position GetPosition(int positionNum);
    bool CheckForWinner(char &currentTurn, char table[][3]);
bool PlayAgain();
void PrintOutro();

/* ================================================================ */

int main() {
    bool createGame = true;

    PrintHeading();

    // while loop to create a Game until the user does not want to play again
    while(createGame) {
        // create a single Game
        Game();

        // check if the user wants to play another game
        createGame = PlayAgain();
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
*/

void Game() {
    char table[][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char currentTurn = 'X';
    int numRounds = 0;
    int positionNum;
    bool gameFinished = false;
    Position currentPos = {};

    // while the game is not finished, each iteration represents one round of the game
    while(!gameFinished) {
        numRounds++;

        cout << endl << "          Current Turn: " << currentTurn << endl << endl;

        PrintBoard(table);

        // get a position that is a valid placement
        ValidatePosition(positionNum, currentPos, table);

        // assign the position in the game board to the current turn
        table[currentPos.row][currentPos.column] = currentTurn;

        // check for a winner after each placement
        gameFinished = CheckForWinner(currentTurn, table);

        // if the game resulted in a winner being found within 9 rounds of plays the game is over
        if(gameFinished) {
            cout << endl << "         " << currentTurn << " has won the game!" << endl << endl;
            PrintBoard(table);
        }

        // if the game results in no winner within 9 rounds of plays the game is a tie
        if(!gameFinished && numRounds == 9) {
            cout << endl << "        The game was a tie!" << endl << endl;
            PrintBoard(table);
            gameFinished = true;
        }

        // change the currentTurn to the next player's turn
        if(currentTurn == 'X')
            currentTurn = 'O';
        else
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
    ValidatePosition performs error checking on if the requested position is a valid entry and placement. The position
    number entered must be an integer between the values of 1 - 9. This function does not return until a valid
    placement is made on the game board.
    Parameters:
        positionNum: the play position the user chooses (1 - 9 based on the 3x3 2D game board)
        currentPos: Position struct that represents a row and column coordinate
        table: the current 2D array TicTacToe game board
*/

void ValidatePosition(int &positionNum, Position &currentPos, char table[][3]) {
    bool validPlacement = false;

    // keep looping until a valid placement is made
    while(!validPlacement) {
        // prompt the user to enter their position to play
        cout << endl << "         Play Position: ";
        cin >> positionNum;

        // keep looping until the user enters a valid position
        while(!cin || positionNum < 1 || positionNum > 9) {
            // clear cin fail state and cin buffer to prevent extraneous data flowing in
            cin.clear();
            cin.ignore(256, '\n');

            cout << endl << "Error: You must enter a valid position!" << endl;

            // prompt the user to enter their position to play
            cout << endl << "         Play Position: ";
            cin >> positionNum;
        }

        currentPos = GetPosition(positionNum);

        if(table[currentPos.row][currentPos.column] == 'X' || table[currentPos.row][currentPos.column] == 'O')
            cout << endl << "Error: You may not choose a position that is taken!" << endl;
        else
            validPlacement = true;

        // clear cin buffer to prevent extraneous data from entering
        cin.ignore(256, '\n');
    }
}

/* ================================================================ */

/*
    GetPosition will locate the row and column number that corresponds to the 2D array TicTacToe game board based
    on the play position the user requested.
    Parameters:
        positionNum: the requested play position the user chose (1 - 9 based on the 3x3 2D game board)
    Return Value: Position struct that represents a row and column coordinate
*/

Position GetPosition(const int positionNum) {
    Position currentPos = {};

    switch(positionNum) {
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

    // clear cin buffer to prevent extraneous data from entering
    cin.ignore(256, '\n');

    return playAgain;
}

/* ================================================================ */

/*
    PrintOutro prints the outro output.
*/

void PrintOutro() {
    cout << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "          Thanks for playing!          " << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}