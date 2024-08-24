#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include <string>

using namespace std;

/// @brief This class uses a texture and its position to render everything it needs.
class entity {
    public:
        /// @brief Constructor. Initializes x, y and textures. w and h are the ones of the texture.
        /// @param p_x Initial position of the X coordinate.
        /// @param p_y Initial position of the Y coordinate.
        /// @param p_tex Texture of the entity.
        entity(double p_x, double p_y, SDL_Texture* p_tex);

        /// @brief Constructor. Initializes x, y and textures.
        /// @param p_x Initial position of the X coordinate.
        /// @param p_y Initial position of the Y coordinate.
        /// @param p_w Width of the entity.
        /// @param p_h Height of the entity.
        /// @param p_tex Texture of the entity.
        entity(double p_x, double p_y, double p_w, double p_h, SDL_Texture* p_tex);
        
        ~entity();

        /// @brief Sets the X position.
        /// @param p_x New X to set.
        void set_x(double p_x);

        /// @brief Gets the current X position.
        /// @return The current X position.
        double get_x();

        /// @brief Sets the Y position.
        /// @param p_x New Y to set.
        void set_y(double p_y);

        /// @brief Gets the current Y position.
        /// @return The current Y position.
        double get_y();

        /// @brief Sets the entity width.
        /// @param p_w New W to set.
        void set_w(double p_w);
        
        /// @brief Gets the current width.
        /// @return The current width.
        double get_w();

        /// @brief Sets the entity height.
        /// @param p_h New H to set.
        void set_h(double p_h);
        
        /// @brief Gets the current height.
        /// @return The current height.
        double get_h();

        /// @brief Sets the scaling.
        /// @param scale New scale to set.
        void set_scale(float scale);
        
        /// @brief Gets the current scale.
        /// @return The current scale.
        float get_scale();

        /// @brief Sets the rotation.
        /// @param scale New rotation to set.
        void set_rotation(double p_rotation);

        /// @brief Gets the current rotation.
        /// @return The current rotation.
        double get_rotation();
        
        /// @brief Gets the entity's texture.
        /// @return The current texture.
        SDL_Texture* get_tex();
        
        /// @brief Sets the rotation center.
        /// @param pt New rotation center,
        void set_rot_center(SDL_Point pt);

        /// @brief Gets the rotation center.
        /// @return The current rotation center.
        SDL_Point get_rot_center();
    private:
        double x;
        double y;
        double w;
        double h;
        double rotation;
        float scale;

        SDL_Point rot_center;

        SDL_Texture* tex;
};
