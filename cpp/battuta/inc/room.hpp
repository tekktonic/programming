#ifndef ROOM_H
#define ROOM_H
#include <memory>
#include <string>
#include <vector>

#include <jansson.h>

#include "interactable.hpp"
#include "polygon.hpp"
#include "serializable.hpp"
#include "texturewrap.hpp"

class Room// : public Serializable
{
    std::unique_ptr<TextureWrap> background;
/*    static Entity player;

    std::vector<Polygon&> walkableArea;
    std::vector<Interactable&> objects;*/
public:
    std::string serialize();
//    Item& take(Item& item);
    Room(std::string room);
//    void draw();
//    ~Room();
};

#endif
