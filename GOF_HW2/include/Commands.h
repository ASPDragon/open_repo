//
// Created by ionian_caster on 2022-01-25.
//

#pragma once

#include <vector>
#include <algorithm>
#include "Plane.h"
#include "Bomb.h"

class ICommand {
protected:
    ICommand() {}
public:
    virtual ~ICommand() {}
    virtual void Execute() = 0;
};

template<class T>
class DeleteObject : public ICommand {
public:
    DeleteObject(std::vector<T*>& _ObjectsVec, T* _Obj) : ObjectsVec{_ObjectsVec}, Obj{_Obj} {}

    virtual void Execute() override;
private:
    std::vector<T*>& ObjectsVec;
    T* Obj;
};

template<class T>
void DeleteObject<T>::Execute() {
    auto it = std::find(ObjectsVec.begin(), ObjectsVec.end(), Obj);
    if (it != ObjectsVec.end())
        ObjectsVec.erase(it);
};

class BombLauncher :public ICommand {
public:
    BombLauncher(const Plane*, std::vector<DynamicObject*>&, const uint16_t&, const uint16_t&, const uint16_t&, int16_t&);

protected:
    IBomb* BombCreator() const;
    const Plane* plane;
    std::vector<DynamicObject*>& ObjectsVec;
    const uint16_t& bombsQuantity;
    const uint16_t& freeFallSpeed;
    const uint16_t& craterWidth;
    int16_t& score;
};

class DropBomb : public BombLauncher {
public:
    DropBomb(const Plane* _plane, std::vector<DynamicObject*>& _ObjectsVec, const uint16_t& _bombsQuantity,
             const uint16_t& _freeFallSpeed, const uint16_t& _craterWidth, int16_t& _score)
             : BombLauncher(_plane, _ObjectsVec, _bombsQuantity, _freeFallSpeed, _craterWidth, _score) {}
    void Execute() override;
};

class DropDecoratedBomb : public BombLauncher {
public:
    DropDecoratedBomb(const Plane* _plane, std::vector<DynamicObject*>& _ObjectsVec, const uint16_t& _bombsQuantity,
             const uint16_t& _freeFallSpeed, const uint16_t& _craterWidth, int16_t& _score)
            : BombLauncher(_plane, _ObjectsVec, _bombsQuantity, _freeFallSpeed, _craterWidth, _score) {}
    void Execute() override;
};