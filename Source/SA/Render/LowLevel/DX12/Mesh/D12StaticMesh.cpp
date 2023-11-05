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
				D3D12_RESOURCE_STATE_COMMON,
				D3D12_HEAP_TYPE_DEFAULT);

			_init.cmd.CopyBuffer(staging, mVertexBuffer, _raw.vertices.GetDataSize());

			// View
			mVertexView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
			mVertexView.StrideInBytes = _raw.vertices.GetVertexStride();
			mVertexView.SizeInBytes = static_cast<uint32_t>(_raw.vertices.GetDataSize());
		}


		// Index Buffer
		{
			mIndexCount = _raw.indices.GetIndexCount();
			SA::RND::IndexBufferType indexBufferType = _raw.indices.GetIndexBufferType();

			Buffer& staging = _init.CreateStagingBuffer(_device, _raw.indices.GetDataSize(), _raw.indices.GetData());

			mIndexBuffer.Create(_device,
				_raw.indices.GetDataSize(),
				D3D12_RESOURCE_STATE_COMMON,
				D3D12_HEAP_TYPE_DEFAULT);

			_init.cmd.CopyBuffer(staging, mIndexBuffer, _raw.indices.GetDataSize());

			// View
			mIndexView.BufferLocation = mIndexBuffer->GetGPUVirtualAddress();
			mIndexView.SizeInBytes = static_cast<uint32_t>(_raw.indices.GetDataSize());

			switch (indexBufferType)
			{
				case SA::RND::IndexBufferType::UINT16:
					mIndexView.Format = DXGI_FORMAT_R16_UINT;
					break;
				case SA::RND::IndexBufferType::UINT32:
					mIndexView.Format = DXGI_FORMAT_R32_UINT;
					break;
				default:
				{
					mIndexView.Format = DXGI_FORMAT_UNKNOWN;
					SA_LOG((L"Invalid index buffer format [%1]", indexBufferType), Error, SA.Render.DX12);
					break;
				}
			}
		}


		// Transitions
		{
			const D3D12_RESOURCE_BARRIER barriers[2]{
				// Vertex Buffer
				{
					.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
					.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
					.Transition
					{
						.pResource = mVertexBuffer.Get(),
						.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST,
						.StateAfter = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
					}
				},

				// Index Buffer
				{
					.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
					.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
					.Transition
					{
						.pResource = mIndexBuffer.Get(),
						.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST,
						.StateAfter = D3D12_RESOURCE_STATE_INDEX_BUFFER,
					}
				}
			};

			_init.cmd.Transition(barriers, 2);
		}

		SA_LOG("Static Mesh created.", Info, SA.Render.DX12);
	}

	void StaticMesh::Destroy()
	{
		mVertexBuffer.Destroy();
		mIndexBuffer.Destroy();

		SA_LOG("Static Mesh destroyed.", Info, SA.Render.DX12);
	}

	void StaticMesh::Draw(const CommandBuffer& _cmd, uint32_t _instanceNum)
	{
		_cmd->IASetVertexBuffers(0, 1, &mVertexView);
		_cmd->IASetIndexBuffer(&mIndexView);
		_cmd->DrawIndexedInstanced(mIndexCount, _instanceNum, 0, 0, 0);
	}
}
