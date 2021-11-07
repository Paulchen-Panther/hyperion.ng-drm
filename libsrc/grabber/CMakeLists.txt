if (ENABLE_AMLOGIC)
	add_subdirectory(amlogic)
endif (ENABLE_AMLOGIC)

if (ENABLE_DISPMANX)
	add_subdirectory(dispmanx)
endif (ENABLE_DISPMANX)

if (ENABLE_FB)
	add_subdirectory(framebuffer)
endif (ENABLE_FB)

if (ENABLE_OSX)
	add_subdirectory(osx)
endif(ENABLE_OSX)

if (ENABLE_V4L2 OR ENABLE_MF)
	add_subdirectory(video)
endif ()

if (ENABLE_X11)
	add_subdirectory(x11)
endif(ENABLE_X11)

if (ENABLE_XCB)
	add_subdirectory(xcb)
endif(ENABLE_XCB)

if (ENABLE_QT)
	add_subdirectory(qt)
endif(ENABLE_QT)

if (ENABLE_DX)
	add_subdirectory(directx)
endif(ENABLE_DX)

# TODO: integrate libdrm into CMake system (dependency libdrm-dev from buster-backports)
# To install libdrm-dev from buster backports install as root (sudo su)
# curl https://ftp-master.debian.org/keys/archive-key-10.asc | gpg --import
# gpg --export DC30D7C23CBBABEE | apt-key add -
# echo "deb http://deb.debian.org/debian buster-backports main" |sudo tee /etc/apt/sources.list.d/deb_buster_backports.list
# apt-get update
# apt-get -t buster-backports install libdrm-dev
add_subdirectory(drm)
