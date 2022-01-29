#pragma once

#include "DynamicObject.h"
#include <memory>

class IBomb : public DynamicObject {
public:
    virtual ~IBomb() {}
};

class Bomb : public IBomb
{
public:

	static const uint16_t BombCost = 10; // ��������� ����� � �����

	void Draw() const override;

private:

};

class BombDecorator : public IBomb {
public:
    BombDecorator(IBomb*);
    void SetSpeed(double sp) override {
        bomb->SetSpeed(sp);
    }

    void SetDirection(double dx, double dy) override {
        bomb->SetDirection(dx, dy);
    }

    void Draw() const override;
    void Move(uint16_t) override;

    double GetY() const override { return bomb->GetY(); }
    double GetX() const override { return bomb->GetX(); }

    void SetWidth(uint16_t widthN) override { bomb->SetWidth(widthN); }

    void SetPos(double nx, double ny);
    uint16_t GetWidth() const;
private:
    std::unique_ptr<IBomb> bomb;
};