#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "transform.h"
#include "component.h"
#include <map>

class Object : public Transform
{
protected:
	std::map<u32,BaseComponent*> comp_list;

public:
	Object();
	Object(Transform* parent);
	~Object();

	BaseComponent* addComponent(BaseComponent* comp);
	void removeComponent(BaseComponent* comp);
	void removeComponent(u32 type_id);
	BaseComponent* getComponent(u32 type_id);

	void removeAllComponents();

	template <class T> inline T* addComponent() {
		return (T*)addComponent(new T);
	}
	template <class T> inline void removeComponent() {
		removeComponent(T::type_id);
	}
	template <class T> inline T* getComponent() {
		return (T*)getComponent(T::type_id);
	}
};

#endif
