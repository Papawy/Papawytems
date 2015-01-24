#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <map>

#include "Utils.h"

#include "ItemShema.h"

class Item
{
public:
	Item();
	Item(ItemShema& shema);
	Item(ItemShema& shema, ObjectPosition position);

	Item(const Item& other);
	// I add it if it's requested
	/*Item(ItemShema& shema,
	float posX,
	float posY,
	float posZ,

	float rotX,
	float rotY,
	float rotZ);*/

	// Setters

	void setPosition(float posX, float posY, float posZ);
	void setPosition(ObjectPosition position);

	void setRotation(float rotX, float rotY, float rotZ);

	void setName(std::string name);

	bool setVar(std::string varName, int value);

	// Accessors

	ObjectPosition& getPosition();

	int getVar(std::string varName);

	std::string getName();

	ItemShema& getShema();

	// --

	void Show();
	void Hide();

	bool createVar(std::string varName, int value = 0);
	bool removeVar(std::string varName);
	bool isVariableExist(std::string varName);

	void setDefaultName();

	~Item();

private:
	ItemShema *m_shema;

	std::string m_name;

	std::map<std::string, int> m_vars;
	
	ObjectPosition m_position;

	bool m_showed;

	int m_gtaObjectId;
};
#endif // ITEM_H_INCLUDED