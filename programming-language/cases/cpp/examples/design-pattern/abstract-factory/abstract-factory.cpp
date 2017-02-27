#include <iostream>

////////////////////////////////////////

class Door {
public:
    virtual void description();
    ~Door() {}
};

class DoorFittingExpert {
public:
    virtual void description();
    ~DoorFittingExpert() {}
};

template<typename Door, typename Expert>
class DoorAbstractFactory {
public:
    Door new_door() { return Door {}; }
    Expert new_expert() { return Expert {}; }
};

////////////////////////////////////////

class WoodenDoor : public Door {
public:
    void description() override { std::cout << "A wooden door!" << '\n'; }
    ~WoodenDoor() {}
};

class IronDoor : public Door {
public:
    void description() override { std::cout << "A iron door!" << '\n'; }
    ~IronDoor() {}
};

////////////////////////////////////////

class Carpenter : public DoorFittingExpert {
public:
    void description() override { std::cout << "I can only fit wooden door!" << '\n'; }
    ~Carpenter() {}
};

class Welder : public DoorFittingExpert {
public:
    void description() override { std::cout << "I can only fit iron door!" << '\n'; }
    ~Welder() {}
};

////////////////////////////////////////

using WoodenDoorFactory = DoorAbstractFactory<WoodenDoor, Carpenter>;
using IronDoorFactory = DoorAbstractFactory<IronDoor, Welder>;


int main() {
    {
        auto factory = WoodenDoorFactory();
        auto door = factory.new_door();
        auto expert = factory.new_expert();
        door.description();
        expert.description();
    }
    {
        auto factory = IronDoorFactory();
        auto door = factory.new_door();
        auto expert = factory.new_expert();
        door.description();
        expert.description();
    }
    {
        auto factory = WoodenDoorFactory();
        auto door   = factory.new_door();
        auto expert = factory.new_expert();
        auto pdoor   = static_cast<Door*>             (&door);
        auto pexpert = static_cast<DoorFittingExpert*>(&expert);
        pdoor->description();
        pexpert->description();
    }
    {
        auto factory = IronDoorFactory();
        auto door   = factory.new_door();
        auto expert = factory.new_expert();
        auto pdoor   = static_cast<Door*>             (&door);
        auto pexpert = static_cast<DoorFittingExpert*>(&expert);
        pdoor->description();
        pexpert->description();
    }
    return 0;
}

