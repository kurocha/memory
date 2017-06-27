//
//  Finalizer.hpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

namespace Memory
{
	class Object;
	
	/// Provides weak reference semantic between objects.
	class Finalizer {
	public:
		virtual ~Finalizer();
		
		// Called when the object is going to be deleted.
		virtual void finalize(Object * object) = 0;
		
		struct Node {
			Node * next;
			Finalizer * finalizer;
		};
		
		struct List {
			Node * head = nullptr;
			
			void insert(Finalizer *);
			bool erase(Finalizer *);
			
			void finalize(Object * object);
		};
	};
}
