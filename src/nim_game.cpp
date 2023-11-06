#include "nim_game.h"
#include <ctime>
#include <cstdlib>

array_game seed_0 = {9,5,8,7};
array_game seed_1 = {6,6,7,8};
array_game seed_2 = {4,6,8,1};
array_game seed_3 = {7,7,6,7};
array_game seed_4 = {5,3,8,6};
array_game seed_5 = {2,4,5,9};

array_game get_game_state_by_seed(unsigned seed)
{
    switch(seed)
    {
        case 0:
            return seed_0;

        case 1:
            return seed_1;

        case 2:
            return seed_2;

        case 3:
            return seed_3;

        case 4:
            return seed_4;

        case 5:
            return seed_5;

        default:
            return seed_0;
    }
}


void game::set_game(unsigned seed)
{
    srand(time(NULL));
    stacks = get_game_state_by_seed(seed);
    tokens = 0;
    for(auto i: stacks)
    {
        tokens += i;
    }
    player = NIM_PLAYER_USER;
    game_state = NIM_STATE_ON;
}


unsigned game::get_stack(unsigned num)
{
    if(num >= NIM_STACKS)
    {
        return 0;
    }
    return stacks[num];
}


unsigned game::get_tokens_left()
{
    return tokens;
}


unsigned game::get_player()
{
    return player;
}


unsigned game::get_game_state()
{
    return game_state;
}

unsigned game::get_last_stack()
{
    return last_stack;
}

unsigned game::get_last_move()
{
    return last_move;
}


bool game::make_move(unsigned stack, unsigned move)
{
    if(move == 0)
    {
        return false;
    }
    if(stack >= NIM_STACKS)
    {
        return false;
    }
    if(move > stacks[stack])
    {
        return false;
    }

    stacks[stack] -= move;
    tokens -= move;

    last_move = move;
    last_stack = stack;

    if(player == NIM_PLAYER_USER)
    {
        player = NIM_PLAYER_CPU;
    }
    else
    {
        player = NIM_PLAYER_USER;
    }

    if(tokens == 0)
    {
        game_state = NIM_STATE_OFF;
    }


    return true;
}

void game::make_optimal_move()
{
    unsigned xor_var = 0;
    for(auto i: stacks)
    {
        xor_var ^= i;
    }

    if(xor_var == 0)
    {
        unsigned stack_num = rand() % NIM_STACKS;
        while(stacks[stack_num] == 0)
        {
            stack_num++;
            stack_num %= NIM_STACKS;
        }
        unsigned stack_var = rand() % stacks[stack_num] + 1;
        make_move(stack_num, stack_var);
        return;
    }

    for(int i=0; i<NIM_STACKS; i++)
    {
        unsigned xor_holder = xor_var^stacks[i];
        if(xor_holder <= stacks[i])
        {
            make_move(i, stacks[i] - xor_holder);
            return;
        }
    }
}

