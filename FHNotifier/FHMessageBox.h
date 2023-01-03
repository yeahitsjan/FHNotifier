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

#ifndef __FHMessageBox_h__
#define __FHMessageBox_h__

#include <FramelessWidget>
#include <QObject>

#include <QPointer>
#include <QList>

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

FRAMELESSHELPER_USE_NAMESPACE

class FHMessageBox : public FramelessWidget {
    Q_OBJECT
public:
    enum MessageBoxType {
        Ok,
        YesNo,
        YesNoCancel
    };
    enum MessageBoxIcon {
        Information,
        Warning,
        Error
    };
    FHMessageBox(MessageBoxType _type, QColor _accentColor, bool _darkMode, QWidget *parent = nullptr);
    ~FHMessageBox();

    // Set the icon of the message box.
    void setMessageBoxIcon(MessageBoxIcon _icon);
    MessageBoxIcon messageBoxIcon();

    // Set the title of the message box (window title).
    void setMessageBoxTitle(const QString &_title);
    QString messageBoxTitle() { return m_title; }

    // Set the text to be displayed in the message box.
    void setText(const QString &_text);
    QString text() { return m_text; }

    // Return both text holder widgets.
    QLabel* titleWidget() { return m_titleLbl; }
    QLabel* textWidget() { return m_textLbl; }

    // Return the buttons to allow styling them.
    QPushButton* firstButton() { return m_firstBtn; }
    QPushButton* secondaryButton() { return m_secondBtn; }
    QPushButton* thirdButton() { return m_thirdBtn; }

protected:
    MessageBoxType m_type;
    MessageBoxIcon m_icon;
    QColor m_accentColor;
    bool m_darkMode;

    QString m_title;
    QString m_text;

    QPointer<QVBoxLayout> m_widgetLayout;
    
    // Titlebar
    QLabel *m_titleLbl;
    QPushButton *m_closeBtn;

    // Content
    QPushButton *m_iconBtn;
    QLabel *m_textLbl;

    // Buttons (depending on choice)
    QPushButton *m_firstBtn;
    QPushButton *m_secondBtn;
    QPushButton *m_thirdBtn;
    QList<QPushButton*> m_lBtns;
};

#endif // __FHMessageBox_h__