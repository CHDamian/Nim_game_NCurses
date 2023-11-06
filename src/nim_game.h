#ifndef NIM_GAME_H
#define NIM_GAME_H

#include "libs.h"

const unsigned NIM_STACKS = 4;

enum nim_player_enum{
    NIM_PLAYER_UNDEFINED = 0,
    NIM_PLAYER_USER = 1,
    NIM_PLAYER_CPU = 2
};

enum nim_state_enum {

    NIM_STATE_STEADY = 0,
    NIM_STATE_ON = 1,
    NIM_STATE_OFF = 2
};

using array_game = std::array<unsigned, NIM_STACKS>;

class game
{
    private:

        std::array<unsigned, NIM_STACKS> stacks;
        unsigned tokens = 0;
        unsigned player = NIM_PLAYER_UNDEFINED;
        unsigned game_state = NIM_STATE_STEADY;
        unsigned last_stack = 0;
        unsigned last_move = 0;

    public:

        game(){}

        void set_game(unsigned seed);

        unsigned get_stack(unsigned num);
        unsigned get_tokens_left();
        unsigned get_player();
        unsigned get_game_state();
        unsigned get_last_stack();
        unsigned get_last_move();



        bool make_move(unsigned stack, unsigned move);
        void make_optimal_move();

};

#endif //NIM_GAME_H