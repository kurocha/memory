//
//  Test.Pointer.cpp
//  This file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Memory/Pointer.hpp>
#include "Fixtures.hpp"

namespace Memory
{
	UnitTest::Suite PointerTestSuite {
		"Memory::Pointer",
		
		{"it can construct a pointer",
			[](UnitTest::Examiner & examiner) {
				int i = 10;
				
				auto p = pointer(&i);
				
				examiner.expect(*p) == 10;
			}
		},
		
		{"it can upcast a pointer",
			[](UnitTest::Examiner & examiner) {
				B object;
				
				auto b = pointer(&object);
				auto a = Pointer<A>(b);
				
				examiner.expect(a.get()) == static_cast<A*>(&object);
			}
		},
		
		{"it can downcast a pointer",
			[](UnitTest::Examiner & examiner) {
				B object;
				
				auto a = Pointer<A>(&object);
				auto b = a.as<B>();
				
				examiner.expect(b.get()) == &object;
			}
		},
	};
}
