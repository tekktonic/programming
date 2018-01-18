#include "room.hpp"

#include <iostream>
#include <map>

enum RoomEntries
{
    Id,
    Background,
    Foreground,
    Walkareas,
    Entrance,
    Items,
    Doors,
    InvalRoomEntry
};

static std::map<const char*, RoomEntries> stringRoomEntry;

static enum RoomEntries string_to_roomentry(const char *s)
{
    std::string str(s);
    if (str == "id") return Id;
    else if (str == "background") return Background;
    else if (str == "foreground") return Foreground;
    else if (str == "walkareas") return Walkareas;
    else if (str == "entrance") return Entrance;
    else if (str == "items") return Items;
    else if (str == "doors") return Doors;
    return InvalRoomEntry;

    
}
Room::Room(std::string room)
{

    std::string loadFile = "resources/rooms/" + room;
    json_error_t err;
    std::cout << loadFile << std::endl;
    
    json_t *json = json_load_file(loadFile.c_str(), 0, &err);

    if (!json)
    {
        std::cout << err.source << "<" << err.line << ":" << err.column << ": " << err.text << std::endl;
    }
    const char *key;
    json_t *val;
    json_object_foreach(json, key, val) {
        std::cout << key << std::endl;
        std::cout << stringRoomEntry[key] << std::endl;
        switch(string_to_roomentry(key))
        {
        case Id:
            std::cout << "RoomID is " << json_string_value(val) << std::endl;
            break;
        case Background:
            std::cout << "Background is " << json_string_value(val) << std::endl;
            break;
        case Foreground:
            std::cout << "Foreground is " << json_string_value(val) << std::endl;
            break;
        case Walkareas:
            std::cout << "Walkarea is a thing" << std::endl;
        case Entrance:
            
        default:
            break;
        }

    }
}

std::string Room::serialize() {
    return "";
}

