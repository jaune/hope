#ifndef HOPE_SAMPLES_UI_UI_CANVAS_H
#define HOPE_SAMPLES_UI_UI_CANVAS_H

#include <map>

namespace hope {
	namespace ui {

		struct Point {
			float x;
			float y;
		};

		class Box {
		public:
			float xMax;
			float yMax;

			float xMin;
			float yMin;

			Box() :
				xMax(0),
				yMax(0),
				xMin(0),
				yMin(0) {
			}

			inline bool contains(float x, float y) const {
				return (x <= xMax) && (x >= xMin) && (y <= yMax) && (y >= yMin);
			}

			void setX(float a, float b) {
				xMin = (a < b) ? a : b;
				xMax = (a > b) ? a : b;
			}

			void setY(float a, float b) {
				yMin = (a < b) ? a : b;
				yMax = (a > b) ? a : b;
			}

			inline float width() const {
				return xMax - xMin;
			}

			inline float height() const {
				return yMax - yMin;
			}

		};

		class Size {
		public:
			enum Type {
				NONE = 0,
				PERCENT,
				PIXEL
			};

			Type type;
			float value;

			Size() :
				type(NONE),
				value(0.0f) {
			}

			Size(Type type, float value) :
				type(type),
				value(value) {
			}

			static Size px(float value) {
				return Size(PIXEL, value);
			}

			static Size pc(float value) {
				return Size(PERCENT, value);
			}

			static Size none() {
				return Size(NONE, 0.f);
			}
		};

		class Layout {
		public:
			enum Type {
				FIT = 0,
				VERTICAL,
				HORIZONTAL
			};

			Type type;

			Layout() :
				type(VERTICAL) {
			}
		};


		struct Style {
			Size height;
			Size width;
			Layout layout;
			NVGcolor backgroundColor;

			Style() : 
				backgroundColor(nvgRGBA(0, 0, 0, 0)) {
			}
		};


		typedef uint16_t ElementId;

		struct Element {
		public:
			ElementId id;
			ElementId parent;

			ElementId next;
			ElementId previous;

			ElementId firstChild;
			ElementId lastChild;

			std::string text;

			uint16_t propsSum;
			void* propsData;

			Box box;
			Style style;
			

			Element(ElementId id) :
				id(id),
				parent(0),

				next(0),
				previous(0),

				propsSum(0),
				propsData(NULL),

				firstChild(0),
				lastChild(0) {
			}
		};

		typedef uint32_t ElementGid;

		typedef uint8_t CanvasId;
		class Canvas;

		template <typename T>
		struct Callback {
			typedef void(*Function)(Canvas*, ElementId, typename T);

			ElementId element_id;
			Function function;
		};

		namespace event {
			struct Scroll {
				struct Event {
					int deltaX;
					int deltaY;
				};

				typedef std::function<void(Canvas *, ElementId, const Event&)> Callback;
				typedef std::unordered_map<ElementGid, Callback> ListenerMap;

				static ListenerMap listeners;
			};
			Scroll::ListenerMap Scroll::listeners;


			struct Click {
				struct Event {
					int x;
					int y;
				};

				typedef std::function<void(Canvas *, ElementId, const Event&)> Callback;

				typedef std::unordered_map<ElementGid, Callback> ListenerMap;
				static ListenerMap listeners;
			};
			Click::ListenerMap Click::listeners;

			struct DragStart {
				struct Event {
					int startX;
					int startY;

					int deltaX;
					int deltaY;
				};

				typedef std::function<void(Canvas *, ElementId, const Event&)> Callback;

				typedef std::unordered_map<ElementGid, Callback> ListenerMap;
				static ListenerMap listeners;
			};
			DragStart::ListenerMap DragStart::listeners;

			struct DragEnd {
				struct Event {
					int startX;
					int startY;

					int deltaX;
					int deltaY;
				};

				typedef std::function<void(Canvas *, ElementId, const Event&)> Callback;

				typedef std::unordered_map<ElementGid, Callback> ListenerMap;
				static ListenerMap listeners;
			};
			DragEnd::ListenerMap DragEnd::listeners;

			struct DragMove {
				struct Event {
					int startX;
					int startY;

