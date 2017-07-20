//
//  Owned.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Pointer.hpp"

namespace Memory
{
	template <typename ObjectT>
	class Owned : public Pointer<ObjectT>
	{
	private:
		void retain() {
			if (this->_value) {
				this->_value->retain();
			}
		}

	public:
		void clear() {
			if (this->_value) {
				this->_value->release();
				this->_value = nullptr;
			}
		}

		Owned& set(ObjectT * object) {
			clear();
			
			if (object) {
				this->_value = object;
				this->_value->retain();
			}
			
			return *this;
		}
		
		Owned() {}
		
		Owned(ObjectT * object) : Pointer<ObjectT>(object)
		{
			retain();
		}
		
		Owned(const Owned & other) : Pointer<ObjectT>(other.get())
		{
			retain();
		}
		
		template <typename OtherObjectT>
		Owned(const Owned<OtherObjectT> & other) : Pointer<ObjectT>(other.get())
		{
			retain();
		}
		
		~Owned()
		{
			clear();
		}
		
		Owned& operator=(const Owned & other)
		{
			return set(other.get());
		}
		
		template <typename OtherObjectT>
		Owned& operator=(const Owned<OtherObjectT> & other)
		{
			return set(other.get());
		}

		Owned& operator=(ObjectT * object)
		{
			return set(object);
		}
		
		template <typename OtherObjectT>
		Owned<OtherObjectT> as() const
		{
			return dynamic_cast<OtherObjectT*>(this->_value);
		}
	};

	template <typename ValueT>
	Owned<ValueT> own(ValueT* value)
	{
		return Owned<ValueT>(value);
	}

	template <typename ValueT, typename ...Arguments>
	inline static Owned<ValueT> owned(Arguments&& ...arguments)
	{
		return Owned<ValueT>(new ValueT(arguments...));
	}

	template <typename ObjectT>
	using Own = Owned<ObjectT>;
}
