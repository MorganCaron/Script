set_project("Script")
set_version("0.0.0", {build = "%Y%m%d%H%M"})
set_license("LGPL3")
set_languages("clatest", "cxxlatest")
set_warnings("allextra", "pedantic", "error")
add_cxflags("-Wconversion -Wfatal-errors")
add_cxflags("clang::-Wno-deprecated-declarations")
add_cxflags("clang::-fcolor-diagnostics", "clang::-fansi-escape-codes", "gcc::-fdiagnostics-color=always")
-- add_cxflags("-Wno-gnu-statement-expression-from-macro-expansion -Wno-gnu-statement-expression", {tools = { "clang", "gcc" })
set_optimize("fastest")

add_cxxflags("clang::-fexperimental-library", {force = true}) -- Pour avoir std::jthread
add_cxxflags("cl::/EHsc", {force = true}) -- Pour avoir std::jthread

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

option("enable_tests")
option("local_CppUtils")

package("CppUtils", function()
	set_kind("library")

	if get_config("local_CppUtils") then
		set_sourcedir("../CppUtils")
		else
		add_urls("https://github.com/MorganCaron/CppUtils.git")
	end

	on_install("*", function(package)
		import("package.tools.xmake").install(package)
	end)
end)

add_requires("CppUtils")

target("Script", function()
	set_kind("binary")
	
	if is_plat("windows") and is_config("cxx", "cl") and not is_plat("mingw") then
		set_runtimes(is_mode("debug") and "MDd" or "MD")
		add_defines("NOMINMAX", "VC_EXTRALEAN", "WIN32_LEAN_AND_MEAN", { public = true })
		add_cxflags("/wd4251", {force = true}) -- ‘identifier’ : class ‘type’ needs to have dll-interface to be used by clients of class ‘type2’
	elseif is_plat("linux", "macosx") then
		add_syslinks("pthread", "dl")
	end

	add_packages("CppUtils")

	set_policy("build.merge_archive", true)
	set_policy("build.c++.modules", true)
	add_files("modules/**.mpp", { public = true })
end)

if has_config("enable_tests") then
	includes("tests")
end
