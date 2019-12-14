#include "Triangle.hpp"

Triangle::Triangle(const Point& a, const Point& b, const Point& c){
    t_points.push_back(a);
    t_points.push_back(b);
    t_points.push_back(c);
}
Triangle::Triangle(const std::vector<Point>& vp):t_points(vp){}
Triangle::Triangle(const Triangle& t_):t_points(t_.t_points){}
// Drawing function
void Triangle::drawTriangle(const Point &a, const Point &b, const Point &c) const
{
	Line l1;
	Line l2;
	Line l3;
	l1.dda(a, b);
	l2.dda(b, c);
	l3.dda(a, c);
}

// using drawTriangle and the point store in the vector to draw a triangle
void Triangle::draw() const{
    // std::cout<<"Draw a Triangle"<< std::endl;
    for (int i = t_points.size() % 3 ==0 ? t_points.size() : t_points.size()-1 ; i >=3; i-=3)
    {
        drawTriangle(t_points[i-1], t_points[i-2], t_points[i-3]);
    }
    
}
double dist_to_line(const Point &a, const Point &b,const Point &c)
{
    //std::cout<<"aa: "<<a.getX()<<", "<<a.getY()<<", "<<a.getZ()<<std::endl;
    //std::cout<<"bb: "<<b.getX()<<", "<<b.getY()<<", "<<b.getZ()<<std::endl;
    //std::cout<<"cc: "<<c.getX()<<", "<<c.getY()<<", "<<c.getZ()<<std::endl;
    Vector3f ba(a.getX()-b.getX(),a.getY()-b.getY(),a.getZ()-b.getZ());
    Vector3f bc(c.getX()-b.getX(),c.getY()-b.getY(),c.getZ()-b.getZ());
    //ba=-ba;bc=-bc;
    bc.normalize();
    double len_ba2=ba.modulus()*ba.modulus();
    double len_bp=ba.dot(bc);
    double len_bp2=len_bp*len_bp;
    double len_ap2=len_ba2-len_bp2;
    if(len_ap2<=0) len_ap2=0;
    // if(!(len_ap2>=0))
    //     printf("%f %f %f \n",ba.modulus(),len_bp,len_bp2);
    //     printf("%f %f %f \n",len_ap2,len_ba2,len_bp2);
    assert(len_ap2>=0);
    return sqrt(len_ap2);

}
double Triangle::smallest_distance(const Point& p_){
    Point a = t_points[0];
    //std::cout<<"p_: "<<p_.getX()<<", "<<p_.getY()<<", "<<p_.getZ()<<std::endl;
    Point b = t_points[1];
    // std::cout<<"c: "<<b.getX()<<", "<<b.getY()<<", "<<b.getZ()<<std::endl;
    Point c = t_points[2];
    // std::cout<<"c: "<<c.getX()<<", "<<c.getY()<<", "<<c.getZ()<<std::endl;
    Vector3f ac(c.getX()-a.getX(),c.getY()-a.getY(),c.getZ()-a.getZ());
    ac.normalize();
    Vector3f ap(p_.getX()-a.getX(), p_.getY()-a.getY(), p_.getZ()-a.getZ());
    Vector3f project_ac = ap * ac;
    double distance_pa = sqrt(pow(ap.modulus(),2) - pow(project_ac.modulus(),2));
    double min_d=1e100;
    double d;
    d=dist_to_line(p_,a,b);
    if(d<min_d) min_d=d;   
    d=dist_to_line(p_,a,c);
    if(d<min_d) min_d=d;   
    d=dist_to_line(p_,c,b);
    if(d<min_d) min_d=d;

    return min_d;
}

Vector3f Triangle::getNorm(){
    // Matrix m_;
    Vector3f temp_a(
        //vector ab
        t_points[1].getX()-t_points[0].getX(),
        t_points[1].getY()-t_points[0].getY(),
        t_points[1].getZ()-t_points[0].getZ()
    );
    Vector3f temp_b(
        //vector ac
        t_points[2].getX()-t_points[0].getX(),
        t_points[2].getY()-t_points[0].getY(),
        t_points[2].getZ()-t_points[0].getZ()
    );
    // temp_a.cross_product(temp_b);
    // Vector3f norm = m_.cross_product(temp_a, temp_b);
    return Vector3f(temp_a.cross_product(temp_b));
}
Vector3f Triangle::getNormB(){
    // Matrix m_;
    Vector3f temp_a(
        // vector bc
        t_points[2].getX()-t_points[1].getX(),
        t_points[2].getY()-t_points[1].getY(),
        t_points[2].getZ()-t_points[1].getZ()
    );
    Vector3f temp_b(
        // vectir ba
        t_points[0].getX()-t_points[1].getX(),
        t_points[0].getY()-t_points[1].getY(),
        t_points[0].getZ()-t_points[1].getZ()
    );

    return Vector3f(temp_a.cross_product(temp_b));
}
Vector3f Triangle::getNormC(){
    // Matrix m_;
    // Vector ca
    Vector3f temp_a(
        t_points[0].getX()-t_points[2].getX(),
        t_points[0].getY()-t_points[2].getY(),
        t_points[0].getZ()-t_points[2].getZ()
    );
    //vector cb
    Vector3f temp_b(
        t_points[1].getX()-t_points[2].getX(),
        t_points[1].getY()-t_points[2].getY(),
        t_points[1].getZ()-t_points[2].getZ()
    );
    // temp_a.cross_product(temp_b);
    // Vector3f norm = m_.cross_product(temp_a, temp_b);
    return Vector3f(temp_a.cross_product(temp_b));
}

const std::vector<Vector3f> Triangle::getNormList(){
    norm_list.push_back(getNorm());
    norm_list.push_back(getNormB());
    norm_list.push_back(getNormC());
    return norm_list;
}
