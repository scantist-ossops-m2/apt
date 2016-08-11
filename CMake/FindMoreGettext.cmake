# Find additional gettext binaries not found by FindGettext

find_package(Gettext)

get_filename_component(GETTEXT_DIR ${GETTEXT_MSGMERGE_EXECUTABLE} DIRECTORY)
find_program(XGETTEXT_EXECUTABLE xgettext HINTS ${GETTEXT_DIR})
find_program(MSGCOMM_EXECUTABLE msgcomm HINTS ${GETTEXT_DIR})


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MoreGettext
                                  REQUIRED_VARS MSGCOMM_EXECUTABLE XGETTEXT_EXECUTABLE
                                  VERSION_VAR ${GETTEXT_VERSION_STRING})
