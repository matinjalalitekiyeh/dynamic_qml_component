#ifndef DQC_MODEL_HXX
#define DQC_MODEL_HXX

#include <QAbstractListModel>
#include "dqc_proprty.hxx"

namespace dqc {

class DQC_Roles {
    Q_GADGET
public:
    enum class roles {
        Data_source = Qt::UserRole + 1,
        Color,
        Initial_x,
        Initial_y,
        Interval,
        Random_num,
        Random_from,
        Random_to
    };
    Q_ENUM(roles)
};

class dqc_model
    : public QAbstractListModel {
    Q_OBJECT
public:
    explicit
        dqc_model(QObject *parent = nullptr);

    /*override.*/
    int rowCount([[__maybe_unused__]]const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index,
                 const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void add_dqc_rect(dqc::dqc_rect_properties *property);
    Q_INVOKABLE void add_dqc_rect();
    Q_INVOKABLE void remove_dqc_rect(const int index);

private:
    QList<dqc::dqc_rect_properties*> m_dqc_rect_properties;
};

}

#endif /* DQC_MODEL_HXX */
