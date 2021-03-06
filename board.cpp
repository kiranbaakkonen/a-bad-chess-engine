#include "board.h"
#include <iostream>
#include <cstdio>

void Board::loadBoard(piece pieces[8][8], player players[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i+2][j+2] = pieces[i][j];
            color[i+2][j+2] = players[i][j];
        }
    }
}


void Board::printBoard(){
    std::cout << "Printing Current state of board\n";
    for(int i = 9; i > 1; i--){
        for(int j = 2; j < 10; j++){
            printf("%02d ", board[i][j]);
        }
        printf("\n\n");
    }
}

void Board::printMoveSet(move moves[12][12]){
    for(int i = 9; i > 1; i--){
        for(int j = 2; j < 10; j++){
            printf("%02d ", moves[i][j]);
        }
        printf("\n\n");
    }
}

void Board::getValidMoves(move moves[12][12], int row, int col){
    int actual_row = row + 2;
    int actual_col = col + 2;
    int p = board[actual_row][actual_col];
    int c = color[actual_row][actual_col];

    if(p == PAWN){
        std::cout << "Getting the moves for a pawn at " << row << "," << col << "\n";

        // stores the piece in front of the pawn
        int front_p;

        // stores the row in front of the pawn
        int fr;

        // stores the columns diagonal to the pawn
        int dlc = actual_col - 1;
        int drc = actual_col + 1;

        // stores the piece and color diagonal to the pawn
        int dleft;
        int dright;
        int dleft_c;
        int dright_c;

        bool start = false;
        int start_r;

        if(c == WHITE){
            front_p = board[actual_row+1][actual_col];
            dleft = board[actual_row+1][actual_col-1];
            dright = board[actual_row+1][actual_col+1];
            dleft_c = color[actual_row+1][actual_col-1];
            dright_c = color[actual_row+1][actual_col+1];

            fr = actual_row + 1;
            start_r = actual_row + 2;
            start = (row == 1)? true : false;
        }
        else if(c == BLACK){
            front_p = board[actual_row-1][actual_col];
            dleft = board[actual_row-1][actual_col-1];
            dright = board[actual_row-1][actual_col+1];
            dleft_c = color[actual_row-1][actual_col-1];
            dright_c = color[actual_row-1][actual_col+1];

            fr = actual_row - 1;
            start_r = actual_row - 2;
            start = (row == 6)? true : false;
        }

        if(front_p == EMPTY){
            moves[fr][actual_col] = MOVE;
        }

        if(dleft_c != NONE && dleft_c != c && dleft != KING){
            moves[fr][dlc] = ATTACK;
        }

        if(dright_c != NONE && dright_c != c && dright != KING){
            moves[fr][drc] = ATTACK;
        }

        if(start && board[start_r][actual_col] == EMPTY && moves[fr][actual_col] == MOVE){
            moves[start_r][actual_col] = MOVE;
        }
    }
    else if(p == KNIGHT){
        /*
            -  1  -  2  -
            8  -  -  -  3
            -  -  K  -  -
            7  -  -  -  4
            -  6  -  5  -
        */

        std::cout << "Getting the moves for a knight at " << row << "," << col << "\n";

        int rows[4] = {actual_row - 2, actual_row + 2, actual_row - 1, actual_row + 1};
        int cols[4] = {actual_col - 1, actual_col + 1, actual_col - 2, actual_col + 2};

        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                if(board[rows[i]][cols[j]] == EMPTY){
                    moves[rows[i]][cols[j]] = MOVE;
                }
                else if(color[rows[i]][cols[j]] != c && board[rows[i]][cols[j]] != INVALID && board[rows[i]][cols[j]] != KING){
                    moves[rows[i]][cols[j]] = ATTACK;
                }

                if(board[rows[i+2]][cols[j+2]] == EMPTY){
                    moves[rows[i+2]][cols[j+2]] = MOVE;
                }
                else if(color[rows[i+2]][cols[j+2]] != c && board[rows[i+2]][cols[j+2]] != INVALID && board[rows[i+2]][cols[j+2]] != KING){
                    moves[rows[i+2]][cols[j+2]] = ATTACK;
                }
            }
        }
    }
}


int main(){
    Board b;
    
    piece testBoard[8][8] = {
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, KNIGHT, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, PAWN, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };

    player testColor[8][8] = {
        {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        {NONE, NONE, NONE, NONE, WHITE, NONE, NONE, NONE},
        {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        {NONE, NONE, NONE, NONE, NONE, BLACK, NONE, NONE},
        {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}
    };

    b.loadBoard(testBoard, testColor);
    b.printBoard();

    move moves[12][12] = {};
    b.getValidMoves(moves, 4, 4);
    b.printMoveSet(moves);

    

}