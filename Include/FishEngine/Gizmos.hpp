#pragma once

#include "ClassDef.hpp"
#include "Math.hpp"
#include "Material.hpp"
#include "MeshVertex.hpp"
#include <vector>


template<class T>
size_t Sizeof(const std::vector<T> v)
{
    return sizeof(T) * v.size();
}


class Gizmos : public Static
{
    friend class RenderSystem;
public:
    inline static Vector4 color;
    inline static Matrix4x4 matrix;

    static void StaticInit();
    static void DrawCube(const Vector3& center, const Vector3& size);
    static void DrawLine(Vector3 from, Vector3 to);
    static void DrawWireSphere(const Vector3& center, float radius);
    
private:
	
	// call by RenderSystem
	static void __Draw();

	
	inline static Material* s_ColorMaterial = nullptr;
	inline static Material* s_VertexColorMaterial = nullptr;
    inline static std::vector<VertexPC> s_Lines;
	inline static bgfx::DynamicVertexBufferHandle s_LineDynamicVertexBuffer;
};
