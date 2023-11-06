// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_D12_STATIC_MESH_GUARD

#include <SA/Render/LowLevel/Common/Mesh/RawStaticMesh.hpp>

#include <SA/Render/LowLevel/DX12/Buffers/D12Buffer.hpp>

namespace SA::RND::DX12
{
	class Device;
	class ResourceInitializer;
	class CommandBuffer;

	class StaticMesh
	{
		Buffer mVertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW mVertexView;

		Buffer mIndexBuffer;
		D3D12_INDEX_BUFFER_VIEW mIndexView;

		uint32_t mIndexCount = 0;

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawStaticMesh& _raw);
		void Destroy();

		void Draw(const CommandBuffer& _cmd, uint32_t _instanceNum = 1u);
	};
}

#endif // SAPPHIRE_RENDER_D12_STATIC_MESH_GUARD
