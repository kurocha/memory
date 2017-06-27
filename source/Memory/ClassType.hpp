//
//  ClassType.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Object.hpp"
#include "Pointer.hpp"

namespace Memory
{
	class ClassType
	{
	public:
		virtual ~ClassType();
		virtual bool is_class_of(const Pointer<Object> other) = 0;
	};

	/// Check whether a particular object implements a given class type.
	/// @example ClassType<MyObject>
	template <typename ClassT>
	class SpecificClassType : virtual public ClassType
	{
	public:
		virtual ~SpecificClassType() {}
		
		virtual bool is_class_of(const Pointer<Object> other)
		{
			return dynamic_cast<const ClassT*>(other.get()) != nullptr;
		}
	};
}
