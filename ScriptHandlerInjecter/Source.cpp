#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <filesystem>

std::string GetFileExtension(const std::string& filePath)
{
    int fileExtensionDotIndex = filePath.find_last_of('.');

    if (fileExtensionDotIndex == -1)
    {
        std::cout << "File name has no extension. No extension found\n";
        return "";
    }

    if (fileExtensionDotIndex == filePath.size() - 1)
    {
        std::cout << "File name ends with dot. No extension found\n";
        return "";
    }

    return filePath.substr(fileExtensionDotIndex + 1, filePath.size() - 1);
}

std::string GetFileName(const std::string& filePath)
{
    int fileExtensionDotIndex = filePath.find_last_of('.');
    int fileBackSlashIndex = filePath.find_last_of('/');

    if (fileExtensionDotIndex == -1)
    {
        std::cout << "File name has no extension. No extension found\n";
        return "";
    }

    if (fileExtensionDotIndex == filePath.size() - 1)
    {
        std::cout << "File name ends with dot. No extension found\n";
        return "";
    }

    if (fileBackSlashIndex == -1)
    {
        return filePath.substr(0, fileExtensionDotIndex);
    }
    else
    {
        return filePath.substr(fileBackSlashIndex + 1, fileExtensionDotIndex - fileBackSlashIndex - 1);
    }
}

int main(void)
{
    std::string path = "../3DEngine/res/scripts";
    std::string scriptHandlerStr = "";
    scriptHandlerStr += "#pragma once\n"
                        "#include \"Component/Script.h\"\n"
                        "\n"
                        "#include <unordered_map>\n"
                        "#include <iostream>\n"
                        "\n";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::string filePath = entry.path().generic_string();
        if (GetFileExtension(filePath) == "h")
        {
            std::string fileName = GetFileName(filePath);
            scriptHandlerStr += "#include \"../res/scripts/" + fileName + ".h\"\n";
        }
    }

    scriptHandlerStr += "class ScriptHandler\n"
                        "{\n"
                        "private:\n"
                        "   template<typename T> T* AddScript(unsigned int objectId, GameObject* _gameobject)\n"
                        "   {\n"
                        "       std::cout << typeid(T).name() << \" is not a script\" << std::endl;\n"
                        "   }\n"
                        "   template<typename T> void RemoveScript(unsigned int objectId)\n"
                        "   {\n"
                        "       std::cout << typeid(T).name() << \" is not a script\" << std::endl;\n"
                        "   }\n"
                        "   template<typename T> T* GetScript(unsigned int objectId)\n"
                        "   {\n"
                        "       std::cout << typeid(T).name() << \" is not a script\" << std::endl;\n"
                        "       return nullptr;\n"
                        "   }\n"
                        "   template<typename T> T* GetScriptUnSafe(unsigned int objectId)\n"
                        "   {\n"
                        "       std::cout << typeid(T).name() << \" is not a script\" << std::endl;\n"
                        "       return nullptr;\n"
                        "   }\n"
                        "\n"
                        "   friend class Scene;\n"
                        "   friend class GameObject;\n"
                        "\n";

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::string filePath = entry.path().generic_string();
        if (GetFileExtension(filePath) == "h")
        {
            std::string fileName = GetFileName(filePath);
            scriptHandlerStr += "   std::unordered_map<unsigned int, " + fileName + "> " + fileName + "_map;\n"
                                "   template<> " + fileName + "* AddScript<" + fileName + ">(unsigned int objectId, GameObject* _gameobject)\n"
                                "   {\n"
                                "       " + fileName + "* comp = &" + fileName + "_map[objectId];\n"
                                "       comp->componentGameObjectId = objectId;\n"
                                "       comp->gameobject = _gameobject;\n"
                                "       return comp;\n"
                                "   }\n"
                                "   template<> void RemoveScript<" + fileName + ">(unsigned int objectId)\n"
                                "   {\n"
                                "       " + fileName + "_map.erase(objectId);\n"
                                "   }\n"
                                "   template<> " + fileName + "* GetScript<" + fileName + ">(unsigned int objectId)\n"
                                "   {\n"
                                "       if (" + fileName + "_map.count(objectId) == 1)\n"
                                "           return &" + fileName + "_map[objectId];\n"
                                "       return nullptr;\n"
                                "   }\n"
                                "   template<> " + fileName + "* GetScriptUnSafe<" + fileName + ">(unsigned int objectId)\n"
                                "   {\n"
                                "       return &" + fileName + "_map[objectId];\n"
                                "   }\n";
        }
    }

    scriptHandlerStr += "   void CallScriptUpdates()\n"
                        "   {\n";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::string filePath = entry.path().generic_string();
        if (GetFileExtension(filePath) == "h")
        {
            std::string fileName = GetFileName(filePath);
            scriptHandlerStr += "       std::unordered_map<unsigned int, " + fileName + ">::iterator " + fileName + "_ittr;\n"
                                "       for (" + fileName + "_ittr = " + fileName + "_map.begin(); " + fileName + "_ittr != " + fileName + "_map.end(); ++" + fileName + "_ittr)\n"
                                "       {\n"
                                "           if (" + fileName + "_ittr->second.isEnabled)\n"
                                "               " + fileName + "_ittr->second.Update();\n"
                                "       }\n";
        }
    }
    scriptHandlerStr += "   }\n";

    scriptHandlerStr += "   void StartScripts()\n"
        "   {\n";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::string filePath = entry.path().generic_string();
        if (GetFileExtension(filePath) == "h")
        {
            std::string fileName = GetFileName(filePath);
            scriptHandlerStr += "       std::unordered_map<unsigned int, " + fileName + ">::iterator " + fileName + "_ittr;\n"
                "       for (" + fileName + "_ittr = " + fileName + "_map.begin(); " + fileName + "_ittr != " + fileName + "_map.end(); ++" + fileName + "_ittr)\n"
                "       {\n"
                "           if (" + fileName + "_ittr->second.isEnabled)\n"
                "               " + fileName + "_ittr->second.OnStart();\n"
                "       }\n";
        }
    }
    scriptHandlerStr += "   }\n";
    
    scriptHandlerStr += "};";

    std::string fileToWritePath = "../3DEngine/src/ScriptHandler_Injected.h";
    std::ofstream stream(fileToWritePath);
    stream << scriptHandlerStr;
}