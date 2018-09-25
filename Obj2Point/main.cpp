#include <iostream>
#include "obj_shape_loader.h"
#include "utils_sampling.hpp"

inline void write_point_cloud(
    const std::string& fn,
    const std::vector<Vec3>& pts,
    const std::vector<Vec3>& nrs
)
{
    std::ofstream ofs(fn);
    for(int i=0;i<pts.size();i++)
        ofs<<pts[i].x<<" "<<pts[i].y<<" "<<pts[i].z<<" "
           <<nrs[i].x<<" "<<nrs[i].y<<" "<<nrs[i].z<<"\n";
    ofs.flush();
    ofs.close();
}

int main(int argc, char** argv) {
#ifdef TEST_CODE
    std::vector<Vec3> verts,norms;
    std::vector<int> verts_idxs,norms_idxs;
    get_mesh("/home/liuyuan/data/ShapeNetCore.v2/02691156/1a6ad7a24bb89733f412783097373bdc/models/model_normalized.obj",
             verts,norms,verts_idxs,norms_idxs);
    std::cout<<"num verts: "<<verts.size()<<"\t num norms: "<<norms.size()<<"\t num triangles: "<<verts_idxs.size()<<std::endl;
    assert(verts_idxs.size()==norms_idxs.size());

    calculate_norm(verts,verts_idxs,norms);

    std::vector<Vec3> sample_verts,sample_norms;
    poisson_disk(0.005f,4096,verts,norms,verts_idxs,sample_verts,sample_norms);

    write_point_cloud("/home/liuyuan/code/Obj2Points/test.txt",sample_verts);
    return 0;
#else
    if(argc<3||argc>4){
        std::cout<<"invalid parameters:\n program path-to-obj-file path-to-output-txt-file "
                   "[sample-radius=0.005]\n";
        return 0;
    }
    float radius=0.005;
    if(argc==4) radius=std::stof(argv[3]);

    std::vector<Vec3> verts,norms;
    std::vector<int> verts_idxs,norms_idxs;
    read_mesh(argv[1],verts,norms,verts_idxs,norms_idxs);
    calculate_norm(verts,verts_idxs,norms);
    std::vector<Vec3> sample_verts,sample_norms;
    poisson_disk(radius,4096,verts,norms,verts_idxs,sample_verts,sample_norms);

    write_point_cloud(argv[2],sample_verts,sample_norms);
    std::cout<<"\n";
    return 0;
#endif

}