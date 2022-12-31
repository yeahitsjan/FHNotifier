/*
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
*/

#ifndef __FHNotifyWidget_h__
#define __FHNotifyWidget_h__

#include <FramelessWidget>
#include <QObject>

#include <QPointer>

#include <QHBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>

FRAMELESSHELPER_USE_NAMESPACE

class FHNotifyWidget : public FramelessWidget {
    Q_OBJECT
public:
    FHNotifyWidget(QColor _accentColor, bool _darkMode, QWidget *parent = nullptr);
    ~FHNotifyWidget();

    // Set the text of the notify widget.
    void setNotificationText(const QString &_text);
    QString notificationText() { return m_text; }

    // Set the timespan the notify widget is visible before it's closed. Default is 3000 (3 sec).
    void setTimespan(int _msec);
    int timespan() { return m_timespan; }

    // Apply a custom font to the full widget.
    void setWidgetFont(QFont _f);
    QFont widgetFont() { return m_font; }

protected:
    QColor m_accentColor;
    bool m_darkMode;

    QString m_text;
    int m_timespan = 3000;
    QFont m_font;

    QPointer<QHBoxLayout> m_widgetLayout;
    QProgressBar *m_timerBar;
    QLabel *m_textLbl;
    QPushButton *m_closeBtn;

public slots:
    // Display the notify widget with given timespan.
    virtual void notify();
};

#endif // __FHNotifyWidget_h__