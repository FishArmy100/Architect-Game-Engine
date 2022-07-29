#pragma once
#include "UpdateEntitySystem.h"
#include "RenderEntitySystem.h"

#include "Rendering-System/Framebuffer.h"
#include "Rendering-System/Camera.h"

namespace Architect
{
	class EntitySystems
	{
	public:
		static void AddUpdateSystem(std::shared_ptr<UpdateEntitySystem> system);
		static bool ContainsUpdateSystem(std::shared_ptr<UpdateEntitySystem> system);

		static void AddRenderSystem(std::shared_ptr<RenderEntitySystem> system);
		static bool ContainsRenderSystem(std::shared_ptr<RenderEntitySystem> system);

		static void OnUpdate(std::shared_ptr<Scene> scene, float timestep);

		static void OnRender(std::shared_ptr<Scene> scene, 
							 Camera camera, 
							 glm::mat4 cameraTransform = glm::mat4(1.0f), 
							 std::shared_ptr<Framebuffer> framebuffer = nullptr);



		template<typename Func>
		static void OnUpdate(std::shared_ptr<Scene> scene, float timestep, Func func)
		{
			for (auto& us : s_UpdateSystems)
			{
				if (func(us))
				{
					us->OnUpdate(scene, timestep);
				}
			}
		}

	private:
		static std::vector<std::shared_ptr<UpdateEntitySystem>> s_UpdateSystems;
		static std::vector<std::shared_ptr<RenderEntitySystem>> s_RenderSystems;
	};
}

