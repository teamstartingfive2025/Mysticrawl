#include "PlayerLose.h"
#include <iostream>
using namespace std;

bool EndOfBattle(Player& player)
{
    if (player.getHealth() <= 0)
    {
        // lose message in color
        std::cout << Constants::UI::SELECTION_COLOR
            << "Game over. You lose" << Constants::UI::COLOR_RESET << "\n";

        // false = signal to end program 
        return false;
    }

    //true = continue normal flow (return to dungeon loop)
    return true;
}