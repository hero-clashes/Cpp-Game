#include "Main_Menu.hpp"
#include "Engine/Engine.hpp"
void Main_Menu::init(Engine* Engine)
{

 
}

void Main_Menu::deinit(Engine* Engine)
{

}

void Main_Menu::handle_input(Engine* engine)
{

}

void Main_Menu::update(Engine* engine,float delta)
{
    
}

void Main_Menu::render(Renderer &renderer,Engine* engine)
{
    for (size_t i = 0; i < title.size(); i++)
    {
        renderer.render_text_pro(12,4+i,title[i],0.4f,0,static_cast<int>(-(i*12*0.4f)),&colors[(loop_num+i)%colors.size()],nullptr);
        
    }
    if(fmod(GetTime(),0.1)>0.05){
        if(std::numeric_limits<unsigned int>::max() != loop_num)    
            loop_num++;
        else {
            loop_num = 0;
        }
    };
}
