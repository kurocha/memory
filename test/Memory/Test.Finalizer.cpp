//
//  Test.Finalizer.cpp
//  This file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Memory/Finalizer.hpp>
#include <Memory/Object.hpp>
#include <Memory/Owner.hpp>

namespace Memory
{
	class CountingFinalizer : virtual public Finalizer {
	public:
		std::size_t count = 0;
		
		virtual void finalize(Object * object)
		{
			count += 1;
		}
	};
	
	UnitTest::Suite FinalizerTestSuite {
		"Memory::Finalizer",
		
		{"it invokes the finalizer",
			[](UnitTest::Examiner & examiner) {
				CountingFinalizer finalizer;
				
				{
					auto object = owner<Object>();
					object->finalizers().insert(&finalizer);
				}
				
				examiner.expect(finalizer.count) == 1;
			}
		},
		
		{"it can remove the finalizer",
			[](UnitTest::Examiner & examiner) {
				CountingFinalizer finalizer;
				
				{
					auto object = owner<Object>();
					object->finalizers().insert(&finalizer);
					object->finalizers().erase(&finalizer);
				}
				
				examiner.expect(finalizer.count) == 0;
			}
		},
	};
}
