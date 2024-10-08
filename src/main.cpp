#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<unistd.h>

#include "rendering/render_window.hpp"
#include "base_elements/entity.hpp"
#include "rendering/fontcache.hpp"
#include "rendering/event_mgr.hpp"
#include "base_elements/gui_element.hpp"
#include "gui_elements/gui_button.hpp"

#include "game_elements/game.hpp"

using namespace std;

/// @brief initializes all necessary elements. Prints errors if something fails.
/// @return true if everything initializes successfully, false if something fails.
bool check_functions(){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)>0){
        cerr<<"SDL_Init() has failed. Error code: "<<SDL_GetError()<<"\n";
        return false;
    }
    if(!IMG_Init(IMG_INIT_PNG)){
        cerr<<"IMG_Init(IMG_INIT_PNG) has failed. Error code: "<<SDL_GetError()<<"\n";
        return false;
    }
    if(TTF_Init()!=0){
        cerr<<"TTF_init() has failed. Error: "<<SDL_GetError()<<"\n";
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)!=0){
        cerr<<"Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) has failed. Error code: "<<SDL_GetError()<<"\n";
        return false;
    }

    return true;
}

/// @brief Closes everything that has been initialized in check_functions
void close(){
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool is_admin(){
    BOOL admin_perms=false;
    PSID admin_grp; //contains admin token
    SID_IDENTIFIER_AUTHORITY admin_auth=SECURITY_NT_AUTHORITY;

    if(AllocateAndInitializeSid(&admin_auth, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0,0,0,0,0,0,&admin_grp)){
        if(!CheckTokenMembership(NULL, admin_grp, &admin_perms)){
            FreeSid(admin_grp);
            admin_perms=FALSE;
        }
    }

    FreeSid(admin_grp);
    return admin_perms;
}

int main(int argc, char** argv){
    if(!check_functions()){
        return -1;
    }

    if(!is_admin()){
        MessageBoxA(NULL, "Please execute launch.bat as an administrator! These are needed for the game mechanics (penalties) to work correctly.", "Admin permissions needed", MB_OK | MB_ICONINFORMATION);
        return -1;
    }

    render_window window("SDL_base", 900, 675);                         //initializes the window and the renderer
    TTF_Font* main_font=window.load_font("../res/font/CustomKarmaticArcade.ttf", 40);
    TTF_Font* second_font=window.load_font("../res/font/CustomKarmaticArcade.ttf", 25);
    
    guess_or_die game(window, main_font, second_font);

    event_mgr::init();                                  //initialize event_mgr attributes

    while(window.is_running()){                         //while the window is still running
        window.clear();                                 //refreshes the screen. Might take a color as parameter (background color)
        
        event_mgr::update();                            //refreshes the events. While with a continuous polling of events you could manage one event at a time, 
                                                        //and it was lost before you could go on with the other, now it is refreshed at request and all the pumped
                                                        //events are available until the next refresh
        if(event_mgr::get_event(SDL_QUIT).status==true){        //close button handling
            window.set_running(false);
        }

        game.render();

        window.display();                               //displays everything that has been put in the renderer
    }

    close();

    return 0;
}