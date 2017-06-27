//
//  Test.SharedObject.cpp
//  This file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Memory/SharedObject.hpp>

namespace Memory
{
	UnitTest::Suite SharedObjectTestSuite {
		"Memory::SharedObject",
		
		{"it deletes the object when reference count falls to zero",
			[](UnitTest::Examiner & examiner) {
				auto shared_object = new SharedObject();
				
				examiner.expect(shared_object->reference_count()) == 0;
				
				shared_object->retain();
				examiner.expect(shared_object->reference_count()) == 1;
				
				shared_object->retain();
				examiner.expect(shared_object->reference_count()) == 2;
				
				examiner.expect(shared_object->release()) == false;
				examiner.expect(shared_object->reference_count()) == 1;
				
				examiner.expect(shared_object->release()) == true;
			}
		},
	};
}
