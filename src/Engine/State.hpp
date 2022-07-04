#pragma once
#include "raylib.h"
#include "Renderer\renderer.hpp"
class Engine;
class State{
public:
virtual void init(Engine* engine) = 0;
virtual void deinit(Engine* Engine){};
virtual void handle_input(Engine* engine) = 0;
virtual void update(Engine* engine,float delta) = 0;
virtual void render(Renderer &renderer,Engine* engine) = 0;
virtual ~State(){};
};
