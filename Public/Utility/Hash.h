/** Hash.h
*
* Implementation of hashing functions.
*
* FNV-1a hash constants from http://www.isthe.com/chongo/tech/comp/fnv/
* FNV-1a implementation based on http://create.stephan-brumme.com/fnv-hash/
*/
#pragma once

#include <stdint.h>
#include "Utility/Types.h"

namespace ETL
{
namespace Utility
{
namespace Hash
{
	const uint32 kPrime32 = 0x1000193;
	const uint32 kSeed32 = 0x811C9DC5;
	const uint64 kPrime64 = 0x100000001B3;
	const uint64 kSeed64 = 0x14650FB0739D0383;

	inline uint32 FNV32(byte data, uint32 hash = kSeed32)
	{
		return (data ^ hash) * kPrime32;
	}

	inline uint32 FNV32(const byte* data, size_t dataSize, uint32 hash = kSeed32)
	{
		while (dataSize--)
			hash = FNV32(*data++, hash);
		return hash;
	}

	inline uint32 FNV32(const char* data, size_t dataSize, uint32 hash = kSeed32)
	{
		return FNV32((byte*)data, dataSize, hash);
	}

	inline uint32 FNV32(const wchar_t* data, size_t dataSize)
	{
		return FNV32((byte*)data, dataSize);
	}

	inline uint32 FNV32(const char16_t* data, size_t dataSize)
	{
		return FNV32((byte*)data, dataSize);
	}

	inline uint32 FNV32(const WideString& str)
	{
		return FNV32(str.c_str(), str.length() * sizeof(wchar_t));
	}

	inline uint32 FNV32(const MbString& str)
	{
		return FNV32(str.c_str(), str.length() * sizeof(char));
	}

	inline uint32 FNV32(const Wide16String& str)
	{
		return FNV32(str.c_str(), str.length() * sizeof(char16_t));
	}

	inline uint64 FNV64(byte data, uint64 hash = kSeed64)
	{
		return (data ^ hash) * kPrime64;
	}

	inline uint64 FNV64(const byte* data, size_t dataSize, uint64 hash = kSeed64)
	{
		while (dataSize--)
			hash = FNV64(*data++, hash);
		return hash;
	}

	inline uint64 FNV64(const char* data, size_t dataSize, uint64 hash = kSeed64)
	{
		return FNV64((byte*)data, dataSize, hash);
	}

	inline uint64 FNV64(const wchar_t* data, size_t dataSize)
	{
		return FNV64((byte*)data, dataSize);
	}

	inline uint64 FNV64(const char16_t* data, size_t dataSize)
	{
		return FNV64((byte*)data, dataSize);
	}

	inline uint64 FNV64(const EtlString& str)
	{
		return FNV64(str.c_str(), str.length() * sizeof(EtlChar));
	}

	inline uint64 FNV64(const MbString& str)
	{
		return FNV64(str.c_str(), str.length() * sizeof(char));
	}

	inline uint64 FNV64(const Wide16String& str)
	{
		return FNV64(str.c_str(), str.length() * sizeof(char16_t));
	}
}
}
}