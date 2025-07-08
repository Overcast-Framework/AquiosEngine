#pragma once
#include <AquiosEngine/Core.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Aquios
{
	class AQUIOS_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// CORE LOGGING MACROS
#define AQ_CORE_WARN(...)     ::Aquios::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AQ_CORE_ERROR(...)    ::Aquios::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AQ_CORE_FATAL(...)    ::Aquios::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define AQ_CORE_INFO(...)     ::Aquios::Log::GetCoreLogger()->info(__VA_ARGS__) 
#define AQ_CORE_TRACE(...)    ::Aquios::Log::GetCoreLogger()->trace(__VA_ARGS__)

// CLIENT LOGGING MACROS
#define AQ_WARN(...)	      ::Aquios::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AQ_ERROR(...)         ::Aquios::Log::GetClientLogger()->error(__VA_ARGS__)
#define AQ_FATAL(...)         ::Aquios::Log::GetClientLogger()->critical(__VA_ARGS__)
#define AQ_INFO(...)          ::Aquios::Log::GetClientLogger()->info(__VA_ARGS__) 
#define AQ_TRACE(...)         ::Aquios::Log::GetClientLogger()->trace(__VA_ARGS__)