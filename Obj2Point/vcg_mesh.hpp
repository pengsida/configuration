#ifndef VCG_MESH_HPP__
#define VCG_MESH_HPP__

#include <vector>
#include <cassert>

#include <vcg/simplex/vertex/base.h>
#include <vcg/simplex/vertex/component.h>
#include <vcg/simplex/face/base.h>
#include <vcg/simplex/face/component.h>

#include <vcg/complex/complex.h>
#include <vcg/complex/allocate.h>

#include <vcg/complex/algorithms/point_sampling.h>

/**
    @file vcg_mesh.hpp
    @brief Handling and definitions of vcg library's meshes

    The vcg library is powerfull tool for mesh processing (mesh repair,
    hole filling, mesh smoothing, mesh sampling and more). See
    @link http://vcg.sourceforge.net/index.php/Tutorial to get more infos.

    This headers defines classes of meshes/vertices/faces/... that can be
    processed by vcg.

    You'll find also some functions to ease the interaction between vcg's meshes
    and our meshes.


    An example to process a vcg mesh:
    @code
    #include "vcg_mesh.hpp"
    #include <vcg/complex/algorithms/smooth.h>
    {
        MyMesh vcg_mesh;
        // fill mesh ...
        // Do a classic laplacian smoothing with 10 iterations
        vcg::tri::Smooth<MyMesh>::VertexCoordLaplacian(vcg_mesh, 10);
    }
    @endcode

    @warning doesn't seem to be cuda 4.1 compatible dunno which c++ feature
    is missing ... You won't be able to include this in .cu files
*/

// =============================================================================
namespace vcg {
// =============================================================================


class MyVertex;
class MyFace;

// -----------------------------------------------------------------------------

class MyUsedTypes : public vcg::UsedTypes
        <
        vcg::Use<MyVertex>::AsVertexType,
        vcg::Use<MyFace>::AsFaceType
        >
{ };

// -----------------------------------------------------------------------------

/** @brief the type of a vcg vertex
    use case:
    @code
    MyVertex v;
    // access position
    vcg::vertex::Coord3f pos = v.P()
    pos.X() = pos.Y() = pos.Z() = 0.f;
    // access normal
    vcg::vertex::Normal3f nor = v.N()
    nor.X() = nor.Y() = nor.Z() = 0.f;
    @endcode
*/
class MyVertex : public vcg::Vertex
        <
        MyUsedTypes,
        vcg::vertex::Coord3f,
        vcg::vertex::Normal3f
        >
{

};

// -----------------------------------------------------------------------------

/** @brief the type of a vcg face */
class MyFace : public vcg::Face<MyUsedTypes, vcg::face::VertexRef> { };

// -----------------------------------------------------------------------------

/** @brief the type of a vcg mesh */
class MyMesh : public vcg::tri::TriMesh
        <
        std::vector<MyVertex>,
        std::vector<MyFace>
        >
{
public:

    typedef vcg::Point3f NormalType;

    MyMesh();

    /// Copy constructor
    MyMesh(const MyMesh& m);


    /// A simple way to concatenate triangles to the mesh.
    /// @param verts: list of vertices verts[i*3+0] = x_coord,
    /// verts[i*3+1] = y_coord etc.
    /// @param triangles: list of triangles referencing a vertex index three
    /// by three. triangles[i*3+0] = first_vert_idx,
    /// triangles[i*3+0] = second_vert_idx etc.
    /// @param nb_vert: number of vertices. 'verts' array size == nb_vert*3
    /// @param nb_face: number of triangles. 'triangles' array size == nb_face*3
    /// @warning you might want to update the bounding box
    void concat(const float* verts, const int* triangles, int nb_vert, int nb_face);

    /// @param normals: normals array of size == (this->vert.size()*3)
    void set_normals(const float* normals);

    /// update the mesh bounding box
    void update_bb();

    /// fill 'vertices' with the the vcg mesh's vertices.
    template<class Vert_t>
    void get_vertices(std::vector<Vert_t>& vertices)
    {
        assert( sizeof(Vert_t) == (sizeof(float) * 3) );

        const int nb_vert = this->vert.size();
        vertices.clear();
        vertices.resize(nb_vert);
        float* ptr = (float*)&(vertices[0]);
        MyMesh::ConstVertexIterator vi = this->vert.begin();
        for(int i = 0; i < nb_vert; ++i, ++vi)
        {
            MyMesh::CoordType coord = (*vi).P();
            ptr[i*3 + 0] = coord.X();
            ptr[i*3 + 1] = coord.Y();
            ptr[i*3 + 2] = coord.Z();
        }
    }

    int nb_vert() const { return this->vn; }

};

// -----------------------------------------------------------------------------

/// @brief stores samples in a std::vector<MyMesh::CoordType>
class VecSampler : public vcg::tri::TrivialSampler<MyMesh> { };

// -----------------------------------------------------------------------------

/// @brief stores samples in a vcg_mesh
class MySampler {
public:

    MyMesh *mesh;


    MySampler(MyMesh* _m) : mesh(_m)
    { }

    void AddVert(const MyMesh::VertexType& p)
    {
        vcg::tri::Allocator<MyMesh>::AddVertices(*mesh, 1);
        mesh->vert.back().ImportData(p);
    }

    void AddFace(const MyMesh::FaceType& f, MyMesh::CoordType p)
    {
        vcg::tri::Allocator<MyMesh>::AddVertices(*mesh, 1);
        mesh->vert.back().P() = f.P(0)      * p[0] + f.P(1)      * p[1] + f.P(2)      * p[2];
        mesh->vert.back().N() = f.V(0)->N() * p[0] + f.V(1)->N() * p[1] + f.V(2)->N() * p[2];

    }

    void AddTextureSample(const MyMesh::FaceType&,
                          const MyMesh::CoordType&,
                          const vcg::Point2i& ,
                          float )
    {
        // Retrieve the color of the sample from the face f using the
        // barycentric coord p and write that color in a texture image at
        // position <tp[0], texHeight-tp[1]> if edgeDist is > 0 then the
        // corresponding point is affecting face color even if outside the face
        // area (in texture space)
        // see vcg/complex/algorithms/point_sampling.h/: class TrivialSampler
        // for an example
    }
};

// -----------------------------------------------------------------------------

void fill_vcg_mesh(MyMesh& vcg_mesh,
                   const float* verts,
                   const int* triangles,
                   int nb_vert,
                   int nb_face);

// -----------------------------------------------------------------------------





// =============================================================================
namespace MyAlgorithms {
// =============================================================================


struct Poison_setup {

    Poison_setup() :
        _radius( 0.f ),
        _nb_samples( 1000 ),
        _montecarlo_rate( 20 ),
        _sub_sampling( false ),
        _approx_geodesic_dist(false),
        _refine(false)
    {    }


    float _radius;              ///< Min radius
    int _nb_samples;            ///< Max number of samples
    int _montecarlo_rate;
    bool _sub_sampling;
    bool _approx_geodesic_dist;
    bool _refine;               ///< use existing vertices to sample

};

// -----------------------------------------------------------------------------

void poison_disk_sampling(MyMesh& vcg_mesh,
                          const Poison_setup& params,
                          MyMesh &samples);

}// END NAMESPACE MyAlgorithms =================================================

}// END NAMESPACE VCG ===========================================================

#endif // VCG_MESH_HPP__
