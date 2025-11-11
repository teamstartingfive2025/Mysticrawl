#include "EnemyTemplates.h"

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
    "Greater Rat", "A greater rat suddenly appears! Looks like it means business...\n",
    10, // hit points
    40, // block chance (%)
    3,  // min damage
    6,  // max damage
    40, // block exit chance (%)
    80, // attack chance (%) *
    5,  // idle chance (%)   *These must add up to 100
    15  // taunt chance (%)  *
);