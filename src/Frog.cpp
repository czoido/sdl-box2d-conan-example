#include "Frog.hpp"
#include "World.hpp"
#include "Game.hpp"
#include <iostream>
#include <math.h>



Frog::Frog(const b2Vec2& position, const World& world)
{
    // Create a dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    _body = world.getWorld()->CreateBody(&bodyDef);

    // Next we create a fixture definition using the box. Notice that we set density to 1.
    // The default density is zero. Also, the friction on the shape is set to 0.3.
    b2FixtureDef fixtureDef;
    // create and attach a polygon shape using a fixture definition. First we create a box shape:
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(frog_dimensions.x,
                        frog_dimensions.y);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = _density;
    fixtureDef.friction = _friction;
    fixtureDef.restitution = _restitution;
    // Using the fixture definition we can now create the fixture. This automatically updates the mass of the body.
    // You can add as many fixtures as you like to a body. Each one contributes to the total mass.
    _body->CreateFixture(&fixtureDef);

    b2Vec2 a = Game::world2screen(frog_dimensions);
    b2Vec2 b = Game::world2screen(b2Vec2(0,0));
    b2Vec2 dim = b - a;
    frog_dimensions_world = b2Vec2(dim.x, dim.y);
    
}

void Frog::impulse() {
    _body->ApplyForce(b2Vec2(0,100.0), _body->GetPosition(), true);
}

SDL_Texture* Frog::initTexture(const std::string& name, SDL_Renderer *renderer) {
    SDL_Surface* tmp_image;
    tmp_image = IMG_Load(name.c_str());
    if(!tmp_image) {
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmp_image);
    SDL_FreeSurface(tmp_image);
    return texture;
}

void Frog::render(SDL_Renderer *renderer, float color) {
    //Render filled quad


    b2Vec2 frog_world_position = getPosition();
    b2Vec2 frog_screen_position = Game::world2screen(frog_world_position);
    SDL_Rect frogRect = { static_cast<int>(frog_screen_position.x),
                          static_cast<int>(frog_screen_position.y),
                          static_cast<int>(fabs(frog_dimensions_world.x)),
                          static_cast<int>(fabs(frog_dimensions_world.y))};

    if(!_texture) {
        _texture = initTexture("frog.png", renderer);
    }
    else {
        SDL_RenderCopyEx(renderer, _texture, NULL, &frogRect, color, NULL, SDL_FLIP_NONE);
    }
    
    //SDL_RenderFillRect( renderer, &frogRect );
}

void Frog::update(float delta) {
    _timeAlive += delta;
}
