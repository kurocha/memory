
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "1.3"

define_project "Memory" do |project|
	project.add_author "Samuel Williams"
	project.license = "MIT License"

	project.version = "1.0.0"
end


define_target "memory" do |target|
	target.build do |environment|
		source_root = target.package.path + 'source'
		
		copy headers: source_root.glob('Memory/**/*.hpp')
		
		build static_library: "Memory", source_files: source_root.glob('Memory/**/*.cpp')
	end
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.provides "Library/Memory" do
		append linkflags ->{install_prefix + "lib/libMemory.a"}
	end
end

define_target "memory-tests" do |target|
	target.build do |environment|
		test_root = target.package.path + 'test'
		
		run tests: "Memory", source_files: test_root.glob('Memory/**/*.cpp')
	end
	
	target.depends "Language/C++11", private: true
	
	target.depends "Library/UnitTest"
	target.depends "Library/Memory"
	
	target.provides "Test/Memory"
end

define_configuration "test" do |configuration|
	configuration[:source] = "http://github.com/kurocha/"
	
	configuration.require "platforms"
	configuration.require "build-files"
	
	configuration.require "unit-test"
	
	configuration.require "language-cpp-class"
end
