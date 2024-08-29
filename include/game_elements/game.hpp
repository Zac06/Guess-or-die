#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<string>
#include<cstdlib>

#include "rendering/render_window.hpp"
#include "base_elements/entity.hpp"
#include "rendering/fontcache.hpp"
#include "rendering/event_mgr.hpp"
#include "base_elements/gui_element.hpp"
#include "gui_elements/gui_button.hpp"

#include "game_elements/title_screen.hpp"
#include "game_elements/level.hpp"

enum {
    PHASE_TITLE_SCREEN=0,

    PHASE_LEVEL_1,
    PHASE_LEVEL_2,
    PHASE_LEVEL_3,
    PHASE_LEVEL_4,
    PHASE_LEVEL_5,
    PHASE_LEVEL_6,
    PHASE_LEVEL_7,
    PHASE_LEVEL_8,

    PHASE_CONGRATS_1,
    PHASE_CONGRATS_2,
    PHASE_CONGRATS_3,
    PHASE_CONGRATS_4,
    PHASE_CONGRATS_5,
    PHASE_CONGRATS_6,
    PHASE_CONGRATS_7,
    PHASE_CONGRATS_8,

    PHASE_PENALTY_1,
    PHASE_PENALTY_2,
    PHASE_PENALTY_3,
    PHASE_PENALTY_4,
    PHASE_PENALTY_5,
    PHASE_PENALTY_6,
    PHASE_PENALTY_7,
    PHASE_PENALTY_8,

    PHASE_END_SCREEN
};

class guess_or_die {
    public:
        guess_or_die(render_window& p_game_win, TTF_Font* p_main_font, TTF_Font* p_second_font);
        ~guess_or_die();

        void render();

        level* load_level(std::string p_file_name);
        std::string read_until_whiteline(ifstream& fin);
    private:
        render_window& game_win;
        TTF_Font* main_font;
        TTF_Font* second_font;

        SDL_Texture* button_normal;
        SDL_Texture* button_active;
        SDL_Texture* bg_neutral;
        SDL_Texture* bg_error;
        SDL_Texture* bg_good;

        title_screen ts;
        title_screen es;

        int current_phase;

        fontcache fc_ts_1;
        fontcache fc_ts_2;
        
        level* level1;
        level* level2;
        level* level3;
        level* level4;
        level* level5;
        level* level6;
        level* level7;
        level* level8;

        title_screen congrats_1_ts;
        title_screen congrats_2_ts;
        title_screen congrats_3_ts;
        title_screen congrats_4_ts;
        title_screen congrats_5_ts;
        title_screen congrats_6_ts;
        title_screen congrats_7_ts;
        title_screen congrats_8_ts;

        title_screen penalty_1_ts;
        title_screen penalty_2_ts;
        title_screen penalty_3_ts;
        title_screen penalty_4_ts;
        title_screen penalty_5_ts;
        title_screen penalty_6_ts;
        title_screen penalty_7_ts;
        title_screen penalty_8_ts;

        void penalty_1();
        void penalty_2();
        void penalty_3();
        void penalty_4();
        void penalty_5();
        void penalty_6();
        void penalty_7();
        void penalty_8();

};