#include "EnemyTemplates.h"
#include <iostream>
using namespace std;

Enemy RatTemplate(
    "Rat", "A rat suddenly appears! I hope it doesn't have rabies...\n",
    5,  // hit points
    20, // block chance (%)
    1,  // min damage
    3,  // max damage
    40, // block exit chance (%)
    70, // attack chance (%) *
    15, // idle chance (%)   *These must add up to 100
    15  // taunt chance (%)  *
);

Enemy GreaterRatTemplate(
    [&](Enemy* self, Player& target) { // to access its member variables in the lambda, the object passes a pointer to itself as an argument. it feels ugly but John couldn't figure out a better way to do it.
        self->setSpecialInt(self->getSpecialInt()+1);
        self->resetProbabilities(0, 0, 0, 100); // once it begins its special attack, the Greater Rat will always choose Special for its action until it has charged and used its attack
        
        if (self->getSpecialInt() == 3) { // charge for 2 turns, attack on the third
            cout << "The Greater Rat unleashes a special attack!\n";
            self->setTauntMultiplier(self->getTauntMultiplier() + 4.0); // this attack is additively 4x as effective
            self->attack(target);
            self->resetProbabilities(60, 5, 15, 20); // reset probabilities back to normal. there should be a constants sheet with all this information so we don't have to repeat magic numbers in the constructor like this, but it's already midnight and I'm not doing that right now.
            self->setSpecialInt(0);
        }
        else {
            cout << "The Greater Rat charges a special attack!\n";
        }
    },
    "Greater Rat", "A Greater Rat suddenly appears! Looks like it means business...\n",
    12, // hit points
    40, // block chance (%)
    3,  // min damage
    6,  // max damage
    40, // block exit chance (%)
    60, // attack chance (%) *
    5,  // idle chance (%)   *These must add up to 100
    15, // taunt chance (%)  *
    20, // special chance(%) *
    0   // special int
);

Enemy WizardTemplate(
    "Evil Wizard", "An evil wizard glares at you, ready to cast a spell!\n", 
	30, 30, 5, 10, 20, 50, 20, 15
);