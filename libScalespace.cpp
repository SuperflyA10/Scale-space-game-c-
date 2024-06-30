#include "libScalespace.h"

namespace ScaleSpace
{
    int string_to_int(string str)
    {
        int intNum;
        stringstream ss{str};
        ss >> intNum;
        if (ss.fail())
        {
            cerr << str << " cannot be converted into an integer." << endl;
        }
        return intNum;
    }

    int genRand(int low, int high)
    {
        int num;
        num = low + (rand() % high - low + 1);
        return num;
    }

    TwoD_arr alloc_Mem(int intRow, int intCol)
    {
        TwoD_arr Game = new OneD_arr[intRow];
        for (int r = 0; r < intRow; r++)
        {
            Game[r] = new Gamecell[intCol];
            for (int c = 0; c < intCol; c++)
            {
                Game[r][c].gfeature = SPACE;
                Game[r][c].intScale = 0;
            }
        }
        return Game; // Return the allocated memory
    }

    // Display the Game World
    void displayBoard(gameB &Board)
    {
        // Clear Screen
        system("cls");

        // Print World
        for (int r = 0; r < Board.introws; r++)
        {
            for (int c = 0; c < Board.intcols; c++)
            {
                if (Board.game[r][c].intScale == 0 || Board.game[r][c].gfeature == PLAYER)
                {
                    cout << ENTITIES[Board.game[r][c].gfeature];
                    // cout << Board.game[r][c].intScale;
                }
                else
                {
                    // cout << ENTITIES[Board.game[r][c].gfeature];
                    cout << Board.game[r][c].intScale;
                }
            }
            cout << endl;
        }
        cout << "Number of wieghts collected: " << Board.pWeight;
        // Print Menu
        cout << endl;
        cout << "A) Left Q) Top Left W) Up E) Top Right D) Right C) Bottom Right S) Down Z) Bottom Left" << " T) Drop Weights" << endl;
        cout << "X) Exit" << endl
             << endl;
    }

    void place_weights(gameB &Board, int num_weights, std::function<int(int, int)> genRand)
    {
        for (int i = 0; i < num_weights; i++)
        {
            int r, c;
            do
            {
                r = genRand(0, Board.introws - 1);
                c = genRand(0, Board.intcols - 1);
            } while (Board.game[r][c].gfeature != SPACE);
            Board.game[r][c].gfeature = WEIGHTS;
        }
    }

    void place_scale(gameB &Board, int num_weights, int numScales)
    {

        int weights[numScales];
        int s;

        do
        {
            s = 0;
            for (int i = 0; i < numScales; i++)
            {

                weights[i] = rand() % num_weights + 1;
                s += weights[i];
            }
        } while (s != num_weights);

        for (int i = 0; i < numScales; i++)
        {
            int r = genRand(0, Board.introws - 1);
            int c = genRand(0, Board.intcols - 1);
            do
            {
                r = genRand(0, Board.introws - 1);
                c = genRand(0, Board.intcols - 1);
                // if(Board.game[r][c]==SPACE)

            } while (Board.game[r][c].gfeature != SPACE);
            Board.game[r][c].intScale += weights[i];
        }
    }

    void place_player(gameB &Board)
    {
        int r = Board.introws / 2;
        int c = Board.intcols / 2;
        Board.game[r][c].gfeature = PLAYER;
        Board.pRows = r;
        Board.pCols = c;
    }

    gameB initboard(int intRows, int intCols, int num_weight, int num_scale)
    {
        gameB Play;
        Play.introws = intRows;
        Play.intcols = intCols;
        // Allocate Memory
        Play.game = alloc_Mem(intRows, intCols);
        // Place weights
        // place_wieghts(Play, num_weight);
        place_weights(Play, num_weight, [](int low, int high)
                      { return low + (rand() % (high - low + 1)); });
        // Place scales
        place_scale(Play, num_weight, num_scale);
        // Place Operator
        place_player(Play);
        // Set other Values
        Play.pWeight = 0;
        Play.Gamestatus = RUNNING;

        return Play;
    }

