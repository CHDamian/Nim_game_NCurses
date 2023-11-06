#include "libs.h"
#include "nim_game.h"
#include "screen.h"

game game_instance;
screen screen_instance;
BUTTON_T found = buttons::empty_button;


void player_handler()
{
    found = screen_instance.game_player_move();
    if(button_is_number(found))
    {
        unsigned curr_stack = screen_instance.game_get_chosen_stack();
        bool correct_move = game_instance.make_move(curr_stack, found - 48);
        if(correct_move)
        {
            screen_instance.game_set_stack(curr_stack, game_instance.get_stack(curr_stack));
            screen_instance.game_set_last_move(game_instance.get_last_stack() + 1, game_instance.get_last_move());
            if(game_instance.get_game_state() == NIM_STATE_ON)
            {
                screen_instance.prepare_stacks_visually();
                screen_instance.set_player_str(screen_game_strings::state_CPU_1);
                screen_instance.show();
            }
            else
            {
                screen_instance.game_set_winner(NIM_PLAYER_USER);
                screen_instance.type_set(screen_endgame);
            }
        }
    }
}

void CPU_handler()
{
    for(int i = 0; i < 3; i++)
    {
        screen_instance.set_player_str(screen_game_strings::state_CPU_1);
        screen_instance.show();
        napms(150);

        screen_instance.set_player_str(screen_game_strings::state_CPU_2);
        screen_instance.show();
        napms(150);

        screen_instance.set_player_str(screen_game_strings::state_CPU_3);
        screen_instance.show();
        napms(150);
    }

    game_instance.make_optimal_move();

    unsigned curr_stack = game_instance.get_last_stack();

    screen_instance.game_set_stack(curr_stack, game_instance.get_stack(curr_stack));
    screen_instance.game_set_last_move(game_instance.get_last_stack() + 1, game_instance.get_last_move());
    if(game_instance.get_game_state() == NIM_STATE_ON)
    {
        screen_instance.prepare_stacks_visually();
        screen_instance.set_player_str(screen_game_strings::state_USER);
        screen_instance.show();
        flushinp();
    }
    else
    {
        screen_instance.game_set_winner(NIM_PLAYER_CPU);
        screen_instance.type_set(screen_endgame);
    }
}


void turn_handler()
{
    switch (game_instance.get_player())
    {
    case NIM_PLAYER_USER:
        player_handler();
        break;

    case NIM_PLAYER_CPU:
        CPU_handler();
        break;
    
    default:
        break;
    }

}

void game_set_match()
{
    screen_instance.type_set(screen_game);
    unsigned seed = rand()%6;
    game_instance.set_game(seed);
    for(int i=0; i < NIM_STACKS; i++)
    {
        screen_instance.game_set_stack(i, game_instance.get_stack(i));
    }
    screen_instance.game_set_chosen_stack(0);
    screen_instance.prepare_stacks_visually();
    screen_instance.set_player_str(screen_game_strings::state_USER);
    screen_instance.show();
}

void engame_handler()
{
    screen_instance.show();
    found = screen_instance.engame_buttons_handler();
    if(found == buttons::accept_k)screen_instance.type_set(screen_menu);
}

void menu_handler()
{
    screen_instance.show();
    found = screen_instance.menu_buttons_handler();
    if(found == buttons::accept_k)
    {
        switch(screen_instance.menu_get_option())
        {
            case menu_start:
                game_set_match();
                break;

            case menu_about:
                screen_instance.type_set(screen_about);
                break;

            case menu_quit:
                found = buttons::quit_k;
                break;

            default:
                break;
        }
    }
}

void about_handler()
{
    screen_instance.show();
    found = screen_instance.about_buttons_handler();
    if(found == buttons::accept_k)screen_instance.type_set(screen_menu);
}

int main()
{
    srand(time(NULL));
    screen_instance.init();
    screen_instance.type_set(screen_menu);
    while(found != buttons::quit_k)
    {
        switch (screen_instance.type_get())
        {
        case screen_game:
            turn_handler();
            break;

        case screen_endgame:
            engame_handler();
            break;

        case screen_menu:
            menu_handler();
            break;

        case screen_about:
            about_handler();
            break;
        
        default:
            break;
        }
    }
    endwin(); // Zakończenie trybu NCurses
    return 0;
}