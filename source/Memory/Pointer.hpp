//
//  Pointer.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 3/10/2009.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <type_traits>
#include <cassert>

namespace Memory
{
	template <typename ValueT>
	class Pointer {
	protected:
		ValueT * _value = nullptr;

	public:
		Pointer() {}

		Pointer(ValueT * value) : _value(value) {}

		ValueT * operator->() const
		{
			assert(_value != nullptr);
			
			return _value;
		}

		ValueT & operator*() const
		{
			assert(_value != nullptr);
			
			return *_value;
		}

		bool operator==(const Pointer & other) const
		{
			return _value == other._value;
		}

		bool operator!=(const Pointer & other) const
		{
			return _value != other._value;
		}

		bool operator<(const Pointer & other) const
		{
			return _value < other._value;
		}

		bool operator>(const Pointer & other) const
		{
			return _value > other._value;
		}

		bool operator<=(const Pointer & other) const
		{
			return _value <= other._value;
		}

		bool operator>=(const Pointer & other) const
		{
			return _value >= other._value;
		}

		ValueT * get() const
		{
			return _value;
		}

		explicit operator bool() const
		{
			return _value ? true : false;
		}

		operator ValueT *() const
		{
			return _value;
		}
		
		template <typename OtherValueT>
		Pointer<OtherValueT> as() const {
			return dynamic_cast<OtherValueT*>(_value);
		}
	};

	template <typename ValueT>
	Pointer<ValueT> pointer(ValueT* value) {
		return Pointer<ValueT>(value);
	}

	template <typename ValueT>
	using Ptr = Pointer<ValueT>;
}
