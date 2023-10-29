#ifndef FEUP_AED1_MENU_H
#define FEUP_AED1_MENU_H

#include <string>
#include "Dataset.h"

class Menu {
  public:
    explicit Menu(Dataset& dataset);

    void launch() const;

  private:
    enum SortOption {
        ALPHABETICAL_ORDER = 1,
        REVERSE_ALPHABETICAL_ORDER = 2,
        ASCENDING_CODES = 3,
        DESCENDING_CODES = 4,
    };

    Dataset &dataset_;

    void searchMenu() const;
    static SortOption sortMenu();

    static int receiveOption(int max);
    static void waitForEnter();
};


#endif //FEUP_AED1_MENU_H
