## FHNotifier

> **WARNING** - Currently not ready for production use! Code will change, break some things - or not.

``FHNotifier`` tries to extend [FramelessHelper](https://github.com/wangwenx190/framelesshelper) with prebuilt widgets.

- ``FHNotifier`` - toast-like notification to display a text for a short amount of time
- ``FHMessageBox`` - message box to display info, warning or error

Mainly needed for [Pawxel](https://pawxel.rocks), I thought, why not use it as an example of what is possible with FramelessHelper.

### How to use

Just include the ``FHNotifier.pri`` file or the relevant files from the ``FHNotifier/`` folder in your project. The files **do not** rely on each other.

**You don't need to pull the submodules, as this is just for testing purposes only. FHNotifier works with your already working FramelessHelper _installation_.**

### Run the demo

If you want to run the demo, fire up a terminal:
```
$ git clone https://github.com/yeahitsjan/FHNotifier.git
$ cd FHNotifier
$ git submodule init && git submodule update
```

From there on either use Qt Creator or QMake from terminal (``demo/demo.pro``). The demo uses an [own fork](https://github.com/yeahitsjan/framelesshelper/tree/qmake_mods) of FramelessHelper which does not always include the newest features. You are able to opt-in whatever version you want by cloning into the root directory!

### License

MIT. Just as FramelessHelper.

```
Copyright (c) 2022 Jan Kowalewicz <jan.kowalewicz@web.de, jan@nitroosit.de>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```