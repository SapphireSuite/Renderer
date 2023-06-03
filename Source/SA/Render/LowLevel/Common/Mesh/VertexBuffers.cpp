// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Mesh/Vertex/VertexBuffers.hpp>

namespace SA::RND
{
	VertexBuffers::~VertexBuffers()
	{
		Clear();
	}

	bool VertexBuffers::RemoveVertexComponent(VertexComponent* _comp)
	{
		for(auto it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			if(*it == _comp)
			{
				mComponents.erase(it);
				return true;
			}
		}

		return false;
	}

	void VertexBuffers::Clear()
	{
		for(auto comp : mComponents)
			delete comp;

		mComponents.clear();
	}

	VertexBuffers::iterator VertexBuffers::begin() { return mComponents.begin(); }
	VertexBuffers::const_iterator VertexBuffers::begin() const { return mComponents.begin(); }
	
	VertexBuffers::iterator VertexBuffers::end() { return mComponents.end(); }
	VertexBuffers::const_iterator VertexBuffers::end() const { return mComponents.end(); }

	void VertexBuffers::AppendDefines(std::vector<std::wstring>& _defines)
	{
		for(auto comp : mComponents)
			_defines.push_back(L"SA_HAS_"  + SA::ToWString(comp->GetComponentName()));
	}
}
