#ifndef HOPE_SAMPLES_UI_UI_StorageListItem_H
#define HOPE_SAMPLES_UI_UI_StorageListItem_H

#include "./Canvas.h"

#include "./InputNumber.h"
#include "../command/Command.h"

namespace ui {
	using namespace hope::ui;

	struct StorageListItem {

		struct Props {
			EntityId storage_id;
			ItemId item_id;
			const char* label;
			float quantity;
			float request_quantity;
		};

		static void render(Canvas* c, ElementId root, const Props& props) {
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
				InputNumber<ItemQuantity>::Props rq_p;

				rq_p.minValue = 0;
				rq_p.maxValue = 1000;
				rq_p.step = 10;
				rq_p.value = props.request_quantity;
				rq_p.onChange = c->bindCallback<int16_t>(root, onRequestQuantityChange);

				auto rq = c->appendChild< InputNumber<ItemQuantity> >(root, rq_p);

				Style& style = c->getElement(rq).style;

				style.width = Size::pc(0.25f);
				style.height = Size::pc(1.0f);
			}
		}

		static void onRequestQuantityChange(Canvas* c, ElementId id, int16_t value) {
			const Props& props = c->getProps<StorageListItem>(id);

			command::StorageSetItemRequestQuantity command;

			command.storage_id = props.storage_id;
			command.item_id = props.item_id;
			command.quantity = value;

			command::trigger(command);
		}
	};


}

#endif /* HOPE_SAMPLES_UI_UI_StorageListItem_H */