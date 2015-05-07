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


uint32_t lastTime = 0, currentTime, elaspsedTime;
float elaspsedAgentTime = 0; // in hours
float elaspsedAgentTimeAccumulator = 0; // in hours

enum CellType {
	VOID = 0,
	WALL,
	FLOOR
};

struct Cell {
	float color;
	bool solid;
	float hp;
	CellType type;
	bool o2;
};

struct GridCellCallback {
	virtual ~GridCellCallback() {}

	virtual void iterateCell(Cell& cell, int32_t x, int32_t y) = 0;
};

struct SetWallCallback : GridCellCallback {

	void iterateCell(Cell& cell, int32_t x, int32_t y) {
		cell.solid = true;
		cell.type = CellType::WALL;
	}
};



struct ApplyVoidCallback : GridCellCallback {

	void iterateCell(Cell& cell, int32_t x, int32_t y) {
		cell.o2 = false;
	}

};


struct SetDestroyCallback : GridCellCallback {

	void iterateCell(Cell& cell, int32_t x, int32_t y) {
		cell.solid = false;
		cell.hp = 0.0;
	}

};

struct SetFloorCallback : GridCellCallback {

	void iterateCell(Cell& cell, int32_t x, int32_t y) {
		cell.solid = false;
		cell.type = CellType::FLOOR;
		cell.o2 = true;
	}

};



struct Vector2 {
	int32_t x, y;
};

struct AABox {
	int32_t xMax;
	int32_t yMax;

	int32_t xMin;
	int32_t yMin;

	inline bool contains(int32_t x, int32_t y) const {
		return (x <= xMax) && (x >= xMin) && (y <= yMax) && (y >= yMin);
	}
};


struct Grid {
	Cell* cells;
	size_t width;
	size_t height;
	int32_t length;

	AABox aabox;

	Grid(size_t width, size_t height) :
		width(width),
		height(height) {

		size_t index;

		length = width * height;

		aabox.yMin = 0;
		aabox.xMin = 0;

		aabox.yMax = height;
		aabox.xMax = width;

		cells = new Cell[length];

		for (index = 0; index < length; index++) {
			cells[index].color = 0.0f;
			cells[index].solid = false;
			cells[index].hp = 1.0;
			cells[index].type = CellType::VOID;
			cells[index].o2 = false;
		}
	}

	~Grid() {
		delete[] cells;
	}

	inline Cell* at(size_t x, size_t y){
		return cells + (x + (y * width));
	}

	inline const Cell* at(size_t x, size_t y) const {
		return cells + (x + (y * width));
	}

	void queryFillRect(int32_t x, int32_t y, int32_t w, int32_t h, GridCellCallback* callback) {
		Cell* c;
		int32_t xMax = x + w;
		int32_t yMax = y + h;

		xMax = (xMax < width) ? xMax : width;
		yMax = (yMax < height) ? yMax : height;

		int32_t xMin;
		int32_t yMin;

		for (xMin = (x >= 0) ? x : 0; xMin < xMax; xMin++) {
			for (yMin = (y >= 0) ? y : 0; yMin < yMax; yMin++) {
				callback->iterateCell(*at(xMin, yMin), xMin, yMin);
			}
		}
	}

	void queryStrokeRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t b, GridCellCallback* callback) {
		queryFillRect(x, y, w, b, callback);
		queryFillRect(x, y + (h - b), w, b, callback);
		queryFillRect(x, y + b, b, h - (2 * b), callback);
		queryFillRect(x + (w - b), y + b, b, h - (2 * b), callback);
	}
};

class ShipBlueprint {
public:
	Grid* build() {
		Grid* grid = new Grid(100, 100);

		SetWallCallback cbWall;
		SetFloorCallback cbFloor;

		grid->queryStrokeRect(5, 5, 20, 20, 2, &cbWall);
		grid->queryStrokeRect(15, 15, 25, 25, 2, &cbWall);

		grid->queryFillRect(5 + 2, 5 + 2, 20 - 4, 20 - 4, &cbFloor);
		grid->queryFillRect(15 + 2, 15 + 2, 25 - 4, 25 - 4, &cbFloor);

		return grid;
	}

}; /* ShipBlueprint */




struct SetColorCallback : GridCellCallback {

	float color = 0.1;

	void iterateCell(Cell& cell, int32_t x, int32_t y) {
		// cell.color += 0.2;
		cell.color = color;
	}

};

struct SetEmptyCallback : GridCellCallback {
	void iterateCell(Cell& cell, int32_t x, int32_t y) {
		cell.solid = false;
		cell.color = 1.0;
	}
};




struct FloodFillQuery {
	
	std::queue<Vector2> floodFillQueue;
	bool* visitedCells;
	Grid& grid;

	FloodFillQuery(Grid& grid) : grid(grid){
		visitedCells = new bool[grid.length];
		reset();
	}

	~FloodFillQuery(){
		delete[] visitedCells;
	}

	void reset() {
		for (size_t i = 0; i < grid.length; i++) {
			visitedCells[i] = false;
		}
	}

