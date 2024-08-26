#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<vector>

#include "rendering/render_window.hpp"
#include "base_elements/entity.hpp"
#include "rendering/fontcache.hpp"
#include "rendering/event_mgr.hpp"
#include "base_elements/gui_element.hpp"
#include "gui_elements/gui_button.hpp"
#include "gui_elements/gui_textbutton.hpp"

class level {
    private:
        SDL_Texture* tex_1;
        SDL_Texture* tex_2;

        render_window& win;

        fontcache& quest_fc;
        fontcache& answ_fc;

        gui_textbutton answer1;
        /*gui_textbutton answer2;
        gui_textbutton answer3;
        gui_textbutton answer4;*/

    public:
        level(render_window& p_win, fontcache& p_quest_fc, fontcache& p_answ_fc);

        bool update_render();
};