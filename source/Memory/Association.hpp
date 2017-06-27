//
//  Association.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Pointer.hpp"
#include "Finalizer.hpp"

namespace Memory
{
	// An association maintains a weak reference with a given object.
	template <typename ObjectT>
	class Association : public Pointer<ObjectT>, virtual public Finalizer
	{
	private:
		void associate()
		{
			// Calling this function more than once may cause memory related crashes.
			if (this->_value)
				this->_value->finalizers().insert(this);
		}

	public:
		virtual void finalize(Object * object)
		{
			this->_value = nullptr;
		}
		
		void clear()
		{
			if (this->_value) {
				this->_value->finalizers().erase(this);
				this->_value = nullptr;
			}
		}

		Association& set(ObjectT * object)
		{
			clear();

			if (object) {
				object->finalizers().insert(this);
				this->_value = object;
			}

			return *this;
		}

		Association() {}

		Association(ObjectT * object) : Pointer<ObjectT>(object)
		{
			associate();
		}

		Association(const Association& other) : Pointer<ObjectT>(other.get())
		{
			associate();
		}

		template <typename OtherObjectT>
		Association(const Pointer<OtherObjectT> & other) : Pointer<ObjectT>(other.get())
		{
			associate();
		}

		Association& operator=(const Association & other)
		{
			return set(other.get());
		}

		template <typename OtherObjectT>
		Association& operator=(const Pointer<OtherObjectT> & other)
		{
			return set(other.get());
		}

		Association& operator=(ObjectT * object)
		{
			return set(object);
		}

		template <typename OtherObjectT>
		Association& operator=(OtherObjectT * object)
		{
			return set(dynamic_cast<ObjectT *>(object));
		}

		~Association()
		{
			clear();
		}
	};
	
	/// Convenient helper.
	template <typename ObjectT>
	inline static Association<ObjectT> weak(Pointer<ObjectT> object)
	{
		return Association<ObjectT>(object);
	}
}
