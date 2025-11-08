#include "EnemyTemplates.h"

Enemy RatTemplate(
    "Rat", "A rat suddenly appears! I hope it doesn't have rabies...\n",
    5,  // hit points
    20, // block chance (%)
    1,  // min damage
    3,  // max damage
    40, // block exit chance (%)
    70, // attack chance (%)
    15, // idle chance (%)
    15  // taunt chance (%)
);