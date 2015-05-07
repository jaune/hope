#ifndef HOPE_SAMPLES_TOY_systems_Deposit_H
#define HOPE_SAMPLES_TOY_systems_Deposit_H

class DepositSystem {
public:
	EntityId findNearest(ItemId item_id, EntityId to_id){
		return Entities::findFirstWith<DepositComponent>();
	}
	
	EntityId create(const hope::grid::Location& location, ItemId item_id) {
		EntityId id = Entities::create();

		Components::attach<LocationComponent>(id)->position.set(location);
		Components::attach<DepositComponent>(id)->item_id = item_id;

		return id;
	}
};

namespace systems {
	DepositSystem Deposit;
}

#endif /* HOPE_SAMPLES_TOY_systems_Deposit_H */