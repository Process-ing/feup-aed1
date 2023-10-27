#ifndef FEUP_AED1_DATASET_H
#define FEUP_AED1_DATASET_H
#include "UcClass.h"

class Dataset {
public:
    /**
     * Reads UcClass data from a file and populates the dataset.
     * @author Diogo Vieira
     */
    void UcsReader();

    /**
     * Reads UcClass data from a file and populates the dataset.
     * @author Diogo Vieira
     */
    void UcClassReader();

    /**
     * Find a specific UcClass based on its unique code and class code.
     *
     * @param uc_code The unique code of the UcClass to find.
     * @param code_of_class The class code of the UcClass to find.
     * @return The found UcClass, or an empty one if not found.
     * @author Diogo Vieira
     */
    UcClass findUcClass(string uc_code, string code_of_class);

private:
    vector<UcClass> all_classes; ///< A vector containing all UcClass objects in the dataset.
};

#endif //FEUP_AED1_DATASET_H
