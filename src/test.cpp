#include "Graph_lib/GUI.h"
#include "Graph_lib/Point.h"
#include "Graph_lib/Window.h"
#include "game.h"

class MainWindow : Graph_lib::Window {
 private:
  Graph_lib::InteractableCanvas interactive_canvas;
  Game game;

 public:
  MainWindow(Graph_lib::Point xy, int w, int h, const std::string& title)
      : Graph_lib::Window{xy, w, h, title},
        interactive_canvas{Graph_lib::Point(0, 0), w, h, "canvas",
                           [](Graph_lib::Address, Graph_lib::Address pw) { printf("callback"); }},
        game{w, h, 0.7, "./texture.pnm"} {
    interactive_canvas.set_click_handler([this](int x, int y, char b) {
      this->game.click_callback(x, y, b);
      this->game.canvas.clear(Render::Color{128, 128, 128});
      this->game.cube.render(this->game.canvas);
      printf("%d\n", this->game.canvas.tex.get_at(256, 256).r);
      printf("%llx\n", this->game.canvas.tex.unsafe_get_data_view());
    });
    interactive_canvas.set_drag_handler([this](int x0, int y0, int x1, int y1) {
      printf("drag callback");
      this->game.drag_callback(x0, y0, x1, y1);
      this->game.canvas.clear(Render::Color{128, 128, 128});
      this->game.cube.render(this->game.canvas);
    });
    attach(interactive_canvas);
    interactive_canvas.set_image_view(game.canvas.tex.unsafe_get_data_view());
  }
};

int main() {
  MainWindow window{Graph_lib::Point{0, 0}, 512, 512, "test"};
  return Graph_lib::gui_main();
}
