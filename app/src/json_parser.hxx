#ifndef JSON_PARSER_HXX
#define JSON_PARSER_HXX

#include <QObject>
#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QColor>

namespace dqc {

struct frontend_t {
    QString id;
    QColor color;
    QString data_source;
    int x;
    int y;
};

struct backend_t {
    QString id;
    int msec;
    int min;
    int max;
};

class json_parser
    : public QObject {
    Q_OBJECT
public:
    explicit
        json_parser(QObject *parent = nullptr);
    ~json_parser() override = default;

    json_parser(const json_parser&) = delete;
    json_parser& operator=(const json_parser&) = delete;
    json_parser(const json_parser&&) = delete;
    json_parser& operator=(const json_parser&&) = delete;

    Q_INVOKABLE QVector<backend_t> load_backend_config(const QString& config_path);
    Q_INVOKABLE QVector<frontend_t> load_frontend_config(const QString& config_path);
};

}

#endif /* JSON_PARSER_HXX */
