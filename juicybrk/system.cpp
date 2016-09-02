#include "system.h"
#include "component.h"

BaseSystem::BaseSystem() : manage_comp(true)
{
}

BaseSystem::~BaseSystem()
{
	if(manage_comp)
	{
		for(auto it = comp_list.begin(); it != comp_list.end(); it++)
		{
			BaseComponent* comp = *it;
			delete comp;
		}
	}
}

void BaseSystem::addComponent(BaseComponent* comp)
{
	comp_list.push_back(comp);
}

void BaseSystem::removeComponent(BaseComponent* comp)
{
	for(auto it = comp_list.begin(); it != comp_list.end(); it++)
	{
		if(*it == comp)
		{
			comp_list.erase(it);
			break;
		}
	}
}

/* Remove Components whose Object has been deleted */
void BaseSystem::garbageCollection()
{
	for(auto it = comp_list.begin(); it != comp_list.end();)
	{
		BaseComponent* comp = *it;
		auto prev_it = it++;
		if(comp->getParent() == nullptr)
		{
			delete comp;
			comp_list.erase(prev_it);
		}
	}
}

void BaseSystem::update()
{
	for(auto it = comp_list.begin(); it != comp_list.end(); it++)
	{
		BaseComponent* comp = *it;
		if(comp->getParent() != nullptr)
		{
			comp->update();
		}
	}
}
