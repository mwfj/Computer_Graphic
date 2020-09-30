#include "ObjLoader.hpp"
#include "parameter.hpp"
#include <sstream>
#include <assert.h>

ObjLoader::ObjLoader(const std::string& temp_path){
    // std::cout<<"------------------------"<<std::endl;
    file_path = temp_path;
    
}

void ObjLoader::openFile(){
    file.open(file_path.c_str());//open OBJ file
    if (!file)
    {
        std::cout<< "File Does not found !!!"<<std::endl;
        file.close();
        return ;
    }
}

ObjLoader::~ObjLoader()
{
    if (file)
    {
        file.close();// if file exist when destroy this objection, close it.
    }
    
}

void ObjLoader::parsedOBJFile(){
    std::string line;
    while (std::getline(file,line))
    {   std::istringstream iss(line);
        std::string current_line;
        //Store the line currently read into a string for comparsion and extract
        iss >> current_line;
        // std::cout<<current_line<<std::endl; 
        if (current_line == "v")
        {
            double temp_v_x, temp_v_y, temp_v_z;
            iss >> temp_v_x >> temp_v_y >> temp_v_z;
            Vector3f temp_v(temp_v_x,temp_v_y,temp_v_z);
            vertex_list.push_back(temp_v);
        }else if (current_line == "vt")
        {
            double temp_vt_x, temp_vt_y;
            iss >> temp_vt_x >>temp_vt_y;
            Vector2f temp_vt(temp_vt_x, temp_vt_y);
            vt_list.push_back(temp_vt);
        }else if (current_line == "vn")
        {
             double temp_vn_x, temp_vn_y, temp_vn_z;
             iss >> temp_vn_x >> temp_vn_y >> temp_vn_z;
             Vector3f temp_vn(temp_vn_x, temp_vn_y, temp_vn_z);
             vn_list.push_back(temp_vn);
        }else if(current_line == "f"){
            // f vertx/vt/vn
            double vertex_index, vt_index, vn_index;
            std::vector<int> temp_vec; // recording all the vertexes
            // temporary store the index information for each triangle
            std::string ss;
            while (iss >> ss)
            {
                std::string f_line = ss.c_str();
                std::istringstream f_iss(f_line);
                vertex_index=-1;
                f_iss>>vertex_index;
                assert(vertex_index>=0);
                temp_vec.push_back(vertex_index);
                //vertex_indices_list.push_back(vertex_index);
                //vt_indices_list.push_back(vt_index);
                //vn_indices_list.push_back(vn_index);
            }
            if(temp_vec.size()<3){
                std::cerr<<"Build Triangle Failed:2 vertexes cannot make a triangle"<<std::endl;
                assert(temp_vec.size()>=3);
            }

            // Change everything to triangle
            for(int i=0;i<temp_vec.size()-2;i++)
            {
                vertex_indices_list.push_back(temp_vec[0]);
                vertex_indices_list.push_back(temp_vec[i+1]);
                vertex_indices_list.push_back(temp_vec[i+2]);
            }
        }
              
    }
    // std::cout<<vertex_indices_list.size()<<std::endl;
    // for (int j = 0; j < vertex_indices_list.size(); j++)
    // {
    //     std::cout<<vertex_indices_list[j]<<"; ";
    // }
    // std::cout<<std::endl;
    // std::cout<<vertex_list[vertex_indices_list[0]].getX()<<","<<vertex_list[vertex_indices_list[0]].getY()<<","<<vertex_list[vertex_indices_list[0]].getZ()<<std::endl;
    // for (int i = 0; i < vertex_indices_list.size(); i++)
    // {
    //     std::cout<<"i: "<<i<<std::endl;
    //     std::cout<<vertex_list[vertex_indices_list[i]-1].getX()<<","<<vertex_list[vertex_indices_list[i]-1].getY()<<","<<vertex_list[vertex_indices_list[i]-1].getZ()<<std::endl;
    // }
    
    // std::cout<< vertex_indices_list[0]<< vt_indices_list[0] <<vn_indices_list[0]<<std::endl;
    // std::cout<< vertex_indices_list[1]<< vt_indices_list[1] <<vn_indices_list[1]<<std::endl;
    // std::cout<< vertex_indices_list[2]<< vt_indices_list[2] <<vn_indices_list[2]<<std::endl;
    // std::cout<< vertex_indices_list[3]<< vt_indices_list[3] <<vn_indices_list[3]<<std::endl;
    // std::cout<< vertex_indices_list[4]<< vt_indices_list[4] <<vn_indices_list[4]<<std::endl;
    file.close();
    
}

