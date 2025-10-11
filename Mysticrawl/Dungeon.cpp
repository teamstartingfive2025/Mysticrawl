#include "Dungeon.h"
#include "Player.h"
#include "Input.h"
#include <iostream>
#include <limits> 
using namespace std;

/**
 * The StartDungeon function runs the dungeon portion of the game.
 * It sets up the initial rooms, links them together, initializes the player,
 * and manages the main gameplay loop (exploration, movement, and interaction).
 */
void StartDungeon() {
    // --- Define dungeon layout and content ---
    Room spawnRoom{
        "Spawn Room",
        "You awake in a dimly lit dungeon cell, confused and dazed. \n"
        "The fiery light of a torch flickers against the dark, cold walls. \n"
        "The room is barren except for a sole flowerpot resting beside a pile of stones in the corner. \n"
        "A large iron-clad door stands to the east, bearing a large lock on the handle.\n"
    };

    Room nextRoom{
        "Next Room",
        "You step into a darker chamber. Runes glow faintly on the wall. "
        "A torch might help illuminate the strange scroll lying on the ground."
    };

    Room fightRoom{
        "Rat Room",
        "This is the combat demo.\n"
    };

    // Populate the rooms with items
    spawnRoom.items = { "Torch" };              // visible item
    spawnRoom.hiddenItems = { "Key" };          // hidden item found only by investigating
    nextRoom.items = {"Scroll with Riddle"};

    // Connect rooms via exits
    spawnRoom.exits["east"] = &nextRoom;
    nextRoom.exits["west"] = &spawnRoom;
    nextRoom.exits["east"] = &fightRoom;
    fightRoom.exits["west"] = &nextRoom;

    // The east door in the spawn room starts locked
    spawnRoom.locked = true;

    // --- Initialize the player ---
    Player player(&spawnRoom);
    cout << "\n=== Dungeon Entry ===\n";
    player.look();

    bool playing = true;

    // --- Main dungeon loop ---
    while (playing) {
        cout << "\nAvailable actions:\n";
        int option = 1;

        // Dynamic menu numbering based on available actions
        cout << option++ << ". Look around\n";

        //always allow for investigating and looking around
        cout << option << ". Investigate the area\n";
        int investigateOpt = option++;


        bool canMoveEast = player.getCurrentRoom()->exits.count("east");
        bool canMoveWest = player.getCurrentRoom()->exits.count("west");
        bool hasItems = !player.getCurrentRoom()->items.empty();

        // Track valid options
        int eastOpt = 0, westOpt = 0, pickupOpt = 0, invOpt = 0, exitOpt = 0;

        // Show move options only if those exits exist
        if (canMoveEast) {
            cout << option << ". Try moving East\n";
            eastOpt = option++;
        }
        if (canMoveWest) {
            cout << option << ". Move West\n";
            westOpt = option++;
        }
        // Only show pickup if items are present
        if (hasItems) {
            cout << option << ". Pick up Item\n";
            pickupOpt = option++;
        }

        // Always show inventory and exit
        cout << option << ". Check Inventory\n";
        invOpt = option++;
        cout << option << ". Exit Game\n";
        exitOpt = option++;
        cout << "\n";
        // --- Player input ---
        cout << "Selection: ";
        int choice;

        // Input validation loop to prevent crashes on non-numeric input
        while (true) {
            if (!(cin >> choice)) {
                cin.clear(); // clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter a number: ";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard leftover input
            break;
        }

        // --- Handle player actions ---
        if (choice == 1) {
            player.look();
        }
        else if (choice == investigateOpt) {
            // Search for hidden items
            player.investigate();
        }
        else if (choice == eastOpt && canMoveEast) {
            // Handle locked door behavior
            if (player.getCurrentRoom() == &spawnRoom && spawnRoom.locked) {
                cout << "\nYou tug on the iron door, but it will not budge. It is locked tight.\n Perhaps there is a key somewhere to unlock it\n";
                if (player.hasItem("Key")) {
                    cout << "You use the key to unlock the door.\n";
                    spawnRoom.locked = false;
                } else {
                    cout << "You will need to find a key.\n";
                    continue;
                }
            }
            // Move east once unlocked
            if (!player.getCurrentRoom()->locked) {
                player.setCurrentRoom(player.getCurrentRoom()->exits["east"]);
                player.look();
            }
        }
        else if (choice == westOpt && canMoveWest) {
            player.setCurrentRoom(player.getCurrentRoom()->exits["west"]);
            player.look();
        }
        else if (choice == pickupOpt && hasItems) {
            player.pickup();
        }
        else if (choice == invOpt) {
            player.showInventory();
        }
        else if (choice == exitOpt) {
            cout << "You leave the dungeon for now...\n";
            playing = false;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}