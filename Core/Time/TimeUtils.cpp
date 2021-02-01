#include <gapspch.hpp>
#include <Core/Time/TimeUtils.hpp>

namespace gaps
{
	std::string TimeUtils::GetCurrentTimeAndDate()
	{
		time_t t0 = time(0);
		char str[26];
		ctime_s(str, sizeof(str), &t0);
		std::string res = std::string(str);
		res.pop_back();
		return res;
	}
}