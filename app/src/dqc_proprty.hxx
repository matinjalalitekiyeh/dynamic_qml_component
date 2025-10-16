#ifndef DQC_PROPERTY_HXX
#define DQC_PROPERTY_HXX

#include <QObject>
#include <QColor>
#include <QString>

namespace dqc {

class dqc_rect_properties
    : public QObject {

    Q_PROPERTY(QString data_source READ data_source WRITE set_data_source NOTIFY data_source_changed FINAL)
    Q_PROPERTY(QColor color READ color WRITE set_color NOTIFY color_changed FINAL)

    Q_PROPERTY(int initial_x READ initial_x WRITE set_initial_x NOTIFY initial_x_changed FINAL)
    Q_PROPERTY(int initial_y READ initial_y WRITE set_initial_y NOTIFY initial_y_changed FINAL)

    Q_PROPERTY(int interval READ interval WRITE set_interval NOTIFY interval_changed FINAL)

    Q_PROPERTY(int random_num READ random_num WRITE set_random_num NOTIFY random_num_changed FINAL)
    Q_PROPERTY(int random_from READ random_from WRITE set_random_from NOTIFY random_from_changed FINAL)
    Q_PROPERTY(int random_to READ random_to WRITE set_random_to NOTIFY random_to_changed FINAL)

    Q_OBJECT
public:
    explicit
        dqc_rect_properties(QObject *parent = nullptr);

    dqc_rect_properties(const dqc_rect_properties&) = delete;
    dqc_rect_properties& operator=(const dqc_rect_properties&) = delete;
    dqc_rect_properties(const dqc_rect_properties&&) = delete;
    dqc_rect_properties& operator=(const dqc_rect_properties&&) = delete;

    QString data_source() const;
    void set_data_source(const QString &newData_source);

    QColor color() const;
    void set_color(const QColor &newColor);

    int initial_x() const;
    void set_initial_x(int newInitial_x);

    int initial_y() const;
    void set_initial_y(int newInitial_y);

    int interval() const;
    void set_interval(int newInterval);

    int random_num() const;
    void set_random_num(int newRandom_num);

    int random_from() const;
    void set_random_from(int newRandom_from);

    int random_to() const;
    void set_random_to(int newRandom_to);

signals:
    void data_source_changed();
    void color_changed();
    void initial_x_changed();
    void initial_y_changed();
    void interval_changed();
    void random_num_changed();
    void random_from_changed();
    void random_to_changed();

private:
    QString m_data_source;
    QColor  m_color;
    int     m_initial_x;
    int     m_initial_y;
    int     m_interval;
    int     m_random_num;
    int     m_random_from;
    int     m_random_to;
};

}

#endif /* DQC_PROPERTY_HXX */
