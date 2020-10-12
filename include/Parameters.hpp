#pragma once

#include <CppUtils.hpp>

#include <config.hpp>

namespace Script
{
	struct Settings
	{
		enum class Mode
		{
			Dev,
			Test,
			Prod
		};

		Settings() = default;
		explicit Settings(const Mode& mode)
		{
			if (mode == Mode::Test)
			{
				verbose = true;
				chrono = true;
			}
			else if (mode == Mode::Prod)
				warning = false;
		}

		std::string filename = "main.script";
		bool verbose = false;
		bool warning = true;
		bool chrono = false;
		bool abort = false;
	};

	[[nodiscard]] Settings executeCommands(const int argc, const char *argv[])
	{
		auto settings = Settings{Settings::Mode::Dev};
		
		settings.abort = CppUtils::Terminal::Parameters::executeCommands(argc, argv, {
			{
				"help",
				[]([[maybe_unused]] auto value) -> bool {
					CppUtils::Log::Logger::logImportant("The parameters available are:\n- help\n- file[filename]\n- info\n- version\n- signature\n- verbose\n- no-warning\n- chrono\n\nUsage: ./"s + EXECUTABLE_NAME + " file[main.script] warning");
					return true;
				}
			},
			{
				"info",
				[]([[maybe_unused]] auto value) -> bool {
					CppUtils::Log::Logger::logImportant(EXECUTABLE_DESCRIPTION + "\nVersion: "s + EXECUTABLE_VERSION + "\nLicense: " + EXECUTABLE_LICENSE + "\nAuthor: " + EXECUTABLE_COMPANY_NAME + "\n" + EXECUTABLE_COMMENT);
					return true;
				}
			},
			{
				"version",
				[]([[maybe_unused]] auto value) -> bool {
					CppUtils::Log::Logger::logImportant("Version: "s + EXECUTABLE_VERSION);
					return true;
				}
			},
			{
				"file",
				[&settings](auto value) -> bool {
					settings.filename = (!value.empty()) ? value : "main.script";
					return false;
				}
			},
			{
				"signature",
				[&settings]([[maybe_unused]] auto value) -> bool {
					const auto src = CppUtils::FileSystem::File::String::read(settings.filename);
					const auto signature = std::to_string(CppUtils::Hash::constexprHash(src));
					CppUtils::Log::Logger::logImportant("Signature: "s + signature);
					return true;
				}
			},
			{
				"verbose",
				[&settings]([[maybe_unused]] auto value) -> bool {
					settings.verbose = true;
					return false;
				}
			},
			{
				"no-warning",
				[&settings]([[maybe_unused]] auto value) -> bool {
					settings.warning = false;
					return false;
				}
			},
			{
				"chrono",
				[&settings]([[maybe_unused]] auto value) -> bool {
					settings.chrono = true;
					return false;
				}
			}
		});

		return settings;
	}
}
