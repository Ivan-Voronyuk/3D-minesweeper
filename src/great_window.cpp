#include "great_window.h"

Great_window::Great_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  level_1{Point{x_max()-480, y_max() - 350}, 260, 60, "LEVEL 1",
    [ ] (Address, Address pw) {
      reference_to<Great_window>(pw).level1();
    }
  },
  level_2{Point{x_max()-480, y_max() - 280}, 260, 60, "LEVEL 2",
    [ ] (Address, Address pw) {
      reference_to<Great_window>(pw).level2();
    }
  },
  level_3{Point{x_max()-480, y_max() - 210}, 260, 60, "LEVEL 3", 
    [ ] (Address, Address pw) {
      reference_to<Great_window>(pw).level3();
    }
  },
  but_exit{Point{x_max()-480, y_max() - 140}, 260, 60, "EXIT", 
    [ ] (Address, Address pw) {
      reference_to<Great_window>(pw).exit();
    }
  },
  ts{Point {x_max()-530, y_max() - 410}, "3D-MINESWEEPER"}
{
  ts.set_font(Font::times_bold);
  ts.set_color(Color::dark_cyan);
  ts.set_font_size(40);
  attach(level_1);
  attach(level_2);
  attach(level_3);
  attach(but_exit);
  attach(ts);
}

int Great_window::level1(){
  Level1_window win_l1(Point{100, 100},700, 500, "3D-MINESWEEPER_LEVEL_1");
  return gui_main();
}
void Great_window::level2(){
  return;
}
void Great_window::level3(){
  return;
}
void Great_window::exit(){
  hide();
}

Level1_window::Level1_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  but_quit{Point {30, y_max() - 350}, 260, 60, "EXIT",
    [ ] (Address, Address pw) {
      reference_to<Level1_window>(pw).quit_func();
    }
  },
  ltxt{Point {x_max()-100, y_max() - 100}, "LEVEL 1"}
{ 
  attach(but_quit);
  attach(ltxt);
}

void Level1_window::quit_func(){
  hide();
}
