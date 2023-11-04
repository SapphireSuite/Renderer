// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_D12_STATIC_MESH_GUARD

#include <SA/Render/LowLevel/Common/Mesh/RawMesh.hpp>

#include <SA/Render/LowLevel/DX12/Buffers/D12Buffer.hpp>

namespace SA::RND::DX12
{
	class Device;
	class ResourceInitializer;

	class StaticMesh
	{
		Buffer mVertexBuffer;
		Buffer mIndexBuffer;

		uint32_t mIndexCount = 0;
		SA::RND::IndexBufferType mIndexBufferType;

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw);
		void Destroy();
	};
}

#endif // SAPPHIRE_RENDER_D12_STATIC_MESH_GUARD
