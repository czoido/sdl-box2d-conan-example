#include "World.hpp"
#include "Game.hpp"

World::World() {
    // Create the ground body
    b2BodyDef groundBodyDef;
    b2Vec2 world_position = b2Vec2(0,-0.5);
    groundBodyDef.position.Set(world_position.x, world_position.y);
    b2Body* groundBody = _world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 0.5f);
    groundBody->CreateFixture(&groundBox, 0.0f);
}


void World::update(float elapsedTime) {
    _world->Step(elapsedTime, _velocityIterations, _positionIterations);
}
