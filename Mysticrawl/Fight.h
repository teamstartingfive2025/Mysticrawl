#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Interactable.h"
#include "Player.h"

class Fight : public Interactable {
public:
	Fight() {}
	void fightMenu(Player& player);
};