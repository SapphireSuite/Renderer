// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_VERTICIES_GUARD
#define SAPPHIRE_RENDER_COMMON_VERTICIES_GUARD

#include <vector>

#include "VertexComponent.hpp"
#include "VertexPositionComponent.hpp"
#include "VertexNormalComponent.hpp"
#include "VertexTangentComponent.hpp"
#include "VertexBitangentComponent.hpp"
#include "VertexUVComponent.hpp"
#include "VertexColorComponent.hpp"

namespace SA::RND
{
	struct Verticies
	{
	private:
		std::vector<VertexComponent*> mComponents;

	public:
		inline ~Verticies()
		{
			Clear();
		}


		template <typename T>
		T* AddVertexComponent(std::initializer_list<typename T::DataT> _init)
		{
			T* const comp = new T(std::move(_init));

			mComponents.emplace_back(comp);

			return comp;
		}

		template <typename T>
		T* AddVertexComponent(std::vector<typename T::DataT>&& _data)
		{
			T* const comp = new T(std::move(_data));

			mComponents.emplace_back(comp);

			return comp;
		}


		inline bool RemoveVertexComponent(VertexComponent* _comp)
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


		template <typename T>
		T* GetVertexComponent()
		{
			for(auto comp : mComponents)
			{
				if(T* const cast = dynamic_cast<T*>(comp))
					return cast;
			}

			return nullptr;
		}

		template <typename T>
		const T* GetVertexComponent() const
		{
			return const_cast<Verticies&>(*this).GetVertexComponent<T>();
		}
	
		inline void Clear()
		{
			for(auto comp : mComponents)
				delete comp;

			mComponents.clear();
		}
	};
}

#endif // SAPPHIRE_RENDER_COMMON_VERTICIES_GUARD
