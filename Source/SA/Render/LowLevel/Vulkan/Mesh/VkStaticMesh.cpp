// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Mesh/VkStaticMesh.hpp>

#include <SA/Collections/Debug>

#include <Device/VkDevice.hpp>
#include <VkResourceInitializer.hpp>

namespace SA::RND::VK
{
	void StaticMesh::Create(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw)
	{
		// Vertex Buffer
		{
			Buffer& staging = _init.CreateStagingBuffer(_device, _raw.vertices.GetDataSize(), _raw.vertices.GetData());

			mVertexBuffer.Create(_device,
				_raw.vertices.GetDataSize(),
				VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			_init.cmd.CopyBuffer(staging, mVertexBuffer, _raw.vertices.GetDataSize());
		}

		// Index Buffer
		{
			mIndexCount = _raw.indices.GetIndexCount();
			mIndexBufferType = _raw.indices.GetIndexBufferType();

			Buffer& staging = _init.CreateStagingBuffer(_device, _raw.indices.GetDataSize(), _raw.indices.GetData());

			mIndexBuffer.Create(_device,
				_raw.indices.GetDataSize(),
				VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			_init.cmd.CopyBuffer(staging, mIndexBuffer, _raw.indices.GetDataSize());
		}

		SA_LOG("Static Mesh created.", Info, SA.Render.Vulkan);
	}

	void StaticMesh::Destroy(const Device& _device)
	{
		mVertexBuffer.Destroy(_device);
		mIndexBuffer.Destroy(_device);

		SA_LOG("Static Mesh destroyed.", Info, SA.Render.Vulkan);
	}
}
