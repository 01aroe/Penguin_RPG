#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include "healing.h"
#include "weapon.h"
#include "armour.h"

#include <list>
#include <utility>
#include <iostream>

class Inventory
{
public:
	//Whilst weapons and armour are items, they have their own 
	//specific properties and can't be stored in the same list.
	//The first element of the pair stores a pointer to the item
	//in the item/weapon/armour atlas, defined in main(), the second
	//if the quantity of the item

	std::list<std::pair<Item*, int>> items;
	std::list<std::pair<Healing*, int>> healing;
	std::list<std::pair<Weapon*, int>> weapons;
	std::list<std::pair<Armour*, int>> armours;

	Inventory(){};
	Inventory(std::list<std::pair<Item*, int>> items,
		std::list<std::pair<Healing*, int>> healing,
		std::list<std::pair<Weapon*, int>> weapons,
		std::list<std::pair<Armour*, int>> armours) :
		items(items), healing(healing), weapons(weapons), 
		armours(armours){};

	void add_item(Item* item, int count);
	void add_healing(Healing*, int count);
	void add_weapon(Weapon* weapon, int count);
	void add_armour(Armour* armour, int count);

	void remove_item(Item*, int count);
	void remove_healing(Healing*, int count);
	void remove_weapon(Weapon*, int count);
	void remove_armour(Armour*, int count);

	void merge(Inventory* inventory);
	void clear();

	int print_items(bool label = false);
	int print_healing(bool label = false);
	int print_weapons(bool label = false);
	int print_armours(bool label = false);
	void print(bool label = false);
};
#endif //INVENTORY_H