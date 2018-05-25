
#pragma once


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4127) // 定数条件式
#endif


// Eigen
#define EIGEN_NO_DEBUG 1
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/StdVector>


#if defined(_MSC_VER)
#pragma warning(pop)
#endif

