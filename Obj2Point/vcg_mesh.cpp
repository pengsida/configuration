#include "vcg_mesh.hpp"

#include <vcg/complex/algorithms/update/bounding.h>
#include <vcg/complex/append.h>

// =============================================================================
namespace vcg {
// =============================================================================


MyMesh::MyMesh() : vcg::tri::TriMesh< std::vector<MyVertex>, std::vector<MyFace> >()
{
    bbox = Box3<ScalarType>();
}

// -----------------------------------------------------------------------------

MyMesh::MyMesh(const MyMesh& m){
    this->Clear();
    // Since append is not using const iterators for m I'm forced to use
    // the ugly const_cast(). shame I know ...
    tri::Append<MyMesh, MyMesh>::Mesh(*this, const_cast<MyMesh&>(m));
}

// -----------------------------------------------------------------------------

void MyMesh::concat(const float* verts,
                    const int* triangles,
                    int nb_vert,
                    int nb_face)

{
    vcg::tri::Allocator<MyMesh>::AddVertices(*this, nb_vert);
    vcg::tri::Allocator<MyMesh>::AddFaces   (*this, nb_face);

    std::vector<VertexPointer> ivp( nb_vert );
    VertexIterator vi = this->vert.end();
    for(int i = (nb_vert-1); i >= 0; --i)
    {
        --vi;
        ivp[i] = &*vi;
        (*vi).P() = CoordType(verts[i*3], verts[i*3+1], verts[i*3+2]);
    }

    FaceIterator fi = this->face.end();
    for(int i = (nb_face-1); i >= 0; --i)
    {
        --fi;
        (*fi).V(0) = ivp[ triangles[i*3 + 0] ];
        (*fi).V(1) = ivp[ triangles[i*3 + 1] ];
        (*fi).V(2) = ivp[ triangles[i*3 + 2] ];
    }
}

// -----------------------------------------------------------------------------

void MyMesh::set_normals(const float* normals)
{
    const int nb_vert = this->vert.size();
    vcg::MyMesh::VertexIterator vi = this->vert.begin();
    for(int i = 0; i < nb_vert; ++i, ++vi)
    {
        (*vi).N() = NormalType(normals[i*3 + 0], normals[i*3 + 1], normals[i*3 + 2]);
        /*
        (*vi).N().X() = normals[i*3 + 0];
        (*vi).N().Y() = normals[i*3 + 1];
        (*vi).N().Z() = normals[i*3 + 2];
        */
    }
}

// -----------------------------------------------------------------------------

void MyMesh::update_bb()
{
    vcg::tri::UpdateBounding<MyMesh>::Box( *this );
}

// -----------------------------------------------------------------------------

void fill_vcg_mesh(MyMesh& vcg_mesh,
                   const float* verts,
                   const int* triangles,
                   int nb_vert,
                   int nb_face)

{
    vcg_mesh.Clear();
    vcg::tri::Allocator<MyMesh>::AddVertices(vcg_mesh, nb_vert);
    vcg::tri::Allocator<MyMesh>::AddFaces   (vcg_mesh, nb_face);

    std::vector<MyMesh::VertexPointer> ivp( nb_vert );
    MyMesh::VertexIterator vi = vcg_mesh.vert.begin();
    for(int i = 0; i < nb_vert; ++i, ++vi)
    {
        ivp[i] = &*vi;
        (*vi).P() = MyMesh::CoordType(verts[i*3], verts[i*3+1], verts[i*3+2]);
    }

    MyMesh::FaceIterator fi = vcg_mesh.face.begin();
    for(int i = 0; i < nb_face; ++i, ++fi)
    {
        (*fi).V(0) = ivp[ triangles[i*3 + 0] ];
        (*fi).V(1) = ivp[ triangles[i*3 + 1] ];
        (*fi).V(2) = ivp[ triangles[i*3 + 2] ];
    }
}

// -----------------------------------------------------------------------------

// =============================================================================
namespace MyAlgorithms {
// =============================================================================


void poison_disk_sampling(MyMesh& vcg_mesh,
                          const Poison_setup& params,
                          MyMesh& samples)
{

    // Parameters
    float rad     = params._radius;
    int   nb_samp = params._nb_samples;
    int   mc_rate = params._montecarlo_rate;

    bool sub_sample      = params._sub_sampling;
    bool approx_geodesic = params._approx_geodesic_dist;
    bool refine          = params._refine;
    // end parameters

    // check parameters
    if( rad < 0.00001f && nb_samp == 0)
    {
        std::cerr << "ERROR poisson disk sampling:";
        std::cerr << "you must specify a maximal radius";
        std::cerr << "or a minimal number of samples";
    }

    if(rad <= 0) rad     = vcg::tri::SurfaceSampling<MyMesh, MySampler>::ComputePoissonDiskRadius( vcg_mesh, nb_samp );
    else         nb_samp = vcg::tri::SurfaceSampling<MyMesh, MySampler>::ComputePoissonSampleNum ( vcg_mesh, rad     );

    printf("Computing %i Poisson Samples for an expected radius of %f", nb_samp, rad);

    // first of all generate montecarlo samples for fast lookup
    MyMesh* presampledMesh = &vcg_mesh;

    // this mesh is used only if we need real poisson sampling
    // (and therefore we need to choose points different from
    // the starting mesh vertices)
    MyMesh montecarloMesh;

    if( !sub_sample )
    {
        MySampler sampler( &montecarloMesh );
        vcg::tri::SurfaceSampling<MyMesh, MySampler>::Montecarlo(vcg_mesh, sampler, nb_samp * mc_rate);

        montecarloMesh.bbox = vcg_mesh.bbox; // we want the same bounding box
        presampledMesh = &montecarloMesh;

        printf("Generated %i Montecarlo Samples", montecarloMesh.vn);
    }


    vcg::tri::SurfaceSampling<MyMesh, MySampler>::PoissonDiskParam pp;

    if( refine )
    {
        pp.preGenFlag = true;
        pp.preGenMesh = &vcg_mesh;
    }

    pp.geodesicDistanceFlag = approx_geodesic;

    {
        MySampler sampler( &samples );
        vcg::tri::SurfaceSampling<MyMesh, MySampler>::PoissonDiskPruning(vcg_mesh, sampler, *presampledMesh, rad, pp);
        //vcg::tri::SurfaceSampling<MyMesh,MySampler>::PoissonDisk(vcg_mesh, mps, *presampledMesh, radius,pp);

        samples.update_bb();
        printf("Sampling created a new mesh of %i points", samples.vn);
        fflush(stdout);
    }

}

}// END NAMESPACE MyAlgorithms =================================================

}// END NAMESPACE VCG ==========================================================
