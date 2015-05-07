#include "Application.h"

#include <entry/entry.h>
#include <core/core.h>
#include <console.h>
#include <input/mouse.h>
#include <asset/asset.h>
#include <asset/asset.h>
#include <nvg.h>

#include <unordered_set>
#include <Box2D/Box2D.h>
#include <GLES2/gl2.h>

#include <vector>
#include <queue>
#include <map>

#include <grid/FloodFillQuery.h>
#include <grid/Pathfinder.h>


#include "./TileIndexTable.h"

#include <gles2/Framebuffer.h>


#include "./ItemTable_generated.h"
#include "./ConstructionRecipeTable_generated.h"

#include <functional>

#include "./Task.h"

#include "./systems/TheGrid.h"

#include "./Entities.h"
#include "./systems/Task.h"
#include "./systems/Action.h"
#include "./systems/task/Construction.h"

#include "./systems/Deposit.h"

#include "./factories/storage.h"
#include "./factories/agent.h"

#include "./ui/Canvas.h"
#include "./ui/StorageList.h"

hope::ui::Canvas uiCanvas(1);


ComponentManager<GoToComponent> Components::manager_GoToComponent;
ComponentManager<ItemBagComponent> Components::manager_ItemBagComponent;
ComponentManager<LocationComponent> Components::manager_LocationComponent;
ComponentManager<AgentComponent> Components::manager_AgentComponent;
ComponentManager<StorageComponent> Components::manager_StorageComponent;
ComponentManager<AttachToAgentComponent> Components::manager_AttachToAgentComponent;
ComponentManager<DoableComponent> Components::manager_DoableComponent;
ComponentManager<PlanComponent> Components::manager_PlanComponent;
ComponentManager<LaborComponent> Components::manager_LaborComponent;
ComponentManager<DepositComponent> Components::manager_DepositComponent;

ComponentManager<TaskComponent> Components::manager_TaskComponent;
ComponentManager<ConstructionTaskComponent> Components::manager_ConstructionTaskComponent;
ComponentManager<ItemTransfertTaskComponent> Components::manager_ItemTransfertTaskComponent;
ComponentManager<ConstructTaskComponent> Components::manager_ConstructTaskComponent;
ComponentManager<ExtractTaskComponent> Components::manager_ExtractTaskComponent;


ComponentManager<ActionComponent> Components::manager_ActionComponent;
ComponentManager<GoToAdjacentActionComponent> Components::manager_GoToAdjacentActionComponent;
ComponentManager<ExtractActionComponent> Components::manager_ExtractActionComponent;
ComponentManager<ItemPickActionComponent> Components::manager_ItemPickActionComponent;
ComponentManager<ConstructActionComponent> Components::manager_ConstructActionComponent;
ComponentManager<ItemGiveActionComponent> Components::manager_ItemGiveActionComponent;




typedef std::unordered_map<int32_t, const hope::samples::toy::fbs::Item*> ItemTable;


static ItemTable kItemTable;

static hope::ai::plan::NeedType N_SLEEP;
static hope::ai::plan::NeedType N_DRINK;
static hope::ai::plan::NeedType N_EAT;
static hope::ai::plan::NeedType N_LAZY;

static uint32_t kAccuTime = 0;
static uint32_t kUIAccuTime = 0;









enum MouseMode {
	MOUSE_MODE_NONE = 0,
	MOUSE_MODE_WALL,
	MOUSE_MODE_DESTROY,
	MOUSE_MODE_FLOOR,
	MOUSE_MODE_CANCEL,
	MOUSE_MODE_DOOR,
	MOUSE_MODE_ROOM
};


const char* toString(MouseMode mode){
	switch (mode){

	case MouseMode::MOUSE_MODE_NONE:
		return "<none>";
		break;

	case MouseMode::MOUSE_MODE_WALL:
		return "Wall";
		break;

	case MouseMode::MOUSE_MODE_DESTROY:
		return "Destroy";
		break;

	case MouseMode::MOUSE_MODE_FLOOR:
		return "Floor";
		break;

	case MouseMode::MOUSE_MODE_ROOM:
		return "Room";
		break;
	case MouseMode::MOUSE_MODE_DOOR:
		return "Door";
		break;

	case MouseMode::MOUSE_MODE_CANCEL:
		return "Cancel";
		break;


	default:
		return "<unkown>";
	}
}

static MouseMode kMouseMode = MOUSE_MODE_NONE;












void cancelConstructionCallback(int32_t x, int32_t y) {
	systems::task::Construction.cancelConstruction(x, y);
}

void floorConstructionCallback(int32_t x, int32_t y) {
	systems::task::Construction.beginFloorConstruction(x, y);
}

