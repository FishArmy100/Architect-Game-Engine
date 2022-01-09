#pragma once
#include "MannagedVertexArray.h"
#include "MannagedIndexBuffer.h"
#include "Material.h"
#include <vector>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Core.h"
#include "Framebuffer.h"

namespace Architect
{
	struct DrawCallData
	{
		DrawCallData(MannagedVertexArray& va, MannagedIndexBuffer& ib, Material& mat, glm::mat4& transform)
		{
			VertexArray = va;
			IndexBuffer = ib;
			Mat = mat;
			Transform = transform;
		}

		MannagedVertexArray VertexArray;
		MannagedIndexBuffer IndexBuffer;
		Material Mat;
		glm::mat4 Transform;
	};

	class Renderer
	{		
	public:
		static void Begin(Camera* camera, glm::mat4 cameraTransform);
		static void Begin(Camera* camera, glm::mat4 cameraTransform, std::shared_ptr<Framebuffer> framebuffer);
		static void AddDrawCall(MannagedVertexArray& va, MannagedIndexBuffer& ib, Material& mat, glm::mat4& transform);
		static void End();

	private:
		static std::vector<DrawCallData> m_DrawCalls;
		static Camera* m_Camera;
		static glm::mat4 m_CameraTransform;
		static std::shared_ptr<Framebuffer> m_ActiveFrameBuffer;
	};
}

