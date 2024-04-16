#include "Shader.h"
#include "GLCall.h"

void Shader::LoadGlShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    const char* vertexShaderChar = vertexShader.c_str();
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertex_shader_id, 1, &vertexShaderChar, NULL));
    GLCall(glCompileShader(vertex_shader_id));
    int result;
    GLCall(glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
        std::cout << "Vertex Shader error\n";

    const char* fragmentShaderChar = fragmentShader.c_str();
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragment_shader_id, 1, &fragmentShaderChar, NULL));
    GLCall(glCompileShader(fragment_shader_id));
    GLCall(glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
        std::cout << "Fragment Shader error\n";

    gl_ShaderId = glCreateProgram();
    GLCall(glAttachShader(gl_ShaderId, vertex_shader_id));
    GLCall(glAttachShader(gl_ShaderId, fragment_shader_id));
    GLCall(glLinkProgram(gl_ShaderId));
    GLCall(glValidateProgram(gl_ShaderId));

    GLCall(glDeleteShader(vertex_shader_id));
    GLCall(glDeleteShader(fragment_shader_id));

    mvp_location = glGetUniformLocation(gl_ShaderId, "MVP");
}

void Shader::LoadShaderFile(const std::string& filePath)
{
    std::string extensionTypeStr = FileLoader::GetFileExtension(filePath);

    if (extensionTypeStr == "shader")
    {
        std::vector<std::string> shaderStrings = FileLoader::LoadShaderFile(filePath);

        if (shaderStrings.size() != 0)
        {
            LoadGlShader(shaderStrings[0], shaderStrings[1]);
        }
    }
    else
    {
        std::cout << "File extension not supported\n";
    }
}

void Shader::SetMVP(const float* mvp)
{
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, mvp);
}

Shader::~Shader()
{
    //GLCall(glDeleteProgram(gl_ShaderId));
}

void Shader::Bind()
{
    GLCall(glUseProgram(gl_ShaderId));
}