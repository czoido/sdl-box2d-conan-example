#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <memory>
#include <box2d/box2d.h>


class World {

    const int32 _velocityIterations {6};
    const int32 _positionIterations {2};
    const b2Vec2 _gravity{0.0f, -10.0f};

    std::unique_ptr<b2World> _world{std::make_unique<b2World>(_gravity)};

public:

    World();
    ~World() = default;
    void update(float elapsedTime);
    const std::unique_ptr<b2World>& getWorld() const {return _world;};
    
};

#endif /* World_hpp */
