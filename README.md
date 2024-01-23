# FEUP-AED1 - SchAEDuler

Repository for the first project of the [Algorithms and Data Structures](https://sigarra.up.pt/feup/pt/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=520316) course, at [FEUP](https://sigarra.up.pt/feup/pt/web_page.inicial).

## Objectives of the Project

The main goal of the project is to create a schedule management system for FEUP's informatic system, with various functionalities related to schedules, such as modifying, searching, viewing, sorting and listing, among others. This project also focuses on the usage of linear and hierarchical data structures (vector, list, set, queue, stack, ...), as well as sorting and search algorithms.

## Instructions to Run

1. Clone the repository
2. Run the following commands on the terminal:
    ```
    cd feup-aed1                   # Open project
    mkdir build && cd build        # Create and open build directory
    cmake .. && cmake --build .    # Build project
    ./feup-aed1                    # Run project
    ```

## Tips and Tricks (for anyone doing a similar project)

 - To reference efficiently objects in certain data structures (such as UcClasses), we used iterators, which worked well because those data structures were not modified after reading the dataset, but if you need to do modifications, this solution is not viable. In either case, we recommend using smart pointers, which were what we used in our second project, as they are much more reliable and flexible.
 - When they say to use the linear and hierarchical data structures, use ALL of them. We change the `request_archive_` field in the `Dataset` class from a stack to a deque last minute, because of the efficiency when saving to file. Although we explained in our presentation that we were using the deque basically as a stack, we still received no points in the stack "part" :') 

 ## Contributors and Results

  - [Bruno Oliveira](https://github.com/Process-ing)
  - [Diogo Vieira](https://github.com/DiogoSV7)
  - [João Mendes](https://github.com/The-Memechanic)

Grade: 19.25/20 (would be 19.75 if we used a stack :') )


