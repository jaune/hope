#ifndef HOPE_SAMPLES_TOY_systems_action_AbstractSystem_H
#define HOPE_SAMPLES_TOY_systems_action_AbstractSystem_H

template <typename T>
class AbstractActionSystem {

public:

	void cleanup() {
		std::vector<EntityId> result;

		Entities::findByComponentMask(T::COMPONENT_MASK | ActionComponent::COMPONENT_MASK, result);

		for (auto it = result.begin(); it != result.end(); ++it){
			ActionComponent::Status s = Components::get<ActionComponent>(*it)->status;

			if (s == ActionComponent::Status::SUCCESS || s == ActionComponent::Status::FAILURE) {
				Components::detach<T>(*it);
			}
		}
	}



};

#endif /* HOPE_SAMPLES_TOY_systems_action_AbstractSystem_H */