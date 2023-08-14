#include <stdio.h>
#include <stdlib.h>
#include "velha.h"

Game* create_game() {
    Game* game = (Game*)malloc(sizeof(Game));
    game->current_player = PLAYER1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            game->board[i][j] = EMPTY;
        }
    }
    return game;
}

int make_move(Game* game, int row, int column) {
    if (row < 0 || row > 2 || column < 0 || column > 2 || game->board[row][column] != EMPTY) {
        return INVALID_MOVE;
    }
    game->board[row][column] = game->current_player;
    if (game->current_player == PLAYER1) {
        game->current_player = PLAYER2;
    } else {
        game->current_player = PLAYER1;
    }
    return VALID_MOVE;
}

void print_board(Game* game) {
    printf("\n");
    printf(" %c | %c | %c \n", game->board[0][0], game->board[0][1], game->board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", game->board[1][0], game->board[1][1], game->board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", game->board[2][0], game->board[2][1], game->board[2][2]);
    printf("\n");
}

int check_win(Game* game) {
    char winner;
    for (int i = 0; i < 3; i++) {
        if (game->board[i][0] == game->board[i][1] && game->board[i][1] == game->board[i][2] && game->board[i][0] != EMPTY) {
            winner = game->board[i][0];
            if (winner == PLAYER1) {
                return PLAYER1_WIN;
            } else {
                return PLAYER2_WIN;
            }
        }
        if (game->board[0][i] == game->board[1][i] && game->board[1][i] == game->board[2][i] && game->board[0][i] != EMPTY) {
            winner = game->board[0][i];
            if (winner == PLAYER1) {
                return PLAYER1_WIN;
            } else {
                return PLAYER2_WIN;
            }
        }
    }
    if (game->board[0][0] == game->board[1][1] && game->board[1][1] == game->board[2][2] && game->board[0][0] != EMPTY) {
        winner = game->board[0][0];
        if (winner == PLAYER1) {
            return PLAYER1_WIN;
        } else {
            return PLAYER2_WIN;
        }
    }
    if (game->board[2][0] == game->board[1][1] && game->board[1][1] == game->board[0][2] && game->board[2][0] != EMPTY) {
        winner = game->board[2][0];
        if (winner == PLAYER1) {
            return PLAYER1_WIN;
        } else {
            return PLAYER2_WIN;
        }
    }
    return 0;
}

int check_draw(Game* game) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game->board[i][j] == EMPTY) {
                return 0;
            }
        }
    }
    return 1;
}

void destroy_game(Game* game) {
    free(game);
}
