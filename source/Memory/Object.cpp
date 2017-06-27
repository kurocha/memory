//
//  Object.cpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Object.hpp"

namespace Memory
{
	Object::Object() {
	}

	Object::~Object () {
		_finalizers.finalize(this);
	}
}
