#pragma once

#include "Bomb.h"
#include "Plane.h"
#include <vector>

template<typename Iter, typename Obj>
class IIterator {
public:
    virtual void Next() = 0;
    virtual bool isValid() const = 0;
    virtual Obj* ObjectPtr() const = 0;
    virtual ~IIterator() = default;

protected:
    IIterator() {}
};

template<typename Iter, typename Obj>
class BombIterator : public IIterator<Iter, Obj> {
public:
    BombIterator(std::vector<Iter*>& _vecObj)
    : vecObj{_vecObj} {
        current = vecObj.begin();

        obj();
    }

    void Next() override {
        if (isValid())
            current++;

        obj();
    }

    void obj() {
        while (isValid()) {
            objectPtr = dynamic_cast<Obj*>(*current);

            if (objectPtr != nullptr) {
                break;
            }
            current++;
        }
    }

    bool isValid() const override {
        return current < vecObj.end();
    }


    Obj* ObjectPtr() const override {
        return objectPtr;
    }


protected:
    typename std::vector<Iter*>::iterator current;
    std::vector<Iter*>& vecObj;
    Obj* objectPtr;
};