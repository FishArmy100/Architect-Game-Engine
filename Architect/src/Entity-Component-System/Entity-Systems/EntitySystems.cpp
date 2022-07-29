#include "EntitySystems.h"
#include "Rendering-System/Renderer.h"

namespace Architect
{
	std::vector<std::shared_ptr<UpdateEntitySystem>> EntitySystems::s_UpdateSystems;
	std::vector<std::shared_ptr<RenderEntitySystem>> EntitySystems::s_RenderSystems;

	void EntitySystems::AddUpdateSystem(std::shared_ptr<UpdateEntitySystem> system)
	{
		if (!ContainsUpdateSystem(system))
		{
			s_UpdateSystems.push_back(system);
			system->OnAttach();
		}
	}

	bool EntitySystems::ContainsUpdateSystem(std::shared_ptr<UpdateEntitySystem> system)
	{
		for (auto& us : s_UpdateSystems)
		{
			if (us->GetName() == system->GetName())
				return true;
		}

		return false;
	}

	void EntitySystems::AddRenderSystem(std::shared_ptr<RenderEntitySystem> system)
	{
		if (!ContainsRenderSystem(system))
		{
			s_RenderSystems.push_back(system);
			system->OnAttach();
		}
	}

	bool EntitySystems::ContainsRenderSystem(std::shared_ptr<RenderEntitySystem> system)
	{
		for (auto& rs : s_RenderSystems)
		{
			if (rs->GetName() == system->GetName())
				return true;
		}

		return false;
	}

	void EntitySystems::OnUpdate(std::shared_ptr<Scene> scene, float timestep)
	{
		for (auto& us : s_UpdateSystems)
			us->OnUpdate(scene, timestep);
	}

	void EntitySystems::OnRender(std::shared_ptr<Scene> scene, Camera camera, glm::mat4 cameraTransform, std::shared_ptr<Framebuffer> framebuffer)
	{
		if (framebuffer)
			Renderer::Begin(camera, cameraTransform, framebuffer);
		else
			Renderer::Begin(camera, cameraTransform);

		for (auto& rs : s_RenderSystems)
			rs->OnRender(scene);

		Renderer::End();
	}
}
