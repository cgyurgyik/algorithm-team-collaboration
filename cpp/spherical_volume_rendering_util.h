#ifndef SPHERICAL_VOLUME_RENDERING_SPHERICALVOLUMERENDERINGUTIL_H
#define SPHERICAL_VOLUME_RENDERING_SPHERICALVOLUMERENDERINGUTIL_H

#include "ray.h"
#include "vec3.h"
#include "spherical_voxel_grid.h"
#include <vector>

namespace svr {

    // Represents a spherical voxel coordinate.
    struct SphericalVoxel {
        int radial_voxel;
        int angular_voxel;
        int azimuthal_voxel;
    };

    // Represents the boundary for the sphere.
    struct SphereBound {
        double radial;
        double angular;
        double azimuthal;
    };

    // A spherical coordinate voxel traversal algorithm. The algorithm traces the ray over the spherical voxel grid
    // provided. t_begin is the time the ray begins, and t_end is the time at which the ray ends. Returns a
    // vector of the spherical coordinate voxels traversed. Does not assume that the ray direction is normalized.
    // Recall that if, for example, a radial hit occurs, the azimuthal and angular voxels will remain the
    // same as before. This applies for each traversal type. The sphere bounds are used to determine the sector
    // of the sphere to be traversed.
    // For example, if one wants to traverse the entire sphere, then:
    // SphereBound min_bound = { .radial=0.0, .angular=0.0, .azimuthal=0.0 }
    // SphereBound max_bound = { .radial=SPHERE_MAX_RADIUS, .angular=2*M_PI, .azimuthal=2*M_PI }
    //
    // If instead one wants to traverse the upper hemisphere, then:
    // SphereBound min_bound = { .radial=0.0, .angular=0.0, .azimuthal=0.0 }
    // SphereBound max_bound = { .radial=SPHERE_MAX_RADIUS, .angular=2*M_PI, .azimuthal=M_PI }
    std::vector<SphericalVoxel> walkSphericalVolume(const Ray &ray, const svr::SphericalVoxelGrid &grid,
                                                    const svr::SphereBound &min_bound,
                                                    const svr::SphereBound &max_bound,
                                                    double t_begin, double t_end) noexcept;

    // Simplified parameters to Cythonize the function; implementation remains the same as above.
    std::vector<SphericalVoxel> walkSphericalVolume(double *ray_origin, double *ray_direction,
                                                    std::size_t num_radial_voxels,
                                                    std::size_t num_angular_voxels,
                                                    std::size_t num_azimuthal_voxels,
                                                    double *sphere_center, double sphere_max_radius,
                                                    double *min_bound, double *max_bound,
                                                    double t_begin, double t_end) noexcept;

} // namespace svr

#endif //SPHERICAL_VOLUME_RENDERING_SPHERICALVOLUMERENDERINGUTIL_H