#ifndef HOPE_SAMPLES_UI_UI_StorageRequestQuantitySetValue_H
#define HOPE_SAMPLES_UI_UI_StorageRequestQuantitySetValue_H

namespace ui {
	using namespace hope::ui;

	namespace action {

		struct StorageRequestQuantitySetValue {
			
			struct Action {
				EntityId storage_id;
				ItemId item_id;
				ItemQuantity quantity;
			};

			static void trigger(const Action& a) {
				hope::console::log("storage(#%d) item(#%d) => %d", a.storage_id, a.item_id, a.quantity);
			}
		};

	}
}

#endif /* HOPE_SAMPLES_UI_UI_StorageRequestQuantitySetValue_H */