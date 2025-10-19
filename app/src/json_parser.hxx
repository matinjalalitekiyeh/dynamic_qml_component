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

/**
 * @struct frontend_t
 * @brief Represents a frontend display element configuration
 */
struct frontend_t {
    QString id;
    QColor color;
    QString data_source;
    int x;
    int y;
};

/**
 * @struct backend_t
 * @brief Represents a backend generator configuration
 */
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

    /**
     * @brief Parses a JSON configuration file to load backend generator configurations
     *
     * This function reads a JSON configuration file containing an array of backend
     * generator definitions and converts them into backend_t structures.
     *
     * @param config_path Path to the JSON configuration file
     * @return QVector<backend_t> Vector of parsed backend configurations.
     *         Returns empty vector if file cannot be read or parsed.
     *
     * @note Expected JSON format:
     * [
     *   {
     *     "id": "generator1",
     *     "msec": 1000,
     *     "min": 0,
     *     "max": 100
     *   },
     *   ...
     * ]
     *
     * @note Validation rules:
     * - id must not be empty
     * - msec must be positive (> 0)
     * - min must be less than max
     * - All numeric fields must be valid integers
     */
    Q_INVOKABLE QVector<backend_t> load_backend_config(const QString& config_path);

    /**
    * @brief Parses a JSON configuration file to load frontend element configurations
    *
    * This function reads a JSON configuration file containing an array of frontend
    * element definitions and converts them into frontend_t structures.
    *
    * @param config_path Path to the JSON configuration file
    * @return QVector<frontend_t> Vector of parsed frontend configurations.
    *         Returns empty vector if file cannot be read or parsed.
    *
    * @note Expected JSON format:
    * [
    *   {
    *     "id": "element1",
    *     "x": 100,
    *     "y": 200,
    *     "color-hex": "#FF0000",
    *     "dataSource": "source1_1"
    *   },
    *   ...
    * ]
    */
    Q_INVOKABLE QVector<frontend_t> load_frontend_config(const QString& config_path);
};

}

#endif /* JSON_PARSER_HXX */
