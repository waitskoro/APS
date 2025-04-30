#include "targetdesignationmodel.h"

using namespace Commands;

TargetDesignationModel::TargetDesignationModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_values = new std::vector<std::array<short, 2>>;
}

void TargetDesignationModel::append(short newCoordinates[2])
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_values->push_back({newCoordinates[0], newCoordinates[1]});
    endInsertRows();
}

int TargetDesignationModel::rowCount(const QModelIndex &) const
{
    return m_values->size();
}

int TargetDesignationModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant TargetDesignationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 ||
        static_cast<size_t>(index.row()) >= m_values->size())
    {
        return QVariant();
    }

    const auto& coords = m_values->at(index.row());

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 0: return coords[0]; //Azimuth
            case 1: return coords[1]; //Elevation
            default: return QVariant();
        }
    }

    return QVariant();
}

QVariant TargetDesignationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return QString("Текущий азимут");
            case 1: return QString("Текущий угол места");
            default: return QString("");
        }
    }
    return QVariant();
}
