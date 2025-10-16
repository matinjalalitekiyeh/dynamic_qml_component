#include "json_parser.hxx"
#include <QDir>

namespace dqc {

json_parser::json_parser(QObject *parent)
    : QObject(parent)
{
}

QVector<backend_t> dqc::json_parser::load_backend_config(const QString &config_path)
{
    QFile config_file(config_path);
    QVector<backend_t> ret_vect;
    if (!config_file.open(QIODevice::ReadOnly)) {
        qWarning() << "Current directory:" << QDir::currentPath();
        qWarning() << "Could not open backend config file:" << config_path;
        return ret_vect;
    }

    QByteArray config_data = config_file.readAll();
    QJsonDocument config_doc = QJsonDocument::fromJson(config_data);

    if (!config_doc.isArray()) {
        qWarning() << "Invalid backend config format - expected array";
        return ret_vect;
    }

    QJsonArray config_array = config_doc.array();

    for (const QJsonValue& value : std::as_const(config_array)) {
        QJsonObject config_obj = value.toObject();
        backend_t backend;

        backend.id = config_obj["id"].toString();
        backend.msec = config_obj["msec"].toInt();
        backend.min = config_obj["min"].toInt();
        backend.max = config_obj["max"].toInt();

        if (backend.id.isEmpty() || backend.msec <= 0 || backend.min >= backend.max) {
            qWarning() << "Invalid generator configuration:" << backend.id << backend.msec << backend.min << backend.max;
            continue;
        }

        ret_vect.append(backend);
    }

 return ret_vect;
}

QVector<frontend_t> dqc::json_parser::load_frontend_config(const QString &config_path)
{
    QFile config_file(config_path);
    QVector<frontend_t> ret_vect;
    if (!config_file.open(QIODevice::ReadOnly)) {
        qWarning() << "Current directory:" << QDir::currentPath();
        qWarning() << "Could not open backend config file:" << config_path;
        return ret_vect;
    }

    QByteArray config_data = config_file.readAll();
    QJsonDocument config_doc = QJsonDocument::fromJson(config_data);

    if (!config_doc.isArray()) {
        qWarning() << "Invalid backend config format - expected array";
        return ret_vect;
    }

    QJsonArray config_array = config_doc.array();

    for (const QJsonValue& value : std::as_const(config_array)) {
        QJsonObject config_obj = value.toObject();
        frontend_t front;
        front.id = config_obj["id"].toString();
        front.x = config_obj["x"].toInt();
        front.y = config_obj["y"].toInt();
        front.color = QColor(config_obj["color-hex"].toString());
        front.data_source = config_obj["dataSource"].toString();

        if (front.id.isEmpty()) {
            qWarning() << "Invalid generator configuration:" << front.id;
            continue;
        }

        ret_vect.append(front);
    }

    return ret_vect;
}

}
