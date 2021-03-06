//
//  Test.Owned.cpp
//  This file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Memory/Object.hpp>
#include <Memory/Owned.hpp>

namespace Memory
{
	UnitTest::Suite OwnedTestSuite {
		"Memory::Owned",
		
		{"it should increment reference count",
			[](UnitTest::Examiner & examiner) {
				auto object = owned<Object>();
				
				examiner.expect(object.get()) != nullptr;
				examiner.expect(object->reference_count()) == 1;
			}
		},
	};
}
