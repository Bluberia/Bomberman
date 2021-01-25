#include "MapManager.hpp"
#include "APlayer.hpp"
#include <cstdlib>
#include <algorithm>
#include "GameObject.hpp"
#include "IrrlichtDevice.hpp"
#include "Exception.hpp"
#include "Model.hpp"

GameObject::GameObject(double lifespan, irr::scene::ISceneNode* irrNode, bool isSolid, bool isMovable) :
    _lifespan(lifespan),
    _irrNode(irrNode),
    solid(isSolid),
    isMovable(isMovable),
    _type(DEFAULT),
    _toDelete(false)
{
}

irr::scene::ISceneNode* GameObject::getNode() const
{
    if (_irrNode == nullptr)
        throw(IndieException("Error: irrlicht node is null", std::string(__FILE__) + std::to_string(__LINE__)));
    return _irrNode;
}

const irr::core::vector3df& GameObject::getPosition() const
{
    return getNode()->getPosition();
}

const irr::core::vector3df& GameObject::getRotation() const
{
    return getNode()->getRotation();
}

const irr::core::vector3df& GameObject::getScale() const
{
    return getNode()->getScale();
}

void GameObject::setPosition(const irr::core::vector3df& position)
{
    getNode()->setPosition(position);
}

void GameObject::setRotation(const irr::core::vector3df& position)
{
    getNode()->setRotation(position);
}

void GameObject::setScale(const irr::core::vector3df& position)
{
    getNode()->setScale(position);
}

GameObject::~GameObject() {
    if (_irrNode) {
        auto* meta = IrrlichtDevice::getInstance().getMetaSelector();
        if (meta) {
            auto* selector = getNode()->getTriangleSelector();
            meta->removeTriangleSelector(selector);
        }
        getNode()->removeAnimators();
        getNode()->removeAll();
        getNode()->remove();
    }
}

bool GameObject::isSolid() const
{
    return solid;
}

void GameObject::update(std::vector<std::shared_ptr<GameObject>>& cubes) {
    if (_lifespan > 0)
        _lifespan -= 5 * IrrlichtDevice::getInstance().getFrameDeltaTime();
    if (_lifespan < 0 && _lifespan != -1)
        onDeath(cubes);
}

void GameObject::setNode(irr::scene::ISceneNode* irrNode)
{
    _irrNode = irrNode;
}

void GameObject::onDeath(std::vector<std::shared_ptr<GameObject>>& cubes)
{
    setDeleted(true);
}

void GameObject::addCollision()
{
    irr::scene::ITriangleSelector* selector = IrrlichtDevice::getInstance().getManager()->createTriangleSelectorFromBoundingBox(getNode());

    if (selector == nullptr)
        throw(IndieException("Error : Collider : Failed to create selector", std::string(__FILE__) + std::to_string(__LINE__)));
    getNode()->setTriangleSelector(selector);
    IrrlichtDevice::getInstance().getMetaSelector()->addTriangleSelector(selector);

    const irr::core::aabbox3d<irr::f32>& box = getNode()->getBoundingBox();
    irr::core::vector3df radius = box.MaxEdge - box.getCenter();
    irr::scene::ISceneNodeAnimatorCollisionResponse* anim = IrrlichtDevice::getInstance().getManager()->createCollisionResponseAnimator(IrrlichtDevice::getInstance().getMetaSelector(), getNode(), radius, { 0, 0, 0 }, { 0, 0, 0 }, 0);
    if (anim == nullptr)
        throw(IndieException("Error : Collider : Failed to create animator", std::string(__FILE__) + std::to_string(__LINE__)));
    getNode()->addAnimator(anim);
}

std::shared_ptr<GameObject> GameObject::isColliding(std::vector<std::shared_ptr<GameObject>>& world)
{
    auto* collisionManager = IrrlichtDevice::getInstance().getManager()->getSceneCollisionManager();
    irr::core::line3df ray;
    auto position = getNode()->getPosition();
    auto rotation = getNode()->getRotation();
    auto *edges = new irr::core::vector3d<irr::f32>[8];
    irr::scene::ISceneNode* outNode = nullptr;
    irr::video::SMaterial m;
    irr::core::vector3df outCollisionPoint;
    irr::core::triangle3df outTriangle;
    irr::s32 idBitMask = 0;
    irr::scene::ISceneNode* collisionRootNode = 0;

    getNode()->getTransformedBoundingBox().getEdges(edges);

    irr::f32 height = edges[1].Y - edges[0].Y;
    irr::f32 width = edges[5].X - edges[1].X;
    delete[] edges;
    ray.start = getNode()->getTransformedBoundingBox().getCenter();
    ray.start.Y -= height / 2.5;
    float ray_len = 2.5;

    switch (static_cast<int>(rotation.Y))
    {
    case 0:
        ray.start.Z -= width / 1.5;
        ray.end = ray.start;
        ray.end.Z -= ray_len;
        break;
    case 90:
        ray.start.X -= width / 1.5;
        ray.end = ray.start;
        ray.end.X -= ray_len;
        break;
    case -90:
        ray.start.X += width / 1.5;
        ray.end = ray.start;
        ray.end.X += ray_len;
        break;
    case 180:
        ray.start.Z += width / 1.5;
        ray.end = ray.start;
        ray.end.Z += ray_len;
        break;
    default:
        break;
    }

#ifdef DEBUG
    m.Lighting = false;
    m.Thickness = 10.0f;
    IrrlichtDevice::getInstance()._driver->setMaterial(m);
    IrrlichtDevice::getInstance()._driver->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    IrrlichtDevice::getInstance()._driver->draw3DLine(ray.start, ray.end, irr::video::SColor(0, 255, 0, 0));
#endif

    std::shared_ptr<GameObject> EntityCollided = nullptr;
    if ((outNode = collisionManager->getSceneNodeAndCollisionPointFromRay(ray, outCollisionPoint, outTriangle, idBitMask, collisionRootNode))) {
        std::for_each(world.begin(), world.end(), [&](std::shared_ptr<GameObject >& Entity) {
            if (Entity->getNode() == outNode)
                EntityCollided = Entity;
            }
        );
    }
    return EntityCollided;
}

GameObject::CubeType GameObject::getType() const {
    return _type;
}

void GameObject::debug() {
    getNode()->setDebugDataVisible(true);
}

bool GameObject::isDeleted()
{
    return _toDelete;
}

void GameObject::setDeleted(bool del)
{
    _toDelete = del;
}

void GameObject::defaultTransform() {
    setPosition(_defaultPosition);
    setRotation(_defaultRotation);
    setScale(_defaultScale);
}