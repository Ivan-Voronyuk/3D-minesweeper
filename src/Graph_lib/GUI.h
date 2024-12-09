//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#ifndef GUI_GUARD
#define GUI_GUARD

#include "Graph.h"
#include "Window.h"

namespace Graph_lib {

//------------------------------------------------------------------------------

using Address = void*;                        // Address is a synonym for void*
using Callback = void (*)(Address, Address);  // FLTK's required function type for all callbacks

//------------------------------------------------------------------------------

template <class W>
W& reference_to(Address pw)
// treat an address as a reference to a W
{
  return *static_cast<W*>(pw);
}

//------------------------------------------------------------------------------

class Widget {
  // Widget is a handle to an Fl_widget - it is *not* an Fl_widget
  // We try to keep our interface classes at arm's length from FLTK

 public:
  Widget(Point xy, int w, int h, const std::string& s, Callback cb)
      : loc{xy}, width{w}, height{h}, label{s}, do_it{cb} {}

  virtual void move(int dx, int dy) {
    hide();
    pw->position(loc.x += dx, loc.y += dy);
    show();
  }

  virtual void hide() { pw->hide(); }

  virtual void show() { pw->show(); }

  virtual void attach(Window&) = 0;

  Window& window() { return *own; }

  Point loc;
  int width;
  int height;
  std::string label;
  Callback do_it;

  virtual ~Widget() {}

  Widget& operator=(const Widget&) = delete;  // don't copy Widgets
  Widget(const Widget&) = delete;

 protected:
  Window* own;    // every Widget belongs to a Window
  Fl_Widget* pw;  // connection to the FLTK Widget
};

//------------------------------------------------------------------------------

struct Button : Widget {
  Button(Point xy, int w, int h, const std::string& label, Callback cb) : Widget{xy, w, h, label, cb} {}

  void attach(Window&);
};

//------------------------------------------------------------------------------

struct In_box : Widget {
  In_box(Point xy, int w, int h, const std::string& s) : Widget{xy, w, h, s, nullptr} {}

  int get_int();
  std::string get_string();

  void attach(Window& win);
};

//------------------------------------------------------------------------------

struct Out_box : Widget {
  Out_box(Point xy, int w, int h, const std::string& s) : Widget{xy, w, h, s, nullptr} {}

  void put(int);
  void put(const std::string&);

  void attach(Window& win);
};

//------------------------------------------------------------------------------

struct Menu : Widget {
  enum Kind { horizontal, vertical };

  Menu(Point xy, int w, int h, Kind kk, const std::string& label)
      : Widget{xy, w, h, label, nullptr}, k{kk}, offset{0} {}

  Vector_ref<Button> selection;
  Kind k;
  int offset;

  int attach(Button& b);  // Menu does not delete &b
  int attach(Button* p);  // Menu deletes p

  void show()  // show all buttons
  {
    for (int i = 0; i < selection.size(); ++i) selection[i].show();
  }

  void hide()  // hide all buttons
  {
    for (int i = 0; i < selection.size(); ++i) selection[i].hide();
  }

  void move(int dx, int dy)  // move all buttons
  {
    for (int i = 0; i < selection.size(); ++i) selection[i].move(dx, dy);
  }

  void attach(Window& win)  // attach all buttons
  {
    for (int i = 0; i < selection.size(); ++i) win.attach(selection[i]);
    own = &win;
  }
};

class InteractableCanvas : public Widget {
 public:
  InteractableCanvas(Point xy, int w, int h, const std::string& label, Callback callback);

  virtual ~InteractableCanvas() override { delete interractable; }

  void move(int dx, int dy) override {
    // Shape::move(dx, dy);
    // image->draw(point(0).x, point(0).y);
    loc.x += dx;
    loc.y += dy;
    this->interractable->position(loc.x, loc.y);
  }
  void set_click_handler(std::function<void(int, int, char)>);
  void set_drag_handler(std::function<void(int, int, int, int)>);
  void set_image_view(const uchar* image_view);

 private:
  class Fl_InterractableSpace : public Fl_Widget {
    std::function<int(int)> actual_handler = nullptr;
    Fl_RGB_Image* img = nullptr;

   public:
    Fl_InterractableSpace(int x, int y, int w, int h, const char* label) : Fl_Widget(x, y, w, h, label){};
    void set_handler(std::function<int(int)> handler) { actual_handler = handler; }
    void set_image(Fl_RGB_Image* img) {
      delete this->img;
      this->img = img;
    }
    virtual int handle(int event) override { return actual_handler ? actual_handler(event) : 0; }
    virtual void draw() override {
      printf("draw canvas\n");
      if (img) img->uncache();
      if (img) img->draw(this->x(), this->y());
      if (!img) printf("No image yet!\n");
    }
    virtual ~Fl_InterractableSpace() {
      // if (img) delete img;
      Fl_Widget::~Fl_Widget();
    }
  };

  Fl_InterractableSpace* interractable = nullptr;
  std::function<void(int, int, char)> click_handler = nullptr;
  std::function<void(int, int, int, int)> drag_handler = nullptr;

  int interraction_handlert(int event);
  virtual void attach(Window& window) override;
};

//------------------------------------------------------------------------------

}  // namespace Graph_lib

#endif  // GUI_GUARD
