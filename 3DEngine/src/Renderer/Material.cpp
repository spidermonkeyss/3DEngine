#include "Material.h"
#include "GLCall.h"
#include "Scene.h"
#include "FileLoader.h"

unsigned int Material::nextId = 0;

void Material::CreateProperties()
{
	std::unordered_map<std::string, Shader::ShaderProperity>::iterator i;
	for (i = shader->uniforms.begin(); i != shader->uniforms.end(); ++i)
	{
		Shader::ShaderProperity* sp = &i->second;
		switch (sp->type)
		{
		case GL_SAMPLER_2D:
			textures[sp->name];
			break;
		case GL_INT:
			ints[sp->name];
			break;
		case GL_FLOAT:
			floats[sp->name];
			break;
		case GL_FLOAT_VEC2:
			float2s[sp->name];
			break;
		case GL_FLOAT_VEC3:
			float3s[sp->name];
			break;
		case GL_FLOAT_VEC4:
			float4s[sp->name];
			break;
		}
	}
}

void Material::ApplyMaterialToShader()
{
	for (std::unordered_map<std::string, Texture*>::iterator i = textures.begin(); i != textures.end(); ++i)
		shader->SetTexture(i->first, 0, i->second);
	
	for (std::unordered_map<std::string, int>::iterator i = ints.begin(); i != ints.end(); ++i)
		shader->SetUniform1i(i->first, i->second);
	
	for (std::unordered_map<std::string, float>::iterator i = floats.begin(); i != floats.end(); ++i)
		shader->SetUniform1f(i->first, i->second);
	
	for (std::unordered_map<std::string, float[2]>::iterator i = float2s.begin(); i != float2s.end(); ++i)
		shader->SetUniform2f(i->first, i->second[0], i->second[1]);
	
	for (std::unordered_map<std::string, float[3]>::iterator i = float3s.begin(); i != float3s.end(); ++i)
		shader->SetUniform3f(i->first, i->second[0], i->second[1], i->second[2]);
	
	for (std::unordered_map<std::string, float[4]>::iterator i = float4s.begin(); i != float4s.end(); ++i)
		shader->SetUniform4f(i->first, i->second[0], i->second[1], i->second[2], i->second[3]);
}

Material::Material()
	:isLoaded(false)
{
	id = nextId;
	nextId++;
}

Material* Material::CreateMaterial()
{
	return Scene::currentScene->CreateMaterial();
}

void Material::SetShader(Shader* _shader)
{
	if (_shader->isLoaded)
	{
		shader = _shader;
		CreateProperties();
	}
	else
	{
		std::cout << "WARNING: shader not loaded when trying to apply to material" << std::endl;
	}
}

void Material::SetShader(std::string _filePath)
{
	//if the shader is already loaded just set it the material
	bool foundShader = false;

	for (LinkedList<Shader>::Iterator i = Scene::currentScene->shaders.Begin(); i != Scene::currentScene->shaders.End(); ++i)
	{
		Shader* _shader = i.Data();
		if (_filePath == _shader->filePath)
		{
			foundShader = true;
			if (_shader->isLoaded)
			{
				shader = _shader;
				CreateProperties();
			}
			else
			{
				std::cout << "WARNING: shader " + _filePath << " not loaded when trying to apply to material" << std::endl;
			}
		}
	}

	if (!foundShader)
	{
		std::cout << "Loading shader at: " << _filePath << std::endl;
		shader = Shader::CreateShader();
		bool loaded = shader->LoadShaderFile(_filePath);
		if (loaded)
			CreateProperties();
		else
		{
			shader = nullptr;
			std::cout << "WARNING: no shader found by the name: " + _filePath << std::endl;
		}
	}
}

void Material::SetTexture(std::string uniformName, Texture* _texture)
{
	if (textures.find(uniformName) != textures.end())
		textures[uniformName] = _texture;
	else
		std::cout << "WARNING: no material properity called: " + uniformName << std::endl;
}

