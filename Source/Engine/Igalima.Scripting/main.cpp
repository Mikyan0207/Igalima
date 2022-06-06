#include "mono/jit/jit.h"
#include "mono/jit/mono-private-unstable.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/class.h"
#include <iostream>

int main()
{
    mono_set_dirs("D:\Projects\Igalima\Libraries\Mono\Debug", "C:\Program Files\Mono\etc");

    monovm_initialize(0, nullptr, nullptr);

    MonoDomain* domain = mono_jit_init("IgalimaDomain");

    if (!domain)
    {
        std::cout << "Failed to initialize domain" << std::endl;
        return 0;
    }

    MonoAssembly* assembly = mono_domain_assembly_open(domain, "D:\Projects\Igalima\x64\Debug\Igalima.Editor.exe");


    system("pause");

    return 0;
}
