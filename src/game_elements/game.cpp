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

#include "game_elements/game.hpp"

guess_or_die::guess_or_die(render_window& p_game_win, TTF_Font* p_main_font)
    :   game_win(p_game_win), 
        main_font(p_main_font), 
        ts(p_game_win), es(p_game_win), 
        current_phase(0), 
        fc_ts_1(p_main_font, (SDL_Color){0,0,0,255}, game_win.get_renderer()), 
        level1(game_win)
{
    SDL_Texture* bg1_ts=game_win.load_texture("../res/gfx/bg1.png");

    ts.add_slide(ts_slide(bg1_ts, NULL, 0,0,"abcdefg\nhijklmno\npqrstuvwx\nyz/*-+#;:\n,.-_", game_win.get_win_width()/2, 100, &fc_ts_1));
}   

void guess_or_die::render(){
    switch(current_phase){
        case PHASE_TITLE_SCREEN:{
            bool ret=ts.update_render();
            if(ret){
                es.reset();
                current_phase++;
            }
            
            break;
        }
        case PHASE_LEVEL_1:{
            bool ret=level1.update_render();
            if(ret){
                //es.reset();
                current_phase++;
            }

            break;
        }
        case END_SCREEN:{
            bool ret=es.update_render();
            if(ret){
                current_phase=PHASE_TITLE_SCREEN;
                ts.reset();
            }
            break;
        }
    }
}