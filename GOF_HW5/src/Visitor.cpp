//
// Created by ionian_caster on 2022-02-09.
//

#include "Visitor.h"
#include "Plane.h"
#include "Bomb.h"
#include "MyTools.h"

void LogVisitor::log(Plane &p) const {
    MyTools::WriteToLog(std::string("Get Plane Speed") + " was invoked", p.GetSpeed());
    MyTools::WriteToLog(std::string("Get Plane X Axis Direction") + " was invoked", p.GetDirection().first);
    MyTools::WriteToLog(std::string("Get Plane Y Axis Direction") + " was invoked", p.GetDirection().second);
}

void LogVisitor::log(Bomb &b) const {
    MyTools::WriteToLog(std::string("Get Bomb Speed") + " was invoked", b.GetSpeed());
    MyTools::WriteToLog(std::string("Get Bomb X Axis Direction") + " was invoked", b.GetDirection().first);
    MyTools::WriteToLog(std::string("Get Bomb Y Axis Direction") + " was invoked", b.GetDirection().second);
}