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

#include "FHNotifier.h"
#include "FHMessageBox.h"

#include <QtGlobal>

#include <Utils>
#include <FramelessWidgetsHelper>

#include <QHBoxLayout>

FHMessageBox::FHMessageBox(MessageBoxType _type, QColor _accentColor, bool _darkMode, QWidget *parent)
            : m_type(_type), m_accentColor(_accentColor), m_darkMode(_darkMode), FramelessDialog(parent) {
#if defined(Q_OS_LINUX)
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
#else
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
#endif
    this->setAttribute(Qt::WA_DeleteOnClose);
    // For now let's keep this size as default.
    this->setMinimumSize(QSize(350, 175));
    this->setFixedSize(QSize(350, 175));
    this->setPalette(themePalette(m_accentColor, m_darkMode));

    if (!m_widgetLayout)
        m_widgetLayout = new QVBoxLayout;
    m_widgetLayout->setSpacing(2);
    m_widgetLayout->setMargin(0);

    QWidget *_titleBar = new QWidget;
    {
        _titleBar->setObjectName("FHNotifierTitleBar");
        _titleBar->setFixedHeight(38);
    }
    QHBoxLayout *_titleBarLayout = new QHBoxLayout;
    {
        _titleBarLayout->setSpacing(0);
        _titleBarLayout->setMargin(0);
    }
    m_titleLbl = new QLabel("Message Box", this);
    {
        m_titleLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_titleLbl->setContentsMargins(12, 0, 0, 0);
    }
    _titleBarLayout->addWidget(m_titleLbl);
    m_closeBtn = new QPushButton(this);
    {
        m_closeBtn->setFixedSize(QSize(38, 38));
        m_closeBtn->setFont(QFont(ICON_FONT, ICON_FONT_SIZE));
        m_closeBtn->setText(CLOSE_POINT);
        m_closeBtn->setObjectName("FHNotifierCloseButton");
        connect(m_closeBtn, &QPushButton::clicked, this, [=]() {
            this->close();
        });
    }
    _titleBarLayout->addWidget(m_closeBtn);
    _titleBar->setLayout(_titleBarLayout);

    FramelessWidgetsHelper *_helper = FramelessWidgetsHelper::get(this);
    _helper->setTitleBarWidget(_titleBar);
    _helper->setHitTestVisible(m_closeBtn);
    m_widgetLayout->addWidget(_titleBar);

    QHBoxLayout *_contentLayout = new QHBoxLayout;
    _contentLayout->setMargin(6);
    m_iconBtn = new QPushButton(this);
    {
        m_iconBtn->setObjectName("FHNotifierIconButton");
        m_iconBtn->setFixedSize(QSize(72, 72));
        // Here we will only use Google's Material Icons.
        m_iconBtn->setFont(QFont("Material Icons Outlined", 32));
    }
    m_textLbl = new QLabel("Hello, World!", this);
    {
        m_textLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_textLbl->setWordWrap(true);
    }
    _contentLayout->addWidget(m_iconBtn);
    _contentLayout->addWidget(m_textLbl);
    _contentLayout->setAlignment(m_textLbl, Qt::AlignHCenter);
    m_widgetLayout->addLayout(_contentLayout);

    m_lBtns.append( m_firstBtn = new QPushButton(this) );
    {
        connect(m_firstBtn, &QPushButton::clicked, this, [=]() {
            emit firstButtonClicked();
        });
    }
    m_lBtns.append( m_secondBtn = new QPushButton(this) );
    {
        connect(m_secondBtn, &QPushButton::clicked, this, [=]() {
            emit secondaryButtonClicked();
        });
    }
    m_lBtns.append( m_thirdBtn = new QPushButton(this) );
    {
        connect(m_thirdBtn, &QPushButton::clicked, this, [=]() {
            emit thirdButtonClicked();
        });
    }
    foreach(QPushButton *_btn, m_lBtns) {
        _btn->setMinimumSize(QSize(60, 26));
        _btn->setObjectName("FHNotifierDecisionButton");
        _btn->hide();
    }
    
    QHBoxLayout *_buttonLayout = new QHBoxLayout;
    _buttonLayout->setMargin(6);
    // Fill up space until the buttons are displayed.
    QWidget *_spacer = new QWidget;
    _spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    _buttonLayout->addWidget(_spacer);
    // Change layout based on messagebox type.
    if (m_type == MessageBoxType::Ok) {
        // Set text.
        m_firstBtn->setText(tr("Ok"));
        // Show the button.
        m_firstBtn->show();
        // Add to the layout.
        _buttonLayout->addWidget(m_firstBtn);
    } else if (m_type == MessageBoxType::YesNo) {
        m_firstBtn->setText(tr("Yes"));
        m_secondBtn->setText(tr("No"));
        m_firstBtn->show();
        m_secondBtn->show();
        _buttonLayout->addWidget(m_firstBtn);
        _buttonLayout->addWidget(m_secondBtn);
    } else if (m_type == MessageBoxType::YesNoCancel) {
        m_firstBtn->setText(tr("Yes"));
        m_secondBtn->setText(tr("No"));
        m_thirdBtn->setText(tr("Cancel"));
        m_firstBtn->show();
        m_secondBtn->show();
        m_thirdBtn->show();
        _buttonLayout->addWidget(m_firstBtn);
        _buttonLayout->addWidget(m_secondBtn);
        _buttonLayout->addWidget(m_thirdBtn);
    }
    m_widgetLayout->addLayout(_buttonLayout);

    this->setLayout(m_widgetLayout);
}

FHMessageBox::~FHMessageBox() {
}

void FHMessageBox::setMessageBoxIcon(MessageBoxIcon _icon) {
    m_icon = _icon;
    switch (m_icon) {
        case Information: {
            m_iconBtn->setText("\uE88E");
            m_iconBtn->setStyleSheet(m_iconBtn->styleSheet() + "color: #74d0f1;");
        } break;
        case Warning: {
            m_iconBtn->setText("\uE002");
            m_iconBtn->setStyleSheet(m_iconBtn->styleSheet() + "color: #ffef00;");
        } break;
        case Error: {
            m_iconBtn->setText("\uE000");
            m_iconBtn->setStyleSheet(m_iconBtn->styleSheet() + "color: #cd001a;");
        } break;
    }
}

void FHMessageBox::setMessageBoxTitle(const QString &_title) {
    m_title = _title;
    m_titleLbl->setText(m_title);
}

void FHMessageBox::setText(const QString &_text) {
    m_text = _text;
    m_textLbl->setText(m_text);
}

void FHMessageBox::setButtonFont(QFont _f) {
    foreach(QPushButton *_btn, m_lBtns) {
        _btn->setFont(_f);
    }
}