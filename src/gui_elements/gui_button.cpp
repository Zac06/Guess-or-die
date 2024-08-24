#include "gui_elements/gui_button.hpp"

gui_button::gui_button(SDL_Texture* p_tex_normal, SDL_Point p_coords)
    :gui_element(p_tex_normal, p_coords)
{}

gui_button::gui_button(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_active, SDL_Point p_coords)
    :gui_element(p_tex_normal, p_tex_active, p_coords)
{}


gui_button::gui_button(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_hover, SDL_Texture* p_tex_active, SDL_Texture* p_tex_disabled, SDL_Point p_coords)
    :gui_element(p_tex_normal, p_tex_hover, p_tex_active, p_tex_disabled, p_coords)
{}

void gui_button::update(){
    if(state==GUI_STATE_DISABLE){
        return;
    }

    int mousex, mousey;
    int w, h;
    bool last_state=state;

    SDL_QueryTexture(current_state_texture, NULL, NULL, &w, &h);
    SDL_GetMouseState(&mousex, &mousey);

    if(mousex>=x&&mousex<=x+w&&mousey>=y&&mousey<=y+h){
        ev_ret_type mousequerydown=event_mgr::get_event(SDL_MOUSEBUTTONDOWN);
        ev_ret_type mousequeryup=event_mgr::get_event(SDL_MOUSEBUTTONUP);

        if(state!=GUI_STATE_ACTIVE&&mousequerydown.status&&mousequerydown.event.button.button==SDL_BUTTON_LEFT){
            state=GUI_STATE_ACTIVE;
        }else if(state==GUI_STATE_ACTIVE&&mousequeryup.status&&mousequeryup.event.button.button==SDL_BUTTON_LEFT){
            state=GUI_STATE_HOVER;
        }else if(state!=GUI_STATE_ACTIVE){
            state=GUI_STATE_HOVER;
        }
    }else{
        state=GUI_STATE_NORMAL;
    }

    if(state==last_state){
        return;
    }

    switch(state){
        case GUI_STATE_NORMAL:{
            current_state_texture=tex_normal;
            break;
        }
        case GUI_STATE_HOVER:{
            current_state_texture=tex_hover;
            break;
        }
        case GUI_STATE_ACTIVE:{
            current_state_texture=tex_active;
            break;
        }
        case GUI_STATE_DISABLE:{
            current_state_texture=tex_disabled;
            break;
        }
        default:{
            current_state_texture=NULL;
            break;
        }
    }

}