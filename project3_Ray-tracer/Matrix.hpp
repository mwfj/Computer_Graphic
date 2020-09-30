#ifndef MATRIX__H
#define MATRIX__H
#include <math.h>
#include <iostream>
#include <vector>
#include "Vector3f.hpp"
/**
 * @author Wufangjie Ma
 * This class is for matrix related operation
 **/
class Matrix
{
private:
    std::vector<std::vector<double> > diagonal;
    std::vector<std::vector<double> > P;
    Matrix& operator=(const Matrix&);

public:
    std::vector<std::vector<double> > Transpose(const std::vector<std::vector<double> >&);
    std::vector<std::vector<double> > dotProduct(const std::vector<std::vector<double> >&, const std::vector<std::vector<double> >&);
    std::vector<std::vector<double> > dotProduct();
    Vector3f cross_product(const Vector3f&, const Vector3f&);
    //only for 3x3 matrix
    // double determinant(const std::vector<std::vector<double> >&);
    // the reason for using array rather than vector is for loading speed, avoid malioc
    double determinant(double (&)[3][3]);
    Vector3f reverse_norm(const Vector3f&) const;
    Matrix(){};
    Matrix(const Matrix&);
    Matrix(const std::vector<std::vector<double> >&, const std::vector<std::vector<double> >&);
    Matrix(double, double);
    ~Matrix();
    const std::vector<std::vector<double> >& getDiagonal() const{
        return diagonal;
    }

    const std::vector<std::vector<double> >& getP() const{
        return P;
    }
    std::vector<std::vector<double> > Normalize();
};

#endif //MATRIX__H