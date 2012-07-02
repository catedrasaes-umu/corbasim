#ifndef CORBASIM_QT_PLOTMODEL_HPP
#define CORBASIM_QT_PLOTMODEL_HPP

#include <QStandardItemModel>
#include <corbasim/core/reflective_fwd.hpp>
#include <list>
#include <corbasim/qt/export.hpp>

namespace corbasim
{
namespace qt
{

class CORBASIM_QT_DECLSPEC ParametersModel : public QStandardItemModel
{
    Q_OBJECT

public:
    ParametersModel(QObject *parent = 0);
    virtual ~ParametersModel();

public slots:

    void registerInstance(const QString& name,
            core::interface_reflective_base const * reflective);

    void unregisterInstance(const QString& name);

signals:

    void clicked(const QString& id, 
            core::interface_reflective_base const * reflective,
            const QList< int >& path);

protected:

    struct FirstLevelItem
    {
        QString name;
        core::interface_reflective_base const * reflective;
    };

    typedef std::list< FirstLevelItem > FirstLevelItems_t;

    FirstLevelItems_t m_items;
};

} // qt
} // corbasim

#endif // CORBASIM_QT_PLOTMODEL_HPP

