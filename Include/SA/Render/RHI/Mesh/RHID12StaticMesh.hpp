// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_RHI_D12_STATIC_MESH_GUARD

#include <SA/Render/RHI/Mesh/RHIStaticMesh.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Mesh/D12StaticMesh.hpp>

namespace SA::RND::RHI
{
	class D12StaticMesh : public StaticMesh
	{
		DX12::StaticMesh mHandle;

	public:
		void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawStaticMesh& _raw) override final;
		void Destroy(const Device* _device) override final;

		void Draw(const CommandBuffer* _cmd, uint32_t _instanceNum = 1) override final;

		const DX12::StaticMesh& API_DirectX12() const override final;
	};
}

#endif

#endif // SAPPHIRE_RENDER_RHI_D12_STATIC_MESH_GUARD
