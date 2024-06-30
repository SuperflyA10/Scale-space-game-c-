#include <iostream>
#include "libScalespace.h"
#include "libScalespace.h"
#include "assert.h"
#include "time.h"

using namespace std;

using namespace ScaleSpace;

int main(int argc, char **argv)
{
    // Random Number Seed
    srand(time(nullptr));

    assert(argc == 5);

    int intRows, intCols, intWeights, numScales;

    intRows = string_to_int(argv[1]);
    intCols = string_to_int(argv[2]);
    intWeights = string_to_int(argv[3]);
    numScales = string_to_int(argv[4]);

    cout << "Number of Rows: " << intRows << endl
         << "Number of columns: " << intCols << endl
         << "Number of weights: " << intWeights << endl
         << "Number of scales: " << numScales << endl;
    system("Pause");

    gameB World = initboard(intRows, intCols, intWeights, numScales);
    bool blnContinue = true;
    char chOption = '\0';
    do
    {
        // cout << "Running";
        //  Display World
        displayBoard(World);
        cin >> chOption;
        chOption = tolower(chOption);
        switch (chOption)
        {
        case 'a':
        case 'q':
        case 'w':
        case 'e':
        case 'd':
        case 'c':
        case 'z':
        case 's':
        case 't':
        {
            // Move Player
            movePlayer(World, chOption);
            break;
        }
        case 'x':
        {
            cout << "Quitting game, thank you for playing" << endl;
            // dealloc(World);
            World.Gamestatus = QUIT;
            break;
        }
        default:
        {
            cerr << "Wrong character entered, please try again" << endl;
            break;
        }
        }
        if (World.Gamestatus == WON)
        {
            cout << "You have won, all scale have been filled.";
            blnContinue = false;
        }
        else if (World.Gamestatus != RUNNING)
        {
            blnContinue = false;
        }
    } while (blnContinue);

    // Check for game ending based on state

    // Deallocate Memory - Give back memory to Free Store
    dealloc(World);

    return SUCCESS;
}
