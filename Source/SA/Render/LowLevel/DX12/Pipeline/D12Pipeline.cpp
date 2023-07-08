// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/D12Pipeline.hpp>

#include <Device/D12Device.hpp>

namespace SA::RND::DX12
{
	void Pipeline::Destroy()
	{
		if (mHandle)
		{
			SA_LOG_RAII(L"Pipeline destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));

			mHandle.Reset();
			mRootSignatureRef.Reset();
		}
	}

	DXPipelineT Pipeline::operator->() const
	{
		return mHandle;
	}
}
