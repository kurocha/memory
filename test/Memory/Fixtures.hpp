//
//  Mock.hpp
//  This file is part of the "Memory" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

namespace Memory
{
	class A
	{
	public:
		virtual ~A() {}
	};

	class B : public A
	{
	public:
		virtual ~B() {}
	};
}
