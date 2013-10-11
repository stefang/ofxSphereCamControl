A simple addon and TouchOSC layout to enable bi-directional control of my sphereCamera addon (https://github.com/stefang/ofxSphereCam) using OSC and the free iOS app TouchOSC (http://hexler.net/software/touchosc). Could very easily be amended for any other OSC software or control surface. I use it to find and tweak nice camera angles to use in my scene manager.

See a quick demo video here... https://vimeo.com/76519105

To understand how it works please take a look at the example app, it's pretty simple. A def in the .h file, a couple of calls to set it up with the IP address and ports of the iPad/iPhone and a call to the update() method. You don't need to #include the ofxOsc addon in your app as it's included in the addon but you do need to add it to your project and set the search paths appropriately. Or just copy the example app and build from there.

As you adjust the camera position and target the addon will output ofVec3f defs of both so you can easily cut and paste into your code.

Requires ofxOsc (part of the standard oF download), TouchOSC (http://hexler.net/software/touchosc) and an iPad or iPhone