#include "rendering/fontcache.hpp"

fontcache::fontcache(TTF_Font* p_f, int p_font_size, SDL_Color p_color, SDL_Renderer* p_rend)
    :char_textures(256, NULL), font_size(p_font_size), font(p_f), color(p_color)
{
    SDL_Surface* tmp_surface;   //temporary surface to render the text on
    char tmp_str[2]={0,0};

    for(int i=0; i<(int)char_textures.size(); i++){
        tmp_str[0]=(char)i;     //char to render
        tmp_surface=TTF_RenderText_Solid(font, tmp_str, color);     //transform into a surface
        char_textures[i]=SDL_CreateTextureFromSurface(p_rend, tmp_surface);     //transform into a texture
        SDL_FreeSurface(tmp_surface);       //free the surface
    }
}

fontcache::~fontcache(){
    for(int i=0; i<(int)char_textures.size(); i++){
        SDL_DestroyTexture(char_textures[i]);           //deallocate everything
    }
}

SDL_Texture* fontcache::get_char_texture(unsigned char c){
    if(c>=char_textures.size()||c<0){       //if it's not a valid char, return NULL
        return NULL;
    }
    return char_textures[c];
}

void fontcache::set_char_texture(SDL_Texture* p_tex, unsigned char c){
    if(c>=char_textures.size()||c<0){       //if it's not a valid char, exit and do not set
        return;
    }
    char_textures[c]=p_tex;
}

int fontcache::get_fc_size(){
    return char_textures.size();
}

int fontcache::get_font_size(){
    return font_size;
}

SDL_Color fontcache::get_color(){
    return color;
}
