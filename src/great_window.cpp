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
  }
{ 
  attach(level_1);
  attach(level_2);
  attach(level_3);
  attach(but_exit);
}

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