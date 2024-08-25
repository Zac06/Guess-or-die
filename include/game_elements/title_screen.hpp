#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<string>
#include<vector>

#include "rendering/render_window.hpp"
#include "base_elements/entity.hpp"
#include "rendering/fontcache.hpp"
#include "rendering/event_mgr.hpp"
#include "base_elements/gui_element.hpp"
#include "gui_elements/gui_button.hpp"

#include "game_elements/game.hpp"

class ts_slide {
    public:
        SDL_Texture* bg;
        SDL_Texture* splash;
        int splash_x;
        int splash_y;

        std::string text;
        int text_x;
        int text_y;

        fontcache* text_fc;
        float splash_offset_y;
        float delta_offset;
        float limit;
        int last_millis;

        ts_slide(SDL_Texture* p_bg, SDL_Texture* p_splash, int p_splash_x, int p_splash_y, std::string p_text, int p_text_x, int p_text_y, fontcache* p_text_fc)
            :bg(p_bg), splash(p_splash), splash_x(p_splash_x), splash_y(p_splash_y), text(p_text), text_x(p_text_x), text_y(p_text_y), text_fc(p_text_fc)
        {
            splash_offset_y=0;
            delta_offset=0.01;
            limit=20;
            last_millis=0;
        }

        void wiggle(){
            if(splash_offset_y<0){
                delta_offset*=-1;
                splash_offset_y=0;
            }

            if(splash_offset_y>limit){
                delta_offset*=-1;
                splash_offset_y=limit;
            }

            splash_offset_y+=delta_offset*(SDL_GetTicks()-last_millis);
            last_millis=SDL_GetTicks();
        }
};

class title_screen {
    public:
        title_screen(render_window& p_win);
        void add_slide(ts_slide p_slide);

        //Returns true if slides have ended.
        bool update_render();
        void reset();

    private:
        std::vector<ts_slide> slides;
        int curr_slide;
        render_window& win;
};