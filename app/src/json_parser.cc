#include "json_parser.hxx"
#include <QDir>

namespace dqc {

json_parser::json_parser(QObject *parent)
    : QObject(parent)
{
}

QVector<backend_t> dqc::json_parser::load_backend_config(const QString &config_path)
{
    QVector<backend_t> ret_vect;

    /* Validate input path */
    if (config_path.isEmpty()) {
        qWarning() << "Configuration path is empty";
        return ret_vect;
    }

    QFile config_file(config_path);

    /* Attempt to open the configuration file */
    if (!config_file.open(QIODevice::ReadOnly)) {
        qWarning() << "Current directory:" << QDir::currentPath();
        qWarning() << "Could not open backend config file:" << config_path
                   << "Error:" << config_file.errorString();
        return ret_vect;
    }

    /* Read and validate file content */
    QByteArray config_data = config_file.readAll();
    config_file.close();

    if (config_data.isEmpty()) {
        qWarning() << "Backend configuration file is empty:" << config_path;
        return ret_vect;
    }

    QJsonParseError parse_error;
    QJsonDocument config_doc = QJsonDocument::fromJson(config_data, &parse_error);

    /* Check for JSON parsing errors */
    if (parse_error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error in backend config" << config_path
                   << "at offset" << parse_error.offset
                   << ":" << parse_error.errorString();
        return ret_vect;
    }

    /* Validate JSON structure */
    if (!config_doc.isArray()) {
        qWarning() << "Invalid backend config format - expected array";
        return ret_vect;
    }

    QJsonArray config_array = config_doc.array();

    if (config_array.isEmpty()) {
        qWarning() << "Backend configuration array is empty";
        return ret_vect;
    }

    /* Parse each configuration object */
    int valid_count = 0;
    for (int i = 0; i < config_array.size(); ++i) {
        const QJsonValue& value = config_array[i];

        if (!value.isObject()) {
            qWarning() << "Skipping invalid backend configuration at index" << i << "- not an object";
            continue;
        }

        QJsonObject config_obj = value.toObject();
        backend_t backend;

        /* Extract and validate required fields */
        backend.id = config_obj["id"].toString().trimmed();

        /* Validate required ID field */
        if (backend.id.isEmpty()) {
            qWarning() << "Skipping backend configuration at index" << i << "- missing or empty ID";
            continue;
        }

        /* Extract numeric fields with validation */
        bool msec_ok, min_ok, max_ok;
        backend.msec = config_obj["msec"].toInt(0);
        backend.min = config_obj["min"].toInt(0);
        backend.max = config_obj["max"].toInt(0);

        /* Check if conversion was successful (optional fields might be 0)
         We'll rely on our business logic validation below */

        /* Comprehensive validation */
        QStringList validation_errors;

        if (backend.msec <= 0) {
            validation_errors.append(QString("msec must be positive (got: %1)").arg(backend.msec));
        }

        if (backend.min >= backend.max) {
            validation_errors.append(QString("min (%1) must be less than max (%2)").arg(backend.min).arg(backend.max));
        }

        /* Check for reasonable value ranges */
        if (backend.msec > 60000) { /*1 min*/
            validation_errors.append(QString("msec (%1) is unusually large (> 60000)").arg(backend.msec));
        }

        if (qAbs(backend.min) > 1000000 || qAbs(backend.max) > 1000000) {
            validation_errors.append("min/max values are unusually large (> 1,000,000)");
        }

        /* If any validation errors, skip this configuration */
        if (!validation_errors.isEmpty()) {
            qWarning() << "Skipping backend" << backend.id << "- validation errors:" << validation_errors.join("; ");
            continue;
        }

        /* Add valid configuration to results */
        ret_vect.append(backend);
        valid_count++;

        /*
        qDebug() << "Loaded backend generator - ID:" << backend.id
                 << "Interval:" << backend.msec << "ms"
                 << "Range:" << backend.min << "-" << backend.max;
        */
    }

    /*
    qInfo() << "Successfully loaded" << valid_count << "out of"
            << config_array.size() << "backend generator configurations";
    */

    return ret_vect;
}

QVector<frontend_t> dqc::json_parser::load_frontend_config(const QString &config_path)
{
    QVector<frontend_t> ret_vect;

    /* Validate input path */
    if (config_path.isEmpty()) {
        qWarning() << "Configuration path is empty";
        return ret_vect;
    }

    QFile config_file(config_path);

    /* Attempt to open the configuration file */
    if (!config_file.open(QIODevice::ReadOnly)) {
        qWarning() << "Current directory:" << QDir::currentPath();
        qWarning() << "Could not open frontend config file:" << config_path
                   << "Error:" << config_file.errorString();
        return ret_vect;
    }

    /* Read and validate file content */
    QByteArray config_data = config_file.readAll();
    config_file.close();

    if (config_data.isEmpty()) {
        qWarning() << "Configuration file is empty:" << config_path;
        return ret_vect;
    }

    QJsonParseError parse_error;
    QJsonDocument config_doc = QJsonDocument::fromJson(config_data, &parse_error);

    /* Check for JSON parsing errors */
    if (parse_error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error in" << config_path
                   << "at offset" << parse_error.offset
                   << ":" << parse_error.errorString();
        return ret_vect;
    }

    /* Validate JSON structure */
    if (!config_doc.isArray()) {
        qWarning() << "Invalid frontend config format - expected array";
        return ret_vect;
    }

    QJsonArray config_array = config_doc.array();

    if (config_array.isEmpty()) {
        qWarning() << "Frontend configuration array is empty";
        return ret_vect;
    }

    /* Parse each configuration object */
    int valid_count = 0;
    for (int i = 0; i < config_array.size(); ++i) {
        const QJsonValue& value = config_array[i];

        if (!value.isObject()) {
            qWarning() << "Skipping invalid configuration at index" << i << "- not an object";
            continue;
        }

        QJsonObject config_obj = value.toObject();
        frontend_t front;

        /* Extract and validate required fields */
        front.id = config_obj["id"].toString().trimmed();
        front.data_source = config_obj["dataSource"].toString().trimmed();

        /* Validate required ID field */
        if (front.id.isEmpty()) {
            qWarning() << "Skipping configuration at index" << i << "- missing or empty ID";
            continue;
        }

        /* Extract position coordinates with validation */
        bool x_ok, y_ok;
        front.x = config_obj["x"].toInt(-1);
        front.y = config_obj["y"].toInt(-1);

        /* Validate coordinates are non-negative */
        if (front.x < 0 || front.y < 0) {
            qWarning() << "Skipping" << front.id << "- invalid coordinates (x:"
                       << front.x << "y:" << front.y << ")";
            continue;
        }

        /* Extract and validate color */
        QString color_hex = config_obj["color-hex"].toString().trimmed();
        if (color_hex.isEmpty()) {
            qWarning() << "Skipping" << front.id << "- missing color-hex";
            continue;
        }

        front.color = QColor(color_hex);
        if (!front.color.isValid()) {
            qWarning() << "Skipping" << front.id << "- invalid color format:" << color_hex;
            continue;
        }

        /* Add valid configuration to results */
        ret_vect.append(front);
        valid_count++;

        /*
        qDebug() << "Loaded frontend element - ID:" << front.id
                 << "Position:" << front.x << "," << front.y
                 << "Color:" << front.color.name()
                 << "Data source:" << front.data_source;
        */
    }

    /*
    qInfo() << "Successfully loaded" << valid_count << "out of"
            << config_array.size() << "frontend configurations";
    */

    return ret_vect;
}

}
