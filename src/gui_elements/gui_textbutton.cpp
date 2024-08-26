#include "gui_elements/gui_textbutton.hpp"


gui_textbutton::gui_textbutton(SDL_Texture* p_tex_normal, SDL_Point p_coords, render_window& p_win, fontcache& p_fc, std::string p_txt, int p_txt_x, int p_txt_y, bool center)
    :   win(p_win),
        fc(p_fc),

        gui_button( build_text_texture(p_tex_normal, p_win, p_fc, p_txt, p_txt_x, p_txt_y, center), 
                    p_coords)
        
{
}

gui_textbutton::gui_textbutton(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_active, SDL_Point p_coords, render_window& p_win, fontcache& p_fc, std::string p_txt, int p_txt_x, int p_txt_y, bool center)
    :   win(p_win),
        fc(p_fc),

        gui_button( build_text_texture(p_tex_normal, p_win, p_fc, p_txt, p_txt_x, p_txt_y, center), 
                    build_text_texture(p_tex_active, p_win, p_fc, p_txt, p_txt_x, p_txt_y, center),
                    p_coords)
        
{
}

gui_textbutton::gui_textbutton(SDL_Texture* p_tex_normal, SDL_Texture* p_tex_hover, SDL_Texture* p_tex_active, SDL_Texture* p_tex_disabled, SDL_Point p_coords, render_window& p_win, fontcache& p_fc, std::string p_txt, int p_txt_x, int p_txt_y, bool center)
    :   win(p_win),
        fc(p_fc),

        gui_button( build_text_texture(p_tex_normal, p_win, p_fc, p_txt, p_txt_x, p_txt_y, center), 
                    build_text_texture(p_tex_hover, p_win, p_fc, p_txt, p_txt_x, p_txt_y, center), 
                    build_text_texture(p_tex_active, p_win, p_fc, p_txt, p_txt_x, p_txt_y, center), 
                    build_text_texture(p_tex_disabled, p_win, p_fc, p_txt, p_txt_x, p_txt_y, center), 
                    p_coords)
        
{
}

SDL_Texture* gui_textbutton::build_text_texture(SDL_Texture* p_base, render_window& p_win, fontcache& p_fc, std::string p_txt, int p_txt_x, int p_txt_y, bool center){
    SDL_Texture* aux=SDL_CreateTexture(p_win.get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, p_win.get_texture_width(p_base), p_win.get_texture_height(p_base));
    
    SDL_SetTextureBlendMode(aux, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(p_win.get_renderer(), aux);

    p_win.render_texture(p_base, 0,0);
    p_win.render_text_fc(p_fc, p_txt, p_txt_x, p_txt_y, center);
    //cerr<<p_txt_x<<";"<<p_txt_y<<"\n";

    p_win.append_loaded_tex(aux);

    SDL_SetRenderTarget(p_win.get_renderer(), NULL);

    return aux;
}