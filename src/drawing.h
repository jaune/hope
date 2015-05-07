
static float textOffset = 8;
static char textBuffer[256];

void nvgBeginStackText() {
	textOffset = 8;
}


void nvgDrawStrokeCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
	int32_t winWidth, winHeight;

	hope::core::getViewportSize(&winWidth, &winHeight);

	nvgSave(vg);

	nvgBeginPath(vg);
	nvgCircle(vg, (winWidth / 2.0) + (center.x * 10.0f), (winHeight / 2.0) + (center.y * -10.0f), radius * 10.0f);
	nvgStrokeColor(vg, nvgRGBA(
		(uint8_t)(color.r * 255.0f),
		(uint8_t)(color.g * 255.0f),
		(uint8_t)(color.b * 255.0f),
		255));
	nvgStroke(vg);
	nvgRestore(vg);
}

void nvgDrawFillCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
	int32_t winWidth, winHeight;

	hope::core::getViewportSize(&winWidth, &winHeight);

	nvgSave(vg);

	nvgBeginPath(vg);
	nvgCircle(vg, (winWidth / 2.0) + (center.x * 10.0f), (winHeight / 2.0) + (center.y * -10.0f), radius * 10.0f);
	nvgFillColor(vg, nvgRGBA(
		(uint8_t)(color.r * 255.0f),
		(uint8_t)(color.g * 255.0f),
		(uint8_t)(color.b * 255.0f),
		255));
	nvgFill(vg);
	nvgRestore(vg);
}



void nvgStackText(const char* format, ...) {
	va_list args;
	va_start(args, format);

	vsprintf(textBuffer, format, args);

	va_end(args);

	nvgText(vg, 8, textOffset, textBuffer, NULL);
	textOffset += 20.0f;
}

class nvgDebugDraw : public b2Draw
{
	/// Draw a closed polygon provided in CCW order.
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
		::hope::console::log("--------------- nvgDebugDraw::DrawPolygon ------------------");
	}

	/// Draw a solid closed polygon provided in CCW order.
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
		// ::hope::console::log("--------------- nvgDebugDraw::DrawSolidPolygon ------------------");


		int32_t winWidth, winHeight, i;

		hope::core::getViewportSize(&winWidth, &winHeight);

		float_t xOffset = (winWidth / 2.0f), yOffset = (winHeight / 2.0f);

		nvgSave(vg);

		nvgBeginPath(vg);

		for (i = 0; i < vertexCount; i++) {
			if (i == 0) {
				nvgMoveTo(vg,
					(vertices[i].x * 10.0f) + xOffset,
					(vertices[i].y * -10.0f) + yOffset
					);
			}
			else {
				nvgLineTo(vg,
					(vertices[i].x * 10.0f) + xOffset,
					(vertices[i].y * -10.0f) + yOffset
					);
			}

		}

		nvgClosePath(vg);

		nvgStrokeColor(vg, nvgRGBA(
			(uint8_t)(color.r * 255.0f),
			(uint8_t)(color.g * 255.0f),
			(uint8_t)(color.b * 255.0f),
			255));
		nvgStroke(vg);

		nvgRestore(vg);
	}

	/// Draw a circle.
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
		::hope::console::log("--------------- nvgDebugDraw::DrawCircle ------------------");
	}


	/// Draw a solid circle.
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
		// ::hope::console::log("nvgDebugDraw::DrawSolidCircle %f,%f %f", center.x, center.y, radius);

		nvgDrawStrokeCircle(center, radius, color);
	}

	/// Draw a particle array
	void DrawParticles(const b2Vec2 *centers, float32 radius, const b2ParticleColor *colors, int32 count) {
		::hope::console::log("--------------- nvgDebugDraw::DrawParticles ------------------");
	}

	/// Draw a line segment.
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
		::hope::console::log("--------------- nvgDebugDraw::DrawSegment ------------------");
	}

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	void DrawTransform(const b2Transform& xf) {
		::hope::console::log("--------------- nvgDebugDraw::DrawTransform ------------------");
	}
};


