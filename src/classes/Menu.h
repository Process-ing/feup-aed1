#ifndef FEUP_AED1_MENU_H
#define FEUP_AED1_MENU_H

#include <string>
#include "Dataset.h"

/**
 * @brief Object responsible for all project's UI/UX.
 * @details It makes all the calls to the dataset, based on the user's input.
 */
class Menu {
  public:
    /**
     * @brief Constructor of the class.
     * @param dataset Dataset for the menu to use.
     */
    explicit Menu(Dataset& dataset);

    /**
     * @brief Launches the menu, starting on the welcome screen.
     */
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