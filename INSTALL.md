NEXT-NDNVIDEO -- Pre-recorded Video Streaming Project based on Consumer/Producer API
==

Prerequisites
==
These are prerequisites to build NEXT-NDNVIDEO.

**Required:**
* [NDN-CXX](https://github.com/named-data/ndn-cxx.git)
* [NFD](https://github.com/named-data/NFD.git)
* [consumer-producer-api](https://github.com/iliamo/Consumer-Producer-API)
* [repo-ng](https://github.com/named-data/repo-ng.git)
* [gstreamer-1.0](http://gstreamer.freedesktop.org/data/pkg/osx/1.4.3/)
* [boost](http://www.boost.org/)

Prerequisites build instructions
==

MacOS build considerations
-

NDN-CXX & NFD
--
First install NDN-CXX, then install NFD, all from the source.

consumer-producer-api
--
Only after NDN-CXX & NFD installation, build and install this API.

repo-ng
--
copy the repo-ng.config into ${SYSCONFDIR}/ndn(default is /usr/local/etc).

gstreamer-1.0
--
downlaod from http://gstreamer.freedesktop.org/data/pkg/osx/1.4.3/

**Installation: please follow the order listed below. Only tested on the 1.4.3, use exactly this version.**
* gstreamer-1.0-1.4.3-universal.pkg  --- the basic gstreamer lib
* gstreamer-1.0-devel-1.4.3-universal.pkg  --- the develpoer gstreamer lib
* gstreamer-1.0-1.4.3-universal-packages.dmg --- some useful plugins, please install all of them expect the last one

**Config:**
* Please add /Library/Frameworks/GStreamer.framework/Versions/1.0/lib/pkgconfig to your $PKG_CONFIG_PATH
* e.g. add "export PKG_CONFIG_PATH=/Library/Frameworks/GStreamer.framework/Versions/1.0/lib/pkgconfig:$PKG_CONFIG_PATH" to your .bashrc

boost
--
sudo port install boost

Build instructions
==
<pre>
$ ./waf configure
$ ./waf
</pre>
