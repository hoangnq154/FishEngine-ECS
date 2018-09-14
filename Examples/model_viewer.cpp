#include <FishEngine.hpp>
#include <FishEditor.hpp>
#include <GLFW/glfw3.h>


class DrawSkeletonSystem : public ECS::ISystem
{
	SYSTEM(DrawSkeletonSystem);
public:
	void Update() override
	{
		m_Scene->ForEach<Renderable>([](ECS::GameObject* go, Renderable* rend)
		{
			if (rend->skin == nullptr)
				return;
			
			Gizmos::matrix = Matrix4x4::identity;
			Gizmos::color = Vector4(1, 0, 0, 1);
			for (auto* bone : rend->skin->joints)
			{
				auto t = bone->GetTransform();
				//Gizmos::matrix = t->GetLocalToWorldMatrix();
				//Gizmos::DrawCube(Vector3::zero, Vector3::one * 0.05f);
				Gizmos::DrawCube(t->GetPosition(), Vector3::one * 0.05f);
				
				//auto p = t->GetParent();
				//if (p != nullptr)
				//{
				//	Gizmos::matrix = p->GetLocalToWorldMatrix();
				//	Gizmos::DrawLine(t->GetLocalPosition(), Vector3::zero);
				//}
			}

			Gizmos::matrix = Matrix4x4::identity;
			Gizmos::color = Vector4(0, 1, 0, 1);
			for (auto* bone : rend->skin->joints)
			{
				auto t = bone->GetTransform();
				auto p = t->GetParent();
				if (p != nullptr)
				{
					Gizmos::DrawLine(t->GetPosition(), p->GetPosition());
				}
			}
		});
	}
};


inline std::string GetglTFSample(const std::string& name)
{
#ifdef __APPLE__
	return "/Users/yushroom/program/github/glTF-Sample-Models/2.0/"
	
#else
	return R"(D:\program\glTF-Sample-Models\2.0\)"
#endif
		+ name + "/glTF-Binary/" + name + ".glb";
}

class ModelViewer : public GameApp
{
public:
	void Start() override
	{
		//const char* path = FISHENGINE_ROOT "Assets/Models/T-Rex.glb";
		auto path = GetglTFSample("CesiumMan");
		//path = GetglTFSample("RiggedSimple");
		//path = GetglTFSample("TextureCoordinateTest");
//		path = GetglTFSample("Triangle");
//		path = "/Users/yushroom/program/github/glTF-Sample-Models/2.0/Triangle/glTF/Triangle.gltf";
		//path = R"(D:\program\glTF-Sample-Models\2.0\Sponza\glTF\Sponza.gltf)";
//		path = "/Users/yushroom/program/github/glTF-Sample-Models/2.0/Sponza/glTF/Sponza.gltf";
		path = GetglTFSample("Buggy");
//		path = GetglTFSample("BrainStem");

		{
			auto go = m_Scene->CreateGameObject();
			m_Scene->GameObjectAddComponent<Camera>(go);
			go->GetTransform()->SetLocalPosition(0, 0, -10);
			//m_Scene->GameObjectAddComponent<FreeCamera>(go);
			go->m_Name = "Main Camera";
		}
		{
			auto go = m_Scene->CreateGameObject();
			auto t = go->GetTransform();
			auto light = m_Scene->GameObjectAddComponent<Light>(go);
			t->SetLocalEulerAngles(50, -30, 0);
			t->SetLocalPosition(0, 3, 0);
			go->m_Name = "Directional Light";
		}
		
		auto rootGO = ModelUtil::FromGLTF(path, m_Scene);
//		auto rootGO = m_Scene->CreateGameObject();
//		auto r = m_Scene->GameObjectAddComponent<Renderable>(rootGO);
//		r->mesh = Mesh::Cube;
#if 0
		auto vs = FISHENGINE_ROOT "Shaders/runtime/PBR_vs.bin";
		auto fs = FISHENGINE_ROOT "Shaders/runtime/PBR_fs.bin";
		m_Shader = ShaderUtil::Compile(vs, fs);
		Material* mat = new Material();
		mat->SetShader(m_Shader);
		Vector4 pbrparams(0, 0.5f, 0, 0);
		mat->SetVector("BaseColor", Vector4::one);
		mat->SetVector("PBRParams", pbrparams);
#else
		Material* mat = Material::Clone(Material::ColorMaterial);
		mat->SetVector("u_color", Vector4(1, 1, 0, 1));
#endif
//		r->m_Materials.push_back( mat );

//		m_Scene->ForEach<Renderable>([mat](ECS::GameObject* go, Renderable* r){
//			r->mesh = nullptr;
//		});

		//rootGO->GetTransform()->SetLocalEulerAngles(-90, -90, 0);
		rootGO->GetTransform()->SetLocalScale(0.1f);

		//m_Scene->AddSystem<FreeCameraSystem>();

		{
			auto s = m_Scene->AddSystem<AnimationSystem>();
			s->m_Priority = 999;
			s->m_Enabled = false;
		}
		m_Scene->AddSystem<DrawSkeletonSystem>();

		//m_Scene->AddSystem<SelectionSystem>();
		auto selection = m_EditorScene->GetSingletonComponent<SingletonSelection>();
		selection->selected = Camera::GetMainCamera()->m_GameObject;

		

		{
			auto cam = Camera::GetEditorCamera();
			assert(cam != nullptr);
			cam->GetTransform()->SetLocalPosition(2.5, 2.5, -11);
			cam->GetTransform()->SetLocalEulerAngles(45, -60, 0);
		}
	}
	
private:
	Shader* m_Shader = nullptr;
};


int main(void)
{
	ModelViewer demo;
	demo.Run();
	return 0;
}