	void queryFloodFill(int32_t x, int32_t y, GridCellCallback* callback) {
		Cell* c;

		push(x, y);

		while (!floodFillQueue.empty()) {
			const Vector2& v = floodFillQueue.front();
			c = grid.at(v.x, v.y);

			if (!c->solid && !isVisited(v.x, v.y)) {
				queryFloodFillLine(v.x, v.y, callback);
			}

			floodFillQueue.pop();
		}
	}

	void queryFloodFillLine(int32_t x, int32_t y, GridCellCallback* callback) {
		Cell* c;

		int32_t xMin = x, xMax;
		int32_t xMinBottom = -1;
		int32_t xMinTop = -1;
		int32_t index;

		bool pulseBottom = false;
		bool pulseTop = false;

		while ((xMin >= 0) && !grid.at(xMin, y)->solid) { xMin--; }
		xMin++;
		xMax = xMin;
		
		while ((xMax < grid.width) && !grid.at(xMax, y)->solid) {
			index = xMax + (y * grid.width);
			if (!visitedCells[index] && !grid.at(xMax, y - 1)->solid) { 
				if (xMinBottom == -1) {
					xMinBottom = xMax;
				}
				if (pulseBottom) {
					push( xMax, y - 1 );
					pulseBottom = false;
				}
			}
			else {
				pulseBottom = true;
			}


			if (!visitedCells[index] && !grid.at(xMax, y + 1)->solid) {
				if (xMinTop == -1) {
					xMinTop = xMax;
				}
				if (pulseTop) {
					push( xMax, y + 1 );
					pulseTop = false;
				}
			}
			else {
				pulseTop = true;
			}
			xMax++;
		}

		if (xMinBottom != -1) { 
			push( xMinBottom, y - 1);
		}
		if (xMinTop != -1) { 
			push( xMinTop, y + 1 ); 
		}

		for (int32_t i = xMin; i < xMax; i++) {
			index = i + (y * grid.width);

			if (!visitedCells[index]) {
				callback->iterateCell(*grid.at(i, y), i, y);
				visitedCells[index] = true;
			}
		}

	}
private:
		inline void push(int32_t x, int32_t y) {
			if ((y >= 0) && (y < grid.height) && (x >= 0) && (x < grid.width)) {
				floodFillQueue.push({ x, y });
			}
		}
public:
	inline bool isVisited(int32_t x, int32_t y) const {
		return visitedCells[x + (y * grid.width)];
	}

	bool findFirstUnvisitedArea(GridCellCallback* cb) {
		int32_t x, y;

		for (x = 0; x < grid.width; x++) {
			for (y = 0; y < grid.height; y++) {
				if (!grid.at(x, y)->solid && !isVisited(x, y)){
					queryFloodFill(x, y, cb);
					return true;
				}
			}
		}
		return false;
	}
};

void drawGrid(const Grid& grid) {
	NVGcontext* vg = ::hope::nanovg::getContext();
	b2Vec2 center(0.0f, 0.0f);
	float radius = 15.0f;

	nvgSave(vg);

	size_t x, y;
	const Cell* c;

	
	for (x = 0; x < grid.width; x++) {
		for (y = 0; y < grid.height; y++) {
			c = grid.at(x, y);

			//if (c->solid){
				nvgBeginPath(vg);

				switch (c->type) {
				case CellType::WALL: {
					if (c->hp > 0.0) {
						nvgFillColor(vg, nvgRGB(0xCC, 0xCC, 0xCC));
					}
					else {
						nvgFillColor(vg, nvgRGB(0x3C, 0x3C, 0x3C));
					}
					
					break;
				}
				case CellType::FLOOR: {
					if (c->o2) {
						nvgFillColor(vg, nvgRGB(0x00, 0xFF, 0x00));
					}
					else {
						nvgFillColor(vg, nvgRGB(0xFF, 0x00, 0x00));
					}
					
					break;
				}
				case CellType::VOID: {
					nvgFillColor(vg, nvgRGB(0x0C, 0x0C, 0x0C));
					break;
				}
				default:
					nvgFillColor(vg, nvgHSL(c->color, 0.5, 0.5));
				}

				nvgRect(vg, 1 + (x * 6), 1 + (y * 6), 5, 5);
				nvgFill(vg);
			// }
		}
	}	
	nvgRestore(vg);
}

void drawGrid() {
	NVGcontext* vg = ::hope::nanovg::getContext();
	b2Vec2 center(0.0f, 0.0f);
	float radius = 15.0f;
	b2Color color(1.0, 0.0, 1.0);

	int32_t winWidth, winHeight;

	hope::core::getViewportSize(&winWidth, &winHeight);
	float ox = (winWidth / 2.0);
	float oy = (winHeight / 2.0);

	nvgSave(vg);
	nvgStrokeColor(vg, nvgRGBA(
		(uint8_t)(color.r * 255.0f),
		(uint8_t)(color.g * 255.0f),
		(uint8_t)(color.b * 255.0f),
		255));
	nvgStrokeWidth(vg, 1.0f);

	
	nvgBeginPath(vg);

	float pencil;

	for (pencil = -1000.0f; pencil <= 1000.f; pencil += 10.0f) {
		nvgMoveTo(vg,
			pencil + ox,
			-1000 + oy
		);
		nvgLineTo(vg,
			pencil + ox,
			1000 + oy
		);
	}

	for (pencil = -1000.0f; pencil <= 1000.f; pencil += 10.0f) {
		nvgMoveTo(vg,
			-1000 + ox,
			 pencil  + oy
			);
		nvgLineTo(vg,
			1000 + ox,
			pencil + oy
			);
	}
	nvgStroke(vg);
	
	nvgRestore(vg);
}


