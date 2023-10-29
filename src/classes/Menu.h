#ifndef FEUP_AED1_MENU_H
#define FEUP_AED1_MENU_H

#include <string>
#include "Dataset.h"

class Menu {
  public:
    explicit Menu(Dataset& dataset);

    void launch() const;

  private:
    Dataset &dataset_;

    static int receiveOption(int max);
    static void waitForEnter();
};


#endif //FEUP_AED1_MENU_H
