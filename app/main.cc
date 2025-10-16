#include <application/dqc_application.hxx>
#include "version.hxx"

int main(int argc, char *argv[])
{
    (void)::cmake::version::print_version();

    auto app = dqc::dqc_application::instance(argc, argv);
    Q_CHECK_PTR(app);
    if(app->error()) {
        app->exec();
        return -1;
    }

    /* Initialize some parameters before boot. */
    app->init_common();

    /* Boot application. */
    app->init_for_normal_boot();

    const auto error_code = app->error();

    delete app;
    app = nullptr;

    return error_code;
}
