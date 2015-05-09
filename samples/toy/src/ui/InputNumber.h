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

			hope::ui::Callback<T> onChange;
		};
		

		static void render(Canvas* c, ElementId root, const Props& props) {
			Style& style = c->getElement(root).style;

			style.width = Size::pc(1.0f);
			style.height = Size::pc(1.0f);

			c->setListener<event::Scroll>(root, onScroll);
			c->setListener<event::DragMove>(root, onDragMove);

			c->setText(root, std::to_string(props.value));
		}

		static void setValue(Canvas* c, ElementId id, T value) {
			const Props& props = c->getProps<InputNumber>(id);

			value = ((value + props.step - 1) / props.step) * props.step;
			
			if (value > props.maxValue) {
				value = props.maxValue;
			}

			if (value < props.minValue) {
				value = props.minValue;
			}

			if (value != props.value) {
				c->callCallback<T>(props.onChange, value);
			}
		}

		static void onScroll(Canvas* c, ElementId id, const event::Scroll::Event& e) {
			const Props& props = c->getProps<InputNumber>(id);
			
			setValue(c, id, props.value + ((T)e.deltaY) * props.step);
		}


		static void onDragMove(Canvas* c, ElementId id, const event::DragMove::Event& e) {
			const Props& props = c->getProps<InputNumber>(id);

			setValue(c, id, e.deltaX * props.step);
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