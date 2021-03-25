#include <windows.h>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <cstdlib>
#include <string>
#include <iostream>
#pragma comment(lib, "mono-2.0-sgen.lib")

#define MONO_HOME "C:\\Program Files\\Mono"

int main(int argc, char* argv[])
{
#pragma region Load and compile the script
    std::cout << "hello" << std::endl;
    std::string scriptPath(R"(Dog.cs)");
    std::string command = "\"" MONO_HOME "/bin/mcs\" " + scriptPath + " -target:library";

    //Compile the script
    system(command.c_str());
#pragma endregion

//#pragma region Init mono runtime
    mono_set_dirs(MONO_HOME "/lib",
        MONO_HOME "/etc");

    //Init a domain
    MonoDomain *domain;
    domain = mono_jit_init("MonoScriptTry");
    if (!domain)
    {
        std::cout << "mono_jit_init failed" << std::endl;
//        system("pause");
        return 1;
    }


    //Open a assembly in the domain
    MonoAssembly *assembly;
    char* assemblyPath = "Dog.dll";
    assembly = mono_domain_assembly_open(domain, assemblyPath);
    if (!assembly)
    {
        std::cout << "mono_domain_assembly_open failed" << std::endl;
//        system("pause");
        return 1;
    }

    //Get a image from the assembly
    MonoImage* image;
    image = mono_assembly_get_image(assembly);
    if (!image)
    {
        std::cout << "mono_assembly_get_image failed" << std::endl;
//        system("pause");
        return 1;
    }
#pragma endregion

#pragma region Run a static method
    {
        //Build a method description object
        MonoMethodDesc* TypeMethodDesc;
        char* TypeMethodDescStr = "Dog:Type()";
        TypeMethodDesc = mono_method_desc_new(TypeMethodDescStr, NULL);
        if (!TypeMethodDesc)
        {
            std::cout << "mono_method_desc_new failed" << std::endl;
//            system("pause");
            return 1;
        }

        //Search the method in the image
        MonoMethod* method;
        method = mono_method_desc_search_in_image(TypeMethodDesc, image);
        if (!method)
        {
            std::cout << "mono_method_desc_search_in_image failed" << std::endl;
//            system("pause");
            return 1;
        }

        //run the method
        std::cout << "Running the static method: " << TypeMethodDescStr << std::endl;
        mono_runtime_invoke(method, nullptr, nullptr, nullptr);
    }
#pragma endregion

#pragma region Run a normal method
    {
        //Get the class
        MonoClass* dogclass;
        dogclass = mono_class_from_name(image, "", "Dog");
        if (!dogclass)
        {
            std::cout << "mono_class_from_name failed" << std::endl;
//            system("pause");
            return 1;
        }

        //Create a instance of the class
        MonoObject* dogA;
        dogA = mono_object_new(domain, dogclass);
        if (!dogclass)
        {
            std::cout << "mono_object_new failed" << std::endl;
//            system("pause");
            return 1;
        }

        //Call its default constructor
        mono_runtime_object_init(dogA);

        //Build a method description object
        MonoObject* result;
        MonoMethodDesc* BarkMethodDesc;
        char* BarkMethodDescStr = "Dog:Bark(int)";
        BarkMethodDesc = mono_method_desc_new(BarkMethodDescStr, NULL);
        if (!BarkMethodDesc)
        {
            std::cout << "mono_method_desc_new failed" << std::endl;
//            system("pause");
            return 1;
        }

        //Search the method in the image
        MonoMethod* method;
        method = mono_method_desc_search_in_image(BarkMethodDesc, image);
        if (!method)
        {
            std::cout << "mono_method_desc_search_in_image failed" << std::endl;
//            system("pause");
            return 1;
        }

        //Set the arguments for the method
        void* args[1];
        int barkTimes = 3;
        args[0] = &barkTimes;

        //Run the method
        std::cout << "Running the method: " << BarkMethodDescStr << std::endl;
        mono_runtime_invoke(method, dogA, args, nullptr);
    }
#pragma endregion

//    system("pause");
    return 0;
}