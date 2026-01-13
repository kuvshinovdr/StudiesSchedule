#include <solve_graph_adaptor.hpp>
#include <doctest.h>

using namespace studies_schedule;

TEST_SUITE("solve_graph_adaptor")
{
    TEST_CASE("makeSameColoredGraph")
    {
        Coloring coloring = {0, 1, 0, 2, 1};

        AdjacencyList graph = makeSameColoredGraph(coloring);

        CHECK(graph.size() == 5);

        CHECK(graph[0] == std::vector<VertexIndex>{2});
        CHECK(graph[2] == std::vector<VertexIndex>{0});

        CHECK(graph[1] == std::vector<VertexIndex>{4});
        CHECK(graph[4] == std::vector<VertexIndex>{1});

        CHECK(graph[3].empty());
    }

    TEST_CASE("indicesOfImpossibleColors")
    {
        Coloring coloring = {0, 2, 3, 1, 5};

        Color maxPossibleColor = 2;

        auto indices = indicesOfImpossibleColors(coloring, maxPossibleColor);

        REQUIRE(indices.size() == 2);
        CHECK(indices[0] == 2);
        CHECK(indices[1] == 4);
    }

    TEST_CASE("updateForbiddenColorsForSubjectGraph")
    {
        ForbiddenColors forbidden = {{}, {}, {}};

        Coloring subjectTimeSlots = {1, 3, 1};

        IndicesOfImpossibleColors subjectsToMove = {0, 2};

        updateForbiddenColorsForSubjectGraph(
            forbidden,
            subjectTimeSlots,
            subjectsToMove
        );

        CHECK(forbidden[0] == std::vector<Color>{1});
        CHECK(forbidden[1].empty());
        CHECK(forbidden[2] == std::vector<Color>{1});
    }

}