					int deltaX;
					int deltaY;
				};

				typedef std::function<void(Canvas *, ElementId, const Event&)> Callback;

				typedef std::unordered_map<ElementGid, Callback> ListenerMap;
				static ListenerMap listeners;
			};
			DragMove::ListenerMap DragMove::listeners;
		};


		class Canvas {

			typedef std::unordered_map <ElementId, Element*> ElementMap;

			ElementId root_id;
			ElementId next_id;
			ElementId first_id;

			ElementMap elements;

		private:
			ElementId createElement() {
				ElementId id = next_id++;

				auto e = new Element(id);
				elements.insert(ElementMap::value_type(id, e));
				return id;
			}

			void destroyElements() {
				for (auto it = elements.begin(); it != elements.end(); ++it) {

					if (it->second->propsData != NULL){
						free(it->second->propsData);
					}

					delete it->second;

				}
				elements.clear();
			}

		CanvasId id;

		public:
			Canvas(CanvasId id) :
				id(id),
				root_id(0x32),
				first_id(0x42),
				next_id(first_id) {
			}			

			size_t find(float x, float y, std::vector<ElementId>& ids) {
				for (auto element : elements) {
					if (element.second->box.contains(x, y)) {
						ids.push_back(element.first);
					}
				}
				return ids.size();
			}

			Element& getRootElement() {
				return *(elements.find(root_id)->second);
			}

			Element& getElement(ElementId id) {
				return *(elements.find(id)->second);
			}
			
			const Element& getElement(ElementId id) const {
				return *(elements.find(id)->second);
			}


			ElementId appendChild(ElementId parent_id) {
				ElementId child_id = createElement();

				Element& child = getElement(child_id);
				Element& parent = getElement(parent_id);

				child.parent = parent_id;

				if (parent.firstChild == 0) {
					parent.firstChild = child_id;
				}

				if (parent.lastChild != 0) {
					Element& lastChild = getElement(parent.lastChild);

					lastChild.next = child_id;
					child.previous = parent.lastChild;
				}

				parent.lastChild = child_id;

				return child_id;
			}

			// ----------

			void setText(ElementId id, const std::string& text) {
				getElement(id).text = text;
			}
				

			// ----------

			float width; float height;

			void setSize(float width, float height){
				this->width = width;
				this->height = height;
			}

			// -----------------

			template <typename T>
			ElementId appendChild(ElementId parent_id, typename T::Props props) {
				ElementId id = appendChild(parent_id);

				setProps<T>(id, props);
				T::render(this, id, props);

				return id;
			}

			// -----------------

			template <typename T>
			void render(ElementId id, const typename T::Props& props) {
				Element& e = getElement(id);

				setProps<T>(id, props);
				T::render(this, id, props);
			}

			template <typename T>
			void render(const typename T::Props& props) {
				destroyElements();
				elements.insert(ElementMap::value_type(root_id, new Element(root_id)));
				next_id = first_id;

				render<T>(root_id, props);
				updateElementBox(root_id);
			}

			// -----------------

			template <typename T>
			void setProps(ElementId id, const typename T::Props& props) {
				Element&e = getElement(id);
				
				if (e.propsData != NULL) {
					free(e.propsData);
				}
				
				e.propsData = malloc(sizeof(typename T::Props));

				std::memcpy(e.propsData, &props, sizeof(typename T::Props));
			}

			template <typename T>
			const typename T::Props& getProps(ElementId id) const {
				const Element&e = getElement(id);

				assert(e.propsData != NULL);

				return *(typename T::Props *)e.propsData;
			}


			// -----------------


			template <class T>
			void setListener(ElementId id, typename T::Callback callback) {
				ElementGid gid = (this->id << 16) | id;

				auto it = T::listeners.find(gid);
				if (it != T::listeners.end()) {
					it->second = callback;
				}
				else {
					T::listeners.insert(T::ListenerMap::value_type(gid, callback));
				}
			}

			template <class T>
			bool notify(float x, float y, const typename T::Event& e){
				std::vector<ElementId> ids;

				find(x, y, ids);

				for (auto it = ids.begin(); it != ids.end(); ++it) {
					ElementGid gid = (this->id << 16) | *it;
					auto itListener = T::listeners.find(gid);
					if (itListener != T::listeners.end()) {
						itListener->second(this, *it, e);
						return true;
					}
				}

				return false;
			}


