#ifndef HOPE_SAMGLES_TOY_RESOURCE_H
#define HOPE_SAMGLES_TOY_RESOURCE_H

#include <Box2D/Box2D.h>
#include <unordered_set>



static b2Color kResourcesColor[] = {
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 1.0f }
};

enum ResourceType {
	NONE = -1,
	FOOD = 0,
	WATER,
	GOLD,
	ENERGY
};

static char* kResourceTypeNames[] = { "Food", "Water", "Gold", "Energy" };
static ResourceType kResourceTypeMasks[] = { FOOD, WATER, GOLD, ENERGY };
#define RESOURCE_TYPE_ITEM_COUNT 4

static ResourceType kResourceTypePrimaries[] = { FOOD, WATER, ENERGY };
#define RESOURCE_TYPE_PRIMARY_ITEM_COUNT 3


class ResourceSet {
public:
	uint32_t mask;

	ResourceSet() : mask(0) {
	}

	void set(ResourceType type) {
		mask |= (1 << type);
	}

	void set(ResourceType type, bool value) {
		if (value) {
			set(type);
		}
		else {
			unset(type);
		}
	}
	
	void unset(ResourceType type) {
		mask &= 0xFFFFFFFF ^ (1 << type);
	}

	bool has(ResourceType type) {
		return (mask & (1 << type)) != 0;
	}

	bool isEmpty() {
		return mask == 0;
	}
};


typedef std::unordered_set<ResourceType> ResourceTypeSet;

class ResourceMap {
public:
	float resoures[RESOURCE_TYPE_ITEM_COUNT];

	ResourceMap() {
		for (size_t i = 0; i < RESOURCE_TYPE_ITEM_COUNT; i++) {
			resoures[i] = 0.0f;
		}
	}

	void set(ResourceType type, float value) {
		resoures[type] = value;
	}

	float get(ResourceType type) {
		return resoures[type];
	}

	ResourceMap operator+ (ResourceMap const &other) {
		ResourceMap result;

		for (size_t i = 0; i < RESOURCE_TYPE_ITEM_COUNT; i++) {
			result.resoures[i] = resoures[i] + other.resoures[i];
		}

		return result;
	}

	ResourceMap operator- (ResourceMap const &other) {
		ResourceMap result;

		for (size_t i = 0; i < RESOURCE_TYPE_ITEM_COUNT; i++) {
			result.resoures[i] = resoures[i] - other.resoures[i];
		}

		return result;
	}


	ResourceMap& operator+= (const ResourceMap& other)
	{
		*this = *this + other;
		return *this;
	}

	ResourceMap& operator-= (const ResourceMap& other)
	{
		*this = *this - other;
		return *this;
	}

	ResourceTypeSet getUnderPrimarySet(float value) {
		ResourceTypeSet set;

		for (size_t i = 0; i < RESOURCE_TYPE_PRIMARY_ITEM_COUNT; i++) {
			ResourceType type = kResourceTypePrimaries[i];

			if (get(type) <= value) {
				set.insert(type);
			}
		}

		return set;
	}
};



#endif /* HOPE_SAMGLES_AGENT_RESOURCE_H */