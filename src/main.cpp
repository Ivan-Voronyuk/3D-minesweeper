#include <stdexcept>
#include <iostream>
#include <string>

#include "great_window.h"

using namespace Graph_lib;

int main ()
try
{
  setlocale(LC_ALL, "RU");

  Great_window win(Point{100, 100},700, 500, "3D-MINESWEEPER");
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