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
  Graph_lib::Text ts;

  static void cb_level1(Address, Address);
  static void cb_level2(Address, Address);
  static void cb_level3(Address, Address);
  static void cb_exit(Address, Address);

  int level1();
  int level2();
  int level3();
  void exit();
  };

struct Level1_window:Window {
  Level1_window (Point xy, int w, int h, const std::string& title);
private:
  Graph_lib::Button but_quit;
  Graph_lib::Text l1txt;

  static void cb_quit_func1(Address, Address);

  void quit_func1();
};

struct Level2_window:Window {
  Level2_window (Point xy, int w, int h, const std::string& title);
private:
  Graph_lib::Button but_quit;
  Graph_lib::Text l2txt;

  static void cb_quit_func2(Address, Address);

  void quit_func2();
};

struct Level3_window:Window {
  Level3_window (Point xy, int w, int h, const std::string& title);
private:
  Graph_lib::Button but_quit;
  Graph_lib::Text l3txt;

  static void cb_quit_func3(Address, Address);

  void quit_func3();
};
