#ifndef HOPE_SAMPLES_TOY_ITEMBAG_H
#define HOPE_SAMPLES_TOY_ITEMBAG_H

#include "./types.h"


//typedef std::unordered_map<ItemId, ItemQuantity> ItemBag;

class ItemBag {

	typedef std::unordered_map<ItemId, ItemQuantity> Map;

public:
	Map items;
	

public:
	ItemBag() {
	}

	ItemQuantity getItemQuantity(ItemId id) const {
		auto it = items.find(id);

		if (it == items.end()) {
			return 0;
		}

		return it->second;
	}

	ItemQuantity getTotalQuantity() const {
		ItemQuantity total = 0;

		for (auto it = items.begin(); it != items.end(); ++it){
			total += it->second;
		}

		return total;
	}

	void setItemQuantity(ItemId id, ItemQuantity q){
		auto it = items.find(id);

		if (it == items.end()) {
			items.insert(Map::value_type(id, q));
		}
		else {
			it->second = q;
		}
	}

	void decrementItemQuantity(ItemId item_id) {
		ItemQuantity q = getItemQuantity(item_id);

		if (q > 0) {
			setItemQuantity(item_id, q - 1);
		}
	}
	
	void incrementItemQuantity(ItemId item_id) {
		ItemQuantity q = getItemQuantity(item_id);

		setItemQuantity(item_id, q + 1);
	}


};



#endif /* HOPE_SAMPLES_TOY_ITEMBAG_H */