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

		if (q < 0) {
			q = 0;
		}

		if (it == items.end()) {
			if (q > 0) {
				items.insert(Map::value_type(id, q));
			}
		}
		else {
			if (q > 0) {
				it->second = q;
			}
			else {
				items.erase(it);
			}			
		}
	}

	void decrementItemQuantity(ItemId item_id) {
		addItemQuantity(item_id, -1);
	}
	
	void incrementItemQuantity(ItemId item_id) {
		addItemQuantity(item_id, 1);
	}

	void addItemQuantity(ItemId item_id, ItemQuantity q) {
		setItemQuantity(item_id, getItemQuantity(item_id) + q);
	}

	
	
};



#endif /* HOPE_SAMPLES_TOY_ITEMBAG_H */