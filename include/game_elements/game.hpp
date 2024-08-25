#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>

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
    END_SCREEN
};

class guess_or_die {
    public:
        guess_or_die(render_window& p_game_win, TTF_Font* p_main_font);

        void render();

    private:
        render_window& game_win;
        TTF_Font* main_font;

        title_screen ts;
        title_screen es;

        level level1;

        int current_phase;

        fontcache fc_ts_1;
};