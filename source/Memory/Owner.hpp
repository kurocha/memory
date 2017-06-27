//
//  Owner.hpp
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
	class Owner : public Pointer<ObjectT>
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

		Owner& set(ObjectT * object) {
			clear();
			
			if (object) {
				this->_value = object;
				this->_value->retain();
			}
			
			return *this;
		}
		
		Owner() {}
		
		Owner(ObjectT * object) : Pointer<ObjectT>(object)
		{
			retain();
		}
		
		Owner(const Owner & other) : Pointer<ObjectT>(other.get())
		{
			retain();
		}
		
		template <typename OtherObjectT>
		Owner(const Owner<OtherObjectT> & other) : Pointer<ObjectT>(other.get())
		{
			retain();
		}
		
		~Owner()
		{
			clear();
		}
		
		Owner& operator=(const Owner & other)
		{
			return set(other.get());
		}
		
		template <typename OtherObjectT>
		Owner& operator=(const Owner<OtherObjectT> & other)
		{
			return set(other.get());
		}

		Owner& operator=(ObjectT * object)
		{
			return set(object);
		}
		
		template <typename OtherObjectT>
		Owner<OtherObjectT> as() const
		{
			return dynamic_cast<OtherObjectT*>(this->_value);
		}
	};

	template <typename ValueT>
	Owner<ValueT> own(ValueT* value)
	{
		return Owner<ValueT>(value);
	}

	template <typename ValueT, typename ...Arguments>
	inline static Owner<ValueT> owner(Arguments&& ...arguments)
	{
		return Owner<ValueT>(new ValueT(arguments...));
	}

	template <typename ObjectT>
	using Own = Owner<ObjectT>;
}
