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
  Level1_window* win_l1 = new Level1_window(Point{100, 100}, 1000, 500, "3D-MINESWEEPER_LEVEL_1");
  return gui_main();
}
int Great_window::level2(){
  Level2_window win_l2(Point{100, 100},1000, 500, "3D-MINESWEEPER_LEVEL_2");
  return gui_main();
}
int Great_window::level3(){
  Level3_window win_l3(Point{100, 100},1000, 500, "3D-MINESWEEPER_LEVEL_3");
  return gui_main();
}
void Great_window::exit(){
  hide();
}

Level1_window::Level1_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  but_quit{Point {15, y_max() - 70}, 100, 50, "EXIT",
    [ ] (Address, Address pw) {
      reference_to<Level1_window>(pw).quit_func1();
    }
  },
  but_return{Point {15, y_max() - 140}, 100, 50, "RETURN",
    [ ] (Address, Address pw) {
      reference_to<Level1_window>(pw).return_func1();
    }
  },
  l1txt{Point {30, 30}, "LEVEL 1"}
{ 
  l1txt.set_color(Color::dark_green);
  l1txt.set_font_size(20);
  l1txt.set_font(Font::times_bold_italic);
  attach(but_quit);
  attach(l1txt);
  attach(but_return);
}

int Level1_window::return_func1(){
  Great_window win(Point{100, 100},700, 500, "3D-MINESWEEPER");
  return gui_main(); 

}

Level2_window::Level2_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  but_quit{Point {15, y_max() - 70}, 100, 50, "EXIT",
    [ ] (Address, Address pw) {
      reference_to<Level2_window>(pw).quit_func2();
    }
  },
  l2txt{Point {30, 30}, "LEVEL 2"}
{ 
  l2txt.set_color(Color::dark_yellow);
  l2txt.set_font_size(20);
  l2txt.set_font(Font::times_bold_italic);
  attach(but_quit);
  attach(l2txt);
}

Level3_window::Level3_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  but_quit{Point {15, y_max() - 70}, 100, 50, "EXIT",
    [ ] (Address, Address pw) {
      reference_to<Level3_window>(pw).quit_func3();
    }
  },
  l3txt{Point {30, 30}, "LEVEL 3"}
{ 
  l3txt.set_color(Color::red);
  l3txt.set_font_size(20);
  l3txt.set_font(Font::times_bold_italic);
  attach(but_quit);
  attach(l3txt);
}

void Level1_window::quit_func1(){
  hide();
}

void Level2_window::quit_func2(){
  hide();
}

void Level3_window::quit_func3(){
  hide();
}
