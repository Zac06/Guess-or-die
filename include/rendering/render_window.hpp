#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<string>
#include<queue>
#include<sstream>

#include "base_elements/entity.hpp"
#include "rendering/fontcache.hpp"
#include "base_elements/gui_element.hpp"

using namespace std;

class render_window{
    public:
        /// @brief Constructor. Takes a window title, and size.
        /// @param p_title Window title
        /// @param p_w Window width
        /// @param p_h Window height
        render_window(string p_title, int p_w, int p_h);
        ~render_window();

        /// @brief Returns pointer to renderer. Useful for setupping the fontcache
        /// @return Pointer to renderer
        SDL_Renderer* get_renderer();

        //void clean();

        /// @brief cleans up renderer memory, aka cleans the screen.
        void clear();

        /// @brief cleans the screen, but sets background color.
        /// @param p_bgcolor 
        void clear(SDL_Color p_bgcolor);

        /// @brief Returns program state (running/not running)
        /// @return current state of program
        bool is_running();

        /// @brief Sets program state (true=running, false=not running)
        /// @param p_run State to set.
        void set_running(bool p_run);

        /// @brief Returns the width of a given texture.
        /// @param p_tex Texture to query the width of
        /// @return The actual width of the given texture
        int get_texture_width(SDL_Texture* p_tex);

        /// @brief Returns the height of a given texture.
        /// @param p_tex Texture to query the height of
        /// @return The actual height of the given texture
        int get_texture_height(SDL_Texture* p_tex);

        /// @brief loads texture from file into memory. Prints error if fails.
        /// @param p_filepath Path to the file of the texture to load.
        /// @return NULL if fails, pointer to texture otherwise.
        SDL_Texture* load_texture(string p_filepath);
        
        /// @brief loads font from file into memory. Prints error if fails
        /// @param p_filepath  Path to the file of the font to load.
        /// @param size size of the font you want to use (Es. Arial, 10pt)
        /// @return NULL if fails, pointer to font otherwise.
        TTF_Font* load_font(string p_filepath, int size);

        /// @brief loads audio from file into memory. Prints error if fails.
        /// @param p_filepath Path to the file of the audio to load.
        /// @return NULL if fails, pointer to audio otherwise.
        Mix_Chunk* load_sound(string p_filepath);

        /// @brief Copies a texture to the rendering engine. Width and height are determined by the texture size.
        /// @param p_tex Texture to render. Must be loaded.
        /// @param p_x Horizontal position where the top left of the texture is positioned.
        /// @param p_y Vertical position where the top left of the texture is positioned.
        void render_texture(SDL_Texture* p_tex, int p_x, int p_y);

        /// @brief  Copies a texture to the rendering engine. Width and height are determined by the texture size multiplied by the scale
        /// @param p_tex Texture to render. Must be loaded.
        /// @param p_x Horizontal position where the top left of the texture is positioned.
        /// @param p_y Vertical position where the top left of the texture is positioned.
        /// @param scale Scaling factor. If 1, renders as normal.
        void render_texture_ex(SDL_Texture* p_tex, int p_x, int p_y, float scale);

        /// @brief  Copies a texture to the rendering engine. Width and height are determined by the user.
        /// @param p_tex Texture to render. Must be loaded.
        /// @param p_x Horizontal position where the top left of the texture is positioned.
        /// @param p_y Vertical position where the top left of the texture is positioned.
        /// @param p_w Width of the texture to display.
        /// @param p_h Height of the texture to display.
        void render_texture_ex2(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h);
        
        /// @brief  Copies a texture to the rendering engine. Width and height are determined by the texture size multiplied by the scale
        /// @param p_tex Texture to render. Must be loaded.
        /// @param p_x Horizontal position where the top left of the texture is positioned.
        /// @param p_y Vertical position where the top left of the texture is positioned.
        /// @param scale Scaling factor. If 1, renders as normal.
        /// @param rotation Angle of rotation. Rotation focus is the center of the texture.
        void render_texture_pro(SDL_Texture* p_tex, int p_x, int p_y, float scale, float rotation);
        
