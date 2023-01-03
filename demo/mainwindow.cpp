#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *_centralWidget = new QWidget;
    QVBoxLayout *_layout = new QVBoxLayout(_centralWidget);

    // NotifyWidget
    QPushButton *_notifyWidgetTest = new QPushButton("Notify Widget", _centralWidget);
    {
        m_notifyWidget = new FHNotifyWidget(QColor(125, 30, 40), false, nullptr);
        m_notifyWidget->setNotificationText("Color #5CA6 copied to clipboard");
        m_notifyWidget->setFixedWidth(250); // resize, let's find another way, default is 175x30
        m_notifyWidget->setTimespan(3500);
        m_notifyWidget->notificationTextLabel()->setFont(QFont("Bahnschrift Semilight", 10));
        connect(_notifyWidgetTest, &QPushButton::clicked, m_notifyWidget, &FHNotifyWidget::notify);
    }
    _layout->addWidget(_notifyWidgetTest);

    _centralWidget->setLayout(_layout);
    this->setCentralWidget(_centralWidget);
}

MainWindow::~MainWindow() {
}
