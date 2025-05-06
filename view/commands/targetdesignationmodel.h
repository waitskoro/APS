#include <vector>
#include <array>

#include <QAbstractListModel>

namespace Commands {

class TargetDesignationModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TargetDesignationModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void append(short azimuth, short elevation);
    void append(const std::array<short, 2>& newCoordinates);

    const std::vector<std::array<short, 2>>& coordinates() const;

private:
    std::vector<std::array<short, 2>> m_values;
};

}