void wallConstructionCallback(int32_t x, int32_t y)  {
	systems::task::Construction.beginWallConstruction(x, y);
}




/*

class RoomFloodFillCallback : public hope::grid::FloodFillQuery::Callback {
public:
	bool isOpen(int32_t x, int32_t y) const {
		return TheGrid::kToyGrid->at(x, y)->type == FLOOR;
	}
};



static std::vector<Room*> kRooms;

struct ApplyRoomCallback : hope::grid::Callback {
	RoomCell room;

	void iterateCell(int32_t x, int32_t y)  const {
		const Room* oldRoom = TheGrid::kRoomGrid->get(x, y).room;

		TheGrid::kRoomGrid->set(x, y, room);
		if (room.room != NULL) {
			room.room->airtight &= (TheGrid::kToyGrid->at(x + 1, y)->type != VOID)
				&& (TheGrid::kToyGrid->at(x - 1, y)->type != VOID)
				&& (TheGrid::kToyGrid->at(x, y + 1)->type != VOID)
				&& (TheGrid::kToyGrid->at(x, y - 1)->type != VOID);
			room.room->cell_count++;
		}
	}

};

Room* findRoom(const hope::grid::Location& location) {
	const RoomGrid::Cell& cell = TheGrid::kRoomGrid->get(location);

	return cell.room;
}

void updateRooms() {
	ApplyRoomCallback cb;
	RoomFloodFillCallback ffcb;

	for (auto it = kRooms.begin(); it != kRooms.end(); ++it) {
		delete (*it);
	}

	kRooms.clear();

	hope::grid::FloodFillQuery query(TheGrid::kGrid->width, TheGrid::kGrid->height, ffcb);

	std::vector<Room*> newRooms;

	bool test = true;
	while (test) {
		cb.room.room = new Room();
		cb.room.room->cell_count = 0;
		cb.room.room->airtight = true;
		cb.room.room->o2 = 0;

		test = query.findFirstUnvisitedArea(cb);
		if (!test) {
			delete cb.room.room;
		}
		else {
			if (cb.room.room->airtight) {
				cb.room.room->o2 = 33 * cb.room.room->cell_count;
			}
			kRooms.push_back(cb.room.room);
		}
	}
}


struct ApplyVoidCallback : hope::grid::Callback {

	void iterateCell(int32_t x, int32_t y) const {
		RoomCell* cell = TheGrid::kRoomGrid->find(x, y);
		if (cell != NULL){
			cell->room->o2 = 0;
		}
	}

};
*/

/*
class VoidFloodFillCallback : public hope::grid::FloodFillQuery::Callback {
public:
	bool isOpen(int32_t x, int32_t y) const {
		return TheGrid::kGrid->isOpen(x, y);
	}
};


void updateVoid() {
	ApplyVoidCallback cb;
	VoidFloodFillCallback ffcb;

	hope::grid::FloodFillQuery query(TheGrid::kGrid->width, TheGrid::kGrid->height, ffcb);
	query.queryFloodFill(0, 0, cb);
}
*/




TileIndexTable kTileIndexTable;




void Application::BeginCancelConstructionCommand::execute() {
	kMouseMode = MOUSE_MODE_CANCEL;
}

void Application::BeginFloorConstructionCommand::execute() {
	kMouseMode = MOUSE_MODE_FLOOR;
}

void Application::BeginWallConstructionCommand::execute() {
	kMouseMode = MOUSE_MODE_WALL;
}

void Application::BeginRoomConstructionCommand::execute() {
	kMouseMode = MOUSE_MODE_ROOM;
}




void initializeGrid() {
	systems::TheGrid()->initialize(100, 100);
	
	systems::task::Construction.initialize(100, 100);
	

	ItemCell item;

	item.items.setItemQuantity(849867, 10);

	systems::TheGrid()->kItemGrid->set(34, 53, item);
	
	systems::TheGrid()->setRoom(15, 15, 25, 25);
	systems::TheGrid()->setRoom(5, 5, 20, 20);

	systems::TheGrid()->setRoom(39, 30, 10, 10);

	systems::TheGrid()->setRoom(51, 51, 10, 10);


	systems::TheGrid()->setDoor(20, 24, false, false);
	systems::TheGrid()->setDoor(24, 20, true, true);
	systems::TheGrid()->setDoor(24, 18, false, true);
	systems::TheGrid()->setDoor(39, 34, false, false);
	systems::TheGrid()->setDoor(48, 34, false, false);
	
	
	systems::TheGrid()->setWall(99, 99);
	systems::TheGrid()->setWall(49, 49);
	
	// FloorConstructionCallback fcb;
	// WallConstructionCallback scb;

	/*
	kGrid->queryRect(43, 18, 10, 10, 1, &fcb, &scb);
	kGrid->queryRect(29, 49, 10, 10, 1, &fcb, &scb);
	kGrid->queryRect(10, 43, 10, 10, 1, &fcb, &scb);
	*/

	// TheGrid::kGrid->queryRect(10, 43, 3, 3, 1, &fcb, &scb);

	systems::TheGrid()->updateNavigationGroups();

	systems::TheGrid()->kToyGrid->queryFillRect(10, 43, 1, 1, &floorConstructionCallback);

//	updateRooms();
}



