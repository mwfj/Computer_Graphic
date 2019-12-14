/**
 * @author Wufangjie Ma
 * 
 **/
#include "Ray_tracer.hpp"
#include "parameter.hpp"
#include "Illumination.hpp"
#include <iostream>
#include <math.h>
#include <limits>
Ray_tracer::~Ray_tracer() {}
Ray_tracer::Ray_tracer(const std::vector<Triangle> &t_)
    : triangle_list(t_) {}
Ray_tracer::Ray_tracer(const Ray_tracer &rt_) : triangle_list(rt_.triangle_list) {}

//Normalize the direction vector
Vector3f Ray_tracer::normalize(double x_, double y_, double z_)
{
    double nx = x_ / sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));
    double ny = y_ / sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));
    double nz = z_ / sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));
    return Vector3f(nx, ny, nz);
}
Vector3f Ray_tracer::normalize(const Vector3f &other)
{
    double nx = other.getX() / sqrt((other.getX() * other.getX()) + (other.getY() * other.getY()) + (other.getZ() * other.getZ()));
    double ny = other.getY() / sqrt((other.getX() * other.getX()) + (other.getY() * other.getY()) + (other.getZ() * other.getZ()));
    double nz = other.getZ() / sqrt((other.getX() * other.getX()) + (other.getY() * other.getY()) + (other.getZ() * other.getZ()));
    return Vector3f(nx, ny, nz);
}
Vector3f Ray_tracer::calBarycentry(const Ray &eye_ray, const Triangle &tri_)
{

    double t = 0.0, gamma = 0.0, beta = 0.0;
    std::vector<Point> temp_t_point;
    temp_t_point = tri_.getPointList(); //vertexs in one triangle
    Point eb = temp_t_point[1] - temp_t_point[0];
    Point ec = temp_t_point[2] - temp_t_point[0];
    // std::cout<<"ec: "<<"x: "<<ec.getX()<<", "<<"y: "<<ec.getY()<<", "<<"z: "<<ec.getZ()<<std::endl;
    /** T
     * { -EBX, -ECX, (ax - ROX)
     *   -EBY, -ECY, (ay - ROY)
     *   -EBZ, -ECZ, (az - ROZ) }
     * **/
    double T[3][3] = {
        {-eb.getX(), -ec.getX(), (temp_t_point[0].getX() - eye_ray.getOri().getX())},
        {-eb.getY(), -ec.getY(), (temp_t_point[0].getY() - eye_ray.getOri().getY())},
        {-eb.getZ(), -ec.getZ(), (temp_t_point[0].getZ() - eye_ray.getOri().getZ())}};

    /** A
     * { -EBX, -ECX, RdX
     *   -EBY, -ECY, Rdy
     *   -EBZ, -ECZ, Rdz }
     * **/
    double A[3][3] = {
        {-eb.getX(), -ec.getX(), eye_ray.getDir().getX()},
        {-eb.getY(), -ec.getY(), eye_ray.getDir().getY()},
        {-eb.getZ(), -ec.getZ(), eye_ray.getDir().getZ()}};

    /** B
     * { (ax-ROX), -ECX, RdX
     *   (ay-ROY), -ECY, Rdy
     *   (az-ROZ), -ECZ, RdZ }
     * **/
    double B[3][3] = {
        {(temp_t_point[0].getX() - eye_ray.getOri().getX()), -ec.getX(), eye_ray.getDir().getX()},
        {(temp_t_point[0].getY() - eye_ray.getOri().getY()), -ec.getY(), eye_ray.getDir().getY()},
        {(temp_t_point[0].getZ() - eye_ray.getOri().getZ()), -ec.getZ(), eye_ray.getDir().getZ()}};

    /** C
     * { -EBX, (ax-ROX), RdX
     *   -EBY, (ay-ROY), Rdy
     *   -EBZ, (az-ROZ), RdZ }
     * **/
    double C[3][3] = {
        {-eb.getX(), (temp_t_point[0].getX() - eye_ray.getOri().getX()), eye_ray.getDir().getX()},
        {-eb.getY(), (temp_t_point[0].getY() - eye_ray.getOri().getY()), eye_ray.getDir().getY()},
        {-eb.getZ(), (temp_t_point[0].getZ() - eye_ray.getOri().getZ()), eye_ray.getDir().getZ()}};

    Matrix m_;
    double det_a = m_.determinant(A);
    if (det_a == 0)
    {
        return Vector3f(-1, 0, 0);
    }
    double det_b = m_.determinant(B);
    double det_c = m_.determinant(C);
    double det_t = m_.determinant(T);
    // std::cout<<"det_a: "<< det_a<<" det_b: "<< det_b<<" det_c: "<< det_c<<" det_t: "<< det_t<<std::endl;
    t = det_t / det_a;
    beta = det_b / det_a;
    gamma = det_c / det_a;
    // std::cout<<"t:"<<t<<", "<<"beta:"<<beta<<", "<<"gamma:"<<gamma<<std::endl;
    if (t <= 0)
    {
        return Vector3f(-1, -1, -1);
    }
    if (beta <= 0 || beta > 1)
    {
        return Vector3f(-1, -1, -1);
    }

    if (gamma <= 0 || gamma > 1)
    {
        return Vector3f(-1, -1, -1);
    }
    if (beta + gamma > 1)
    {
        return Vector3f(-1, -1, -1);
    }
    return Vector3f(t, beta, gamma);
    // return t;
}

