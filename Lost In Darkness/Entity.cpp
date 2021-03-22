#include "Entity.h"

Entity::Entity(std::string _name)
	: Name(_name)
{
	ID++;
	Id = ID;
}

Entity::~Entity()
{
	
}
