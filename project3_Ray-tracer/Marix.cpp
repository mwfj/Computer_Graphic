#include "Matrix.hpp"
#include <iostream>

Matrix::Matrix(const Matrix& m_)
    :diagonal(m_.getDiagonal()), P(m_.getP()){}

Matrix::Matrix(const std::vector<std::vector<double> > &dia_, const std::vector<std::vector<double> >&p_)
    :diagonal(dia_),P(p_)
{
}

Matrix::~Matrix()
{}

std::vector<std::vector<double> > Matrix::dotProduct(const std::vector<std::vector<double> >& a, const std::vector<std::vector<double> >& b){

    if(a[0].size() != b.size()){
        std::cout<<"The column of first matrix unequal to the row of second matrix!!"<<std::endl;
    }
    std::vector<std::vector<double> > c(a.size(), std::vector<double>(b[0].size(),0));
    int a_row = a.size();
    int a_col = a[0].size();
    int b_col = b[0].size();
    for (int i = 0; i < a_row; i++)
    {
        for (int j = 0; j < b_col; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k <a_col; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
            
        }
        
    }
    return c;
}

std::vector<std::vector<double> > Matrix::dotProduct(){

    if(diagonal[0].size() != P.size()){
        std::cout<<"The column of first matrix unequal to the row of second matrix!!"<<std::endl;
    }
    std::vector<std::vector<double> > c(diagonal.size(), std::vector<double>(P[0].size(),0));
    int a_row = diagonal.size();
    int a_col = diagonal[0].size();
    int b_col = P[0].size();
    for (int i = 0; i < a_row; i++)
    {
        for (int j = 0; j < b_col; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k <a_col; k++)
            {
                c[i][j] += diagonal[i][k] * P[k][j];
            }
            
        }
        
    }
    return c;
}

std::vector<std::vector<double> > Transpose(const std::vector<std::vector<double> >& matrix){

    std::vector<std::vector<double> > transpose(matrix[0].size(), std::vector<double>());
    int row = matrix.size();
    int col = matrix[0].size();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            transpose[j].push_back(matrix[i][j]);
        }
    }
    return transpose;
}

Vector3f Matrix::cross_product(const Vector3f& a, const Vector3f& b){
    double temp_x = ( a.getY() * b.getZ() ) - (b.getY()*a.getZ());
    double temp_y = -(a.getX()*b.getZ() - b.getX()*a.getZ() );
    double temp_z = ( a.getX()*b.getY() ) - ( b.getX()*a.getY());
    return Vector3f(temp_x,temp_y,temp_z);
}

Vector3f Matrix::reverse_norm(const Vector3f& norm) const{
    return Vector3f(-norm.getX(), -norm.getY(), -norm.getZ());
}

// This function only fit in 3x3 matrix
double Matrix::determinant(double (&matrix)[3][3]){
    double sum1 = matrix[0][2]*matrix[1][0]*matrix[2][1]+matrix[0][1]*matrix[1][2]*matrix[2][0]+matrix[0][0]*matrix[1][1]*matrix[2][2];
    double sum2 = matrix[2][2]*matrix[0][1]*matrix[1][0]+matrix[2][1]*matrix[1][2]*matrix[0][0]+matrix[0][2]*matrix[1][1]*matrix[2][0];
    double det = sum1 - sum2;
    // std::cout<<"sum1:"<<sum1<<" sum2: "<<sum2<<std::endl;
    return det;
}