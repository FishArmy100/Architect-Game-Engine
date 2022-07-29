#pragma once
#include "MannagedVertexArray.h"
#include "IndexBuffer.h"
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
		DrawCallData(MannagedVertexArray& va, std::shared_ptr<IndexBuffer> ib, Material& mat, glm::mat4& transform, int id)
		{
			VertexArray = va;
			IndexBuffer = ib;
			Mat = mat;
			Transform = transform;
			ID = id;
		}

		MannagedVertexArray VertexArray;
		std::shared_ptr<IndexBuffer> IndexBuffer;
		Material Mat;
		glm::mat4 Transform;
		int ID;
	};

	class Renderer
	{		
	public:
		static void Begin(Camera camera, glm::mat4 cameraTransform);
		static void Begin(Camera camera, glm::mat4 cameraTransform, std::shared_ptr<Framebuffer> framebuffer);
		static void AddDrawCall(MannagedVertexArray& va, std::shared_ptr<IndexBuffer> ib, Material& mat, glm::mat4& transform, int id);
		static void End();

	private:
		inline static std::vector<DrawCallData> m_DrawCalls;
		inline static Camera m_Camera = Camera(0, 0);
		inline static glm::mat4 m_CameraTransform;
		inline static std::shared_ptr<Framebuffer> m_ActiveFrameBuffer;
	};
}

