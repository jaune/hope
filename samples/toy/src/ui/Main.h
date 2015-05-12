#ifndef HOPE_SAMPLES_UI_UI_MAIN_H
#define HOPE_SAMPLES_UI_UI_MAIN_H

#include "./Canvas.h"

#include "./StorageList.h"

namespace ui {
	using namespace hope::ui;

	struct Main {	

		struct Props {
			EntityId selected_entity_id;
		};

		static void render(Canvas* c, ElementId root, const Props& props) {
			c->getElement(root).stopPropagation = false;

			Style& style = c->getElement(root).style;

			style.width = Size::pc(1.f);
			style.height = Size::pc(1.f);
			style.layout.type = Layout::VERTICAL;
			// style.backgroundColor = nvgRGBA(0, 0, 255, 128);
			// hope::console::log("======%d======", props.selected_entity_id);

			{
				ElementId main_id = c->appendChild(root);
				Element& el = c->getElement(main_id);
				Style& style = el.style;

				el.stopPropagation = false;

				style.width = Size::pc(1.f);
				style.height = Size::px(c->height - 50.f);
				style.layout.type = Layout::HORIZONTAL;
				style.backgroundColor = nvgRGBA(255, 0, 0, 128);


				if (props.selected_entity_id != 0)
				{
					if (Entities::testComponentMask(props.selected_entity_id, StorageComponent::COMPONENT_MASK)){

						ui::StorageList::Props sl_p;
						sl_p.storage_id = props.selected_entity_id;

						auto rq = c->appendChild< StorageList >(main_id, sl_p);
					}

				}
			}

			{
				ElementId toolbar_id = c->appendChild(root);
				Element& el = c->getElement(toolbar_id);
				Style& style = el.style;

				el.stopPropagation = false;

				style.width = Size::pc(1.f);
				style.height = Size::px(50.f);
				style.layout.type = Layout::HORIZONTAL;
				style.backgroundColor = nvgRGBA(0, 0, 255, 128);
			}


		}


	};

}

#endif /* HOPE_SAMPLES_UI_UI_MAIN_H */