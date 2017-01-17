find_path(GTEST_ROOT src/gtest.cc
   /usr/src/googletest/googletest
   /usr/src/gtest
)
find_package(GTest)
set(GTEST_DEPENDENCIES)

if(NOT GTEST_FOUND AND EXISTS ${GTEST_ROOT})
   include(ExternalProject)
   ExternalProject_Add(gtest PREFIX ./gtest
                             SOURCE_DIR ${GTEST_ROOT}
                             INSTALL_COMMAND true)

   link_directories(${CMAKE_CURRENT_BINARY_DIR}/gtest/src/gtest-build)

   set(GTEST_LIBRARIES "-lgtest")
   set(GTEST_DEPENDENCIES "gtest")
   set(GTEST_FOUND TRUE)
   find_path(GTEST_INCLUDE_DIRS NAMES gtest/gtest.h)

   message(STATUS "Found GTest at ${GTEST_ROOT}, headers at ${GTEST_INCLUDE_DIRS}")
endif()

if(GTEST_FOUND)
   # Definition of the C++ files used (alphabetical order per group)
   set(files
      # Runner
       "gtest_runner.cc"
       # Helpers
       "file-helpers.cc"
       # Tests
       "acqprogress_test.cc"
       "cachefilter_test.cc"
       "cdrom_test.cc"
       "cdromfindpackages_test.cc"
       "commandline_test.cc"
       "compareversion_test.cc"
       "configuration_test.cc"
       "extracttar_test.cc"
       "fileutl_test.cc"
       "getarchitectures_test.cc"
       "getlanguages_test.cc"
       "getlistoffilesindir_test.cc"
       "globalerror_test.cc"
       "hashsums_test.cc"
       "indexcopytosourcelist_test.cc"
       "install_progress_test.cc"
       "openmaybeclearsignedfile_test.cc"
       "parsedepends_test.cc"
       "priority_test.cc"
       "sourcelist_test.cc"
       "srvrecs_test.cc"
       "stringview_test.cc"
       "strutil_test.cc"
       "tagfile_test.cc"
       "tagsection_test.cc"
       "teestream_test.cc"
       "uri_test.cc"
   )
   add_executable(libapt_test ${files})
   target_include_directories(libapt_test PRIVATE ${GTEST_INCLUDE_DIRS})
   target_link_libraries(libapt_test ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} apt-private apt-inst)
   if (GTEST_DEPENDENCIES)
      add_dependencies(libapt_test ${GTEST_DEPENDENCIES})
   endif()
   add_test(NAME AptTests
            COMMAND libapt_test
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
