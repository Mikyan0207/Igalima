#include <Windows.h>

#define STR(s) L##s
#define CH(c) L##c
#define DIR_SEPARATOR L'\\'

#include <string>
#include <iostream>
#include "hostfxr/hostfxr.h"
#include <cassert>

using string_t = std::basic_string<char_t>;


hostfxr_initialize_for_dotnet_command_line_fn hostfxr_initialize_for_dotnet_command_line = nullptr;
hostfxr_initialize_for_runtime_config_fn hostfxr_initialize_for_runtime_config = nullptr;
hostfxr_get_runtime_delegate_fn hostfxr_get_runtime_delegate = nullptr;
hostfxr_close_fn hostfxr_close = nullptr;

int main(int argc, char_t* argv[])
{
	std::string fxr_path = "C:\\Program Files\\dotnet\\host\\fxr\\6.0.9\\hostfxr.dll";

	auto dll = LoadLibraryA(fxr_path.c_str());
	hostfxr_initialize_for_runtime_config = (hostfxr_initialize_for_runtime_config_fn)GetProcAddress(dll, "hostfxr_initialize_for_runtime_config");
	hostfxr_get_runtime_delegate = (hostfxr_get_runtime_delegate_fn)GetProcAddress(dll, "hostfxr_get_runtime_delegate");
	hostfxr_close = (hostfxr_close_fn)GetProcAddress(dll, "hostfxr_close");

	char_t host_path[MAX_PATH];
	auto size = ::GetFullPathNameW(argv[0], sizeof(host_path) / sizeof(char_t), host_path, nullptr);
	assert(size != 0);

	string_t root_path = host_path;
	auto pos = root_path.find_last_of(DIR_SEPARATOR);
	assert(pos != string_t::npos);
	root_path = root_path.substr(0, pos + 1);
	const string_t config_path = root_path + STR("Igalima.Engine.runtimeconfig.json");

	hostfxr_handle ctx = nullptr;

	std::wcout << config_path.c_str() << std::endl;

	auto rc = hostfxr_initialize_for_runtime_config(config_path.c_str(), nullptr, &ctx);

	if (rc != 0 || ctx == nullptr)
	{
		std::cerr << "Init failed: " << std::hex << std::showbase << rc << std::endl;
		hostfxr_close(ctx);
	}

	return 0;
}