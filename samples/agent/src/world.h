#ifndef HOPE_SAMPLES_AGENT_WORLD_H
#define HOPE_SAMPLES_AGENT_WORLD_H

#include "ai/System.h"
#include "action.h"
#include <world/Store.h>

struct WithBody {
	b2Vec2 position;
	b2Body* body;
	float radius;

	explicit WithBody(float radius) : radius(radius) {
		body = NULL;
	}
};

struct Deposit : WithBody {
public:
	ResourceType type;
	float quantity;

	Deposit() :
		WithBody(1.5),
		type(ResourceType::NONE),
		quantity(0){
	}
};

enum GaugeType {
	EAT,
	DRINK,
	SLEEP
};

const char* toString(GaugeType type);

struct AgentAlive : WithBody {
public:
	const char* label;

	std::unordered_map<GaugeType, float> gauges;
	hope::ai::Agent ai;

	Action currentAction;
	
	AgentAlive() :
		WithBody(0.5) {
		gauges[EAT] = 1000.0f;
		gauges[DRINK] = 1000.0f;
		gauges[SLEEP] = 1000.0f;
	}
};

struct AgentCorpse : WithBody {
	const char* label;

	AgentCorpse() :
		WithBody(0.5) {

	}

	void set(const AgentAlive& alive) {
		position = alive.position;
		label = alive.label;
	}
};



#define REGISTER_STORE(CLASS_) \
	::hope::world::Store<CLASS_> store_##CLASS_; \
	template<> CLASS_* allocate<CLASS_>() { return store_##CLASS_.allocate(); } \
	template<> void release<CLASS_>(CLASS_* item) { store_##CLASS_.release(item); }

struct World {
	template< typename T >
	T* allocate();

	template< typename T >
	void release(T* item);

	REGISTER_STORE(AgentAlive);
	REGISTER_STORE(AgentCorpse);
	REGISTER_STORE(Deposit);	

	static World* getInstance() {
		static World* instance = NULL;

		if (instance == NULL) {
			instance = new World();
		}

		return instance;
	}
	
	
	
	Location findNearestDeposit(ResourceType type) const;
	
};


#endif /* HOPE_SAMPLES_AGENT_WORLD_H */