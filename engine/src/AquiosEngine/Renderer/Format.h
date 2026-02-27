#pragma once

namespace Aquios
{
	enum class Format
	{
		RGB8, RGBA8, D24S8,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		UByte4, UByte4N,
	};

	inline size_t get_fmt_bpp(Format fmt)
	{
		switch (fmt)
		{
		case Format::RGB8:
			return 3;
		case Format::RGBA8:
			return 4;
		case Format::D24S8:
			return 4;
		default:
			AQ_CORE_ERROR("Cannot get BPP for format type {}. Returning 0", (int)fmt);
			return 0;
		}
	}
}