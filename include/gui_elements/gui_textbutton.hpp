#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include "base_elements/gui_element.hpp"
#include "gui_elements/gui_button.hpp"

#include "rendering/render_window.hpp"
#include "rendering/fontcache.hpp"

#include<string>

class gui_textbutton : public gui_button {
    private:
        render_window& win;
        fontcache& fc;

        static SDL_Texture* build_text_texture(SDL_Texture* p_base, render_window& p_win, fontcache& p_fc, std::string p_txt, int p_txt_x, int p_txt_y, bool center=true);

    public:
        gui_textbutton(SDL_Texture* p_tex_normal, SDL_Point p_coords, render_window& p_win, fontcache& p_fc, std::string p_txt, int p_txt_x, int p_txt_y, bool center=true);

        gui_textbutton(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_active, SDL_Point p_coords, render_window& p_win, fontcache& p_fc, std::string p_txt, int p_txt_x, int p_txt_y, bool center=true);

        gui_textbutton(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_hover, SDL_Texture* p_tex_active, SDL_Texture* p_tex_disabled, SDL_Point p_coords, render_window& p_win, fontcache& p_fc, std::string p_txt, int p_txt_x, int p_txt_y, bool center=true);

};