struct Bullet {
	int32_t x;
	int32_t y;
};


void drawBullet(const Bullet& bullet, const b2Color& color) {
	NVGcontext* vg = ::hope::nanovg::getContext();
	b2Vec2 center(0.0f, 0.0f);
	float radius = 15.0f;
//
	int32_t winWidth, winHeight;

	hope::core::getViewportSize(&winWidth, &winHeight);
	float ox = (winWidth / 2.0);
	float oy = (winHeight / 2.0);

	nvgSave(vg);

	nvgBeginPath(vg);
	nvgFillColor(vg, nvgRGBA(
		(uint8_t)(color.r * 255.0f),
		(uint8_t)(color.g * 255.0f),
		(uint8_t)(color.b * 255.0f),
		255));

	nvgRect(vg, 1 + (bullet.x * 6), 1 + (bullet.y * 6), 5, 5);
	nvgFill(vg);


	nvgRestore(vg);
}




static Bullet* kBullet = NULL;

static Grid* kGrid = NULL;



void updateVoid(Grid& grid) {
	float color = 0.1;
	bool test;

	ApplyVoidCallback cb;
	
	FloodFillQuery query(grid);

	query.queryFloodFill(0, 0, &cb);
}




namespace hope {

namespace entry {


    void onInitialize (void) {
		ShipBlueprint blueprint;

		kGrid = blueprint.build();



		Cell* c = NULL;

		// findAllRoom(kGrid);

			
//		SetColorCallback cb;
//		cb.color = 0.9;
//		kGrid.queryFloodFill(15, 15, &cb);
    }

	void onRelease (void) {
    }

	static uint32_t kAccuTime = 0;
	
	void onLoop(void) {
		const ::hope::input::mouse::MouseState& mouseSate = ::hope::input::mouse::getMouseState();

		int32_t winWidth = 1024, winHeight = 768;
		int blowup = 0;

		hope::core::getViewportSize(&winWidth, &winHeight);

		currentTime = hope::core::getTicks();

		elaspsedTime = currentTime - lastTime;

		lastTime = currentTime;

		kAccuTime += elaspsedTime;

		float e = elaspsedTime / (3600.0f / 15.0f);

		elaspsedAgentTime += e;
		elaspsedAgentTimeAccumulator += e;

		// -------------------------- UPDATE

		if (kAccuTime > 400) {

			for (size_t i = 0; i < 5; i++) {

	//			if (kBullet != NULL) {
					//kBullet->x += -1;
					//kBullet->y += 0;

//					if (kGrid->aabox.contains(kBullet->x, kBullet->y)) {
//						kGrid.setFillRect(kBullet->x - 2, kBullet->y - 2, 4, 4, 0.0);
//						kBullet = NULL;
//					}
//				}
				
			}			

			kAccuTime -= 400;
		}		

		// -------------------------- UPDATE

		float_t xCenter = winWidth / 2.0f;
		float_t yCenter = winHeight / 2.0f;

		float xMouse = (mouseSate.x - xCenter) / 10.f;
		float yMouse = (mouseSate.y - yCenter) / -10.f;

		b2AABB aabb;
		
		aabb.lowerBound.Set(xMouse - .5f, yMouse - .5f);
		aabb.upperBound.Set(xMouse + .5f, yMouse + .5f);
		
//		physics->queryMouse(xMouse, yMouse);
//		physics->step();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		::hope::nanovg::beginFrame();

		if (mouseSate.buttons[1].just_down) {
			int32_t x = mouseSate.x / 6.0f;
			int32_t y = mouseSate.y / 6.0f;

			SetDestroyCallback cb;

			kGrid->queryFillRect(x - 2, y - 2, 4, 4, &cb);
			updateVoid(*kGrid);
		}

		// ---------------------------- DRAW

//		drawHull(kShip.hull);
		nvgDrawAABB(aabb);
		drawGrid(*kGrid);
		
		if (kBullet) {
			drawBullet(*kBullet, b2Color(1.0, 1.0, 0.0));
		}
		

		// ---------------------------- DRAW

		nvgBeginStackTextLeft(); {

			nvgStackText("%.2f hours", elaspsedAgentTime);

		}

		nvgBeginStackTextRight(); {

			nvgStackText("%d;%d", mouseSate.x, mouseSate.y);
			size_t i;
			for (i = 0; i < 6; i++) {
				nvgStackText("button %d: %d", i, mouseSate.buttons[i].down);
			}

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

} /* namespace entry */

} /* namespace hope */

