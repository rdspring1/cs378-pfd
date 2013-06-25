// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------
#include "PFD.h"
#include <iostream> // cin, cout, ios_base
#include <queue>

// ----
// main
// ----

int main () {
    using namespace std;
	int pfd_graph[MAX_SIZE][MAX_SIZE]; 
	priority_queue< int, vector<int>, greater<int> > min_heap;
		
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    pfd_solve(cin, cout, pfd_graph, min_heap);
    return 0;
}
