#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<vector>
#include<string>

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
        SDL_Texture* bg;

        render_window& win;

        fontcache& quest_fc;
        fontcache& answ_fc;

        gui_textbutton answer1;
        gui_textbutton answer2;
        gui_textbutton answer3;
        gui_textbutton answer4;

        std::string answ1_txt;
        std::string answ2_txt;
        std::string answ3_txt;
        std::string answ4_txt;
        std::string quest_txt;

        int correct_answer;
        int right_selected;
    public:
        level(  render_window& p_win, 
                fontcache& p_quest_fc, 
                fontcache& p_answ_fc, 
                int p_correct_answer,
                std::string p_answ1_txt,
                std::string p_answ2_txt,
                std::string p_answ3_txt,
                std::string p_answ4_txt,
                std::string p_quest_txt,
                SDL_Texture* p_tex_norm,
                SDL_Texture* p_tex_act,
                SDL_Texture* p_bg);

        int update_render();
};