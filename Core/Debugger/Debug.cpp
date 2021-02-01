#include <gapspch.hpp>
#include <Core/Debugger/Debug.hpp>
#include <Core/Time/TimeUtils.hpp>

namespace gaps
{
	void Debug::Enable()
	{
		if (!bEnabled)
		{
			enableStartTime = TimeUtils::GetCurrentTimeAndDate();

			for (auto& c : enableStartTime)
			{
				if (c == ':')
				{
					c = '-';
				}
			}

			bEnabled = true;
		}
	}

	void Debug::Disable() noexcept
	{
		bEnabled = false;
	}

	void Debug::Info(const std::string& msg, const std::string& mod)
	{
		if (bEnabled)
		{
			std::string text = "[INFO-"
				+ TimeUtils::GetCurrentTimeAndDate()
				+ "-" + mod + "]: \"" + msg + "\"\n";

			WriteText(std::move(text));
		}
	}

	void Debug::Warn(const std::string& msg, const std::string& mod)
	{
		if (bEnabled)
		{
			std::string text = "[WARN-"
				+ TimeUtils::GetCurrentTimeAndDate()
				+ "-" + mod + "]: \"" + msg + "\"\n";

			WriteText(std::move(text));
		}
	}

	void Debug::Crit(const std::string& msg, const std::string& mod)
	{
		if (bEnabled)
		{
			std::string text = "[CRIT-"
				+ TimeUtils::GetCurrentTimeAndDate()
				+ "-" + mod + "]: \"" + msg + "\"\n";

			WriteText(std::move(text));
		}
	}

	void Debug::Todo(const std::string& msg, const std::string& mod)
	{
		if (bEnabled)
		{
			std::string text = "[TODO-"
				+ TimeUtils::GetCurrentTimeAndDate()
				+ "-" + mod + "]: \"" + msg + "\"\n";

			WriteText(std::move(text));
		}
	}

	void Debug::Log(const std::string& msg)
	{
		if (bEnabled)
		{
			std::string text = "\"" + msg + "\"" + "\n";

			WriteText(std::move(text));
		}
	}

	bool Debug::IsEnabled() noexcept
	{
		return bEnabled;
	}

	void Debug::WriteText(std::string text)
	{
		if (!bDisableWriteToConsole)
		{
			std::cout << text;
		}

		if (!bDisableWriteToFile)
		{
			std::fstream f;
			std::string fileName = "Logs\\Log_" + enableStartTime + ".txt";

			if (!std::filesystem::is_directory("Logs"))
			{
				std::filesystem::create_directory("Logs");
			}

			f.open(fileName.c_str(), std::ios::app | std::ios::binary);
			f << text;
			f.close();
		}
	}
}