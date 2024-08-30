#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

#include<iostream>
#include<fstream>
#include<vector>
#include<thread>
#include<chrono>
#include<string>

#include<windows.h>
#include<unistd.h>
#include<mmdeviceapi.h>
#include<endpointvolume.h>
#include<audioclient.h>
#include<winternl.h>

#include "rendering/render_window.hpp"
#include "base_elements/entity.hpp"
#include "rendering/fontcache.hpp"
#include "rendering/event_mgr.hpp"
#include "base_elements/gui_element.hpp"
#include "gui_elements/gui_button.hpp"

#include "game_elements/game.hpp"

#include "game_elements/penalties.hpp"

using namespace std::chrono_literals;

guess_or_die::guess_or_die(render_window& p_game_win, TTF_Font* p_main_font, TTF_Font* p_second_font)
    :   game_win(p_game_win), 
        main_font(p_main_font),
        second_font(p_second_font), 
        ts(p_game_win), es(p_game_win), 
        current_phase(0), 
        fc_ts_1(p_main_font,(SDL_Color){0,0,0,255}, game_win.get_renderer()), 
        fc_ts_2(p_second_font,(SDL_Color){0,0,0,255}, game_win.get_renderer()),
        level1(NULL), level2(NULL), level3(NULL), level4(NULL), level5(NULL),
        level6(NULL), level7(NULL), level8(NULL),

        congrats_1_ts(p_game_win), congrats_2_ts(p_game_win), congrats_3_ts(p_game_win),
        congrats_4_ts(p_game_win), congrats_5_ts(p_game_win), congrats_6_ts(p_game_win),
        congrats_7_ts(p_game_win), congrats_8_ts(p_game_win),

        penalty_1_ts(p_game_win), penalty_2_ts(p_game_win), penalty_3_ts(p_game_win), 
        penalty_4_ts(p_game_win), penalty_5_ts(p_game_win), penalty_6_ts(p_game_win), 
        penalty_7_ts(p_game_win), penalty_8_ts(p_game_win)
        
