#include "Dungeon.h"
#include "Player.h"
#include "Input.h"
#include "Enemy.h"
#include "Item.h"
#include "Key.h"
#include "Potion.h"
#include "Fight.h"
#include "SimpleMechanism.h"
#include "EnemyTemplates.h"
#include "Prompt.h"
#include "Lockable.h"
#include "Container.h"
#include "Random.h"

#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

/**
 * The StartDungeon function runs the dungeon portion of the game.
 * It sets up the initial rooms, links them together, initializes the player,
 * and manages the main gameplay loop (exploration, movement, and interaction).
 */
void StartDungeon() {

    // --- Define dungeon layout and content ---
    Room spawnRoom(
        "Spawn Room",
        "You awake in a dimly lit dungeon cell, confused and dazed. \n"
        "The fiery light of a torch flickers against the dark, cold walls. \n"
        "The room is barren except for a sole flowerpot resting beside a pile of stones in the corner. \n"
        "A large iron-clad door stands to the east, bearing a large lock on the handle.\n",
        { make_shared<Item>("Torch") }
    );

    // --- Initialize the player ---
    Player player(&spawnRoom, "Hero", 100);

    Room nextRoom(
        "Next Room",
        "You step into a darker chamber. Runes glow faintly on the wall. "
        "A torch might help illuminate the strange scroll lying on the ground.",
        { make_shared<Item>("Scroll with Riddle") }
    );

    Room fightRoom(
        "Dusty Cellar",
        "Old crates and the smell of mildew.\n"
    );

    Room leverRoom(
        "Lever Room",
        "You step into a dimly lit chamber. A single iron lever is fixed to the wall."
    );

    Room a4(
        "Snake Den",
        "The floor is littered with shed snake skins."
    );

    Room buttonRoom(
        "Button Room",
        "The air smells of dust. A round stone button is embedded in the far wall."
    );

    Room wizardRoom(
        "Wizard's Lair",
        "The air crackles with magical energy. Ancient tomes and potions clutter the space.\n"
    );

    Room southRoom(
        "Wizard Treasury",
        "A low-ceiling cellar stuffed with broken barrels. Something skitters beneath the debris.\n"
    );
    
    Room a8(
        "a8: Puzzle to go north",
        "Placeholder"
    );

    Room a9(
        "a9: Fight here",
        "Placeholder"
    );

    Room greaterRatRoom(
        "The Trial of the Greater Rat",
        "The edges of this room are cluttered with the corpses of lesser rats."
    );

    Room a11(
        "Secret Room",
        "A secret is revealed!"
    );

    Room b1( //there should be a single use means for the player to heal to max
        "The Catacombs",
        "Both sides of the passageway are covered with neat piles of skulls and bones. A crucifix hangs on the wall high above the bones."
    );

    Room b2(
        "b2: Puzzle Room",
        "Puzzle east"
    );

    Room b3(
        "b3: Fight Room",
        "Placeholder"
    );

    Room b4(
        "b4: Puzzle Room",
        "Puzzle east and south"
    );

    Room b5(
        "b5: Fight Room",
        "Placeholder"
    );
    
    Room b6(
        "b6: Secret Treasure Room",
        "Placeholder"
    );

    Room b7(
        "b7: Treasure Room",
        "Put something that buffs the player here"
    );

    Room b8(
        "b8: Fight Room",
        "Placeholder"
    );

    Room b9(
        "b9: Puzzle Room",
        "puzzle south"
    );

    Room b10(
        "b10: Fight Room",
        "Placeholder"
    );

    Room b11(
        "b11: Puzzle Room",
        "puzzle east"
    );

    Room b12(
        "b12: Mini boss Room",
        "Placeholder"
    );

    Room b13(
        "b13: Treasure Room",
        "Put something that buffs the player here"
    );

    Room c1(
        "Dark tunnel",
        "A passage so dark you can barely see"
    );

    Room c2(
        "Dark tunnel",
        "You begin to see a faint light eastward..."
    );

    Room d1(
        "The Old Mine",
        "A sign hangs above the door at the end of this dimly illuminated room: \"DANGER: DO NOT ENTER BY ORDER OF THE KING UNDER THE MOUNTAIN\""
    );

    Room d7(
        "d7: Puzzle Room",
        "Crates and pickaxes line the walls. There appears to be black mold on the eastern wall."
    );

    Room d8(
        "d8: Fight Room",
        "The posts holding up the ceiling are rotted through with black slime. The equipment in this room is thoroughly rusted."
    );

    Room d9(
        "d9: Fight Room",
        "The walls and ceiling are covered with black slime that glows in some places."
    );

    Room d10(
        "The Murky Pool",
        "The black slime in the mine seems to be growing from a pool in the center of the room."
    );

    Room d11(
        "d11: Treasure Room",
        "Put something useful here"
    );

    Room d12(
        "Storage house",
        "Crates filled with ores, all abandoned."
    );

    Room d13(
        "Passageway",
        "A dark sludge drips from the ceiling and leaks from the walls."
    );

    Room d14(
        "d14: Puzzle Room",
        "Puzzle north"
    );

    Room d15(
        "d15: Treasure Room",
        "Put something useful here"
    );

    Room d16(
        "d16: Treasure Room",
        "Put something useful here"
    );

    Room d17(
        "d17: Fight Room",
        "Placeholder"
    );

    Room d18(
        "d18: Empty Room",
        "Placeholder"
    );

    Room e1(
        "e1: Healing Room",
        "Single use means to heal to max"
    );

    Room e2(
        "e2: Puzzle Room",
        "Puzzle north"
    );

    Room e3(
        "e3: Puzzle Room",
        "Puzzle north"
    );

    Room e4(
        "e4: Puzzle Room",
        "Puzzle north"
    );

    Room e5(
        "e5: Treasure Room",
        "Big weapon here"
    );

    // This room sits at the very end of the dungeon path, its the final dungeon room
    Room finalBossRoom(
        "Final Boss Chamber",
        "You step into a vast circular chamber. Ancient stone pillars rise into the darkness.\n"
        "The air feels unnaturally heavy, as though the dungeon itself is watching you.\n"
        "This feels like the heart of the entire labyrinth...\n"
    );

    //Add enemies
    Enemy rat = RatTemplate;
    fightRoom.addEnemy(&rat);

    Enemy snake = SnakeTemplate;
    a4.addEnemy(&snake);

    Enemy rat_01 = RatTemplate;
    a9.addEnemy(&rat_01);

    Enemy wizard = WizardTemplate;
    wizardRoom.addEnemy(&wizard);
    shared_ptr<Item> wizardKey = make_shared<Item>();
    wizardKey->setName("Wizard's Key");
    wizardRoom.addItem(wizardKey);
    
    Enemy gRat = GreaterRatTemplate;
    greaterRatRoom.addEnemy(&gRat);

    Enemy skeleton_b3 = SkeletonTemplate;
    b3.addEnemy(&skeleton_b3);

    Enemy skeleton_b5 = SkeletonTemplate;
    b5.addEnemy(&skeleton_b5);

    Enemy ghost_b8 = GhostTemplate;
    b8.addEnemy(&ghost_b8);

    Enemy ghost_b10 = GhostTemplate;
    b10.addEnemy(&ghost_b10);

    Enemy gRat_d8 = GreaterRatTemplate;
    d8.addEnemy(&gRat_d8);

    Enemy mole_d9 = GiantMoleTemplate;
    d9.addEnemy(&mole_d9);

    Enemy gRat_d12 = GreaterRatTemplate;
    d12.addEnemy(&gRat_d12);

    Enemy mole_d17 = GiantMoleTemplate;
    d17.addEnemy(&mole_d17);

    Enemy theThing = ThingTemplate;
    d10.addEnemy(&theThing);

    //Add items and containers
    shared_ptr<Key> key = make_shared<Key>();
    spawnRoom.setExits({ Exit("east", &nextRoom, { [&]() -> bool { return player.hasItem(key); } }) });
    key->setName("Key");
    key->setExitKeyUnlockDestination(spawnRoom.getExit("east"));
    spawnRoom.addHiddenItem(key);

    fightRoom.addItem(make_shared<Potion>("Potion of Healing", 10));

    southRoom.addContainer(Container(
        "Wizard Box",
        { make_shared<Potion>("Potion of Healing", 10) },
        { [&]() -> bool { return player.hasItem(wizardKey); } }
    ));

    // Connect rooms via exits
    // Next Room connects in all four directions
    nextRoom.setExits({
        Exit("west",  &spawnRoom),
        Exit("east",  &fightRoom),
        //Exit("north", &wizardRoom),
        //Exit("south", &southRoom)
    });

    fightRoom.setExits({
        Exit("west", &nextRoom),
        Exit("east", &leverRoom),
        //Exit("north", &greaterRatRoom)
    });

    leverRoom.setExits({
        Exit("west", &fightRoom),
        Exit("east", &a4) // locked initially
    });

    a4.setExits({
        Exit("west", &leverRoom),
        Exit("north", &a8),
        Exit("south", &buttonRoom)
    });

    buttonRoom.setExits({
        Exit("north", &a4)
    });

    southRoom.setExits({
        Exit("east", &wizardRoom)
    });

    wizardRoom.setExits({
        Exit("west", &southRoom),
        Exit("east", &a8)
    });

    a8.setExits({
        Exit("west", &wizardRoom),
        Exit("north", &a9),
        Exit("south", &a4)
    });

    a9.setExits({
        Exit("east", &greaterRatRoom),
        Exit("south", &a8)
    });

    greaterRatRoom.setExits({
        Exit("west", &a9),
        Exit("south", &b1)
    });

    a11.setExits({
        Exit("south", &greaterRatRoom)
    });

    b1.setExits({
        Exit("north", &greaterRatRoom),
        Exit("south", &b2)
    });

    b2.setExits({
        Exit("north", &b1),
        Exit("east", &b7)
    });

    b3.setExits({
        Exit("east", &b4),
        Exit("south", &b7)
        });

    b4.setExits({
        Exit("west", &b3),
        Exit("east", &b5),
        Exit("south", &b8)
        });

    b5.setExits({
        Exit("west", &b4),
        Exit("south", &b9)
        });

    b6.setExits({
        Exit("south", &b5)
        });

    b7.setExits({
        Exit("west", &b2),
        Exit("east", &b8),
        Exit("north", &b3),
        Exit("south", &b10)
    });

    b8.setExits({
        Exit("west", &b7),
        Exit("east", &b9),
        Exit("north", &b4),
        Exit("south", &b11)
        });

    b9.setExits({
        Exit("west", &b8),
        Exit("north", &b5),
        Exit("south", &b12)
        });

    b10.setExits({
        Exit("east", &b11),
        Exit("north", &b7),
        });

    b11.setExits({
        Exit("west", &b10),
        Exit("east", &b12),
        Exit("north", &b8)
        });

    b12.setExits({
        Exit("west", &b11),
        Exit("north", &b9),
        Exit("south", &b13)
        });

    b13.setExits({
        Exit("west", &c1),
        Exit("north", &b12)
        });

    c1.setExits({
        Exit("east", &b13),
        Exit("south", &c2)
        });

    c2.setExits({
        Exit("north", &c1),
        Exit("east", &d1)
        });

    d1.setExits({
        Exit("west", &c2),
        Exit("east", &d7)
        });

    d7.setExits({
        Exit("west", &d1),
        Exit("east", &d8),
        Exit("south", &d12)
        });

    d8.setExits({
        Exit("west", &d7),
        Exit("east", &d9)
        });

    d9.setExits({
        Exit("west", &d8),
        Exit("east", &d10),
        Exit("south", &d14)
        });

    d10.setExits({
        Exit("west", &d9),
        Exit("east", &d11)
        });

    d11.setExits({
        Exit("west", &d10),
        Exit("east", &e1)
        });

    d12.setExits({
        Exit("east", &d13),
        Exit("north", &d7)
        });

    d13.setExits({
        Exit("west", &d12),
        Exit("south", &d17)
        });

    d14.setExits({
        Exit("east", &d15),
        Exit("north", &d9),
        Exit("south", &d18)
        });

    d15.setExits({
        Exit("west", &d14)
        });

    d16.setExits({
        Exit("east", &d17)
        });

    d17.setExits({
        Exit("west", &d16),
        Exit("east", &d18),
        Exit("north", &d13)
        });

    d18.setExits({
        Exit("west", &d17),
        Exit("north", &d14)
        });

    e1.setExits({
        Exit("west", &d11),
        Exit("north", &e2)
        });

    e2.setExits({
        Exit("south", &e1),
        Exit("north", &e3)
        });

    e3.setExits({
        Exit("south", &e2),
        Exit("north", &e4)
        });

    e4.setExits({
        Exit("south", &e3),
        Exit("north", &e5)
        });

    e5.setExits({
        Exit("south", &e4),
        Exit("north", &finalBossRoom)
        });

    finalBossRoom.setExits({
        Exit("south", &e5)
        });

    //Add interactables
    
    shared_ptr<SimpleMechanism> lever = make_shared<SimpleMechanism>(
        "Iron Lever", true, // true = lever type
        [&leverRoom](bool state) {                // capture leverRoom by reference
            if (exit) {
                if (state) {
                    cout << "You hear gears turning, the eastern door unlocks!\n";
                }
                else {
                    cout << "The lever resets, the door locks again.\n";
                }
            }
        }
    );

    leverRoom.getExit("east")->addLock([&]() -> bool { return lever->getState(); });

    leverRoom.addMechanism(lever);

    auto button = make_shared<SimpleMechanism>(
        "Stone Button", false,
        [&buttonRoom](bool) {
            cout << "A hidden panel opens revealing a glittering amulet!\n";
            auto amulet = make_shared<Item>("Glittering Amulet");
            buttonRoom.addItem(amulet); 
        }
    );

    buttonRoom.addMechanism(button);

    shared_ptr<SimpleMechanism> button_a10 = make_shared<SimpleMechanism>(
        "Loose Brick", false, 
        [&greaterRatRoom, &a9, &b1, &a11](bool) {
            cout << "A door appears to the north!\n";
            greaterRatRoom.setExits({
                Exit("north", &a11),
                Exit("west", &a9),
                Exit("south", &b1)
                });
        }
    );
    greaterRatRoom.addMechanism(button_a10);

    shared_ptr<SimpleMechanism> heal_b1 = make_shared<SimpleMechanism>(
        "Crucifix",
        [&b1, &player](bool) {
            cout << "Healed to max.\n";
            player.setHealth(player.getMaxHealth());
        },
        "The crucifix's healing power is spent.\n" //sticky lever
    );
    b1.addMechanism(heal_b1);

    shared_ptr<SimpleMechanism> button_b5 = make_shared<SimpleMechanism>(
        "Outline on North Wall", false, 
        [&b5, &b4, &b6, &b9](bool) {
            cout << "A door appears to the north!\n";
            b5.setExits({
                Exit("north", &b6),
                Exit("west", &b4),
                Exit("south", &b9)
                });
        }
    );
    b5.addMechanism(button_b5);

    // --- Initialize fight manager ---
    Fight fight;

    // --- Main dungeon loop ---
    player.look();

    try {
        while (true) {
            vector< tuple<string, function<void()>> > options;

            options = {
                {"Look around", [&player]() { player.look(); }},
                {"Investigate the area", [&player]() { player.investigate(); }},
                {"Check Inventory", [&player]() { player.showInventory(); }},
                {"Move Somewhere", [&player]() { player.move(); }},
                {"Pickup Item", [&player]() { player.pickup(); }},
            };
            if (!player.inventoryEmpty()) {
                options.push_back({ "Use Item", [&player]() { player.useItem(player.itemSelectMenu());  } });
            }

            //only give fight option if enemy is present
            if (!player.getCurrentRoom()->getEnemies().empty()) {
                options.push_back({ "Fight", [&]() {
                    fight.fightMenu(player);
                } });
            }

            if (!player.getCurrentRoom()->getMechanisms().empty() ||
				!player.getCurrentRoom()->getContainers().empty()
            ) {
                options.push_back({ "Interact", [&]() { player.interact(); } });
            }

            options.push_back(
                { "Exit Game", [&]() {
                    WaitForEnterPrompt("You leave the dungeon for now...\n\n");
                    throw runtime_error("exit lambda and dungeon loop");
                } }
            );

            for (Enemy* enemy : player.getCurrentRoom()->getEnemies()) {
                if (enemy) {
                    enemy->action(player);
                    if (player.getHealth() <= 0) {
                        return;
                    }
                }
            }

            if (player.isPoisoned()) {
                int damage = Random::GetInstance().randInt(player.getPoisonMin(), player.getPoisonMax());
                
                cout << "\nTook " << damage << " damage from poison\n";

                player.decrementPoison();
            }

            player.displayHealthBar();

            player.getCurrentRoom()->RefreshSelectionMenu(options);
            player.getCurrentRoom()->SelectMenuOption();
            
            player.decrementAttackDebuff();
        }
    }
    catch (const runtime_error&) {
        return;
    }
}