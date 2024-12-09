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
  Graph_lib::Text ts;

  static void cb_level1(Address, Address);
  static void cb_level2(Address, Address);
  static void cb_level3(Address, Address);

  int level1();
  int level2();
  int level3();
};

struct Level1_window:Window {
  Level1_window (Point xy, int w, int h, const std::string& title);
private:
  Graph_lib::Text l1txt;
  Graph_lib::Rectangle rect01; // наш кубик
  Graph_lib::Out_box box_out1; // поле для отображения количества мин 
  // Fl_Timer timeer; объявление секундомера
};

struct Level2_window:Window {
  Level2_window (Point xy, int w, int h, const std::string& title);
private:
  Graph_lib::Text l2txt;
  Graph_lib::Rectangle rect02; // наш кубик
  Graph_lib::Out_box box_out2; // поле для отображения количества мин 
};

struct Level3_window:Window {
  Level3_window (Point xy, int w, int h, const std::string& title);
private:
  Graph_lib::Text l3txt;
  Graph_lib::Rectangle rect03; // наш кубик
  Graph_lib::Out_box box_out3; // поле для отображения количества мин 
};
