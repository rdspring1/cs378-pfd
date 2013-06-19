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
#define MAX_SIZE 6
using namespace std;
// graph representing the partial ordering
int pfd_graph[MAX_SIZE][MAX_SIZE];
int initial_total_task;
int task_left;
//priority_queue<int, vector<int>, greater<int>> min_heap;
// ------------
// pfd_read
// ------------

int initial_value = -1;
int pass = -2;

/**
 * reads two ints into range1 and range2
 * @param input a  std::istream
 * @param range1 an int by reference
 * @param range2 an int by reference
 * @return true if that succeeds, false otherwise
 */
bool pfd_read (std::istream& input) 
{
    if (!input)
        return false;
    int rule_count;
    input >> task_left;
    initial_total_task = task_left;
    input >> rule_count;
    cout<<"a\n";
    for(int i = 0; i < rule_count; i++)
    {
        cout<<"i: "<< i << "\n";
        int current_vertex, dependencies;
        input >> current_vertex;
        input >> dependencies;
        cout<<"dep " << dependencies;
        pfd_graph[current_vertex][0] = dependencies;
        for(int j = 1; j <= dependencies; j++)
        {
            cout << "comes Here";
            cout << "cv: " << current_vertex;
            
            input >> pfd_graph[current_vertex][j];
            cout<<"j: " << j;
        }
    }
    cout<<"true";
    return true;
}

void print_crazy()
{
    for(int i = 0; i < MAX_SIZE; i++)
    {
        for(int j = 0; j < MAX_SIZE; j++)
        {
            cout << pfd_graph[i][j] << " ";
        }
        cout << "\n";
    }
}

// -------------
// collatz_print
// -------------

/**
 * prints the values of range1, range2, and cycle_count
 * @param output a std::ostream
 * @param range1 the beginning of the range, inclusive
 * @param range2 the end       of the range, inclusive
 * @param cycle_count the max cycle length
 */
void pfd_print (std::ostream& output, int range1, int range2, int cycle_count) {
    assert(range1 > 0);
    assert(range2 > 0);
    assert(range1 < 1000000);
    assert(range2 < 1000000);
    assert(cycle_count > 0);
    output << range1 << " " << range2 << " " << cycle_count << std::endl;}

void pfd_clean(int removed_vertex)
{
    for(int i = 1; i < initial_total_task; i++)
    {
        if(pfd_graph[i][0] == 0 || pfd_graph[i][0] == initial_value || pfd_graph[i][0] == pass)
        {
            continue;
        }
        for(int j = 1; j < MAX_SIZE; j++)
        {
            if(pfd_graph[i][j] == initial_value)
            {
                break;
            }
            else if(pfd_graph[i][j] == removed_vertex)
            {
                pfd_graph[i][j] = 0;
                pfd_graph[i][0]--;
                break;
            }
        }
    }
}


void pfd_remove()
{
    for(int i = 1; i <= initial_total_task; i++)
    {
//        cout << i;
        if((pfd_graph[i][0] == initial_value) || (pfd_graph[i][0] == 0))
        {
            cout << i;
            cout << i << " ";
            task_left--;
            pfd_graph[i][0] = pass;
            pfd_clean(i);
        }
    }    
}

// -------------
// collatz_solve
// -------------

/**
 * read, eval, print loop
 * @param input a std::istream
 * @param output a std::ostream
 */
void pfd_solve (std::istream& input, std::ostream& output) 
{
    for(int i = 0; i < MAX_SIZE; i++)
    {
        for(int j = 0; j < MAX_SIZE; j++)
        {
            pfd_graph[i][j] = -1;
        }
    }
cout << "1\n";        
    if(!pfd_read(input))
    {
        output << "empty input stream";
    }
    cout<<"2\n";
 print_crazy(); 
 cout <<"3\n";  
    while(task_left > 0)
    {
 //       cout << task_left;
        pfd_remove();
    }

//    const int cycle_count = collatz_eval(range1, range2);
//    assert(cycle_count > 0);
//    pfd_print(output, range1, range2, cycle_count);
}


