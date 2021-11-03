#ifndef SlicedPolygon_hpp
#define SlicedPolygon_hpp

#include "Polygon.hpp"
#include "Preprocessor.hpp"
#include <limits>

class Edge
{
	public:
	
		// Constructors
		Edge();
		Edge(Rvector3 node1, Rvector3 node2);
		Edge(AnglePair node1, AnglePair node2);

		// Destructor
		~Edge();
		
		// Checks whether edge is crossed using necessary strike and hemisphere check
		int contains(Rvector3 query, Real lon);
		// Hemisphere check
		int crossesBoundary(Rvector3 query);
		// Necessary strike condition
		bool boundsPoint(Real lon);

		// Getters
		Rvector3 getPole();
		Real getBound1();
		Real getBound2();

		// Print function override
		friend std::ostream& operator<<(std::ostream& os, const Edge& edge);

	protected:
	
		Rvector3 pole;
		Real bound1;
		Real bound2;
		Real shooterDotPole;
};

class SlicedPolygon : public Polygon
{
	public:

		// Constructors
		SlicedPolygon(std::vector<Rvector3> &poly, Rvector3 contained);
		SlicedPolygon(std::vector<AnglePair> &poly, AnglePair contained);
		// Init function for constructors 
		void init(std::vector<Rvector3> &poly, Rvector3 contained);
		// Function to generate array of Edge objects used by constructor
		std::vector<Edge> generateEdgeArray();

		// Destructor
		~SlicedPolygon();
		
		// Add preprocessor to the polygon
		void addPreprocessor(Preprocessor*);
		// Returns the subset of eligible edges from the preprocessor, if present
		std::vector<int> getSubset(AnglePair query);

		// Core query method for a single query point
		int contains(AnglePair query);
		// Core query method for a vector of queries
		std::vector<int> contains(std::vector<AnglePair> queries);

		// Counts number of crossings for the arc PQ for a single query point
		int numCrossings(AnglePair query);
		// Counts number of crossings for the arc PQ for a vector of queries
		std::vector<int> numCrossings(std::vector<AnglePair> queries);
		
		// Coordinate Transformation
		Rmatrix33 generateQI();
		AnglePair toQueryFrame(AnglePair query);

		// Getters
		std::vector<Edge> getEdgeArray();
		std::vector<Real> getLonArray();
		std::vector<Real> getLatArray();
		Rmatrix33 getQI();

		// Overide print function 
		friend std::ostream& operator<<(std::ostream& os, const SlicedPolygon& poly);
		
	protected:

		bool processed;
		Rvector3 contained;
		Preprocessor* preprocessor;
		std::vector<Edge> edgeArray;
		std::vector<int> indexArray;
		std::vector<Rvector3> vertices;
		Rmatrix33 QI;
};

#endif /* SlicedPolygon_hpp */