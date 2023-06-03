// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_VERTEX_BUFFER_GUARD
#define SAPPHIRE_RENDER_COMMON_VERTEX_BUFFER_GUARD

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
	struct VertexBuffers
	{
	private:
		std::vector<VertexComponent*> mComponents;

	public:
		using iterator = std::vector<VertexComponent*>::iterator;
		using const_iterator = std::vector<VertexComponent*>::const_iterator;

		~VertexBuffers();


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


		inline bool RemoveVertexComponent(VertexComponent* _comp);


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
			return const_cast<VertexBuffers&>(*this).GetVertexComponent<T>();
		}
	
		void Clear();

		inline iterator begin();
		inline const_iterator begin() const;
		
		inline iterator end();
		inline const_iterator end() const;

		void AppendDefines(std::vector<std::wstring>& _defines);
	};
}

#endif // SAPPHIRE_RENDER_COMMON_VERTEX_BUFFER_GUARD
