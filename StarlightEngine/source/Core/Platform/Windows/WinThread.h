#ifndef WIN_THREAD_H
#define WIN_THREAD_H

#include <Windows.h>

#ifdef _WIN32
#define PLATFORM_API WINAPI
#else
#define PLATFORM_API 
#endif // _WIN32

namespace Starlight
{
	namespace Windows
	{
		class WinThread
		{
		public:
			WinThread(LPTHREAD_START_ROUTINE routine, void* params, LPSECURITY_ATTRIBUTES attributes);

			void Resume() noexcept;
			void Suspend() noexcept;
			void WaitTillEnd() noexcept;

			~WinThread();
		private:
			HANDLE m_Handle;
			DWORD m_Id;
		};
	}
}


#endif // !WIN_THREAD_H
