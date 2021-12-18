##load("@rules_cc//cc:defs.bzl", "cc_test")  #load the test target


cc_test(
    name = "mma_test",
    size = "small",
    srcs = ["mma_test.cc"],
    deps = [
        "@gtest//:gtest_main",
        "@com_github_grpc_grpc//:grpc++",
        "//lib:mma_client_lib",
        "//lib:mma_server_lib",
        ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
        "-pthread",
    ]
)