#ifndef HOPE_SAMPLES_UI_UI_StorageListItem_H
#define HOPE_SAMPLES_UI_UI_StorageListItem_H

#include "./Canvas.h"

#include "./InputNumber.h"

namespace ui {
	using namespace hope::ui;

	struct StorageListItem {

		// state

		struct Props {
			std::string label;
			float quantity;
			int item_id;
		};

		static void create(Canvas* c, ElementId root, const Props& props) {
			Style& style = c->getElement(root).style;

			style.width = Size::pc(1.00f);
			style.height = Size::px(15.0f);
			style.layout.type = Layout::HORIZONTAL;


			// label
			{
				auto l = c->appendChild(root);
				c->setText(l, props.label);

				Style& style = c->getElement(l).style;

				style.width = Size::pc(0.50f);
				style.height = Size::pc(1.0f);
			}

			{
				// quantity
				auto q = c->appendChild(root);
				c->setText(q, std::to_string(props.quantity));

				Style& style = c->getElement(q).style;

				style.width = Size::pc(0.25f);
				style.height = Size::pc(1.0f);
			}

			{
				// request quantity
				InputNumber::Props rq_p;

				rq_p.minValue = 0;
				rq_p.maxValue = 1000;
				rq_p.step = 10;
				rq_p.value = props.quantity;
				rq_p.onChange = std::bind(onRequestQuantityChange, c, root, std::placeholders::_1);

				auto rq = c->appendChild<InputNumber>(root, rq_p);

				Style& style = c->getElement(rq).style;

				style.width = Size::pc(0.25f);
				style.height = Size::pc(1.0f);
			}
		}

		static void onRequestQuantityChange(Canvas* c, ElementId id, float value) {
			const Props& props = c->getProps<StorageListItem>(id);

			hope::console::log("%s (#%d) => %f", props.label.c_str(), props.item_id, value);
		}
				
		typedef std::unordered_map<ElementGid, Props> PropsMap;
		static PropsMap props;
	};
	StorageListItem::PropsMap StorageListItem::props;

}

#endif /* HOPE_SAMPLES_UI_UI_StorageListItem_H */