void initializeEntities() {

	// explodeEntity_ConstructionTask(*TheGrid::kTaskPool, 69);
	// TheGrid::kTaskPool->sortHeadersByLevelAndPriority();

	factories::agent::create("Adrien", hope::grid::Location(20, 20));
	factories::agent::create("Bernard", hope::grid::Location(22, 22));
	factories::agent::create("Alan", hope::grid::Location(23, 23));
	factories::agent::create("Axel", hope::grid::Location(23, 20));
	factories::agent::create("Louis", hope::grid::Location(23, 21));


	EntityId id_RawIron;

	{
		EntityId id = factories::storage::create(hope::grid::Location(35, 35));

		ItemBag& items = Components::get<ItemBagComponent>(id)->items;
		items.setItemQuantity(849867, 10000);
		items.setItemQuantity(728974, 10000);

		ItemBag& requests = Components::get<StorageComponent>(id)->request_quantities;

		requests.setItemQuantity(987546, 500); // "Raw Carbon"
		requests.setItemQuantity(798265, 500); // "Raw Water"
		requests.setItemQuantity(952366, 500); // "Raw Iron"
		requests.setItemQuantity(9654, 500); // "Raw Aluminum"
		requests.setItemQuantity(982, 500); // "Raw Gold"

		
		
		ui::StorageList::Props sl_p;
		sl_p.storage_id = id;
		hope::asset::Asset asset_ItemTable = hope::asset::get("ItemTable.json(flatc)");
		sl_p.table = hope::samples::toy::fbs::GetItemTable(asset_ItemTable.pointer);

		// hope::core::Tick begin = hope::core::getTicks();

		hope::ui::ElementId e = uiCanvas.appendChildToRoot<ui::StorageList>(sl_p);

		// hope::console::log("appendChildToRoot %dms ", hope::core::getTicks() - begin);
	}

	{
		EntityId id = systems::Deposit.create(hope::grid::Location(60, 40), 987546);; // Raw Carbon

		auto &q = Components::get<DepositComponent>(id)->item_quantities;
		q.push_back(1000);
	}

	{
		EntityId id = systems::Deposit.create(hope::grid::Location(60, 20), 952366); // Raw Iron

		auto &q = Components::get<DepositComponent>(id)->item_quantities;
		q.push_back(1000);

		id_RawIron = id;
	}

	{
		EntityId id = factories::agent::create("Guillaume", hope::grid::Location(19, 19));

		/*	
		Components::attach<ActionComponent>(id);
		auto g = Components::attach<GoToAdjacentActionComponent>(id);

		g->to_id = id_RawIron;
		*/
	}

}

hope::grid::PathFinder* gPathFinder = NULL;