			// -----------------

			void updateElementBox(ElementId id){
				Element& e = getElement(id);
				Style& s = e.style;

				float x = 0.0f;

				if (e.parent != 0) {
					Element &p = getElement(e.parent);

					if (e.previous != 0 && (p.style.layout.type == Layout::HORIZONTAL)) {
						x = getElement(e.previous).box.xMax;
					}
					else {
						x = p.box.xMin;
					}
				}


				// refactor !!!!
				switch (s.width.type) {
				case Size::PIXEL:
					e.box.setX(x, x + (s.width.value));
					break;
				case Size::PERCENT:
					if (e.parent == 0) {
						e.box.setX(x, x);
					}
					else {
						e.box.setX(x, x + (getElement(e.parent).box.width() * s.width.value));
					}
					break;
				case Size::NONE:
					e.box.setY(x, x + 3);
					break;
				}
				// refactor !!!!


				float y = 0.0f;

				if (e.parent != 0) {
					Element &p = getElement(e.parent);

					if (e.previous != 0 && (p.style.layout.type == Layout::VERTICAL)) {
						y = getElement(e.previous).box.yMax;
					}
					else {
						y = p.box.yMin;
					}
				}

				// refactor !!!!
				switch (s.height.type) {
				case Size::PIXEL:
					e.box.setY(y, y + s.height.value);
					break;
				case Size::PERCENT:
					if (e.parent == 0) {
						e.box.setY(y, y + 3);
					}
					else {
						e.box.setY(y, y + (getElement(e.parent).box.height() * s.height.value));
					}
					break;
				case Size::NONE:
					e.box.setY(y, y + 3);
					break;
				}
				// refactor !!!!

				if (id == root_id) {
					e.box.setX(0, width);
					e.box.setY(0, height);
				}

				ElementId idChild = e.firstChild;

				while (idChild != 0) {
					updateElementBox(idChild);
					idChild = getElement(idChild).next;
				}
			}


			// -----------------

			void drawBox(NVGcontext* vg, const Box& box, const NVGcolor& color) {
				nvgBeginPath(vg);
				nvgRect(vg, box.xMin, box.yMin, box.width(), box.height());
				nvgFillColor(vg, color);
				nvgFill(vg);
				nvgClosePath(vg);
			}

			void drawElementBox(NVGcontext* vg, ElementId id) {
				Element &e = getElement(id);

				drawBox(vg, e.box, nvgHSLA((id * NVG_PI * 2) / elements.size(), 1.0f, 0.33f, 33));

				ElementId idChild = e.firstChild;

				while (idChild != 0) {
					drawElementBox(vg, idChild);
					idChild = getElement(idChild).next;
				}
			}

			void drawElementBox(NVGcontext* vg) {
				drawElementBox(vg, root_id);
			}

			// -----------------

			template <typename T>
			typename Callback<typename T> bindCallback(ElementId id, typename Callback<T>::Function function) const {
				Callback<T> cb;

				cb.element_id = id;
				cb.function = function;

				return cb;
			}

			template <typename T>
			void callCallback(const Callback<T>& cb, T value) {
				cb.function(this, cb.element_id, value);
			}

			

			// -----------------

			void draw(NVGcontext* vg, ElementId id) {
				Element &e = getElement(id);

				drawBox(vg, e.box, e.style.backgroundColor);
				nvgFontFace(vg, "sans");
				nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
				nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));

				if (!e.text.empty()){
					nvgFontSize(vg, e.box.height());
					nvgText(vg, e.box.xMin, e.box.yMin, e.text.c_str(), NULL);
				}

				ElementId idChild = e.firstChild;

				while (idChild != 0) {
					draw(vg, idChild);
					idChild = getElement(idChild).next;
				}
			}

			void draw(NVGcontext* vg) {
				// drawElementBox(vg);
				draw(vg, root_id);
			}

			// -----------------

	
		};

	}
}

#endif /* HOPE_SAMPLES_UI_UI_HANDLE_H */
