#ifndef LIBSCALESPACE_H
#define LIBSCALESPACE_H

#include <iostream>
#include <sstream>
#include <vector>
#include "functional"

using namespace std;

namespace ScaleSpace
{
    enum sError
    {
        SUCCESS,
        CONV_ERR = -1,

    };

    enum features
    {
        SPACE,
        PLAYER = 1,
        WEIGHTS = 2
    };

    enum gamestate
    {
        RUNNING,
        WON,
        LOST,
        QUIT
    };

    struct Gamecell
    {
        features gfeature;
        int intScale;
    };

    const string ENTITIES[3] = {". ", "P ", "o "};

    typedef Gamecell *OneD_arr;
    typedef OneD_arr *TwoD_arr;

    struct gameB
    {
        TwoD_arr game;
        int introws;
        int intcols;
        int pRows;
        int pCols;
        int pWeight;
        gamestate Gamestatus;
    };

    TwoD_arr alloc_Mem(int intRow, int intCol); // function for allocating memory;
    int string_to_int(string str);              // function for converting a string into an integer;
    int genRand(int low, int high);             // function for generating random number
    void dealloc(gameB &Board);                 // function for deallocating memory
    void displayBoard(gameB &Board);            // function for displaying the board
    void place_weights(gameB &Board, int num_weights, std::function<int(int, int)> genRand);
    void place_scale(gameB &Board, int num_weights, int numScales);
    gameB initboard(int intRows, int intCols, int num_weight, int num_scale);
    bool isInGame(gameB &Board, int intRow, int intCol);
    void movePlayer(gameB &Board, char chOption);
    void check_scale(gameB &Board);

}

#endif // LIBSCALESPACE_H
