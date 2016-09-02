#include "object.h"

Object::Object() : Transform()
{
}

Object::Object(Transform* parent) : Transform(parent)
{
}

Object::~Object()
{
	removeAllComponents();
}

BaseComponent* Object::addComponent(BaseComponent* comp)
{
	if(comp != nullptr)
	{
		//already has component of same type attached
		if(comp_list.find(comp->id) != comp_list.end())
		{
			//add debug out later
			return nullptr;
		}

		comp_list[comp->id] = comp;
		comp->setParent(this);
	}

	return comp;
}

void Object::removeComponent(BaseComponent* comp)
{
	if(comp == nullptr) return;

	for(auto it = comp_list.begin(); it != comp_list.end(); it++)
	{
		if(it->second == comp)
		{
			comp_list.erase(it);
			break;
		}
	}
}

/* Remove object from list and set parent to null
to mark for garbage collection by the System */
void Object::removeComponent(u32 type_id)
{
	auto it = comp_list.find(type_id);
	if(it != comp_list.end())
	{
		BaseComponent* comp = it->second;
		comp->setParent(nullptr);
		comp_list.erase(it);
	}
}

BaseComponent* Object::getComponent(u32 type_id)
{
	auto it = comp_list.find(type_id);

	if(it != comp_list.end())
		return it->second;
	else
		return nullptr;
}

void Object::removeAllComponents()
{
	for(auto it = comp_list.begin(); it != comp_list.end(); it++)
	{
		BaseComponent* comp = it->second;
		comp->setParent(nullptr);
	}
}
