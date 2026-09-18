// COMP 2450 — Warden of the Foundations (Midterm 1)
// battle/Battle.cpp — YOU build the body.
//
// =====================================================================
// REQUIRED MECHANICS
// =====================================================================
// Re-read the public midterm page if anything below is unclear.
//
// MENU (at minimum, four options):
//   1. Attack          — damage the warden; warden retaliates that turn
//   2. Use item        — pick from inventory; effect; turn ends
//   3. Inspect Warden  — print warden's state; FREE action — turn does
//                        NOT end
//   4. Flee            — leave; gate stays closed
//
// END:
//   Victory  when wardenHP <= 0
//   Defeat   when playerHP <= 0
//   Fled     when the player chose Flee
//
// =====================================================================
// FLOOR-TIED REQUIREMENTS — ALL FOUR MUST APPEAR IN YOUR CODE
// =====================================================================
//
//   F0 (ADT)         — the available actions on a turn must live in a
//                      container of your choice. ABOVE the declaration,
//                      in a comment, name the ADT and defend it in one
//                      sentence (the same kind of defence Trial I Q1
//                      practiced — but this is a different collection
//                      than Q1's items menu; the right ADT may differ).
//
//   F1 (search)      — the Use-item branch MUST call findByName<Item>
//                      against hero.inventory to look up the item the
//                      player typed.
//
//   F2 (sort)        — when the items menu is displayed, sort the
//                      inventory at display time with a comparator
//                      (std::sort or your Floor 2 sortInventory). Pick
//                      a criterion (value — the healing-power stand-in
//                      — weight, or name) and document it in a comment.
//
//   F3 (templates +  — invalid menu input must `throw BattleException`
//      exceptions)     (ready skeleton in Battle.h) — or BagException
//                      where a genuinely bad index is the fault —
//                      caught INSIDE the battle loop so the player gets
//                      another prompt — not a crash, not an exit.
//
// =====================================================================
// WHAT THE GRADER WILL DO
// =====================================================================
//   1. cmake --build the project. If it does not compile, the Warden
//      has won by default.
//   2. Type `battle warden`, play through to BOTH a victory and a
//      defeat (or attempt to — items + RNG permitting).
//   3. Type a deliberately invalid menu choice (e.g., "9" for a
//      4-option menu). The game must NOT crash; it must re-prompt.
//   4. Open this file and find each of the four Floor ties. They must
//      be REAL — i.e., the menu actually runs through your container,
//      Use-item actually goes through findByName, the items menu is
//      actually sorted, the throw actually fires on bad input.

#include "Battle.h"

#include <iostream>
#include <string>

#include "../hero/Bag.h"
#include "../hero/BagException.h"
#include "../hero/Item.h"
#include "../bestiary/Search.h"
#include "../hero/Sort.h"

namespace dungeon {

namespace {

// =====================================================================
// Tunable battle parameters. Edit to taste; document any tuning in
// encounter-notes.md so the grader knows what to expect.
// =====================================================================
constexpr int kPlayerStartHP   = 30;
constexpr int kWardenStartHP   = 50;
constexpr int kPlayerAttackDmg = 6;   // damage per Attack action
constexpr int kWardenAttackDmg = 4;   // warden's retaliation damage

}  
// enum creates a set of named choices
// enum class, keeps our names scoped

enum class MenuAction {
	Attack,
	UseItem,
	Inspect,
	Flee
};

// {1, "Attack", MenuAction:: Attack}
struct MenuOption {
	int number;
	std::string label;
	MenuAction action;
};

void printMenu(
	Bag<MenuOption>& menu,
	int playerHP,
	int wardenHP
) {
std::cout << "\n -- Your turn -- your hp: " << playerHP << ", warden hp: " << wardenHP << "\n";
for (std::size_t i = 0; i < menu.size(); ++i) {
	// bag overload our operator[], allow menu[i]
	// to retrieve our menuoption at index i
	std::cout << "   " << menu[i].number << ". " << menu[i].label << "\n";
	}
std::cout << " > ";
}

MenuAction readMenuChoice(const Bag<MenuOption>& menu) {
	std::string line;

	//getline will get entire line up to enter key
	// if fails, std input may have been closed, treat as Flee
	if (!std::getline(std::cin, line)) {
		return MenuAction::Flee;  // EOF or error, treat as Flee
	}

	int n = -1;

	try {
		// "2" --> 2
		// if cant be converted, stoi throws an except
		n = std::stoi(line);
	}
	catch (...) {
		// catch any exceptions
		// replace low-level stoi w/ domain specific exception
		// BattleException
		throw BattleException(
			"'" + line + "' is not a valid menu number.(enter 1 to"
		+ std::to_string(menu.size()) + ")");
	}
	// search our menu for an opt who display num
	// matches num enter by player
	for (std::size_t i = 0; i < menu.size(); ++i) {
		if (menu[i].number == n) {
			return menu[i].action;
		}
	}
	//Input was numeric but it did not match a menu
	throw BagException(
		static_cast<std::size_t>(n),
		menu.size()
	);
}

// Handle player's use item action
// Hero& will give funct access
void useItem(Hero& hero, int& playerHP) {
	// handle empty inventory
	if (hero.inventory.empty()) {
		std::cout << "Your satchel is empty.\n";
		return;
	}
	// sort inventory
	sortInventory(hero, "value desc"); // sort by value, highest to lowest
	std::cout << "Choose an item by name:\n";
	printInventory(hero);
	std::cout << " > ";

	std::string name;

	// || short-circuit
	// try read line, if success, check whether line is empty
	// if either truem player does nothing
	if (!std::getline(std::cin, name) || name.empty()) {
		std::cout << "You appear to hesitate.\n";
		return;
	}

	// findByName<Item> <---- funct-template specialization
	// <item> will tell compiler search will op
	const Item* it = findByName<Item>(hero.inventory, name);

	//nullptr converts to false
	if (!it) {
		throw BattleException(
			"'" + name + "' is not in your satchel."
		);
	}

	//if find Potion, healing potion
	if (it->name.find("otion") != std::string::npos) {
		// heal 12 hp, also don't need heal to exceed max hp
		playerHP = std::min(playerHP + 12, kPlayerStartHP);
		std::cout << "You drink the " << it->name << " HP -> " << playerHP << ".\n";
	}
	else {
		std::cout << "You ready " << it->name << ", but it is not a consumable.\n";
	}
}
BattleOutcome runWardenBattle(Hero& hero) {
  // create 2 varia for player & warden hp (rep the state)
	int playerHP = kPlayerStartHP;
	int wardenHP = kWardenStartHP;

	// create bag specialized for MenuOption objects
	Bag<MenuOption> menu;
	menu.push_back({ 1, "Attack", MenuAction::Attack });
	menu.push_back({ 2, "Use item", MenuAction::UseItem });
	menu.push_back({ 3, "Inspect Warden", MenuAction::Inspect });
	menu.push_back({ 4, "Flee", MenuAction::Flee });

	// Continue battle while both are alive and player has not fled
	while (playerHP > 0 && wardenHP > 0) {
		try {
			printMenu(menu, playerHP, wardenHP);

			// readMenuChoice return a menuaction
			switch (readMenuChoice(menu)) {
			case MenuAction::Attack:{
				wardenHP -= kPlayerAttackDmg;
				// hp may internall fall below 0. 

				std::cout << "You attack the warden for " 
					<< kPlayerAttackDmg 
					<< " damage! Warden HP -> " 
					<< std::max(wardenHP, 0) 
					<< ".\n";
		}
	}
}

}  // namespace dungeon
