//
//  main.c
//  knights_tour
//
//  Created by David Wagner on 16/02/2018.
//  Copyright © 2018 David Wagner. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#define KNIGHT_POSITIONS_EQUAL(a, b) (((a).column == (b).column) && ((a).row == (b).row))

static const unsigned int NumberOfColumns = 5;
static const unsigned int NumberOfRows = 5;

typedef struct {
    unsigned int row;
    unsigned int column;
} KnightPosition;

typedef enum  {
    Unvisited = 0,
} Square;

typedef struct {
    KnightPosition knightPosition;
    int move;
    Square board[NumberOfColumns][NumberOfRows];
} Game;

void print_game(const Game * const game) {
    printf("\n");
    printf("Game state:\n");
    printf("\tKnight position: %u, %u\n", game->knightPosition.column, game->knightPosition.row);
    printf("\tMove: %d\n", game->move);
    for (unsigned int row = 0; row < NumberOfRows; row++) {
        printf("\t\t");
        for (unsigned int column = 0; column < NumberOfColumns; column++) {
            printf("%3d ", game->board[column][row]);
        }
        printf("\n");
    }
}

Game new_game(KnightPosition startingPosition) {
    assert(startingPosition.row < NumberOfRows);
    assert(startingPosition.column < NumberOfColumns);

    Game game = { 0 };
    game.knightPosition = startingPosition;
    game.move = 1;
    game.board[startingPosition.column][startingPosition.row] = game.move;
    
    return game;
}

bool game_won(Game const * const game) {
    for (unsigned int row = 0; row < NumberOfRows; row++) {
        for (unsigned int column = 0; column < NumberOfColumns; column++) {
            if (game->board[column][row] == Unvisited) {
                return false;
            }
        }
    }
    
    return true;
}

bool move_knight(Game * const game, const KnightPosition newPosition) {
    // Bounds check
    if (newPosition.column >= NumberOfColumns) {
        return false;
    }
    if (newPosition.row >= NumberOfRows) {
        return false;
    }
    // Already visited check
    if (game->board[newPosition.column][newPosition.row] != Unvisited) {
        return false;
    }
    // Valid knight move check
    const KnightPosition a = {.column = game->knightPosition.column + 2, .row = game->knightPosition.row - 1};
    const KnightPosition b = {.column = game->knightPosition.column + 2, .row = game->knightPosition.row + 1};
    const KnightPosition c = {.column = game->knightPosition.column - 2, .row = game->knightPosition.row - 1};
    const KnightPosition d = {.column = game->knightPosition.column - 2, .row = game->knightPosition.row + 1};
    const KnightPosition e = {.column = game->knightPosition.column - 1, .row = game->knightPosition.row + 2};
    const KnightPosition f = {.column = game->knightPosition.column + 1, .row = game->knightPosition.row + 2};
    const KnightPosition g = {.column = game->knightPosition.column - 1, .row = game->knightPosition.row - 2};
    const KnightPosition h = {.column = game->knightPosition.column + 1, .row = game->knightPosition.row - 2};
    const bool validMove = (KNIGHT_POSITIONS_EQUAL(a, newPosition)
                            || KNIGHT_POSITIONS_EQUAL(b, newPosition)
                            || KNIGHT_POSITIONS_EQUAL(c, newPosition)
                            || KNIGHT_POSITIONS_EQUAL(d, newPosition)
                            || KNIGHT_POSITIONS_EQUAL(e, newPosition)
                            || KNIGHT_POSITIONS_EQUAL(f, newPosition)
                            || KNIGHT_POSITIONS_EQUAL(g, newPosition)
                            || KNIGHT_POSITIONS_EQUAL(h, newPosition));
    if (!validMove) {
        return false;
    }
    // Looks good, move
    game->knightPosition = newPosition;
    game->move++;
    game->board[newPosition.column][newPosition.row] = game->move;
    
    return true;
}

int main(int argc, const char * argv[]) {
    Game game = new_game((KnightPosition){.column = 0, .row = 0});
    assert(game_won(&game) == false);
    print_game(&game);
    
    assert(move_knight(&game, (KnightPosition){.column = 2, .row = 1}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 4, .row = 0}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 3, .row = 2}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 4, .row = 4}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 2, .row = 3}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 0, .row = 4}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 1, .row = 2}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 3, .row = 1}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 4, .row = 3}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 2, .row = 4}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 0, .row = 3}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 1, .row = 1}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 3, .row = 0}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 4, .row = 2}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 3, .row = 4}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 1, .row = 3}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 0, .row = 1}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 2, .row = 0}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 4, .row = 1}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 3, .row = 3}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 1, .row = 4}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 0, .row = 2}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 1, .row = 0}));
    assert(game_won(&game) == false);
    assert(move_knight(&game, (KnightPosition){.column = 2, .row = 2}));
    assert(game_won(&game) == true);

    print_game(&game);

    return 0;
}
