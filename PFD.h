// --------------------------
// projects/pfd/PFD.h
// Copyright (C) 2011
// Ryan Spring
// Jung (James) Lee
// --------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <queue>

// CONSTANTS
#define MAX_SIZE 101

using namespace std;

// GLOBAL VARIABLES
int pfd_graph[MAX_SIZE][MAX_SIZE]; // A graph representing the partial ordering
int initial_total_task = 0;
int task_left = -1;
int initial_value = -1;
int pass = -2;
priority_queue< int, vector<int>, greater<int> > min_heap;

// ------------
// pfd_read
// ------------

/**
 * Generates the graph by reading from the istream
 * @param input a std::istream
 * @return true if that succeeds, false otherwise
 */
bool pfd_read (std::istream& input) 
{
    // If the file does not contain any input, return false
    if (!input)
        return false;

    input >> task_left;
    assert(task_left > 0);
    assert(task_left < 101);
    initial_total_task = task_left;

    int rule_count;
    input >> rule_count;
    assert(rule_count > 0);
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

        for(int j = 1; j <= dependencies; j++)
        {
            input >> pfd_graph[current_vertex][j];
        }
    }
    return true;
}

// ------------
// pfd_clean
// ------------

/**
 * Removes the number added to min_heap from pfd_graph
 * @param needClean an integer that needs to be removed from the graph
 */
void pfd_clean(int needClean)
{
    assert(needClean > 0);
    assert(needClean < 101);

    // Move through the entire graph
    for(int i = 1; i <= initial_total_task; i++)
    {
	// Ignore the vertices that do not have any prerequisites or that have already been removed from the graph
        if((pfd_graph[i][0] == 0) || (pfd_graph[i][0] == initial_value) || (pfd_graph[i][0] == pass))
        {
            continue;
        }

	// Move through all of the prerequisites for the vertex
        for(int j = 1; j < MAX_SIZE; j++)
        {
	    // Stop moving through the array when there are no more prerequisites for the current vertex
	    // Indicated by encountering the initial_value in the array
	    // Remove the integer, needClean from the prerequisite list and deincrement the prerequisite count
            if(pfd_graph[i][j] == initial_value)
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

// ------------
// pfd_remove
// ------------

/**
 * Adds the first vertex that does not have any prerequisites to min_heap
 * After finding the vertex, the function pfd_clean is run.
 * The function pfd_clean removes the vertex from the pfd_graph
 */
void pfd_remove()
{
    for(int i = 1; i <= initial_total_task; i++)
    {
	// Remove the first vertex that does not have any prerequisites
	// Add the vertex to min_heap
	// Deincrement task_left variable, which tracks how many vertices are left in the graph
	// Set the vertex in pfd_graph to pass, which shows that the vertex has been removed from the graph
	// Remove the vertex from the rest of the graph
        if((pfd_graph[i][0] == initial_value) || (pfd_graph[i][0] == 0))
        {
            min_heap.push(i);
            task_left--;
            pfd_graph[i][0] = pass;
            pfd_clean(i);
	    break;
        }
        else if(pfd_graph[i][0] == pass) // Ignore vertices that have already been removed from the graph
        {
            continue;
        }
    }
}

// -------------
// pfd_solve
// -------------

/**
 * read, eval, print loop
 * @param input a std::istream
 * @param output a std::ostream
 */
void pfd_solve (std::istream& input, std::ostream& output) 
{
    // Initialize pfd_graph to the initial_value
    for(int i = 0; i < MAX_SIZE; i++)
    {
        for(int j = 0; j < MAX_SIZE; j++)
        {
            pfd_graph[i][j] = -1;
        }
    }

    // Read from input
    if(!pfd_read(input))
    {
        output << "empty input stream";
    }

    // Run pfd_remove to initialize min_heap
    pfd_remove();

    // Continue to remove elements from the graph until the graph is empty
    // The graph is empty when min_heap is empty
    while(!min_heap.empty())
    {
        int m = min_heap.top();
	
	assert(m > 0);
    	assert(m < 101);

        min_heap.pop();
    	pfd_remove();
        cout << m << " ";
    }    
}


