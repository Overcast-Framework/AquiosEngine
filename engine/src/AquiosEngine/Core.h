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