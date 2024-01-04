#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport) // TEST 
	#else	
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error HAZEL only support Window!
#endif

#define BIT(x) ( 1 << x )