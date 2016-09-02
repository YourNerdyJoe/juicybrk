#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <list>
#include "types.h"

class BaseComponent;

class BaseSystem
{
protected:
	std::list<BaseComponent*> comp_list;
	u32 id;
	bool manage_comp;	//is responsible for deleting components

public:
	BaseSystem();
	~BaseSystem();

	void addComponent(BaseComponent* comp);
	void removeComponent(BaseComponent* comp);
	void garbageCollection();

	virtual void update();
};

template <class T>
class System : public BaseSystem
{
public:
	System() : BaseSystem() {
		id = T::type_id;
	}

	~System() {}
};

#endif
