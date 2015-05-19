#ifndef HOPE_SAMPLES_TOY_UI_MachinePanelRecipe_H
#define HOPE_SAMPLES_TOY_UI_MachinePanelRecipe_H

#include "./Canvas.h"

#include "./InputNumber.h"
#include "../command/Command.h"


namespace ui {
	using namespace hope::ui;

	struct MachinePanelRecipe {

		struct Props {
			bool is_active;
			CraftRecipeId recipe_id;
			EntityId machine_id;
		};

		static void render(Canvas* c, ElementId root, const Props& props) {
			Style& style = c->getElement(root).style;

			style.width = Size::pc(1.00f);
			style.height = Size::px(15.0f);
			style.layout.type = Layout::HORIZONTAL;
			

			std::string s;

			if (props.is_active) {
				s.append("[[ ");
			}
			
			s.append(asset::CraftRecipeTable::get(props.recipe_id)->label()->c_str());

			if (props.is_active) {
				s.append(" ]]");
			}

			c->setText(root, s);

			c->setListener<event::Click>(root, onClick);
		}

		static void onClick(Canvas* c, ElementId id, const event::Click::Event& e) {
			const Props& props = c->getProps<MachinePanelRecipe>(id);

			command::MachineSelectRecipe command;
			command.machine_id = props.machine_id;
			command.recipe_id = props.recipe_id;
			command::trigger(command);
		}

	};


}

#endif /* HOPE_SAMPLES_TOY_UI_MachinePanelRecipe_H */