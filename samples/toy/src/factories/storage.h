namespace factories {
namespace storage {

	EntityId create(const hope::grid::Location& location) {
		EntityId id = Entities::create();

		Components::attach<LocationComponent>(id)->position.set(location);
		Components::attach<ItemBagComponent>(id);
		Components::attach<StorageComponent>(id);

		return id;
	}

};
};