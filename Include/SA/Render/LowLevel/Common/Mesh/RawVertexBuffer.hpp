// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RAW_VERTEX_BUFFER_GUARD
#define SAPPHIRE_RENDER_RAW_VERTEX_BUFFER_GUARD

#include <vector>
#include <string>

namespace SA::RND
{
	template <typename T>
	struct VertexComponent
	{
		std::string semantic;
		std::vector<T> data;
	};

	struct VertexComponentLayout
	{
		/// Semantic name
		std::string semantic;

		/**
		 * @brief Size of one element of component
		 * 
		 * ex: sizeof float, Vec2, Vec3...
		*/
		uint32_t size = 0u;
	};

	class RawVertexBuffer
	{
		std::vector<char> mData;
		std::vector<VertexComponentLayout> mLayouts;

		template <typename CompT, typename... Args>
		void CopyVertexComponentsToRawData(uint32_t vertexSize, uint32_t compOffset, VertexComponent<CompT>& _comp, Args&&... _args);

	public:
		const char* GetData() const;
		uint64_t GetDataSize() const;
		
		template <typename CompT, typename... Args>
		void BuildVertexBuffer(VertexComponent<CompT>&& _comp, Args&&... _args);

		void AppendDefines(std::vector<std::string>& _defines) const;
	};
}

#include "RawVertexBuffer.inl"

#endif // SAPPHIRE_RENDER_RAW_VERTEX_BUFFER_GUARD
