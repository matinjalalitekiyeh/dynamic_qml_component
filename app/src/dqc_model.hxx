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

    /**
    * @brief Adds an existing dqc_rect_properties object to the model
    *
    * @param property Pointer to the dqc_rect_properties object to add
    *
    * @note The model takes ownership of the property object
    * @note Emits rowsInserted() signal after addition
    * @note Q_INVOKABLE makes this method callable from QML
    */
    Q_INVOKABLE void add_dqc_rect(dqc::dqc_rect_properties *property);

    /**
    * @brief Creates and adds a new dqc_rect_properties object to the model
    *
    * @note Creates a default-initialized dqc_rect_properties object
    * @note Emits rowsInserted() signal after addition
    * @note Q_INVOKABLE makes this method callable from QML
    */
    Q_INVOKABLE void add_dqc_rect();

    /**
    * @brief Removes a dqc_rect_properties object from the model at the specified index
    *
    * @param index Row index of the item to remove
    *
    * @note Deletes the removed dqc_rect_properties object
    * @note Emits rowsRemoved() signal after removal
    * @note Q_INVOKABLE makes this method callable from QML
    *
    * @warning Index must be valid (0 <= index < rowCount())
    */
    Q_INVOKABLE void remove_dqc_rect(const int index);

private:
    QList<dqc::dqc_rect_properties*> m_dqc_rect_properties;
};

}

#endif /* DQC_MODEL_HXX */
