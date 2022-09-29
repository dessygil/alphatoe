#include "ttt.h"

//helper functions declared here
int helperWinner(Board board, char charGiven);
int helperCompute(Board board);
int max(int a, int b);
int min(int a, int b);

// I didn't see the need to use ptr arithmetic
void init_boards()
{
    for (int i = 0; i < HSIZE; i++)
    {
        htable[i].init = 0;
    }
}

// easy boi
int depth(Board board)
{
    int depth = 0;
    for (int i = 0; i < 9; i++)
    {
        if (board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O')
        {
            depth++;
        }
    }
    return depth;
}

// I think it gets the int wins from ttt1
char winner(Board board)
{
    if (helperWinner(board, 'X'))
    {
        return 'X';
    }
    else if (helperWinner(board, 'O'))
    {
        return 'O';
    }
    else if (depth(board) == 9)
    {
        return '-';
    }
    else
    {
        return '?';
    }
}

// returns 1 if a winner is found else returns 0
int helperWinner(Board board, char charGiven)
{
    int checker = 0;
    for (int i = 0; i < 8; i++)
    {
        checker = 0;
        for (int j = 0; j < 3; j++)
        {
            if (board[pos2idx[WINS[i][j]]] == charGiven)
            {
                checker++;
                if (checker == 3)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

char turn(Board board)
{
    int boardhash = board_hash(board);

    if (depth(board) == 9 || htable[boardhash].winner == 'X' || htable[boardhash].winner == 'O')
    {
        return '-';
    }
    else if (depth(board) % 2 == 0)
    {
        return 'X';
    }
    else
    {
        return 'O';
    }
}

void init_board(Board board)
{
    int hashValue = board_hash(board);

    strcpy(htable[hashValue].board, board);
    htable[hashValue].init = 1;
    htable[hashValue].winner = winner(board);
    htable[hashValue].turn = turn(board);
    htable[hashValue].depth = depth(board);
}

// first off wth
void join_graph(Board board)
{

    // this is the base case
    if (depth(board) == 9)
    {
        return;
    }
    int hashValue = board_hash(board);

    // check for values to set to -1
    for (int i = 0; i < 9; i++)
    {
        if (board[pos2idx[i]] == 'O' || board[pos2idx[i]] == 'X')
        {
            htable[hashValue].move[i] = -1;
        }
    }

    if (htable[hashValue].winner == 'X' || htable[hashValue].winner == 'O')
    {
        for (int i = 0; i < 9; i++)
        {
            htable[hashValue].move[i] = -1;
        }
    }

    char turnChecker;
    // for every node that is  not -1 we call join graph with an x and an o
    for (int i = 0; i < 9; i++)
    {

        char tempBoard[BSIZE];
        strcpy(tempBoard, board);

        if (htable[hashValue].move[i] != -1)
        {
            turnChecker = htable[hashValue].turn;
            tempBoard[pos2idx[i]] = turnChecker;

            htable[hashValue].move[i] = board_hash(tempBoard);
            //printf(" %d\n %s\n",board_hash(tempBoard), tempBoard);
            if (htable[board_hash(tempBoard)].init == 0)
            {
                init_board(tempBoard);
                join_graph(tempBoard);
            }
        }
    }
}

void compute_score()
{
    for (int i = 9; i > -1; i--)
    {
        for (int j = 0; j < HSIZE; j++)
        {
            if (htable[j].init == 1 && htable[j].depth == i)
            {
                if (htable[j].winner == 'X')
                {
                    htable[j].score = 1;
                }
                else if (htable[j].winner == 'O')
                {
                    htable[j].score = -1;
                }
                else if (htable[j].winner == '-')
                {
                    htable[j].score = 0;
                }
                else if (i != 9)
                {
                    if (htable[j].turn == 'X')
                    {
                        int score = 0;
                        for (int k = 0; k < 9; k++)
                        {
                            if (htable[j].move[k] != -1)
                            {
                                if (htable[htable[j].move[k]].score > score)
                                {
                                    score = htable[htable[j].move[k]].score;
                                }
                            }
                        }
                        htable[j].score = score;
                    }
                    else if (htable[j].turn == 'O')
                    {
                        int score = 100;
                        for (int k = 0; k < 9; k++)
                        {
                            if (htable[j].move[k] != -1)
                            {
                                if (htable[htable[j].move[k]].score < score)
                                {
                                    score = htable[htable[j].move[k]].score;
                                }
                            }
                        }
                        htable[j].score = score;
                    }
                }
            }
        }
    }
}


int best_move(int board)
{
    int positionHolder = 0;
    if (htable[board].turn == 'X')
    {
        int score = -2;
        for (int i = 0; i < 9; i++)
        {
            if (htable[board].move[i] != -1)
            {
                if (htable[htable[board].move[i]].score > score)
                {
                    score = htable[htable[board].move[i]].score;
                    positionHolder = i;
                }
            }
        }
    }
    else if (htable[board].turn == 'O')
    {
        int score = 2;
        for (int i = 0; i < 9; i++)
        {
            if (htable[board].move[i] != -1)
            {
                if (htable[htable[board].move[i]].score < score)
                {
                    score = htable[htable[board].move[i]].score;
                    positionHolder = i;
                }
            }
        }
    }
    return positionHolder;
}
