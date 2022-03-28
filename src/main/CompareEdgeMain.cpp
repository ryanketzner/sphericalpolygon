#include "PointInPolygon.hpp" 

inline int AstroPyIntersect(const Rvector3& AxB, const Rvector3& A, const Rvector3& B, const Rvector3& C, const Rvector3& D)
{
    Rvector3 CxD = Cross(C,D);
    Rvector3 T = Cross(AxB,CxD);

    double s_1 = Cross(AxB,A) * T;
    double s_2 = Cross(B,AxB) * T;
    double s_3 = Cross(CxD,C) * T;
    double s_4 = Cross(D,CxD) * T;

    bool s_1_positive = s_1 > 0;
    bool s_2_positive = s_2 > 0;
    bool s_3_positive = s_3 > 0;
    bool s_4_positive = s_4 > 0;

    bool allpositive =  s_1_positive*s_2_positive*s_3_positive*s_4_positive;

    bool allnegative = !s_1_positive * !s_2_positive * !s_3_positive * !s_4_positive;

    return (allpositive || allnegative);
}

inline int BevisIntersect(double theta_v_prime, const AnglePair& v1, const AnglePair& q, bool p_east)
{
    double theta_q = q[1];
    double phi_q = q[0];

    double theta_v1 = v1[1];
    double phi_v1 = v1[0];

    double lat_diff = phi_q - phi_v1;
    double num = sin(lat_diff)*cos(theta_q);
    double denom = sin(theta_q)*cos(theta_v1) - cos(theta_q)*sin(theta_v1)*cos(lat_diff);
    double theta_q_prime = atan2(num,denom);

    if (theta_q_prime == theta_v_prime)
        return -1;

    bool east;
    // Doesn't cross singularity
    if (abs(theta_q_prime - theta_v_prime) < M_PI)
        east = (theta_q_prime > theta_v_prime);
    else
        east = (theta_q_prime < theta_v_prime);

    return (p_east == east);
}

inline int DSPIPIntersect(const Rvector3& q, double pdotq, const Rvector3& pole)
{
	double queryDotPole = q*pole;
	
	// Directly on an edge
	if ( queryDotPole == 0.0)
 		return -1;
	// On opposite side of edge as shooter
 	else if (queryDotPole*pdotq < 0)
 		return 1;
	// On same side of edge as shooter
 	else
 		return 0;
}

int main(int argc, char **argv)
{
    int numTests = 10000000;

    AnglePair p = {0,0};

    double q_lat = M_PI/3;
    double q_lon = M_PI/3;


    AnglePair q = {q_lat,q_lon};
    Rvector3 p_cart = util::sphericalToCartesian(p);
    Rvector3 q_cart = util::sphericalToCartesian(q);

    AnglePair v1 = {M_PI/4,M_PI/16};
    AnglePair v2 = {M_PI/4,M_PI/8};
    Rvector3 v1_cart = util::sphericalToCartesian(v1);
    Rvector3 v2_cart = util::sphericalToCartesian(v2);

    Rvector3 pole = Cross(v1_cart,v2_cart);
    double pdotq = pole*q_cart;

    int retval;

    // Bevis Timing
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTests; i++)
    {
        retval = BevisIntersect(v1[1],v1,q,1);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Bevis Edge Crossing Time: " << duration.count()/(float)numTests << "\n" << std::endl;

    // DSPIP Timing
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTests; i++)
    {
        retval = DSPIPIntersect(p_cart,pdotq,pole);
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "DSPIP Edge Crossing Time: " << duration.count()/(float)numTests << "\n" << std::endl;

    // Astropy Timing
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTests; i++)
    {
        retval = AstroPyIntersect(pole,v1_cart,v2_cart,p_cart,q_cart);
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Astropy Edge Crossing Time: " << duration.count()/(float)numTests << "\n" << std::endl;
    
    // Arithmetic Timing: Bevis
    double phi_q = M_PI/4;
    double phi_v1 = M_PI/4;
    double theta_q = M_PI/4;
    double theta_v1 = M_PI/4;
    double lat_diff = phi_q - phi_v1;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTests; i++)
    {
        double num = sin(lat_diff)*cos(theta_q);
        double denom = sin(theta_q)*cos(theta_v1) - cos(theta_q)*sin(theta_v1)*cos(lat_diff);
        double theta_q_prime = atan2(num,denom);
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Bevis Arithmetic Time: " << duration.count()/(float)numTests << "\n" << std::endl;

    // Arithmetic Timing: DSPIP
    double p1 = p_cart[0];
    double p2 = p_cart[1];
    double p3 = p_cart[2];
    double q1 = q_cart[0];
    double q2 = q_cart[1];
    double q3 = q_cart[2];

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTests; i++)
    {
        double result = p1*q1 + p2*q2 + p3*q3;
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "DSPIP Arithmetic Time: " << duration.count()/(float)numTests << "\n" << std::endl;


    return 0;
}