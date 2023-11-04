// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_RAW_INDEX_BUFFER_GUARD
#define SAPPHIRE_RENDER_COMMON_RAW_INDEX_BUFFER_GUARD

#include <vector>
#include <cstdint>

namespace SA::RND
{
	enum class IndexBufferType
	{
		UINT16,

		UINT32,
	};

	class RawIndexBuffer
	{
		std::vector<char> mData;
		IndexBufferType mType = IndexBufferType::UINT16;

	public:
		RawIndexBuffer() = default;
		RawIndexBuffer(const std::vector<uint16_t>& _u16);
		RawIndexBuffer(const std::vector<uint32_t>& _u32);


		/// Getter as U16
		const uint16_t* U16() const;

		/// Getter as U32
		const uint32_t* U32() const;

		uint64_t GetDataSize() const;
		uint32_t GetIndexCount() const;

		IndexBufferType GetIndexBufferType() const;

		/// Setter from U16 values
		void U16(const std::vector<uint16_t>& _u16);

		/// Setter from U32 values
		void U32(const std::vector<uint32_t>& _u32);


		void Clear();
	};
}

#endif // SAPPHIRE_RENDER_COMMON_RAW_INDEX_BUFFER_GUARD
