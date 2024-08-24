#include "base_elements/gui_element.hpp"

gui_element::gui_element(SDL_Texture* p_tex_normal, SDL_Point p_coords)
    :tex_normal(p_tex_normal), 
    tex_hover(p_tex_normal), 
    tex_active(p_tex_normal), 
    tex_disabled(p_tex_normal),
    current_state_texture(p_tex_normal),
    state(0)
{
    x=p_coords.x;
    y=p_coords.y;
}

gui_element::gui_element(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_active, SDL_Point p_coords)
    :tex_normal(p_tex_normal), 
    tex_hover(p_tex_normal), 
    tex_active(p_tex_active), 
    tex_disabled(p_tex_normal),
    current_state_texture(p_tex_normal),
    state(0)
{
    x=p_coords.x;
    y=p_coords.y;
}

gui_element::gui_element(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_hover, SDL_Texture* p_tex_active, SDL_Texture* p_tex_disabled, SDL_Point p_coords)
    :tex_normal(p_tex_normal), 
    tex_hover(p_tex_hover), 
    tex_active(p_tex_active), 
    tex_disabled(p_tex_disabled),
    current_state_texture(p_tex_normal),
    state(0)
{
    x=p_coords.x;
    y=p_coords.y;
}

void gui_element::set_state(int p_state){
    state=p_state;
}

int gui_element::get_state(){
    return state;
}

SDL_Texture* gui_element::get_current_state_texture(){
    return current_state_texture;
}

void gui_element::disable(){
    state=GUI_STATE_DISABLE;
    current_state_texture=tex_disabled;
}

void gui_element::enable(){
    state=GUI_STATE_NORMAL;
    current_state_texture=tex_normal;
}

int gui_element::get_x(){
    return x;
}

int gui_element::get_y(){
    return y;
}

void gui_element::set_x(int p_x){
    x=p_x;
}

void gui_element::set_y(int p_y){
    y=p_y;
}