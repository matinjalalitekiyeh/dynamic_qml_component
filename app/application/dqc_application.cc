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
    m_parser.load_backend_config("backend_3.json");
    m_parser.load_frontend_config("frontend.json");
    for (int i = 0; i < 20; i++) {
        m_model.add_dqc_rect();
    }
}

}
