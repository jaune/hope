#ifndef HOPE_SAMPLES_UI_UI_StorageList_H
#define HOPE_SAMPLES_UI_UI_StorageList_H

#include "./Canvas.h"
#include "../ItemTable_generated.h"

#include "./StorageListItem.h"
#include "../Entities.h"

#include "./action/StorageRequestQuantitySetValue.h"

namespace ui {
	using namespace hope::ui;

	struct StorageList {	

		// state

		struct Props {
			EntityId storage_id;
			const hope::samples::toy::fbs::ItemTable* table;
		};

		static void render(Canvas* c, ElementId root, const Props& props) {
			Style& style = c->getElement(root).style;

			style.width = Size::pc(0.33f);
			style.height = Size::pc(1.0f);
			style.layout.type = Layout::VERTICAL;

			{
				ElementId title = c->appendChild(root);

				Style& style = c->getElement(title).style;

				style.width = Size::pc(1.f);
				style.height = Size::px(20.0f);
				style.layout.type = Layout::HORIZONTAL;


				// label
				{
					auto e = c->appendChild(title);
					c->setText(e, "StorageList");

					Style& style = c->getElement(e).style;

					style.width = Size::pc(0.90f);
					style.height = Size::pc(1.0f);
				}

				// close
				{
					auto e = c->appendChild(title);
					c->setText(e, "X");

					Style& style = c->getElement(e).style;

					style.width = Size::pc(0.10f);
					style.height = Size::pc(1.0f);

					c->setListener<event::Click>(e, onClick);
				}
			}

			const ItemBag& items = Components::get<ItemBagComponent>(props.storage_id)->items;
			const ItemBag& requests = Components::get<StorageComponent>(props.storage_id)->request_quantities;
			
			const hope::samples::toy::fbs::ItemTable* table = props.table;

			size_t i = 0;
			for (auto it = table->items()->begin(); it != table->items()->end(); ++it) {

				StorageListItem::Props sli_p;

				sli_p.label = it->label()->c_str();
				sli_p.quantity = items.getItemQuantity(it->id());
				sli_p.request_quantity = requests.getItemQuantity(it->id());
				sli_p.onRequestQuantityChange = std::bind(onRequestQuantityChange, c, root, it->id(), std::placeholders::_1);

				c->appendChild<StorageListItem>(root, sli_p);

				i++;
			}
		}

		
		static void onRequestQuantityChange(Canvas* c, ElementId id, ItemId item_id, float value) {
			const Props& props = c->getProps<StorageList>(id);

			hope::console::log(" --- setItemQuantity(%d, %f) --- ", item_id, value);

			auto sc = Components::get<StorageComponent>(props.storage_id);
			sc->request_quantities.setItemQuantity(item_id, value);
		}

		static void onClick(Canvas* c, ElementId id, const event::Click::Event& e) {
			hope::console::log(" --- Click --- %d ", id);
		}

		typedef std::unordered_map<ElementGid, Props> PropsMap;
		static PropsMap props;
	};
	StorageList::PropsMap StorageList::props;

}

#endif /* HOPE_SAMPLES_UI_UI_StorageList_H */