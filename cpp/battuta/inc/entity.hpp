#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include <janson.h>

#include "item.hpp"
#include "polygon.hpp"

class Entity : Serializable
{
    Point position;
    std::vector<Polygon> &walkableArea;
    std::vector<Item> inventory;
public:
    void walk_to(Point &p);
    std::string serialize();
    void pick_up(Item &i);
    void use(Item &i);
}
