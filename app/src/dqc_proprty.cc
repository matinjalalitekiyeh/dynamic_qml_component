#include "dqc_proprty.hxx"

namespace dqc {

dqc_rect_properties::dqc_rect_properties(QObject *parent)
    : QObject(parent)
    , m_data_source("")
    , m_color(Qt::GlobalColor::black)
    , m_initial_x(0)
    , m_initial_y(0)
    , m_interval(0)
    , m_random_num(0)
    , m_random_from(0)
    , m_random_to(0)
{

}

QString dqc_rect_properties::data_source() const
{
    return m_data_source;
}

void dqc_rect_properties::set_data_source(const QString &newData_source)
{
    if (m_data_source == newData_source)
        return;
    m_data_source = newData_source;
    emit data_source_changed();
}

QColor dqc_rect_properties::color() const
{
    return m_color;
}

void dqc_rect_properties::set_color(const QColor &newColor)
{
    if (m_color == newColor)
        return;
    m_color = newColor;
    emit color_changed();
}

int dqc_rect_properties::initial_x() const
{
    return m_initial_x;
}

void dqc_rect_properties::set_initial_x(int newInitial_x)
{
    if (m_initial_x == newInitial_x)
        return;
    m_initial_x = newInitial_x;
    emit initial_x_changed();
}

int dqc_rect_properties::initial_y() const
{
    return m_initial_y;
}

void dqc_rect_properties::set_initial_y(int newInitial_y)
{
    if (m_initial_y == newInitial_y)
        return;
    m_initial_y = newInitial_y;
    emit initial_y_changed();
}

int dqc_rect_properties::interval() const
{
    return m_interval;
}

void dqc_rect_properties::set_interval(int newInterval)
{
    if (m_interval == newInterval)
        return;
    m_interval = newInterval;
    emit interval_changed();
}

int dqc_rect_properties::random_num() const
{
    return m_random_num;
}

void dqc_rect_properties::set_random_num(int newRandom_num)
{
    if (m_random_num == newRandom_num)
        return;
    m_random_num = newRandom_num;
    emit random_num_changed();
}

int dqc_rect_properties::random_from() const
{
    return m_random_from;
}

void dqc_rect_properties::set_random_from(int newRandom_from)
{
    if (m_random_from == newRandom_from)
        return;
    m_random_from = newRandom_from;
    emit random_from_changed();
}

int dqc_rect_properties::random_to() const
{
    return m_random_to;
}

void dqc_rect_properties::set_random_to(int newRandom_to)
{
    if (m_random_to == newRandom_to)
        return;
    m_random_to = newRandom_to;
    emit random_to_changed();
}

}
