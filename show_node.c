#include "ttt.h"

int main(int argc, char const *argv[])
{
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
    compute_score();

    // prints all my friends
    for(int i = 1; i < argc; i++)
    {
        print_node(htable[atoi(argv[i])]);
    }

    return 0;
}
