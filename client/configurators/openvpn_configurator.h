#ifndef OPENVPN_CONFIGURATOR_H
#define OPENVPN_CONFIGURATOR_H

#include <QObject>
#include <QProcessEnvironment>

#include "configurator_base.h"
#include "core/defs.h"

class OpenVpnConfigurator : ConfiguratorBase
{
    Q_OBJECT
public:
    OpenVpnConfigurator(std::shared_ptr<Settings> settings,
        std::shared_ptr<ServerController> serverController, QObject *parent = nullptr);

    struct ConnectionData {
        QString clientId;
        QString request; // certificate request
        QString privKey; // client private key
        QString clientCert; // client signed certificate
        QString caCert; // server certificate
        QString taKey; // tls-auth key
        QString host; // host ip
    };

    QString genOpenVpnConfig(const ServerCredentials &credentials, DockerContainer container,
        const QJsonObject &containerConfig, ErrorCode *errorCode = nullptr);

    QString processConfigWithLocalSettings(QString jsonConfig);
    QString processConfigWithExportSettings(QString jsonConfig);

    ErrorCode signCert(DockerContainer container,
        const ServerCredentials &credentials, QString clientId);

private:
    ConnectionData createCertRequest();

    ConnectionData prepareOpenVpnConfig(const ServerCredentials &credentials,
        DockerContainer container, ErrorCode *errorCode = nullptr);

};

#endif // OPENVPN_CONFIGURATOR_H
