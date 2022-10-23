#pragma once
#include "Types.h"

namespace Igalima
{
	class Application
	{
	public:
		Application() = default;
		Application(const Application&) = default;
		Application(Application&&) noexcept = default;
		~Application() = default;

	public:
		Application& operator=(const Application&) = default;
		Application& operator=(Application&&) noexcept = default;

	};

	Pointer<Application> CreateApplication();
}
