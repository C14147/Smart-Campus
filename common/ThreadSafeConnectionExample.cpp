// Example: Thread-safe connection between NetworkManager and UI
#include <QThread>
#include "NetworkManager.h"
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        netMgr = new NetworkManager;
        QThread *netThread = new QThread;
        netMgr->moveToThread(netThread);
        netThread->start();
        connect(netMgr, &NetworkManager::messageReceived,
                this, &MainWindow::onNetworkMessageReceived,
                Qt::QueuedConnection);
    }

public slots:
    void onNetworkMessageReceived(const QJsonObject &json) {
        // UI update code, runs in main thread
    }
private:
    NetworkManager *netMgr;
};
