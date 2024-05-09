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


    int numActiveAttribs = 0;
    int numActiveUniforms = 0;
    GLCall(glGetProgramInterfaceiv(gl_ShaderId, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs));
    GLCall(glGetProgramInterfaceiv(gl_ShaderId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms));

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)
    const GLsizei bufSize = 16; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    for (int i = 0; i < numActiveAttribs; i++)
    {
        glGetActiveAttrib(gl_ShaderId, (GLuint)i, bufSize, &length, &size, &type, name);
        ShaderProperity sp;
        sp.location = i;
        sp.name = name;
        sp.type = type;
        attributies[name] = sp;
    }

    for (int i = 0; i < numActiveUniforms; i++)
    {
        glGetActiveUniform(gl_ShaderId, (GLuint)i, bufSize, &length, &size, &type, name);
        ShaderProperity sp;
        sp.location = i;
        sp.name = name;
        sp.type = type;
        uniforms[name] = sp;
    }
}

bool Shader::LoadShaderFile(const std::string& filePath)
{
    std::string extensionTypeStr = FileLoader::GetFileExtension(filePath);

    if (extensionTypeStr == "shader")
    {
        std::vector<std::string> shaderStrings = FileLoader::LoadShaderFile(filePath);

        if (shaderStrings.size() != 0)
        {
            LoadGlShader(shaderStrings[0], shaderStrings[1]);
            return true;
        }
    }
    else
    {
        std::cout << "File extension not supported\n";
    }
    return false;
}

void Shader::SetMVP(const std::string& mvpUniformName, const float* mvp)
{
    SetUniformMat4(mvpUniformName, mvp);
}

bool Shader::SetTexture(const std::string& name, int slot, Texture* texture)
{
    Bind();
    int result = GetUniformLocation(name);
    if (result == -1)
        return false;

    texture->Bind(slot);
    GLCall(glUniform1i(result, slot));
    return true;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));

}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform2f(const std::string& name, float v1, float v2)
{
    GLCall(glUniform2f(GetUniformLocation(name), v1, v2));
}

void Shader::SetUniform3f(const std::string& name, float v1, float v2, float v3)
{
    GLCall(glUniform3f(GetUniformLocation(name), v1, v2, v3));
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}

void Shader::SetUniformMat4(const std::string& name, const float* mat4)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, mat4);
}

Shader::~Shader()
{
    //GLCall(glDeleteProgram(gl_ShaderId));
}

void Shader::Bind()
{
    GLCall(glUseProgram(gl_ShaderId));
}

int Shader::GetAttributeLocation(const std::string& name)
{
    if (attributies.find(name) != attributies.end())
        return attributies[name].location;
    else
    {
        std::cout << "Warning: " << name << " attributie not found\n";
        return -1;
    }
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (uniforms.find(name) != uniforms.end())
        return uniforms[name].location;
    else
    {
        std::cout << "Warning: " << name << " uniform not found\n";
        return -1;
    }
}
