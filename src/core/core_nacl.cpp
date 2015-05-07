#include "core.h"

#include <ppapi/cpp/module.h>

namespace hope {
namespace core {

	static PP_TimeTicks kLastTimeTicks = -1;
	
	static int32_t kViewportWidth = -1;
	static int32_t kViewportHeigth = -1;

  uint32_t getTicks (void) {
	  PP_TimeTicks now = pp::Module::Get()->core()->GetTimeTicks();

	if (kLastTimeTicks == -1) {
		kLastTimeTicks = now;
		return 0;
	}
	return (now - kLastTimeTicks) * 1000.0;
  }

  void getViewportSize(int32_t *w, int32_t *h) {
	  *w = kViewportWidth;
	  *h = kViewportHeigth;
  }

  namespace nacl {

	  void updateViewportSize(int32_t w, int32_t h) {
		  kViewportWidth = w;
		  kViewportHeigth = h;
	  }

  } /* namespace core */

} /* namespace core */
} /* namespace hope */