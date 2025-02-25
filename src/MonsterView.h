// MonsterView.h
#pragma once
#include "Observer.h"
#include "Monster.h"
#include <iostream>

class MonsterView : public Observer {
    Monster& monster;  // Reference to the Monster

public:
    MonsterView(Monster& m) : monster(m) {}

    void update() override {
        // This will be called whenever the Monster changes
        std::cout << "Monster health updated: " << monster.GetHealth() << " HP\n";
    }
};
