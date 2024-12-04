
#include "Graph_lib/Graph.h"
#include "Graph_lib/Simple_window.h"

using namespace Graph_lib;

#include <stdexcept>
#include <iostream>

int main (int argc, char **argv)
try
{
  setlocale(LC_ALL, "RU");

  Point t1{100, 100};

  Simple_window win{t1, 800, 600, "3D_saper"};
  win.wait_for_button();

  Graph_lib::Rectangle cell{Point{200, 200}, 30, 30};
  //cell.set_fill_color(Color::blue);
  win.attach(cell);
  win.wait_for_button();
  
  
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