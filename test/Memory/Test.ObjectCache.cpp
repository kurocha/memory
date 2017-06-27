//
//  Test.ObjectCache.cpp
//  This file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Memory/Owner.hpp>
#include <Memory/ObjectCache.hpp>

namespace Memory
{
	UnitTest::Suite ObjectCacheTestSuite {
		"Memory::ObjectCache",
		
		{"it should remove dependent object",
			[](UnitTest::Examiner & examiner) {
				ObjectCache<int> object_cache;
				
				{
					auto object = owner<Object>();
				
					object_cache.insert({object, 10});
					
					examiner.expect(object_cache.size()) == 1;
				}
				
				examiner.expect(object_cache.size()) == 0;
			}
		},
	};
}