void nvgDrawStrokeLine(const b2Vec2& src, const b2Vec2& dst, const b2Color& color) {
	int32_t winWidth, winHeight, i;

	hope::core::getViewportSize(&winWidth, &winHeight);

	float_t xOffset = (winWidth / 2.0f), yOffset = (winHeight / 2.0f);


	nvgSave(vg);

	nvgBeginPath(vg);
	nvgMoveTo(vg,
		(src.x * 10.0f) + xOffset,
		(src.y * -10.0f) + yOffset
		);
	nvgLineTo(vg,
		(dst.x * 10.0f) + xOffset,
		(dst.y * -10.0f) + yOffset
		);
	nvgStrokeColor(vg, nvgRGBA(
		(uint8_t)(color.r * 255.0f),
		(uint8_t)(color.g * 255.0f),
		(uint8_t)(color.b * 255.0f),
		255));
	nvgStroke(vg);

	nvgRestore(vg);
}

void nvgDrawAABB(const b2AABB& aabb){

	int32_t winWidth, winHeight, i;

	hope::core::getViewportSize(&winWidth, &winHeight);

	float_t xOffset = (winWidth / 2.0f),
		yOffset = (winHeight / 2.0f);
	nvgSave(vg);

	float_t x = xOffset + (aabb.lowerBound.x * 10.0f),
		y = yOffset + (aabb.upperBound.y * -10.0f),
		w = (aabb.upperBound.x - aabb.lowerBound.x) * 10.0f,
		h = (aabb.upperBound.y - aabb.lowerBound.y) * 10.0f;

	nvgBeginPath(vg);
	nvgRect(vg, x, y, w, h);
	nvgStrokeColor(vg, nvgRGBA(255, 0, 255, 255));
	nvgStroke(vg);

	nvgRestore(vg);
}


void drawAgentAlive(const AgentAlive* agentAlive) {
	nvgStackText("%s", agentAlive->label);
	nvgStackText("=============");
	nvgStackText("Action: %s", toString(agentAlive->currentAction.type));
	nvgStackText("=============");
	for (auto it = agentAlive->gauges.begin(); it != agentAlive->gauges.end(); it++) {
		nvgStackText("%s: %6.2f", toString(it->first), it->second);
	}
	nvgStackText("=============");
	for (auto it = agentAlive->ai.needs.begin(); it != agentAlive->ai.needs.end(); it++) {
		nvgStackText("%s: %s", toString(it->first), toString(it->second));
	}
}

void drawSelectedEntityPanel() {

	const AgentCorpse* agentCorpse = physics->getSelected<AgentCorpse>();
	const AgentAlive* agentAlive = physics->getSelected<AgentAlive>();
	const Deposit* deposit = physics->getSelected<Deposit>();

	if (agentCorpse) {
		nvgStackText("%s", agentCorpse->label);
		nvgStackText("====  action  ====");
	}

	if (agentAlive) {
		drawAgentAlive(agentAlive);
	}

	if (deposit) {
		nvgStackText("%s: %6.2f", kResourceTypeNames[deposit->type], deposit->quantity);
	}
}


void drawDeposit(const Deposit *items, size_t length)
{
	const Deposit* item = items;
	const Deposit* end = items + length;

	for (; item != end; item++) {

		nvgDrawStrokeCircle(item->position, 1.5f, kResourcesColor[item->type]);
	}
}


void drawAgentAlive(const AgentAlive *items, size_t length)
{
	const AgentAlive* item = items;
	const AgentAlive* end = items + length;

	for (; item != end; item++) {

		nvgDrawStrokeCircle(item->position, item->radius, b2Color(1.0f, 0.0f, 1.0f));

		const Action& currentAction = item->currentAction;

		if (currentAction.type == GOTO_ACTION) {
			const GoToAction& action = currentAction.GoToAction;
			b2Vec2 dst(action.location.x, action.location.y);

			nvgDrawStrokeLine(item->position, dst, b2Color(0.0f, 0.5f, 0.0f));
			nvgDrawStrokeCircle(dst, 0.25f, b2Color(0.0f, 0.5f, 0.0f));
		}
	}
}


void drawAgentCorpse(const AgentCorpse *items, size_t length)
{
	const AgentCorpse* item = items;
	const AgentCorpse* end = items + length;

	for (; item != end; item++) {
		nvgDrawStrokeCircle(item->position, 0.5f, b2Color(0.3f, 0.3f, 0.3f));
	}
}
