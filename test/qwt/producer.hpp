#ifndef PRODUCER_
#define PRODUCER_

#include <QtGui>

class DataProducer : public QWidget
{
    Q_OBJECT
public:
    DataProducer(QWidget * parent = 0) :
        QWidget(parent)
    {
        QVBoxLayout * layout = new QVBoxLayout();

        sb = new QSpinBox();
        layout->addWidget(sb);

        QPushButton * bt = new QPushButton("Append");

        QObject::connect(bt, SIGNAL(clicked()),
                this, SLOT(btClicked()));
        layout->addWidget(bt);

        setLayout(layout);
    }

private slots:
    void btClicked()
    {
        emit produced(sb->value());
    }

signals:

    void produced(double);

protected:
    QSpinBox * sb;

};


#endif /* PRODUCER_ */
