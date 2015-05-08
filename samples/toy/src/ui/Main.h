#ifndef HOPE_SAMPLES_UI_UI_MAIN_H
#define HOPE_SAMPLES_UI_UI_MAIN_H

#include "./Canvas.h"

#include "./StorageList.h"

namespace ui {
	using namespace hope::ui;

	struct Main {	

		struct Props {
			EntityId storage_id;
		};

		static void render(Canvas* c, ElementId root, const Props& props) {
			Style& style = c->getElement(root).style;

			style.width = Size::pc(1.f);
			style.height = Size::pc(1.f);
			style.layout.type = Layout::VERTICAL;
			style.backgroundColor = nvgRGBA(255, 0, 255, 128);

			
			if (props.storage_id != 0)
			{
				ui::StorageList::Props sl_p;
				sl_p.storage_id = props.storage_id;

				auto rq = c->appendChild< StorageList >(root, sl_p);
			}
			

		}


	};

}

#endif /* HOPE_SAMPLES_UI_UI_MAIN_H */