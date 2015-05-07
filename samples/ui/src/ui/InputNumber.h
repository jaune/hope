#ifndef HOPE_SAMPLES_UI_UI_InputNumber_H
#define HOPE_SAMPLES_UI_UI_InputNumber_H

#include "./Canvas.h"

namespace ui {
	using namespace hope::ui;

	struct InputNumber {

		struct Props {
			float value;
			float step;
			float minValue;
			float maxValue;

			std::function<void(float)> onChange;
		};
		

		static void create(Canvas* c, ElementId root, const Props& props) {
			Style& style = c->getElement(root).style;

			style.width = Size::pc(1.0f);
			style.height = Size::pc(1.0f);

			c->addListener<event::Scroll>(root, onScroll);
			c->addListener<event::Click>(root, onClick);

			//			c->addListener<event::DragAndDropBegin>(root, InputNumber::onDragAndDropBegin);
			//			c->addListener<event::DragAndDropEnd>(root, InputNumber::onDragAndDropEnd);
			//			c->addListener<event::DragAndDropMove>(root, InputNumber::onDragAndDropMove);

			c->setText(root, std::to_string(props.value));
		}

		static void onClick(Canvas* c, ElementId id, const event::Click::Event& e) {
			hope::console::log(" --- Click --- %d ", id);
		}

		static void onScroll(Canvas* c, ElementId id, const event::Scroll::Event& e) {
			const Props& props = c->getProps<InputNumber>(id);
			
			float value = props.value + (e.deltaY * props.step);

			if (value > props.maxValue) {
				value = props.maxValue;
			}

			if (value < props.minValue) {
				value = props.minValue;
			}

			props.onChange(value);

			// hope::console::log("#%d = %f => %f", id, props.value, value);
			// hope::console::log(" --- Scroll(%d, %d) --- %d ", e.deltaX, e.deltaY, id);
		}

		void onDragAndDropBegin() {
		}

		void onDragAndDropEnd() {
		}

		void onDragAndDropMove() {
		}
		
		typedef std::unordered_map<ElementGid, Props> PropsMap;
		static PropsMap props;
	};
	InputNumber::PropsMap InputNumber::props;
}

#endif /* HOPE_SAMPLES_UI_UI_InputNumber_H */