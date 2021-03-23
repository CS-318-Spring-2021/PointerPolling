#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PollingGraphicsView;
class QTableWidget;
class QPushButton;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    PollingGraphicsView *view;
    QTableWidget *table;
    QPushButton *saveButton, *processButton;
    QTextEdit *console;

    int when0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onMouseEvent(int type, int when, QPointF scenePos);
    void bSave();
    void updateCrosshairs(int curRow, int curCol, int prevRow, int prevCol);
    void bProcess();
    void sketchCleared();
};
#endif // MAINWINDOW_H
