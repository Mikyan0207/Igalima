#pragma once

#include <Application.h>
#include <cstdlib>

extern Pointer<Igalima::Application> Igalima::CreateApplication();

int main(int argc, char** argv)
{
	const auto engine = Igalima::CreateApplication();

	system("pause");

	delete engine;
}
