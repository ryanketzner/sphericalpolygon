#include "../src/Polygon.hpp"
#include <CGAL/Exact_rational.h>
#include <CGAL/Exact_integer.h>
#include <CGAL/double.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/Nef_polyhedron_S2.h>

typedef CGAL::Exact_rational FT;
typedef CGAL::Cartesian<FT> Kernel;
typedef CGAL::Point_3<Kernel> Point_3;
typedef CGAL::Nef_polyhedron_S2<Kernel> Nef_polyhedron_S2;
typedef Nef_polyhedron_S2::SVertex_const_handle SVertex_const_handle;
typedef Nef_polyhedron_S2::SHalfedge_const_handle SHalfedge_const_handle;
typedef Nef_polyhedron_S2::SHalfloop_const_handle SHalfloop_const_handle;
typedef Nef_polyhedron_S2::SFace_const_handle SFace_const_handle;
typedef Nef_polyhedron_S2::Object_handle Object_handle;
typedef Nef_polyhedron_S2::Sphere_point Sphere_point;
typedef Nef_polyhedron_S2::Sphere_segment Sphere_segment;

std::vector<Sphere_point> RvectorToSpherePoint(const std::vector<Rvector3> &rvectors)
{
    std::vector<Sphere_point> spherepoints;
    for (int i = 0; i < rvectors.size(); i++)
    {
        double x = rvectors[i].Get(0);
        double y = rvectors[i].Get(1);
        double z = rvectors[i].Get(2);
        Point_3 pointy(x,y,z);

        spherepoints.push_back(Sphere_point(pointy.x(),pointy.y(),pointy.z()));
    }
    return spherepoints;
}

std::vector<Sphere_segment> SpherePointToSphereSegment(const std::vector<Sphere_point> &points)
{
    std::vector<Sphere_segment> spheresegments;

    // The last point in the input is "contained point", which is not needed in cgal.
    // The second to last point in the input is the first point repeated.
    // Neither of these points are needed by CGAL, hence the iteration
    // continues only up to points.size() - 2.
    for (int i = 0; i < (points.size()-2); i++)
    {
        spheresegments.push_back(Sphere_segment(points[i],points[i+1]));
    }
    
    std::cout << "Number of points in input list: " << points.size() << std::endl;
    return spheresegments;
}

int main(int argc,char **argv)
{
    // The path to a polygon .csv file is specified as input to the program.
    std::string inputpoly = argv[1];
    std::vector<AnglePair> vertices = util::csvRead(inputpoly);
    std::vector<Rvector3> verticesxyz =  util::sphericalToCartesian(vertices);
    std::vector<Sphere_point> spherepoints = RvectorToSpherePoint(verticesxyz);
    std::vector<Sphere_segment> edges = SpherePointToSphereSegment(spherepoints);
    
    Nef_polyhedron_S2 input_poly(edges.begin(),edges.end());

    // These operations cause the porgram to crash.
    // We were unable to determine the reason for this in the CGAL documentation.
    // Nef_polyhedron_S2 input_poly_int = input_poly.closure();
    // Nef_polyhedron_S2 input_poly_reg = input_poly.regularization();

    // Get the centroid 
    Sphere_point centroid = spherepoints.back();
    // Get the antipode of the centroid
    Sphere_point centroid_anti = centroid.antipode();

    // Run the CGAL point location algorithm on the centroid and antipode
    Object_handle location = input_poly.locate(centroid);
    Object_handle location_anti = input_poly.locate(centroid_anti);

    // Determine whether these points are contained in the polygon
    bool inside = input_poly.contains(location);
    bool outside = input_poly.contains(location_anti);

    std::cout << "Centroid Contained: " << inside << std::endl;
    std::cout << "Centroid Antipode Contained: " << outside << std::endl;
    std::cout << "Centroid Value: " << centroid << std::endl;
    std::cout << "Centroid Antipode Value: " << centroid_anti << std::endl;

    // Print the number of faces in the resulting sphere map
    std::cout << "Number of faces:" << std::endl;
    std::cout << input_poly.number_of_sfaces() << std::endl;

    // Print the number of vertices in the input polygon
    std::cout << "Number of vertices:" << std::endl;
    std:: cout << input_poly.number_of_svertices() << std::endl;

    SVertex_const_handle sv;
    SHalfedge_const_handle se;
    SHalfloop_const_handle sl;
    SFace_const_handle sf;

    // Will print the results of the CGAL point location algorithm run on
    // the centroid of the input polygon. The output should tell the user 
    // which type of component of the resulting sphere mape contains the point.
    if(CGAL::assign(sv,location))
        std::cout << "Locating svertex" << std::endl;
    else if(CGAL::assign(se,location))
        std::cout << "Locating shalfedge" << std::endl;
    else if(CGAL::assign(sl,location))
        std::cout << "Locating shalfloop" << std::endl;
    else if(CGAL::assign(sf,location))
        std::cout << "Locating sface" << std::endl;
    else {
        std::cout << "something wrong" << std::endl;
        return 1;
    }

    input_poly.print_statistics(std::cout);

    return 0;
}