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

#define MAX_SIZE 6
using namespace std;
// graph representing the partial ordering
int pfd_graph[MAX_SIZE][MAX_SIZE];
int initial_total_task = 0;
int task_left = -1;
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
    for(int i = 0; i < rule_count; i++)
    {
        int current_vertex, dependencies;
        input >> current_vertex;
        input >> dependencies;
        pfd_graph[current_vertex][0] = dependencies;
        for(int j = 1; j <= dependencies; j++)
        {
            input >> pfd_graph[current_vertex][j];
        }
    }
    return true;
}

void print_graph()
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

void pfd_clean(int needClean[])
{
    for(int i = 1; i <= initial_total_task; i++)
    {
        if((pfd_graph[i][0] == 0) || (pfd_graph[i][0] == initial_value) || (pfd_graph[i][0] == pass))
        {
            continue;
        }
        for(int j = 1; j < MAX_SIZE; j++)
        {
//            cout << "THIS IS I: " << i << "\n";
 //           cout << pfd_graph[i][j] << "t\n";
            if(pfd_graph[i][j] == initial_value)
            {
                break;
            }
            else if(needClean[pfd_graph[i][j]] == 1 )
            {
   //             cout << pfd_graph[i][j] <<"\n";
                pfd_graph[i][j] = 0;
                pfd_graph[i][0]--;
            }
        }
    }
}


void pfd_remove()
{
    int needClean[MAX_SIZE] = {0};
    for(int i = 1; i <= initial_total_task; i++)
    {
   //     cout << pfd_graph[i][0] << "\n";
        if((pfd_graph[i][0] == initial_value) || (pfd_graph[i][0] == 0))
        {
            cout << i << " ";
            task_left--;
 //           cout << "taskleft: " <<task_left<<"\n";
            pfd_graph[i][0] = pass;
            needClean[i] = 1;
        }
        else if(pfd_graph[i][0] == pass)
        {
            continue;
        }
    }    
    pfd_clean(needClean);

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
    if(!pfd_read(input))
    {
        output << "empty input stream";
    }
//    print_graph();
   while(task_left > 0)
    {
        pfd_remove();
    }
         
}


