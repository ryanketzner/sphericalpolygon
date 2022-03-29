#include "SlicedPolygon.hpp"
#include "SliceArray.hpp"
#include <gtest/gtest.h>
#include <iostream>

class Poly_01 : public ::testing::Test {

	protected:

	void SetUp() override 
	{
		int numElements = 13;
		std::vector<AnglePair> polygon(numElements);
		AnglePair contained = {0,0};
		
		for (int i = 0;i < numElements;i++)
			polygon[i][0] = M_PI/4.0;
		
		polygon[0][1] =	0.0;
		polygon[1][1] = 0.5235987756;
		polygon[2][1] = 1.047197551;
		polygon[3][1] = 1.570796327;
		polygon[4][1] = 2.094395102;
		polygon[5][1] = 2.617993878;
		polygon[6][1] = 3.141592654;
		polygon[7][1] = 3.665191429;
		polygon[8][1] = 4.188790205;
		polygon[9][1] = 4.71238898;
		polygon[10][1] = 5.235987756;
		polygon[11][1] = 5.759586532;
		polygon[12][1] = 0.0;
		
		grapefruit = new SlicedPolygon(polygon,contained);
		sliceTree = new SliceArray(grapefruit->getLonArray(),grapefruit->getEdgeArray());
		sliceTree->preprocess();
        grapefruit->addPreprocessor(sliceTree);
	}

  	void TearDown() override 
  	{
  		delete(grapefruit);
  	}

	Real tol = .00000001;
	SlicedPolygon* grapefruit;
	Preprocessor* sliceTree;
};

TEST_F(Poly_01,getEdges)
{
	SliceArray test = SliceArray(grapefruit->getLonArray(),grapefruit->getEdgeArray());
    std::vector<Real> lonArray = test.getLonArray();

    std::cerr << "Elements: \n";
    for (int i = 0; i < lonArray.size(); i++)
    {
        std::cerr << lonArray[i];
        std::cerr << "\n";
    }
    std::cerr << "Finished. \n";

	ASSERT_TRUE(true);
}

TEST_F(Poly_01,Query_03_numCrossings)
{
	// Test 1: Lies inside polygon
	int expectedCrossings = 0;
	AnglePair query = {.01,.01};
	
	int crossings = grapefruit->numCrossings(query);
	ASSERT_EQ(expectedCrossings,crossings);
}

TEST_F(Poly_01,Query_02_boundsPoint)
{
	// Test 2: Lies outside polygon, at same clock angle as starting point

	int expectedCrossings = 1;
	AnglePair query = {1.047197551,0};
	Rmatrix33 QI = grapefruit->getQI();

	query = util::transformSpherical(query,QI);
	Real lon = query[1];
	Real lat = query[0];

	std::vector<Edge> edgeArray = grapefruit->getEdgeArray();

	int expectedNumBounds = 1;
	int numBounds = 0;
	int i = 0;
	for (Edge edge : edgeArray)
	{
		if (edge.boundsPoint(lon,lat))
			std::cerr << i;
		numBounds += edge.boundsPoint(lon,lat);
		i++;
	}

	// Point should only be bounded by one edge
	EXPECT_EQ(expectedNumBounds,numBounds);

	// Point should be bounded by last edge
	Edge last = edgeArray.back();
	EXPECT_EQ(1,last.boundsPoint(lon,lat));
}

TEST_F(Poly_01,Query_02_numCrossings)
{
	// Test 2: Lies outside polygon, at same clock angle as starting point

	int expectedCrossings = 1;
	AnglePair query = {1.047197551,0};
	int crossings = grapefruit->numCrossings(query);
	ASSERT_EQ(expectedCrossings,crossings);
}

TEST_F(Poly_01,Query_01_numCrossings)
{
	int expectedCrossings = 0;
	AnglePair query = {0.6283185307,0};
	int crossings = grapefruit->numCrossings(query);
	ASSERT_EQ(expectedCrossings,crossings);
}

TEST_F(Poly_01,Query_05_numCrossings)
{
	// Test 5: lies inside the polygon, at clock angle in the middle of a segment
	int expectedCrossings = 0;
	AnglePair query = {0.5235987756,0.4487989505};
	int crossings = grapefruit->numCrossings(query);
	ASSERT_EQ(expectedCrossings,crossings);

	// new
	AnglePair query_Q = grapefruit->toQueryFrame(query);
	std::vector<int> subset = grapefruit->getSubset(query_Q);

	ASSERT_TRUE(subset.size() <= 3);
}

TEST_F(Poly_01,Query_06_numCrossings)
{
	// Test 6: lies inside the polygon, at clock angle in the middle of a segment
	int expectedCrossings = 0;
	AnglePair query = {0.5235987756,0.897597901};
	int crossings = grapefruit->numCrossings(query);
	ASSERT_EQ(expectedCrossings,crossings);

	// new
	AnglePair query_Q = grapefruit->toQueryFrame(query);
	std::vector<int> subset = grapefruit->getSubset(query_Q);

	ASSERT_TRUE(subset.size() <= 3);
}

TEST_F(Poly_01,Query_07_numCrossings)
{
	// Test 7: lies outside the polygon, at clock angle in the middle of a segment
	int expectedCrossings = 1;
	AnglePair query = {1.047197551,0.4487989505};
	int crossings = grapefruit->numCrossings(query);
	ASSERT_EQ(expectedCrossings,crossings);

	// new
	AnglePair query_Q = grapefruit->toQueryFrame(query);
	std::vector<int> subset = grapefruit->getSubset(query_Q);

	ASSERT_TRUE(subset.size() <= 3);
}

TEST_F(Poly_01,Query_08_numCrossings)
{
	// Test 7: lies outside the polygon, at clock angle in the middle of a segment
	int expectedCrossings = 1;
	AnglePair query = {1.047197551,0.897597901};
	//int crossings = grapefruit->numCrossings(query);
	//ASSERT_EQ(expectedCrossings,crossings);

	// new
	AnglePair query_Q = grapefruit->toQueryFrame(query);
	std::vector<int> subset = grapefruit->getSubset(query_Q);

	ASSERT_TRUE(subset.size() <= 3);
}

TEST_F(Poly_01,Query_08_boundsPoint)
{
	// Test 2: Lies outside polygon, at same clock angle as starting point

	int expectedCrossings = 1;
	AnglePair query = {1.047197551,0.897597901};
	Rmatrix33 QI = grapefruit->getQI();

	query = util::transformSpherical(query,QI);
	Real lon = query[1];
	Real lat = query[0];

	std::vector<Edge> edgeArray = grapefruit->getEdgeArray();

	int expectedNumBounds = 1;
	int numBounds = 0;
	int i = 0;
	for (Edge edge : edgeArray)
	{
		if (edge.boundsPoint(lon,lat))
			std::cerr << i;
		numBounds += edge.boundsPoint(lon,lat);
		i++;
	}

	// Point should only be bounded by one edge
	EXPECT_EQ(expectedNumBounds,numBounds);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
