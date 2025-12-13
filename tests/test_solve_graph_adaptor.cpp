/// @file  test_solve_graph_adaptor.cpp
#include <solve_graph_adaptor.hpp>
#include <doctest.h>

using namespace studies_schedule;

TEST_SUITE("solve_graph_adaptor")
{

    TEST_CASE("makeSubjectGraph")
    {
        SUBCASE("Basic connections") {
            std::vector<Subject> subjects = {
                {"Math", "group1", "teacher1"},
                {"Physics", "group1", "teacher2"},
                {"Chemistry", "group2", "teacher1"},
                {"Biology", "group3", "teacher3"}
            };
            
            auto graph = makeSubjectGraph(subjects);
            
            REQUIRE(graph.size() == 4);
            
            // Math-Physics: common group
            CHECK(std::find(graph[0].begin(), graph[0].end(), 1) != graph[0].end());
            CHECK(std::find(graph[1].begin(), graph[1].end(), 0) != graph[1].end());
            
            // Math-Chemistry: common teacher
            CHECK(std::find(graph[0].begin(), graph[0].end(), 2) != graph[0].end());
            CHECK(std::find(graph[2].begin(), graph[2].end(), 0) != graph[2].end());
            
            // Physics-Chemistry: no connection
            CHECK(std::find(graph[1].begin(), graph[1].end(), 2) == graph[1].end());
            CHECK(std::find(graph[2].begin(), graph[2].end(), 1) == graph[2].end());
            
            // Biology isolated
            CHECK(graph[3].empty());
        }
        
        SUBCASE("Common instructor only") {
            std::vector<Subject> subjects = {
                {"Math", "group1", "teacher1"},
                {"Physics", "group2", "teacher1"},
                {"Chemistry", "group3", "teacher2"}
            };
            
            auto graph = makeSubjectGraph(subjects);
            
            CHECK(std::find(graph[0].begin(), graph[0].end(), 1) != graph[0].end());
            CHECK(std::find(graph[1].begin(), graph[1].end(), 0) != graph[1].end());
            CHECK(graph[2].empty());
        }
        
        SUBCASE("Empty and single") {
            std::vector<Subject> empty;
            auto graph1 = makeSubjectGraph(empty);
            CHECK(graph1.empty());
            
            std::vector<Subject> single = {{"Math", "group1", "teacher1"}};
            auto graph2 = makeSubjectGraph(single);
            REQUIRE(graph2.size() == 1);
            CHECK(graph2[0].empty());
        }
    }

    TEST_CASE("makeForbiddenColorsForSubjects")
    {
        SUBCASE("Basic merging") {
            Task task;
            
            task.set<Groups>({
                {"group1", {0, 1}},
                {"group2", {2, 3}}
            });
            
            task.set<Instructors>({
                {"teacher1", {1, 4}},
                {"teacher2", {5}}
            });
            
            task.set<Subjects>({
                {"Math", "group1", "teacher1"},
                {"Physics", "group2", "teacher2"},
                {"Chemistry", "group1", "teacher2"}
            });
            
            auto forbidden = makeForbiddenColorsForSubjects(task);
            
            REQUIRE(forbidden.size() == 3);
            
            std::sort(forbidden[0].begin(), forbidden[0].end());
            CHECK(forbidden[0] == std::vector<int>{0, 1, 4});
            
            std::sort(forbidden[1].begin(), forbidden[1].end());
            CHECK(forbidden[1] == std::vector<int>{2, 3, 5});
            
            std::sort(forbidden[2].begin(), forbidden[2].end());
            CHECK(forbidden[2] == std::vector<int>{0, 1, 5});
        }
        
        SUBCASE("Duplicate removal") {
            Task task;
            
            task.set<Groups>({{"group1", {0, 1, 2}}});
            task.set<Instructors>({{"teacher1", {1, 2, 3}}});
            task.set<Subjects>({{"Math", "group1", "teacher1"}});
            
            auto forbidden = makeForbiddenColorsForSubjects(task);
            
            REQUIRE(forbidden.size() == 1);
            REQUIRE(forbidden[0].size() == 4);
            
            std::sort(forbidden[0].begin(), forbidden[0].end());
            CHECK(forbidden[0] == std::vector<int>{0, 1, 2, 3});
        }
        
        SUBCASE("Missing references") {
            Task task;
            
            task.set<Groups>({{"group1", {0, 1}}});
            task.set<Instructors>({{"teacher1", {2, 3}}});
            
            task.set<Subjects>({
                {"Math", "nonexistent_group", "teacher1"},
                {"Physics", "group1", "nonexistent_teacher"}
            });
            
            auto forbidden = makeForbiddenColorsForSubjects(task);
            
            REQUIRE(forbidden.size() == 2);
            
            std::sort(forbidden[0].begin(), forbidden[0].end());
            CHECK(forbidden[0] == std::vector<int>{2, 3});
            
            std::sort(forbidden[1].begin(), forbidden[1].end());
            CHECK(forbidden[1] == std::vector<int>{0, 1});
        }
        
        SUBCASE("Empty forbidden lists") {
            Task task;
            
            task.set<Groups>({{"group1", {}}});
            task.set<Instructors>({{"teacher1", {}}});
            task.set<Subjects>({{"Math", "group1", "teacher1"}});
            
            auto forbidden = makeForbiddenColorsForSubjects(task);
            
            REQUIRE(forbidden.size() == 1);
            CHECK(forbidden[0].empty());
        }
    }

    TEST_CASE("makeSameColoredGraph")
    {
        // TODO
    }

    TEST_CASE("indicesOfImpossibleColors")
    {
        // TODO
    }

    TEST_CASE("updateForbiddenColorsForSubjectGraph")
    {
        // TODO
    }

    TEST_CASE("makeAssignmentsFromColorings")
    {
        // TODO
    }

}
