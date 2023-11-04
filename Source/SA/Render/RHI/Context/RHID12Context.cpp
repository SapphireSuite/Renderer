// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHID12Context.hpp>

#include <Pass/RHID12Pass.hpp>
#include <Pass/RHID12FrameBuffer.hpp>
#include <Shader/RHID12Shader.hpp>
#include <Pipeline/RHID12PipelineLayout.hpp>
#include <Pipeline/RHID12Pipeline.hpp>
#include <Pipeline/RHID12RenderViews.hpp>
#include <Device/Command/RHID12CommandPool.hpp>
#include <Buffer/RHID12Buffer.hpp>
#include <RHID12ResourceInitializer.hpp>
#include <Mesh/RHID12StaticMesh.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	Pass* D12Context::InstantiatePassClass()
	{
		return new D12Pass();
	}
	
	FrameBuffer* D12Context::InstantiateFrameBufferClass()
	{
		return new D12FrameBuffer();
	}

	Shader* D12Context::InstantiateShaderClass()
	{
		return new D12Shader();
	}

	RenderViews* D12Context::InstantiateRenderViewsClass()
	{
		return new D12RenderViews();
	}

	PipelineLayout* D12Context::InstantiatePipelineLayoutClass()
	{
		return new D12PipelineLayout();
	}

	Pipeline* D12Context::InstantiatePipelineClass()
	{
		return new D12Pipeline();
	}

	CommandPool* D12Context::InstantiateCommandPoolClass()
	{
		return new D12CommandPool();
	}

	Buffer* D12Context::InstantiateBufferClass()
	{
		return new D12Buffer();
	}

	ResourceInitializer* D12Context::InstantiateResourceInitializerClass()
	{
		return new D12ResourceInitializer();
	}

	StaticMesh* D12Context::InstantiateStaticMeshClass()
	{
		return new D12StaticMesh();
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL
