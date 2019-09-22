//
//  Member.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

namespace Memory
{
	namespace Member
	{
		/// This function returns the offset of a member of a class/struct.
		/// @example Member::offset(&VertexData::color)
		template <class T, typename U>
		constexpr std::ptrdiff_t offset(U T::* member) noexcept
		{
			return reinterpret_cast<std::ptrdiff_t>(&(reinterpret_cast<T const volatile*>(0)->*member));
		}
	}
}
