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

level::level(render_window& p_win, fontcache& p_quest_fc, fontcache& p_answ_fc)
    :   win(p_win), 
        quest_fc(p_quest_fc), 
        answ_fc(p_answ_fc),
        tex_1(p_win.load_texture("../res/gfx/button_normal.png")),
        tex_2(p_win.load_texture("../res/gfx/button_active.png")),
        answer1(tex_1, tex_2,
                {10,10}, p_win, p_answ_fc, "PROVA", p_win.get_texture_width(tex_1)/2, 20)
{

}

bool level::update_render(){
    answer1.update();
    win.render_text_fc(answ_fc, "LOL", 10,500);
    win.render_gui_element(answer1);

    return false;
}