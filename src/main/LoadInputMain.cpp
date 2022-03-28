#include "PointInPolygon.hpp"

int main(int argc, char **argv)
{
    std::string inputPoly = argv[1];

    std::vector<AnglePair> vertices = util::csvRead(inputPoly);
    AnglePair contained = vertices.back();
    vertices.pop_back();
    
    SlicedPolygon* poly = new SlicedPolygon(vertices,contained);

    delete(poly);

    return 0;
}