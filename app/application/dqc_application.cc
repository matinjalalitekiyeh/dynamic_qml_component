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
    auto backend = m_parser.load_backend_config("backend_3.json");
    auto frontend = m_parser.load_frontend_config("frontend.json");

    // qDebug() << "------------------------------------------------------------";
    auto *property = new dqc::dqc_rect_properties(this);
    for (const auto &f : std::as_const(frontend)) {
        for (const auto &b : std::as_const(backend)) {
            // qDebug() << f.data_source << b.id;
            if (f.data_source == b.id) {

                property->set_data_source(f.data_source);
                property->set_color(f.color);
                property->set_initial_x(f.x);
                property->set_initial_y(f.y);
                property->set_interval(b.msec);
                property->set_random_from(b.min);
                property->set_random_to(b.max);
                property->set_random_num(100);

                m_model.add_dqc_rect(property);
                // qDebug() << "**********FOUND*******FOUND******FOUND***********************";
            }
        }
        // qDebug() << "**************";
    }

    // property


    // for (int i = 0; i < 20; i++) {
    //     m_model.add_dqc_rect();
    // }
}

}