void Application::onInitialize(void) {

	hope::asset::Asset asset_ConstructionRecipeTable = hope::asset::get("ConstructionRecipeTable.json(flatc)");
	systems::task::Construction.loadConstructionRecipeTable(asset_ConstructionRecipeTable);

	hope::asset::Asset asset_ItemTable = hope::asset::get("ItemTable.json(flatc)");
	const hope::samples::toy::fbs::ItemTable* table_ItemTable = hope::samples::toy::fbs::GetItemTable(asset_ItemTable.pointer);

	for (auto it = table_ItemTable->items()->begin(); it != table_ItemTable->items()->end(); ++it) {
		kItemTable.insert(ItemTable::value_type(it->id(), *it));
	}


	defaultMapping.bind(hope::input::keyboard::KEY_Q, this->createCommad<BeginWallConstructionCommand>());
	defaultMapping.bind(hope::input::keyboard::KEY_W, this->createCommad<BeginFloorConstructionCommand>());
	defaultMapping.bind(hope::input::keyboard::KEY_C, this->createCommad<BeginCancelConstructionCommand>());
	defaultMapping.bind(hope::input::keyboard::KEY_R, this->createCommad<BeginRoomConstructionCommand>());

	hope::input::keyboard::enableMapping(&defaultMapping);

	initializeGrid();



	
	kTileIndexTable.initializeFromAssets(hope::asset::get("tiles.indexes.bin"));


	initializeEntities();

//	initializePlanDefinitionNetwork(systems::Task.kPlanNetwork);

	
	// hope::grid::Location begin(10, 43);
	// hope::grid::Location end(20, 20);

		hope::grid::Location begin(20, 20);
		hope::grid::Location end(10, 43);
/*
	{
		auto beginTicks = hope::core::getTicks();
		for (int i = 0; i < 10; i++) {
			hope::grid::PathFinder pf(systems::TheGrid()->bounds, systems::TheGrid()->isCellOpenCallback);
			pf.find(begin, end);
		}
		hope::console::log("PathFinder::find x 10 : %d", hope::core::getTicks() - beginTicks);
	}

	{
		auto beginTicks = hope::core::getTicks();
		for (int i = 0; i < 10; i++) {
			hope::grid::PathFinder_blob_v1 pf(systems::TheGrid()->bounds, systems::TheGrid()->isCellOpenCallback);
			pf.find(begin, end);
		}
		hope::console::log("PathFinder_blob_v1::find x 10 : %d", hope::core::getTicks() - beginTicks);
	}

	{
		auto beginTicks = hope::core::getTicks();
		for (int i = 0; i < 10; i++) {
			hope::grid::PathFinder_blob_v2 pf(systems::TheGrid()->bounds, systems::TheGrid()->isCellOpenCallback);
			pf.find(begin, end);
		}
		hope::console::log("PathFinder_blob_v2::find x 10 : %d", hope::core::getTicks() - beginTicks);
	}
	
	exit(45);
	
	*/
	gPathFinder = new hope::grid::PathFinder(systems::TheGrid()->bounds, systems::TheGrid()->isCellOpenCallback);
	gPathFinder->find(begin, end);


	int32_t winWidth = 1024, winHeight = 768;
	hope::core::getViewportSize(&winWidth, &winHeight);

	uiCanvas.setRootSize(winWidth, winHeight);


	
}





void Application::onRelease(void) {
}

void applyMouseMode(MouseMode mode, const hope::grid::AABox& box) {
	switch (mode)
	{

	case MOUSE_MODE_NONE: {
		break;
	}
	case MOUSE_MODE_ROOM: {

		systems::TheGrid()->kToyGrid->queryRect(box.xMin, box.yMin, box.width() + 1, box.height() + 1, 1, floorConstructionCallback, wallConstructionCallback);
//		updateRooms();
//		updateVoid();
		break;
	}

	case MOUSE_MODE_WALL: {
		

		systems::TheGrid()->kToyGrid->queryFillRect(box.xMin, box.yMin, box.width() + 1, box.height() + 1, wallConstructionCallback);

		// TheGrid::kTaskPool->sortHeadersByLevelAndPriority();

//		updateRooms();
//		updateVoid();
		break;
	}
	case MOUSE_MODE_FLOOR: {

		systems::TheGrid()->kToyGrid->queryFillRect(box.xMin, box.yMin, box.width() + 1, box.height() + 1, floorConstructionCallback);

		// TheGrid::kTaskPool->sortHeadersByLevelAndPriority();

//		updateRooms();
//		updateVoid();

		break;
	}
	case MOUSE_MODE_CANCEL: {

		systems::TheGrid()->kToyGrid->queryFillRect(box.xMin, box.yMin, box.width() + 1, box.height() + 1, cancelConstructionCallback);

//		updateRooms();
//		updateVoid();

		break;
	}
	default:
		break;
	}
}



void DepositComponent_foreach_updateRenderer(TileRenderer& gridRenderer, DepositComponent* component, EntityId agent_id) {
	auto location = Components::get<LocationComponent>(agent_id);

	uint8_t tileIndex;

	switch (component->item_id) {
	
	case 798265: { // Raw Water
		tileIndex = (0 * 16) + 12;
		break;
	}
	case 987546: { // Raw Carbon
		tileIndex = (1 * 16) + 12;
		break;
	}
	case 982: { // Raw Gold
		tileIndex = (2 * 16) + 12;
		break;
	}
	case 9654: { // Raw Aluminum
		tileIndex = (3 * 16) + 12;
		break;
	}
	case 952366: { // Raw Iron
		tileIndex = (4 * 16) + 12;
		break;
	}
	default:
		tileIndex = 0;
	}

	if (component->item_quantities.size() == 0) {
		return;
	}

	ItemQuantity q = component->item_quantities[0];

	if (tileIndex != 0) {
		if (q < 2000) {
			tileIndex += (q / 500) - 1;
		}
		else {
			tileIndex += 3;
		}
	}

	gridRenderer.set(location->position.x, location->position.y, tileIndex);
}


void AgentComponent_foreach_updateRenderer(TileRenderer& gridRenderer, AgentComponent* agent_c, EntityId agent_id) {
	auto location = Components::get<LocationComponent>(agent_id);

	gridRenderer.set(location->position.x, location->position.y, 253);
}


