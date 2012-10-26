#include "Status.hpp"

#include <QPainter>

using namespace corbasim::qt;

Status::Status(QWidget *parent) 
: QWidget(parent), m_color(Qt::darkRed)
{
    setFixedSize(20, 20);
}

Status::~Status() {}

void Status::setRedLight() { setColorLight(Qt::red); }
void Status::setYellowLight() { setColorLight(Qt::yellow); }
void Status::setGreenLight() { setColorLight(Qt::green); }

void Status::setColorLight(const QColor& color)
{
    m_color = color;
    repaint();
}

void Status::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);
    painter.drawEllipse(0, 0, width(), height());
}

