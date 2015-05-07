#include <entry/entry.h>
#include <core/core.h>
#include <console.h>
#include <input/mouse.h>
#include <asset/asset.h>

#include <nvg.h>
#include <vector>
#include <map>
#include <queue>
#include <Box2D/Box2D.h>


#include "resource.h"
#include "ai/System.h"
#include "action.h"
#include <unordered_set>
#include "world.h"


#include "PhysicsSystem.h"

PhysicsSystem* physics;

#include "drawing.h"


static hope::ai::plan::NeedType N_SLEEP;
static hope::ai::plan::NeedType N_DRINK;
static hope::ai::plan::NeedType N_EAT;
static hope::ai::plan::NeedType N_LAZY;

static std::unordered_map<hope::ai::plan::StepIndex, Action> kActionByStepTable;
static hope::ai::System kAiSystem;

void initializeActionTable() {
	hope::ai::plan::StepTable& table = kAiSystem.actionTable;
	
	const hope::ai::condition::Condition * C_PROXIMITY_DEPOSIT_WATER = kAiSystem.createCondition("PROXIMITY_DEPOSIT(WATER)");
	const hope::ai::condition::Condition * C_PROXIMITY_DEPOSIT_FOOD = kAiSystem.createCondition("PROXIMITY_DEPOSIT(FOOD)");
	N_SLEEP = kAiSystem.createNeed("SLEEP");
	N_DRINK = kAiSystem.createNeed("DRINK");
	N_EAT = kAiSystem.createNeed("EAT");
	N_LAZY = kAiSystem.createNeed("LAZY");


	{
		hope::ai::plan::Step aiAction;
		hope::ai::plan::Effect effect;
		hope::ai::condition::Condition condition;

		effect.type = N_DRINK;
		aiAction.effects.push_back(effect);

		aiAction.preconditions.push_back(C_PROXIMITY_DEPOSIT_WATER);

		Action action;
		action.type = CONSUME_ACTION;
		action.ConsumeAction.type = ResourceType::WATER;

		kActionByStepTable.insert(std::unordered_multimap<hope::ai::plan::StepIndex, Action>::value_type(table.add(aiAction), action));
	}

	{
		hope::ai::plan::Step aiAction;
		hope::ai::plan::Effect effect;


		effect.type = N_SLEEP;
		aiAction.effects.push_back(effect);

		Action action;
		action.type = SLEEP_ON_GROUND;

		kActionByStepTable.insert(std::unordered_multimap<hope::ai::plan::StepIndex, Action>::value_type(table.add(aiAction), action));
	}

	{
		hope::ai::plan::Step aiAction;
		hope::ai::plan::Effect effect;


		effect.type = N_LAZY;
		aiAction.effects.push_back(effect);

		Action action;
		action.type = IDLE_ACTION;

		kActionByStepTable.insert(std::unordered_multimap<hope::ai::plan::StepIndex, Action>::value_type(table.add(aiAction), action));
	}


	{
		hope::ai::plan::Step aiAction;
		hope::ai::condition::Condition condition;
		hope::ai::plan::Effect effect;


		effect.type = N_EAT;
		aiAction.effects.push_back(effect);

		aiAction.preconditions.push_back(C_PROXIMITY_DEPOSIT_FOOD);

		Action action;
		action.type = CONSUME_ACTION;
		action.ConsumeAction.type = ResourceType::FOOD;

		kActionByStepTable.insert(std::unordered_multimap<hope::ai::plan::StepIndex, Action>::value_type(table.add(aiAction), action));
	}

	{
		hope::ai::plan::Step aiAction;
		hope::ai::condition::Condition condition;

		aiAction.postconditions.push_back(C_PROXIMITY_DEPOSIT_FOOD);

		Action action;
		action.type = GOTO_DEPOSIT_ACTION;
		action.GoToDepositAction.type = ResourceType::FOOD;

		kActionByStepTable.insert(std::unordered_multimap<hope::ai::plan::StepIndex, Action>::value_type(table.add(aiAction), action));
	}

	{
		hope::ai::plan::Step aiAction;
		hope::ai::condition::Condition condition;

		aiAction.postconditions.push_back(C_PROXIMITY_DEPOSIT_WATER);

		Action action;
		action.type = GOTO_DEPOSIT_ACTION;
		action.GoToDepositAction.type = ResourceType::WATER;

		kActionByStepTable.insert(std::unordered_multimap<hope::ai::plan::StepIndex, Action>::value_type(table.add(aiAction), action));
	}
}


hope::ai::plan::NeedLevel evalNeedLevel(const AgentAlive* agent, float value) {
	if (value > 900.0) {
		return 1000 - 900;
	}
	if (value > 800.0) {
		return 1000 - 800;
	}
	if (value > 750.0) {
		return 1000 - 750;
	}
	if (value > 550.0) {
		return 1000 - 550;
	}
	return 1000;
}

