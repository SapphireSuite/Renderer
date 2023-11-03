// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

namespace SA::RND
{
	namespace Intl
	{
#if SA_DEBUG
		// Checks all components have the same number of elements (data.size()).
		template <typename CompT, typename... Args>
		void CheckVertexComponentsElementSize(uint32_t _size, VertexComponent<CompT>& _comp, Args&&... _args)
		{
			if(_size == uint32_t(-1))
				_size = _comp.data.size();

			SA_ERROR(_comp.data.size() == _size, SA.Render,
				(L"Vertex Component with [%1] elements does not match previous component with [%2] elements", _comp.data.size(), _size));

			if constexpr (sizeof...(Args) > 0)
				CheckVertexComponentsElementSize(_size, _args...);
		}
#endif

		template <typename CompT, typename... Args>
		uint32_t SumVertexComponentsElementSize(VertexComponent<CompT>& _comp, Args&&... _args)
		{
			uint32_t compElemSize = sizeof(CompT);

			if constexpr(sizeof...(Args) > 0)
				return compElemSize + SumVertexComponentsElementSize(_args...);

			return compElemSize;
		}
	}

	template <typename CompT, typename... Args>
	void RawVertexBuffer::CopyVertexComponentsToRawData(uint32_t vertexSize, uint32_t compOffset, VertexComponent<CompT>& _comp, Args&&... _args)
	{
		SA_ERROR((!_comp.semantic.empty()), SA.Render, L"Component has empty semantic name!");

		VertexComponentLayout& layout = mLayouts.emplace_back();
		layout.semantic = _comp.semantic;
		layout.size = sizeof(CompT);

		// Emplace data
		for(int i = 0; i < _comp.data.size(); ++i)
		{
			new(&mData[i * vertexSize + compOffset]) CompT{_comp.data[i]};
		}

		if constexpr (sizeof...(Args) > 0)
			CopyVertexComponentsToRawData(vertexSize, compOffset + sizeof(CompT), _args...);
	}

	template <typename CompT, typename... Args>
	void RawVertexBuffer::BuildVertexBuffer(VertexComponent<CompT>&& _comp, Args&&... _args)
	{
#if SA_DEBUG
		Intl::CheckVertexComponentsElementSize(uint32_t(-1), _comp, _args...);
#endif

		const uint32_t vertexSize = Intl::SumVertexComponentsElementSize(_comp, _args...);

		// Same data.size() for all elements
		mData.resize(_comp.data.size() * vertexSize);
		mLayouts.reserve(sizeof...(Args) + 1);

		CopyVertexComponentsToRawData(vertexSize, 0u, _comp, _args...);
	}
}