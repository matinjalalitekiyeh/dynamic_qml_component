#ifndef DQC_APPLICATION_HXX
#define DQC_APPLICATION_HXX

#include <QApplication>
#include <QQmlApplicationEngine>

namespace dqc {

/**
 * @brief Main application class implementing a singleton QApplication pattern
 *
 * This class serves as the central application controller, managing the
 * QML engine and application lifecycle. It follows the singleton pattern
 * to ensure only one application instance exists.
 */
class dqc_application final
    : public QApplication {
    explicit dqc_application(int &argc, char *argv[]);
public:

    /**
     * @brief Private constructor to enforce singleton pattern
     * @param argc Reference to argument count from main()
     * @param argv Argument vector from main()
     */
    ~dqc_application() override final = default;

    /**
     * @brief Get the singleton application instance
     *
     * Creates the instance on first call and returns the same instance
     * on subsequent calls. Implements the Meyer's singleton pattern.
     *
     * @param argc Reference to argument count from main()
     * @param argv Argument vector from main()
     * @return dqc_application* Pointer to the singleton instance
     */
    static decltype (auto)
    instance(int &argc, char *argv[]) {
        static auto app = new dqc_application(argc, argv);
        return app;
    }

    /* Delete copy and move operations to enforce singleton pattern */
    dqc_application(const dqc_application&) = delete;
    dqc_application& operator=(const dqc_application&) = delete;
    dqc_application(const dqc_application&&) = delete;
    dqc_application& operator=(const dqc_application&&) = delete;

    /**
     * @brief Initialize common application components
     *
     * Performs one-time initialization of components that are
     * common to all application startup modes.
     *
     * @note This function is noexcept and guaranteed not to throw
     */
    void init_common(void) const noexcept;

    /**
     * @brief Initialize application for normal boot sequence
     *
     * Sets up application components for standard application startup,
     * including UI initialization and core service setup.
     */
    void init_for_normal_boot(void);

    /**
     * @brief Get the application exit code
     *
     * @return int The exit code that will be returned when application terminates
     * @note This function is noexcept and guaranteed not to throw
     */
    [[nodiscard]]int error() const noexcept;

private:
    void post_init();

private:
    QQmlApplicationEngine m_engine; /* <- QML application engine for UI management */
    u_int8_t __pad[4];
    int m_exit_code;
};

}

#endif /* DQC_APPLICATION_HXX */
