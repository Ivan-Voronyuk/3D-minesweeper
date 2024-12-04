#include <stdexcept>
#include <iostream>
#include <string>
#include "Graph_lib/Graph.h"
#include "Graph_lib/GUI.h"

using namespace Graph_lib;

struct Great_window:Window {
  Great_window (Point xy, int w, int h, const std::string& title);
private:
  Graph_lib::Button level_1;
  Graph_lib::Button level_2;
  Graph_lib::Button level_3;
  Graph_lib::Button but_exit;

  static void cb_level1(Address, Address);
  static void cb_level2(Address, Address);
  static void cb_level3(Address, Address);
  static void cb_exit(Address, Address);

  static void level1();
  static void level2();
  static void level3();
  static void exit();
  };

void Great_window::level1(){
  return;
}
void Great_window::level2(){
  return;
}
void Great_window::level3(){
  return;
}
void Great_window::exit(){
  return;
}

Great_window::Great_window(Point xy, int w, int h, const std::string& title):Window{xy, w, h, title},
  level_1{Point{x_max()-300, y_max() - 40}, 100, 30, "LEVEL 1",
    [ ] (Address, Address pw) {
      reference_to<Great_window>(pw).level1();
    }
  },
  level_2{Point{x_max()-300, y_max() - 90}, 100, 30, "LEVEL 2",
    [ ] (Address, Address pw) {
      reference_to<Great_window>(pw).level2();
    }
  },
  level_3{Point{x_max()-300, y_max() - 140}, 100, 30, "LEVEL 3", 
    [ ] (Address, Address pw) {
      reference_to<Great_window>(pw).level3();
    }
  },
  but_exit{Point{x_max()-300, y_max() - 190}, 100, 30, "EXIT", 
    [ ] (Address, Address pw) {
      reference_to<Great_window>(pw).exit();
    }
  }
{ 
  attach(level_1);
  attach(level_2);
  attach(level_3);
  attach(but_exit);
}

int main ()
try
{
  setlocale(LC_ALL, "RU");

  Great_window win(Point{100, 100}, 700, 500, "menu");
  return gui_main();

  
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr << "Oops, something went wrong..." << std::endl;
  return 2;
}