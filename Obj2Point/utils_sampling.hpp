#ifndef UTILS_SAMPLING_HPP
#define UTILS_SAMPLING_HPP
#include <vector>

// =============================================================================
namespace Utils_sampling {
// =============================================================================

struct Vec3 {
    Vec3() { x = y = z = 0; }
    Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) { }
    float x,y,z;
    Vec3 operator-(const Vec3& b) const {return {this->x-b.x,this->y-b.y,this->z-b.z};}
    Vec3 operator*(float val) const {return {this->x*val,this->y*val,this->z*val};}
    Vec3 operator/(float val) const {return (*this)*(1.f/val);}
    float operator*(const Vec3& b) {return this->x*b.x+this->y*b.y+this->z*b.z;}
    Vec3 operator-() {return {-this->x,-this->y,-this->z};}
    void operator+=(const Vec3& b) {this->x+=b.x;this->y+=b.y;this->z+=b.z;}
};

/// @param radius : minimal radius between every samples. If radius <= 0
/// a new radius is approximated given the targeted number of samples
/// 'nb_samples'
/// @param nb_samples : ignored if radius > 0 otherwise will try to match
/// and find  nb_samples by finding an appropriate radius.
/// @param verts : list of vertices
/// @param nors : list of normlas coresponding to each verts[].
/// @param tris : triangle indices in verts[] array.
/// @code
///     tri(v0;v1;v3) = { verts[ tris[ith_tri*3 + 0] ],
///                       verts[ tris[ith_tri*3 + 1] ],
///                       verts[ tris[ith_tri*3 + 2] ]   }
/// @endcode
/// @param [out] samples_pos : resulting samples positions
/// @param [out] samples_nors : resulting samples normals associated to samples_pos[]
/// @warning undefined behavior if (radius <= 0 && nb_samples == 0) == true
void poisson_disk(float radius,
                  int nb_samples,
                  const std::vector<Vec3>& verts,
                  const std::vector<Vec3>& nors,
                  const std::vector<int>& tris,
                  std::vector<Vec3>& samples_pos,
                  std::vector<Vec3>& samples_nor);

}// END UTILS_SAMPLING NAMESPACE ===============================================
#endif