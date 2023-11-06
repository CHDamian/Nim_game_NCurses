#include "screen.h"

void screen::clear_screen()
{
    for(int h = 0; h < SCREEN_HEIGHT; h++)
    {
        for(int w = 0; w < SCREEN_WIDTH; w++)
        {
            screen_view[h][w] = EMPTY_PIXEL;
            screen_color[h][w] = EMPTY_COLOR;
            screen_background[h][w] = EMPTY_BACKGROUND;
        }
    }
}

void screen::type_set_game()
{
    clear_screen();

    // Create frame
    for(int i = 1; i < SCREEN_WIDTH - 1; i++)
    {
        screen_view[0][i] = '-'; 
        screen_view[SCREEN_HEIGHT - 1][i] = '-'; 
    }

    for(int i = 1; i < SCREEN_HEIGHT - 1; i++)
    {
        screen_view[i][0] = '|'; 
        screen_view[i][SCREEN_GAME_CUT_COLUMN] = '|'; 
        screen_view[i][SCREEN_WIDTH - 1] = '|'; 
    }

    for(int i = 1; i < SCREEN_GAME_CUT_COLUMN; i++)
    {
        screen_view[SCREEN_GAME_CUT_ROW][i];
    }


    // Create controls strings 
    for(int i = 0; i < screen_game_strings::controls_1_row.size(); i++)
    {
        screen_view[2][i + 2] = screen_game_strings::controls_1_row[i];
    }
    for(int i = 0; i < screen_game_strings::controls_2_row.size(); i++)
    {
        screen_view[3][i + 2] = screen_game_strings::controls_2_row[i];
    }
    for(int i = 0; i < screen_game_strings::controls_4_row.size(); i++)
    {
        screen_view[5][i + 2] = screen_game_strings::controls_4_row[i];
    }
    for(int i = 0; i < screen_game_strings::controls_5_row.size(); i++)
    {
        screen_view[6][i + 2] = screen_game_strings::controls_5_row[i];
    }
    for(int i = 0; i < screen_game_strings::controls_6_row.size(); i++)
    {
        screen_view[7][i + 2] = screen_game_strings::controls_6_row[i];
    }

    // Create state strings 
    for(int i = 0; i < screen_game_strings::state_1_row.size(); i++)
    {
        screen_view[13][i + 4] = screen_game_strings::state_1_row[i];
    }
    for(int i = 0; i < screen_game_strings::state_3_row.size(); i++)
    {
        screen_view[15][i + 4] = screen_game_strings::state_3_row[i];
    }
    for(int i = 0; i < screen_game_strings::state_4_row.size(); i++)
    {
        screen_view[16][i + 4] = screen_game_strings::state_4_row[i];
    }

    game_set_winner(NIM_PLAYER_UNDEFINED);
    screen_set = screen_game;
}

void screen::type_set_endgame()
{
    if(screen_set != screen_game || winner == NIM_PLAYER_UNDEFINED)return;
    clear_screen();
    if(winner == NIM_PLAYER_USER)
    {
        unsigned x_corr = SCREEN_WIDTH/2 - ascii_arts::art_won[0].size()/2;
        unsigned y_corr = SCREEN_HEIGHT/2 - ascii_arts::art_won.size()/2;
        for(int i = 0; i < ascii_arts::art_won.size(); i++)
        {
            for(int j = 0; j < ascii_arts::art_won[i].size(); j++)
            {
                screen_view[y_corr + i][x_corr + j] = ascii_arts::art_won[i][j];
            }
        }
    }
    if(winner == NIM_PLAYER_CPU)
    {
        unsigned x_corr = SCREEN_WIDTH/2 - ascii_arts::art_lose[0].size()/2;
        unsigned y_corr = SCREEN_HEIGHT/2 - ascii_arts::art_lose.size()/2;
        for(int i = 0; i < ascii_arts::art_lose.size(); i++)
        {
            for(int j = 0; j < ascii_arts::art_lose[i].size(); j++)
            {
                screen_view[y_corr + i][x_corr + j] = ascii_arts::art_lose[i][j];
            }
        }
    }

    unsigned y_corr = SCREEN_HEIGHT - 3;
    unsigned x_corr = SCREEN_WIDTH/2 - screen_game_strings::continue_str.size()/2;
    for(int i = 0; i < screen_game_strings::continue_str.size(); i++)
    {
        screen_view[y_corr][x_corr + i] = screen_game_strings::continue_str[i];
    }

    x_corr = SCREEN_WIDTH/2 - screen_game_strings::quit_str.size()/2;
    for(int i = 0; i < screen_game_strings::quit_str.size(); i++)
    {
        screen_view[y_corr + 1][x_corr + i] = screen_game_strings::quit_str[i];
    }


    screen_set = screen_endgame;
}


