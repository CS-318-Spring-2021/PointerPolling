#include "mainwindow.h"

#include <QtWidgets>
#include <QDebug>

#include "pollinggraphicsview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *w = new QWidget();
    setCentralWidget(w);

    QHBoxLayout *mainLayout = new QHBoxLayout(w);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(table = new QTableWidget());
    rightLayout->addWidget(saveButton = new QPushButton("Save"));
    rightLayout->addWidget(processButton = new QPushButton("Process\ndrawing"));

    connect(saveButton, &QPushButton::clicked, this, &MainWindow::bSave);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::bProcess);

    QVBoxLayout *leftLayout = new QVBoxLayout();

    leftLayout->addWidget(view = new PollingGraphicsView(), 3);
    leftLayout->addWidget(console = new QTextEdit(), 1);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    table->setColumnCount(5);
    table->setColumnWidth(0, 10);
    table->setColumnWidth(1, 25);
    table->setColumnWidth(2, 25);
    table->setColumnWidth(3, 25);
    table->setColumnWidth(4, 100);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setMinimumWidth(350);
    table->verticalHeader()->setVisible(false);

    table->setHorizontalHeaderLabels(QStringList() << "Evt" << "t" << "x" << "y" << "Notes");
    connect(view, &PollingGraphicsView::mouseEvent, this, &MainWindow::onMouseEvent);
    connect(view, &PollingGraphicsView::sketchCleared, this, &MainWindow::sketchCleared);
    connect(table, &QTableWidget::currentCellChanged, this, &MainWindow::updateCrosshairs);

    when0 = 0;
}

void MainWindow::sketchCleared() {
    table->setRowCount(0);

    when0 = 0;
}

void MainWindow::bProcess() {
    console->append("Did some stuff; here are the results!");
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateCrosshairs(int curRow, int, int, int) {
    if (curRow==-1)  // If no selection, curRow==-1; hide crosshairs and don't try to update position!
        view->setCrosshairsVisible(false);
    else {
        view->setCrosshairsVisible(true);
        view->setCrosshairsPos(QPointF(table->item(curRow, 2)->text().toDouble(), table->item(curRow, 3)->text().toDouble()));
    }
}

void MainWindow::bSave() {
    QString fName = QFileDialog::getSaveFileName(this, "Enter save filename", QString(), tr("Comma-separated values (*.csv)"));
    if (fName.isEmpty()) return;

    QFile fOut(fName);
    if (!fOut.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::warning(this, "Error opening file", "Can't open selected file for output.");
        return;
    }

    QTextStream out(&fOut);
    out << "Evt,t,x,y,Notes\n";
    for (int row = 0; row < table->rowCount(); ++row) {
        out << table->item(row, 0)->text() << "," << table->item(row, 1)->text() << "," << table->item(row, 2)->text() << "," << table->item(row, 3)->text();
        QString note = table->item(row, 4)->text();
        if (!note.isEmpty()) out << "," << note;
        out << "\n";
    }

    return;
}

void MainWindow::onMouseEvent(int type, ulong when, QPointF pos) {
    static QString types = "PRM";

    if (when0==0) when0 = when;

    int row;
    table->setRowCount((row = table->rowCount())+1);

    table->setItem(row, 0, new QTableWidgetItem(types.mid(type, 1)));
    table->setItem(row, 1, new QTableWidgetItem(QString::number(when-when0)));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(pos.x())));
    table->setItem(row, 3, new QTableWidgetItem(QString::number(pos.y())));

    QTableWidgetItem *note = new QTableWidgetItem("");
    note->setFlags(note->flags() | Qt::ItemIsEditable);
    table->setItem(row, 4, note);

}
