//
//  Shared.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <iostream>

#include "Owned.hpp"
#include "SharedObject.hpp"

#include <cassert>

namespace Memory
{
	template <typename ValueT>
	class Shared {
	protected:
		template <typename> friend class Shared;
		
		class Allocation : public SharedObject
		{
		public:
			ValueT value;
			
			template <typename ...Arguments>
			Allocation(Arguments&& ...arguments) : value(arguments...) {}
			
			virtual ~Allocation() {}
		};
		
		Owned<SharedObject> _allocation;
		ValueT * _value = nullptr;
		
		Shared(Allocation * allocation)
		{
			_allocation = allocation;
			_value = &allocation->value;
		}
		
		Shared(Pointer<SharedObject> allocation, ValueT * value)
		{
			_allocation = allocation;
			_value = value;
		}
		
	public:
		Shared() {}
		
		// The default copy constructor and operator= are sufficient.
		
		template <typename OtherValueT>
		Shared(Shared<OtherValueT> other)
		{
			_allocation = other._allocation;
			_value = other._value;
		}
		
		~Shared() {}
		
		ValueT * get() const
		{
			assert(_value != nullptr);
			
			return _value;
		}
		
		/// Copy operator. Doesn't modify reference count.
		template <typename OtherSharedT>
		Shared & operator=(const OtherSharedT & other)
		{
			_allocation = other._allocation;
			_value = other._value;
			
			return *this;
		}
		
		ValueT* operator->() const {
			assert(_value != nullptr);
			
			return _value;
		}
		
		ValueT& operator*() const {
			assert(_value != nullptr);
			
			return *_value;
		}
		
		explicit operator bool() const
		{
			return _value != nullptr;
		}
		
		bool operator==(const Shared & other) const
		{
			return _value == other._value;
		}
		
		bool operator!=(const Shared & other) const
		{
			return _value != other._value;
		}
		
		bool operator<(const Shared & other) const
		{
			return _value < other._value;
		}
		
		bool operator>(const Shared & other) const
		{
			return _value > other._value;
		}
		
		bool operator<=(const Shared & other) const
		{
			return _value <= other._value;
		}
		
		bool operator>=(const Shared & other) const
		{
			return _value >= other._value;
		}
		
		template <typename OtherValueT>
		Shared<OtherValueT> as() const {
			auto value = dynamic_cast<OtherValueT*>(_value);
			
			if (value) {
				return Shared<OtherValueT>(_allocation.get(), value);
			} else {
				return Shared<OtherValueT>();
			}
		}
		
		template <typename ...Arguments>
		inline static Shared<ValueT> make(Arguments&& ...arguments) {
			return new Allocation(arguments...);
		}
	};
	
	/// Convenient helper.
	template <typename ValueT, typename ...Arguments>
	inline static Shared<ValueT> shared(Arguments&& ...arguments)
	{
		return Shared<ValueT>::make(arguments...);
	}
}
