/*
Copyright (c) 2022-2023 Jan Kowalewicz <jan.kowalewicz@web.de, jan@nitroosit.de>

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
*/

#include <QPalette>
#include <QColor>

// On Windows we are going to use the included Segoe MDL2 Assets to get our
// close button. On Linux there is no such font and you can't just pack MDL2 with
// it due to licensing issues with Microsoft. Pawxel uses Google's Material Icons as
// a font. You'll need to install it first in order to use it. Pawxel includes Google's
// Material iconfont in resources and installs it during launch just for the current session.
// You can also change the iconfont by also changing the codepoints.
#if defined(Q_OS_WINDOWS)
#define ICON_FONT "Segoe MDL2 Assets"
#define ICON_FONT_SIZE 8
#define CLOSE_POINT "\uE8BB"
#else
#define ICON_FONT "Material Icons Outlined"
#define ICON_FONT_SIZE 16
#define CLOSE_POINT "\uE5CD"
#endif

inline QPalette themePalette(QColor _accentColor, bool _darkMode) {
    QPalette pal;
    if (_darkMode) {
        pal.setColor(QPalette::Window, QColor(34, 34, 34));
        pal.setColor(QPalette::Base, QColor(34, 34, 34));
        pal.setColor(QPalette::AlternateBase, QColor(26, 26, 26));
        pal.setColor(QPalette::Button, QColor(26, 26, 26));
        pal.setColor(QPalette::WindowText, QColor(197, 197, 197));
        pal.setColor(QPalette::Text, QColor(197, 197, 197));
        pal.setColor(QPalette::ButtonText, QColor(197, 197, 197));
    } else {
        pal.setColor(QPalette::Window, QColor(254, 254, 254));
        pal.setColor(QPalette::Base, QColor(254, 254, 254));
        pal.setColor(QPalette::AlternateBase, QColor(255, 255, 255));
        pal.setColor(QPalette::Button, QColor(255, 255, 255));
        pal.setColor(QPalette::WindowText, QColor(43, 43, 43));
        pal.setColor(QPalette::Text, QColor(43, 43, 43));
        pal.setColor(QPalette::ButtonText, QColor(43, 43, 43));
    }
    pal.setColor(QPalette::Highlight, _accentColor);
    return pal;
}