#ifndef POLLINGGRAPHICSVIEW_H
#define POLLINGGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

class QGraphicsPathItem;

class PollingGraphicsView : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene mScene;
    QPointF lastPos;
    QGraphicsPathItem *crosshairs;

    void maybeAddSegment(const QPointF &pos);

public:
    enum { MousePressed, MouseReleased, MouseMoved };

    PollingGraphicsView();

    void setCrosshairsVisible(bool visible);
    void setCrosshairsPos(const QPointF &pos);

protected:
    virtual void mousePressEvent(QMouseEvent *evt) override;
    virtual void mouseReleaseEvent(QMouseEvent *evt) override;
    virtual void mouseMoveEvent(QMouseEvent *evt) override;

signals:
    void mouseEvent(int type, int when, QPointF pos);
};

#endif // POLLINGGRAPHICSVIEW_H