    bool isInGame(gameB &Board, int intRow, int intCol)
    {
        if (intRow >= 0 && intRow < Board.introws && intCol >= 0 && intCol < Board.intcols)
        {
            return true;
        }
        return false;
    }

    void movePlayer(gameB &Board, char chOption)
    {

        // Destination Values
        int intDR = Board.pRows;
        int intDC = Board.pCols;

        switch (chOption)
        {
        case 'a':
        {
            intDC--;
            break;
        }
        case 'q':
        {
            intDC--;
            intDR--;
            break;
        }
        case 'w':
        {
            intDR--;
            break;
        }
        case 'e':
        {
            intDR--;
            intDC++;
            break;
        }
        case 'd':
        {
            intDC++;
            break;
        }
        case 'c':
        {
            intDC++;
            intDR++;
            break;
        }
        case 'z':
        {
            intDC--;
            intDR++;
            break;
        }
        case 's':
        {
            intDR++;
            break;
        }
        case 't':
        {
            if (Board.pWeight > 0)
            {
                int r = intDR + (rand() % 3 - 1);
                int c = intDC + (rand() % 3 - 1);
                // Check bounds
                do
                {
                    r = intDR + (rand() % 3 - 1);
                    c = intDC + (rand() % 3 - 1);
                } while (r < 0 || r > Board.introws || c < 0 || c > Board.intcols ||
                         Board.game[r][c].gfeature != SPACE || Board.game[r][c].intScale != 0);

                Board.game[r][c].gfeature = WEIGHTS; // Place weight
                Board.pWeight--;                     // Drop the weights
            }
            else
            {
                cout << "You have lost, no weights to drop." << endl;
                system("Pause");
                Board.Gamestatus = LOST;
            }
        }
        }

        if (isInGame(Board, intDR, intDC))
        {
            if (Board.game[intDR][intDC].gfeature == WEIGHTS)
            {
                Board.pWeight += 1;
                Board.game[Board.pRows][Board.pCols].gfeature = SPACE;
                Board.pRows = intDR;
                Board.pCols = intDC;
                Board.game[intDR][intDC].gfeature = PLAYER;
            }
            else if (Board.game[intDR][intDC].intScale > 0)
            {
                if (Board.pWeight == 0)
                {
                    Board.game[Board.pRows][Board.pCols].gfeature = SPACE;
                    Board.pRows = intDR;
                    Board.pCols = intDC;
                    Board.game[intDR][intDC].gfeature = PLAYER;
                }
                else if (Board.game[intDR][intDC].intScale == Board.pWeight)
                {
                    Board.pWeight = 0;
                    Board.game[Board.pRows][Board.pCols].gfeature = SPACE;
                    Board.game[intDR][intDC].intScale = 0;
                    Board.pRows = intDR;
                    Board.pCols = intDC;
                    Board.game[intDR][intDC].gfeature = PLAYER;
                    check_scale(Board);
                }
                else
                {
                    cout << "You have lost, wrong total weights for the scale entered." << endl;
                    system("Pause");
                    Board.Gamestatus = LOST;
                }
            }
            else if (Board.game[intDR][intDC].gfeature == SPACE || Board.game[intDR][intDC].intScale == 0)
            {
                // Move Player to Next Cell
                Board.game[Board.pRows][Board.pCols].gfeature = SPACE;
                Board.pRows = intDR;
                Board.pCols = intDC;
                Board.game[intDR][intDC].gfeature = PLAYER;
            }
        }
    }

    void dealloc(gameB &Board)
    {
        for (int r = 0; r < Board.introws; r++)
        {
            delete[] Board.game[r];
        }
        delete[] Board.game;
        Board.game = nullptr;
    }

    void check_scale(gameB &Board)
    {
        Board.Gamestatus = WON;
        for (int r = 0; r < Board.introws; r++)
        {
            for (int c = 0; c < Board.intcols; c++)
            {
                if (Board.game[r][c].intScale > 0)
                {
                    Board.Gamestatus = RUNNING;
                }
            }
        }
    }

}
