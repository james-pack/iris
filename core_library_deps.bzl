load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def core_library_deps():
    if not native.existing_rule("com_google_googletest"):
        http_archive(
            name = "com_google_googletest",
            sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
            strip_prefix = "googletest-release-1.10.0",
            urls = [
                "https://github.com/google/googletest/archive/release-1.10.0.zip",
            ],
        )

    if not native.existing_rule("com_github_gflags_gflags"):
        http_archive(
            name = "com_github_gflags_gflags",
            sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
            strip_prefix = "gflags-2.2.2",
            urls = [
                "https://github.com/gflags/gflags/archive/v2.2.2.tar.gz",
            ],
        )

    if not native.existing_rule("com_github_google_glog"):
        http_archive(
            name = "com_github_google_glog",
            sha256 = "62efeb57ff70db9ea2129a16d0f908941e355d09d6d83c9f7b18557c0a7ab59e",
            strip_prefix = "glog-d516278b1cd33cd148e8989aec488b6049a4ca0b",
            urls = ["https://github.com/google/glog/archive/d516278b1cd33cd148e8989aec488b6049a4ca0b.zip"],
        )

    if not native.existing_rule("rules_proto"):
        http_archive(
            name = "rules_proto",
            sha256 = "66bfdf8782796239d3875d37e7de19b1d94301e8972b3cbd2446b332429b4df1",
            strip_prefix = "rules_proto-4.0.0",
            urls = [
                "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/refs/tags/4.0.0.tar.gz",
                "https://github.com/bazelbuild/rules_proto/archive/refs/tags/4.0.0.tar.gz",
            ],
        )

    if not native.existing_rule("com_google_absl"):
        http_archive(
            name = "com_google_absl",
            sha256 = "d468586a90059921b9e1eeee81fd88283a47dc3c699b01b9763e58c87d5a2401",
            strip_prefix = "abseil-cpp-c86347d4cec43074e64e225a8753728f4bfc5ed6",
            urls = ["https://github.com/abseil/abseil-cpp/archive/c86347d4cec43074e64e225a8753728f4bfc5ed6.zip"],
        )

    if not native.existing_rule("com_gitlab_libeigen_eigen"):
        http_archive(
            name = "com_gitlab_libeigen_eigen",
            sha256 = "8586084f71f9bde545ee7fa6d00288b264a2b7ac3607b974e54d13e7162c1c72",
            strip_prefix = "eigen-3.4.0",
            urls = [
                "https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz",
            ],
            build_file = "//third_party/eigen:eigen.BUILD",
        )
