#include "Engine.hpp"
Engine::Engine() : renderer(80, 45, "terminal.png", 12)
{
    SetExitKey(0);
    SetTargetFPS(60);
}

Engine::~Engine()
{
    current_state->deinit(this);
    delete current_state;
}

void Engine::handle_events()
{
    current_state->handle_input(this);
}

void Engine::update()
{
    current_state->update(this,GetFrameTime());
}

void Engine::render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    current_state->render(renderer, this);
    EndDrawing();
}

void Engine::change_state(State *state)
{
    if(current_state != nullptr){
        current_state->deinit(this);
        delete current_state;
    }

    current_state = state;
    current_state->init(this);
}
