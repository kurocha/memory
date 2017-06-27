//
//  Test.ClassType.cpp
//  This file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Memory/ClassType.hpp>
#include <Memory/Owner.hpp>
#include <Memory/Object.hpp>

namespace Memory
{
	class MyObject : public Object
	{
	public:
		virtual ~MyObject() {}
	};
	
	UnitTest::Suite ClassTypeTestSuite {
		"Memory::ClassType",
		
		{"it can detect instances of object",
			[](UnitTest::Examiner & examiner) {
				SpecificClassType<Object> class_type;
				auto object = owner<Object>();
				
				examiner.expect(class_type.is_class_of(object)) == true;
			}
		},
		
		// {"it can detect instances derived from object",
		// 	[](UnitTest::Examiner & examiner) {
		// 		SpecificClassType<MyObject> class_type;
		// 		Owner<Object> object = owner<MyObject>();
		// 		
		// 		examiner.expect(class_type.is_class_of(object)) == true;
		// 	}
		// },
	};
}
