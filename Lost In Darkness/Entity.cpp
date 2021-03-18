#include "Entity.h"

static int i = 0;
Entity::Entity(std::string _name)
	: Name(_name)
{
	i++;
	Id = i;
}

Entity::~Entity()
{
	
}
