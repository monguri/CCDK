Frequently Asked Questions about CCDK
====
- <B>What is the Shinra CCDK?</B><BR>
The Shinra CCDK, or Community Cloud Development Kit, is a toolkit that is designed to allow small developers and hobbyists to create their own cloud-powered games.
<BR>
- <B>What do I need to do to get started?</B><BR>
To make a cloud game with the CCDK, you will need a PC running Windows 7, DirectX 9/11, and the development environment of your choice (VS 2012 /2013 have been tested). To create cloud games that utilize N:N architecture, a Linux virtual machine is required.
<BR>
- <B>Where can I get it?</B><BR>
The CCDK will be distributed, updated, and supported via GitHub.
<BR>
- <B>When is it coming out?</B><BR>
A private release will be made available in April 2015 to selected developers; contact DevUS@shinra.com for more information.
<BR>
- <B>Does every game on the Shinra platform run on the CCDK?</B><BR>
No. The Shinra CCDK is intended for small developers and hobbyists; the development environment and architecture for larger developers have more aggressive hardware requirements.
<BR>
- <B>How much do I need to know about networked programming to make a CCDK game?</B><BR>
Networking programming knowledge is not required to make games under the 1:1 model or 1:N architectures. Running under the N:N architecture requires socket programming knowledge, but this can be made easier with a standard sync server or by using the VCE library.
<BR>
- <B>What kind of architecture do I use to build a cloud game?</B><BR>
You can read a blog post here [LINK] about the different types of architectures that run on Shinra, which we classify as 1:1, 1:N, and N:N.
<BR>
- <B>What is VCE, and how do I use it?</B><BR>
VCE is a library written in C that performs high-speed networking via TCP, and comes in very useful when writing Shinra games. It runs under Windows and Linux, and was used as the networking base for the Shinra sample game Space Sweeper. VCE will be released for free, and is intended to be used with the CCDK.
<BR>
- <B>Can I make a CCDK game under 1:1, 1:N, or N:N?</B><BR>
Yes. There is no limit on the actual game architecture.
<BR>
- <B>What can't I do with the CCDK?</B><BR>
Heavy GPU usage for example, trying to use multiple GPUs linked in tandem) may still be limited in the initial stages of development; tuning the remote renderer itself may also be unavailable. Our technical support team can provide you with more information.
<BR>
- <B>Do I need to be a subscriber to the Shinra service and/or have a fiber connection in order to make a CCDK-powered game?</B><BR>
Neither are required. You can develop your game using a local machine and local network.
<BR>
- <B>What kind of middleware can I use to make a CCDK game?</B><BR>
From a pure architecture perspective, any middleware or engine that uses DirectX 9 or 11 is supported by the system; however, license and other restrictions for a streaming platform are the responsibility of the developer. We are currently preparing a list of tested middleware.
<BR>
- <B>How do I sell a game that I've written with the CCDK?</B><BR>
Our goal is to support independent developers who make use of the CCDK, and we'll be addressing the business side of CCDK development in a future update to the Q&A section.
<BR>
- <B>What language can I write my game in?</B><BR>
The CCDK sample programs (such as Space Sweeper) are written in C++. Other languages should be fully compatible (in the same way that DX9/11 middleware is supported by the system). 
<BR>
- <B>Am I able to take advantage of the client's GPU as well?</B><BR>
One of the benefits of Shinra is that there are no per-game installs on the client side; everything is kept inside the data center and transported by video stream.
<BR>
- <B>Is it possible to use my own backend server that doesn't exist inside a Shinra data center?</B><BR>
Yes, there are currently no restrictions on where your backend server lives.
<BR>
- <B>If I make a game on Shinra, does it have to take advantage of sharing (or multiplayer)?</B><BR>
While there's nothing to stop you from making a single-player experience with the CCDK, sharing data by running games inside the same data center is a unique feature of the Shinra platform, and can result in interesting new multiplayer experiences.
<BR>
- <B>For 1:1: 1:N, and N:N, all input is taken from the client PC side, but how do you handle an environment with latency?</B><BR>
In Japan, we are able to utilize NGNs to ensure the network environment is optimal. We're aiming for a maximum of 30ms to 40ms maximum latency, plus our rendering system already reduces the latency loop in half, making the feel seamless. 
<BR>