// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Mesh/RHIVkStaticMesh.hpp>

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void VkStaticMesh::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawMesh& _raw)
	{
		mHandle.Create(_device->API_Vulkan(), _init->API_Vulkan(), _raw);
	}

	void VkStaticMesh::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}

	void VkStaticMesh::Draw(const CommandBuffer* _cmd, uint32_t _instanceNum)
	{
		mHandle.Draw(_cmd->API_Vulkan(), _instanceNum);
	}

	const VK::StaticMesh& VkStaticMesh::API_Vulkan() const
	{
		return mHandle;
	}
}