void StoreComponent_foreach_updateRenderer(TileRenderer& gridRenderer, StorageComponent* agent_c, EntityId agent_id) {
	auto location = Components::get<LocationComponent>(agent_id);

	gridRenderer.set(location->position.x, location->position.y, (4 * 16) + 12);
}

void ConstructionTaskComponent_foreach_updateRenderer(TileRenderer& gridRenderer, ConstructionTaskComponent* ctc, EntityId task_id) {
	auto location = Components::get<LocationComponent>(task_id);

	switch (ctc->recipe->id()) {
	case 353441: {// Wall
		gridRenderer.set(location->position.x, location->position.y, 0 + (16 * 11));
		break;
	}
	case 574164: { // Floor
		gridRenderer.set(location->position.x, location->position.y, 1 + (16 * 11));
		break;
	}
	}
}



uint8_t toTileIndex(int32_t x, int32_t y) {
	return kTileIndexTable.get(systems::TheGrid()->getCellType(x, y),
		systems::TheGrid()->getCellType(x, y - 1),
		systems::TheGrid()->getCellType(x + 1, y - 1),
		systems::TheGrid()->getCellType(x + 1, y),
		systems::TheGrid()->getCellType(x + 1, y + 1),
		systems::TheGrid()->getCellType(x, y + 1),
		systems::TheGrid()->getCellType(x - 1, y + 1),
		systems::TheGrid()->getCellType(x - 1, y),
		systems::TheGrid()->getCellType(x - 1, y - 1)
		);
}

void Application::updateRenderer() {
	uint8_t tileIndex;

	int32_t x, y;
	const ToyCell* c;
	hope::grid::Location location;

	for (x = 0; x < systems::TheGrid()->kToyGrid->width; x++) {
		for (y = 0; y < systems::TheGrid()->kToyGrid->height; y++) {
			location.set(x, y);
			c = systems::TheGrid()->kToyGrid->at(x, y);

			switch (c->type) {
			case CellType::WALL: {

				tileIndex = 0;// toTileIndex(x, y);

				break;
			}
			case CellType::FLOOR: {
				const RoomCell& roomCell = systems::TheGrid()->kRoomGrid->get(x, y);

				if ((roomCell.room != NULL) && (roomCell.room->o2 > 0)) {
					// floor avec o2
				}
				else {
					// floor sans 02
				}

				tileIndex = toTileIndex(x, y);

				break;
			}
			case CellType::VOID: {
				tileIndex = 255;
				break;
			}
			case CellType::DOOR: {

				const DoorCell* cell = systems::TheGrid()->kDoorGrid->find(location);

				tileIndex = 3 + (16 * 1); // close unlock

				if (cell != NULL) {
					if (!cell->isClose) {
						tileIndex = 3 + (16 * 3); // open lock & unlock
					}
					else if (cell->isLocked) {
						tileIndex = 3 + (16 * 2); // close lock
					}
				}

				break;
			}
			default:
				tileIndex = 0;
			}


			gridRenderer.set(x, y, tileIndex);
		}
	}



	std::function <void(ConstructionTaskComponent*, EntityId)> f0 = std::bind(ConstructionTaskComponent_foreach_updateRenderer, gridRenderer, std::placeholders::_1, std::placeholders::_2);
	Components::foreach<ConstructionTaskComponent>(f0);

	std::function <void(StorageComponent*, EntityId)> f2 = std::bind(StoreComponent_foreach_updateRenderer, gridRenderer, std::placeholders::_1, std::placeholders::_2);
	Components::foreach<StorageComponent>(f2);


	std::function <void(AgentComponent*, EntityId)> f1 = std::bind(AgentComponent_foreach_updateRenderer, gridRenderer, std::placeholders::_1, std::placeholders::_2);
	Components::foreach<AgentComponent>(f1);

	std::function <void(DepositComponent*, EntityId)> f3 = std::bind(DepositComponent_foreach_updateRenderer, gridRenderer, std::placeholders::_1, std::placeholders::_2);
	Components::foreach<DepositComponent>(f3);

	gridRenderer.commit();
}

void nvgDrawMenuText(float x, float y, const char* shortcut, const char* title, bool isActive) {
	if (isActive) {
		nvgText(x, y, "[%s: %s]", shortcut, title);
	}
	else {
		nvgText(x, y, "%s: %s", shortcut, title);
	}
}


uint32_t lastTime = 0, currentTime, elaspsedTime;

/*
static bool kDragInProgress = false;

static float kDragStartX = 0.f;
static float kDragStartY = 0.f;
*/




hope::input::mouse::DragAndDrop kDnDView(::hope::input::mouse::ButtonIndex::BOUTON_MIDDLE);
hope::input::mouse::DragAndDrop kDnDSelection(::hope::input::mouse::ButtonIndex::BOUTON_LEFT);


