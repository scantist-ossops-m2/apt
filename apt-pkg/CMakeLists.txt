# Include apt-pkg directly, as some files have #include <system.h>
include_directories(${PROJECT_BINARY_DIR}/include/apt-pkg)

add_definitions("-DAPT_PKG_EXPOSE_STRING_VIEW")

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include/apt-pkg/)
execute_process(COMMAND ${PERL_EXECUTABLE} ${PROJECT_SOURCE_DIR}/triehash/triehash.pl
                        --ignore-case
                         --header ${PROJECT_BINARY_DIR}/include/apt-pkg/tagfile-keys.h
                         --code ${CMAKE_CURRENT_BINARY_DIR}/tagfile-keys.cc
                         --enum-class
                         --enum-name pkgTagSection::Key
                         --function-name pkgTagHash
                         --include "<apt-pkg/tagfile.h>"
                         ${CMAKE_CURRENT_SOURCE_DIR}/tagfile-keys.list)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "tagfile-keys.list")


# Set the version of the library
execute_process(COMMAND awk -v ORS=. "/^\#define APT_PKG_M/ {print \$3}"
                COMMAND sed "s/\\.\$//"
                INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/contrib/macros.h
                OUTPUT_VARIABLE MAJOR OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND grep "^#define APT_PKG_RELEASE"
                COMMAND cut -d " " -f 3
                INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/contrib/macros.h
                OUTPUT_VARIABLE MINOR OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "Building libapt-pkg ${MAJOR} (release ${MINOR})")
set(APT_PKG_MAJOR ${MAJOR} PARENT_SCOPE) # exporting for methods/CMakeLists.txt

# Definition of the C++ files used (alphabetical order)
set(library
    "acquire-item.cc"
    "acquire-method.cc"
    "acquire-worker.cc"
    "acquire.cc"
    "algorithms.cc"
    "aptconfiguration.cc"
    "cachefile.cc"
    "cachefilter.cc"
    "cacheset.cc"
    "cdrom.cc"
    "clean.cc"
    "contrib/cdromutl.cc"
    "contrib/cmndline.cc"
    "contrib/configuration.cc"
    "contrib/crc-16.cc"
    "contrib/error.cc"
    "contrib/fileutl.cc"
    "contrib/gpgv.cc"
    "contrib/hashes.cc"
    "contrib/hashsum.cc"
    "contrib/md5.cc"
    "contrib/mmap.cc"
    "contrib/netrc.cc"
    "contrib/progress.cc"
    "contrib/proxy.cc"
    "contrib/sha1.cc"
    "contrib/sha2_internal.cc"
    "contrib/srvrec.cc"
    "contrib/strutl.cc"
    "deb/debindexfile.cc"
    "deb/deblistparser.cc"
    "deb/debmetaindex.cc"
    "deb/debrecords.cc"
    "deb/debsrcrecords.cc"
    "deb/debsystem.cc"
    "deb/debversion.cc"
    "deb/dpkgpm.cc"
    "depcache.cc"
    "edsp.cc"
    "edsp/edspindexfile.cc"
    "edsp/edsplistparser.cc"
    "edsp/edspsystem.cc"
    "indexcopy.cc"
    "indexfile.cc"
    "init.cc"
    "install-progress.cc"
    "metaindex.cc"
    "orderlist.cc"
    "packagemanager.cc"
    "pkgcache.cc"
    "pkgcachegen.cc"
    "pkgrecords.cc"
    "pkgsystem.cc"
    "policy.cc"
    "prettyprinters.cc"
    "sourcelist.cc"
    "srcrecords.cc"
    "statechanges.cc"
    "tagfile-compat.cc"
    "tagfile.cc"
    "update.cc"
    "upgrade.cc"
    "version.cc"
    "versionmatch.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/tagfile-keys.cc"
)
set(headers
    "acquire-item.h"
    "acquire-method.h"
    "acquire-worker.h"
    "acquire.h"
    "algorithms.h"
    "aptconfiguration.h"
    "cachefile.h"
    "cachefilter.h"
    "cacheiterators.h"
    "cacheset.h"
    "cdrom.h"
    "clean.h"
    "contrib/cdromutl.h"
    "contrib/cmndline.h"
    "contrib/configuration.h"
    "contrib/crc-16.h"
    "contrib/error.h"
    "contrib/fileutl.h"
    "contrib/gpgv.h"
    "contrib/hashes.h"
    "contrib/hashsum_template.h"
    "contrib/macros.h"
    "contrib/md5.h"
    "contrib/mmap.h"
    "contrib/netrc.h"
    "contrib/progress.h"
    "contrib/proxy.h"
    "contrib/sha1.h"
    "contrib/sha2.h"
    "contrib/sha256.h"
    "contrib/sha2_internal.h"
    "contrib/sptr.h"
    "contrib/srvrec.h"
    "contrib/string_view.h"
    "contrib/strutl.h"
    "contrib/weakptr.h"
    "deb/debarchtuple.h"
    "deb/debindexfile.h"
    "deb/deblistparser.h"
    "deb/debmetaindex.h"
    "deb/debrecords.h"
    "deb/debsrcrecords.h"
    "deb/debsystem.h"
    "deb/debversion.h"
    "deb/dpkgpm.h"
    "depcache.h"
    "edsp.h"
    "edsp/edspindexfile.h"
    "edsp/edsplistparser.h"
    "edsp/edspsystem.h"
    "indexcopy.h"
    "indexfile.h"
    "init.h"
    "install-progress.h"
    "metaindex.h"
    "orderlist.h"
    "packagemanager.h"
    "pkgcache.h"
    "pkgcachegen.h"
    "pkgrecords.h"
    "pkgsystem.h"
    "policy.h"
    "prettyprinters.h"
    "sourcelist.h"
    "srcrecords.h"
    "statechanges.h"
    "tagfile.h"
    "update.h"
    "upgrade.h"
    "version.h"
    "versionmatch.h"
)

# Create a library using the C++ files
add_library(apt-pkg SHARED ${library})
add_dependencies(apt-pkg apt-pkg-versionscript)
# Link the library and set the SONAME
target_include_directories(apt-pkg
                           PRIVATE ${ZLIB_INCLUDE_DIRS}
                                   ${BZIP2_INCLUDE_DIR}
                                   ${LZMA_INCLUDE_DIRS}
                                   ${LZ4_INCLUDE_DIRS}
                                   ${ICONV_INCLUDE_DIRS}
)

target_link_libraries(apt-pkg
                      PRIVATE -lutil ${CMAKE_DL_LIBS} ${RESOLV_LIBRARIES}
                             ${CMAKE_THREAD_LIBS_INIT}
                             ${ZLIB_LIBRARIES}
                             ${BZIP2_LIBRARIES}
                             ${LZMA_LIBRARIES}
                             ${LZ4_LIBRARIES}
                             ${ICONV_LIBRARIES}
)
set_target_properties(apt-pkg PROPERTIES VERSION ${MAJOR}.${MINOR})
set_target_properties(apt-pkg PROPERTIES SOVERSION ${MAJOR})
add_version_script(apt-pkg)

# Install the library and the header files
install(TARGETS apt-pkg LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/apt-pkg)
flatify(${PROJECT_BINARY_DIR}/include/apt-pkg/ "${headers}")

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
  target_link_libraries(apt-pkg PUBLIC noprofile)
endif()