void updateAgentAliveNeeds(AgentAlive *items, size_t length) {
	AgentAlive* item = items;
	AgentAlive* end = (items + length);

	for (; item != end; item++) {
		item->ai.needs[N_DRINK] = evalNeedLevel(item, item->gauges[DRINK]);
		item->ai.needs[N_EAT] = evalNeedLevel(item, item->gauges[EAT]);
		item->ai.needs[N_SLEEP] = evalNeedLevel(item, item->gauges[SLEEP]);
		item->ai.needs[N_LAZY] = 350;
	}
}

void updateAgentAliveNextAction(AgentAlive *agent) {
	World* world = World::getInstance();
	const ::hope::ai::plan::Step* aiAction = kAiSystem.nextStep(agent->ai);

	if (aiAction == NULL) {
		agent->currentAction.type = IDLE_ACTION;
		return;
	}

	const Action& action = kActionByStepTable[aiAction->index];

	if (action.type == GOTO_DEPOSIT_ACTION) {
		agent->currentAction.type = GOTO_ACTION;
		agent->currentAction.GoToAction.location = world->findNearestDeposit(action.GoToDepositAction.type);
	}
	else {
		agent->currentAction = action;
	}
}



























uint32_t lastTime = 0, currentTime, elaspsedTime;
float elaspsedAgentTime = 0; // in hours
float elaspsedAgentTimeAccumulator = 0; // in hours


void updateAgentAliveActionSleepOnGround(AgentAlive *item, float elapsedTime)
{
	float speed = 10.0f;

	float max = 1000.0f - item->gauges[SLEEP];
	float available = speed * elapsedTime;
	float consumed = (max > available) ? available : max;

	item->gauges[SLEEP] += consumed;

	if (consumed < available) {
		item->currentAction.type = IDLE_ACTION;
	}
}

void updateAgentAliveActionGoTo(AgentAlive *item, float elapsedTime)
{
	float speed = 1.0f;

	const GoToAction& action = item->currentAction.GoToAction;
	b2Vec2 dst(action.location.x, action.location.y);
	b2Vec2 velocity = dst - item->position;

	float length = velocity.Normalize();

	if (length < 0.1) {
		item->position = dst;
		item->currentAction.type = IDLE_ACTION;
	}
	else {
		velocity *= (speed * elapsedTime);
		item->position += velocity;
	}

	item->body->SetTransform(item->position, item->body->GetAngle());
}


float aliveConsumeResource(AgentAlive* agent, ResourceType type, float available) {
	float consumed = 0.0f;
	float m, a;

	switch (type) {
	case WATER: {
		m = (1000.0f - agent->gauges[DRINK]);
		consumed = (m > available) ? available : m;
		agent->gauges[DRINK] += consumed;
		break;
	}
	case FOOD: {
		m = (1000.0f - agent->gauges[EAT]);
		consumed = (m > available) ? available : m;
		agent->gauges[EAT] += consumed;
		break;
	}
	}

	return consumed;
}


void updateAgentAliveActionConsume(AgentAlive *item, float elapsedTime)
{
	float speed = 100.0f;
	float allowedQuantity = elapsedTime * speed;
	float consumedQuantity;

	float r = item->radius;
	float x = item->position.x;
	float y = item->position.y;

	b2AABB aabb;

	aabb.lowerBound.Set(x - r, y - r);
	aabb.upperBound.Set(x + r, y + r);

	std::vector<Deposit*> result;

	physics->queryAll<Deposit>(aabb, result);

	if (result.empty()) {
		item->currentAction.type = IDLE_ACTION;
		return;
	}
	else {
		for (auto it = result.begin(); it != result.end(); it++) {
			if ((*it)->type == item->currentAction.ConsumeAction.type) {
				consumedQuantity = aliveConsumeResource(item, (*it)->type, fmin((*it)->quantity, allowedQuantity));
				(*it)->quantity -= consumedQuantity;
				allowedQuantity -= consumedQuantity;
			}
		}

		if (consumedQuantity < allowedQuantity) {
			item->currentAction.type = IDLE_ACTION;
			return;
		}
	}
}





void updateAgentAliveAction(AgentAlive *items, size_t length, float elapsedTime)
{
	World* world = World::getInstance();

	AgentAlive* item = items;
	AgentAlive* end = (items + length);

	for (; item != end; item++) {

		switch (item->currentAction.type) {
		case IDLE_ACTION: {
			updateAgentAliveNextAction(item);
			break;
		}
		case CONSUME_ACTION: {
			updateAgentAliveActionConsume(item, elapsedTime);
			break;
		}
		case GOTO_ACTION: {
			updateAgentAliveActionGoTo(item, elapsedTime);
			break;
		}
		case SLEEP_ON_GROUND: {
			updateAgentAliveActionSleepOnGround(item, elapsedTime);
			break;
		}

		}
	}
}




void killAgentAlive(AgentAlive* agent) {
	AgentCorpse* corpse = World::getInstance()->allocate<AgentCorpse>();

	corpse->set(*agent);
	physics->assign(corpse);
	agent->body->GetWorld()->DestroyBody(agent->body);
	World::getInstance()->release(agent);
}


