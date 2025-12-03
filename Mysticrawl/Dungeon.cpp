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
    cout << "Your journey awaits...\n";
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
        "You step into a darker chamber. Runes glow faintly on the wall. \n"
        "A torch might help illuminate the strange scroll lying on the ground.\n",
        { make_shared<Item>("Scroll with Riddle") }
    );

    Room fightRoom(
        "Dusty Cellar",
        "Old crates and the smell of mildew.\n"
    );

    Room leverRoom(
        "Lever Room",
        "You step into a dimly lit chamber. A single iron lever is fixed to the wall.\n"
    );

    Room a4(
        "Snake Den",
        "The floor is littered with shed snake skins.\n"
    );

    Room buttonRoom(
        "Button Room",
        "The air smells of dust. A round stone button is embedded in the far wall.\n"
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
        "Placeholder\n"
    );

    Room a9(
        "a9: Fight here",
        "Placeholder\n"
    );

    Room greaterRatRoom(
        "The Trial of the Greater Rat",
        "The edges of this room are cluttered with the corpses of lesser rats.\n"
    );

    Room a11(
        "Secret Room",
        "A secret is revealed!\n"
    );

    Room b1( //there should be a single use means for the player to heal to max
        "The Catacombs",
        "Both sides of the passageway are covered with neat piles of skulls and bones. A crystal is embedded in the wall high above the bones.\n"
    );

    Room b2(
        "b2: Puzzle Room",
        "Puzzle east\n"
    );

    Room b3(
        "Piles of Bones",
        "The floor is littered with heaps of bones.\n"
    );

    Room b4(
        "b4: Puzzle Room",
        "Puzzle east and south\n"
    );

    Room b5(
        "Stone Room",
        "The walls in this room are bare, though some bones are still scattered on the ground.\n"
    );
    
    Room b6(
        "Secret Resting Place",
        "A skeleton in an open casket holds a box.\n" ///REPLACE BOX WITH WHATEVER GOES HERE
    );

    Room b7(
        "b7: Treasure Room",
        "Put something that buffs the player here\n"
    );

    Room b8(
        "Circular Room",
        "A mist fills the air, you can hardly see the skulls on the other side.\n"
    );

    Room b9(
        "East hallway",
        "A sign hangs over the southern doorway: \"THE CRYP -\". The rest is lost.\n"
    );

    Room b10(
        "Well Room",
        "A well is in the center of this room. You see no bucket though.\n You could swear you saw the skulls looking at you out of the corner of your eye.\n"
    );

    Room b11(
        "South hallway",
        "A sign hangs over the eastern doorway: \"THE CRYPT OF -\". The rest is lost.\n"
    );

    Room b12(
        "The Knight's Crypt",
        "In the center of this room, a skeleton wearing armor and fine jewelry sits on a throne.\n"
    );

    Room b13(
        "b13: Treasure Room",
        "Put something that buffs the player here\n"
    );

    Room c1(
        "Dark tunnel",
        "A passage so dark you can barely see\n"
    );

    Room c2(
        "Dark tunnel",
        "You begin to see a faint light eastward...\n"
    );

    Room d1(
        "The Old Mine",
        "A sign hangs above the door at the end of this dimly illuminated room: \"DANGER: DO NOT ENTER BY ORDER OF THE KING UNDER THE MOUNTAIN.\" A crystal is embedded in the southern wall.\n"
    );

    Room d7(
        "Shaft",
        "Crates and pickaxes line the walls. There appears to be black mold on the eastern wall.\n"
    );

    Room d8(
        "Corrupted Passageway",
        "The posts holding up the ceiling are rotted through with black slime. The equipment in this room is thoroughly rusted.\n"
    );

    Room d9(
        "Slime Room",
        "The walls and ceiling are covered with black slime that glows in some places.\n"
    );

    Room d10(
        "The Murky Pool",
        "The black slime in the mine seems to be growing from a pool in the center of the room.\n"
    );

    Room d11(
        "d11: Treasure Room",
        "Put something useful here\n"
    );

    Room d12(
        "Storage house",
        "Crates filled with ores, all abandoned.\n"
    );

    Room d13(
        "Passageway",
        "A dark sludge drips from the ceiling and leaks from the walls.\n"
    );

    Room d14(
        "Mineshaft",
        "To the north, the door post is covered in glowing slime.\n"
    );

    Room d15(
        "Supply depot",
        "Pickaxes and lanterns hang on the walls. All are rusted and covered in black slime.\n"
    );

    Room d16(
        "Collapsed Passageway",
        "Rocks block the way. A skeleton's arms are sticking out between the boulders.\n"
    );

    Room d17(
        "d17: Fight Room",
        "Placeholder\n"
    );

    Room d18(
        "d18: Empty Room",
        "Placeholder\n"
    );

    Room e1(
        "The Dark Lair",
        "Floating flames illuminate a hall with ebony walls. A crystal is embedded in the eastern wall.\n"
    );

    Room e2(
        "e2: Puzzle Room",
        "Puzzle north\n"
    );

    Room e3(
        "e3: Puzzle Room",
        "Puzzle north\b"
    );

    Room e4(
        "e4: Puzzle Room",
        "Puzzle north\n"
    );

    Room e5(
        "e5: Treasure Room",
        "Big weapon here\n"
    );

    // This room sits at the very end of the dungeon path, its the final dungeon room
    // add final boss to boss room at the end of the lever + button path
    Room finalBossRoom(
        "Final Boss Chamber",
        "\nThe chamber opens up into a vast hall. The walls are lined with crumbling statues,\n"
        "and a cold, oppressive silence hangs in the air. At the far end, a dark figure waits,\n"
        "watching your every move.\n"
        "It's the ghostly figure you met at the beginning of your journey.\n"
        "Every turn you took.\n"
        "Every room you explores.\n"
        "It... was... watching\n"
        "The Dungeon Overlord raises a hand and the exits slam shut!\n"
        "You sense that you won't leave this place until one of you falls...\n"

    );

    // List of pointers for testing using teleportation, not intended for long term use
    vector<Room*> allRooms = {
        &spawnRoom, &nextRoom, &fightRoom, &leverRoom, &a4, &buttonRoom, &wizardRoom, &southRoom,
        &a8, &a9, &greaterRatRoom, &a11, &b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8,
        &b9, &b10, &b11, &b12, &b13, &c1, &c2, &d1, &d7, &d8, &d9, &d10, &d11,
        &d12, &d13, &d14, &d15, &d16, &d17, &d18, &e1, &e2, &e3, &e4, &e5,
        &finalBossRoom
    };

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

    Enemy skKnight = SkeletonKnightTemplate;
    b12.addEnemy(&skKnight);

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
    // Create the final boss from the template and place it in the Final Boss Chamber
    Enemy finalBoss = BossTemplate;
    finalBossRoom.addEnemy(&finalBoss);

 
    // Connect rooms via exits
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

    shared_ptr<SimpleMechanism> heal_d1 = make_shared<SimpleMechanism>(
        "Crystal",
        [&d1, &player](bool) {
            cout << "Healed to max.\n";
            player.setHealth(player.getMaxHealth());
        },
        "The crystal's healing power is spent.\n" //sticky lever
    );
    d1.addMechanism(heal_d1);

    shared_ptr<SimpleMechanism> heal_e1 = make_shared<SimpleMechanism>(
        "Crystal",
        [&e1, &player](bool) {
            cout << "Healed to max.\n";
            player.setHealth(player.getMaxHealth());
        },
        "The crystal's healing power is spent.\n" //sticky lever
    );
    e1.addMechanism(heal_e1);

    // --- Initialize fight manager ---
    Fight fight;

    // --- Main dungeon loop ---
    player.look();

    try {
        while (true) {
            vector< tuple<string, function<void()>> > options;
            cout << "\nWhat would you like to do next?\n";

            options = {
                {"Look around", [&player]() { player.look(); }},
                {"Investigate the area", [&player]() { player.investigate(); }},
                {"Check Inventory", [&player]() { player.showInventory(); }},
                {"Move Somewhere", [&player]() { player.move(); }},
                {"Pickup Item", [&player]() { player.pickup(); }},
#ifdef _DEBUG
                {"Teleport", [&player, allRooms]() { player.teleport(allRooms); }},
#endif
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

            if (player.isDefending()) {
                player.setDefenceTurns(player.getDefenceTurns() - 1);
            }

            player.decrementDefenceCooldown();

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