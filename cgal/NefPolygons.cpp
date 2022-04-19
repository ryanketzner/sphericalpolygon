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

        // std::cout << "Vertex: " << i << std::endl; 
        // std::cout << x  << std::endl;
        // std::cout << y << std::endl;
        // std::cout << z << std::endl;

        spherepoints.push_back(Sphere_point(pointy.x(),pointy.y(),pointy.z()));
    }
    return spherepoints;
}

std::vector<Sphere_segment> SpherePointToSphereSegment(const std::vector<Sphere_point> &points)
{
    std::vector<Sphere_segment> spheresegments;

    // Last point is contained point, not needed in cgal
    for (int i = 0; i < (points.size()-2); i++)
    {
        spheresegments.push_back(Sphere_segment(points[i],points[i+1]));
    }
    
    std::cout << "Number of points: " << points.size() << std::endl;
    return spheresegments;
}

int main(int argc,char **argv)
{
    std::string inputpoly = argv[1];
    std::vector<AnglePair> vertices = util::csvRead(inputpoly);
    std::vector<Rvector3> verticesxyz =  util::sphericalToCartesian(vertices);
    std::vector<Sphere_point> spherepoints = RvectorToSpherePoint(verticesxyz);
    std::vector<Sphere_segment> edges = SpherePointToSphereSegment(spherepoints);
    
    Nef_polyhedron_S2 TN(edges.begin(),edges.end());

    // These operations cause crash
    // Nef_polyhedron_S2 TN_int = TN.closure();
    // Nef_polyhedron_S2 TN_reg = TN.regularization();

    Sphere_point centroid = spherepoints.back();
    Sphere_point centroid_anti = centroid.antipode();
    Object_handle location = TN.locate(centroid);
    Object_handle location_anti = TN.locate(centroid_anti);
    bool inside = TN.contains(location);
    bool outside = TN.contains(location_anti);

    std::cout << "Centroid Contained: " << inside << std::endl;
    std::cout << "Centroid Antipode Contained: " << outside << std::endl;
    std::cout << "Centroid Value: " << centroid << std::endl;
    std::cout << "Centroid Antipode Value: " << centroid_anti << std::endl;

    std::cout << "Number of faces:" << std::endl;
    std::cout << TN.number_of_sfaces() << std::endl;

    std::cout << "Number of vertices:" << std::endl;
    std:: cout << TN.number_of_svertices() << std::endl;

    SVertex_const_handle sv;
    SHalfedge_const_handle se;
    SHalfloop_const_handle sl;
    SFace_const_handle sf;

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

    TN.print_statistics(std::cout);

    // std::cout << TN.number_of_connected_components() << std::endl;
    // std::cout << TN.number_of_sedges() << std::endl;

    return 0;
}