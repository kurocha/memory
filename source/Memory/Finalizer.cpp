//
//  Finalizer.cpp
//  File file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Finalizer.hpp"

namespace Memory
{
	Finalizer::~Finalizer()
	{
	}
	
	void Finalizer::List::insert(Finalizer * finalizer)
	{
		Node * node = new Node;

		node->finalizer = finalizer;
		node->next = head;

		head = node;
	}
	
	bool Finalizer::List::erase(Finalizer * finalizer)
	{
		Node ** previous = &head;
		Node * current = head;

		// It may be possible to improve upon this approach since it is a linear scan.
		while (current) {
			if (current->finalizer == finalizer) {
				*previous = current->next;

				delete current;

				return true;
			}

			previous = &(current->next);
			current = current->next;
		}

		return false;
	}
	
	void Finalizer::List::finalize(Object * object)
	{
		Node * current = head;
		
		while (current) {
			if (current->finalizer)
				current->finalizer->finalize(object);

			Node * next = current->next;

			delete current;
			current = next;
		}
	}
}
