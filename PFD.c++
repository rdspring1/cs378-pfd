#include "PFD.h"
#include <iostream>
#include <cassert>
#include <queue>

using namespace std;

/**
 * Generates the graph by reading from the istream
 * @param input	std::istream
 * @param pfd_graph A graph representing the partial ordering of the PFD problem 
 * @return return the number of tasks for the problem if the function succeeds, -1 otherwise
 */
int pfd_read (istream& input, int pfd_graph[][MAX_SIZE]) 
{
	int task_left = 0;

    // If the file does not contain any input, return false
    if (!input)
        return -1;

    input >> task_left;
    assert(task_left > 0);
    assert(task_left < 101);
	
    int rule_count;
    input >> rule_count;
    assert(rule_count >= 0);
    assert(rule_count < 101);

    for(int i = 0; i < rule_count; i++)
    {
        int current_vertex, dependencies;
        input >> current_vertex;
        input >> dependencies;
    	assert(current_vertex > 0);
    	assert(current_vertex < 101);
    	assert(dependencies > 0);
    	assert(dependencies < 101);

        pfd_graph[current_vertex][0] = dependencies;
        assert(dependencies < MAX_SIZE);
        for(int j = 1; j <= dependencies; j++)
        {
            input >> pfd_graph[current_vertex][j];
        }
    }
    return task_left;
}

/**
 * Removes the number added to min_heap from pfd_graph
 * @param needClean an integer that needs to be removed from the graph
 * @param initial_total_task the original number of tasks for the PFD problem
 * @param pfd_graph A graph representing the partial ordering of the PFD problem 
 */
void pfd_clean(int needClean, int initial_total_task, int pfd_graph[][MAX_SIZE])
{
    assert(needClean > 0);
    assert(needClean < 101);

    // Move through the entire graph
    for(int i = 1; i <= initial_total_task; i++)
    {
        assert(initial_total_task < MAX_SIZE);
        assert(i > 0);
        assert(i < 101);
		// Ignore the vertices that do not have any prerequisites or that have already been removed from the graph
        if((pfd_graph[i][0] == 0) || (pfd_graph[i][0] == INITIAL_VALUE) || (pfd_graph[i][0] == PASS))
        {
            continue;
        }

		// Move through all of the prerequisites for the vertex
        for(int j = 1; j < MAX_SIZE; j++)
        {
	    	// Stop moving through the array when there are no more prerequisites for the current vertex
	    	// Indicated by encountering the INITIAL_VALUE in the array
	    	// Remove the integer, needClean from the prerequisite list and deincrement the prerequisite count
            assert(j > 0);
            assert(j < 101);
            if(pfd_graph[i][j] == INITIAL_VALUE)
            {
                break;
            }
            else if(pfd_graph[i][j] == needClean)
            {
                pfd_graph[i][j] = 0;
                pfd_graph[i][0]--;
            }
        }
    }
}

/**
 * Adds the first vertex that does not have any prerequisites to min_heap
 * After finding the vertex, the function pfd_clean is run.
 * The function pfd_clean removes the vertex from the pfd_graph
 * @param task_left the number of tasks for the PFD problem
 * @param initial_total_task the original number of tasks for the PFD problem
 * @param pfd_graph A graph representing the partial ordering of the PFD problem 
 * @param min_heap A heap maintaining the list of vertices that have been removed
 */
void pfd_remove(int& task_left, int& initial_total_task, int pfd_graph[][MAX_SIZE], priority_queue< int, vector<int>, greater<int> >& min_heap)
{
    for(int i = 1; i <= initial_total_task; i++)
    {
		// Remove the first vertex that does not have any prerequisites
		// Add the vertex to min_heap
		// Deincrement task_left variable, which tracks how many vertices are left in the graph
		// Set the vertex in pfd_graph to PASS, which shows that the vertex has been removed from the graph
		// Remove the vertex from the rest of the graph
        assert(i > 0);
        assert(i < 101);
        assert(INITIAL_VALUE == -1);
        assert(PASS == -2);
        if((pfd_graph[i][0] == INITIAL_VALUE) || (pfd_graph[i][0] == 0))
        {
            min_heap.push(i);
            task_left--;
            pfd_graph[i][0] = PASS;
            pfd_clean(i, initial_total_task, pfd_graph);
    	    break;
        }
        else if(pfd_graph[i][0] == PASS) // Ignore vertices that have already been removed from the graph
        {
            continue;
        }
    }
}

/**
 * read, eval, print loop for solving the PFD sphere problem
 * @param std::istream
 * @param output a std::ostream
 * @param pfd_graph A graph representing the partial ordering of the PFD problem 
 * @param min_heap A heap maintaining the list of vertices that have been removed
 */
void pfd_solve (istream& input, ostream& output, int pfd_graph[][MAX_SIZE], priority_queue< int, vector<int>, greater<int> >& min_heap) 
{
    // Initialize pfd_graph to the INITIAL_VALUE
    for(int i = 0; i < MAX_SIZE; i++)
    {
        for(int j = 0; j < MAX_SIZE; j++)
        {
            pfd_graph[i][j] = -1;
        }
    }

    // Read from input
	int task_left = pfd_read(input, pfd_graph);
    if(task_left == -1)
    {
        output << "empty input stream";
        assert(false);
    }

	int initial_total_task = 0;
    initial_total_task = task_left;
    assert(initial_total_task < MAX_SIZE);
    
    // Run pfd_remove to initialize min_heap
    pfd_remove(task_left, initial_total_task, pfd_graph, min_heap);

    // Continue to remove elements from the graph until the graph is empty
    // The graph is empty when min_heap is empty
    while(!min_heap.empty())
    {
        assert(min_heap.empty() == false);
        int m = min_heap.top();
	
    	assert(m > 0);
    	assert(m < 101);

        min_heap.pop();
    	pfd_remove(task_left, initial_total_task, pfd_graph, min_heap);
        output << m << " ";
    }    
}
