#ifndef Frog_hpp
#define Frog_hpp

#include <memory>
#include <string>
#include <stdio.h>
#include <box2d/box2d.h>
#include <SDL.h>
#include <SDL_image.h>

class World;

class Frog {

public:
    Frog(const b2Vec2& position, const World& world);
    Frog(const Frog&);
    Frog& operator=(const Frog&);
    void update(float delta);
    void impulse();
    b2Vec2 getPosition() const {return _body->GetPosition();};
    const b2Body* getBody() {return _body;};
    void render(SDL_Renderer *renderer, float color);
    SDL_Texture* initTexture(const std::string& name, SDL_Renderer *renderer);
private:
    const float _density{0.01f};
    const float _friction{0.01f};
    const float _restitution{0.5};
    const b2Vec2 frog_dimensions{3, 4};
    b2Vec2 frog_dimensions_world;
    float _timeAlive {0};
    b2Body* _body;
    SDL_Texture* _texture{nullptr};
};

#endif /* Frog_hpp */
