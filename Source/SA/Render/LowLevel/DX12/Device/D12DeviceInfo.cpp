// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/D12DeviceInfo.hpp>

namespace SA::RND::DX12
{
	void DeviceInfo::SetPhysicalDevice(PhysicalDevice _device)
	{
		physicalDevice = _device;

		physicalDevice->GetDesc2(&desc);
	}
	

	bool DeviceInfo::TryCreateLogicalDevice()
	{
		return SUCCEEDED(D3D12CreateDevice(physicalDevice.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&logicalDevice)));
	}


	bool ProcessFamily(
		LogicalDevice _logicalDevice,
		uint32_t& _num,
		QueueFamilyInfo& _queueFam,
		const D3D12_COMMAND_QUEUE_DESC& _desc)
	{
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue;

		while(_num > 0)
		{
			queue = nullptr;

			if(FAILED(_logicalDevice->CreateCommandQueue(&_desc, IID_PPV_ARGS(&queue))))
				return false;

			_queueFam.queues.emplace_back(std::move(queue));
			--_num;
		}

		return true;
	}


	int DeviceInfo::QueryQueueFamilies(QueueRequirements _queueReqs)
	{
		// Graphics
		{
			D3D12_COMMAND_QUEUE_DESC queueDesc{};
			queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

			ProcessFamily(logicalDevice, _queueReqs.graphicsNum, graphics, queueDesc);
		}

		// Compute
		{
			D3D12_COMMAND_QUEUE_DESC queueDesc{};
			queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;

			ProcessFamily(logicalDevice, _queueReqs.computeNum, compute, queueDesc);
		}

		// Transfer
		{
			D3D12_COMMAND_QUEUE_DESC queueDesc{};
			queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;

			ProcessFamily(logicalDevice, _queueReqs.transferNum, transfer, queueDesc);
		}

		// Present
		{
			D3D12_COMMAND_QUEUE_DESC queueDesc{};
			queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

			ProcessFamily(logicalDevice, _queueReqs.presentNum, present, queueDesc);
		}

		return _queueReqs.GetCompletedCode();
	}


	void DeviceInfo::Evaluate()
	{
		// Not CGPU
		if((desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0)
			score += 1000;
	}
}
