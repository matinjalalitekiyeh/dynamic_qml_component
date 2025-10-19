#include "dqc_application.hxx"
#include <QQmlContext>

namespace dqc {

dqc_application::dqc_application(int &argc, char *argv[])
    : QApplication(argc, argv)
    , m_exit_code{0}
{ /*Nill*/ }

void dqc_application::init_common() const noexcept
{
    m_engine.rootContext()->setContextProperty("m_model", QVariant::fromValue(&m_model));
}

void dqc_application::init_for_normal_boot()
{
   QObject::connect(
       &m_engine,
       &QQmlApplicationEngine::objectCreationFailed,
       this,
       [&]() {
            m_exit_code = -1;
            QCoreApplication::exit(-1);
        },
       Qt::QueuedConnection);
   m_engine.loadFromModule("dynamic_qml_component/app", "Main");

    this->post_init();
    this->exec();
}

int dqc_application::error() const noexcept
{
    return m_exit_code;
}

void dqc_application::post_init()
{

    /* Load configuration files */
    auto backend = m_parser.load_backend_config("cnfg/backend_2.json");
    auto frontend = m_parser.load_frontend_config("cnfg/frontend.json");

    /* Use (hash) efficient lut */
    QHash<QString, const backend_t*> backend_lookup;
    for (const auto &b : std::as_const(backend)) {
        backend_lookup.insert(b.id, &b);
    }

    /* Associate frontend elements with their backend data sources */
    for (const auto &f : std::as_const(frontend)) {
        auto backend_iter = backend_lookup.find(f.data_source);
        if (backend_iter == backend_lookup.end()) {
            qWarning() << "No backend found for data source:" << f.data_source;
            continue;
        }

        const auto &b = *backend_iter.value();

        /* Create and configure the rectangle properties */
        auto *property = new dqc::dqc_rect_properties(this);

        property->set_data_source(f.data_source);
        property->set_color(f.color);
        property->set_initial_x(f.x);
        property->set_initial_y(f.y);
        property->set_interval(b.msec);
        property->set_random_from(b.min);
        property->set_random_to(b.max);

        /* ADd new peoperty to model */
        m_model.add_dqc_rect(property);

        /*
        qDebug() << "Connected" << f.id << "to" << b.id
                 << "at (" << f.x << "," << f.y << ")"
                 << "interval:" << b.msec << "ms";
        */
    }


}

}
