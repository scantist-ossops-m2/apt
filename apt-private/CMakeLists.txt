# Set the version of the library
set(MAJOR 0.0)
set(MINOR 0)

# Definition of the C++ files used (alphabetical order)
set(library
    "acqprogress.cc"
    "private-cachefile.cc"
    "private-cacheset.cc"
    "private-cmndline.cc"
    "private-depends.cc"
    "private-download.cc"
    "private-install.cc"
    "private-list.cc"
    "private-main.cc"
    "private-moo.cc"
    "private-output.cc"
    "private-search.cc"
    "private-show.cc"
    "private-source.cc"
    "private-sources.cc"
    "private-unmet.cc"
    "private-update.cc"
    "private-upgrade.cc"
    "private-utils.cc"
)
set(headers
    "acqprogress.h"
    "private-cachefile.h"
    "private-cacheset.h"
    "private-cmndline.h"
    "private-depends.h"
    "private-download.h"
    "private-install.h"
    "private-list.h"
    "private-main.h"
    "private-moo.h"
    "private-output.h"
    "private-search.h"
    "private-show.h"
    "private-source.h"
    "private-sources.h"
    "private-unmet.h"
    "private-update.h"
    "private-upgrade.h"
    "private-utils.h"
)
# Create a library using the C++ files
add_library(apt-private SHARED ${library})

# Link the library and set the SONAME
target_link_libraries(apt-private PUBLIC apt-pkg)
set_target_properties(apt-private PROPERTIES VERSION ${MAJOR}.${MINOR})
set_target_properties(apt-private PROPERTIES SOVERSION ${MAJOR})
add_version_script(apt-private)

# Install the library and the headers
install(TARGETS apt-private
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        NAMELINK_SKIP)

flatify(${PROJECT_BINARY_DIR}/include/apt-private/ "${headers}")
