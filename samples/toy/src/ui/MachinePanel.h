#ifndef HOPE_SAMPLES_TOY_UI_MachinePanel_H
#define HOPE_SAMPLES_TOY_UI_MachinePanel_H

#include "./Canvas.h"

#include "./MachinePanelRecipe.h"
#include "../Entities.h"
#include "../asset/ItemTable.h"
#include "../asset/MachineTable.h"
#include "../command/SelectEntity.h"

namespace ui {
	using namespace hope::ui;

	struct MachinePanel {

		// state

		struct Props {
			EntityId machine_id;
		};

		static void render(Canvas* c, ElementId root, const Props& props) {
			Style& style = c->getElement(root).style;

			style.width = Size::pc(0.33f);
			style.height = Size::pc(1.0f);
			style.layout.type = Layout::VERTICAL;
			style.backgroundColor = nvgRGBA(255, 0, 255, 255);

			auto machine = Components::get<MachineComponent>(props.machine_id);
			auto machine_class = asset::MachineTable::get(machine->type);

			
			{
				ElementId title = c->appendChild(root);

				Style& style = c->getElement(title).style;

				style.width = Size::pc(1.f);
				style.height = Size::px(20.0f);
				style.layout.type = Layout::HORIZONTAL;

				
				// label
				{
					auto e = c->appendChild(title);

					c->setText(e, machine_class->label()->c_str());

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

					c->setListener<event::Click>(e, onCloseClick);
				}
			}


			

			{
				for (auto it = machine_class->recipes()->begin(); it != machine_class->recipes()->end(); ++it){
					
					ui::MachinePanelRecipe::Props p;

					p.recipe_id = *it;
					p.is_active = machine->recipe_id == *it;
					p.machine_id = props.machine_id;

					auto e = c->appendChild<ui::MachinePanelRecipe>(root, p);
				}
			}
		}		

		static void onCloseClick(Canvas* c, ElementId id, const event::Click::Event& e) {
			command::SelectEntity command;
			command.entity_id = 0;
			command::trigger(command);
		}

	};

}

#endif /* HOPE_SAMPLES_TOY_UI_MachinePanel_H */