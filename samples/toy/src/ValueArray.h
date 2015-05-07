#ifndef HOPE_SAMPLES_TOY_VALUEARRAY_H
#define HOPE_SAMPLES_TOY_VALUEARRAY_H

#include <map>

#include <grid/Location.h>
#include "./EntityManager.h"
#include "./ItemBag.h"

struct BaseValue {
	virtual bool cast_ItemId(ItemId &result) const = 0; // { return false; }
	virtual bool cast_EntityId(EntityId &result) const = 0; // { return false; }
	virtual BaseValue* newClone() const = 0;
	virtual ~BaseValue() {};
};

template <typename T>
struct Value : public BaseValue {};

template <>
struct Value<ItemId> : public BaseValue {
	ItemId value;

	Value(const ItemId& value) : value(value) {}
	
	bool cast_ItemId(ItemId &result) const { result = value; return true; }
	bool cast_EntityId(EntityId &result) const { return false; }

	BaseValue* newClone() const { return new Value<ItemId>(value); }
};

template <>
struct Value<EntityId> : public BaseValue {
	EntityId value;

	Value(const EntityId& value) : value(value) {}
	
	bool cast_EntityId(EntityId &result) const { result = value;  return true; }
	bool cast_ItemId(ItemId &result) const { return false; }

	BaseValue* newClone() const { return new Value<EntityId>(value); }
};

struct ValueArray {

	std::vector < BaseValue* > values;

	ValueArray() {}

	ValueArray(const ValueArray& other) {
		for (auto it = other.values.begin(); it != other.values.end(); ++it) {
			values.push_back((*it)->newClone());
		}
	}
	
	~ValueArray() {
		for (auto it = values.begin(); it != values.end(); ++it) {
			delete (*it);
		}
		values.clear();
	}

	void push(const BaseValue& value) {
		BaseValue *clone = value.newClone();

		values.push_back(clone);
	}

	const BaseValue* get(size_t index) const {
		return values.at(index);
	}

};

#endif /* HOPE_SAMPLES_TOY_VALUEARRAY_H */