void Material::SetTexture(std::string uniformName, std::string textureFilePath)
{
	//if the texture is already loaded just set it the material
	bool foundTexture = false;

	for (LinkedList<Texture>::Iterator i = Scene::currentScene->textures.Begin(); i != Scene::currentScene->textures.End(); ++i)
	{
		Texture* _texture = i.Data();
		if (textureFilePath == _texture->filePath)
		{
			foundTexture = true;
			if (_texture->isLoaded)
			{
				SetTexture(uniformName, _texture);
			}
			else
			{
				std::cout << "WARNING: texture " + textureFilePath << " not loaded when trying to apply to material" << std::endl;
			}
		}
	}

	if (!foundTexture)
	{
		std::cout << "Loading texture at: " << textureFilePath << std::endl;
		Texture* _texture = Texture::CreateTexture();
		bool loaded = _texture->LoadTextureFile(textureFilePath);
		if (loaded)
		{
			SetTexture(uniformName, _texture);
		}
		else
		{
			std::cout << "WARNING: no texture found by the name: " + textureFilePath << std::endl;
		}
	}
}

void Material::SetInt(std::string uniformName, int value)
{
	if (ints.find(uniformName) != ints.end())
		ints[uniformName] = value;
	else
		std::cout << "WARNING: no material properity called: " + uniformName << std::endl;
}

void Material::SetFloat(std::string uniformName, float value)
{
	if (floats.find(uniformName) != floats.end())
		floats[uniformName] = value;
	else
		std::cout << "WARNING: no material properity called: " + uniformName << std::endl;
}

void Material::SetFloat2(std::string uniformName, float v1, float v2)
{
	if (float2s.find(uniformName) != float2s.end())
	{
		float2s[uniformName][0] = v1;
		float2s[uniformName][1] = v2;
	}
	else
		std::cout << "WARNING: no material properity called: " + uniformName << std::endl;
}

void Material::SetFloat3(std::string uniformName, float v1, float v2, float v3)
{
	if (float3s.find(uniformName) != float3s.end())
	{
		float3s[uniformName][0] = v1;
		float3s[uniformName][1] = v2;
		float3s[uniformName][2] = v3;
	}
	else
		std::cout << "WARNING: no material properity called: " + uniformName << std::endl;
}

void Material::SetFloat4(std::string uniformName, float v1, float v2, float v3, float v4)
{
	if (float4s.find(uniformName) != float4s.end())
	{
		float4s[uniformName][0] = v1;
		float4s[uniformName][1] = v2;
		float4s[uniformName][2] = v3;
		float4s[uniformName][3] = v4;
	}
	else
		std::cout << "WARNING: no material properity called: " + uniformName << std::endl;
}

bool Material::LoadMaterialFile(const std::string& _filePath)
{
	std::string extensionTypeStr = FileLoader::GetFileExtension(_filePath);

	if (extensionTypeStr == "bmat")
	{
		MaterialFileProperties mfp;
		bool loaded = FileLoader::Load_bmat_file(_filePath, &mfp);
		if (loaded)
		{
			isLoaded = true;
			filePath = _filePath;
			SetShader(mfp.shaderFilePath);
	
			for (int i = 0; i < mfp.textures.size(); i++)
				SetTexture(mfp.textures[i].propertyName, mfp.textures[i].filePath);
			for (int i = 0; i < mfp.ints.size(); i++)
				SetInt(mfp.ints[i].propertyName, mfp.ints[i].value);
			for (int i = 0; i < mfp.floats.size(); i++)
				SetFloat(mfp.floats[i].propertyName, mfp.floats[i].value);
			for (int i = 0; i < mfp.float2s.size(); i++)
				SetFloat2(mfp.float2s[i].propertyName, mfp.float2s[i].value[0], mfp.float2s[i].value[1]);
			for (int i = 0; i < mfp.float3s.size(); i++)
				SetFloat3(mfp.float3s[i].propertyName, mfp.float3s[i].value[0], mfp.float3s[i].value[1], mfp.float3s[i].value[2]);
			for (int i = 0; i < mfp.float4s.size(); i++)
				SetFloat4(mfp.float4s[i].propertyName, mfp.float4s[i].value[0], mfp.float4s[i].value[1], mfp.float4s[i].value[2], mfp.float4s[i].value[3]);
			
			return true;
		}
	}
	else
	{
		std::cout << "File extension not supported\n";
	}
	return false;
}
