#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PollingGraphicsView;
class QTableWidget;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    PollingGraphicsView *view;
    QTableWidget *table;
    QPushButton *saveButton;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onMouseEvent(int type, int when, QPointF scenePos);
    void bSave();
    void updateCrosshairs(int curRow, int curCol, int prevRow, int prevCol);
};
#endif // MAINWINDOW_H
