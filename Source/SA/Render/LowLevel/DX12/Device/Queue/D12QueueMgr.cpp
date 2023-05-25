// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Queue/D12QueueMgr.hpp>

#include <Device/D12DeviceInfo.hpp>

namespace SA::RND::DX12
{
	QueueMgr::QueueMgr()
	{
	#if SA_DEBUG || SA_LOG_RELEASE_OPT
		graphics.debugName = "Graphics";
		compute.debugName = "Compute";
		transfer.debugName = "Transfer";
		present.debugName = "Present";
	#endif
	}

	void QueueMgr::Create(const DeviceInfo& _info)
	{
		graphics.Create(_info.graphics);
		compute.Create(_info.compute);
		transfer.Create(_info.transfer);
		present.Create(_info.present);

		SA_LOG(L"Queue Mgr created.", Info, SA.Render.DX12);
	}

	void QueueMgr::Destroy()
	{
		graphics.Destroy();
		compute.Destroy();
		transfer.Destroy();
		present.Destroy();

		SA_LOG(L"Queue Mgr destroyed.", Info, SA.Render.DX12);
	}
}
