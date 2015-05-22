#include "./action.h"
#include "../Components.h"

#include <profile.h>

namespace logic {
	namespace action {

		void process() {
			hope::profile::begin(__FUNCTION__);
			
			std::vector<EntityId> candidates;

			Entities::findByComponentMask(ActorComponent::COMPONENT_MASK, candidates);

			if (candidates.empty()){
				return;
			}

			for (EntityId id : candidates) {
				auto actor = Components::get<ActorComponent>(id);
				process(id, actor->action);
			}

			hope::profile::end();
		}

		void idle() {
			hope::profile::begin(__FUNCTION__);

			std::vector<EntityId> candidates;

			Entities::findByComponentMask(ActorComponent::COMPONENT_MASK, candidates);

			if (candidates.empty()){
				return;
			}

			for (EntityId id : candidates) {
				auto actor = Components::get<ActorComponent>(id);
				
				if (actor->action.status == logic::action::SUCCESS || actor->action.status == logic::action::FAILURE){
					logic::action::Idle::Options options;

					actor->action = logic::action::create(options);
				}
			}

			hope::profile::end();
		}

	}
}