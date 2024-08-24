#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include "rendering/event_mgr.hpp"

using namespace std;

#define GUI_STATE_NORMAL 0
#define GUI_STATE_HOVER 1
#define GUI_STATE_ACTIVE 2
#define GUI_STATE_DISABLE -1

class gui_element {
    public:
        /// @brief Shortest constructor.
        /// @param p_tex_normal Texture at a normal state.
        /// @param p_events Main event manager.
        /// @param p_coords X and Y coordinates of the texture.
        gui_element(SDL_Texture* p_tex_normal, SDL_Point p_coords);

        /// @brief Mid-length constructor.
        /// @param p_tex_normal Texture in a normal state.
        /// @param p_tex_active Texture in an active state (while cursor is over and mouse pressed)
        /// @param p_events Main event manager.
        /// @param p_coords X and Y coordinates os the textures.
        gui_element(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_active, SDL_Point p_coords);

        /// @brief Full-length construtor.
        /// @param p_tex_normal Texture in a normal state.
        /// @param p_tex_hover Texture in a hovered state (when the cursor is over it)
        /// @param p_tex_active Texture in an active state (while cursor is over and mouse pressed)
        /// @param p_tex_disabled Texture in a disabled state
        /// @param p_events Main event manager.
        /// @param p_coords X and Y coordinates of the texture.
        gui_element(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_hover, SDL_Texture* p_tex_active, SDL_Texture* p_tex_disabled, SDL_Point p_coords);

        /// @brief Sets another state.
        /// @param p_state State to set.
        void set_state(int p_state);

        /// @brief Getter of the current state.
        /// @return Current state of the gui_element.
        int get_state();

        /// @brief Updates the current state. Changes between different gui elements.
        virtual void update()=0;        //pure virtual method (equivalent of abstract) (updates state)
        
        /// @brief Getter of the current texture based on the state.
        /// @return The meant texture.
        SDL_Texture* get_current_state_texture();

        /// @brief Sets the state to disabled. Behaviour on the state can change based on the update() method.
        void disable();
        
        /// @brief Sets the state to enabled.
        void enable();

        /// @brief Gets the X coordinate.
        /// @return X coord.
        int get_x();

        /// @brief Sets the X coordinate.
        /// @param p_x X coord. to set.
        void set_x(int p_x);

        /// @brief Gets the Y coordinate.
        /// @return Y coord.
        int get_y();

        /// @brief Sets the Y coordinate.
        /// @param p_y Y coord.
        void set_y(int p_y);

    protected:
        SDL_Texture* tex_normal;
        SDL_Texture* tex_hover;
        SDL_Texture* tex_active;
        SDL_Texture* tex_disabled;

        SDL_Texture* current_state_texture;

        int state;
        
        int x,y;

};
