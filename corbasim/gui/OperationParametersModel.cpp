#include "OperationParametersModel.hpp"
#include <iostream>

using namespace corbasim::gui;

OperationParametersModel::OperationParametersModel(QObject *parent)
    : QStandardItemModel(parent), m_reflective(NULL)
{
    QStringList headers;
    headers << "Parameters";

    setHorizontalHeaderLabels(headers);
}

OperationParametersModel::~OperationParametersModel()
{
}

bool OperationParametersModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    // TODO get the current value
    
    bool res = QStandardItemModel::setData(index, value, role);

    if (role == Qt::CheckStateRole)
    {
        QList< int > path;

        QModelIndex parent = index;

        // Calculate path
        do {
            path.push_front(parent.row());
            parent = parent.parent();
        } while(parent.isValid());
        
        if (path.size() > 1)
        {
            // Remove instance index
            path.pop_front();

            QStandardItem * mitem = itemFromIndex(index);

            if (mitem->checkState() == Qt::Checked)
                emit checked(m_reflective, path);
            else
                emit unchecked(m_reflective, path);
        }
    }

    return res;
}

corbasim::core::operation_reflective_base const * 
OperationParametersModel::getReflective(const QString& id) const
{
    return m_reflective;
}

void OperationParametersModel::insertRecursive(QStandardItem * parent, 
        corbasim::core::reflective_base const * reflective)
{
    const corbasim::core::reflective_type type = reflective->get_type();

    const bool process = (type == corbasim::core::TYPE_STRUCT ||
            type == corbasim::core::TYPE_UNION);

    if (!process) return;

    const unsigned int count = reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        corbasim::core::reflective_base const * child =
            reflective->get_child(i);

        const corbasim::core::reflective_type type = child->get_type();

        bool bIsCheckable = isCheckable(child);

        QStandardItem * childItem = 
            new QStandardItem(reflective->get_child_name(i));
        childItem->setEditable(false);
        childItem->setCheckable(bIsCheckable);

        // Recursive
        if (type == corbasim::core::TYPE_STRUCT ||
                type == corbasim::core::TYPE_UNION)
        {
            insertRecursive(childItem, child);
        }
        else if (child->is_repeated())
        {
            unsigned int length = 1;
            
            if (!child->is_variable_length())
            {
                length = child->get_length(core::holder());
            }

            bool bIsCheckable = isCheckable(child->get_slice());

            for (int j = 0; j < length; j++) 
            {
                QStandardItem * item = new QStandardItem(QString("%1").arg(j));

                item->setEditable(false);
                item->setCheckable(bIsCheckable);

                insertRecursive(item, child->get_slice());
                childItem->appendRow(item);
            }
        }

        // TODO union

        parent->appendRow(childItem);
    }
}

bool OperationParametersModel::isCheckable(core::reflective_base const * reflective)
{
    return true;
}

void OperationParametersModel::initialize(
        corbasim::core::operation_reflective_base const * op)
{
    QStandardItem * opItem = new QStandardItem(op->get_name());
    opItem->setEditable(false);
    opItem->setCheckable(isCheckable(op));

    insertRecursive(opItem, op);
    appendRow(opItem);

    m_reflective = op;
}

void OperationParametersModel::uncheck(const QList< int >& path)
{
    // Instance element
    QModelIndex idx = index(0, 0);
    
    for (int i = 0; i < path.size(); i++) 
    {
        idx = index(path[i], 0, idx);
    }

    QStandardItem * item = itemFromIndex(idx);

    item->setCheckState(Qt::Unchecked);
}

void OperationParametersModel::check(const QList< int >& path)
{
    // Instance element
    QModelIndex idx = index(0, 0);
    
    for (int i = 0; i < path.size(); i++) 
    {
        idx = index(path[i], 0, idx);
    }

    QStandardItem * item = itemFromIndex(idx);

    item->setCheckState(Qt::Checked);
}

