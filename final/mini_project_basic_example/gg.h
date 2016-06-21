#ifndef GG_H
#define GG_H

#include <QWidget>

class gg : public QWidget
{
    Q_OBJECT
public:
    explicit gg(QWidget *parent = 0);
    ~gg();
protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:
};

#endif // GG_H
