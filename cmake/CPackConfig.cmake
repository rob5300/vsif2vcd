# CPack configuration file

# General Configuration for all OS's
set(CPACK_PACKAGE_NAME "Vsif2vcd")
set(CPACK_PACKAGE_VENDOR "Sławomir Śpiewak")
set(CPACK_PACKAGE_CONTACT "slawekwaga@gmail.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Vsif2vcd")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_CHECKSUM "SHA256")


#including CPack

if(WIN32 OR MSYS OR MINGW)
if(NOT CPACK_SYSTEM_NAME)
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
	
    set(CPACK_CPU_ARCH "x86")
endif()
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(CPACK_CPU_ARCH "x64")
endif()
    set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CPACK_CPU_ARCH}")
  endif()
  set(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)
	set(CPACK_GENERATOR "ZIP")
	set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-v${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")
	set(CPACK_PACKAGE_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)
endif()

include(CPack)
