//
//  ObjectCache.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <unordered_map>

#include "Object.hpp"

namespace Memory
{
	/// Implements a simple weak-key value storage container which is typically useful for handling decoupled state, e.g. a cache.
	template <typename ValueT>
	class ObjectCache : virtual protected Finalizer {
	public:
		typedef std::unordered_map<Object *, ValueT> CacheMapT;

	protected:
		CacheMapT _cache;

		virtual void finalize(Object * object) {
			_cache.erase(object);
		}

	public:
		typedef typename CacheMapT::iterator iterator;
		typedef typename CacheMapT::const_iterator const_iterator;
		typedef typename CacheMapT::value_type value_type;

		virtual ~ObjectCache() {
			// We need to remove ourselves from the list of finalizers for each
			for (auto node : _cache) {
				node.first->finalizers().erase(this);
			}
		}

		void insert(const value_type & value) {
			_cache.insert(value);
			
			value.first->finalizers().insert(this);
		}

		iterator find(Object * key) {
			return _cache.find(key);
		}

		const CacheMapT & objects() const {
			return _cache;
		}
		
		std::size_t size() const {
			return _cache.size();
		}
	};
}
