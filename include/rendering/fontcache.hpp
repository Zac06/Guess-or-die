#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<vector>
#include<iostream>
using namespace std;

/// @brief This class caches the rendered textures of a given font at a given size. It uses the ASCII base.
class fontcache{
    private:
        vector<SDL_Texture*> char_textures;
        int font_size;
        TTF_Font* font;
        SDL_Color color;
        
    public:
        /// @brief Constructor. Builds the fontcache.
        /// @param p_f Font to use to cache the characters.
        /// @param p_font_size Size of the font to render (es. Arial, 10pt)
        /// @param p_color Color of the font to render.
        /// @param p_rend Renderer. Usually took from render_window::get_renderer();
        fontcache(TTF_Font* p_f, SDL_Color p_color, SDL_Renderer* p_rend);
        ~fontcache();

        /// @brief returns the texture of a single character. Used when rendering.
        /// @param c Character to return the texture of.
        /// @return 
        SDL_Texture* get_char_texture(unsigned char c);

        /// @brief sets the texture of a single char. Useful when building the fontcache.
        /// @param p_tex Texture to set
        /// @param c Character to set the texture of
        void set_char_texture(SDL_Texture* p_tex, unsigned char c);

        /// @brief Returns the size of the buffer containing the textures themselves
        /// @return The actual buffer size
        int get_fc_size();

        /// @brief Returns the size of the font given in the constructor
        /// @return The actual font size
        int get_font_size();

        /// @brief Returns the color of the font given in the constructor
        /// @return The actual color of the font
        SDL_Color get_color();
};
