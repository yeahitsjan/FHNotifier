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

#include "FHNotifyWidget.h"

#include <QtGlobal>

#include <Utils>
#include <FramelessWidgetsHelper>

#include <QTimer>

FHNotifyWidget::FHNotifyWidget(QColor _accentColor, bool _darkMode, QWidget *parent) : m_accentColor(_accentColor), m_darkMode(_darkMode), FramelessWidget(parent) {
#if defined(Q_OS_LINUX)
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
#else
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
#endif
    this->setMinimumSize(QSize(175, 35));
    this->setFixedSize(QSize(175, 35));

    if (m_darkMode)
        this->setStyleSheet("background-color: rgb(47, 47, 47);");
    else
        this->setStyleSheet("background-color: rgb(254, 254, 254);");

    QVBoxLayout *_logic = new QVBoxLayout(this);
    _logic->setSpacing(0);
    _logic->setMargin(0);

    m_timerBar = new QProgressBar(this);
    {
        m_timerBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_timerBar->setMaximumHeight(2);
        m_timerBar->setMinimum(0);
        m_timerBar->setMaximum(m_timespan);
        m_timerBar->setTextVisible(false);
        m_timerBar->setStyleSheet("QProgressBar { border: none; background: transparent; color: red; }"
                                "QProgressBar:chunk { background-color: " + m_accentColor.name() + "; }");
    }
    _logic->addWidget(m_timerBar);

    if (!m_widgetLayout)
        m_widgetLayout = new QHBoxLayout;
    m_widgetLayout->setSpacing(4);
    m_widgetLayout->setMargin(2);

    m_textLbl = new QLabel("Hello, World!", this);
    {
        if (m_darkMode)
            m_textLbl->setStyleSheet(m_textLbl->styleSheet() + "color: rgb(197, 197, 197);");
        else
            m_textLbl->setStyleSheet(m_textLbl->styleSheet() + "color: rgb(34, 34, 34);");
        m_textLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    m_widgetLayout->addWidget(m_textLbl);
    m_widgetLayout->setAlignment(m_textLbl, Qt::AlignHCenter);

    m_closeBtn = new QPushButton(this);
    {
#if defined(Q_OS_WINDOWS)
        m_closeBtn->setFont(QFont("Segoe MDL2 Assets", 8));
        m_closeBtn->setText("\uE8BB");
#else
#endif
        m_closeBtn->setObjectName("FHNotifierCloseButton");
        m_closeBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_closeBtn->setFixedWidth(40);
    }
    m_widgetLayout->addWidget(m_closeBtn);

    _logic->addLayout(m_widgetLayout);
    this->setLayout(_logic);
}

FHNotifyWidget::~FHNotifyWidget() {
}

void FHNotifyWidget::setNotificationText(const QString &_text) {
    m_text = _text;
    m_textLbl->setText(m_text);
}

void FHNotifyWidget::setTimespan(int _msec) {
    m_timespan = _msec;
    m_timerBar->setMaximum(m_timespan);
}

void FHNotifyWidget::setWidgetFont(QFont _f) {
    m_font = _f;
    m_textLbl->setFont(m_font);
}

void FHNotifyWidget::notify() {
    if (m_timespan == 0) m_timespan = 3000;
    if (m_text.isEmpty()) m_textLbl->setText("Hello, World!");
    m_timerBar->setValue(0);

    this->show();
    // todo
}
