#include "xmlparser.h"
#include <QDomNodeList>
#include <QDebug>

using namespace Connection;

XmlParser::XmlParser()
    : QObject()
{
    m_path = "../connection_parameters.xml";
}

qint32 XmlParser::generateNextId()
{
    QVector<ConnectionInfo> existing = elements();
    if (existing.isEmpty())
        return 1;

    qint32 maxId = 0;
    for (const ConnectionInfo &info : existing) {
        if (info.id > maxId)
            maxId = info.id;
    }
    return maxId + 1;
}

ConnectionInfo XmlParser::save(ConnectionInfo info)
{
    if (info.id <= 0)
        info.id = generateNextId();

    QFile xmlFile(m_path);
    QDomDocument document;

    if (xmlFile.open(QIODevice::ReadOnly)) {
        document.setContent(&xmlFile);
        xmlFile.close();
    } else {
        QDomElement root = document.createElement("Connections");
        document.appendChild(root);
    }

    QDomElement root = document.documentElement();
    if (root.isNull()) {
        root = document.createElement("Connections");
        document.appendChild(root);
    }

    QDomNodeList connections = root.elementsByTagName("connection");
    for (int i = 0; i < connections.size(); i++) {
        QDomElement elem = connections.at(i).toElement();
        if (elem.attribute("id").toInt() == info.id) {
            root.removeChild(connections.at(i));
            break;
        }
    }

    QDomElement connection = document.createElement("connection");
    connection.setAttribute("id", info.id);
    connection.setAttribute("nameConnection", info.nameConnection);
    connection.setAttribute("tcpAC", info.tcpAC);
    connection.setAttribute("tcpP2", info.tcpP2);
    root.appendChild(connection);

    if (xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&xmlFile);
        document.save(stream, 4);
        xmlFile.close();
    } else {
        qDebug() << "Failed to open file for writing:" << xmlFile.errorString();
    }

    m_connectionElements.append(info);

    return info;
}

QVector<ConnectionInfo> XmlParser::elements()
{
    QVector<ConnectionInfo> result;
    QFile xmlFile(m_path);

    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return result;
    }

    QDomDocument document;
    if (!document.setContent(&xmlFile)) {
        xmlFile.close();
        return result;
    }
    xmlFile.close();

    QDomElement root = document.documentElement();
    if (root.isNull()) {
        return result;
    }

    QDomNodeList connections = root.elementsByTagName("connection");

    for (int i = 0; i < connections.size(); i++) {
        QDomElement elem = connections.at(i).toElement();
        ConnectionInfo info;
        info.id = elem.attribute("id").toInt();
        info.nameConnection = elem.attribute("nameConnection");
        info.tcpAC = elem.attribute("tcpAC");
        info.tcpP2 = elem.attribute("tcpP2");
        result.append(info);
    }

    return result;
}

ConnectionInfo XmlParser::element(const qint32 id)
{
    for (auto &item : m_connectionElements) {
        if (item.id == id)
            return item;
    }

    return {};
}

void XmlParser::change(const qint32 id, ConnectionInfo info)
{
    for (auto &item : m_connectionElements) {
        if (item.id == id)
            item = info;
    }
}

void XmlParser::remove(const qint32 id)
{
    QFile xmlFile(m_path);
    QDomDocument document;

    if (xmlFile.open(QIODevice::ReadOnly)) {
        document.setContent(&xmlFile);
        xmlFile.close();
    }

    QDomElement root = document.documentElement();

    QDomNodeList connections = root.elementsByTagName("connection");
    for (int i = 0; i < connections.size(); i++) {
        QDomElement elem = connections.at(i).toElement();
        if (elem.attribute("id").toInt() == id) {
            root.removeChild(connections.at(i));
            break;
        }
    }

    if (xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&xmlFile);
        document.save(stream, 4);
    }
}
