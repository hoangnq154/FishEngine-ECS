#pragma once

#include "Object.hpp"

//#include <bgfx/bgfx.h>
#include "GraphicsAPI.hpp"

namespace FishEngine
{

	class Shader : public NamedObject
	{
		friend class ShaderUtil;
		
	public:
		Shader() = default;
		
	//	bgfx::ProgramHandle& GetProgram() { return m_Program; }
		
		static Shader* Find(const std::string& shaderName);
		
	public:
	//	bgfx::ProgramHandle m_Program;
	//	bgfx::ShaderHandle m_VertexShdaer;
	//	bgfx::ShaderHandle m_FragmentShader;
		ShaderHandle m_VertexShader;
		ShaderHandle m_FragmentShader;
		
		ShaderUniformSignature m_VertexShaderSignature;
		ShaderUniformSignature m_FragmentShaderSignature;
		
		bool m_IsReflected = false;
	};


	class ShaderUtil : public Static
	{
	public:
	//	static Shader* Compile(const std::string& vs_path, const std::string& fs_path);
		
		static Shader* CompileFromShaderName(const std::string & shaderName);
	};

}
