#ifndef CORBA_QT_STATUS_HPP
#define CORBA_QT_STATUS_HPP

#include <QWidget>
#include <QColor>

namespace corbasim
{
namespace qt
{

class Status : public QWidget
{
    Q_OBJECT

public:
    Status(QWidget *parent = 0);
    virtual ~Status();

public slots:
    void setRedLight();
    void setYellowLight();
    void setGreenLight();

protected:
    void setColorLight(const QColor& color);

    virtual void paintEvent(QPaintEvent *);

    QColor m_color;
};

} // qt
} // corbasim

#endif // CORBA_QT_STATUS_HPP
