#pragma once

#include "DestroyableGroundObject.h"
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <array>

constexpr std::size_t HEIGHT = 7;
constexpr std::size_t WIDTH = 14;

struct Houses {
    constexpr static char house_no_chimney[HEIGHT][WIDTH] = {
            "      #      ",
            "    #####    ",
            "  #       #  ",
            "#############",
            "#           #",
            "#           #",
            "#############"
    };

    constexpr static char house_chimney[HEIGHT][WIDTH] = {
            "      #   #  ",
            "    ##### #  ",
            "  #       #  ",
            "#############",
            "#           #",
            "#           #",
            "#############"
    };

    constexpr static char house_no_chimney_small_windows[HEIGHT][WIDTH] = {
            "      #      ",
            "    #####    ",
            "  ###   ###  ",
            "#############",
            "###       ###",
            "###       ###",
            "#############"
    };
};

class House : public DestroyableGroundObject {
public:
    bool isInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override {
        return score;
    }

    friend class HouseBuilderA;

    void Draw() const override;

private:
    const uint16_t score = 40;
    char look[HEIGHT][WIDTH];
};

class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
    virtual void Create() = 0;
    virtual HouseBuilder& SetLook(char const(&house_look)[HEIGHT][WIDTH]) = 0;
    virtual House* Build() const = 0;
};

class HouseBuilderA : public HouseBuilder {
public:
    HouseBuilderA() {
        this->Create();
    }

    void Create() override {
        house = new House;
    }

    virtual ~HouseBuilderA() override {
        delete house;
    }

    HouseBuilderA& SetLook(char const(&house_look)[HEIGHT][WIDTH]) override {
        for (size_t beg = 0; beg < HEIGHT; ++beg)
            strcpy(house->look[beg], house_look[beg]);
        return *this;
    }

    House* Build() const override {
        return house;
    }
protected:
    House* house;
};

class Director {
public:
    House* BuildHouseClassic(HouseBuilderA& builder) {
        builder.SetLook(Houses::house_no_chimney);
        return builder.Build();
    }

    House* BuildHouseChimney(HouseBuilderA& builder) {
        builder.SetLook(Houses::house_chimney);
        return builder.Build();
    }

    House* BuildHouseSmallWindow(HouseBuilderA& builder) {
        builder.SetLook(Houses::house_no_chimney_small_windows);
        return builder.Build();
    }
};