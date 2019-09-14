//
//  SharedObject.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <atomic>

namespace Memory
{
	class SharedObject {
	public:
		typedef uint32_t NumberT;
	protected:
		/// The number of references to this instance.
		mutable std::atomic<NumberT> _count;

	public:
		/// Default constructor. Sets the reference count to 0.
		SharedObject();
		
		/// Default copy constructor. Sets the reference count of this object to 0.
		SharedObject(const SharedObject & other);
		
		/// Copy operator. Doesn't modify reference count.
		SharedObject & operator=(const SharedObject & other);
		
		virtual ~SharedObject() noexcept;
		
		NumberT reference_count() const;
		
		/// Increase the reference count by 1.
		void retain() const;

		/// Decrement the reference count by 1 and invoke `delete this` if it became 0.
		/// @returns true if the object has been deleted was invoked.
		bool release() const;
	};
}
