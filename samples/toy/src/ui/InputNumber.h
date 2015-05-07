#ifndef HOPE_SAMPLES_UI_UI_InputNumber_H
#define HOPE_SAMPLES_UI_UI_InputNumber_H

#include "./Canvas.h"

namespace ui {
	using namespace hope::ui;

	template <typename T>
	struct InputNumber {

		struct Props {
			T value;
			T step;
			T minValue;
			T maxValue;

			std::function<void(T)> onChange;
		};
		

		static void render(Canvas* c, ElementId root, const Props& props) {
			Style& style = c->getElement(root).style;

			style.width = Size::pc(1.0f);
			style.height = Size::pc(1.0f);

			c->setListener<event::Scroll>(root, onScroll);
			c->setListener<event::Click>(root, onClick);

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
			
			T value = props.value + ((T)e.deltaY * props.step);

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
	InputNumber<float>::PropsMap InputNumber<float>::props;

	InputNumber<int16_t>::PropsMap InputNumber<int16_t>::props;
	InputNumber<uint16_t>::PropsMap InputNumber<uint16_t>::props;

	InputNumber<int32_t>::PropsMap InputNumber<int32_t>::props;
	InputNumber<uint32_t>::PropsMap InputNumber<uint32_t>::props;
}

#endif /* HOPE_SAMPLES_UI_UI_InputNumber_H */