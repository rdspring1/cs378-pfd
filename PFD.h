// --------
// includes
// --------
#include <queue>
#include <cassert>
#include <iostream>

using namespace std;

// CONSTANTS
#define MAX_SIZE 101
#define INITIAL_VALUE -1
#define PASS -2

/**
 * Generates the graph by reading from the istream
 * @param input	std::istream
 * @param pfd_graph A graph representing the partial ordering of the PFD problem 
 * @return return the number of tasks for the problem if the function succeeds, -1 otherwise
 */
int pfd_read (istream& input, int pfd_graph[][MAX_SIZE]); 

/**
 * Removes the number added to min_heap from pfd_graph
 * @param needClean an integer that needs to be removed from the graph
 * @param initial_total_task the original number of tasks for the PFD problem
 * @param pfd_graph A graph representing the partial ordering of the PFD problem 
 */
void pfd_clean(int needClean, int initial_total_task, int pfd_graph[][MAX_SIZE]);

/**
 * Adds the first vertex that does not have any prerequisites to min_heap
 * After finding the vertex, the function pfd_clean is run.
 * The function pfd_clean removes the vertex from the pfd_graph
 * @param task_left the number of tasks for the PFD problem
 * @param initial_total_task the original number of tasks for the PFD problem
 * @param pfd_graph A graph representing the partial ordering of the PFD problem 
 * @param min_heap A heap maintaining the list of vertices that have been removed
 */
void pfd_remove(int& task_left, int& initial_total_task, int pfd_graph[][MAX_SIZE], priority_queue< int, vector<int>, greater<int> >& min_heap);

/**
 * read, eval, print loop for solving the PFD sphere problem
 * @param std::istream
 * @param output a std::ostream
 * @param pfd_graph A graph representing the partial ordering of the PFD problem 
 * @param min_heap A heap maintaining the list of vertices that have been removed
 */
void pfd_solve (istream& input, ostream& output, int pfd_graph[][MAX_SIZE], priority_queue< int, vector<int>, greater<int> >& min_heap); 
