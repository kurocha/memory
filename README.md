# Memory

Provides shared pointers and ownership semantics.

[![Build Status](https://travis-ci.org/kurocha/memory.svg?branch=master)](https://travis-ci.org/kurocha/memory)

## Setup

Firstly the build tool `teapot` needs to be installed (which requires [Ruby][2]):
 
	$ gem install teapot

To fetch all dependencies, run:

	$ teapot fetch

[2]: http://www.ruby-lang.org/en/downloads/

## Usage

To run unit tests:

	$ teapot Test/Memory

### `Memory::Object`

This is the most efficient intrusive pointer.

```c++
class MyObject : public Memory::Object
{
};

auto o = Memory::reference<MyObject>();
```

An instance of `Memory::Object` supports the concept of finalizers. This allows you to register callbacks which will be invoked when the object is destroyed. This can be used to implement `Memory::Association` and `Memory::ObjectCache` which are both kinds of weak references.

### `Memory::Shared`

```c++
auto i = Memory::shared<int>(10);
```

## Contributing

1. Fork it.
2. Create your feature branch (`git checkout -b my-new-feature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin my-new-feature`).
5. Create new Pull Request.

## License

Released under the MIT license.

Copyright, 2017, by [Samuel G. D. Williams](http://www.codeotaku.com/samuel-williams).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
