#include "base_elements/entity.hpp"

entity::entity(double p_x, double p_y, SDL_Texture* p_tex)
    :x(p_x), y(p_y), tex(p_tex)
{
    int f_w, f_h;

    SDL_QueryTexture(p_tex, NULL, NULL, &f_w, &f_h);    //detect width and length of the texture
    w=f_w;
    h=f_h;
    rotation=0;
    rot_center={0,0};
}

entity::entity(double p_x, double p_y, double p_w, double p_h, SDL_Texture* p_tex)
    :x(p_x), y(p_y), w(p_w), h(p_h), tex(p_tex)
{
    rotation=0;
    rot_center={0,0};
    scale=1;
}

entity::~entity(){
    SDL_DestroyTexture(tex);
}

void entity::set_x(double p_x){
    x=p_x;
}

double entity::get_x(){
    return x;
}

void entity::set_y(double p_y){
    y=p_y;
}

double entity::get_y(){
    return y;
}

void entity::set_w(double p_w){
    w=p_w;
}

double entity::get_w(){
    return w;
}

void entity::set_h(double p_h){
    h=p_h;
}

double entity::get_h(){
    return h;
}

void entity::set_rotation(double p_rotation){
    rotation=p_rotation;
}

double entity::get_rotation(){
    return rotation;
}

void entity::set_scale(float p_scale){
    scale=p_scale;
}

float entity::get_scale(){
    return scale;
}

SDL_Texture* entity::get_tex(){
    return tex;
}

void entity::set_rot_center(SDL_Point p_rot_center){
    rot_center=p_rot_center;
}

SDL_Point entity::get_rot_center(){
    return rot_center;
}