static float kRendererOffsetX = 0.f;
static float kRendererOffsetY = 0.f;

static bool kSelectionInProgress = false;

static hope::grid::AABox kSelectionBox;
static hope::grid::Location kSelectionStartLocation;





void nvgStackTextTaskDetail(EntityId id) {
	auto task = Components::find<ConstructionTaskComponent>(id);

	if (task == NULL) {
		return;
	}

	auto bag = Components::get<ItemBagComponent>(id);
	auto labor = Components::get<LaborComponent>(id);

	nvgStackText("=== Task #%d construction ===", id);
	nvgStackText("recipe: %s", task->recipe->label()->c_str());
	nvgStackText("labor: %d / %d", labor->labor, task->recipe->labor());
	nvgStackText("== items ==");
	for (auto it = task->recipe->items()->begin(); it != task->recipe->items()->end(); ++it){
		int32_t quantity = bag->items.getItemQuantity(it->item_id());
		nvgStackText("%s: %d / %d", kItemTable[it->item_id()]->label()->c_str(), quantity, it->quantity());
	}
	nvgStackText("=============");
}


void StorageComponent_stackTextDetail_mouseLocation(const hope::grid::Location& mouseLocation, StorageComponent* c, EntityId id) {
	auto loc = Components::find<LocationComponent>(id);

	if (loc == NULL) {
		return;
	}

	if (loc->position != mouseLocation){
		return;
	}

	auto bag = Components::find<ItemBagComponent>(id);

	nvgStackText("==== Storage #%d ====", id);
	nvgStackText("==== items %d/%d ====", bag->items.getTotalQuantity(), c->max);

	for (auto it = c->request_quantities.items.begin(); it != c->request_quantities.items.end(); ++it){
		int32_t quantity = bag->items.getItemQuantity(it->first);
		nvgStackText("%s: %d / %d", kItemTable[it->first]->label()->c_str(), quantity, it->second);
	}

	nvgStackText("=============");
}

void DepositComponent_stackTextDetail_mouseLocation(const hope::grid::Location& mouseLocation, DepositComponent* c, EntityId id) {
	auto loc = Components::find<LocationComponent>(id);

	if (loc == NULL) {
		return;
	}

	if (loc->position != mouseLocation){
		return;
	}

	nvgStackText("==== Deposit \"%s\" #%d ====", kItemTable[c->item_id]->label()->c_str(), id);

	for (auto it = c->item_quantities.begin(); it != c->item_quantities.end(); ++it){
		nvgStackText("%d", (*it));
	}

	nvgStackText("=============");
}


void ItemBagComponent_stackTextDetail_mouseLocation(const hope::grid::Location& mouseLocation, ItemBagComponent* c, EntityId id) {
	auto loc = Components::find<LocationComponent>(id);

	if (loc == NULL) {
		return;
	}

	if (loc->position != mouseLocation){
		return;
	}

	nvgStackText("==== ItemBag #%d ====", id);

	for (auto it = c->items.items.begin(); it != c->items.items.end(); ++it){
		nvgStackText("%s: %d", kItemTable[it->first]->label()->c_str(), it->second);
	}

	nvgStackText("=============");
}


void TaskComponent_stackTask(TaskComponent* c, EntityId id) {

	nvgStackText("#%d %s (level: %d, priority: %d)", id, c->label, c->level, c->priority);

	if (c->parent != 0) {
		nvgStackText("   parent: #%d", c->parent);
	}
	if (c->next != 0) {
		nvgStackText("   next: #%d", c->next);
	}
	if (c->previous != 0) {
		nvgStackText("   previous: #%d", c->previous);
	}

	if (c->childrenTotal > 0) {
		nvgStackText("   children: %d / %d", c->childrenDone, c->childrenTotal);
	}
	

	auto ata = Components::find<AttachToAgentComponent>(id);
	if (ata != NULL) {
		nvgStackText("   agent: #%d", ata->agent);
	}

	auto t = Components::find<ConstructionTaskComponent>(id);

	if (t != NULL) {
		nvgStackText("   recipe: %s", t->recipe->label()->c_str());
	}

	auto nata = Components::find<DoableComponent>(id);
	if (nata != NULL) {
		nvgStackText("   doable");
	}
}

void dumpTasks() {
	// Components::foreach<TaskComponent>(TaskComponent_stackTask);
}


hope::gles2::Framebuffer framebuffer;

hope::grid::Location mouseLocation;



