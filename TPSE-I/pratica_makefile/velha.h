#ifndef VELHA_H_INCLUDED
#define VELHA_H_INCLUDED

typedef struct Game {
    char board[3][3];
    char current_player;
} Game;

#define EMPTY ' '
#define PLAYER1 'X'
#define PLAYER2 'O'

#define INVALID_MOVE 0
#define VALID_MOVE 1

#define PLAYER1_WIN 1
#define PLAYER2_WIN 2
#define DRAW 3

Game* create_game();
int make_move(Game* game, int row, int column);
void print_board(Game* game);
int check_win(Game* game);
int check_draw(Game* game);
void destroy_game(Game* game);

#endif // VELHA_H_INCLUDED
