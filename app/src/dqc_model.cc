#include "dqc_model.hxx"

namespace dqc {

dqc_model::dqc_model(QObject *parent)
    : QAbstractListModel(parent)
{
}

int dqc_model::rowCount([[__maybe_unused__]]const QModelIndex &parent) const
{
    return m_dqc_rect_properties.size();
}

QVariant dqc_model::data(const QModelIndex &index, int role) const
{
    if(index.row()<0||index.row()>=m_dqc_rect_properties.size()) {
        return QVariant();
    }

    auto property = m_dqc_rect_properties.at( index.row() );
    const auto type = static_cast<dqc::DQC_Roles::roles>(role);

    if(type == DQC_Roles::roles::Data_source)
        return property->data_source();
    if(type == DQC_Roles::roles::Color)
        return property->color();
    if(type == DQC_Roles::roles::Initial_x)
        return property->initial_x();
    if(type == DQC_Roles::roles::Initial_y)
        return property->initial_y();
    if(type == DQC_Roles::roles::Interval)
        return property->interval();
    if(type == DQC_Roles::roles::Random_num)
        return property->random_num();
    if(type == DQC_Roles::roles::Random_from)
        return property->random_from();
    if(type == DQC_Roles::roles::Random_to)
        return property->random_to();

    return QVariant();
}

bool dqc_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto property = m_dqc_rect_properties.at( index.row() );
    const auto type = static_cast<dqc::DQC_Roles::roles>(role);
    bool something_changed = false; /* to avoid multireturn */

    switch(type) {
    case dqc::DQC_Roles::roles::Data_source: {
        if(property->data_source()!=value.toString()){
            property->set_data_source(value.toString());
            something_changed=true;
        }
    }
    break;
    case dqc::DQC_Roles::roles::Color: {
        if(property->color()!=value.value<QColor>()){
            property->set_color(value.value<QColor>());
            something_changed=true;
        }
    }
    break;
    case dqc::DQC_Roles::roles::Initial_x: {
        if(property->initial_x()!=value.toInt()){
            property->set_initial_x(value.toInt());
            something_changed=true;
        }
    }
    break;
    case dqc::DQC_Roles::roles::Initial_y: {
        if(property->initial_y()!=value.toInt()){
            property->set_initial_y(value.toInt());
            something_changed=true;
        }
    }
    break;
    case dqc::DQC_Roles::roles::Interval: {
        if(property->interval()!=value.toInt()){
            property->set_interval(value.toInt());
            something_changed=true;
        }
    }
    break;
    case dqc::DQC_Roles::roles::Random_num: {
        if(property->random_num()!=value.toInt()){
            property->set_random_num(value.toInt());
            something_changed=true;
        }
    }
    break;
    case dqc::DQC_Roles::roles::Random_from: {
        if(property->random_from()!=value.toInt()){
            property->set_random_from(value.toInt());
            something_changed=true;
        }
    }
    break;
    case dqc::DQC_Roles::roles::Random_to: {
        if(property->random_to()!=value.toInt()){
            property->set_random_to(value.toInt());
            something_changed=true;
        }
    }
    break;
    }
    if(something_changed) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags dqc_model::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> dqc_model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(dqc::DQC_Roles::roles::Data_source)] = "data_source";
    roles[static_cast<int>(dqc::DQC_Roles::roles::Color)] = "_color";
    roles[static_cast<int>(dqc::DQC_Roles::roles::Initial_x)] = "initial_x";
    roles[static_cast<int>(dqc::DQC_Roles::roles::Initial_y)] = "initial_y";
    roles[static_cast<int>(dqc::DQC_Roles::roles::Interval)] = "interval";
    roles[static_cast<int>(dqc::DQC_Roles::roles::Random_num)] = "random_num";
    roles[static_cast<int>(dqc::DQC_Roles::roles::Random_from)] = "random_from";
    roles[static_cast<int>(dqc::DQC_Roles::roles::Random_to)] = "random_to";

    return roles;
}

void dqc_model::add_dqc_rect(dqc::dqc_rect_properties *property)
{
    const auto index = m_dqc_rect_properties.size();
    beginInsertRows(QModelIndex(), index, index);
    m_dqc_rect_properties.append(property);
    endInsertRows();
}

void dqc_model::add_dqc_rect()
{
    auto *property = new dqc::dqc_rect_properties(this);
    property->set_color("red");
    add_dqc_rect(property);
}

void dqc_model::remove_dqc_rect(const int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_dqc_rect_properties.removeAt(index);
    endRemoveRows();
}

}
