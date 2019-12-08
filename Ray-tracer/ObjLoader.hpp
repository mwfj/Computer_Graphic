#ifndef OBJLOADER__H
#define OBJLOADER__H
/**
 * @author Wufangjie Ma
 * This class is for loading and parse the Obj file
 * After parse Obj file, store its information for its related vector
 **/
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Vector2f.hpp"
#include "Vector3f.hpp"
// This class is to parsed the OBJ file and store its information to vectors.
class ObjLoader
{
private:
    std::vector<Vector2f> vt_list; // store texture information
    std::vector<Vector3f> vertex_list; // store vertex informatino
    std::vector<Vector3f> vn_list; // store norm informatino

    std::vector<int> vertex_indices_list; //vertex index form face
    std::vector<int> vn_indices_list; // norm index
    std::vector<int> vt_indices_list; //texture index

    std::fstream file;

    ObjLoader(const ObjLoader&);
    ObjLoader& operator=(const ObjLoader&);

public:
    // ObjLoader(){};
    ObjLoader(const std::string&);
    void parsedOBJFile();
    ~ObjLoader();

    Vector3f getCenter() const;
    Vector3f getMax() const;
    Vector3f getMin() const;
    void shape_normalize(); // Reshape 3D model
    const std::vector<Vector2f>& getVT_list() const{
        return vt_list;
    }
    const std::vector<Vector3f>& getVertex_list() const{
        return vertex_list;
    }
    const std::vector<Vector3f>& getVN_list() const{
        return vn_list;
    }

    const std::vector<int>& get_Vertex_indices() const{
        return vertex_indices_list;
    }

    const std::vector<int>& get_VN_indices() const{
        return vn_indices_list;
    }

    const std::vector<int>& get_VT_indices(){
        return vt_indices_list;
    }
};


#endif // !OBJLOADER__H