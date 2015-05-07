#ifndef HOPE_SAMPLES_UI_UI_StorageList_H
#define HOPE_SAMPLES_UI_UI_StorageList_H

#include "./Canvas.h"
#include "../ItemTable_generated.h"

#include "./StorageListItem.h"

namespace ui {
	using namespace hope::ui;

	struct StorageList {	

		// state

		struct Props {
			int storage_id;
			const hope::samples::ui::fbs::ItemTable* table;
		};

		static void create(Canvas* c, ElementId root, const Props& props) {
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

					c->addListener<event::Click>(e, onClick);
				}
			}
			
			const hope::samples::ui::fbs::ItemTable* table = props.table;

			size_t i = 0;
			for (auto it = table->items()->begin(); it != table->items()->end(); ++it) {

				StorageListItem::Props sli_p;

				sli_p.label = it->label()->c_str();
				sli_p.quantity = i * 52;
				sli_p.item_id = it->id();

				c->appendChild<StorageListItem>(root, sli_p);

				i++;
			}
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