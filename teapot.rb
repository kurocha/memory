
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "1.3"

# Project Metadata

define_project "memory" do |project|
	project.title = 'Memory'
	project.summary = 'Provides shared pointers and ownership semantics.'
	
	project.license = "MIT License"
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = "1.0.0"
end

# Build Targets

define_target 'memory-library' do |target|
	target.build do
		source_root = target.package.path + 'source'
		
		copy headers: source_root.glob('Memory/**/*.hpp')
		
		build static_library: "Memory", source_files: source_root.glob('Memory/**/*.cpp')
	end
	
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.provides "Library/Memory" do
		append linkflags [
			->{install_prefix + 'lib/libMemory.a'},
		]
	end
end

define_target "memory-tests" do |target|
	target.build do |*arguments|
		test_root = target.package.path + 'test'
		
		run tests: "Memory", source_files: test_root.glob('Memory/**/*.cpp'), arguments: arguments
	end
	
	target.depends "Language/C++11", private: true
	
	target.depends "Library/UnitTest"
	target.depends "Library/Memory"
	
	target.provides "Test/Memory"
end

# Configurations

define_configuration "memory" do |configuration|
	configuration[:source] = "http://github.com/kurocha/"
	
	# Provides all the build related infrastructure:
	configuration.require 'platforms'
	
	# Provides unit testing infrastructure and generators:
	configuration.require 'unit-test'
	
	# Provides some useful C++ generators:
	configuration.require "generate-project"
	configuration.require "generate-travis"
	configuration.require "generate-cpp-class"
end
