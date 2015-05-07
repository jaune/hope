#include "entry.h"

#include "../input/mouse.h"
#include "../core/core.h"

#include <GLES2/gl2.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// C++ headers
#include <sstream>
#include <string>

#include <ppapi/cpp/input_event.h>
#include <ppapi/cpp/graphics_3d.h>

#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/module.h>
#include <ppapi/cpp/var.h>
#include <ppapi/cpp/var_array.h>
#include <ppapi/lib/gl/gles2/gl2ext_ppapi.h>
#include <ppapi/utility/completion_callback_factory.h>

#ifdef WIN32
#undef PostMessage
// Allow 'this' in initializer list
#pragma warning(disable : 4355)
#endif

namespace {

std::string ModifierToString(uint32_t modifier) {
  std::string s;
  if (modifier & PP_INPUTEVENT_MODIFIER_SHIFTKEY) {
    s += "shift ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_CONTROLKEY) {
    s += "ctrl ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_ALTKEY) {
    s += "alt ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_METAKEY) {
    s += "meta ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_ISKEYPAD) {
    s += "keypad ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_ISAUTOREPEAT) {
    s += "autorepeat ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_LEFTBUTTONDOWN) {
    s += "left-button-down ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_MIDDLEBUTTONDOWN) {
    s += "middle-button-down ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_RIGHTBUTTONDOWN) {
    s += "right-button-down ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_CAPSLOCKKEY) {
    s += "caps-lock ";
  }
  if (modifier & PP_INPUTEVENT_MODIFIER_NUMLOCKKEY) {
    s += "num-lock ";
  }
  return s;
}

/*
std::string MouseButtonToString(PP_InputEvent_MouseButton button) {
  switch (button) {
    case PP_INPUTEVENT_MOUSEBUTTON_NONE:
      return "None";
    case PP_INPUTEVENT_MOUSEBUTTON_LEFT:
      return "Left";
    case PP_INPUTEVENT_MOUSEBUTTON_MIDDLE:
      return "Middle";
    case PP_INPUTEVENT_MOUSEBUTTON_RIGHT:
      return "Right";
    default:
      std::ostringstream stream;
      stream << "Unrecognized (" << static_cast<int32_t>(button) << ")";
      return stream.str();
  }
}
*/


} /* namespace */

class MainInstance : public pp::Instance {
 public:
  explicit MainInstance(PP_Instance instance) : pp::Instance(instance),
        callback_factory_(this),
        startTimeTicks_(pp::Module::Get()->core()->GetTimeTicks()),
        width_(0),
        height_(0)
         {
      RequestInputEvents(PP_INPUTEVENT_CLASS_MOUSE | PP_INPUTEVENT_CLASS_WHEEL |
                         PP_INPUTEVENT_CLASS_TOUCH);
      RequestFilteringInputEvents(PP_INPUTEVENT_CLASS_KEYBOARD);

    }

  virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]) {
    ::hope::entry::onInitialize();



    return true;
  }

  virtual void DidChangeView(const pp::View& view) {
    // Pepper specifies dimensions in DIPs (device-independent pixels). To
    // generate a context that is at device-pixel resolution on HiDPI devices,
    // scale the dimensions by view.GetDeviceScale().
    int32_t new_width = view.GetRect().width() * view.GetDeviceScale();
    int32_t new_height = view.GetRect().height() * view.GetDeviceScale();

    printf("Size %i x %i", new_width, new_height);

    if (context_.is_null()) {
      if (!initializeGL(new_width, new_height)) {
        // failed.
        return;
      }

      ::hope::entry::onGLInitialize();

      MainLoop(0);
    } else {
      // Resize the buffers to the new size of the module.
      int32_t result = context_.ResizeBuffers(new_width, new_height);
      if (result < 0) {
        fprintf(stderr,
                "Unable to resize buffers to %d x %d!\n",
                new_width,
                new_height);
        return;
      }
    }

    width_ = new_width;
    height_ = new_height;

	::hope::core::nacl::updateViewportSize(width_, height_);

    ::hope::entry::onResize(width_, height_);

    
  }

  virtual bool HandleInputEvent(const pp::InputEvent& event) {
    switch (event.GetType()) {
      case PP_INPUTEVENT_TYPE_IME_COMPOSITION_START:
      case PP_INPUTEVENT_TYPE_IME_COMPOSITION_UPDATE:
      case PP_INPUTEVENT_TYPE_IME_COMPOSITION_END:
      case PP_INPUTEVENT_TYPE_IME_TEXT:
      case PP_INPUTEVENT_TYPE_UNDEFINED:
        // these cases are not handled.
        break;
      case PP_INPUTEVENT_TYPE_MOUSEDOWN:
      case PP_INPUTEVENT_TYPE_MOUSEUP:
      case PP_INPUTEVENT_TYPE_MOUSEMOVE:
      case PP_INPUTEVENT_TYPE_MOUSEENTER:
      case PP_INPUTEVENT_TYPE_MOUSELEAVE:
      case PP_INPUTEVENT_TYPE_CONTEXTMENU: {
        pp::MouseInputEvent mouse_event(event);

		hope::input::mouse::SampleData data;

		data.x = mouse_event.GetPosition().x();
		data.y = mouse_event.GetPosition().y();

		hope::input::mouse::updateSample(data);
		PP_TimeTicks t = ((pp::Module::Get()->core()->GetTimeTicks() - startTimeTicks_) * 1000.0);
    uint32_t ut = t;

        std::ostringstream stream;
        stream << "Mouse event:"
//               << " modifier:" << ModifierToString(mouse_event.GetModifiers())
//             << " button:" << MouseButtonToString(mouse_event.GetButton())
			   << " x:" << mouse_event.GetPosition().x() << "/" << width_
		       << " y:" << mouse_event.GetPosition().y() << "/" << height_
               << " click_count:" << mouse_event.GetClickCount()
               << " time:" << mouse_event.GetTimeStamp()

			   << " ticks:" << ut
			   << " ticksddd:" << (pp::Module::Get()->core()->GetTimeTicks() * 1000.0)
               << " is_context_menu: "
                   << (event.GetType() == PP_INPUTEVENT_TYPE_CONTEXTMENU);
        // PostMessage(stream.str());

        break;
      }

      case PP_INPUTEVENT_TYPE_RAWKEYDOWN:
      case PP_INPUTEVENT_TYPE_KEYDOWN:
      case PP_INPUTEVENT_TYPE_KEYUP:
      case PP_INPUTEVENT_TYPE_CHAR: {
        pp::KeyboardInputEvent key_event(event);
        std::ostringstream stream;
        stream << "Key event:"
               << " modifier:" << ModifierToString(key_event.GetModifiers())
               << " key_code:" << key_event.GetKeyCode()
               << " time:" << key_event.GetTimeStamp()
               << " text:" << key_event.GetCharacterText().DebugString();
        PostMessage(stream.str());
        break;
      }

      default: {
        // For any unhandled events, send a message to the browser
        // so that the user is aware of these and can investigate.
        std::stringstream oss;
        oss << "Default (unhandled) event, type=" << event.GetType();
        PostMessage(oss.str());
      } break;
    }

    return true;
  }

  virtual void HandleMessage(const pp::Var& message) {
  }

 private:
  bool initializeGL(int32_t new_width, int32_t new_height) {
    if (!glInitializePPAPI(pp::Module::Get()->get_browser_interface())) {
      fprintf(stderr, "Unable to initialize GL PPAPI!\n");
      return false;
    }

    const int32_t attrib_list[] = {
      PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 8,
      PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 24,
      PP_GRAPHICS3DATTRIB_WIDTH, new_width,
      PP_GRAPHICS3DATTRIB_HEIGHT, new_height,
      PP_GRAPHICS3DATTRIB_NONE
    };

    context_ = pp::Graphics3D(this, attrib_list);
    if (!BindGraphics(context_)) {
      fprintf(stderr, "Unable to bind 3d context!\n");
      context_ = pp::Graphics3D();
      glSetCurrentContextPPAPI(0);
      return false;
    }

    glSetCurrentContextPPAPI(context_.pp_resource());
    return true;
  }

  void MainLoop(int32_t) {
    ::hope::entry::onLoop();
    context_.SwapBuffers(callback_factory_.NewCallback(&MainInstance::MainLoop));
  }

  pp::CompletionCallbackFactory<MainInstance> callback_factory_;
  pp::Graphics3D context_;
  PP_TimeTicks startTimeTicks_;

  int32_t width_;
  int32_t height_;
};

class MainModule : public pp::Module {
 public:
  MainModule() : pp::Module() {}
  virtual ~MainModule() {}

  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new MainInstance(instance);
  }
};

namespace pp {
Module* CreateModule() { return new MainModule(); }
}  // namespace pp
