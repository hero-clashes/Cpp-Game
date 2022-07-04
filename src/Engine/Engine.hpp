#pragma once
#include "raylib.h"
#include "Renderer/renderer.hpp"
#include "State.hpp"

class Engine{
    public:
    Engine();
    ~Engine();
    void handle_events();
    void update();
    void render();
    void change_state(State *state);
    Renderer renderer;
    bool Should_Exit = false;
    private:
    State *current_state = nullptr;
};