#include "Application.h"

#include <entry/entry.h>
#include <core/core.h>
#include <console.h>
#include <input/mouse.h>
#include <asset/asset.h>
#include <nvg.h>
#include <GLES2/gl2.h>


#include <grid/Grid.h>

#include <gles2/Framebuffer.h>

#include "./Message_generated.h"

#include <nn.h>
#include <pair.h>


#include "./ItemTable_generated.h"

#include <thread>
#include <map>

int main_sock;

#include "./ui/Canvas.h"


/*


void sendFlatBuffer(const flatbuffers::FlatBufferBuilder& fbb) const {
int16_t size = fbb.GetSize();

int result;

result = nn_send(main_sock, &size, sizeof(int16_t), NN_DONTWAIT);
if (result == -1) {
hope::console::log("nn_send: %d: %s (%d)", nn_errno(), nn_strerror(nn_errno()), main_sock);
}

result = nn_send(main_sock, fbb.GetBufferPointer(), fbb.GetSize(), NN_DONTWAIT);
if (result == -1) {
hope::console::log("nn_send: %d: %s (%d)", nn_errno(), nn_strerror(nn_errno()), main_sock);
}
}
void sendMessages() {
if (changed <= 0) {
return;
}

flatbuffers::FlatBufferBuilder fbb(512);

int player_id = -1;
int storage_id = -1;

for (size_t i = 0; i < size; i++) {
if (items[i].changed) {
fbb.Clear();

auto c = ::hope::samples::ui::fbs::CreateStorage_SetRequestCommand(fbb, storage_id, items[i].item_id, items[i].request_quantity);
auto m = ::hope::samples::ui::fbs::CreateMessage(fbb, player_id, ::hope::samples::ui::fbs::Command_Storage_SetRequestCommand, c.Union());

fbb.Finish(m);

sendFlatBuffer(fbb);

items[i].changed = false;
}
}
changed = 0;
}


*/


hope::ui::Canvas uiCanvas(1);

hope::gles2::Framebuffer fb;


uint32_t lastTime = 0, currentTime, elaspsedTime;

std::thread* worker;

hope::core::Tick kAccu = 0;

class Worker {
	bool is_running = true;
	int sock = -1;

public:
	void onMessage(const hope::samples::ui::fbs::Message* message) {
		hope::console::log("==> %s", hope::samples::ui::fbs::EnumNameCommand(message->command_type()));
	}

	void process(){
		sock = nn_socket(AF_SP, NN_PAIR);
		assert(sock >= 0);
		assert(nn_connect(sock, "inproc://test") >= 0);

		hope::console::log("worker_process: %d", sock);
			
		int rc;
		struct nn_pollfd pfd[1];

		pfd[0].fd = sock;
		pfd[0].events = NN_POLLIN | NN_POLLOUT;

		int nbytes;
		int16_t msg_size;
		uint8_t msg_buffer[512];

		while (is_running) {
			rc = nn_poll(pfd, 1, 200);
			if (rc == 0) {
				hope::console::log("worker_process: %d TIMEOUT", sock);
			}
			else if (rc == -1) {
				hope::console::log("worker_process: %d ERROR", sock);
				is_running = false;
			}
			else if (pfd[0].revents & NN_POLLIN) {
				nbytes = nn_recv(sock, &msg_size, sizeof(msg_size), 0);
				if (nbytes != sizeof(msg_size)) {
					hope::console::log("worker_process: %d ERROR SIZE %d / %d", sock, nbytes, sizeof(msg_size));
					is_running = false;
				}
				else {
					if (msg_size == -1) { // EXIT THREAD
						is_running = false;
					}
					else {
						nbytes = nn_recv(sock, msg_buffer, msg_size, 0);
						if (nbytes != msg_size) {
							hope::console::log("worker_process: %d ERROR MSG %d / %d", sock, nbytes, msg_size);
						}
						else {
							onMessage(hope::samples::ui::fbs::GetMessage(msg_buffer));
						}
					}					
				}
			}
		}
		assert(nn_close(sock) == 0);
	}
};



void worker_process(){
	Worker worker;

	worker.process();
}

#include "./ui/StorageList.h"


