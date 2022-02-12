#include "WinThread.h"

#include "Core/Log.h"

namespace Starlight
{
	namespace Windows
	{
		WinThread::WinThread(LPTHREAD_START_ROUTINE routine, void* params, LPSECURITY_ATTRIBUTES attributes)
		{
			m_Handle = CreateThread(attributes, 0, routine, params, 0, &m_Id);
			
			if (m_Handle == nullptr)
			{
				SL_FATAL("Thread isn\'t created!");
			}
		}

		void WinThread::Resume() noexcept
		{
			ResumeThread(m_Handle);
		}

		void WinThread::Suspend() noexcept
		{
			SuspendThread(m_Handle);
		}

		void WinThread::WaitTillEnd() noexcept
		{
			WaitForSingleObject(m_Handle, INFINITE);
		}
		
		WinThread::~WinThread()
		{
			CloseHandle(m_Handle);
		}
	}
}