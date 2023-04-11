#include <stdio.h>
#include <stdlib.h>
#include "velha.h"

int main() {
    Game* game = create_game();
    int row, column, move_result, game_result;
    while (1) {
        print_board(game);
        printf("Player %c, enter row (1-3): ", game->current_player);
        scanf("%d", &row);
        printf("Player %c, enter column (1-3): ", game->current_player);
        scanf("%d", &column);
        move_result = make_move(game, row - 1, column - 1);
        if (move_result == INVALID_MOVE) {
            printf("Invalid move!\n");
        } else {
            game_result = check_win(game);
            if (game_result == PLAYER1_WIN) {
                print_board(game);
                printf("Player 1 wins!\n");
                break;
            } else if (game_result == PLAYER2_WIN) {
                print_board(game);
                printf("Player 2 wins!\n");
                break;
            } else if (check_draw(game)) {
                print_board(game);
                printf("Draw!\n");
                break;
            }
        }
    }
    destroy_game(game);
    return 0;
}
