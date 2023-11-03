// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Mesh/RawVertexBuffer.hpp>

namespace SA::RND
{
	const char* RawVertexBuffer::GetData() const
	{
		return mData.data();
	}

	uint64_t RawVertexBuffer::GetDataSize() const
	{
		return mData.size();
	}

	void RawVertexBuffer::AppendDefines(std::vector<std::string>& _defines) const
	{
		for(auto& layout : mLayouts)
		{
			if(!layout.semantic.empty())
				_defines.push_back("SA_HAS_" + layout.semantic);
		}
	}
}
