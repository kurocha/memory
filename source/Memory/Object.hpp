//
//  Object.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <cstddef>

#include "SharedObject.hpp"
#include "Finalizer.hpp"

namespace Memory
{
	/// A reference counted object.
	class Object : virtual public SharedObject {
	private:
		Finalizer::List _finalizers;

	public:
		Object();
		virtual ~Object();
		
		Finalizer::List & finalizers() {return _finalizers;}
	};
}
