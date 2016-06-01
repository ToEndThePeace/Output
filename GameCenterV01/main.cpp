#include <cstdlib>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <vector>
#include <fstream>

typedef int* array;

using namespace std;

class BoardClass {
public:
    BoardClass(int, int);
    
    void output();
    // These functions are for player types and turns
    void play();
    // This method checks all win conditions
    bool isWin();
    // This method switches the turn int
    void nextTurn();
    // This method announces the winner all fancy-like.
    void winner();
    int numTurns;
private:
    int user();
    int easy();
    int hard();
    void setLoc(int);
    int p1;
    int p2;
    int turn; // The player who went last
    array* b;
};

void tic();

int main(int argc, char** argv) {
    srand(time(0));
    
    cout << "**************************" << endl <<
            "* Welcome to GameCenter! *" << endl <<
            "**************************" << endl;
    int input(0);
    do {
        cout << endl <<
                "What would you like to play?" << endl <<
                "1: Tic-Tac-Toe" << endl <<
                "2: Ask me again." << endl <<
                "3: Nothing, I want to exit." << endl <<
                ">> ";
        cin >> input;
        
        switch(input) {
            case 1:
                tic();
                break;
            case 2:
                cout << "Alright." << endl;
                break;
            case 3:
                cout << "No problem! Thanks for playing!" << endl;
        }
        
    } while (input != 3);
    
    return 0;
}

void tic() {
    cout << endl <<
            "***************************" << endl <<
            "* Welcome to Tic-Tac-Toe! *" << endl <<
            "***************************" << endl;
    int input;
    do {
        cout << endl <<
                "How would you like to play?" << endl <<
                "1: Player     vs.  Player" << endl <<
                "2: Player     vs.  CPU (Easy)" << endl <<
                "3: Player     vs.  CPU (Hard)" << endl <<
                "4: CPU (Easy) vs.  CPU (Easy)" << endl <<
                "5: I wouldn't, take me to the home menu." << endl <<
                ">> ";
        cin >> input;
        int a, b;
        switch (input) {
            case 1:
                a = 0;
                b = 0;
                break;
            case 2:
                a = 0;
                b = 1;
                break;
            case 3:
                a = 0;
                b = 2;
                break;
            case 4:
                a = 1;
                b = 1;
                break;
            case 5:
                cout << "Alright." << endl;
        }
        BoardClass x(a, b);
        if (input != 5) {
            do {
                x.play();
            } while (!x.isWin() && x.numTurns < 9);
            x.winner();
        }
    } while (input != 5);
}

// BoardClass code below //
/**
 * Creates an instance of BoardClass
 * Player types: 0 - User, 1 - Easy AI, 2 - Hard AI
 * @param x player 1 type
 * @param y player 2 type
 */
BoardClass::BoardClass(int x, int y) {
    // This fills all the private variables
    p1 = x;
    p2 = y;
    turn = 2;
    numTurns = 0;
    
    // And this makes the board
    b = new array[3];
    // This loop adds columns to the empty rows
    for (int i = 0; i < 3; i++) {
        b[i] = new int[3];
        // This loop uses the outer loop to initialize each board spot with a 0
        for (int j = 0; j < 3; j++) {
            b[i][j] = 0;
        }
    }
}

void BoardClass::output() {
    cout << "     1   2   3  " << endl <<
            "   –––––––––––––" << endl <<
            " A | " << (b[0][0] == 1 ? 'X' : b[0][0] == 2 ? 'O' : ' ') << 
              " | " << (b[0][1] == 1 ? 'X' : b[0][1] == 2 ? 'O' : ' ') << 
              " | " << (b[0][2] == 1 ? 'X' : b[0][2] == 2 ? 'O' : ' ') << 
              " |" << endl << "   –––––––––––––" << endl <<
            " B | " << (b[1][0] == 1 ? 'X' : b[1][0] == 2 ? 'O' : ' ') << 
              " | " << (b[1][1] == 1 ? 'X' : b[1][1] == 2 ? 'O' : ' ') << 
              " | " << (b[1][2] == 1 ? 'X' : b[1][2] == 2 ? 'O' : ' ') << 
              " |" << endl << "   –––––––––––––" << endl <<
            " C | " << (b[2][0] == 1 ? 'X' : b[2][0] == 2 ? 'O' : ' ') << 
              " | " << (b[2][1] == 1 ? 'X' : b[2][1] == 2 ? 'O' : ' ') << 
              " | " << (b[2][2] == 1 ? 'X' : b[2][2] == 2 ? 'O' : ' ') << 
              " |" << endl <<"   –––––––––––––" << endl;
            
}
bool BoardClass::isWin() {
    // Uses BoardClass->turn as a basis for checking -
    // Only the person who just went could have won
    int countD(0), countX(0);
    bool win(false);
    for (int i = 0; i < 3; i++) {
        // Rows and Columns
        int countR(0), countC(0);
        for  (int j = 0; j < 3; j++) {
            if (b[i][j] == turn) countR++;
            if (b[j][i] == turn) countC++;
        }
        if (countC == 3 || countR == 3) win = true;
        
        // Diagonal and Counter-Diagonal
        if (b[i][i] == turn) countD++;
        if (b[i][2-i] == turn) countX++;
    }
    if (countD == 3 || countX == 3) win = true;
    return win;
}

