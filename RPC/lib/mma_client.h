#ifndef MMA_CLIENT_H
#define MMA_CLIENT_H

#include <memory>
#include <cstdlib>

#include <grpc++/grpc++.h>

#ifdef BAZEL_BUILD
#include "proto/mma.grpc.pb.h"
#else
#include "mma.grpc.pb.h"
#endif


namespace proj4 {

class ArrayList;

class MmaClient {
};

} //namespace proj4

#endif