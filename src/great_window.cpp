#include "great_window.h"
#include <string>

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
  ts{Point {x_max()-530, y_max() - 410}, "3D-MINESWEEPER"}
{
  ts.set_font(Font::times_bold);
  ts.set_color(Color::dark_cyan);
  ts.set_font_size(40);
  attach(level_1);
  attach(level_2);
  attach(level_3);
  attach(ts);
}

// функции по вызову окон разных уровней
int Great_window::level1(){
  Level1_window win_l1(Point{100, 100}, 1000, 500, "3D-MINESWEEPER_LEVEL_1");
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

Level1_window::Level1_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  l1txt{Point {30, 30}, "LEVEL 1"},
  box_out1{Point{100, 100}, 30, 30, "Мин осталось:"},// поле количества оставшихся мин
  // timeer{FL_VALUE_TIMER, 200, 100, 100, 50, "S"} было бы здорово, но у меня не получилось добавить секундомер
  //---------------------------------------------Потом удалить--------------------------------------
  cube1{Point{x_max()-300, y_max() - 300}, 200, 200, "LEVEL 1",
    [ ] (Address, Address pw) {
      reference_to<Level1_window>(pw).cube1_func();
    }
  }
  //---------------------------------------------Потом удалить--------------------------------------
{ 
  int num = 10; // переменая для хранения количества мин
  std::string n_str = std::to_string(num);
  l1txt.set_color(Color::dark_green);
  l1txt.set_font_size(20);
  l1txt.set_font(Font::times_bold_italic);
  attach(l1txt); 
  attach(box_out1);
  box_out1.put(n_str);
  // Fl::add_timeout(timeer); для секундомера
  attach(cube1);
}

Level2_window::Level2_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  l2txt{Point {30, 30}, "LEVEL 2"},
  box_out2{Point{100, 100}, 30, 30, "Мин осталось:"},// поле количества оставшихся мин
  //---------------------------------------------Потом удалить--------------------------------------
  cube2{Point{x_max()-300, y_max() - 300}, 200, 200, "LEVEL 2",
    [ ] (Address, Address pw) {
      reference_to<Level2_window>(pw).cube2_func();
    }
  }
  //---------------------------------------------Потом удалить--------------------------------------

{ 
  int num = 10; // переменая для хранения количества мин
  std::string n_str = std::to_string(num);
  l2txt.set_color(Color::dark_yellow);
  l2txt.set_font_size(20);
  l2txt.set_font(Font::times_bold_italic);
  attach(l2txt);
  attach(cube2);
  attach(box_out2);
  box_out2.put(n_str);
}

Level3_window::Level3_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  l3txt{Point {30, 30}, "LEVEL 3"},
  box_out3{Point{100, 100}, 30, 30, "Мин осталось:"}, // поле количества оставшихся мин
  //---------------------------------------------Потом удалить--------------------------------------
  cube3{Point{x_max()-300, y_max() - 300}, 200, 200, "LEVEL 3",
    [ ] (Address, Address pw) {
      reference_to<Level3_window>(pw).cube3_func();
    }
  }
  //---------------------------------------------Потом удалить--------------------------------------

{ 
  int num = 10; // переменая для хранения количества мин
  std::string n_str = std::to_string(num);
  l3txt.set_color(Color::red);
  l3txt.set_font_size(20);
  l3txt.set_font(Font::times_bold_italic);
  attach(l3txt);
  attach(box_out3);
  box_out3.put(n_str);
  attach(cube3);
}
  //---------------------------------------------Потом удалить--------------------------------------
void Level1_window::cube1_func(){
  return;
}

void Level2_window::cube2_func(){
  return;
}

void Level3_window::cube3_func(){
  return;
}
  //---------------------------------------------Потом удалить--------------------------------------