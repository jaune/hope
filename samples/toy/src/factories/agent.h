namespace factories {
namespace agent {

	EntityId create(const char* label, const hope::grid::Location& location) {
		EntityId id = Entities::create();

		Components::attach<LocationComponent>(id)->position.set(location);
		Components::attach<ItemBagComponent>(id);
		Components::attach<AgentComponent>(id)->label = label;
		Components::attach<LaborComponent>(id)->labor = 1000;

		return id;
	}

};
};