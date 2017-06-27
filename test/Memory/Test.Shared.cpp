//
//  Test.Shared.cpp
//  This file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Memory/Shared.hpp>
#include "Fixtures.hpp"

namespace Memory
{
	UnitTest::Suite SharedTestSuite {
		"Memory::Shared",
		
		{"it allocates and releases an object",
			[](UnitTest::Examiner & examiner) {
				auto value = shared<int>(10);
				examiner.expect(*value) == 10;
			}
		},
		
		{"it can dynamic_cast one a base object to a derived object",
			[](UnitTest::Examiner & examiner) {
				auto b = shared<B>();
				
				examiner.expect(b.get()) != nullptr;
				
				Shared<A> a = b;
				
				examiner.expect(a.get()) != nullptr;
				
				Shared<B> bb = a.as<B>();
				
				examiner.expect(bb.get()) == b.get();
			}
		}
	};
}
