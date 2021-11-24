##load("@rules_cc//cc:defs.bzl", "cc_test")  #load the test target

cc_test(
    name = "mma_test",
    size = "small",
    srcs = ["mma_test.cc"],
    deps = [
        "@gtest//:gtest_main",
        "//lib:utils_lib",
        "//lib:memory_manager_lib",
        ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
        "-pthread",
    ]
)