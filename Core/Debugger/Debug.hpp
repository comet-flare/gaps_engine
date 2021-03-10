#pragma once

namespace gaps
{
	class Debug final
	{
	public:
		static void Enable();
		static void Disable() noexcept;

		static void Info(const std::string& msg, const std::string& mod = "");
		static void Warn(const std::string& msg, const std::string& mod = "");
		static void Crit(const std::string& msg, const std::string& mod = "");
		static void Todo(const std::string& msg, const std::string& mod = "");

		static void Log(const std::string& msg);

		static bool IsEnabled() noexcept;

		inline static bool bDisableWriteToConsole = false;
		inline static bool bDisableWriteToFile = false;

	private:
		static void WriteText(const std::string& text);

		inline static std::string enableStartTime = "";
		inline static bool bEnabled = false;
	};
}

#define MOD(NAME) static std::string modName = (NAME)
#define DEBUG_INFO(MSG) gaps::Debug::Info((MSG), modName)
#define DEBUG_WARN(MSG) gaps::Debug::Warn((MSG), modName)
#define DEBUG_CRIT(MSG) gaps::Debug::Crit((MSG), modName)
#define DEBUG_TODO(MSG) gaps::Debug::Todo((MSG), modName)