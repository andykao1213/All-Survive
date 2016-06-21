#ifndef GETREADY_H
#define GETREADY_H

#include <QWidget>

class getready : public QWidget
{
    Q_OBJECT
public:
    explicit getready(QWidget *parent = 0);
    ~getready();
protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:
};

#endif // GETREADY_H
