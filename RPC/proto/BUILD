package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")



cc_grpc_library(
    name = "mma_grpc",
    srcs = [":mma_proto"],
    grpc_only = True,
    deps = [":mma_cc_proto"],
)
 
cc_proto_library(
    name = "mma_cc_proto",
    deps = [":mma_proto"],
)
 
proto_library(
    name = "mma_proto",
	srcs = ["mma.proto"],
)