        /// @brief  Copies a texture to the rendering engine. Width and height are determined by the texture size multiplied by the scale
        /// @param p_tex Texture to render. Must be loaded.
        /// @param p_x Horizontal position where the top left of the texture is positioned.
        /// @param p_y Vertical position where the top left of the texture is positioned.
        /// @param scale Scaling factor. If 1, renders as normal.
        /// @param rotation Angle of rotation.
        /// @param rot_center Rotation focus.
        void render_texture_ultra(SDL_Texture* p_tex, int p_x, int p_y, float scale, float rotation, SDL_Point rot_center);

        /// @brief  Copies a texture to the rendering engine. Width and height are determined by the user and multiplied by the scale
        /// @param p_tex Texture to render. Must be loaded.
        /// @param p_x Horizontal position where the top left of the texture is positioned.
        /// @param p_y Vertical position where the top left of the texture is positioned.
        /// @param p_w Width of the texture to display.
        /// @param p_h Height of the texture to display.
        /// @param scale Scaling factor. If 1, renders as normal.
        /// @param rotation Angle of rotation.
        /// @param rot_center Rotation focus.
        void render_texture_ultra2(SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h, float scale, float rotation, SDL_Point rot_center);

        /// @brief Renders some text to the screen using TTF rendering.
        /// @param font Font to use for the rendering
        /// @param text String to display.
        /// @param color Color of the text to display.
        /// @param destx X position of the text to render
        /// @param desty Y position of the text to render
        void render_text(TTF_Font* font, string text, SDL_Color color, int destx, int desty);

        /// @brief Renders some text to the screen using TTF rendering.
        /// @param font Font to use for the rendering
        /// @param text String to display.
        /// @param color Color of the text to display.
        /// @param destx X position of the text to render
        /// @param desty Y position of the text to render
        /// @param scale Scaling of the text to render. May become blurry.
        void render_text_ex(TTF_Font* font, string text, SDL_Color color, int destx, int desty, float scale);

        /// @brief Renders some text to the screen using the fontcache.
        /// @param p_fc fontcache to use to render the characters.
        /// @param text Text to render.
        /// @param destx X position of the text to render
        /// @param desty Y position of the text to render
        void render_text_fc(fontcache& p_fc, string text, int destx, int desty, bool center=false);

        /// @brief Renders some text to the screen using the fontcache.
        /// @param p_fc fontcache to use to render the characters.
        /// @param text Text to render.
        /// @param destx X position of the text to render
        /// @param desty Y position of the text to render
        /// @param scale Scaling of the text to render. May become blurry.
        void render_text_fc_ex(fontcache& p_fc, string text, int destx, int desty, float scale);

        /// @brief Renders an entity using its inner attributes.
        /// @param p_ent Entity to render.
        void render_entity(entity& p_ent, bool p_invert_y=true);

        /// @brief Renders a subclass instance of gui_element using its inner attributes.
        /// @param p_gui_el Gui element to render.
        void render_gui_element(gui_element& p_gui_el);

        /// @brief Plays a sound.
        /// @param p_sound Sound to play. Must be loaded.
        void play_sound(Mix_Chunk* p_sound);

        /// @brief Plays a sound.
        /// @param p_sound Sound to play. Must be loaded.
        /// @param p_times Number of times for the sound to be played. -1 if infinitely (around 65k times)
        void play_sound_ex(Mix_Chunk* p_sound, int p_times);

        /// @brief Plays a sound.
        /// @param p_channel Channel to play the sound in.
        /// @param p_sound Sound to play. Must be loaded.
        /// @param p_times Number of times for the sound to be played. -1 if infinitely (around 65k times)
        void play_sound_pro(int p_channel, Mix_Chunk* p_sound, int p_times);

        /// @brief shows the rendering buffer contents to the screen (updates it)
        void display();

        /// @brief returns the width of a line of text, until the next newline.
        int get_text_width(string& p_str, fontcache& p_fc);

        int get_win_width();

        int get_win_height();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool running;

        SDL_Event event;

        vector<SDL_Texture*> loaded_textures;
        vector<TTF_Font*> loaded_fonts;
        vector<Mix_Chunk*> loaded_sounds;
};
