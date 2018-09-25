#include "utils_sampling.hpp"

#include "vcg_mesh.hpp"

// =============================================================================
namespace Utils_sampling {
// =============================================================================

void poisson_disk(float radius,
                  int nb_samples,
                  const std::vector<Vec3>& verts,
                  const std::vector<Vec3>& nors,
                  const std::vector<int>& tris,
                  std::vector<Vec3>& samples_pos,
                  std::vector<Vec3>& samples_nor)
{
    assert(verts.size() == nors.size());
    assert(verts.size() > 0);
    assert(tris.size() > 0);

    vcg::MyMesh vcg_mesh, sampler;
    vcg_mesh.concat((float*)&(verts[0]), (int*)&(tris[0]), verts.size(), tris.size()/3);
    vcg_mesh.set_normals( (float*)&(nors[0]) );
    vcg_mesh.update_bb();

    vcg::MyAlgorithms::Poison_setup pp;
    pp._radius = radius;
    pp._nb_samples = nb_samples;
    pp._approx_geodesic_dist = true;
    vcg::MyAlgorithms::poison_disk_sampling(vcg_mesh, pp, sampler);

    const int nb_vert = sampler.vert.size();
    samples_pos.clear();
    samples_nor.clear();
    samples_pos.resize( nb_vert );
    samples_nor.resize( nb_vert );
    vcg::MyMesh::VertexIterator vi = sampler.vert.begin();
    for(int i = 0; i < nb_vert; ++i, ++vi)
    {
        vcg::MyMesh::CoordType  p = (*vi).P();
        vcg::MyMesh::NormalType n = (*vi).N();
        samples_pos[i] = Vec3(p.X(), p.Y(), p.Z());
        samples_nor[i] = Vec3(n.X(), n.Y(), n.Z());
    }

    // sampler.get_vertices( samples_pos );

}

}// END UTILS_SAMPLING NAMESPACE ===============================================
