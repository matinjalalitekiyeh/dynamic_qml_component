#include "json_parser.hxx"
#include <QDir>

namespace dqc {

json_parser::json_parser(QObject *parent)
    : QObject(parent)
{
}

bool dqc::json_parser::load_backend_config(const QString &config_path)
{
    QFile config_file(config_path);
    if (!config_file.open(QIODevice::ReadOnly)) {
        qWarning() << "Current directory:" << QDir::currentPath();
        qWarning() << "Could not open backend config file:" << config_path;
        return false;
    }

    QByteArray config_data = config_file.readAll();
    QJsonDocument config_doc = QJsonDocument::fromJson(config_data);

    if (!config_doc.isArray()) {
        qWarning() << "Invalid backend config format - expected array";
        return false;
    }

    QJsonArray config_array = config_doc.array();

    qInfo() << "Backend";
    for (const QJsonValue& value : std::as_const(config_array)) {
        QJsonObject config_obj = value.toObject();

        QString id = config_obj["id"].toString();
        int msec = config_obj["msec"].toInt();
        int min = config_obj["min"].toInt();
        int max = config_obj["max"].toInt();

        if (id.isEmpty() || msec <= 0 || min >= max) {
            qWarning() << "Invalid generator configuration:" << id << msec << min << max;
            continue;
        }

        qInfo() << "Id: " << id << " msec: " << msec << " min: " << min << " max: " << max;
    }

    return true;
}

bool dqc::json_parser::load_frontend_config(const QString &config_path)
{
    QFile config_file(config_path);
    if (!config_file.open(QIODevice::ReadOnly)) {
        qWarning() << "Current directory:" << QDir::currentPath();
        qWarning() << "Could not open backend config file:" << config_path;
        return false;
    }

    QByteArray config_data = config_file.readAll();
    QJsonDocument config_doc = QJsonDocument::fromJson(config_data);

    if (!config_doc.isArray()) {
        qWarning() << "Invalid backend config format - expected array";
        return false;
    }

    QJsonArray config_array = config_doc.array();

    qInfo() << "Frontend";
    for (const QJsonValue& value : std::as_const(config_array)) {
        QJsonObject config_obj = value.toObject();

        QString id = config_obj["id"].toString();
        int x = config_obj["x"].toInt();
        int y = config_obj["y"].toInt();
        QString color_hex = config_obj["color-hex"].toString();
        QString data_source = config_obj["dataSource"].toString();

        if (id.isEmpty()) {
            qWarning() << "Invalid generator configuration:" << id;
            continue;
        }

        qInfo() << "id: " << id << " x: " << x << " y: " << y << " color: " << color_hex << " datasrc: " << data_source;
    }

    return true;
}

}
