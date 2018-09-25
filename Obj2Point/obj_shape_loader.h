//
// Created by liuyuan on 18-7-9.
//

#ifndef OBJ2POINTS_OBJ_SHAPE_LOADER_H
#define OBJ2POINTS_OBJ_SHAPE_LOADER_H

#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include "utils_sampling.hpp"

using namespace Utils_sampling;

// Split a String into a string array at a given token
inline void split(const std::string &in,
                  std::vector<std::string> &out,
                  std::string token)
{
    out.clear();

    std::string temp;

    for (int i = 0; i < int(in.size()); i++)
    {
        std::string test = in.substr(i, token.size());

        if (test == token)
        {
            if (!temp.empty())
            {
                out.push_back(temp);
                temp.clear();
                i += (int)token.size() - 1;
            }
            else
            {
                out.push_back("");
            }
        }
        else if (i + token.size() >= in.size())
        {
            temp += in.substr(i, token.size());
            out.push_back(temp);
            break;
        }
        else
        {
            temp += in[i];
        }
    }
}

// Get tail of string after first token and possibly following spaces
inline std::string tail(const std::string &in)
{
    size_t token_start = in.find_first_not_of(" \t");
    size_t space_start = in.find_first_of(" \t", token_start);
    size_t tail_start = in.find_first_not_of(" \t", space_start);
    size_t tail_end = in.find_last_not_of(" \t");
    if (tail_start != std::string::npos && tail_end != std::string::npos)
    {
        return in.substr(tail_start, tail_end - tail_start + 1);
    }
    else if (tail_start != std::string::npos)
    {
        return in.substr(tail_start);
    }
    return "";
}

// Get first token of string
inline std::string firstToken(const std::string &in)
{
    if (!in.empty())
    {
        size_t token_start = in.find_first_not_of(" \t");
        size_t token_end = in.find_first_of(" \t", token_start);
        if (token_start != std::string::npos && token_end != std::string::npos)
        {
            return in.substr(token_start, token_end - token_start);
        }
        else if (token_start != std::string::npos)
        {
            return in.substr(token_start);
        }
    }
    return "";
}



inline Vec3 cross_dot(
        const Vec3& v1,
        const Vec3& v2
)
{
    return {v1.y*v2.z-v1.z*v2.y,
            v1.z*v2.x-v1.x*v2.z,
            v1.x*v2.y-v1.y*v2.x};
}

///
/// due to the .obj file has multiple normals for single vertex
/// the normal is estimated by the face vertices and average among faces
/// \param verts
/// \param verts_tri
/// \param norms
/// \return
bool calculate_norm(
        const std::vector<Vec3>& verts,
        const std::vector<int>& verts_tri,
        std::vector<Vec3>& norms
);

///
/// only parse the shape information from .obj files
/// this function assumes all faces consist of triangles and doesn't support other surface.
/// \param fn
/// \param verts
/// \param norms
/// \param verts_tri
/// \param norms_tri
/// \return
bool read_mesh(
        const std::string &fn,
        std::vector<Vec3> &verts,
        std::vector<Vec3> &norms,
        std::vector<int> &verts_tri,
        std::vector<int> &norms_tri
);

#endif //OBJ2POINTS_OBJ_SHAPE_LOADER_H
