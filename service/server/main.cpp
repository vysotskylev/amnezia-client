#include <QDir>

#include "defines.h"
#include "localserver.h"
#include "log.h"
#include "systemservice.h"
#include "utils.h"


int runApplication(int argc, char** argv)
{
    QCoreApplication app(argc,argv);
    LocalServer localServer;

    return app.exec();
}


int main(int argc, char **argv)
{
    Utils::initializePath(Utils::systemLogPath());

    Log::init();

    if (argc == 2) {
        qInfo() << "Started as console application";
        return runApplication(argc, argv);
    }
    else {
        qInfo() << "Started as system service";
#ifdef Q_OS_WIN
        SystemService systemService(argc, argv);
        return systemService.exec();
#else
    return runApplication(argc, argv);
#endif

    }
}
