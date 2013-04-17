microscope
---

This is a small OSX App I clicked, copied and pasted together. I was making a microscope from a PS3 camera. Getting the camera to work on OSX 10.8 was a bit of a problem. The ofxMacamPs3Eye addon for openframeworks worked just fine. I guess the ps3eye videograbber can easily be replaced to use the app on other systems or cameras.

![screenshot](http://f.cl.ly/items/3V053R0S312I0O3A2s0K/Screen%20Shot%202013-04-01%20at%204.48.33%20PM.png)

With key 'g' you call upon the gui. With 'f' you save the current frame (WITH gui if present). With 'v' you save a video (w/o gui). Currently there are no video options. You would need to hardcode them.

And of course there are the camera options to fine tune the picture. And a fullscreen toogle, because micro image look better macro style.

_The video recording function depends on ffmpeg installed_

Thanks goes to these addons:

[ofxMacamPs3Eye](https://github.com/paulobarcelos/ofxMacamPs3Eye)
[ofxVideoRecorder](https://github.com/timscaffidi/ofxVideoRecorder)
[ofxUI](https://github.com/rezaali/ofxUI)

**The selfwritten code in *src* is released unter GPL, 2013, the rest according to their own specific licenses.** 

Todos

- ffmpeg integrieren
- frame capture 1:1, no scaling
- scale line gezogen
- filename bei video / frame automatisch nummerieren
- usb abstellen wenn pc zugeklappt