void screen::type_set_menu()
{
    clear_screen();
    menu_chosen_option = menu_start;
    unsigned y_high = SCREEN_HEIGHT/2 - 3 - ascii_arts::art_title.size()/2;
    unsigned x_left = SCREEN_WIDTH/2 - ascii_arts::art_title[0].size()/2;
    for(int i = 0; i < ascii_arts::art_title.size(); i++)
    {
        for(int j = 0; j < ascii_arts::art_title[i].size(); j++)
        {
            screen_view[y_high + i][x_left + j] = ascii_arts::art_title[i][j];
        }
    }

    unsigned y_corr = SCREEN_HEIGHT - 3;
    unsigned x_corr = SCREEN_WIDTH/2 - screen_game_strings::select_str.size()/2;
    for(int i = 0; i < screen_game_strings::select_str.size(); i++)
    {
        screen_view[y_corr][x_corr + i] = screen_game_strings::select_str[i];
    }

    x_corr = SCREEN_WIDTH/2 - screen_game_strings::quit_str.size()/2;
    for(int i = 0; i < screen_game_strings::quit_str.size(); i++)
    {
        screen_view[y_corr + 1][x_corr + i] = screen_game_strings::quit_str[i];
    }

    screen_set = screen_menu;
    draw_menu_option((MENU_T) menu_chosen_option);
}

void screen::type_set_about()
{
    clear_screen();
    unsigned y_corr = SCREEN_HEIGHT/2 - screen_game_strings::gameRules.size()/2;
    for(unsigned i = 0; i < screen_game_strings::gameRules.size(); i++)
    {
        unsigned x_corr = SCREEN_WIDTH/2 - screen_game_strings::gameRules[i].size()/2;
        for(int j = 0; j < screen_game_strings::gameRules[i].size(); j++)
        {
            screen_view[y_corr + i][x_corr + j] = screen_game_strings::gameRules[i][j];
        }
    }

    screen_set = screen_about;
}


void screen::type_set(SCR_T s_type)
{
    switch(s_type)
    {
        case screen_menu:
            type_set_menu();
            break;

        case screen_game:
            type_set_game();
            break;

        case screen_endgame:
            type_set_endgame();
            break;

        case screen_about:
            type_set_about();
            break;

        default:
            return;
    }
}


BUTTON_T screen::button_getter()
{
    unsigned pressed = getch();
    switch(pressed)
    {
        case ERR:
            return buttons::empty_button;
        
        case buttons::quit_k:
            return buttons::quit_k;

        case buttons::resize_k:
            return buttons::resize_k;

        case buttons::accept_k:
            return buttons::accept_k;

        case buttons::up_k:
            return buttons::up_k;

        case buttons::down_k:
            return buttons::down_k;

        case buttons::left_k:
            return buttons::left_k;

        case buttons::right_k:
            return buttons::right_k;

        case buttons::k_1:
            return buttons::k_1;

        case buttons::k_2:
            return buttons::k_2;

        case buttons::k_3:
            return buttons::k_3;

        case buttons::k_4:
            return buttons::k_4;

        case buttons::k_5:
            return buttons::k_5;

        case buttons::k_6:
            return buttons::k_6;

        case buttons::k_7:
            return buttons::k_7;

        case buttons::k_8:
            return buttons::k_8;

        case buttons::k_9:
            return buttons::k_9;

        default:
            return buttons::empty_button;
    }
}

bool button_is_number(BUTTON_T b)
{
    return (b >= 48) && (b <= 57);
}

void screen::show()
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    if(maxY < SCREEN_HEIGHT || maxX < SCREEN_WIDTH)
    {
        return show_err();
    }

    switch (screen_set)
    {
        case screen_game:
            return show_game(maxY, maxX);

        case screen_endgame:
            return show_game(maxY, maxX);

        case screen_menu:
            return show_game(maxY, maxX);

        case screen_about:
            return show_game(maxY, maxX);

        default:
            return;
    }
}

void screen::show_err()
{
    clear();

    move(0, 0);
    mvprintw(0, 0, "Screen too small! Resize it!");


    refresh();
}

