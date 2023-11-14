// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <list>
#include <thread>

#include <SA/Collections/Debug>
#include <SA/Collections/Maths>

#include <SA/Maths/Transform/Transform.hpp>
#include <SA/Render/LowLevel/Common/Camera/CameraUBO.hpp>
#include <SA/Render/RHI/RHIVkRenderInterface.hpp>
#include <SA/Render/RHI/RHID12RenderInterface.hpp>
#include <SA/Render/RHI/Compatibility/IRenderWindow.hpp>
#include <SA/Render/RHI/Compatibility/IWindowInterface.hpp>
using namespace SA::RND;

// Must be included after vulkan.
#include <GLFW/glfw3.h>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#endif

void GLFWErrorCallback(int32_t error, const char* description)
{
	SA_LOG((L"GLFW Error [%1]: %2", error, description), Error, SA.Render.Proto.GLFW.API);
}

class WindowInterface : public RHI::IWindowInterface
{
public:
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	std::vector<const char*> QueryVkRequiredExtensions() const override final
	{
		std::vector<const char*> vkExts;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = nullptr;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		vkExts.reserve(glfwExtensionCount);
		vkExts.insert(vkExts.end(), glfwExtensions, glfwExtensions + glfwExtensionCount);

		return vkExts;
	}

#endif
};

