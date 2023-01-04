## FHNotifier

Works on:

![qt5](https://img.shields.io/badge/qt5-5.14.x-brightgreen?style=flat-square)
![qt6](https://img.shields.io/badge/qt6-with--changes-orange?style=flat-square)

> **WARNING** - Currently not ready for production use! Code will change, break some things - or not.

``FHNotifier`` tries to extend [FramelessHelper](https://github.com/wangwenx190/framelesshelper) with prebuilt widgets.

- ``FHNotifyWidget`` - toast-like notification to display a text for a short amount of time
- ``FHMessageBox`` - message box to display info, warning or error

Mainly needed for [Pawxel](https://pawxel.rocks), I thought, why not use it as an example of what is possible with FramelessHelper.

### How to use

Just include the ``FHNotifier.pri`` file or the relevant files from the ``FHNotifier/`` folder in your project. Do not exclude ``FHNotifier.h`` as it is used in some files for theming. The classes itself **do not** rely on each other.

**You don't need to pull the submodules, as this is just for testing purposes only. FHNotifier works with your already working FramelessHelper _installation_.**

### Example

This is an Example, how FHNotifier is used inside Pawxel:
```cpp
#include <FHNotifier/FHMessageBox.h>

void Application::onPrefChangeRestartRequired() {
    if (!m_restartMsgBox)
        m_restartMsgBox = new FHMessageBox(FHMessageBox::Ok, m_accentColor, m_shouldAppsUseDarkMode);
    m_restartMsgBox->setMessageBoxTitle(tr("Restart required"));
    m_restartMsgBox->setText(tr("A restart is required for these changes to take some effect."));
    m_restartMsgBox->setMessageBoxIcon(FHMessageBox::Warning);
    {
        m_restartMsgBox->titleWidget()->setFont(QFont("Josefin Sans Bold", 9));
        m_restartMsgBox->textWidget()->setFont(QFont("Josefin Sans", 9));
        m_restartMsgBox->setButtonFont(QFont("Josefin Sans", 9));
    }
    connect(m_restartMsgBox, &FHMessageBox::firstButtonClicked, this, [=]() {
        m_restartMsgBox->close();
    });
    m_restartMsgBox->show();
}
```

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