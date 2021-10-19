//
// Created by aspdr on 10/13/2021.
//

#pragma once

class IRepository {
    virtual void Open(std::string filename) = 0; // бинарная десериализация в файл
    virtual void Save() = 0; // бинарная сериализация в файл
};