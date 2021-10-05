##load("@rules_cc//cc:defs.bzl", "cc_test")  #load the test target

cc_binary(
    name = "q0",
    srcs = [
        "q0.cc"
            ],
    deps = [
        "//lib:embedding_lib",
        "//lib:instruction_lib",
        "//lib:utils_lib",
        "//lib:model_lib"
    ],
    copts = [
        "-std=c++11",
    ],
    data = glob(["data/q0*"]),
)

cc_binary(
    name = "format",
    srcs = [
        "format.cc"
            ],
)

cc_binary(
    name = "q1",
    srcs = [
        "q1.cc"
            ],
)

cc_binary(
    name = "q2",
    srcs = [
        "q2.cc"
            ],
)

cc_binary(
    name = "q3",
    srcs = [
        "q3.cc"
            ],
)

cc_test(
  name = "benchmark",
  size = "small",
  srcs = ["benchmark.cc"],
  deps = [
      "@gbench//:benchmark",
      ],
  copts = [
        "-O3",
        "-std=c++11",
  ],
  data = glob(["data/*"]),
)