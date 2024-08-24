#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include<algorithm>
#include<list>

using namespace std;


struct ev_ret_type {
    bool status;
    SDL_Event& event;
};

struct keypress {
    int keysym;
    bool pressed;

    bool operator<(const keypress& kp){
        return keysym<kp.keysym;
    }
};

class event_status {
    public: 
        int event_type=SDL_FIRSTEVENT;
        bool status;
        SDL_Event event;

        event_status(int p_event_type, bool p_status, SDL_Event p_event)
            :event_type(p_event_type), status(p_status), event(p_event)
        {}
        
        bool operator<(const event_status& es){
            return event_type<es.event_type;
        }
};

class event_mgr {
    public:
        /// @brief Initializes everything
        static void init();

        /// @brief Updates the events and puts them into a table.
        static void update();

        /// @brief Searches for an event based on its ID and returns its state and data.
        /// @param p_event_id ID that you want to search.
        /// @return A struct containing the state and the data.
        static ev_ret_type get_event(int p_event_id);

        /// @brief Returns the state of a keyboard key based on its virtual keycode.
        /// @param p_vkeycode Virtual keycode to search. It must be between the SDLK codes.
        /// @return Returns state of the key.
        static bool iskeypress(int p_vkeycode);
        
    private:
        static SDL_Event event;
        static vector<event_status> event_container;

        static list<int> to_clear;
        static vector<keypress> curr_pressed_keys;

        static int get_event_container_pos(int p_event_type);
        static int get_curr_pressed_keys_pos(int p_vkeycode);
        static void manage_keypress(int p_ev_cont_pos);
};