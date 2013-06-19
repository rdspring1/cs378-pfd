// -------------------------------
// projects/pfd/RunPFD.c++
// Ryan Spring
// Jung (James) Lee
// -------------------------------

/*
To run the program:
    % g++ -ansi -pedantic -Wall RunPFD.c++ -o RunPFD.c++.app
    % valgrind RunPFD.c++.app < RunPFD.in >& RunPFD.out

To configure Doxygen:
    % doxygen -g
That creates the file "Doxyfile".
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout, ios_base

#include "PFD.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    pfd_solve(cin, cout);
    return 0;}
