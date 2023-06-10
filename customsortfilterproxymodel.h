#ifndef CUSTOMSORTFILTERPROXYMODEL_H
#define CUSTOMSORTFILTERPROXYMODEL_H

#include "QtCore/qdatetime.h"
#include <QSortFilterProxyModel>

class CustomSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    explicit CustomSortFilterProxyModel(QObject *parent = nullptr);

    void setSortField(const QString& field);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    QString m_sortField;
};

CustomSortFilterProxyModel::CustomSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void CustomSortFilterProxyModel::setSortField(const QString& field)
{
    m_sortField = field;
}

bool CustomSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    // Check if the columns being compared are the selected sort field
    if (leftData.type() == rightData.type() && leftData.type() != QVariant::Invalid && left.column() == 0 && right.column() == 0) {
        if (leftData.type() == QVariant::String) {
            QString leftString = leftData.toString();
            QString rightString = rightData.toString();

            // Compare the strings
            return QString::localeAwareCompare(leftString, rightString) < 0;
        } else if (leftData.type() == QVariant::Int) {
            int leftInt = leftData.toInt();
            int rightInt = rightData.toInt();

            // Compare the integers
            return leftInt < rightInt;
        } else if (leftData.type() == QVariant::Date) {
            QDate leftDate = leftData.toDate();
            QDate rightDate = rightData.toDate();

            // Compare the dates
            return leftDate < rightDate;
        }
    }

    // Use default sorting behavior
    return QSortFilterProxyModel::lessThan(left, right);
}



#endif // CUSTOMSORTFILTERPROXYMODEL_H
