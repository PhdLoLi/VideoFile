NEXT-NDNVIDEO -- Pre-recorded Video Streaming
----

NDN Pre-recorded Video Streaming Project based on Consumer/Producer API

For license information see LICENSE.

http://named-data.net/

Description
----

NDN-based Pre-recorded Streaming Video Project using Consumer/Producer API. 


- Producer
    - The repo\_producer will publish all the video files frame by frame into Repo-ng.
    - The list\_producer will publish the latest playing list every minute. 

- Consumer
    - The consumer should first ask for the latest playing list, then chose one to play back. 

Structure
----

The directory structure is as follows:

* **/root**
    * **src/** *-- source code*
    * **waf** *-- binary waf file*
    * **wscript** *-- waf instruction file*
    * **repo-ng.config** *-- repo-ng config file, the default path is "/usr/local/etc/ndn/"*
    * **.waf-tools/** *-- additional waf tools*
    * **examples/** *-- no use now*
    * **tests/** *-- no use now*
    * **LICENSE**
    * **README.md**
    * **INSTALL.md** 


Building instructions
----
Please, see the [INSTALL.md](INSTALL.md) for build instructions.

Usage
----
- Terminal 1 for repo\_producer -- Publishing video & audio to Repo-ng
<pre>
$ .build/repo\_producer
</pre>

- Terminal 2 for list\_producer -- Publishing playing list
<pre>
$ .build/producer
</pre>

- Terminal 3 -- Playing video & audio
<pre>
$ .build/consumer
</pre>

License
---
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version, with the additional exemption that compiling, linking, and/or using OpenSSL is allowed.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