void Application::onInitialize(void) {
	int32_t winWidth = 1024, winHeight = 768;
	hope::core::getViewportSize(&winWidth, &winHeight);


	worker = new std::thread(worker_process);

	main_sock = nn_socket(AF_SP, NN_PAIR);
	if (main_sock == -1) {
		hope::console::log("nn_socket: %d: %s (%d)", nn_errno(), nn_strerror(nn_errno()), main_sock);
	}
	if (nn_bind(main_sock, "inproc://test") == -1) {
		hope::console::log("nn_bind: %d: %s (%d)", nn_errno(), nn_strerror(nn_errno()), main_sock);
	}

	hope::asset::Asset asset_ItemTable = hope::asset::get("ItemTable.json(flatc)");


	uiCanvas.setRootSize(winWidth, winHeight);
			
	ui::StorageList::Props sl_p;
	sl_p.storage_id = 1;
	sl_p.table = hope::samples::ui::fbs::GetItemTable(asset_ItemTable.pointer);

	 hope::ui::ElementId e = uiCanvas.appendChildToRoot<ui::StorageList>(sl_p);
}


void Application::onRelease(void) {
	int16_t msg = -1;
	nn_send(main_sock, &msg, sizeof(msg), 0);
	worker->join();

	assert(nn_close(main_sock) == 0);
}



void Application::onLoop(void) {
	const ::hope::input::mouse::MouseState& mouseState = ::hope::input::mouse::getMouseState();

	int32_t winWidth = 1024, winHeight = 768;
	int blowup = 0;

	hope::core::getViewportSize(&winWidth, &winHeight);

	currentTime = hope::core::getTicks();

	elaspsedTime = currentTime - lastTime;

	lastTime = currentTime;

	float_t xCenter = winWidth / 2.0f;
	float_t yCenter = winHeight / 2.0f;

	float xMouse = (mouseState.x - xCenter) / 10.f;
	float yMouse = (mouseState.y - yCenter) / -10.f;

	// ---------------------------- INPUT UI

	uiCanvas.updateElementBox();

	if (mouseState.scroll.deltaX != 0 || mouseState.scroll.deltaY != 0)
	{
		hope::ui::event::Scroll::Event e;

		e.deltaX = mouseState.scroll.deltaX;
		e.deltaY = mouseState.scroll.deltaY;

		uiCanvas.notify<hope::ui::event::Scroll>(mouseState.x, mouseState.y, e);
	}

	if (mouseState.buttons[hope::input::mouse::BOUTON_LEFT].just_up
		|| mouseState.buttons[hope::input::mouse::BOUTON_MIDDLE].just_up
		|| mouseState.buttons[hope::input::mouse::BOUTON_RIGHT].just_up)
	{
		hope::ui::event::Click::Event e;

		e.x = mouseState.x;
		e.y = mouseState.y;

		uiCanvas.notify<hope::ui::event::Click>(mouseState.x, mouseState.y, e);
	}
	
	// ---------------------------- INPUT UI


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	::hope::nanovg::beginFrame();
	
	// ---------------------------- DRAW UI

	auto vg = ::hope::nanovg::getContext();
		
	// uiWindow.draw(vg);

	uiCanvas.drawElementBox(vg);

	uiCanvas.draw(vg);


	// ---------------------------- DRAW UI


	// ---------------------------- DRAW DEBUG

	nvgBeginStackTextLeft(); {
		
	}

	nvgBeginStackTextRight(); {
		nvgStackText("mouse: %i ; %i", mouseState.x, mouseState.y);

		{
			std::vector<hope::ui::ElementId> ids;
			uiCanvas.find(mouseState.x, mouseState.y, ids);

			for (auto id : ids) {
				nvgStackText("element: %d", id);
			}
		}

	}

	// ---------------------------- DRAW DEBUG


	::hope::nanovg::endFrame();
}




void Application::onResize(int width, int height) {
	glViewport(0, 0, width, height);

	fb.resize(width, height);

	uiCanvas.setRootSize(width, height);
}


void Application::onGLInitialize() {
	if (!::hope::nanovg::initialize()) {
		exit(42);
	}

	::hope::nanovg::loadFont("Roboto-Regular.ttf", "sans");
	::hope::nanovg::loadFont("Roboto-Bold.ttf", "roboto-bold");
	::hope::nanovg::loadFont("Roboto-Regular.ttf", "roboto-regular");
	::hope::nanovg::loadFont("Material-Design-Iconic-Font.ttf", "material-design-iconic-font");

	int32_t winWidth = 1024, winHeight = 768;
	hope::core::getViewportSize(&winWidth, &winHeight);

	fb.initialize(winWidth, winHeight);
}

void Application::onGLRelease(void) {
	::hope::nanovg::release();
}