void ObjLoader::shape_normalize(){
    double top = getMax().getY();
    double bottom = getMin().getY();
    double left = getMin().getX();
    double right = getMax().getX();
    double near = getMax().getZ();
    double far = getMin().getZ();
    // double shape_size = 100.00;

    for (int i = 0; i < vertex_list.size(); i++)
    {
        vertex_list[i].setX( vertex_list[i].getX() * ( SHAPE_SIZE/( right-left ) ) );
        vertex_list[i].setY( vertex_list[i].getY() * ( SHAPE_SIZE/( top-bottom ) ) );
        vertex_list[i].setZ( vertex_list[i].getZ() * ( SHAPE_SIZE/( near-far ) ) );
    }


}

// Averaging x axis, y axis and z axis
Vector3f ObjLoader::getCenter() const{
    double temp_x = 0, temp_y = 0, temp_z =0;
    int list_size = vertex_list.size();
    for (int i = 0; i < list_size; i++)
    {
        temp_x += vertex_list[i].getX();
        temp_y += vertex_list[i].getY();
        temp_z += vertex_list[i].getZ();
    }
    temp_x /= list_size;
    temp_y /= list_size;
    temp_z /= list_size;
    Vector3f center_v3(temp_x, temp_y, temp_z);
    
    return center_v3;
}
// get max value for x, y, z
Vector3f ObjLoader::getMax() const{
    double max_x = vertex_list[0].getX(), max_y = vertex_list[0].getY(), max_z = vertex_list[0].getZ();
    double temp_x = 0, temp_y = 0, temp_z =0;
    int list_size = vertex_list.size();
    for (int i = 0; i < list_size; i++)
    {
        temp_x = vertex_list[i].getX();
        temp_y = vertex_list[i].getY();
        temp_z = vertex_list[i].getZ();
        if (temp_x > max_x)
        {
            std::swap(max_x,temp_x);
        }
        if (temp_y > max_y)
        {
            std::swap(max_y,temp_y);
        }
        if (temp_z > max_z)
        {
            std::swap(max_z,temp_z);
        }
        
    }
    Vector3f max_v3(max_x,max_y,max_z);
    // std::cout<<"Max value:" <<"x: "<<max_x<<", "<<"y: "<<max_y<<", "<<"z: "<<max_z<<", "<<std::endl;   
    return max_v3;
}
// get min value for x, y, z
Vector3f ObjLoader::getMin() const{
    double min_x = vertex_list[0].getX(), min_y = vertex_list[0].getY(), min_z = vertex_list[0].getZ();
    double temp_x = 0, temp_y = 0, temp_z =0;
    int list_size = vertex_list.size();
    for (int i = 0; i < list_size; i++)
    {
        temp_x = vertex_list[i].getX();
        temp_y = vertex_list[i].getY();
        temp_z = vertex_list[i].getZ();
        if (temp_x < min_x)
        {
            std::swap(min_x,temp_x);
        }
        if (temp_y < min_y)
        {
            std::swap(min_y,temp_y);
        }
        if (temp_z < min_z)
        {
            std::swap(min_z,temp_z);
        }
        
    }
    Vector3f min_v3(min_x,min_y,min_z);
    // std::cout<<"Min value:" <<"x: "<<min_x<<", "<<"y: "<<min_y<<", "<<"z: "<<min_z<<", "<<std::endl;
    return min_v3;  
}