void updateAgentAliveGauges(AgentAlive *items, size_t length) {
	AgentAlive* item = items;
	AgentAlive* end = (items + length);
	for (; item != end; item++) {

		float eat = item->gauges[EAT] -= 1000.0f / (24.0f * 35.0f);
		float drink = item->gauges[DRINK] -= 1000.0f / (24.0f * 4.0f);
		float sleep = item->gauges[SLEEP] -= 1000.0f / (24.0f * 12.0f);

		if ((eat <= 0.0f) || (drink <= 0.0f) || (sleep <= 0.0f)) {
			killAgentAlive(item);
		}
	}
	World::getInstance()->store_AgentAlive.cleanup();
}


class Application : public hope::entry::Application {


    void onInitialize (void) {

		initializeActionTable();
				
		physics = new PhysicsSystem();

		AgentAlive* agent;
		
		agent = World::getInstance()->allocate<AgentAlive>();
		agent->label = "Adrien";
		agent->position.Set(-5.5f, -5.5f);
		agent->currentAction.type = CONSUME_ACTION;
		agent->currentAction.ConsumeAction.type = FOOD;
		physics->assign(agent);


		agent = World::getInstance()->allocate<AgentAlive>();
		agent->label = "Alan";
		agent->position.Set(10.0f, 10.0f);
		physics->assign(agent);

		agent = World::getInstance()->allocate<AgentAlive>();
		agent->label = "Axel";
		agent->position.Set(-15.0f, 10.0f);
		agent->currentAction.type = GOTO_ACTION;
		agent->currentAction.GoToAction.location.x = 0.0f;
		agent->currentAction.GoToAction.location.y = 0.0f;
		physics->assign(agent);

		Deposit* deposit;

		deposit = World::getInstance()->allocate<Deposit>();
		deposit->position.Set(-5.0f, 0.0f);
		deposit->type = WATER;
		deposit->quantity = 500000.0f;
		physics->assign(deposit);

		deposit = World::getInstance()->allocate<Deposit>();
		deposit->position.Set(-15.0f, -15.0f);
		deposit->type = GOLD;
		deposit->quantity = 500000.0f;
		physics->assign(deposit);

		deposit = World::getInstance()->allocate<Deposit>();
		deposit->position.Set(-5.0f, -5.0f);
		deposit->type = FOOD;
		deposit->quantity = 500000.0f;
		physics->assign(deposit);

    }

	void onRelease (void) {
		delete physics;
    }

	

	void onLoop() {
		World* world = World::getInstance();

		int32_t mx = 0, my = 0;
		int32_t winWidth = 1024, winHeight = 768;
		int blowup = 0;

		hope::input::mouse::getPosition(&mx, &my);
		hope::core::getViewportSize(&winWidth, &winHeight);

		currentTime = hope::core::getTicks();

		elaspsedTime = currentTime - lastTime;

		lastTime = currentTime;

		float e = elaspsedTime / (3600.0f / 15.0f);

		elaspsedAgentTime += e;
		elaspsedAgentTimeAccumulator += e;

		// -------------------------- UPDATE
		if (elaspsedAgentTimeAccumulator > 1.0f) {
			updateAgentAliveGauges(world->store_AgentAlive.pool, world->store_AgentAlive.pool_cursor);
			updateAgentAliveNeeds(world->store_AgentAlive.pool, world->store_AgentAlive.pool_cursor);
			elaspsedAgentTimeAccumulator -= 1.0f;
		}
		updateAgentAliveAction(world->store_AgentAlive.pool, world->store_AgentAlive.pool_cursor, e);
		// -------------------------- UPDATE



		float_t xCenter = winWidth / 2.0f;
		float_t yCenter = winHeight / 2.0f;

		float xMouse = (mx - xCenter) / 10.f;
		float yMouse = (my - yCenter) / -10.f;

		physics->queryMouse(xMouse, yMouse);

		physics->step();


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		::hope::nanovg::beginFrame();

		// ---------------------------- DRAW
		drawDeposit(world->store_Deposit.pool, world->store_Deposit.pool_cursor);
		drawAgentAlive(world->store_AgentAlive.pool, world->store_AgentAlive.pool_cursor);
		drawAgentCorpse(world->store_AgentCorpse.pool, world->store_AgentCorpse.pool_cursor);
		// ---------------------------- DRAW

		nvgBeginStackTextLeft(); {
			nvgStackText("%.2f hours", elaspsedAgentTime);
		}

		nvgBeginStackTextRight(); {
			drawSelectedEntityPanel();

			drawAgentAlive(world->store_AgentAlive.pool);
		}
		
		::hope::nanovg::endFrame();
    }


   void onResize(int width, int height) {
        glViewport(0, 0, width, height);
    }

    void onGLInitialize() {
		if (!::hope::nanovg::initialize()) {
			exit(42);
		}

		::hope::nanovg::loadFont("nanovg/Roboto-Regular.ttf", "sans");
    }

    void onGLRelease(void) {
		::hope::nanovg::release();
    }

};


namespace hope {
	namespace entry {

		hope::entry::Application* createApplication() {
			return new ::Application();
		}

	} /* namespace entry */
} /* namespace hope */

