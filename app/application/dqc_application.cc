#include "dqc_application.hxx"

namespace dqc {

dqc_application::dqc_application(int &argc, char *argv[])
    : QApplication(argc, argv)
    , m_exit_code{0}
{ /*Nill*/ }

void dqc_application::init_common() const noexcept
{
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
}

}