void Application::onLoop(void) {
	const ::hope::input::mouse::MouseState& mouseState = ::hope::input::mouse::getMouseState();

	int32_t winWidth = 1024, winHeight = 768;
	int blowup = 0;

	hope::core::getViewportSize(&winWidth, &winHeight);

	currentTime = hope::core::getTicks();

	elaspsedTime = currentTime - lastTime;

	lastTime = currentTime;

	kAccuTime += elaspsedTime;
	kUIAccuTime += elaspsedTime;

	bool scrollNotified = false;

	// ---------------------------- INPUT UI

	uiCanvas.updateElementBox();

	if (mouseState.scroll.deltaX != 0 || mouseState.scroll.deltaY != 0)
	{
		hope::ui::event::Scroll::Event e;

		e.deltaX = mouseState.scroll.deltaX;
		e.deltaY = mouseState.scroll.deltaY;

		scrollNotified = uiCanvas.notify<hope::ui::event::Scroll>(mouseState.x, mouseState.y, e);
	}

	if (mouseState.buttons[hope::input::mouse::BOUTON_LEFT].just_up
		|| mouseState.buttons[hope::input::mouse::BOUTON_MIDDLE].just_up
		|| mouseState.buttons[hope::input::mouse::BOUTON_RIGHT].just_up)
	{
		hope::ui::event::Click::Event e;

		e.x = mouseState.x;
		e.y = mouseState.y;

		uiCanvas.notify<hope::ui::event::Click>(mouseState.x, mouseState.y, e);
	}

	// ---------------------------- INPUT UI

	// -------------------------- INPUT

	float_t xCenter = winWidth / 2.0f;
	float_t yCenter = winHeight / 2.0f;


	float xMouse = (mouseState.x - xCenter) / 10.f;
	float yMouse = (mouseState.y - yCenter) / -10.f;

	mouseLocation.set(
		(systems::TheGrid()->kToyGrid->width / 2) - (((xCenter - mouseState.x - kRendererOffsetX) / 32.f) / gridRenderer.zoomValue),
		(systems::TheGrid()->kToyGrid->height / 2) - (((yCenter - mouseState.y - kRendererOffsetY) / 32.f) / gridRenderer.zoomValue)
		);



	switch (kDnDView.process(mouseState)) {
	case hope::input::mouse::DragAndDrop::Status::BEGIN:
		break;
	case hope::input::mouse::DragAndDrop::Status::END:
		gridRenderer.translate(-(kRendererOffsetX + kDnDView.getDeltaX()), -(kRendererOffsetY + kDnDView.getDeltaY()));
		kRendererOffsetX += kDnDView.getDeltaX();
		kRendererOffsetY += kDnDView.getDeltaY();
		break;
	case hope::input::mouse::DragAndDrop::Status::IN_PROGRESS:
		gridRenderer.translate(-(kRendererOffsetX + kDnDView.getDeltaX()), -(kRendererOffsetY + kDnDView.getDeltaY()));
		break;
	default:
		break;
	}


	switch (kDnDSelection.process(mouseState)) {
	case hope::input::mouse::DragAndDrop::Status::BEGIN:
		kSelectionStartLocation = mouseLocation;
		break;
	case hope::input::mouse::DragAndDrop::Status::END:
		kSelectionBox.setX(kSelectionStartLocation.x, mouseLocation.x);
		kSelectionBox.setY(kSelectionStartLocation.y, mouseLocation.y);
		applyMouseMode(kMouseMode, kSelectionBox);
		break;
	case hope::input::mouse::DragAndDrop::Status::IN_PROGRESS:
		break;
	default:
		break;
	}

	if (!scrollNotified) {
		gridRenderer.zoom((float)mouseState.scroll.deltaY / 16.0f);
	}

	// -------------------------- INPUT


	// -------------------------- UPDATE WORLD
	while (kAccuTime > 30) {
		//		updateAgentAliveGauges(store_Alive.pool, store_Alive.pool_cursor);
		//		updateAgentAliveNeeds(store_Alive.pool, store_Alive.pool_cursor);
		//		updateAgentAliveAction(store_Alive.pool, store_Alive.pool_cursor);
		
		systems::Task.updatePlans();

		systems::Action::cleanup();

		systems::Task.assignTaskToLazy();

		systems::Task.attachAction();

		systems::Action::process();

		

		kAccuTime = 0;
	}
	// -------------------------- UPDATE WORLD

	// -------------------------- UPDATE GRID
	updateRenderer();
	// -------------------------- UPDATE GRID

	
	// ---------------------------- DRAW

	if (kUIAccuTime > 100) {
		drawUI();
		kUIAccuTime = 0;
	}

	glViewport(0, 0, winWidth, winHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	gridRenderer.render();

	framebuffer.render();
	
	
	
	
		
	// ---------------------------- DRAW
}


void Application::drawUI() {
	const ::hope::input::mouse::MouseState& mouseState = ::hope::input::mouse::getMouseState();

	int32_t winWidth = 1024, winHeight = 768;
	hope::core::getViewportSize(&winWidth, &winHeight);

	float_t xCenter = winWidth / 2.0f;
	float_t yCenter = winHeight / 2.0f;


	framebuffer.begin();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	{
		// ---------------------------- DRAW NANOVG
		::hope::nanovg::beginFrame();

		auto vg = ::hope::nanovg::getContext();

		uiCanvas.drawElementBox(vg);

		uiCanvas.draw(vg);



		//	nvgDrawAABB(aabb);

		nvgBeginStackTextLeft(); {
			dumpTasks();
		}

		nvgBeginStackTextRight(); {
			nvgStackText("mode: %s", toString((MouseMode)kMouseMode));

			//		nvgStackText("nodes: %d", gPathFinder->nodes.size());

			nvgStackText("%d;%d", mouseLocation.x, mouseLocation.y);

			nvgStackText("=============");

			/*
			Room* mouseRoom = findRoom(mouseLocation);
			if (mouseRoom != NULL) {
			nvgStackText("=============");
			nvgStackText("room");
			nvgStackText("o2: %d", mouseRoom->o2);
			nvgStackText("%d cells", mouseRoom->cell_count);
			nvgStackText("=============");
			}
			*/

			nvgStackText("Navigation group: %d", systems::TheGrid()->getNavigationGroup(mouseLocation));



			const ItemCell* icell = systems::TheGrid()->kItemGrid->find(mouseLocation);
			if (icell != NULL) {
				nvgStackText("=== items ===");

				for (auto it = icell->items.items.begin(); it != icell->items.items.end(); ++it){
					nvgStackText("%s: %d", kItemTable[it->first]->label()->c_str(), it->second);
				}

				nvgStackText("=============");
			}


			EntityId taskId = systems::task::Construction.findTask(mouseLocation);
			if (taskId != 0) {
				nvgStackTextTaskDetail(taskId);
			}

			std::function<void(ItemBagComponent*, EntityId)> f0 = std::bind(ItemBagComponent_stackTextDetail_mouseLocation, mouseLocation, std::placeholders::_1, std::placeholders::_2);
			Components::foreach<ItemBagComponent>(f0);

			std::function<void(DepositComponent*, EntityId)> f1 = std::bind(DepositComponent_stackTextDetail_mouseLocation, mouseLocation, std::placeholders::_1, std::placeholders::_2);
			Components::foreach<DepositComponent>(f1);

			std::function<void(StorageComponent*, EntityId)> f2 = std::bind(StorageComponent_stackTextDetail_mouseLocation, mouseLocation, std::placeholders::_1, std::placeholders::_2);
			Components::foreach<StorageComponent>(f2);
		}

		nvgDrawMenuText(xCenter - 150, winHeight - 40, "a", "WALL", kMouseMode == MOUSE_MODE_WALL);
		nvgDrawMenuText(xCenter - 50, winHeight - 40, "z", "FLOOR", kMouseMode == MOUSE_MODE_FLOOR);
		nvgDrawMenuText(xCenter + 50, winHeight - 40, "r", "ROOM", kMouseMode == MOUSE_MODE_ROOM);
		nvgDrawMenuText(xCenter + 150, winHeight - 40, "d", "DOOR", kMouseMode == MOUSE_MODE_DOOR);
		nvgDrawMenuText(xCenter + 250, winHeight - 40, "c", "CANCEL", kMouseMode == MOUSE_MODE_CANCEL);


	}
	::hope::nanovg::endFrame();
	framebuffer.end();

	
}



void Application::onResize(int width, int height) {
	glViewport(0, 0, width, height);

	gridRenderer.resize(width, height);
	uiCanvas.setRootSize(width, height);
}



void Application::onGLInitialize() {
	int32_t winWidth = 1024, winHeight = 768;
	hope::core::getViewportSize(&winWidth, &winHeight);

	if (!::hope::nanovg::initialize()) {
		exit(42);
	}

	if (!framebuffer.initialize(winWidth, winHeight)){
		exit(43);
	}

	::hope::nanovg::loadFont("Roboto-Regular.ttf", "sans");

	gridRenderer.initialize(systems::TheGrid()->kToyGrid->width, systems::TheGrid()->kToyGrid->height, "tiles.png(webp)", "grid.vert", "grid.frag");
	gridRenderer.resize(winWidth, winHeight);
	//	for (auto it = kResources.cells.begin(); it != kResources.cells.end(); ++it) {
	//		gridRenderer.set(it->second.x, it->second.y, toTileIndex(it->second));
	//	}
	//	gridRenderer.commit();


	
}

void Application::onGLRelease(void) {
	gridRenderer.release();
	::hope::nanovg::release();
}

