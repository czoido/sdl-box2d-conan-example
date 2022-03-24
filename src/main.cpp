#include <iomanip>
#include <Box2D/Box2D.h>
#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <memory>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int PIX2METR = 32;

const b2Vec2& screen2world(const b2Vec2& screen_point) {
  static b2Vec2 world_point;
  world_point.x = screen_point.x/(float)PIX2METR;
  world_point.y = SCREEN_HEIGHT/(float)PIX2METR - screen_point.y/(float)PIX2METR;
  return world_point;
}

const b2Vec2& world2screen(const b2Vec2& world_point) {
  static b2Vec2 screen_point;
  screen_point.x = world_point.x*(float)PIX2METR;
  screen_point.y = (SCREEN_HEIGHT - world_point.y*(float)PIX2METR);
  return screen_point;
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    SDL_Window *window = SDL_CreateWindow("Basic Game Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    

    SDL_Event event;

    // creation of a b2World object. b2World is the physics hub that manages memory, objects, 
    // and simulation. You can allocate the physics world on the stack, heap, or data section.
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    
    // Create a dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(5.0, 10.0);
    
    b2Body* body = world.CreateBody(&bodyDef);

    // create and attach a polygon shape using a fixture definition. First we create a box shape:
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.1f, 0.1f);

    // Next we create a fixture definition using the box. Notice that we set density to 1. 
    // The default density is zero. Also, the friction on the shape is set to 0.3.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.01f;

    // Using the fixture definition we can now create the fixture. This automatically updates the mass of the body.
    // You can add as many fixtures as you like to a body. Each one contributes to the total mass.
    body->CreateFixture(&fixtureDef);

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    bool quit = false;
    double elapsedTime = 1.0/60.0;
    while(!quit) {
        uint32_t startTime = SDL_GetTicks();
        while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                body->ApplyForce(b2Vec2(0,100.0), body->GetPosition(), true);
            }
        }
        world.Step(elapsedTime, velocityIterations, positionIterations);
        b2Vec2 world_position = body->GetPosition();
        b2Vec2 screen_position = world2screen(world_position);
        //Clear screen
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
        SDL_RenderClear( renderer );

        //Render red filled quad
        SDL_Rect fillRect = { screen_position.x, screen_position.y, SCREEN_WIDTH/20, SCREEN_WIDTH/20 };
        SDL_SetRenderDrawColor( renderer, 255, 0, 255, 255);		
        SDL_RenderFillRect( renderer, &fillRect );

        //Update screen
        SDL_RenderPresent( renderer );
        uint32_t currTime = SDL_GetTicks();
        elapsedTime = (currTime - startTime) / 1000.0; // Convert to seconds.
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}