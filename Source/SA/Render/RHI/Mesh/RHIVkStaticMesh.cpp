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


	const VK::StaticMesh& VkStaticMesh::API_Vulkan() const
	{
		return mHandle;
	}
}
