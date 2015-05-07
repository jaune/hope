#ifndef HOPE_ASSET_H
#define HOPE_ASSET_H

#include <stdint.h>
#include <string>

namespace hope {
namespace asset {

	struct Asset {
		const void* pointer;
		size_t size;

		Asset() : 
			pointer(NULL),
			size(0) {
		}

		inline bool is_null() const {
			return pointer == NULL;
		}
	};

	int32_t load(const char* headersPath, const char* contentPath);
	void unload(void);

	Asset get(const char* identifier);
	Asset get(const std::string& identifier);

} /* namespace asset */
} /* namespace hope */

#endif /* HOPE_ASSET_H */