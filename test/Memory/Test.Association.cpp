//
//  Test.Association.cpp
//  This file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Memory/Owner.hpp>
#include <Memory/Object.hpp>
#include <Memory/Association.hpp>

namespace Memory
{
	UnitTest::Suite AssociationTestSuite {
		"Memory::Association",
		
		{"it clears weak reference after object is deallocated",
			[](UnitTest::Examiner & examiner) {
				auto object = owner<Object>();
				auto association = weak(object);
				
				examiner.expect(association.get()) == object.get();
				
				object = nullptr;
				
				examiner.expect(association.get()) == nullptr;
			}
		},
	};
}
