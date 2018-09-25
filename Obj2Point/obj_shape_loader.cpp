//
// Created by liuyuan on 18-7-10.
//

#include "obj_shape_loader.h"


bool calculate_norm(
        const std::vector<Vec3>& verts,
        const std::vector<int>& verts_tri,
        std::vector<Vec3>& norms
)
{
    norms.clear();
    // compute normal for every face
    std::vector<std::vector<Vec3>> norm_vec(verts.size());
    for(int i=0;i<verts_tri.size()/3;i++)
    {
        int i0=verts_tri[i*3];
        int i1=verts_tri[i*3+1];
        int i2=verts_tri[i*3+2];

        norm_vec[i0].push_back(cross_dot(verts[i1]-verts[i0],verts[i2]-verts[i0]));
        norm_vec[i1].push_back(cross_dot(verts[i2]-verts[i1],verts[i0]-verts[i1]));
        norm_vec[i2].push_back(cross_dot(verts[i0]-verts[i2],verts[i1]-verts[i2]));
    }

    // average normals
    for(int i=0;i<norm_vec.size();i++)
    {
        if(norm_vec[i].empty())
            norms.push_back(Vec3(0.f,0.f,0.f));
        else
        {
            Vec3 norm(0.f,0.f,0.f);
            for(int j=0;j<norm_vec[i].size();j++)
            {
                // if normal not consistent then flip it
                if(j>0&&norm_vec[i][j]*norm_vec[i][0]<0) norm_vec[i][j]=-norm_vec[i][j];
                norm+=norm_vec[i][j];
            }
            norm=norm/float(norm_vec[i].size());
            norms.push_back(norm);
        }
    }
    return true;
}

bool read_mesh(
        const std::string &fn,
        std::vector<Vec3> &verts,
        std::vector<Vec3> &norms,
        std::vector<int> &verts_tri,
        std::vector<int> &norms_tri
)
{
    if (fn.substr(fn.size() - 4, 4) != ".obj")
        return false;

    verts.clear();
    norms.clear();
    verts_tri.clear();
    norms_tri.clear();

    std::string curline;
    auto ifs=std::ifstream(fn);
    while (std::getline(ifs, curline))
    {
        if(curline.size()<2) continue;
        std::string head=firstToken(curline);
        if(head=="v")
        {
            std::vector<std::string> spos;
            Vec3 vpos;
            split(tail(curline), spos, " ");

            vpos.x = std::stof(spos[0]);
            vpos.y = std::stof(spos[1]);
            vpos.z = std::stof(spos[2]);

            verts.push_back(vpos);
        }
        else if(head=="vn")
        {
            std::vector<std::string> snorm;
            Vec3 vnorm;
            split(tail(curline), snorm, " ");

            vnorm.x = float(std::stod(snorm[0]));
            vnorm.y = float(std::stod(snorm[1]));
            vnorm.z = float(std::stod(snorm[2]));

            norms.push_back(vnorm);
        }
        else if(head=="f")
        {
            std::vector<std::string> sidxs;
            split(tail(curline), sidxs, " ");
            assert(sidxs.size()==3);

            for(int i=0;i<3;i++)
            {
                std::vector<std::string> csidxs;
                split(sidxs[i], csidxs, "/");
                assert(csidxs.size()==3);
                verts_tri.push_back(std::stoi(csidxs[0])-1);
                norms_tri.push_back(std::stoi(csidxs[2])-1);
            }
        }
    }
    ifs.close();

    return true;
}