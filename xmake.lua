set_project("Script")
set_version("0.0.0", {build = "%Y%m%d%H%M"})
set_license("LGPL3")
set_languages("clatest", "cxxlatest")
set_warnings("allextra", "pedantic", "error")
set_policy("check.auto_ignore_flags", false)
add_cxflags("-Wconversion -Wfatal-errors", {force = true})
add_cxflags("clang::-Wno-deprecated-declarations -Wno-unknown-attributes")
add_cxflags("clang::-fcolor-diagnostics", "clang::-fansi-escape-codes", "gcc::-fdiagnostics-color=always")
-- add_cxflags("-Wno-gnu-statement-expression-from-macro-expansion -Wno-gnu-statement-expression", {tools = { "clang", "gcc" })
set_optimize("fastest")

add_cxxflags("clang::-fexperimental-library", {force = true}) -- Pour avoir std::jthread
add_cxxflags("cl::/EHsc", {force = true}) -- Pour avoir std::jthread

if is_plat("windows") and is_config("cxx", "cl") and not is_plat("mingw") then
	set_runtimes(is_mode("debug") and "MDd" or "MD")
	add_defines("NOMINMAX", "VC_EXTRALEAN", "WIN32_LEAN_AND_MEAN", { public = true })
	add_cxflags("/wd4251", {force = true}) -- ‘identifier’ : class ‘type’ needs to have dll-interface to be used by clients of class ‘type2’
elseif is_plat("linux", "macosx") then
	add_syslinks("pthread", "dl")
end

add_rules(
	"mode.debug",
	"mode.release",
	"mode.releasedbg",
	"mode.minsizerel",
	"mode.check",
	"mode.profile",
	"mode.coverage",
	"mode.valgrind",
	"mode.asan",
	"mode.tsan",
	"mode.lsan",
	"mode.ubsan")

add_repositories("xmake-repo git@github.com:MorganCaron/xmake-repo.git")
add_requires("CppUtils")

target("Script", function()
	set_kind("moduleonly")

	add_packages("CppUtils", {public = true})

	add_files("modules/**.mpp", { public = true })
end)

target("Script-Executable", function()
	set_kind("binary")
	add_deps("Script")
	add_files("src/main.cpp")
end)

option("enable_tests")

if has_config("enable_tests") then
	includes("tests")
end
