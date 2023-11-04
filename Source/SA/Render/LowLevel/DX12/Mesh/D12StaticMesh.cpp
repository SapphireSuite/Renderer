// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Mesh/D12StaticMesh.hpp>

#include <D12ResourceInitializer.hpp>

namespace SA::RND::DX12
{
	void StaticMesh::Create(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw)
	{
		// Vertex Buffer
		{
			Buffer& staging = _init.CreateStagingBuffer(_device, _raw.vertices.GetDataSize(), _raw.vertices.GetData());

			mVertexBuffer.Create(_device,
				_raw.vertices.GetDataSize(),
				D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
				D3D12_HEAP_TYPE_DEFAULT);

			_init.cmd.CopyBuffer(staging, mVertexBuffer, _raw.vertices.GetDataSize());
		}

		// Index Buffer
		{
			mIndexCount = _raw.indices.GetIndexCount();
			mIndexBufferType = _raw.indices.GetIndexBufferType();

			Buffer& staging = _init.CreateStagingBuffer(_device, _raw.indices.GetDataSize(), _raw.indices.U32());

			mIndexBuffer.Create(_device,
				_raw.indices.GetDataSize(),
				D3D12_RESOURCE_STATE_INDEX_BUFFER,
				D3D12_HEAP_TYPE_DEFAULT);

			_init.cmd.CopyBuffer(staging, mIndexBuffer, _raw.indices.GetDataSize());
		}

		SA_LOG("Static Mesh created.", Info, SA.Render.DX12);
	}

	void StaticMesh::Destroy()
	{
		mVertexBuffer.Destroy();
		mIndexBuffer.Destroy();

		SA_LOG("Static Mesh destroyed.", Info, SA.Render.DX12);
	}
}
