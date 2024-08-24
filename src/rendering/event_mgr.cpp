#include "rendering/event_mgr.hpp"

SDL_Event event_mgr::event;
vector<event_status> event_mgr::event_container;
list<int> event_mgr::to_clear;
vector<keypress> event_mgr::curr_pressed_keys;

void event_mgr::init(){
    event_container={
            event_status(SDL_FIRSTEVENT, false, SDL_Event()),

            event_status(SDL_QUIT, false, SDL_Event()),

            event_status(SDL_APP_TERMINATING, false, SDL_Event()),
            event_status(SDL_APP_LOWMEMORY, false, SDL_Event()),
            event_status(SDL_APP_WILLENTERBACKGROUND, false, SDL_Event()),
            event_status(SDL_APP_DIDENTERBACKGROUND, false, SDL_Event()),
            event_status(SDL_APP_WILLENTERFOREGROUND, false, SDL_Event()),
            event_status(SDL_APP_DIDENTERFOREGROUND, false, SDL_Event()),

            event_status(SDL_LOCALECHANGED, false, SDL_Event()),
            event_status(SDL_DISPLAYEVENT, false, SDL_Event()),
            event_status(SDL_WINDOWEVENT, false, SDL_Event()),
            event_status(SDL_SYSWMEVENT, false, SDL_Event()),

            event_status(SDL_KEYDOWN, false, SDL_Event()),
            event_status(SDL_KEYUP, false, SDL_Event()),
            event_status(SDL_TEXTEDITING, false, SDL_Event()),
            event_status(SDL_TEXTINPUT, false, SDL_Event()),
            event_status(SDL_KEYMAPCHANGED, false, SDL_Event()),
            event_status(SDL_TEXTEDITING_EXT, false, SDL_Event()),

            event_status(SDL_MOUSEMOTION, false, SDL_Event()),
            event_status(SDL_MOUSEBUTTONDOWN, false, SDL_Event()),
            event_status(SDL_MOUSEBUTTONUP, false, SDL_Event()),
            event_status(SDL_MOUSEWHEEL, false, SDL_Event()),

            event_status(SDL_JOYAXISMOTION, false, SDL_Event()),
            event_status(SDL_JOYBALLMOTION, false, SDL_Event()),
            event_status(SDL_JOYHATMOTION, false, SDL_Event()),
            event_status(SDL_JOYBUTTONDOWN, false, SDL_Event()),
            event_status(SDL_JOYBUTTONUP, false, SDL_Event()),
            event_status(SDL_JOYDEVICEADDED, false, SDL_Event()),
            event_status(SDL_JOYDEVICEREMOVED, false, SDL_Event()),
            event_status(SDL_JOYBATTERYUPDATED, false, SDL_Event()),

            event_status(SDL_CONTROLLERAXISMOTION, false, SDL_Event()),
            event_status(SDL_CONTROLLERBUTTONDOWN, false, SDL_Event()),
            event_status(SDL_CONTROLLERBUTTONUP, false, SDL_Event()),
            event_status(SDL_CONTROLLERDEVICEADDED, false, SDL_Event()),
            event_status(SDL_CONTROLLERDEVICEREMOVED, false, SDL_Event()),
            event_status(SDL_CONTROLLERDEVICEREMAPPED, false, SDL_Event()),
            event_status(SDL_CONTROLLERTOUCHPADDOWN, false, SDL_Event()),
            event_status(SDL_CONTROLLERTOUCHPADMOTION, false, SDL_Event()),
            event_status(SDL_CONTROLLERTOUCHPADUP, false, SDL_Event()),
            event_status(SDL_CONTROLLERSENSORUPDATE, false, SDL_Event()),

            event_status(SDL_FINGERDOWN, false, SDL_Event()),
            event_status(SDL_FINGERUP, false, SDL_Event()),
            event_status(SDL_FINGERMOTION, false, SDL_Event()),

            event_status(SDL_DOLLARGESTURE, false, SDL_Event()),
            event_status(SDL_DOLLARRECORD, false, SDL_Event()),
            event_status(SDL_MULTIGESTURE, false, SDL_Event()),

            event_status(SDL_CLIPBOARDUPDATE, false, SDL_Event()),

            event_status(SDL_DROPFILE, false, SDL_Event()),

            event_status(SDL_DROPTEXT, false, SDL_Event()),
            event_status(SDL_DROPBEGIN, false, SDL_Event()),
            event_status(SDL_DROPCOMPLETE, false, SDL_Event()),

            event_status(SDL_AUDIODEVICEADDED, false, SDL_Event()),
            event_status(SDL_AUDIODEVICEREMOVED, false, SDL_Event()),

            event_status(SDL_SENSORUPDATE, false, SDL_Event()),

            event_status(SDL_RENDER_TARGETS_RESET, false, SDL_Event()),
            event_status(SDL_RENDER_DEVICE_RESET, false, SDL_Event()),

            event_status(SDL_POLLSENTINEL, false, SDL_Event()),

            event_status(SDL_USEREVENT, false, SDL_Event())

        };
    curr_pressed_keys={
            {SDLK_UNKNOWN, false},
            {SDLK_BACKSPACE, false},
            {SDLK_TAB, false},
            {SDLK_RETURN, false},
            {SDLK_ESCAPE, false},
            {SDLK_SPACE, false},
            {SDLK_EXCLAIM, false},
            {SDLK_QUOTEDBL, false},
            {SDLK_HASH, false},
            {SDLK_DOLLAR, false},
            {SDLK_PERCENT, false},
            {SDLK_AMPERSAND, false},
            {SDLK_QUOTE, false},
            {SDLK_LEFTPAREN, false},
            {SDLK_RIGHTPAREN, false},
            {SDLK_ASTERISK, false},
            {SDLK_PLUS, false},
            {SDLK_COMMA, false},
            {SDLK_MINUS, false},
            {SDLK_PERIOD, false},
            {SDLK_SLASH, false},
            {SDLK_0, false},
            {SDLK_1, false},
            {SDLK_2, false},
            {SDLK_3, false},
            {SDLK_4, false},
            {SDLK_5, false},
            {SDLK_6, false},
            {SDLK_7, false},
            {SDLK_8, false},
            {SDLK_9, false},
            {SDLK_COLON, false},
            {SDLK_SEMICOLON, false},
            {SDLK_LESS, false},
            {SDLK_EQUALS, false},
            {SDLK_GREATER, false},
            {SDLK_QUESTION, false},
            {SDLK_AT, false},
            {SDLK_LEFTBRACKET, false},
            {SDLK_BACKSLASH, false},
            {SDLK_RIGHTBRACKET, false},
            {SDLK_CARET, false},
            {SDLK_UNDERSCORE, false},
            {SDLK_BACKQUOTE, false},
            {SDLK_a, false},
            {SDLK_b, false},
            {SDLK_c, false},
            {SDLK_d, false},
            {SDLK_e, false},
            {SDLK_f, false},
            {SDLK_g, false},
            {SDLK_h, false},
            {SDLK_i, false},
            {SDLK_j, false},
            {SDLK_k, false},
            {SDLK_l, false},
            {SDLK_m, false},
            {SDLK_n, false},
            {SDLK_o, false},
            {SDLK_p, false},
            {SDLK_q, false},
            {SDLK_r, false},
            {SDLK_s, false},
            {SDLK_t, false},
            {SDLK_u, false},
            {SDLK_v, false},
            {SDLK_w, false},
            {SDLK_x, false},
            {SDLK_y, false},
            {SDLK_z, false},
            {SDLK_DELETE, false},
            {SDLK_CAPSLOCK, false},
            {SDLK_F1, false},
            {SDLK_F2, false},
            {SDLK_F3, false},
            {SDLK_F4, false},
            {SDLK_F5, false},
            {SDLK_F6, false},
            {SDLK_F7, false},
            {SDLK_F8, false},
            {SDLK_F9, false},
            {SDLK_F10, false},
            {SDLK_F11, false},
            {SDLK_F12, false},
            {SDLK_PRINTSCREEN, false},
            {SDLK_SCROLLLOCK, false},
            {SDLK_PAUSE, false},
            {SDLK_INSERT, false},
            {SDLK_HOME, false},
            {SDLK_PAGEUP, false},
            {SDLK_END, false},
            {SDLK_PAGEDOWN, false},
            {SDLK_RIGHT, false},
            {SDLK_LEFT, false},
            {SDLK_DOWN, false},
            {SDLK_UP, false},
            {SDLK_NUMLOCKCLEAR, false},
            {SDLK_KP_DIVIDE, false},
            {SDLK_KP_MULTIPLY, false},
            {SDLK_KP_MINUS, false},
            {SDLK_KP_PLUS, false},
            {SDLK_KP_ENTER, false},
            {SDLK_KP_1, false},
            {SDLK_KP_2, false},
            {SDLK_KP_3, false},
            {SDLK_KP_4, false},
            {SDLK_KP_5, false},
            {SDLK_KP_6, false},
            {SDLK_KP_7, false},
            {SDLK_KP_8, false},
            {SDLK_KP_9, false},
            {SDLK_KP_0, false},
            {SDLK_KP_PERIOD, false},
            {SDLK_APPLICATION, false},
            {SDLK_POWER, false},
            {SDLK_KP_EQUALS, false},
            {SDLK_F13, false},
            {SDLK_F14, false},
            {SDLK_F15, false},
            {SDLK_F16, false},
            {SDLK_F17, false},
            {SDLK_F18, false},
            {SDLK_F19, false},
            {SDLK_F20, false},
            {SDLK_F21, false},
            {SDLK_F22, false},
            {SDLK_F23, false},
            {SDLK_F24, false},
            {SDLK_EXECUTE, false},
            {SDLK_HELP, false},
            {SDLK_MENU, false},
            {SDLK_SELECT, false},
            {SDLK_STOP, false},
            {SDLK_AGAIN, false},
            {SDLK_UNDO, false},
            {SDLK_CUT, false},
            {SDLK_COPY, false},
            {SDLK_PASTE, false},
            {SDLK_FIND, false},
            {SDLK_MUTE, false},
            {SDLK_VOLUMEUP, false},
            {SDLK_VOLUMEDOWN, false},
            {SDLK_KP_COMMA, false},
            {SDLK_KP_EQUALSAS400, false},
            {SDLK_ALTERASE, false},
            {SDLK_SYSREQ, false},
            {SDLK_CANCEL, false},
            {SDLK_CLEAR, false},
            {SDLK_PRIOR, false},
            {SDLK_RETURN2, false},
            {SDLK_SEPARATOR, false},
            {SDLK_OUT, false},
            {SDLK_OPER, false},
            {SDLK_CLEARAGAIN, false},
            {SDLK_CRSEL, false},
            {SDLK_EXSEL, false},
            {SDLK_KP_00, false},
            {SDLK_KP_000, false},
            {SDLK_THOUSANDSSEPARATOR, false},
            {SDLK_DECIMALSEPARATOR, false},
            {SDLK_CURRENCYUNIT, false},
            {SDLK_CURRENCYSUBUNIT, false},
            {SDLK_KP_LEFTPAREN, false},
            {SDLK_KP_RIGHTPAREN, false},
            {SDLK_KP_LEFTBRACE, false},
            {SDLK_KP_RIGHTBRACE, false},
            {SDLK_KP_TAB, false},
            {SDLK_KP_BACKSPACE, false},
            {SDLK_KP_A, false},
            {SDLK_KP_B, false},
            {SDLK_KP_C, false},
            {SDLK_KP_D, false},
            {SDLK_KP_E, false},
            {SDLK_KP_F, false},
            {SDLK_KP_XOR, false},
            {SDLK_KP_POWER, false},
            {SDLK_KP_PERCENT, false},
            {SDLK_KP_LESS, false},
            {SDLK_KP_GREATER, false},
            {SDLK_KP_AMPERSAND, false},
            {SDLK_KP_DBLAMPERSAND, false},
            {SDLK_KP_VERTICALBAR, false},
            {SDLK_KP_DBLVERTICALBAR, false},
            {SDLK_KP_COLON, false},
            {SDLK_KP_HASH, false},
            {SDLK_KP_SPACE, false},
            {SDLK_KP_AT, false},
            {SDLK_KP_EXCLAM, false},
            {SDLK_KP_MEMSTORE, false},
            {SDLK_KP_MEMRECALL, false},
            {SDLK_KP_MEMCLEAR, false},
            {SDLK_KP_MEMADD, false},
            {SDLK_KP_MEMSUBTRACT, false},
            {SDLK_KP_MEMMULTIPLY, false},
            {SDLK_KP_MEMDIVIDE, false},
            {SDLK_KP_PLUSMINUS, false},
            {SDLK_KP_CLEAR, false},
            {SDLK_KP_CLEARENTRY, false},
            {SDLK_KP_BINARY, false},
            {SDLK_KP_OCTAL, false},
            {SDLK_KP_DECIMAL, false},
            {SDLK_KP_HEXADECIMAL, false},
            {SDLK_LCTRL, false},
            {SDLK_LSHIFT, false},
            {SDLK_LALT, false},
            {SDLK_LGUI, false},
            {SDLK_RCTRL, false},
            {SDLK_RSHIFT, false},
            {SDLK_RALT, false},
            {SDLK_RGUI, false},
            {SDLK_MODE, false},
            {SDLK_AUDIONEXT, false},
            {SDLK_AUDIOPREV, false},
            {SDLK_AUDIOSTOP, false},
            {SDLK_AUDIOPLAY, false},
            {SDLK_AUDIOMUTE, false},
            {SDLK_MEDIASELECT, false},
            {SDLK_WWW, false},
            {SDLK_MAIL, false},
            {SDLK_CALCULATOR, false},
            {SDLK_COMPUTER, false},
            {SDLK_AC_SEARCH, false},
            {SDLK_AC_HOME, false},
            {SDLK_AC_BACK, false},
            {SDLK_AC_FORWARD, false},
            {SDLK_AC_STOP, false},
            {SDLK_AC_REFRESH, false},
            {SDLK_AC_BOOKMARKS, false},
            {SDLK_BRIGHTNESSDOWN, false},
            {SDLK_BRIGHTNESSUP, false},
            {SDLK_DISPLAYSWITCH, false},
            {SDLK_KBDILLUMTOGGLE, false},
            {SDLK_KBDILLUMDOWN, false},
            {SDLK_KBDILLUMUP, false},
            {SDLK_EJECT, false},
            {SDLK_SLEEP, false}
        };

    sort(event_container.begin(), event_container.end());
    sort(curr_pressed_keys.begin(), curr_pressed_keys.end());

}

