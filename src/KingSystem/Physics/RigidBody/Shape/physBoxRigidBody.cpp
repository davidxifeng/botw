#include "KingSystem/Physics/RigidBody/Shape/physBoxRigidBody.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFactory.h"

namespace ksys::phys {

BoxRigidBody* BoxRigidBody::make(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return RigidBodyFactory::createBox(param, heap);
}

BoxRigidBody::BoxRigidBody(hkpRigidBody* hk_body, BoxShape* shape, ContactLayerType layer_type,
                           const sead::SafeString& name, bool set_flag_10, sead::Heap* heap)
    : RigidBodyFromShape(hk_body, layer_type, name, set_flag_10, heap), mShape(shape) {}

BoxRigidBody::~BoxRigidBody() {
    if (hasFlag(RigidBody::Flag::_10) && mShape) {
        delete mShape;
        mShape = nullptr;
    }
}

void BoxRigidBody::setExtents(const sead::Vector3f& extents) {
    if (mShape->setExtents(extents))
        updateShape();
}

void BoxRigidBody::setTranslate(const sead::Vector3f& translate) {
    if (mShape->setTranslate(translate))
        updateShape();
}

const sead::Vector3f& BoxRigidBody::getExtents() const {
    return mShape->mExtents;
}

const sead::Vector3f& BoxRigidBody::getTranslate() const {
    return mShape->mTranslate;
}

void BoxRigidBody::getTransformedTranslate(sead::Vector3f* translate) {
    lock();
    const auto& transform = getHkBody()->getMotion()->getMotionState()->getTransform();
    unlock();
    mShape->getTranslate(translate, transform);
}

void BoxRigidBody::setMaterialMask(const MaterialMask& mask) {
    mShape->setMaterialMask(mask);
}

const MaterialMask& BoxRigidBody::getMaterialMask() const {
    return mShape->mMaterialMask;
}

float BoxRigidBody::getVolume() {
    return mShape->getVolume();
}

Shape* BoxRigidBody::getShape_() {
    return mShape;
}

const Shape* BoxRigidBody::getShape_() const {
    return mShape;
}

u32 BoxRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks) {
    masks->ignored_layers = ~mContactMask.getDirect();
    masks->collision_filter_info = getCollisionFilterInfo();
    masks->material_mask = getMaterialMask().getRawData();
    return 0;
}

}  // namespace ksys::phys
