#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include "base_elements/gui_element.hpp"

using namespace std;

class gui_button : public gui_element{
    public:
        /// @brief Shortest constructor.
        /// @param p_tex_normal Texture at a normal state.
        /// @param p_events Main event manager.
        /// @param p_coords X and Y coordinates of the texture.
        gui_button(SDL_Texture* p_tex_normal, SDL_Point p_coords);

        /// @brief Mid-length constructor.
        /// @param p_tex_normal Texture in a normal state.
        /// @param p_tex_active Texture in an active state (while cursor is over and mouse pressed)
        /// @param p_events Main event manager.
        /// @param p_coords X and Y coordinates os the textures.
        gui_button(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_active, SDL_Point p_coords);

        /// @brief Full-length construtor.
        /// @param p_tex_normal Texture in a normal state.
        /// @param p_tex_hover Texture in a hovered state (when the cursor is over it)
        /// @param p_tex_active Texture in an active state (while cursor is over and mouse pressed)
        /// @param p_tex_disabled Texture in a disabled state
        /// @param p_events Main event manager.
        /// @param p_coords X and Y coordinates of the texture.
        gui_button(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_hover, SDL_Texture* p_tex_active, SDL_Texture* p_tex_disabled, SDL_Point p_coords);

        /// @brief Checks for new states to become.
        void update() override;

    private:
        bool ismousedown;

};