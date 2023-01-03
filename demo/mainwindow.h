#pragma once

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <FHNotifier/FHNotifyWidget.h>
#include <FHNotifier/FHMessageBox.h>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    FHNotifyWidget *m_notifyWidget;
    FHMessageBox *m_msgBox;
};
