//
//  SharedObject.cpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "SharedObject.hpp"

namespace Memory
{
	SharedObject::SharedObject() : _count(0) 
	{
	}

	SharedObject::SharedObject(const SharedObject & other) : _count(0) {
	}

	SharedObject & SharedObject::operator=(const SharedObject & other) {
		// Don't copy the reference count.
		return *this;
	}

	SharedObject::~SharedObject() {
	}

	void SharedObject::retain() const {
		_count.fetch_add(1);
	}

	bool SharedObject::release() const {
		// Returns the value before subtracting 1:
		NumberT count = _count.fetch_sub(1);
		
		if (count == 1) {
			delete this;
			
			return true;
		}

		return false;
	}
	
	SharedObject::NumberT SharedObject::reference_count() const {
		return _count.load();
	}
}