{
    srand(time(NULL));

    bg_neutral=game_win.load_texture("../res/gfx/bg1.png");
    bg_good=game_win.load_texture("../res/gfx/bg2.png");
    bg_error=game_win.load_texture("../res/gfx/bg3.png");

    button_normal=game_win.load_texture("../res/gfx/button_normal.png");
    button_active=game_win.load_texture("../res/gfx/button_active.png");

    title_splash=game_win.load_texture("../res/gfx/splash.png");

    level1=load_level("../res/levels/level1");
    level2=load_level("../res/levels/level2");
    level3=load_level("../res/levels/level3");
    level4=load_level("../res/levels/level4");
    level5=load_level("../res/levels/level5");
    level6=load_level("../res/levels/level6");
    level7=load_level("../res/levels/level7");
    level8=load_level("../res/levels/level8");

    ts.add_slide(ts_slide(bg_neutral, title_splash, game_win.get_win_width()/2-game_win.get_texture_width(title_splash)/2, game_win.get_win_height()/2-game_win.get_texture_height(title_splash)/2,"", 0,0, NULL));
    ts.add_slide(ts_slide(bg_neutral, NULL, 0,0,"Welcome to the\nGuess or die game!\n\nYou will need to\npay attention, however,\nas errors will be\ncostly... Good luck!\n\nNote: you might see\nlots of errors, but\nthey are actually\nharmless.", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));

    congrats_1_ts.add_slide(ts_slide(bg_good, NULL, 0,0,"Excellent!", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    congrats_2_ts.add_slide(ts_slide(bg_good, NULL, 0,0,"Fantastic!", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    congrats_3_ts.add_slide(ts_slide(bg_good, NULL, 0,0,"Well done!", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    congrats_4_ts.add_slide(ts_slide(bg_good, NULL, 0,0,"Superb!", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    congrats_5_ts.add_slide(ts_slide(bg_good, NULL, 0,0,"Brilliant!", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    congrats_6_ts.add_slide(ts_slide(bg_good, NULL, 0,0,"Outstanding!", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    congrats_7_ts.add_slide(ts_slide(bg_good, NULL, 0,0,"Amazing!", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    congrats_8_ts.add_slide(ts_slide(bg_good, NULL, 0,0,"Great job!", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    
    penalty_1_ts.add_slide(ts_slide(bg_error, NULL, 0,0,"What happened to\nthe desktop?", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    penalty_2_ts.add_slide(ts_slide(bg_error, NULL, 0,0,"Watch out for \nbad people...", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    penalty_3_ts.add_slide(ts_slide(bg_error, NULL, 0,0,"Ya doin' all this?", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    penalty_4_ts.add_slide(ts_slide(bg_error, NULL, 0,0,"Lower that tone!\nDon't you hear\nyour volume is\na bit too high?", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    penalty_5_ts.add_slide(ts_slide(bg_error, NULL, 0,0,"Keyboard? Mouse?\nNever heard of them...", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    penalty_6_ts.add_slide(ts_slide(bg_error, NULL, 0,0,"Random DLLs in C:\\?\nThat's weird...", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    penalty_7_ts.add_slide(ts_slide(bg_error, NULL, 0,0,"Look at the time,\ndude?", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
    penalty_8_ts.add_slide(ts_slide(bg_error, NULL, 0,0,"You really messed up...\n\nTime.\nTo.\nDie.", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));

    es.add_slide(ts_slide(bg_neutral, NULL, 0,0,"Thanks for playing!\n\nCheck out the source at\ngithub.com/zac06", game_win.get_win_width()/2, game_win.get_win_height()/2, &fc_ts_1));
}

guess_or_die::~guess_or_die(){
    if(level1!=NULL){
        delete level1;
    }
    if(level2!=NULL){
        delete level2;
    }
    if(level3!=NULL){
        delete level3;
    }
    if(level4!=NULL){
        delete level4;
    }
    if(level5!=NULL){
        delete level5;
    }
    if(level6!=NULL){
        delete level6;
    }
    if(level7!=NULL){
        delete level7;
    }
    if(level8!=NULL){
        delete level8;
    }

}

void guess_or_die::render(){
    switch(current_phase){
        case PHASE_TITLE_SCREEN:{
            bool ret=ts.update_render();
            if(ret){
                es.reset();
                current_phase++;
            }
            
            break;
        }

        case PHASE_LEVEL_1:{
            if(level1==NULL){
                break;
            }

            int ret=level1->update_render();
            if(ret==-1){
                current_phase=PHASE_PENALTY_1;
            }else if(ret==1){
                current_phase=PHASE_CONGRATS_1;
            }
            break;
        }
        case PHASE_LEVEL_2:{
            if(level2==NULL){
                break;
            }

            int ret=level2->update_render();
            if(ret==-1){
                current_phase=PHASE_PENALTY_2;
            }else if(ret==1){
                current_phase=PHASE_CONGRATS_2;
            }
            break;
        }
        case PHASE_LEVEL_3:{
            if(level3==NULL){
                break;
            }

            int ret=level3->update_render();
            if(ret==-1){
                current_phase=PHASE_PENALTY_3;
            }else if(ret==1){
                current_phase=PHASE_CONGRATS_3;
            }
            break;
        }
        case PHASE_LEVEL_4:{
            if(level4==NULL){
                break;
            }

            int ret=level4->update_render();
            if(ret==-1){
                current_phase=PHASE_PENALTY_4;
            }else if(ret==1){
                current_phase=PHASE_CONGRATS_4;
            }
            break;
        }
        case PHASE_LEVEL_5:{
            if(level5==NULL){
                break;
            }

            int ret=level5->update_render();
            if(ret==-1){
                current_phase=PHASE_PENALTY_5;
            }else if(ret==1){
                current_phase=PHASE_CONGRATS_5;
            }
            break;
        }
        case PHASE_LEVEL_6:{
            if(level6==NULL){
                break;
            }

            int ret=level6->update_render();
            if(ret==-1){
                current_phase=PHASE_PENALTY_6;
            }else if(ret==1){
                current_phase=PHASE_CONGRATS_6;
            }
            break;
        }
        case PHASE_LEVEL_7:{
            if(level7==NULL){
                break;
            }

            int ret=level7->update_render();
            if(ret==-1){
                current_phase=PHASE_PENALTY_7;
            }else if(ret==1){
                current_phase=PHASE_CONGRATS_7;
            }
            break;
        }
        case PHASE_LEVEL_8:{
            if(level8==NULL){
                break;
            }

            int ret=level8->update_render();
            if(ret==-1){
                current_phase=PHASE_PENALTY_8;
            }else if(ret==1){
                current_phase=PHASE_CONGRATS_8;
            }
            break;
        }

        case PHASE_CONGRATS_1:{
            bool ret=congrats_1_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_2;
            }
            break;
        }
        case PHASE_CONGRATS_2:{
            bool ret=congrats_2_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_3;
            }
            break;
        }
        case PHASE_CONGRATS_3:{
            bool ret=congrats_3_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_4;
            }
            break;
        }
        case PHASE_CONGRATS_4:{
            bool ret=congrats_4_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_5;
            }
            break;
        }
        case PHASE_CONGRATS_5:{
            bool ret=congrats_5_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_6;
            }
            break;
        }
        case PHASE_CONGRATS_6:{
            bool ret=congrats_6_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_7;
            }
            break;
        }
        case PHASE_CONGRATS_7:{
            bool ret=congrats_7_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_8;
            }
            break;
        }
        case PHASE_CONGRATS_8:{
            bool ret=congrats_8_ts.update_render();
            if(ret){
                current_phase=PHASE_END_SCREEN;
            }
            break;
        }

        case PHASE_PENALTY_1:{
            if(!penalty_1_ts.firstview){
                penalty_1();
            }

            bool ret=penalty_1_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_2;
            }
            break;
        }
        case PHASE_PENALTY_2:{
            if(!penalty_2_ts.firstview){
                penalty_2();
            }

            bool ret=penalty_2_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_3;
            }
            break;
        }
        case PHASE_PENALTY_3:{
            if(!penalty_3_ts.firstview){
                penalty_3();
            }
            
            bool ret=penalty_3_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_4;
            }
            break;
        }
        case PHASE_PENALTY_4:{
            if(!penalty_4_ts.firstview){
                penalty_4();
            }
            
            bool ret=penalty_4_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_5;
            }
            break;
        }
        case PHASE_PENALTY_5:{
            if(!penalty_5_ts.firstview){
                penalty_5();
            }
            
            bool ret=penalty_5_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_6;
            }
            break;
        }
        case PHASE_PENALTY_6:{
            if(!penalty_6_ts.firstview){
                penalty_6();
            }
            
            bool ret=penalty_6_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_7;
            }
            break;
        }
        case PHASE_PENALTY_7:{
            if(!penalty_7_ts.firstview){
                penalty_7();
            }
            
            bool ret=penalty_7_ts.update_render();
            if(ret){
                current_phase=PHASE_LEVEL_8;
            }
            break;
        }
        case PHASE_PENALTY_8:{
            if(!penalty_8_ts.firstview){
                penalty_8();
            }
            
            bool ret=penalty_8_ts.update_render();
            if(ret){
                current_phase=PHASE_END_SCREEN;
            }
            break;
        }

        case PHASE_END_SCREEN:{
            bool ret=es.update_render();
            if(ret){
                //current_phase=PHASE_TITLE_SCREEN;
                es.reset();
            }
            break;
        }
    }
}

level* guess_or_die::load_level(std::string p_file_name){
    level* retval;
    std::ifstream fin(p_file_name);

    if(!fin.good()){
        return NULL;
    }

    std::vector<std::string> questions;
    std::vector<std::string> answs_1;
    std::vector<std::string> answs_2;
    std::vector<std::string> answs_3;
    std::vector<std::string> answs_4;
    std::vector<int> correct_answers;
    
    int rand_quest;
    
    while(!fin.eof()){
        questions.push_back(read_until_whiteline(fin));
        answs_1.push_back(read_until_whiteline(fin));
        answs_2.push_back(read_until_whiteline(fin));
        answs_3.push_back(read_until_whiteline(fin));
        answs_4.push_back(read_until_whiteline(fin));
        correct_answers.push_back(atoi(read_until_whiteline(fin).c_str()));
    }

    rand_quest=rand()%questions.size();
    retval=new level(game_win, fc_ts_1, fc_ts_2,    correct_answers[rand_quest], 
                                                    answs_1[rand_quest],
                                                    answs_2[rand_quest],
                                                    answs_3[rand_quest],
                                                    answs_4[rand_quest],
                                                    questions[rand_quest],
                                                    button_normal,
                                                    button_active,
                                                    bg_neutral);

    fin.close();

    return retval;
}

std::string guess_or_die::read_until_whiteline(ifstream& fin){
    std::string tmp_string="";
    std::string retval;

    getline(fin, tmp_string);
    while(!fin.eof()){
        if(tmp_string!=""){
            retval+=tmp_string+"\n";
        }else{
            retval.pop_back();
            return retval;
        }

        getline(fin, tmp_string);
    }

    if(tmp_string!=""){
        retval+=tmp_string+"\n";
    }
    if(retval!=""){
        retval.pop_back();
    }
    return retval;
}

void guess_or_die::penalty_1(){
    std::string tmp=std::string(to_string(rand()%256)+" "+to_string(rand()%256)+" "+to_string(rand()%256));

    reg_set_key(HKEY_CURRENT_USER, "Control Panel\\Colors", "Background", tmp);
    reg_set_key(HKEY_CURRENT_USER, "Control Panel\\Desktop", "WallPaper", "");
    
}

void guess_or_die::penalty_2(){
    std::thread th_show_window(display_windows);
    th_show_window.detach();
}

void guess_or_die::penalty_3(){
    std::thread th_spam_window(spam_cmd);
    th_spam_window.detach();
}

void guess_or_die::penalty_4(){
    std::thread th_spam_volume(spam_volume);
    th_spam_volume.detach();
}

void guess_or_die::penalty_5(){
    std::thread th_block(block_inputs);
    th_block.detach();
}

void guess_or_die::penalty_6(){
    std::thread th_make_file(special_file_make);
    th_make_file.detach();
}

void guess_or_die::penalty_7(){
    std::thread th_set_time(set_time);
    th_set_time.detach();
}

void guess_or_die::penalty_8(){
    std::thread th_crash_sys(crash_system);
    th_crash_sys.detach();
}
