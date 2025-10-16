#ifndef DQC_APPLICATION_HXX
#define DQC_APPLICATION_HXX

#include <QApplication>
#include <QQmlApplicationEngine>

namespace dqc {

class dqc_application final
    : public QApplication {
    explicit dqc_application(int &argc, char *argv[]);
public:
    ~dqc_application() override final = default;
    static decltype (auto)
    instance(int &argc, char *argv[]) {
        static auto app = new dqc_application(argc, argv);
        return app;
    }

    dqc_application(const dqc_application&) = delete;
    dqc_application& operator=(const dqc_application&) = delete;
    dqc_application(const dqc_application&&) = delete;
    dqc_application& operator=(const dqc_application&&) = delete;

    void init_common(void) const noexcept;
    void init_for_normal_boot(void);
    [[nodiscard]]int error() const noexcept;

private:
    QQmlApplicationEngine m_engine;
    u_int8_t __pad[4];
    void post_init();
    int m_exit_code;
};

}

#endif /* DQC_APPLICATION_HXX */
