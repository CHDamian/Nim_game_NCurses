#ifndef SCREEN_H
#define SCREEN_H

#include "libs.h"
#include "nim_game.h"

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 20

#define SCREEN_GAME_CUT_COLUMN 19
#define SCREEN_GAME_CUT_ROW 9

#define EMPTY_PIXEL ' '
#define COIN_VISUAL '$'


#define EMPTY_COLOR 0


#define EMPTY_BACKGROUND 0


namespace screen_game_strings
{
    const std::string controls_1_row = "Use arrows";
    const std::string controls_2_row = "to move";
    const std::string controls_4_row = "Press number";
    const std::string controls_5_row = "to take tokens";
    const std::string controls_6_row = "from stack";

    const std::string state_USER = "PLAYER TURN";
    const std::string state_CPU_1 = "CPU TURN.  ";
    const std::string state_CPU_2 = "CPU TURN.. ";
    const std::string state_CPU_3 = "CPU TURN...";

    const std::string state_1_row = "Last move:";
    const std::string state_3_row = "* Stack: ";
    const std::string state_4_row = "* Taken: ";

    const std::string menu_start_option[2] = {"   Play   ", ">> Play <<"};
    const std::string menu_about_option[2] = {"   About   ", ">> About <<"};
    const std::string menu_quit_option[2] = {"   Quit   ", ">> Quit <<"};

    const std::string continue_str = "Press ENTER to continue!";
    const std::string select_str = "Press ENTER to select!";
    const std::string quit_str = "Press q to quit!";

    const std::vector<std::string> gameRules = {
        "Rules:",
        "Each player in his turn chooses one stack,",
        "Then he or she can take as many coins from stack",
        "as he or she wants.",
        "  ",
        "Goal of this game is to take the last coin!",
        "  ",
        "Controls:",
        "Use arrows to move!",
        "Use numbers to take that many coins!",
        "-------------------------------------------------",
        "Press ENTER to continue!",
        "Press q to quit the app!",
    };

}

namespace ascii_arts
{
    const std::vector<std::string> art_won ={
        "__  ______  __  __   _       ______  _   ____",
        "\\ \\/ / __ \\/ / / /  | |     / / __ \\/ | / / /",
        " \\  / / / / / / /   | | /| / / / / /  |/ / / ",
        " / / /_/ / /_/ /    | |/ |/ / /_/ / /|  /_/  ",
        "/_/\\____/\\____/     |__/|__/\\____/_/ |_(_)   "
    };

    const std::vector<std::string> art_lose = {
        "__  ______  __  __   __    ____  _____ ________",
        "\\ \\/ / __ \\/ / / /  / /   / __ \\/ ___// ____/ /",
        " \\  / / / / / / /  / /   / / / /\\__ \\/ __/ / / ",
        " / / /_/ / /_/ /  / /___/ /_/ /___/ / /___/_/  ",
        "/_/\\____/\\____/  /_____/\\____//____/_____(_)   "
    };

    const std::vector<std::string> art_title ={
        "    _   ___              ______                   ",
        "   / | / (_)___ ___     / ____/___ _____ ___  ___ ",
        "  /  |/ / / __ `__ \\   / / __/ __ `/ __ `__ \\/ _ \\",
        " / /|  / / / / / / /  / /_/ / /_/ / / / / / /  __/",
        "/_/ |_/_/_/ /_/ /_/   \\____/\\__,_/_/ /_/ /_/\\___/ "
    };
}

enum screen_type
{
    screen_menu = 0,
    screen_game,
    screen_endgame,
    screen_about,


    screen_types_num
};

enum color_index
{
    DEFAULT_COLOR,
    STACK_COLOR,
    STACK_CHOSEN_COLOR,
    NUM_COLOR,
    NUM_CHOSEN_COLOR,
};

enum menu_option{
    menu_start = 0,
    menu_about,
    menu_quit,


    menu_count,
};
#define MENU_CHOSEN_OPTION 1
#define MENU_EMPTY_OPTION 0


using BUTTON_T = unsigned;

namespace buttons
{
    const BUTTON_T empty_button = 0;
    const BUTTON_T quit_k = 'q';
    const BUTTON_T resize_k = KEY_RESIZE;
    const BUTTON_T accept_k = 10;

    const BUTTON_T up_k = KEY_UP; 
    const BUTTON_T down_k = KEY_DOWN; 
    const BUTTON_T left_k = KEY_LEFT; 
    const BUTTON_T right_k = KEY_RIGHT; 

    const BUTTON_T k_1 = '1';
    const BUTTON_T k_2 = '2';
    const BUTTON_T k_3 = '3';
    const BUTTON_T k_4 = '4';
    const BUTTON_T k_5 = '5';
    const BUTTON_T k_6 = '6';
    const BUTTON_T k_7 = '7';
    const BUTTON_T k_8 = '8';
    const BUTTON_T k_9 = '9';
}

bool button_is_number(BUTTON_T b);


namespace positions
{
    const unsigned stack_lowest_y = 10;
    const unsigned num_highest_y = 12;
    const unsigned num_left_x = SCREEN_GAME_CUT_COLUMN + 4;
}

using U_CHAR = unsigned char;
using SCR_T = enum screen_type;
using COL_T = enum color_index;
using MENU_T = enum menu_option;


class screen
{
    private:

        U_CHAR screen_view[SCREEN_HEIGHT][SCREEN_WIDTH];
        U_CHAR screen_color[SCREEN_HEIGHT][SCREEN_WIDTH];
        U_CHAR screen_background[SCREEN_HEIGHT][SCREEN_WIDTH];
        SCR_T screen_set;
        unsigned winner = NIM_PLAYER_UNDEFINED;
        unsigned chosen_stack = 0;
        unsigned stack_sizes[4];
        unsigned menu_chosen_option = menu_start;

        void init_color();

        void clear_screen();

        void type_set_game();
        void type_set_endgame();
        void type_set_menu();
        void type_set_about();

        void show_game(int maxY, int maxX);
        void show_err();
        void show_endgame();


        void draw_stack(unsigned stack, unsigned x);
        void draw_num(unsigned stack, unsigned x);

        void draw_menu_option(MENU_T option);
        std::string menu_get_str(MENU_T option, unsigned version);
        

    public:

        screen() : screen_set(screen_menu){}

        void init();

        void show();

        BUTTON_T button_getter();

        SCR_T type_get();
        void type_set(SCR_T s_type);

        void game_set_stack(unsigned stack, unsigned num);
        void game_set_last_move(unsigned stack, unsigned num);
        void game_set_chosen_stack(unsigned stack);
        void game_set_winner(unsigned win);

        unsigned game_get_chosen_stack();

        void prepare_stacks_visually();
        void set_player_str(std::string s);

        void game_make_cpu_thinking_animation();

        BUTTON_T game_player_move();
        BUTTON_T engame_buttons_handler();
        BUTTON_T menu_buttons_handler();
        BUTTON_T about_buttons_handler();

        MENU_T menu_get_option();
        void menu_set_option(BUTTON_T b);

};


#endif //SCREEN_H