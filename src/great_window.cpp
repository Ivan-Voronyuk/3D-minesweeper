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
  rect01{Point{600, 200}, 200, 100}, // положение кубика
  box_out1{Point{100, 100}, 30, 30, "Мин осталось:"} // поле количества оставшихся мин
  // timeer{FL_VALUE_TIMER, 200, 100, 100, 50, "S"} было бы здорово, но у меня не получилось добавить секундомер
{ 
  int num = 10; // переменая для хранения количества мин
  std::string n_str = std::to_string(num);
  l1txt.set_color(Color::dark_green);
  l1txt.set_font_size(20);
  l1txt.set_font(Font::times_bold_italic);
  attach(l1txt); 
  attach(rect01);
  rect01.set_fill_color(Color::green); // наверное надо будет удалить, это добавлено было просто так
  attach(box_out1);
  box_out1.put(n_str);
  // Fl::add_timeout(timeer); для секундомера
}

Level2_window::Level2_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  l2txt{Point {30, 30}, "LEVEL 2"},
  rect02{Point{600, 200}, 200, 100}, // положение кубика
  box_out2{Point{100, 100}, 30, 30, "Мин осталось:"} // поле количества оставшихся мин
{ 
  int num = 10; // переменая для хранения количества мин
  std::string n_str = std::to_string(num);
  l2txt.set_color(Color::dark_yellow);
  l2txt.set_font_size(20);
  l2txt.set_font(Font::times_bold_italic);
  attach(l2txt);
  attach(rect02);
  rect02.set_fill_color(Color::dark_yellow); // наверное надо будет удалить, это добавлено было просто так
  attach(box_out2);
  box_out2.put(n_str);
}

Level3_window::Level3_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  l3txt{Point {30, 30}, "LEVEL 3"},
  rect03{Point{600, 200}, 200, 100}, // положение кубика
  box_out3{Point{100, 100}, 30, 30, "Мин осталось:"} // поле количества оставшихся мин
{ 
  int num = 10; // переменая для хранения количества мин
  std::string n_str = std::to_string(num);
  l3txt.set_color(Color::red);
  l3txt.set_font_size(20);
  l3txt.set_font(Font::times_bold_italic);
  attach(l3txt);
  attach(rect03);
  rect03.set_fill_color(Color::dark_red); // наверное надо будет удалить, это добавлено было просто так
  attach(box_out3);
  box_out3.put(n_str);
}
