// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Mesh/RawIndexBuffer.hpp>

#include <cstring>

#include <SA/Collections/Debug>

namespace SA::RND
{
	RawIndexBuffer::RawIndexBuffer(const std::vector<uint16_t>& _u16)
	{
		U16(_u16);
	}

	RawIndexBuffer::RawIndexBuffer(const std::vector<uint32_t>& _u32)
	{
		U32(_u32);
	}


	const uint16_t* RawIndexBuffer::U16() const
	{
		SA_ASSERT((Equals, mType, IndexBufferType::UINT16), SA.Render.Common, L"Query Index as invalid data type!");

		return reinterpret_cast<const uint16_t*>(mData.data());
	}

	const uint32_t* RawIndexBuffer::U32() const
	{
		SA_ASSERT((Equals, mType, IndexBufferType::UINT32), SA.Render.Common, L"Query Index as invalid data type!");
		
		return reinterpret_cast<const uint32_t*>(mData.data());
	}

	uint64_t RawIndexBuffer::GetDataSize() const
	{
		return mData.size();
	}

	void RawIndexBuffer::U16(const std::vector<uint16_t>& _u16)
	{
		mData.clear();

		mType = IndexBufferType::UINT16;

		mData.resize(_u16.size() * sizeof(uint16_t));
		std::memcpy(mData.data(), _u16.data(), mData.size());
	}

	void RawIndexBuffer::U32(const std::vector<uint32_t>& _u32)
	{
		bool bConvertToUint16 = false;

		// Less than UINT16_MAX value: convert to uint16
		if(_u32.size() < uint16_t(-1))
			bConvertToUint16 = true;

		// Shared indices could potentially make value < UINT16_MAX.
		else if(_u32.size() / 3 + 3 < uint16_t(-1))
		{
			bool bMaxReached = false;

			// Verify UINT16_MAX not reached.
			for(auto u : _u32)
			{
				if(u >= uint16_t(-1))
				{
					bMaxReached = true;
					break;
				}
			}

			if(!bMaxReached)
				bConvertToUint16 = true;
		}
		else
		{
			// Too many indices, even with shared indices: must use u32.
		}


		if(bConvertToUint16)
		{
			mType = IndexBufferType::UINT16;
			mData.resize(_u32.size() * sizeof(uint16_t));
		
			uint16_t* const u16Data = reinterpret_cast<uint16_t*>(mData.data());

			for(size_t i = 0; i < _u32.size(); ++i)
				u16Data[i] = static_cast<uint16_t>(_u32[i]);
		}
		else
		{
			mType = IndexBufferType::UINT32;
			mData.resize(_u32.size() * sizeof(uint32_t));
			std::memcpy(mData.data(), _u32.data(), mData.size());
		}
	}


	void RawIndexBuffer::Clear()
	{
		mData.clear();
	}
}
