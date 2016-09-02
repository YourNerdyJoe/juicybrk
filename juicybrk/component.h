#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include "types.h"
#include "system.h"

class Object;

class BaseComponent
{
protected:
	u32 id;
	Object* parent;

	inline void setParent(Object* p) {
		parent = p;
	}

public:
	BaseComponent();
	virtual ~BaseComponent();

	virtual void update() = 0;

	inline Object* getParent() {
		return parent;
	}

	friend Object;
};

template <class T>
class Component : public BaseComponent
{
protected:
	static BaseSystem* system;

public:
	static const u32 type_id;

	static inline void registerSystem(BaseSystem* sys) {
		system = sys;
	}
	static inline BaseSystem* getSystem() {
		return system;
	}

	Component() {
		id = T::type_id;
		system->addComponent(this);
	}

	virtual ~Component() {
		//system->removeComponent(this);
	}
};

template <class T>
BaseSystem* Component<T>::system = nullptr;

template <class T>
const u32 Component<T>::type_id = reinterpret_cast<u32>(&Component<T>::type_id);

#endif
