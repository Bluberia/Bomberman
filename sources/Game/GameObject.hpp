#ifndef INDIE_STUDIO_ACUBE_HPP
#define INDIE_STUDIO_ACUBE_HPP

#include <vector>
#include <memory>
#include "irrlicht.hpp"
#include "Vector3D.hpp"
#include "AssetManager.hpp"

class GameObject {
public:
    typedef enum {
        DEFAULT,
        BOMB,
        PLAYER,
        UNBREAKABLE,
        BREAKABLE,
        EXPLOSION,
        POWERUP
    } CubeType;

public:
    explicit GameObject(double lifespan = -1, irr::scene::ISceneNode * irrNode = nullptr, bool isSolid = false, bool isMovable = false);
    virtual ~GameObject();

    virtual void update(std::vector<std::shared_ptr<GameObject>> &cubes);
    virtual void onDeath(std::vector<std::shared_ptr<GameObject>> &cubes);
    void addCollision();
    void setNode(irr::scene::ISceneNode *irrNode);
    CubeType getType() const;
    std::shared_ptr<GameObject> isColliding(std::vector<std::shared_ptr<GameObject>>& world);
    irr::scene::ISceneNode* getNode() const;
    bool isSolid() const;
    const irr::core::vector3df &getPosition() const;
    virtual void setPosition(const irr::core::vector3df &position);
    const irr::core::vector3df &getScale() const;
    void setScale(const irr::core::vector3df &scale);
    const irr::core::vector3df &getRotation() const;
    void setRotation(const irr::core::vector3df &rotation);
    virtual void onCollide() {};
    virtual void onOverlap(GameObject& player) {};
    void debug();

    bool isDeleted();
    void setDeleted(bool del);

protected:
    void defaultTransform();
protected:
    double _lifespan;
    bool solid;
    bool isMovable;
    bool _toDelete;
    irr::core::vector3df _defaultPosition;
    irr::core::vector3df _defaultScale;
    irr::core::vector3df _defaultRotation;
    CubeType _type;
private:
    irr::scene::ISceneNode* _irrNode;
};

#else

class GameObject;

#endif
