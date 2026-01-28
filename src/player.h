#pragma once
#include <string>
#include "room.h"

class Player {
    public:
    string Name;
    shared_ptr<Room> CurrentRoom;
};

