include_directories(${BERKELEY_DB_INCLUDE_DIRS})
# Definition of the C++ files used (alphabetical order)
set(source
    "apt-ftparchive.cc"
    "byhash.cc"
    "cachedb.cc"
    "contents.cc"
    "multicompress.cc"
    "override.cc"
    "sources.cc"
    "writer.cc"
)
add_executable(apt-ftparchive ${source})

# Link the executables against the libraries
target_include_directories(apt-ftparchive PRIVATE ${BERKELEY_DB_INCLUDE_DIRS})
target_link_libraries(apt-ftparchive apt-inst apt-pkg apt-private ${BERKELEY_DB_LIBRARIES})

# Install the executables
install(TARGETS apt-ftparchive RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