int event_mgr::get_event_container_pos(int p_event_type){
    int i=0,c,f=event_container.size()-1;

    while(i<=f){
        c=(i+f)/2;
        if(event_container[c].event_type==p_event_type){
            return c;
        }
        if(event_container[c].event_type<p_event_type){
            i=c+1;
        }else{
            f=c-1;
        }
    }

    return -1;
}

int event_mgr::get_curr_pressed_keys_pos(int p_vkeycode){
    int i=0,c,f=curr_pressed_keys.size()-1;

    while(i<=f){
        c=(i+f)/2;
        if(curr_pressed_keys[c].keysym==p_vkeycode){
            return c;
        }
        if(curr_pressed_keys[c].keysym<p_vkeycode){
            i=c+1;
        }else{
            f=c-1;
        }
    }

    return -1;
}

void event_mgr::manage_keypress(int p_ev_cont_pos){
    int pos=get_curr_pressed_keys_pos(event_container[p_ev_cont_pos].event.key.keysym.sym);

    if(event_container[p_ev_cont_pos].event_type==SDL_KEYDOWN){
        curr_pressed_keys[pos].pressed=true;
    }else if(event_container[p_ev_cont_pos].event_type==SDL_KEYUP){
        curr_pressed_keys[pos].pressed=false;
    }
}

void event_mgr::update(){
    for(list<int>::iterator it=to_clear.begin(); it!=to_clear.end(); it++){
        event_container[*it].status=false;
        event_container[*it].event=SDL_Event();
    }
    to_clear.clear();

    while(SDL_PollEvent(&event)){
        int pos=get_event_container_pos(event.type);

        event_container[pos].status=true;
        event_container[pos].event=event;

        to_clear.push_back(pos);

        if(event.type==SDL_KEYUP||event.type==SDL_KEYDOWN){
            manage_keypress(pos);
        }
    }
}

ev_ret_type event_mgr::get_event(int p_event_id){
    int pos=get_event_container_pos(p_event_id);
    
    if(event_container[pos].status==false){
        return {false, event_container[0].event};
    }
    
    return {true, event_container[pos].event};
}

bool event_mgr::iskeypress(int p_vkeycode){
    return curr_pressed_keys[get_curr_pressed_keys_pos(p_vkeycode)].pressed;
}