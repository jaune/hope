#ifndef HOPE_CORE_H
#define HOPE_CORE_H

#include <stdint.h>

namespace hope {
namespace core {

	typedef uint32_t Tick;

	Tick getTicks(void);
	void getViewportSize(int32_t *w, int32_t *h);

namespace nacl {

	void updateViewportSize(int32_t w, int32_t h);

} /* namespace core */

} /* namespace core */
} /* namespace hope */

#endif /* HOPE_CORE_H */