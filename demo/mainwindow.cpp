#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *_centralWidget = new QWidget;
    QVBoxLayout *_layout = new QVBoxLayout(_centralWidget);

    // NotifyWidget
    QPushButton *_notifyWidgetTest = new QPushButton("Notify Widget", _centralWidget);
    {
        m_notifyWidget = new FHNotifyWidget(QColor(125, 30, 40), false);
        m_notifyWidget->setNotificationText("Color #5CA6 copied to clipboard");
        m_notifyWidget->setFixedWidth(250); // resize, let's find another way, default is 175x30
        m_notifyWidget->setTimespan(3500);
        m_notifyWidget->setCloseButtonDisabled();
        m_notifyWidget->notificationTextLabel()->setFont(QFont("Bahnschrift Semilight", 10));
        connect(_notifyWidgetTest, &QPushButton::clicked, m_notifyWidget, &FHNotifyWidget::notify);
    }
    _layout->addWidget(_notifyWidgetTest);

    // MessageBox
    QPushButton *_msgBoxTest = new QPushButton("Message Box", _centralWidget);
    {
        m_msgBox = new FHMessageBox(FHMessageBox::YesNo, QColor(125, 30, 40), false);
        m_msgBox->setMessageBoxTitle("ERROR! demo@mainwindow.cpp:25");
        m_msgBox->setMessageBoxIcon(FHMessageBox::Error);
        m_msgBox->setText("Missing some informations @mainwindow.cpp:L25!DoSomeMagic.dll. Please restart the application and contact the maintainer.");
        m_msgBox->titleWidget()->setFont(QFont("Segoe UI SemiBold", 9));
        m_msgBox->textWidget()->setFont(QFont("Segoe UI", 9));
        m_msgBox->setButtonFont(QFont("Segoe UI", 9));
        m_msgBox->firstButton()->setText("Understood!");
        m_msgBox->secondaryButton()->setText("What on earth?!");
        connect(_msgBoxTest, &QPushButton::clicked, this, [=]() {
            m_msgBox->show();
        });
        connect(m_msgBox, &FHMessageBox::firstButtonClicked, this, [=]() {
            qDebug() << "They understood!";
        });
        connect(m_msgBox, &FHMessageBox::secondaryButtonClicked, this, [=]() {
            qDebug() << "They don't understood!";
        });
    }
    _layout->addWidget(_msgBoxTest);

    _centralWidget->setLayout(_layout);
    this->setCentralWidget(_centralWidget);
}

MainWindow::~MainWindow() {
}