void Ray_tracer::findIntersection(bool isBumping)
{
    double inf = std::numeric_limits<double>::infinity();
    std::vector<Point> tri_ave; // recording the midpoint of each triangle
    std::vector<double> tri_min_dis; // recording the smallest ditance from all the triangle's edge to intersection point
    // std::vector<std::vector<Vector3f> > norm_list;// record the norms from all the vetexes
    if (isBumping)
    {
        for (int i = 0; i < triangle_list.size(); i++)
        {
            tri_ave.push_back(triangle_list[i].getAve());
            tri_min_dis.push_back(triangle_list[i].smallest_distance(tri_ave[i]));
            // norm_list.push_back(triangle_list[i].getNormList());
        }
    
    }
    
    double beta = 0.0;
    double gamma = 0.0;
    double alpha = 5;
    // std::cout<<triangle_list.size()<<std::endl;
    // std::cout<<LEFT<<","<<RIGHT<<","<<UP<<","<<BOTTOM<<std::endl;
    for (int i = LEFT; i < RIGHT; i++)
    {
        for (int j = BOTTOM; j < UP; j++)
        {

            double temp_t_value = inf; //recording every t value from eye ray
            double temp_light_t = inf; //recording the t value from object to the light source
            double temp_beta = 0.0;
            double temp_gamma = 0.0;

            double t = inf; // recording the miniest t
            // std::vector<double> t_list;

            Ray eye_ray;   // the ray from viewer to object
            Ray light_ray; // the ray refects from the object to light source
            //Normalize Rd
            //Pespective eyeray parameter
            // Vector3f norRd = normalize( (i-temp_ray.getOri().getX()), (j-temp_ray.getOri().getY()), (-WIDTH/2 - temp_ray.getOri().getZ()) );
            // std::cout<<"i: "<<i<<"rox: "<<i-temp_ray.getOri().getX()<<std::endl;
            // std::cout<<"j: "<<j<<"roy: "<<j-temp_ray.getOri().getY()<<std::endl;
            // std::cout<<"roz: "<< (WIDTH/2)- temp_ray.getOri().getZ()<<std::endl;
            // temp_ray.setDir(
            //         norRd.getX(),
            //         norRd.getY(),
            //         norRd.getZ()
            // );
            //Orthogonal eyeray parameter
            eye_ray.setDir(
                0.0,
                0.0,
                -1.0);
            eye_ray.setOri(
                i,
                j,
                500);

            int smallest_index = 0;

            // std::vector<Vector3f> tri_norm_list; // Recording each triangle's norm
            for (int k = 0; k < triangle_list.size(); k++)
            {
                Vector3f temp_barycentry(calBarycentry(eye_ray, triangle_list[k]));
                temp_t_value = temp_barycentry.getX();
                temp_beta = temp_barycentry.getY();
                temp_gamma = temp_barycentry.getZ();

                if (temp_t_value <= 0)
                {
                    continue;
                }
                // std::cout<<"every t from eye:"<<temp_t_value<<std::endl;
                 
                if (temp_t_value > 0 && temp_t_value != inf)
                {

                    // std::cout<<"t: "<<temp_t_value<<std::endl;
                    // t_list.push_back(temp_t_value);
                    if (temp_t_value < t)
                    {
                        t = temp_t_value;
                        smallest_index = k;
                        gamma = temp_gamma;
                        beta = temp_beta;
                    }
                }
                else
                {
                    continue;
                }
            }

            if (t != inf)
            {
                Illumination temp_i(i, j);
                Vector3f intersect = eye_ray.getOri() + (eye_ray.getDir() * t);
                // std::cout<<"eye ori: "<<eye_ray.getOri().getX()<<", "<<eye_ray.getOri().getY()<<","<<eye_ray.getOri().getZ()<<std::endl;
                // std::cout<<"eye dir: "<<eye_ray.getDir().getX()<<", "<<eye_ray.getDir().getY()<<","<<eye_ray.getDir().getZ()<<std::endl;

                // std::cout<<"t: "<<t<<std::endl;
                Vector3f light_dest(RIGHT / 2, UP*0.75, 600.0); // the point of light source
                light_ray.setOri(intersect.getX(), intersect.getY(), intersect.getZ());
                //Light source - intersection point and normalize it
                light_ray.setDir(
                    normalize(
                        light_dest.getX() - intersect.getX(),
                        light_dest.getY() - intersect.getY(),
                        light_dest.getZ() - intersect.getZ()));
                //vector v
                Vector3f v = normalize(eye_ray.getOri() - intersect);

                //vector l
                Vector3f l = normalize(light_dest - light_ray.getOri());

                // vector n
                Vector3f tri_norm = triangle_list[smallest_index].getNorm();
                
                if (tri_norm.dot(eye_ray.getDir()) > 0)
                {
                    //Norm direction change:
                    // std::cout<<"before: "<<" x: "<<tri_norm.getX()<<" y: "<<tri_norm.getY()<<" z: "<<tri_norm.getZ()<<std::endl;
                    tri_norm.reverse_norm();
                    // std::cout<<"after: "<<" x: "<<tri_norm.getX()<<" y: "<<tri_norm.getY()<<" z: "<<tri_norm.getZ()<<std::endl;
                }
                
                // normalize n
                Vector3f n = normalize(tri_norm);
                // Vector3f n(0,0,0);
                // std::cout<<"n:"<<" x: "<<n.getX()<<", y:"<<n.getY()<<", z:"<<n.getZ()<<std::endl;
                //-------------------------------------------------------------------------------
                // Phong smoothing begin
                // Vector3f smoothing_norm(0.0f,0.0f,0.0f);
                // Recording the each vertex norm of visible face
                // Vector3f tri_na(norm_list[smallest_index][0]);
                // Vector3f tri_nb(norm_list[smallest_index][1]);
                // Vector3f tri_nc(norm_list[smallest_index][2]);
                // Vector3f tri_na(triangle_list[smallest_index].getNorm());
                // Vector3f tri_nb(triangle_list[smallest_index].getNormB());
                // Vector3f tri_nc(triangle_list[smallest_index].getNormC());
                // Vector3f temp_na = normalize(tri_na);
                // Vector3f temp_nb = normalize(tri_nb);
                // Vector3f temp_nc =  normalize(tri_nc);
                // std::cout<<"temp_na:"<<" x: "<<temp_na.getX()<<", y:"<<temp_na.getY()<<", z:"<<temp_na.getZ()<<std::endl;
                // std::cout<<"temp_nb:"<<" x: "<<temp_nb.getX()<<", y:"<<temp_nb.getY()<<", z:"<<temp_nb.getZ()<<std::endl;
                // std::cout<<"temp_nc:"<<" x: "<<temp_nc.getX()<<", y:"<<temp_nc.getY()<<", z:"<<temp_nc.getZ()<<std::endl;
                // if (temp_na.dot(n)<0)
                // {
                //     temp_na.reverse_norm();
                // }
                // if (temp_nb.dot(n)<0)
                // {
                //     temp_nb.reverse_norm();
                // }
                // if (temp_nc.dot(n)<0)
                // {
                //     temp_nc.reverse_norm();
                // }
                // double wa = 1.0-beta-gamma;
                // std::cout<<"beta: "<<beta<<", "<<"gamma:"<<gamma<<std::endl;
                // smoothing_norm = tri_na;
                // smoothing_norm += (tri_nb-tri_na);
                // smoothing_norm *= beta;
                // smoothing_norm += (tri_nc-tri_nb);
                // smoothing_norm *= gamma;
                // smoothing_norm = tri_na;
                // smoothing_norm += (tri_nb*beta);
                // smoothing_norm += (tri_nc*gamma);
                // if (smoothing_norm.dot(eye_ray.getDir()) > 0)
                // {
                //     smoothing_norm.reverse_norm();
                // }
                // n = normalize(smoothing_norm);
                // std::cout<<"n:"<<" x: "<<n.getX()<<", y:"<<n.getY()<<", z:"<<n.getZ()<<std::endl;
                // Phong smmothing end
                //-------------------------------------------------------------------------------

                if(isBumping){
                    double radius = tri_min_dis[smallest_index]*0.7;
                    Vector3f temp_distance(
                        tri_ave[smallest_index].getX()-intersect.getX(),
                        tri_ave[smallest_index].getY()-intersect.getY(),
                        tri_ave[smallest_index].getZ()-intersect.getZ()
                    );
                    //std::cout<<radius<<std::endl;
                    if (temp_distance.modulus() <radius)
                    {
                        double t=temp_distance.modulus();
                        double w1=t/radius;
                        w1=w1*w1*w1*w1*w1;
                        double w2=1-w1;
                        temp_distance=normalize(temp_distance);
                        //n.setX(n.getX() + sin(10*PI*beta));
                        // std::cout<<beta<<gamma<<std::endl;
                        temp_distance=temp_distance*w1;
                        n=n*w2;
                        n=n+temp_distance;
                        n = normalize(n);
                    }
                }
                

                // Vector h
                Vector3f h = normalize(((l + v) / (l + v).modulus()));
                
                Color L(0.5, 0.5, 0.5); //L in each light source(La,Ls,Ld) I made them in the same value
  
                double coef_d = n.dot(l);
                double coef_s = pow(h.dot(n), alpha);
                Color ambient_light = temp_i.getKa() * L;
                Color diffuse_light = temp_i.getKd() * L * coef_d;
                Color specular_light = temp_i.getKs() * L * coef_s;
                Color total_light;

                // std::cout<<"t3: "<<t<<std::endl;
                //all the object will refect ambient light
                total_light = Color(0.0, 0.0, 0.0);
                // temp_i.write_pixel(total_light);
                // if (i == -45 && j == 45){
                // std::cout<<"pow: "<<pow((h.getX() * n.getX()), alpha)<<", "<<pow((h.getY() * n.getY()), alpha)<<", "<<pow((h.getZ() * n.getZ()), alpha)<<std::endl;
                // std::cout<<"v: "<<v.getX()<<", "<<v.getY()<<", "<<v.getZ()<<std::endl;
                // std::cout<<"n: "<<n.getX()<<", "<<n.getY()<<", "<<n.getZ()<<std::endl;
                // std::cout<<"l: "<<l.getX()<<", "<<l.getY()<<", "<<l.getZ()<<std::endl;
                // std::cout<<"h: "<<h.getX()<<", "<<h.getY()<<", "<<h.getZ()<<std::endl;

                // std::cout << "ambient: "<< "Red: " << ambient_light.getRed() << "blue: " << ambient_light.getBlue() << "Green: " << ambient_light.getGreen() << std::endl;
                // std::cout << "diffuse: "<< "Red: " << diffuse_light.getRed() << "blue: " << diffuse_light.getBlue() << "Green: " << diffuse_light.getGreen() << std::endl;
                // std::cout << "specular: "<< "Red: " << specular_light.getRed() << "blue: " << specular_light.getBlue() << "Green: " << specular_light.getGreen() << std::endl;

                bool has_intec=false;
                for (int w = 0; w < triangle_list.size(); w++)
                {
                    if (w == smallest_index)
                    {
                        continue;
                    }

                    temp_light_t = calBarycentry(light_ray, triangle_list[w]).getX();
                    if (temp_light_t > 0 && t != inf)
                    {
                        has_intec=1;
                        break;
                    }
                }
                if (has_intec) //the light block by object, in the shadow
                {
                    // std::vector<Point> tri = triangle_list[w].getPointList();
                    // Vector3f temp_norm = triangle_list[w].getNorm();
                    // std::cout<<temp_norm.getX()<<","<<temp_norm.getY()<<","<<temp_norm.getZ()<<std::endl;
                    // std::cout<<"point1:"<<tri[0].getX()<<tri[0].getY()<<tri[0].getZ()<<std::endl;
                    // std::cout<<"point2:"<<tri[1].getX()<<tri[1].getY()<<tri[1].getZ()<<std::endl;
                    // std::cout<<"point3:"<<tri[2].getX()<<tri[2].getY()<<tri[2].getZ()<<std::endl;
                    // in shadow
                    temp_i.write_pixel(ambient_light);
                }else{
                    total_light += diffuse_light;
                    total_light += specular_light;
                    total_light += ambient_light;
                    // total_light *= temp_i.getObjColor();
                    temp_i.write_pixel(total_light);
                }
                // std::cout << "no hit" << std::endl;
                
                // std::cout<<"total_light: "<< "Red: " <<total_light.getRed()<<"blue: " <<total_light.getBlue()<<"Green: " <<total_light.getGreen()<<std::endl;

                // }
            }
        }
    }
}