void screen::show_game(int maxY, int maxX)
{
    clear();

    int beginY = maxY/2 - SCREEN_HEIGHT/2;
    int beginX = maxX/2 - SCREEN_WIDTH/2;

    for(int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for(int j = 0; j < SCREEN_WIDTH; j++)
        {
            move(beginY + i, beginX + j);
            //mvprintw(beginY + i, beginX + j, "%c", screen_view[i][j]);
            attron( COLOR_PAIR( screen_color[i][j] ) );
            mvaddch(beginY + i, beginX + j, screen_view[i][j]);
            attroff( COLOR_PAIR( screen_color[i][j] ) );
        }
    }

    refresh();
}

void screen::init_color()
{
    start_color();
    init_pair(DEFAULT_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(STACK_COLOR, COLOR_BLUE, COLOR_BLACK);
    init_pair(STACK_CHOSEN_COLOR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(NUM_COLOR, COLOR_WHITE, COLOR_BLUE);
    init_pair(NUM_CHOSEN_COLOR, COLOR_WHITE, COLOR_YELLOW);
}


void screen::init()
{
    initscr(); // Inicjalizacja NCurses
    init_color();
    timeout(0); // Ustawienie nieblokującego trybu oczekiwania na wejście
    noecho();
    curs_set(0);
    keypad( stdscr, TRUE );
}

SCR_T screen::type_get()
{
    return screen_set;
}

unsigned screen::game_get_chosen_stack()
{
    return chosen_stack;
}

void screen::game_set_stack(unsigned stack, unsigned num)
{
    stack_sizes[stack] = num;
}


void screen::game_set_last_move(unsigned stack, unsigned num)
{
    screen_view[15][4 + screen_game_strings::state_3_row.size()] = stack + 48;
    screen_view[16][4 + screen_game_strings::state_4_row.size()] = num + 48;
}

void screen::game_set_chosen_stack(unsigned stack)
{
    chosen_stack = stack;
}

void screen::game_set_winner(unsigned win)
{
    winner = win;
}


void screen::prepare_stacks_visually()
{
    unsigned next_x = positions::num_left_x;

    for(int i = 0; i < NIM_STACKS; i++)
    {
        draw_num(i, next_x);
        draw_stack(i, next_x + 1);
        next_x += 7;
    }
}

void screen::set_player_str(std::string s)
{
    for(int i = 0; i < s.size(); i++)
    {
        screen_view[11][i + 4] = s[i];
    }
}


void screen::draw_stack(unsigned stack, unsigned x)
{
    COL_T current_color = STACK_COLOR;
    if(chosen_stack == stack)current_color = STACK_CHOSEN_COLOR;

    for(int i = 0; i < 9; i++)
    {
        if(i < stack_sizes[stack])
        {
            screen_view[positions::stack_lowest_y - i][x] = COIN_VISUAL;
            screen_color[positions::stack_lowest_y - i][x] = current_color;
        }
        else
        {
            screen_view[positions::stack_lowest_y - i][x] = EMPTY_PIXEL;
            screen_color[positions::stack_lowest_y - i][x] = DEFAULT_COLOR;
        }
    }
}

void screen::draw_num(unsigned stack, unsigned x)
{
    COL_T current_color = NUM_COLOR;
    if(chosen_stack == stack)current_color = NUM_CHOSEN_COLOR;


    switch(stack_sizes[stack])
    {
        case 0:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = current_color;
            screen_color[positions::num_highest_y][x + 2] = current_color;

            screen_color[positions::num_highest_y + 1][x] = current_color;
            screen_color[positions::num_highest_y + 1][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 2] = current_color;

            screen_color[positions::num_highest_y + 2][x] = current_color;
            screen_color[positions::num_highest_y + 2][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 2][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 3][x] = current_color;
            screen_color[positions::num_highest_y + 3][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 4][x] = current_color;
            screen_color[positions::num_highest_y + 4][x + 1] = current_color;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

        case 1:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = current_color;
            screen_color[positions::num_highest_y][x + 2] = DEFAULT_COLOR;

            screen_color[positions::num_highest_y + 1][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 1] = current_color;
            screen_color[positions::num_highest_y + 1][x + 2] = DEFAULT_COLOR;

            screen_color[positions::num_highest_y + 2][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 2][x + 1] = current_color;
            screen_color[positions::num_highest_y + 2][x + 2] = DEFAULT_COLOR;
            
            screen_color[positions::num_highest_y + 3][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 1] = current_color;
            screen_color[positions::num_highest_y + 3][x + 2] = DEFAULT_COLOR;
            
            screen_color[positions::num_highest_y + 4][x] = current_color;
            screen_color[positions::num_highest_y + 4][x + 1] = current_color;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

        case 2:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = current_color;
            screen_color[positions::num_highest_y][x + 2] = current_color;

            screen_color[positions::num_highest_y + 1][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 2] = current_color;

            screen_color[positions::num_highest_y + 2][x] = current_color;
            screen_color[positions::num_highest_y + 2][x + 1] = current_color;
            screen_color[positions::num_highest_y + 2][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 3][x] = current_color;
            screen_color[positions::num_highest_y + 3][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 2] = DEFAULT_COLOR;
            
            screen_color[positions::num_highest_y + 4][x] = current_color;
            screen_color[positions::num_highest_y + 4][x + 1] = current_color;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

        case 3:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = current_color;
            screen_color[positions::num_highest_y][x + 2] = current_color;

            screen_color[positions::num_highest_y + 1][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 2] = current_color;

            screen_color[positions::num_highest_y + 2][x] = current_color;
            screen_color[positions::num_highest_y + 2][x + 1] = current_color;
            screen_color[positions::num_highest_y + 2][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 3][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 4][x] = current_color;
            screen_color[positions::num_highest_y + 4][x + 1] = current_color;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

        case 4:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y][x + 2] = current_color;

            screen_color[positions::num_highest_y + 1][x] = current_color;
            screen_color[positions::num_highest_y + 1][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 2] = current_color;

            screen_color[positions::num_highest_y + 2][x] = current_color;
            screen_color[positions::num_highest_y + 2][x + 1] = current_color;
            screen_color[positions::num_highest_y + 2][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 3][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 4][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 4][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

        case 5:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = current_color;
            screen_color[positions::num_highest_y][x + 2] = current_color;

            screen_color[positions::num_highest_y + 1][x] = current_color;
            screen_color[positions::num_highest_y + 1][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 2] = DEFAULT_COLOR;

            screen_color[positions::num_highest_y + 2][x] = current_color;
            screen_color[positions::num_highest_y + 2][x + 1] = current_color;
            screen_color[positions::num_highest_y + 2][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 3][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 4][x] = current_color;
            screen_color[positions::num_highest_y + 4][x + 1] = current_color;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

        case 6:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = current_color;
            screen_color[positions::num_highest_y][x + 2] = current_color;

            screen_color[positions::num_highest_y + 1][x] = current_color;
            screen_color[positions::num_highest_y + 1][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 2] = DEFAULT_COLOR;

            screen_color[positions::num_highest_y + 2][x] = current_color;
            screen_color[positions::num_highest_y + 2][x + 1] = current_color;
            screen_color[positions::num_highest_y + 2][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 3][x] = current_color;
            screen_color[positions::num_highest_y + 3][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 4][x] = current_color;
            screen_color[positions::num_highest_y + 4][x + 1] = current_color;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

        case 7:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = current_color;
            screen_color[positions::num_highest_y][x + 2] = current_color;

            screen_color[positions::num_highest_y + 1][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 2] = current_color;

            screen_color[positions::num_highest_y + 2][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 2][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 2][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 3][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 4][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 4][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

        case 8:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = current_color;
            screen_color[positions::num_highest_y][x + 2] = current_color;

            screen_color[positions::num_highest_y + 1][x] = current_color;
            screen_color[positions::num_highest_y + 1][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 2] = current_color;

            screen_color[positions::num_highest_y + 2][x] = current_color;
            screen_color[positions::num_highest_y + 2][x + 1] = current_color;
            screen_color[positions::num_highest_y + 2][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 3][x] = current_color;
            screen_color[positions::num_highest_y + 3][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 4][x] = current_color;
            screen_color[positions::num_highest_y + 4][x + 1] = current_color;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

        case 9:
            screen_color[positions::num_highest_y][x] = current_color;
            screen_color[positions::num_highest_y][x + 1] = current_color;
            screen_color[positions::num_highest_y][x + 2] = current_color;

            screen_color[positions::num_highest_y + 1][x] = current_color;
            screen_color[positions::num_highest_y + 1][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 1][x + 2] = current_color;

            screen_color[positions::num_highest_y + 2][x] = current_color;
            screen_color[positions::num_highest_y + 2][x + 1] = current_color;
            screen_color[positions::num_highest_y + 2][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 3][x] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 1] = DEFAULT_COLOR;
            screen_color[positions::num_highest_y + 3][x + 2] = current_color;
            
            screen_color[positions::num_highest_y + 4][x] = current_color;
            screen_color[positions::num_highest_y + 4][x + 1] = current_color;
            screen_color[positions::num_highest_y + 4][x + 2] = current_color;
            
            break;

    }
}

BUTTON_T screen::game_player_move()
{
    BUTTON_T found = buttons::empty_button;
    bool looper = true;
    while (looper)
    {
        found = button_getter();
        switch (found)
        {
        case buttons::quit_k:
            looper = false;
            break;

        case buttons::resize_k:
            show();
            break;

        case buttons::left_k:
            if(chosen_stack > 0)
            {
                game_set_chosen_stack(chosen_stack - 1);
                prepare_stacks_visually();
                show();
            }
            break;

        case buttons::right_k:
            if(chosen_stack < 3)
            {
                game_set_chosen_stack(chosen_stack + 1);
                prepare_stacks_visually();
                show();
            }
            break;
        
        case buttons::k_1:
            looper = false;
            break;

        case buttons::k_2:
            looper = false;
            break;

        case buttons::k_3:
            looper = false;
            break;

        case buttons::k_4:
            looper = false;
            break;

        case buttons::k_5:
            looper = false;
            break;

        case buttons::k_6:
            looper = false;
            break;

        case buttons::k_7:
            looper = false;
            break;

        case buttons::k_8:
            looper = false;
            break;

        case buttons::k_9:
            looper = false;
            break;
        
        default:
            break;
        }
    }
    return found;
}

BUTTON_T screen::engame_buttons_handler()
{
    BUTTON_T found = buttons::empty_button;
    bool looper = true;
    while (looper)
    {
        found = button_getter();
        switch (found)
        {
            case buttons::quit_k:
                looper = false;
                break;

            case buttons::resize_k:
                show();
                break;

            case buttons::accept_k:
                looper = false;
                break;

            default:
                break;
        }
    }
    return found;
}

BUTTON_T screen::about_buttons_handler()
{
    BUTTON_T found = buttons::empty_button;
    bool looper = true;
    while (looper)
    {
        found = button_getter();
        switch (found)
        {
            case buttons::quit_k:
                looper = false;
                break;

            case buttons::resize_k:
                show();
                break;

            case buttons::accept_k:
                looper = false;
                break;

            default:
                break;
        }
    }
    return found;
}

void screen::menu_set_option(BUTTON_T b)
{
    if(b == buttons::up_k  && menu_chosen_option > 0)
    {
        menu_chosen_option--;
        draw_menu_option((MENU_T) menu_chosen_option);
        show();
    }
    if(b == buttons::down_k && menu_chosen_option < menu_count - 1)
    {
        menu_chosen_option++;
        draw_menu_option((MENU_T) menu_chosen_option);
        show();
    }
}

BUTTON_T screen::menu_buttons_handler()
{
    BUTTON_T found = buttons::empty_button;
    bool looper = true;
    while (looper)
    {
        found = button_getter();
        switch (found)
        {
            case buttons::quit_k:
                looper = false;
                break;

            case buttons::resize_k:
                show();
                break;

            case buttons::accept_k:
                looper = false;
                break;

            case buttons::up_k:
                menu_set_option(buttons::up_k);
                break;

            case buttons::down_k:
                menu_set_option(buttons::down_k);
                break;


            default:
                break;
        }
    }
    return found;
}

std::string screen::menu_get_str(MENU_T option, unsigned version)
{
    switch(option)
    {
        case menu_start:
            return screen_game_strings::menu_start_option[version];

        case menu_about:
            return screen_game_strings::menu_about_option[version];

        case menu_quit:
            return screen_game_strings::menu_quit_option[version];

        default:
            return "";
    }
}


void screen::draw_menu_option(MENU_T option)
{
    if(screen_set != screen_menu)return;
    if(option >= menu_count)return;

    unsigned y_high = SCREEN_HEIGHT/2 + 3;

    for(unsigned i = 0; i < menu_count; i++)
    {
        unsigned is_chosen = option == i ? MENU_CHOSEN_OPTION : MENU_EMPTY_OPTION;
        std::string option_str = menu_get_str((MENU_T) i, is_chosen);
        unsigned x_left = SCREEN_WIDTH/2 - option_str.size()/2;
        COL_T color_chosen = menu_chosen_option == i ? STACK_CHOSEN_COLOR : STACK_COLOR;

        for(int j = 0; j < option_str.size(); j++)
        {
            screen_view[y_high + i][x_left + j] = option_str[j];
            screen_color[y_high + i][x_left + j] = color_chosen;
        }
    }
    //screen_view[SCREEN_HEIGHT - 1][SCREEN_WIDTH - 1] = menu_chosen_option + 48;
}

MENU_T screen::menu_get_option()
{
    return (MENU_T) menu_chosen_option;
}

