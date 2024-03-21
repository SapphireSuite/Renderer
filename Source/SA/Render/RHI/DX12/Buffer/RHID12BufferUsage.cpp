// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Common/Buffer/RHIBufferUsage.hpp>

namespace SA::RND::DX12
{
	D3D12_RESOURCE_STATES API_GetBufferUsage(RHI::BufferUsage _usage)
	{
		D3D12_RESOURCE_STATES d12Flags = D3D12_RESOURCE_STATES(0);


		if (_usage & RHI::BufferUsageFlags::CPUUpload)
			d12Flags |= D3D12_RESOURCE_STATE_GENERIC_READ;


		if (_usage & RHI::BufferUsageFlags::UniformBuffer)
			d12Flags |= D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE;
		if (_usage & RHI::BufferUsageFlags::StorageBuffer)
			d12Flags |= D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE;
		if (_usage & RHI::BufferUsageFlags::VertexBuffer)
			d12Flags |= D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
		if (_usage & RHI::BufferUsageFlags::IndexBuffer)
			d12Flags |= D3D12_RESOURCE_STATE_INDEX_BUFFER;

		return d12Flags;
	}

	D3D12_HEAP_TYPE API_GetBufferMemoryHeapType(RHI::BufferUsage _usage)
	{
		D3D12_HEAP_TYPE d12Flags = D3D12_HEAP_TYPE(0);

		SA_ASSERT((Equals0, ((_usage & RHI::BufferUsageFlags::CPUUpload) && (_usage & RHI::BufferUsageFlags::CPUReadBack))), SA.Render.RHI.DX12,
			L"Only one of BufferUsage::CPUUpload and BufferUsage::CPUReadBack flag can be specified at a time.");

		if (_usage & RHI::BufferUsageFlags::CPUUpload)
			d12Flags = D3D12_HEAP_TYPE_UPLOAD;
		else if (_usage & RHI::BufferUsageFlags::CPUReadBack)
			d12Flags = D3D12_HEAP_TYPE_READBACK;
		else
			d12Flags = D3D12_HEAP_TYPE_DEFAULT;

		return d12Flags;
	}
}
