#include "creature.h"

Creature::Creature(std::string name, int health, int str, int end, int dex,
	double hitRate, unsigned int level, std::string className)
{
	this->name = name;
	this->health = health;
	this->maxHealth = health;
	this->str = str;
	this->end = end;
	this->dex = dex;
	this->hitRate = hitRate;
	this->className = className;
	this->equippedArmour[Armour::Slot::HEAD] = nullptr;
	this->equippedArmour[Armour::Slot::TORSO] = nullptr;
	this->equippedArmour[Armour::Slot::LEGS] = nullptr;
	this->equippedWeapon = nullptr;
	this->level = level;
	this->experience = 0;
}

Creature::Creature()
{
	this->equippedArmour[Armour::Slot::HEAD] = nullptr;
	this->equippedArmour[Armour::Slot::TORSO] = nullptr;
	this->equippedArmour[Armour::Slot::LEGS] = nullptr;
	this->equippedWeapon = nullptr;
	this->level = 1;
	this->experience = 0;
}

//calculates the exp required to reach a certain level
//*in total*
unsigned int Creature::expToLevel(unsigned int level)
{
	//exp to level x = 128*x^2
	return 128 * (level * level);
}

//level the creature up if it has enough exp
//returns true if enough exp, false if not
bool Creature::levelUp()
{
	//we want the exp to the next level, not current level
	if (this->experience >= expToLevel(level + 1))
	{
		//level up
		++level;

		//vars to keep track of stat increases
		unsigned int healthBoost = 0;
		unsigned int strBoost = 0;
		unsigned int endBoost = 0;
		unsigned int dexBoost = 0;

		//give a large boost to health every 3 levels
		if (level % 3 == 0)
		{
			//randomly increase health, but keep proportional
			//to creatures end
			healthBoost = 10 + (rand() % 4) + (this->end / 4);
		}
		else
		{
			//standard health increase
			healthBoost = (this->end / 4);
		}
		//if the creature is a fighter, favour str and end boosts
		//Only increase dex 50% of the time
		if (this->className == "Fighter")
		{
			strBoost = 1;
			endBoost = 1;
			if (rand() % 2 == 0)
			{
				dexBoost = 1;
			}
		}
		//if the creature is a Rogue, favour dex and end boosts
		//Only increase str 50% of the time
		if (this->className == "Rogue")
		{
			dexBoost = 1;
			endBoost = 1;
			if (rand() % 2 == 0)
			{
				strBoost = 1;
			}
		}
		//adjust all the variables based on increases
		this->maxHealth += healthBoost;
		this->str += strBoost;
		this->end += endBoost;
		this->dex += dexBoost;

		//inform the user they grew a level, what boosts were and
		//what the new stats for the creature are
		std::cout << this->name << " grew to level " << level << "!" << std::endl;
		std::cout << "Health + " << healthBoost << " -> "
			<< this->maxHealth << std::endl;
		std::cout << "Strength + " << strBoost << " -> "
			<< this->str << std::endl;
		std::cout << "Endurance + " << endBoost << " -> "
			<< this->end << std::endl;
		std::cout << "Dexterity + " << dexBoost << " -> "
			<< this->dex << std::endl;
		std::cout << "-----------------" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void Creature::equipHealing(Healing* healing)
{
	this->health += healing->healing;
	if (this->health > this->maxHealth)
	{
		this->health = this->maxHealth;
	}
	return;
}

void Creature::equipWeapon(Weapon* weapon)
{
	this->equippedWeapon = weapon;
	return;
}

void Creature::equipArmour(Armour* armour)
{
	this->equippedArmour[(int)armour->slot] = armour;
	return;
}