// --------------------------------
// projects/pfd/TestPFD.c++
// Copyright (C) 2011
// Ryan Spring
// Jung (James) Lee
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestPFD.c++ -o TestPFD.c++.app
    % valgrind TestPFD.c++.app >& TestPFD.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

// -----------
// TestCollatz
// -----------

struct TestPFD : CppUnit::TestFixture {
    
    // -----
    // read
    // -----
    void test_pfd_read1()
    {
        std::istringstream input("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
        CPPUNIT_ASSERT(pfd_read(input) == true);
        CPPUNIT_ASSERT(task_left == 5);
        CPPUNIT_ASSERT(initial_total_task == task_left);
        CPPUNIT_ASSERT(pfd_graph[3][0] == 2); //check certain parts of the graph
        CPPUNIT_ASSERT(pfd_graph[3][2] == 5);
        CPPUNIT_ASSERT(pfd_graph[3][3] == 0);
        CPPUNIT_ASSERT(pfd_graph[5][1] == 1);
    }   
    
    void test_pfd_read2()
    {
        std::istringstream input("3 1\n1 2 3 2");
        CPPUNIT_ASSERT(pfd_read(input) == true);
        CPPUNIT_ASSERT(task_left == 3);
        CPPUNIT_ASSERT(initial_total_task == task_left);   
        CPPUNIT_ASSERT(pfd_graph[3][3] == 0);
        CPPUNIT_ASSERT(pfd_graph[1][0] == 2);
        CPPUNIT_ASSERT(pfd_graph[1][1] == 3); 
    }

    void test_pfd_read3()
    {
        std::istringstream input("100 5\n17 4 29 48 39 19\n92 2 17 83\n32 8 1 2 3 4 5 6 7 8\n9 2 33 44\n10 1 99");
        CPPUNIT_ASSERT(pfd_read(input) == true);
        CPPUNIT_ASSERT(task_left == 100);
        CPPUNIT_ASSERT(initial_total_task == task_left);
        CPPUNIT_ASSERT(pfd_graph[4][100] == 0);
        CPPUNIT_ASSERT(pfd_graph[17][0] == 4);
        CPPUNIT_ASSERT(pfd_graph[17][2] == 48);
        CPPUNIT_ASSERT(pfd_graph[100][2] == 0);
    }

    void test_pfd_read4()
    {
        std::istream input(0);
        CPPUNIT_ASSERT(pfd_read(input) == false);
    }

    // -----
    // clean
    // -----
    void graph_initializer()
    {
        for(int i = 0; i < MAX_SIZE; i++)
        {
            for(int j = 0; j < MAX_SIZE; j++)
            {
                pfd_graph[i][j] = -1;
            }
        }
    }


    void test_pfd_clean1()
    {
        graph_initializer();
        pfd_graph[72][0] = 9;
        pfd_graph[72][1] = 3;
        pfd_graph[72][9] = 7;
        pfd_clean(3);
        CPPUNIT_ASSERT(pfd_graph[72][0] == 8);
        CPPUNIT_ASSERT(pfd_graph[72][1] == 0);
        CPPUNIT_ASSERT(pfd_graph[72][10] == -1);        
    }

    void test_pfd_clean2()
    {
        graph_initializer();
        pfd_graph[21][0] = 1;
        pfd_graph[21][1] = 3;
        pfd_graph[22][0] = 0;
        pfd_graph[23][0] = 2;
        pfd_graph[23][1] = 3;
        pfd_graph[23][2] = 5;
        pfd_clean(3);
        pfd_clean(5);
        CPPUNIT_ASSERT(pfd_graph[21][0] == 0);
        CPPUNIT_ASSERT(pfd_graph[21][1] == 0);
        CPPUNIT_ASSERT(pfd_graph[22][0] == 0);
        CPPUNIT_ASSERT(pfd_graph[23][0] == 0);
        CPPUNIT_ASSERT(pfd_graph[23][1] == 0);
        CPPUNIT_ASSERT(pfd_graph[23][2] == 0);
    }
    void test_pfd_clean3()
    {
        graph_initializer();
        pfd_graph[91][0] = 0;
        pfd_graph[91][1] = 3;
        pfd_graph[92][5] = 4;
        pfd_graph[13][0] = 2;
        pfd_graph[13][99] = 1; 
        pfd_clean(1);
        CPPUNIT_ASSERT(pfd_graph[91][0] == 0);
        CPPUNIT_ASSERT(pfd_graph[92][5] == 4);
        CPPUNIT_ASSERT(pfd_graph[92][0] == -1);
        CPPUNIT_ASSERT(pfd_graph[13][99] == 1);
    }
    void test_pfd_clean4()
    {
    }




    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_pfd_read1);
    CPPUNIT_TEST(test_pfd_read2);
    CPPUNIT_TEST(test_pfd_read3);
    CPPUNIT_TEST(test_pfd_read4);
    CPPUNIT_TEST(test_pfd_clean1);
    CPPUNIT_TEST(test_pfd_clean2);
    CPPUNIT_TEST(test_pfd_clean3);
    CPPUNIT_TEST(test_pfd_clean4);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
