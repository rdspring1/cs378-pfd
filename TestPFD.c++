// --------
// includes
// --------
#include "PFD.h"

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

// -----------
// TestCollatz
// -----------

struct TestPFD : CppUnit::TestFixture {
    
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

    void test_pfd_read_basic_functionality()
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
    
    void test_pfd_read_corner_case_small_number_vertices_in_graph()
    {
        std::istringstream input("3 1\n1 2 3 2");
        CPPUNIT_ASSERT(pfd_read(input) == true);
        CPPUNIT_ASSERT(task_left == 3);
        CPPUNIT_ASSERT(initial_total_task == task_left);   
        CPPUNIT_ASSERT(pfd_graph[3][3] == 0);
        CPPUNIT_ASSERT(pfd_graph[1][0] == 2);
        CPPUNIT_ASSERT(pfd_graph[1][1] == 3); 
    }

    void test_pfd_read_corner_case_use_max_value_for_task_left()
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

    void test_pfd_read_failure_case()
    {
        std::istream input(0);
        CPPUNIT_ASSERT(pfd_read(input) == false);
    }

    void test_pfd_clean_basic_functionality()
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

    void test_pfd_clean_calling_multiple_cleans_back_to_back()
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
    void test_pfd_clean_corner_case_high_number_of_vertices_scan_all_before_clean()
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

    void test_pfd_clean_corner_case_give_clean_number_that_does_not_exist_in_graph()
    {
        graph_initializer();
        pfd_graph[22][0] = 2;
        pfd_graph[22][1] = 17;
        pfd_graph[22][2] = 22;
        pfd_clean(2);
        CPPUNIT_ASSERT(pfd_graph[22][0] == 2);
        CPPUNIT_ASSERT(pfd_graph[22][1] == 17);
        CPPUNIT_ASSERT(pfd_graph[22][2] == 22);
    }

    void test_pfd_clean_corner_case_clean_number_greater_than_max_vertices_possible()
    {
        graph_initializer();
        pfd_graph[22][0] = 2;
        pfd_graph[22][1] = 17;
        pfd_graph[22][2] = 22;
        pfd_clean(2);
        CPPUNIT_ASSERT(pfd_graph[22][0] == 2);
        CPPUNIT_ASSERT(pfd_graph[22][1] == 17);
        CPPUNIT_ASSERT(pfd_graph[22][2] == 22);
    }

    void test_pfd_remove_ignore_pass_vertices_that_have_been_cleaned()
    {
        graph_initializer();
        initial_total_task = 4;
        pfd_graph[1][0] = -2;
        pfd_graph[3][0] = 7;
        pfd_graph[4][0] = 0;
        pfd_remove();
        CPPUNIT_ASSERT(min_heap.top() == 2);
        min_heap.pop();
        CPPUNIT_ASSERT(min_heap.empty());
    }

    void test_pfd_remove_multiple_things_to_clean_but_remove_one_at_a_time()
    {
        graph_initializer();
        pfd_graph[1][0] = -1;
        pfd_graph[2][0] = -1;
        pfd_graph[3][0] = -1;
        pfd_remove();
        CPPUNIT_ASSERT(min_heap.top() == 1);
        min_heap.pop();
        CPPUNIT_ASSERT(min_heap.empty());
    }

    void test_pfd_remove_corner_case_multiple_calls_to_pfd_remove()
    {
        graph_initializer();
        pfd_graph[1][0] = -2;
        pfd_graph[2][0] = -2;
        pfd_remove();
        pfd_remove();
        CPPUNIT_ASSERT(min_heap.top() == 3);
        min_heap.pop();
        CPPUNIT_ASSERT(min_heap.top() == 4);
        min_heap.pop();
        CPPUNIT_ASSERT(min_heap.empty());
    }

    void test_pfd_solve_basic_functionality()
    {
        std::istringstream r("7 5\n1 1 3\n4 2 3 2\n5 1 2\n6 2 3 2\n7 1 3");
        std::ostringstream w;
        pfd_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "2 3 1 4 5 6 7 ");
    }

    void test_pfd_solve_corner_case_very_simple_graph_two_vertices()
    {
        std::istringstream r("2 1\n1 1 2");
        std::ostringstream w;
        pfd_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "2 1 ");
    }

    void test_pfd_solve_corner_case_one_vertex_no_rules()
    {
        std::istringstream r("1 0");
        std::ostringstream w;
        pfd_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "1 ");
    }

    void test_pfd_solve_corner_case_many_vertices_no_rules()
    {
        std::istringstream r("100 0");
        std::ostringstream w;
        pfd_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 ");
    }

    void test_pfd_solve_many_rules_test_for_complexity_test()
    {
        std::istringstream r("8 7\n1 2 7 6\n2 1 7\n3 5 7 6 5 2 4\n4 1 7\n5 1 7\n6 1 7\n8 1 7");
        std::ostringstream w;
        pfd_solve(r,w);
        CPPUNIT_ASSERT(w.str() == "7 2 4 5 6 1 3 8 ");
    }
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_pfd_read_basic_functionality);
    CPPUNIT_TEST(test_pfd_read_corner_case_small_number_vertices_in_graph);
    CPPUNIT_TEST(test_pfd_read_corner_case_use_max_value_for_task_left);
    CPPUNIT_TEST(test_pfd_read_failure_case);
    CPPUNIT_TEST(test_pfd_clean_basic_functionality);
    CPPUNIT_TEST(test_pfd_clean_calling_multiple_cleans_back_to_back);
    CPPUNIT_TEST(test_pfd_clean_corner_case_high_number_of_vertices_scan_all_before_clean);
    CPPUNIT_TEST(test_pfd_clean_corner_case_give_clean_number_that_does_not_exist_in_graph);
    CPPUNIT_TEST(test_pfd_clean_corner_case_clean_number_greater_than_max_vertices_possible);
    //CPPUNIT_TEST(test_pfd_remove_ignore_pass_vertices_that_have_been_cleaned);
    //CPPUNIT_TEST(test_pfd_remove_multiple_things_to_clean_but_remove_one_at_a_time);
    //CPPUNIT_TEST(test_pfd_remove_corner_case_multiple_calls_to_pfd_remove);
    CPPUNIT_TEST(test_pfd_solve_basic_functionality);
    CPPUNIT_TEST(test_pfd_solve_corner_case_very_simple_graph_two_vertices);
    CPPUNIT_TEST(test_pfd_solve_corner_case_one_vertex_no_rules);
    CPPUNIT_TEST(test_pfd_solve_corner_case_many_vertices_no_rules);
    CPPUNIT_TEST(test_pfd_solve_many_rules_test_for_complexity_test);
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
