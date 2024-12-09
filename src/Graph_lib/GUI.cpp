#include "GUI.h"

#include <sstream>
#include <stdexcept>
#include <string>

using namespace Graph_lib;

void Button::attach(Window& win) {
  pw = new Fl_Button{loc.x, loc.y, width, height, label.c_str()};
  pw->callback(reinterpret_cast<Fl_Callback*>(do_it), this);  // pass this widget
  own = &win;
}

int In_box::get_int() {
  Fl_Input& pi = reference_to<Fl_Input>(pw);
  const char* p = pi.value();
  if (!isdigit(p[0])) return -999999;
  return atoi(p);
}

std::string In_box::get_string() {
  Fl_Input& pi = reference_to<Fl_Input>(pw);
  return std::string(pi.value());
}

void In_box::attach(Window& win) {
  pw = new Fl_Input{loc.x, loc.y, width, height, label.c_str()};
  own = &win;
}

void Out_box::put(int i) {
  Fl_Output& po = reference_to<Fl_Output>(pw);
  std::stringstream ss;
  ss << i;
  po.value(ss.str().c_str());
}

void Out_box::put(const std::string& s) { reference_to<Fl_Output>(pw).value(s.c_str()); }

void Out_box::attach(Window& win) {
  pw = new Fl_Output{loc.x, loc.y, width, height, label.c_str()};
  own = &win;
}

int Menu::attach(Button& b) {
  b.width = width;
  b.height = height;

  switch (k) {
    case horizontal:
      b.loc = Point{loc.x + offset, loc.y};
      offset += b.width;
      break;
    case vertical:
      b.loc = Point{loc.x, loc.y + offset};
      offset += b.height;
      break;
  }
  selection.push_back(&b);
  return int(selection.size() - 1);
}

int Menu::attach(Button* p) {
  //  owned.push_back(p);
  return attach(*p);
}

InteractableCanvas::InteractableCanvas(Point xy, int w, int h, const std::string& label, Callback callback)
    : Widget{
          xy, w, h, label, callback,
      } {
  // p = new Fl_RGB_Image(image_view, w, h);
}
void InteractableCanvas::attach(Window& window) {
  interractable = new Fl_InterractableSpace(loc.x, loc.y, width, height, "");

  interractable->set_handler([this](int event) -> int {
    static int dist = 0;
    static int x0 = 0, y0 = 0;
    switch (event) {
      case FL_PUSH:
        x0 = Fl::event_x();
        y0 = Fl::event_y();
        dist = 0;
        return 1;
      case FL_DRAG: {
        int x = Fl::event_x();
        int y = Fl::event_y();
        if (this->drag_handler) this->drag_handler(x0, y0, x, y);
        dist += std::abs(x - x0) + std::abs(y - y0);
        x0 = x;
        y0 = y;
      }
        this->interractable->redraw();
        return 1;
      case FL_RELEASE: {
        if (dist > 10) return 0;
        auto b = Fl::event_button();
        if (this->click_handler) switch (b) {
            case FL_LEFT_MOUSE:
              this->click_handler(x0, y0, 'l');
              break;
            case FL_RIGHT_MOUSE:
              this->click_handler(x0, y0, 'r');
              break;
            case FL_MIDDLE_MOUSE:
              this->click_handler(x0, y0, 'm');
              break;
          }
      }
        this->interractable->redraw();
        return 1;
      default:
        return 0;
    }
  });

  pw = interractable;
}

void InteractableCanvas::set_image_view(const uchar* image_view) {
  printf("set_image_view(%llx)\n", image_view);
  if (interractable && image_view) {
    interractable->set_image(new Fl_RGB_Image(image_view, width, height));
  } else {
    throw std::runtime_error("set_image_view must be called after attach");
  }
}
void InteractableCanvas::set_click_handler(std::function<void(int, int, char)> handler) {
  this->click_handler = handler;
}
void InteractableCanvas::set_drag_handler(std::function<void(int, int, int, int)> handler) {
  this->drag_handler = handler;
}
