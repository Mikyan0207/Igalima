#include "EditorApplication.h"

#include <Application.h>
#include <EntryPoint.h>

namespace Igalima
{
	[[nodiscard]]
    Pointer<Application> CreateApplication()
	{
		return CreatePointer<Editor::EditorApplication>();
	}
}