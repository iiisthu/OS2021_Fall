##load("@rules_cc//cc:defs.bzl", "cc_test")  #load the test target

cc_library(
    name = "utils_lib",
    srcs = [
        "utils.cc",
        ],
    hdrs = [
        "utils.h",
        ],
	visibility = [
		"//visibility:public",
	],
)

cc_test(
  name = "utils_lib_test",
  size = "small",
  srcs = ["util_test.cc"],
  deps = [
      "@gtest//:gtest_main",
	  ":utils_lib",
      ],
)

cc_library(
    name = "resource_manager_lib",
    srcs = [
        "resource_manager.cc",
        ],
    hdrs = [
        "resource_manager.h",
        ],
	visibility = [
		"//visibility:public",
	],
)

cc_test(
  name = "resource_manager_lib_test",
  size = "small",
  srcs = ["resource_manager_test.cc"],
  deps = [
      "@gtest//:gtest_main",
	  ":resource_manager_lib",
      ],
)

cc_library(
    name = "workload_lib",
    srcs = [
        "workload.cc",
        ],
    hdrs = [
        "workload.h",
        ],
    deps = [
        ":resource_manager_lib",
        ":utils_lib",
    ],
	visibility = [
		"//visibility:public",
	],
)

cc_test(
  name = "workload_lib_test",
  size = "small",
  srcs = ["workload_test.cc"],
  deps = [
      "@gtest//:gtest_main",
	  ":workload_lib",
      ],
)
