#ifndef APPLICATION_H
#define APPLICATION_H

#include "defines.h"

#include "AWindow.h"

namespace Starlight
{
	class STARLIGHT_API Application
	{
	public:
		SL_SINGLE_CLASS(Application);

		static bool Init() noexcept;

		static void SetCurrentContext(AWindow* context);

		static void Start();
		static void Update();

		static void Shutdown() noexcept;

		~Application() = default;
	private:
		Application() = default;
		static Application s_Instance;

		AWindow* m_CurrentContext = nullptr;
		bool m_Inited = false;
	};
}

#endif // !APPLICATION_H
