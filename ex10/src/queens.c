#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queens.h"

bool isSafe(Cell **board, int row, int col, int N)
{
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i].figure == 'Q')
            return false;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j].figure == 'Q')
            return false;

    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j].figure == 'Q')
            return false;

    return true;
}

bool solveNQUtil(Cell **board, int col, int N)
{
    int i;
    if (col >= N)
        return true;

    for (i = 0; i < N; i++)
    {
        if ( isSafe(board, i, col, N) )
        {
            board[i][col].figure = 'Q';

            if ( solveNQUtil(board, col + 1, N) )
                return true;

            board[i][col].figure = 'E' ;
        }
    }
    return false;
}

void place_queens(Cell **table, int size)
{
    solveNQUtil(table, 1, size);
}