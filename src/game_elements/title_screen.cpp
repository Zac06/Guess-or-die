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
#include "game_elements/title_screen.hpp"

title_screen::title_screen(render_window& p_win)
    :slides(), curr_slide(0), win(p_win), firstview(false)
{
}

void title_screen::add_slide(ts_slide p_slide){
    slides.push_back(p_slide);
}

bool title_screen::update_render(){
    firstview=true;
    
    if(curr_slide==slides.size()){
        return true;
    }
    
    if(slides[curr_slide].bg!=NULL){
        win.render_texture(slides[curr_slide].bg, 0,0);
    }
    if(slides[curr_slide].splash!=NULL){
        win.render_texture(slides[curr_slide].splash, slides[curr_slide].splash_x,slides[curr_slide].splash_y+(int)slides[curr_slide].splash_offset_y);
    }
    if(slides[curr_slide].text_fc!=NULL){
        win.render_text_fc(*(slides[curr_slide].text_fc), slides[curr_slide].text, slides[curr_slide].text_x, slides[curr_slide].text_y, slides[curr_slide].center);
    }

    slides[curr_slide].wiggle();
    
    
    if(event_mgr::get_event(SDL_MOUSEBUTTONDOWN).event.button.state==SDL_PRESSED){
        curr_slide++;
    }
    
    return curr_slide==slides.size();
}

void title_screen::reset(){
    curr_slide=0;
}