class WindowHandle : public RHI::IRenderWindow
{
	GLFWwindow* mHandle = nullptr;

public:
	WindowHandle(GLFWwindow* _handle) noexcept :
		mHandle{ _handle }
	{
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VkSurfaceKHR CreateVkSurfaceKHR(const SA::RND::VK::Instance& _instance) const override final
	{
		VkSurfaceKHR glfwsurface;
		glfwCreateWindowSurface(_instance, mHandle, nullptr, &glfwsurface);

		return glfwsurface;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	HWND GetHWNDHandle() const override final
	{
		return glfwGetWin32Window(mHandle);
	}

#endif
};

class Renderer
{
public:
	GLFWwindow* window = nullptr;

	RHI::RenderInterface* intf = nullptr;
	RHI::Device* device = nullptr;
	RHI::WindowSurface* winSurface = nullptr;
	RHI::Swapchain* swapchain = nullptr;
	RHI::Context* context = nullptr;
	RHI::Pass* pass = nullptr;
	std::vector<RHI::FrameBuffer*> frameBuffers;
	RHI::Shader* vertexShader = nullptr;
	RHI::Shader* pixelShader = nullptr;
	RHI::PipelineLayoutDescriptor pipLayoutDesc;
	RHI::PipelineLayout* pipLayout = nullptr;
	RHI::Pipeline* pipeline = nullptr;
	RHI::RenderViews* views = nullptr;
	RHI::CommandPool* cmdPool = nullptr;
	std::vector<RHI::CommandBuffer*> cmdBuffers;
	RawStaticMesh quadRaw;
	RHI::StaticMesh* quadMesh;
	SA::TransformPRSf cameraTr;
	std::vector<RHI::Buffer*> cameraBuffers;

	struct CreateInfo
	{
		RHI::RenderInterface* intf = nullptr; 
		std::string winName;
		int winPosX = 0;
		int winPosY = 0;
	};

	void Create(const CreateInfo& _info)
	{
		WindowInterface winIntf;

		intf = _info.intf;
		intf->Create(&winIntf);

		// GLFW
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			window = glfwCreateWindow(960, 540, _info.winName.c_str(), nullptr, nullptr);
			glfwSetWindowPos(window, _info.winPosX, _info.winPosY + 30);
			SA_ASSERT((Nullptr, window), SA.Render.Proto.GLFW, L"GLFW create window failed!");
			
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		// Win Surface
		{
			WindowHandle winHandle(window);

			winSurface = intf->CreateWindowSurface(&winHandle);
		}

		// Device
		{
			RHI::DeviceRequirements reqs;
			reqs.SetWindowSurface(winSurface);

			auto infos = intf->QueryDeviceInfos(reqs);

			for (auto& info : infos)
				SA_LOG((L"Device found: Name: [%1], ID: [%2], Vendor [%3], Score [%4]", info->GetName(), info->GetID(), info->GetVendorID(), info->GetScore()));

			device = intf->CreateDevice(infos[0].get());
		}
		
		// Swapchain
		{
			swapchain = intf->CreateSwapchain(device, winSurface);
		}

		// Context
		{
			context = device->CreateContext();
		}

		// RenderPass
		{
			// Info
			RHI::PassInfo passInfo;
			{
				constexpr bool bDepth = true;
				constexpr bool bMSAA = true;

				// Forward
				if (true)
				{
					auto& mainSubpass = passInfo.AddSubpass("Main");

					if(bMSAA)
						mainSubpass.sampling = RHI::Sampling::Sample8Bits;

					// Color and present attachment.
					auto& colorRT = mainSubpass.AddAttachment("Color");
					colorRT.format = swapchain->GetFormat();
					colorRT.usage = AttachmentUsage::Present;

					if(bDepth)
					{
						auto& depthRT = mainSubpass.AddAttachment("Depth");
						depthRT.format = RHI::Format::D16_UNORM;
						depthRT.type = AttachmentType::Depth;
					}

					mainSubpass.SetAllAttachmentExtents(swapchain->GetExtents());
				}
				else if(true) // Deferred
				{
					passInfo.subpasses.reserve(2u);

					// GBuffer
					{
						auto& GBufferSubpass = passInfo.AddSubpass("GBuffer Pass");

						if(bMSAA)
							GBufferSubpass.sampling = RHI::Sampling::Sample8Bits;

						// Render Targets
						{
							// Deferred position attachment.
							auto& posRT = GBufferSubpass.AddAttachment("GBuffer_Position");

							// Deferred normal attachment.
							auto& normRT = GBufferSubpass.AddAttachment("GBuffer_Normal");

							// Deferred albedo attachment.
							auto& albedoRT = GBufferSubpass.AddAttachment("GBuffer_Color");

							// Deferred PBR (Metallic, Roughness, Ambiant occlusion) attachment.
							auto& pbrRT = GBufferSubpass.AddAttachment("GBuffer_PBR");

							if(bDepth)
							{
								auto& pbrDepthRT = GBufferSubpass.AddAttachment("Depth");
								pbrDepthRT.format = RHI::Format::D16_UNORM;
								pbrDepthRT.type = AttachmentType::Depth;
							}
						}

						GBufferSubpass.SetAllAttachmentExtents(swapchain->GetExtents());
					}

					// Present Subpass
					{
						auto& presentSubpass = passInfo.AddSubpass("Present Pass");

						if(bMSAA)
							presentSubpass.sampling = RHI::Sampling::Sample8Bits;

						auto& presentRT = presentSubpass.AddAttachment("Color");
						presentRT.format = swapchain->GetFormat();
						presentRT.usage = AttachmentUsage::Present;

						presentSubpass.SetAllAttachmentExtents(swapchain->GetExtents());
					}
				}
			}

			pass = context->CreatePass(std::move(passInfo));
		}

		// FrameBuffers
		{
			uint32_t num = swapchain->GetImageNum();
			frameBuffers.resize(num);

			for(uint32_t i = 0; i < num; ++i)
				frameBuffers[i] = context->CreateFrameBuffer(pass, swapchain->GetBackBufferHandle(i));
		}

		RHI::ResourceInitializer* resInit = context->CreateResourceInitializer();

		// Mesh
		{
			quadRaw.vertices.BuildVertexBuffer(
				VertexComponent<SA::Vec3f>{
					"POSITION",
					{
						{-0.5f, 0.5f, 0.0f},
						{0.5f, 0.5f, 0.0},
						{-0.5f, -0.5f, 0.0},
						{0.5f, -0.5f, 0.0}
					}
				},

				VertexComponent<Color>{
					"COLOR",
					{
						Color::red,
						Color::green,
						Color::blue,
						Color::white
					}
				}
			);

			quadRaw.indices.U16({0, 1, 2, 1, 3, 2});

			quadMesh = context->CreateStaticMesh(resInit, quadRaw);
		}

		resInit->Submit();

		// Shaders
		{
			// Vertex
			{
				ShaderCompileInfo vsInfo
				{
					.path = L"Resources/Shaders/Passes/MainPass.hlsl",
					.entrypoint = "mainVS",
					.target = "vs_6_5",
				};

				quadRaw.vertices.AppendDefines(vsInfo.defines);

				ShaderCompileResult vsShaderRes = intf->CompileShader(vsInfo);
				vertexShader = context->CreateShader(vsShaderRes);
				pipLayoutDesc.AddShader(vsShaderRes.desc);
			}

			// Pixel
			{
				ShaderCompileInfo psInfo
				{
					.path = L"Resources/Shaders/Passes/MainPass.hlsl",
					.entrypoint = "mainPS",
					.target = "ps_6_5",
				};

				quadRaw.vertices.AppendDefines(psInfo.defines);

				ShaderCompileResult psShaderRes = intf->CompileShader(psInfo);
				pixelShader = context->CreateShader(psShaderRes);
				pipLayoutDesc.AddShader(psShaderRes.desc);
			}
		}
	
		// RenderViews
		{
			views = context->CreateRenderViews();

			views->AddFullView(swapchain->GetExtents());
		}

		// PipelineLayout
		{
			pipLayout = context->CreatePipelineLayout(pipLayoutDesc);
		}

		// Pipeline
		{
			RHI::GraphicsPipelineInfo info;
			info.shaders.vs = vertexShader;
			info.shaders.ps = pixelShader;

			info.layout = pipLayout;

			info.pass = pass;

			info.views = views;

			pipeline = context->CreatePipeline(info);
		}

		// CommandPool
		{
			cmdPool = context->CreateCommandPool();

			cmdBuffers = cmdPool->Allocate(swapchain->GetImageNum());
		}

		// Camera
		{
			cameraBuffers.resize(swapchain->GetImageNum());

			for (auto& cameraBuffer : cameraBuffers)
				cameraBuffer = context->CreateBuffer(sizeof(CameraUBO), RHI::BufferUsageFlags::UniformBuffer | RHI::BufferUsageFlags::CPUUpload);
		}
	}

	void Destroy()
	{
		// Render
		{
			device->WaitIdle();

			cmdPool->Free(cmdBuffers);
			context->DestroyCommandPool(cmdPool);
			context->DestroyPipeline(pipeline);
			context->DestroyPipelineLayout(pipLayout);

			context->DestroyShader(vertexShader);
			context->DestroyShader(pixelShader);

			for(auto& frameBuffer : frameBuffers)
				context->DestroyFrameBuffer(frameBuffer);

			context->DestroyPass(pass);

			device->DestroyContext(context);

			intf->DestroySwapchain(device, swapchain);

			intf->DestroyWindowSurface(winSurface);
			intf->DestroyDevice(device);

			intf->Destroy();
			delete intf;
		}

		// GLFW
		{
			glfwDestroyWindow(window);
		}
	}

	void Loop()
	{
		double oldMouseX = 0.0f;
		double oldMouseY = 0.0f;
		float dx = 0.0f;
		float dy = 0.0f;

		const float moveSpeed = 4.0f;
		const float rotSpeed = 16.0f;

		glfwGetCursorPos(window, &oldMouseX, &oldMouseY);

		const float fixedTime = 0.0025f;
		float accumulateTime = 0.0f;
		auto start = std::chrono::steady_clock::now();

		while (!glfwWindowShouldClose(window))
		{
			auto end = std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - start).count();
			accumulateTime += deltaTime;
			start = end;

			// Fixed Update
			if (accumulateTime >= fixedTime)
			{
				accumulateTime -= fixedTime;

				glfwPollEvents();

				// Process input
				{
					if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
						glfwSetWindowShouldClose(window, true);
					if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
						cameraTr.position += fixedTime * moveSpeed * cameraTr.Right();
					if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
						cameraTr.position -= fixedTime * moveSpeed * cameraTr.Right();
					if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
						cameraTr.position -= fixedTime * moveSpeed * cameraTr.Up();
					if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
						cameraTr.position += fixedTime * moveSpeed * cameraTr.Up();
					if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
						cameraTr.position -= fixedTime * moveSpeed * cameraTr.Forward();
					if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
						cameraTr.position += fixedTime * moveSpeed * cameraTr.Forward();

					double mouseX = 0.0f;
					double mouseY = 0.0f;

					glfwGetCursorPos(window, &mouseX, &mouseY);

					if (mouseX != oldMouseX || mouseY != oldMouseY)
					{
						dx -= static_cast<float>(mouseX - oldMouseX) * fixedTime * rotSpeed * SA::Maths::DegToRad<float>;
						dy += static_cast<float>(mouseY - oldMouseY) * fixedTime * rotSpeed * SA::Maths::DegToRad<float>;

						oldMouseX = mouseX;
						oldMouseY = mouseY;

						dx = dx > SA::Maths::Pi<float> ?
							dx - SA::Maths::Pi<float> :
							dx < -SA::Maths::Pi<float> ? dx + SA::Maths::Pi<float> : dx;
						dy = dy > SA::Maths::Pi<float> ?
							dy - SA::Maths::Pi<float> :
							dy < -SA::Maths::Pi<float> ? dy + SA::Maths::Pi<float> : dy;

						cameraTr.rotation = SA::Quatf(cos(dx), 0, sin(dx), 0) * SA::Quatf(cos(dy), sin(dy), 0, 0);
					}
				}
			}

			const uint32_t frameIndex = swapchain->Begin();

			// Update camera.
			{
				CameraUBO cameraUBO;

				cameraUBO.position = cameraTr.position;
				cameraUBO.inverseView = cameraTr.Matrix().GetInversed();
				cameraUBO.projection = SA::Mat4f::MakePerspective(90, 960.0f / 540.0f);


				cameraBuffers[frameIndex]->UploadData(cameraUBO);
			}

			RHI::CommandBuffer* const cmd = cmdBuffers[frameIndex];
			RHI::FrameBuffer* const fbuff = frameBuffers[frameIndex];

			cmd->Begin();

			pass->Begin(cmd, fbuff);

			views->Bind(cmd);
			pipeline->Bind(cmd);


			quadMesh->Draw(cmd);


			pass->End(cmd);

			cmd->End();

			swapchain->End({ cmd });
		}
	}

	static void RenderThread(const CreateInfo& _info)
	{
		Renderer renderer;

		renderer.Create(_info);

		renderer.Loop();

		renderer.Destroy();
	}
};

int main()
{
	SA::Debug::InitDefaultLoggerThread();

	// GLFW
	{
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwInit();
	}


	// Render
	if (true)
	{
		std::list<std::thread> renderThreads;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
		renderThreads.emplace_back(std::thread(Renderer::RenderThread, Renderer::CreateInfo{ new RHI::VkRenderInterface, "Vulkan" }));
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
		renderThreads.emplace_back(std::thread(Renderer::RenderThread, Renderer::CreateInfo{ new RHI::D12RenderInterface, "DirectX12", 960, 0 }));
#endif

		for (auto& renderThread : renderThreads)
		{
			if (renderThread.joinable())
				renderThread.join();
		}
	}
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	else if (true)
	{
		Renderer::RenderThread(Renderer::CreateInfo{ new RHI::VkRenderInterface, "Vulkan" });
	}
#endif
#if SA_RENDER_LOWLEVEL_DX12_IMPL
	else if (true)
	{
		Renderer::RenderThread(Renderer::CreateInfo{ new RHI::D12RenderInterface, "DirectX12", 960, 0 });
	}
#endif


	// GLFW
	{
		glfwTerminate();
	}

	return 0;
}
