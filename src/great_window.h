#include "Graph_lib/Graph.h"
#include "Graph_lib/GUI.h"
#include "Graph_lib/Window.h"

#include <string>

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