int BoardClass::user() {
    int loc(4);
    bool valid;
    do {
        output();
        valid = true;
        char c;
        int i;
        do {
            cout << "Row: ";
            cin >> c ;
            if (tolower(c) != 'a' && tolower(c) != 'b' && tolower(c) != 'c') {
                cout << "Invalid row." << endl;
            }
        } while (tolower(c) != 'a' && tolower(c) != 'b' && tolower(c) != 'c');
        do {
            cout << "Column: ";
            cin >> i ;
            if (i != 1 && i != 2 && i != 3) {
                cout << "Invalid column." << endl;
            }
        } while (i != 1 && i != 2 && i != 3);
        if (tolower(c) == 'a') {
            if (i == 1) {
                if (b[0][0] != 0) valid = false;
                else loc = 0;
            } else if (i == 2) {
                if (b[0][1] != 0) valid = false;
                else loc = 1;
            } else if (i == 3) {
                if (b[0][2] != 0) valid = false;
                else loc = 2;
            }
        } else if (tolower(c) == 'b') {
            if (i == 1) {
                if (b[1][0] != 0) valid = false;
                else loc = 3;
            } else if (i == 2) {
                if (b[1][1] != 0) valid = false;
                else loc = 4;
            } else if (i == 3) {
                if (b[1][2] != 0) valid = false;
                else loc = 5;
            }
        } else if (tolower(c) == 'c') {
            if (i == 1) {
                if (b[2][0] != 0) valid = false;
                else loc = 6;
            } else if (i == 2) {
                if (b[2][1] != 0) valid = false;
                else loc = 7;
            } else if (i == 3) {
                if (b[2][2] != 0) valid = false;
                else loc = 8;
            }
        }
        if (!valid) cout << "That space is already full!" << endl;
    } while (!valid);
    return loc;
}
int BoardClass::easy() {
    output();
    int loc(4);
    bool valid;
    do {
        valid = true;
        int i = rand() % 3 + 1;
        int i2 = rand() % 3 + 1;
        char c;
        switch (i2) {
            case 1:
                c = 'a';
                break;
            case 2:
                c = 'b';
                break;
            case 3:
                c = 'c';
        }
        if (tolower(c) == 'a') {
            if (i == 1) {
                if (b[0][0] != 0) valid = false;
                else loc = 0;
            } else if (i == 2) {
                if (b[0][1] != 0) valid = false;
                else loc = 1;
            } else if (i == 3) {
                if (b[0][2] != 0) valid = false;
                else loc = 2;
            }
        } else if (tolower(c) == 'b') {
            if (i == 1) {
                if (b[1][0] != 0) valid = false;
                else loc = 3;
            } else if (i == 2) {
                if (b[1][1] != 0) valid = false;
                else loc = 4;
            } else if (i == 3) {
                if (b[1][2] != 0) valid = false;
                else loc = 5;
            }
        } else if (tolower(c) == 'c') {
            if (i == 1) {
                if (b[2][0] != 0) valid = false;
                else loc = 6;
            } else if (i == 2) {
                if (b[2][1] != 0) valid = false;
                else loc = 7;
            } else if (i == 3) {
                if (b[2][2] != 0) valid = false;
                else loc = 8;
            }
        }
    } while (!valid);
    return loc;
}
int BoardClass::hard() {
    int loc; // The location to play the turn, 0-8
    output();
    
    
    // Check for a win condition
    
    /*
    // Check to see if the person with center can win
    int x = b[1][1];
    if (x != 0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i != 1 || j != 1) {
                    if (b[i][j] == x) {
                        switch (i + j) {
                            case 0:
                                loc = 8;
                                break;
                            case 1:
                                if (i == 0) loc = 7;
                                else        loc = 5;
                                break;
                            case 2:
                                if (i == 0) loc = 6;
                                else        loc = 2;
                                break;
                            case 3:
                                if (i == 1) loc = 3;
                                else        loc = 1;
                                break;
                            case 4:
                                loc = 0;
                        }
                    }
                }
            }
        }
    }
    x = b[0][2];
    if (x != 0) { // Checking top-right relatives
        if (b[0][1] == x) loc = 0;
        else if (b[0][0] == x) loc = 1;
        else if (b[1][2] == x) loc = 8;
        else if (b[2][2] == x) loc = 5;
    }
    x = b[2][0];
    if (x != 0) { // bot-left relatives
        if (b[0][0] == x) loc = 3;
        else if (b[1][0] == x) loc = 0;
        else if (b[2][1] == x) loc = 8;
        else if (b[2][2] == x) loc = 7;
    }
    // End of win condition check
    
    // Block a Fork
    // This code checks to see if a fork can be made
    // Switch statement says whether to make or block the fork
        
        */
        
        
    // This is me being an optimist and hoping that this will be short
    
    int count(0);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = b[i][j];
            switch (count) {
                case 0:
                    if (x == b[0][1] && b[0][2] == 0) loc = 2;
                    else if (x == b[0][2] && b[0][1] == 0) loc = 1;
                    else if (x == b[1][0] && b[2][0] == 0) loc = 3;
                    else if (x == b[2][0] && b[1][0] == 0) loc = 6;
                    else if (x == b[1][1] && b[2][2] == 0) loc = 8;
                    else if (x == b[2][2] && b[1][1] == 0) loc = 4;
                    break;
                case 1:
                    if (x == b[1][1] && b[2][1] == 0) loc = 7;
                    else if (x == b[2][1] && b[1][1] == 0) loc = 4;
                    break;
                case 2:
                    if (x == b[1][1] && b[2][0] == 0) loc = 6;
                    else if (x == b[2][0] && b[1][1] == 0) loc = 4;
                    else if (x == b[1][2] && b[2][2] == 0) loc = 8;
                    else if (x == b[2][2] && b[1][2] == 0) loc = 5;
                    break;
                case 3:
                    if (x == b[1][1] && b[1][2] == 0) loc = 5;
                    else if (x == b[1][2] && b[1][1] == 0) loc = 4;
                    break;
                case 6:
                    if (x == b[2][1] && b[2][2] == 0) loc = 8;
                    else if (x == b[2][2] && b[2][1] == 0) loc = 7;
            }
            count++;
        }
    }
        
    return loc;
}
void BoardClass::play() {
    nextTurn(); // Start the turn by swapping the number
    if (turn == 1) { // P1 Turn
        switch (p1) {
            case 0:
                setLoc(user());
                break;
            case 1:
                setLoc(easy());
                break;
            case 2:
                setLoc(hard());
        }
    } else {
        switch (p2) {
            case 0:
                setLoc(user());
                break;
            case 1:
                setLoc(easy());
                break;
            case 2:
                setLoc(hard());
        }
    }
    numTurns++;
}
void BoardClass::nextTurn() {
    if (turn == 1) turn = 2;
    else turn = 1;
}
void BoardClass::winner() {
    if (isWin()) {
        switch (turn) {
            case 1:
                cout << "X's win!" << endl;
                break;
            case 2:
                cout << "O's win!" << endl;
        }
    } else if (numTurns == 9) {
        cout << "It's a tie!" << endl;
    }
    cin.get();
}
void BoardClass::setLoc(int loc) {
    switch (loc) {
        case 0:
            b[0][0] = turn;
            break;
        case 1:
            b[0][1] = turn;
            break;
        case 2:
            b[0][2] = turn;
            break;
        case 3:
            b[1][0] = turn;
            break;
        case 4:
            b[1][1] = turn;
            break;
        case 5:
            b[1][2] = turn;
            break;
        case 6:
            b[2][0] = turn;
            break;
        case 7:
            b[2][1] = turn;
            break;
        case 8:
            b[2][2] = turn;
            break;
    }
}