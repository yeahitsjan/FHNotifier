#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *_centralWidget = new QWidget;
    QVBoxLayout *_layout = new QVBoxLayout(_centralWidget);

    QPushButton *_notifyWidgetTest = new QPushButton("Notify Widget", _centralWidget);
    m_notifyWidget = new FHNotifyWidget(QColor(125, 30, 40), false, nullptr);
    m_notifyWidget->setNotificationText("Screenshot saved!");
    m_notifyWidget->setTimespan(5000);
    m_notifyWidget->setWidgetFont(QFont("Segoe UI Semilight", 9));
    connect(_notifyWidgetTest, &QPushButton::clicked, m_notifyWidget, &FHNotifyWidget::notify);
    _layout->addWidget(_notifyWidgetTest);

    _centralWidget->setLayout(_layout);
    this->setCentralWidget(_centralWidget);
}

MainWindow::~MainWindow() {
}
