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

#include "game_elements/level.hpp"

#include<cstdint>                                       

level::level(render_window& p_win, fontcache& p_quest_fc, fontcache& p_answ_fc, int p_correct_answer)
    :   win(p_win), 
        quest_fc(p_quest_fc), 
        answ_fc(p_answ_fc),
        tex_1(p_win.load_texture("../res/gfx/button_normal.png")),
        tex_2(p_win.load_texture("../res/gfx/button_active.png")),

        answer1(tex_1, tex_2, {20,385}, p_win, p_answ_fc, "PROVA", p_win.get_texture_width(tex_1)/2, 20),
        answer2(tex_1, tex_2, {460,385}, p_win, p_answ_fc, "PROVA", p_win.get_texture_width(tex_1)/2, 20),
        answer3(tex_1, tex_2, {20,530}, p_win, p_answ_fc, "PROVA", p_win.get_texture_width(tex_1)/2, 20),
        answer4(tex_1, tex_2, {460,530}, p_win, p_answ_fc, "PROVA", p_win.get_texture_width(tex_1)/2, 20),

        correct_answer(p_correct_answer),
        right_selected(-1)
{

}

int level::update_render(){
    answer1.update();
    answer2.update();
    answer3.update();
    answer4.update();

    int selected_answer=0;
    if(answer1.get_state()==GUI_STATE_ACTIVE){
        selected_answer=1;
    }else if(answer2.get_state()==GUI_STATE_ACTIVE){
        selected_answer=2;
    }else if(answer3.get_state()==GUI_STATE_ACTIVE){
        selected_answer=3;
    }else if(answer4.get_state()==GUI_STATE_ACTIVE){
        selected_answer=4;
    }

    if(selected_answer!=0){
        if(selected_answer==correct_answer){
            right_selected=1;
        }else{
            right_selected=0;
        }
    }

    win.render_gui_element(answer1);
    win.render_gui_element(answer2);
    win.render_gui_element(answer3);
    win.render_gui_element(answer4);

    if(right_selected==1&&selected_answer==0){
        return 1;
    }
    if(right_selected==0&&selected_answer==0){
        return -1;
    }
    return 0;
}