#pragma once
class AttributeComponent
{
public:
	//Leveling
	int level;
	int exp;
	int expNext;
	int points;

	//Attributes
	int strength;
	int vitality;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damage;
	int damageMax;
	int damageMin;
	int accuracy;
	int defence;
	int luck;


	AttributeComponent(unsigned level);
	~AttributeComponent();

	//Functions
	const std::string debugPrint();

	void gainExp(const int exp);
	void loseExp(const int exp);
	void takeDamage(const int damage);
	void gainHp(const int hp);

	void updateLevel();
	void update();
	void updateStats(const bool reset);
};

