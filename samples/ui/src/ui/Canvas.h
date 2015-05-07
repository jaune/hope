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

	typedef uint16_t StyleId;

	struct Style {
		StyleId id;
		Size height;
		Size width;
		Layout layout;
	};

	struct Metrics {
		float height;
		float width;
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


		Box box;
		float z;
		Style style;
		Metrics metrics;

		Element(ElementId id) :
			id(id),
			parent(0),

			next(0),
			previous(0),

			firstChild(0),
			lastChild(0),

			z(0.f) {
		}
	};



	struct Text {
	public:
		std::string text;
		
		Text(const std::string& text) :
			text(text) {
		}

	};

	typedef uint32_t ElementGid;

	typedef uint8_t CanvasId;
	class Canvas;

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
		


		struct DragAndDropBegin {
			typedef std::function<void()> Callback;
		};

		struct DragAndDropEnd {
			typedef std::function<void()> Callback;
		};

		struct DragAndDropMove {
			typedef std::function<void()> Callback;
		};
	};


	class Canvas {
		
		typedef std::unordered_map <ElementId, Element*> ElementMap;
		typedef std::unordered_map <ElementId, Text*> TextMap;
				
		ElementId root_id;
		ElementId next_id;

		ElementMap elements;
		TextMap texts;

		ElementId createElement() {
			ElementId id = next_id++;

			auto e = new Element(id);

			elements.insert(ElementMap::value_type(id, e));

			return id;
		}
		CanvasId id;

	public:
		Canvas(CanvasId id) :
			id(id),
			root_id(0x32),
			next_id(0x42) {

			elements.insert(ElementMap::value_type(0x32, new Element(0x32)));
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

		ElementId appendChildToRoot() {
			return appendChild(0x32);
		}

		template <typename T>
		ElementId appendChildToRoot(typename T::Props props) {
			ElementId id = appendChildToRoot();
			
			T::create(this, id, props);

			return id;
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

		template <typename T> 
		ElementId appendChild(ElementId parent_id, typename T::Props props) {
			ElementId id = appendChild(parent_id);
			
			setProps<T>(id, props);

			T::create(this, id, props);

			return id;
		}		


		StyleId createStyle() {
		}



		void setText(ElementId id, const std::string& text) {
			auto it = texts.find(id);

			if (it == texts.end()) {
				texts.insert(TextMap::value_type(id, new Text(text)));
			}
			else {
				it->second->text = text;
			}
		}


		void setRootSize(float width, float height){
			Element& root = getRootElement();

			root.metrics.width = width;
			root.metrics.height = height;

			root.style.width = Size::px(width);
			root.style.height = Size::px(height);
		}
		

		// -----------------

		template <typename T>
		void setProps(ElementId id, const typename T::Props& props) {
			ElementGid gid = (this->id << 16) | id;

			T::props.insert(T::PropsMap::value_type(gid, props));
		}

		template <typename T>
		const typename T::Props& getProps(ElementId id) const {
			ElementGid gid = (this->id << 16) | id;
			
			auto it = T::props.find(gid);
			assert(it != T::props.end());
			return it->second;
		}
		

		// -----------------


		template <class T>
		void addListener(ElementId id, typename T::Callback callback) {
			ElementGid gid = (this->id << 16) | id;
			T::listeners.insert(T::ListenerMap::value_type(gid, callback));
		}

		template <class T>
		void notify(float x, float y, const typename T::Event& e){
			std::vector<ElementId> ids;
			
			find(x, y, ids);

			for (auto it = ids.begin(); it != ids.end(); ++it) {
				ElementGid gid = (this->id << 16) | *it;
				auto itListener = T::listeners.find(gid);
				if (itListener != T::listeners.end()) {
					itListener->second(this, *it, e);
				}
			}
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
			

			ElementId idChild = e.firstChild;

			while (idChild != 0) {
				updateElementBox(idChild);
				idChild = getElement(idChild).next;
			}

		}


		void updateElementBox(){
			updateElementBox(root_id);
		}

// -----------------

		void drawElementBox(NVGcontext* vg, const Box& box, const NVGcolor& color) {
			nvgBeginPath(vg);
			nvgRect(vg, box.xMin, box.yMin, box.width(), box.height());
			nvgFillColor(vg, color);
			nvgFill(vg);
			nvgClosePath(vg);
		}

		void drawElementBox(NVGcontext* vg, ElementId id) {
			Element &e = getElement(id);

			drawElementBox(vg, e.box, nvgHSLA((id * NVG_PI * 2) / elements.size(), 1.0f, 0.55f, 33));

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

	void draw(NVGcontext* vg, ElementId id) {
		Element &e = getElement(id);

		auto it = texts.find(id);
		
		if (it != texts.end()){
			nvgFontSize(vg, e.box.height());
			nvgText(vg, e.box.xMin, e.box.yMin, it->second->text.c_str(), NULL);
		}

		ElementId idChild = e.firstChild;

		while (idChild != 0) {
			draw(vg, idChild);
			idChild = getElement(idChild).next;
		}
	}

	void draw(NVGcontext* vg) {
		nvgFontFace(vg, "roboto-regular");
		nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
		nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));

		draw(vg, root_id);
	}

// -----------------

	};
	
}
}

#endif /* HOPE_SAMPLES_UI_UI_HANDLE_H */
