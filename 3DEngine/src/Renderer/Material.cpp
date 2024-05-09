#include "Material.h"

void Material::ApplyMaterialToShader()
{
	{
		std::unordered_map<std::string, Texture*>::iterator i;
		for (i = textures.begin(); i != textures.end(); ++i)
			shader->SetTexture(i->first, 0, i->second);
	}

	{
		std::unordered_map<std::string, int>::iterator i;
		for (i = ints.begin(); i != ints.end(); ++i)
			shader->SetUniform1i(i->first, i->second);
	}

	{
		std::unordered_map<std::string, float>::iterator i;
		for (i = floats.begin(); i != floats.end(); ++i)
			shader->SetUniform1f(i->first, i->second);
	}

	{
		std::unordered_map<std::string, float[2]>::iterator i;
		for (i = float2s.begin(); i != float2s.end(); ++i)
			shader->SetUniform2f(i->first, i->second[0], i->second[1]);
	}

	{
		std::unordered_map<std::string, float[3]>::iterator i;
		for (i = float3s.begin(); i != float3s.end(); ++i)
			shader->SetUniform3f(i->first, i->second[0], i->second[1], i->second[2]);
	}

	{
		std::unordered_map<std::string, float[4]>::iterator i;
		for (i = float4s.begin(); i != float4s.end(); ++i)
			shader->SetUniform4f(i->first, i->second[0], i->second[1], i->second[2], i->second[3]);
	}
}

void Material::SetShader(Shader* _shader)
{
	shader = _shader;
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

void Material::SetTexture(std::string uniformName, Texture* _texture)
{
	if (textures.find(uniformName) != textures.end())
		textures[uniformName] = _texture;
}

void Material::SetInt(std::string uniformName, int value)
{
	if (ints.find(uniformName) != ints.end())
		ints[uniformName] = value;
}

void Material::SetFloat(std::string uniformName, float value)
{
	if (floats.find(uniformName) != floats.end())
		floats[uniformName] = value;
}

void Material::SetFloat2(std::string uniformName, float v1, float v2)
{
	if (float2s.find(uniformName) != float2s.end())
	{
		float2s[uniformName][0] = v1;
		float2s[uniformName][1] = v2;
	}
}

void Material::SetFloat3(std::string uniformName, float v1, float v2, float v3)
{
	if (float3s.find(uniformName) != float3s.end())
	{
		float3s[uniformName][0] = v1;
		float3s[uniformName][1] = v2;
		float3s[uniformName][2] = v3;
	}
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
}
