#ifndef HOPE_SAMGLES_AGENT_PHYSICSSYSTEM_H
#define HOPE_SAMGLES_AGENT_PHYSICSSYSTEM_H

#include <Box2D/Box2D.h>

#define REGISTER_TYPE(CLASS_, TYPE_) \
	template<> CLASS_* getSelected<CLASS_>() const { \
		return getSelected<CLASS_, TYPE_>(); \
	} \
	template<> void assign<CLASS_>(CLASS_* entity) { \
		assign<CLASS_, TYPE_>(entity); \
	} \
	template<> void queryAll(const b2AABB& aabb, std::vector< CLASS_* >& result) { \
		queryAll<CLASS_, TYPE_>(aabb, result); \
	} \
	template<> CLASS_* query(const b2AABB& aabb) { \
		return query<CLASS_, TYPE_>(aabb); \
	} 

class PhysicsSystem  {

	struct BodyUserData {
		enum Type {
			NONE = 0,
			AGENT_ALIVE,
			AGENT_CORPSE,
			DEPOSIT
		};

		Type type;
		void* data;

		BodyUserData(Type type, void* data) : type(type), data(data) {
		}
	};

	template < typename T, BodyUserData::Type Ty>
	class WorldQueryCallback : public b2QueryCallback {
	public:
		std::vector< T* >& selected;

		WorldQueryCallback(std::vector< T* >& selected) :
			selected(selected) {
		}

		bool ReportFixture(b2Fixture* fixture) {
			BodyUserData* data = (BodyUserData*)fixture->GetUserData();

			if (data != NULL && data->type == Ty) {
				selected.push_back((T*)data->data);
			}
			return true;
		}
	};

	class MouseQueryCallback : public b2QueryCallback {
	public:
		int32_t counter;
		BodyUserData* selected;

		MouseQueryCallback() : selected(NULL) {
		}

		bool ReportFixture(b2Fixture* fixture) {
			BodyUserData* data = (BodyUserData*)fixture->GetUserData();
			if (data != NULL) {
				selected = data;
			}
			counter++;
			return true;
		}
	};

	b2World* world;
	std::vector<BodyUserData* > vectorBodyUserData;
	MouseQueryCallback mouseQueryCallback;

public:
	PhysicsSystem() {

		b2Vec2 gravity(0.0f, 0.0f);
		world = new b2World(gravity);

		world->SetAllowSleeping(false);

	}

	~PhysicsSystem(){
		for (auto it = vectorBodyUserData.begin(); it != vectorBodyUserData.end(); ++it) {
			delete (*it);
		}
		delete world;
	}



	template< typename T, BodyUserData::Type Ty>
	T* getSelected() const {
		if (mouseQueryCallback.selected == NULL) {
			return NULL;
		}
		if (mouseQueryCallback.selected->type != Ty) {
			return NULL;
		}
		return (T*)mouseQueryCallback.selected->data;
	}

	template< typename T >
	T* getSelected() const;


	b2Body* createCicleBody(BodyUserData* userData, const b2Vec2& position, float radius) {

		b2CircleShape circleShape;
		circleShape.m_radius = radius;

		b2BodyDef circleBodyDef;
		circleBodyDef.type = b2_staticBody;
		//		circleBodyDef.type = b2_dynamicBody;
		circleBodyDef.position = position;

		vectorBodyUserData.push_back(userData);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.userData = userData;

		b2Body* circleBody = world->CreateBody(&circleBodyDef);
		circleBody->CreateFixture(&fixtureDef);

		return circleBody;
	}

	template< typename T, BodyUserData::Type Ty >
	void assign(T* agent) {
		agent->body = createCicleBody(new BodyUserData(Ty, agent), agent->position, agent->radius);
	}

	template< typename T >
	void assign(T* agent);

	// -------------
	
	template< typename T, BodyUserData::Type Ty >
	void queryAll(const b2AABB& aabb, std::vector< T* >& result) {
		WorldQueryCallback<T, Ty> callback(result);
		
		world->QueryAABB(&callback, aabb);
	}

	template< typename T >
	void queryAll(const b2AABB& aabb, std::vector< T* >& result);

	// -------------

	template< typename T, BodyUserData::Type Ty >
	T* query(const b2AABB& aabb) {
		std::vector<T*>  result;

		queryAll(aabb, result);

		if (result.empty()){
			return NULL;
		}

		return result.at(0);
	}

	template< typename T >
	T* query(const b2AABB& aabb);

	// -------------

	void queryMouse(float xMouse, float yMouse) {
		b2AABB aabb;
		//		::hope::console::log("%f , %f", xMouse, yMouse);

		aabb.lowerBound.Set(xMouse - 0.5f, yMouse - 0.5f);
		aabb.upperBound.Set(xMouse + 0.5f, yMouse + 0.5f);

		mouseQueryCallback.counter = 0;
		mouseQueryCallback.selected = NULL;
		world->QueryAABB(&mouseQueryCallback, aabb);
	}
	

	void step() {
		//		::hope::console::log("%i", elaspsedTime);

		float32 timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world->Step(timeStep, velocityIterations, positionIterations);
	}


	REGISTER_TYPE(AgentAlive, BodyUserData::Type::AGENT_ALIVE);
	REGISTER_TYPE(AgentCorpse, BodyUserData::Type::AGENT_CORPSE);
	REGISTER_TYPE(Deposit, BodyUserData::Type::DEPOSIT);
};


#endif /* HOPE_SAMGLES_AGENT_PHYSICSSYSTEM_H */