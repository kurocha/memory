
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "3.0"

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
	target.depends "Language/C++14"
	
	target.provides "Library/Memory" do
		source_root = target.package.path + 'source'
		
		library_path = build static_library: "Memory", source_files: source_root.glob('Memory/**/*.cpp')
		
		append linkflags library_path
		append header_search_paths source_root
	end
end

define_target "memory-tests" do |target|
	target.depends "Language/C++14"
	
	target.depends "Library/UnitTest"
	target.depends "Library/Memory"
	
	target.provides "Test/Memory" do |*arguments|
		test_root = target.package.path + 'test'
		
		run tests: "Memory", source_files: test_root.glob('Memory/**/*.cpp'), arguments: arguments
	end
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
