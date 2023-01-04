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

#include "FHNotifier.h"
#include "FHNotifyWidget.h"

#include <QtGlobal>

#include <Utils>
#include <FramelessWidgetsHelper>

#include <QTimer>

FHNotifyWidget::FHNotifyWidget(QColor _accentColor, bool _darkMode, QWidget *parent) : m_accentColor(_accentColor), m_darkMode(_darkMode), FramelessWidget(parent) {
    // FramelessWindowHint is enabled on Linux because I got a border around the window
    // on some DEs (GNOME for example).
#if defined(Q_OS_LINUX)
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
#else
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
#endif
    this->setMinimumSize(QSize(175, 30));
    this->setFixedSize(QSize(175, 30));
    // Set the palette of the widget according to the users choice.
    this->setPalette(themePalette(m_accentColor, m_darkMode));

    if (!m_widgetLayout)
        m_widgetLayout = new QHBoxLayout;
    // TODO: Qt6+ uses "setContentMargins"
    m_widgetLayout->setSpacing(2);
    m_widgetLayout->setMargin(2);

    m_textLbl = new QLabel("Hello, World!", this);
    {
        // The text itself should be the biggest and therefore central widget.
        m_textLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    m_widgetLayout->addWidget(m_textLbl);
    m_widgetLayout->setAlignment(m_textLbl, Qt::AlignHCenter);

    m_closeBtn = new QPushButton(this);
    {
        m_closeBtn->setFont(QFont(ICON_FONT, ICON_FONT_SIZE));
        m_closeBtn->setText(CLOSE_POINT);
        // Allow custom styling of the close button.
        m_closeBtn->setObjectName("FHNotifierCloseButton");
        m_closeBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_closeBtn->setFixedWidth(40);
        connect(m_closeBtn, &QPushButton::clicked, this, [=]() {
            this->close();
        });
    }
    m_widgetLayout->addWidget(m_closeBtn);

    this->setLayout(m_widgetLayout);
}

FHNotifyWidget::~FHNotifyWidget() {
}

void FHNotifyWidget::setNotificationText(const QString &_text) {
    m_text = _text;
    m_textLbl->setText(m_text);
}

void FHNotifyWidget::setTimespan(int _msec) {
    m_timespan = _msec;
}

void FHNotifyWidget::notify() {
    if (m_timespan == 0) m_timespan = 3000;
    if (m_text.isEmpty()) m_textLbl->setText("Hello, World!");
    this->show();
    // Thanks to Pence! But I still need to investigate this as I really would like
    // to display a progressbar over it. singleShot is also not the ideal way as I understand
    // Qt's timers & threads...
    QTimer::singleShot(m_timespan, this, [=]() {
        this->close();
    });
}
