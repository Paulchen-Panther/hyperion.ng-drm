# Define the current source locations
SET(CURRENT_HEADER_DIR ${CMAKE_SOURCE_DIR}/include/grabber)
SET(CURRENT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libsrc/grabber/drm)

# Find EGL/GBM/LibDRM
# find_package(EGL REQUIRED)
# if(EGL_FOUND)
# 	find_package(GBM REQUIRED)
# 	find_package(LibDRM 2.4.101 REQUIRED)
# 	if(GBM_FOUND AND LIBDRM_FOUND)
# 		add_definitions(-DHAVE_DRM=1)
# 	endif()
# endif()

find_package(LibDRM 2.4.101 REQUIRED)

# include_directories(${EGL_INCLUDE_DIRS} ${LIBDRM_INCLUDE_DIRS} ${GBM_INCLUDE_DIRS})
include_directories(${LIBDRM_INCLUDE_DIRS})

FILE ( GLOB DRMGrabberSOURCES "${CURRENT_HEADER_DIR}/DRM*.h"  "${CURRENT_SOURCE_DIR}/*.h"  "${CURRENT_SOURCE_DIR}/*.cpp" )
add_library( drm-grabber ${DRMGrabberSOURCES} )

target_link_libraries(drm-grabber
	hyperion
	${LIBDRM_LIBRARIES}
#	${EGL_LIBRARIES}
#	${GBM_LIBRARIES}
)
