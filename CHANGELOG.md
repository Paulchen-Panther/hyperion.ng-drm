# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased](https://github.com/hyperion-project/hyperion.ng/compare/2.0.0-alpha.10...HEAD)

### Breaking

### Added

### Changed

### Fixed

### Removed

## [2.0.0-alpha.10](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.10) - 2021-07-17

The focus of this release is on user experience.
We tried as much as possible supporting you in getting valid setup done, as well as providing enough room for expert users to tweak configurations here and there.
The reworked dashboard provides you now with the ability to control individual components, jump to key configuration items, as well as to switch between LED instances easily.
The refined color coding in the user-interfaces, helps you to quickly identify instance specific and global configuration items.

Of course, the release brings new features (e.g. USB Capture on Windows), as well as minor enhancements and a good number of fixes.

Note: 

- **IMPORTANT:** Due to the rework of the grabbers, both screen- and video grabbers are disabled after the upgrade to the new version.
Please, re-enable the grabber of choice via the UI, validate the configuration and save the setup. The grabber should the restart.

- Hyperion packages can now be installed under Ubuntu (x64) and Debian (amd64/armhf) (incl. Raspberry Pi OS) via our own APT server. 
Details about the installation can be found in the [installation.md](https://github.com/hyperion-project/hyperion.ng/blob/master/Installation.md) and at [apt.hyperion-project.org](apt.hyperion-project.org).
- Find here more details on [supported platforms and configuration sets](https://github.com/hyperion-project/hyperion.ng/blob/master/doc/development/SupportedPlatforms.md)

### Breaking

### Added

- The Dashboard is now a one-stop control element to control instances and link into configuration areas
- LED Instance independent configuration objects (e.g. capturing hardware) are now separated out in the menu
- New menu item "Sources" per LED instances configuration to enable/disable screen or usb grabber per instance

#### Grabbers
- Windows Media Foundation USB grabber (incl. Media Foundation transform/Turbo-JPEG scaling)
- Linux V4L2 Grabber now supports the following formats: NV12, YUV420
- Image flipping ability in ImageResampler/Turbo-JPEG
- UI: Simplified screens for non-expert usage, do only show elements relevant
- Discover available Grabbers (incl. their capabilities for selection), not supported grabbers are not presented. Note: Screen capturing on Wayland is not supported (given the Wayland security architecture)
- USB Grabber: New ability to configure hardware controls (brightness, contrast, saturation, hue), as well as populating defaults
- Configuration item ranges are automatically adopted based on grabber capabilities,
- Grabbers can only be saved with a valid configuration
- Standalone grabbers: Added consistent options/capabilities for standalone grabbers, debug logging support
- Screen grabbers: Allow to set capture frequency, size decimation and cropping across all grabber types
- Screen grabber: QT-Grabber allows to capture individual displays or all displays in a multi-display setup
- Display Signal Detection area in preview (expert users)
- UI: Only show CEC detection, if supported by platform

#### LED-Devices
- Select device from list of available devices (UI Optimization - Select device from list of available devices #1053) - Cololight, Nanoleaf, Serial Devices (e.g. Adalight), SPI-Device, Pi-Blaster
- Get device properties for automatic configuration of number of LEDs and initial layout (WLED, Cololight, Nanoleaf)
- Identify/Test device (WLED, Cololight, Nanoleaf, Adalight)
- For selected devices a default layout configuration is created, if the user chooses "Overwrite" (WLED, Cololight, Nanoleaf, all serial devices, all spi device, pi-blaster)
- Ensure Hardware LED count matches number of lights (Philips Hue, Yeelight, Atmo Orb)
- User is presented a warning/error, if there is a mismatch between configured LED number and available hardware LEDs
- Add udev support for Serial-Devices
- Allow to get properties for Atmo and Karatedevices to limit LED numbers configurable
- Philips Hue: Add basic support for the Play Gradient Lightstrip
- WLED: Support of ["live" property] (https://github.com/Aircoookie/WLED/issues/1308) (#1095)
- WLED: Brightness overwrite control by configuration
- WLED: Allow to disable WLED synchronization when streaming via hyperion
- WLED: Support storing/restoring state (#1101)
- Adalight: Fix LED Num for non analogue output in arduino firmware

- Allow to blacklist LEDs in layout via UI
- Live Video image to LedLayout preview (#1136)

#### Other

- Effects: Support Custom Effect Templates in UI for custom effect creation and configuration
- Effects: Custom effect separation in the systray menu

- New languages - Portuguese (Std/Brazil) & Norwegian (Bokmål)
- New Flags: Russia, Cameroon, Great Britain, England, Scotland

- Provide cross compilation on x86_64 for developers using docker. This includes the ability to use local code, as well as build incrementally

### Changed

- Grabbers use now precise timings for better timing accuracy

- Nanoleaf: Consider Nanoleaf-Shape Controllers
- LED-Devices: Show HW-Ledcount in all setting levels

- System Log Screen: Support to copy loglines, system info and status of the current instance to the clipboard (to share it for investigation)

- Updated dependency rpi_ws281x to latest upstream
- Fix High CPU load (RPI3B+) (#1013)

### Fixed

- Active grabbers are displayed correctly after updating the WebUI
- Issue Crop values are checked against decimated resolution (#1160)
- Framebuffer grabber is deactivated in case of error
- Fix/no signal detection (#1087)

- Fix that global settings were not correctly reflected across instances after updates in other non default instance (#1131,#1186,#1188)
- Fix UI: Handle error scenario properly, when last instance number used does not exist any longer.
- UI Allow to have password handled by Password-Manager (#1263)

- Fixed effect freezing during startup
- Effects were not started from tray (#1199)
- Interrupt effect on timeout (#1013)
- Fixed color and effect handling and duplicate priorities (#993,#1113,#1216)
- Stop background effect, when it gets out of scope (to not use resources unnecessarily)
- Custom Effect Templates (schemas) are now loaded
- Effects: Uploaded images were not found executing custom image effects
- "LED Test" effect description is in wrong order (#1229)

- LED-Devices: Only consider Hardware LED count (#673)
- LED-Devices: Correct total packet count in tpm2net implementation (#1127)
- LED-Hue: Proper black in Entertainment mode if min brightness is set
- LED-Hue: Minor fix of setColor command
- Nanoleaf: Fixed behaviour, if external control mode cannot be set

- System Log Screen: Fixed Auto-Scrolling, Update Look & Feel, Works across multiple Browser tabs/windows, as log stream is not stopped by a new UI

- Rename Instance and Change Password: Modal did not close
- Read-Only mode was not handled in the SysInfo function

- WebSockets: Handling of fragmented frames fixed
- Fixed libcec dependencies

- General language and grammar updates

### Removed

## [2.0.0-alpha.9](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.9) - 2020-11-18
### Added
- Grabber: DirectX9 support (#1039)
- New blackbar detection mode "Letterbox", that considers only bars at the top and bottom of picture

- LED-Devices: Cololight support (Cololight Plus & Strip) incl. configuration wizard
- LED-Devices: SK9822 support (#1005,#1017)

- UX: New language support: Russian and Chinese (simplified) (#1005)
- UX: Additional details on Hardware/CPU information (#1045)
- UX: Systray icons added - Issue #925 (#1040)

- Read-Only configuration database support
- Hide Window Systray icon on Hyperion exit & Install DirectX Redistributable
- Read-Only configuration database support

### Changed
- boblight: reduce cpu time spent on memcopy and parsing rgb values (#1016)
- Windows Installer/Uninstaller notification when Hyperion is running (#1033)
- Updated Windows Dependencies
- Documentation: Optimized images (#1058)
- UX: Default LED-layout is now one LED only to avoid errors as in #673
- UX: Change links from http to https (#1067)
- Change links from http to https (#1067)
- Cleanup packages.cmake & extend NSIS plugin directory
- Optimize images (#1058)
- Docs: Refreshed EN JSON API documentation

### Fixed
- Color calibration for Kodi 18 (#1044)
- LED-Devices: Karatelight, allow an 8-LED configuration (#1037)
- LED-Devices: Save Hue light state between sessions (#1014)
- LED-Devices: LED's retain last state after clearing a source (#1008)
- LED-Devices: Lightpack issue #1015 (#1049)
- Fix various JSON API issues (#1036)
- Fix issue #909, Have ratio correction first and then scale (#1047)
- Fix display argument in hyperion-qt (#1027)
- Fix Python reset thread state
- AVAHI included in Webserver (#996)
- Fix add libcec to deb/rpm dependency list
- Fix Hyperion configuration is corrected during start-up, if required
- Fix color comparison / Signal detection (#1087)

### Removed
- Replace Multi-Lightpack by multi-instance Lightpack configuration (#1049)

## [2.0.0-alpha.8](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.8) - 2020-09-14
### Added
- Add XCB grabber, a faster and safer alternative for X11 grabbing (#912)
- for Windows: Add binary meta (#932)
- Differentiate between LED-Device Enable/Disable and Switch On/Off (#960) (Fixes: #828)
- AtmoOrb discovery and identification support (#988)
- New AtmoOrb Wizard (#988)
- Added and updated some language files (#900, #926, #916) (DE, CS, NL, FR, IT, PL, RO, ES, SV, TR, VI)
### Changed
- Improved UDP-Device Error handling (#961)
- NSIS/Systray option to launch Hyperion on Windows start (HKCU) (#887)
- Updated some dependencies (#929, #1003, #1004)
- refactor: Modernize Qt connections (#914)
- refactor: Resolve some clang warnings (#915)
- refactor: Several random fixes + Experimental playground (#917)
- Use query interface for void returning X requests (#945)
- Move Python related code to Python module (#946)
- General tidy up (#958)
- AtmoOrb ESP8266 sketch to support device identification, plus small fix (#988)

### Fixed
- webui: Works now with HTTPS port 443 (#923 with #924)
- Adalight issue (#903 with #991)
- Fixed CI: Trigger HyperBian build after release
- Fixed: -DUSE_SYSTEM_MBEDTLS_LIBS=ON - undefined reference (#898)
- set zlib back to system ignore list/revert pr #871 (#904)
- Fixed: logger and led colors (#906)
- Fixed: some more threading errors (#911)
- Fix OSX build (#952)
- AtmoOrb Fix (#988)
- Return TAN to API requests whenever possible (#1002)

## [2.0.0-alpha.7](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.7) - 2020-07-23
### Added
- [HyperBian](https://github.com/hyperion-project/HyperBian/releases) - A Raspberry Pi OS Lite image with Hyperion pre installed. (#832)
- An option to reset (delete) the database for the commandline has been added (#820)
- Improve language selection usability (#812)
- re-added V4L2 Input method from old Hyperion (#825)
- Windows: Start Hyperion with a console window `hyperiond -c` (Or new start menu entry) (#860)
- Get process IDs by iterating /proc (#843)
- Dump stack trace on crash (Implement #849) (#870)
- Minor fixes
- New Devices (#875)
  * Yeelight support incl. device discovery and setup-wizard
  * WLED as own device and pre-configuration
- Additional device related capabilities (#875)
  * discover, getProperties, identify, store/restore state and power-on/off available for Philips-Hue, Nanoleaf, Yeelight, partially for Rs232 / USB (Hid)
  * New device capabilities are accessible via JSON-API
  * New REST-API wrapper class in support of network devices, e.g. Philips Hue, Nanoleaf and WLED
  * Flexible SSDP-Discovery incl. RegEx matching and filtering
- Documentation (#875)
  * Process workflow for LED-Devices
  * Documentation of device classes & methods
  * Code template for new LED-Devices available
- CEC detection (#877)

### Changed
- Updated dependency rpi_ws281x to latest upstream (#820)
- Updated websocket-extensions (#826)
- webui: Suppress default password warning (#830)
- webui: Add French, Vietnamese and Turkish (#842)
- Show thread names in GDB for better debugging (#848)
- CompileHowto.md updated (#864)
- Updated Embedded python package (zip) for Linux (#871)
- DBManager: ORDER BY parameter added to getRecord(s) (#770)
- Corrected GitHub Actions badge
- Fix GitHub Actions/Azure Windows Workflow/Pipeline
- Updated submodules flatbuffers/rpi_ws281x (#873)
- LED-Device workflow changed allowing proper suspend/resume & disable/enable scenarios (#875)
- Network LED-Devices will stop sending packages when disabled (#875)
- Rs232 Provider fully reworked and changed to synchronous writes (#875)
- Rs232 configuration via portname and system location (/dev/ style), auto detection is not case-sensitive any longer (#875)
- Additional error handling depending on device type (#875)
- Add Windows compatibility incl. moving to Qt functions (#875)
- Add compatibility for different Qt versions (#875)


### Fixed
- device: Nanoleaf (#829)
- device: LPD8806 Problems fixed (#829)
- Possible crash on shutdown (#846). Issue #668
- Enumerate only V4L2 frame sizes & intervals for framesize type DISCRETE (fix BCM2835 ISP) (#820)
- Fix systemd registration in debian for RPi4 (#820)
- Fix missing define in Profiler & added header notes (#820)
- some Windows Compile issues
- Fix: leaking active effects during quit (#850)
- Correct path for each build configuration
- Fix heap corruption (#862)
- Fix OpenSSL dependencies for Windows (#864)
- Fix resolution change event Fixes part of #620 (#867)
- some code improvements & cleanup (#861) (#872) (#880) (#876)
- some little things, as always (#863)
- AtmoOrb: Buffer length fix and new configuration validations (#875)
- Added missing DMX SubTypes to configuration (#875)
- Fix logger (#885)
  * Make logger thread safe
  * Include timestamp in logs
  * Make logs look a bit more cleaner
- Decrease compile time (#886)
- Fix some data synchronization error (#890)
- Fix Qt screenshot crash (#889)
- Fix crash on startup if no X server available (#892)
- Fix RPC restart of Hyperion (#894)

## [2.0.0-alpha.6](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.6) - 2020-05-27
### Breaking
The release package names have been adjusted.\
If you used a `.deb` package please uninstall it before you upgrade
- Check for the package name `apt-cache search hyperion`. You may see now a entry like `hyperion-x86`, `hyperion-rpi`
- Remove with the correct name `sudo apt-get remove hyperion-XX`
- Now install the new .deb as usual. From now on the package is just called `hyperion`

### Added
- [Documentation](https://docs.hyperion-project.org) for Hyperion (#780)
- Hyperion can be compiled on windows. [Issues list](https://github.com/hyperion-project/hyperion.ng/issues/737) (#738)
- effect: New plasma/lava lamp effect (#792)
- device: Philips Hue Entertainment API now available as new device. [Read about requirements](https://docs.hyperion-project.org/en/user/LedDevices.html#philipshue) (#806)
- webui: Philips Hue Entertainment API Wizard (#806)
- webui: Toggle-Buttons for Component Remote Control (#677) (#778)
- webui: Add Trapezoid to LED Layout creation (#791)

### Changed
- webui: Dark mode adjustments (#789)

### Fixed
- device: Rewrite-/LatchTime definitions for all devices adjusted (#785) (#799)
- device: Nanoleaf crashes hyperion
- Documentation for Hyperion (#780)
- webui: Hide v4l2 if not available (#782)
- Documentation fixes (#790)

### Removed
- Linux 32bit packages are no longer available for download. Also the `.sh` packages are gone.
- Mac `.dmg` package disabled because of new apple restrictions. Please use the `tar.gz` instead.

## [2.0.0-alpha.5](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.5) - 2020-04-17
### Added:
- WebUI Dark Mode (#752) (#765)

### Fixed:
- SSDP Discovery reliability (#756)
- Some effects are running extreme slowly (#763)
- JsonAPI error "Dead lock detected" (2e578c1)
- USB Capture only in Black and white (#766)

### Changed:
- Check if requested Instance is running (#759)
- V4L2 enhancements (#766)
- Stages are now used in Azure CI/CD (9ca197e)

## [2.0.0-alpha.4](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.4) - 2020-03-27
### Fixed:
- Memoryleaks & Coredump, if no Grabber compiled (#724)
- Resolve enable state for v4l and screen capture (#728)
- Enable/Disable loops for components
- Runs now on x86_64 LibreElec (missing libs) (#736)
- Brightness compensation is now visible for configuration (#746)
- Prevent malformed image size for effects with specific led layouts (#746)

### Changed:
- SIGUSR1/SIGUSR2 implemented again (#725)
- V4L2 width/height/fps options available (#734)
- Swedish translation update

## [2.0.0-alpha.3](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.3) - 2020-03-01
### Added
- Package Update Descriptions on WebUi (#694)
- Pull Requests will now create artifacts for faster testing!

### Fixed
- Led Matrix Layout - Save/Restore (#669) (#697)
- New hue user generation (#696)
- Nanoleaf - Udp Network init was missing (#698)
- Multiple memory leaks and segfault issues in Flatbuffer Forwarder

## [2.0.0-alpha.2](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.2) - 2020-02-20
### Added
- Swedish Translation (#675)
- Dutch translation from [Kees](mailto:kees@vannieuwenhuijzen.com), [Nick](mailto:nick@doingcode.nl) & [Ward Wygaerts](mailto:wardwygaerts@gmail.com)
- Polish translation from [Patryk Niedźwiedziński](mailto:pniedzwiedzinski19@gmail.com)
- Romanian translation from [Ghenciu Ciprian](mailto:g.ciprian@osn.ro)

### Changed
- Smoothing comp state on startup (#685)
- Azure GitHub release title (#686)
- SSL/Avahi problems in previous release (#689)
- WebUI Version Check to SemVer. Also adds "Alpha" Channel (#692)

### Removed
- Travis CI tests (#684)

## [2.0.0-alpha.1](https://github.com/hyperion-project/hyperion.ng/releases/tag/2.0.0-alpha.1) - 2020-02-16
### Added
- Initial Release