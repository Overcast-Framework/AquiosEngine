#pragma once
#ifdef AQ_PLATFORM_WINDOWS
	#ifdef AQUIOSENGINE_EXPORTS
		#define AQUIOS_API __declspec(dllexport)
	#else
		#define AQUIOS_API __declspec(dllimport)
	#endif
#else
	#error AquiosEngine only supports Windows devices!
#endif

#ifdef DEBUG
	#define AQ_ENABLE_ASSERTS
#endif

#ifdef AQ_ENABLE_ASSERTS
	#define AQ_ASSERT(x, ...) { if(!(x)){ AQ_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define AQ_CORE_ASSERT(x, ...) { if(!(x)){ AQ_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define AQ_ASSERT(x, ...)
	#define AQ_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x)