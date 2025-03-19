#ifndef CUTEDISCORDPRESENCEPLUGIN_H
#define CUTEDISCORDPRESENCEPLUGIN_H

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>

#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>

#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>

#include <extensionsystem/iplugin.h>

#include <projectexplorer/projecttree.h>
#include <projectexplorer/project.h>

#include <QTimer>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMenu>
#include <QtGui/QAction>

#include <functional>
#include <iostream>
#include <string>

#include <discord_rpc.h>

namespace QtCreatorDRPC {

#define GLOBAL_DRPC_CONTROL_MENU_ID               "QtCreatorDRPC.Menu"
#define GLOBAL_DRPC_CONTROL_MENU_START_ACTION_ID  "QtCreatorDRPC.Action.Start"
#define GLOBAL_DRPC_CONTROL_MENU_STOP_ACTION_ID   "QtCreatorDRPC.Action.Stop"
#define GLOBAL_DISCORD_APPLICATION_ID             "937400240473006092"

class QDiscordRichPresence {
public:
    QString State;
    QString Details;
    quint64 StartTimestamp;
    quint64 EndTimestamp;
    QString LargeImageKey;
    QString LargeImageText;
    QString SmallImageKey;
    QString SmallImageText;
    QString PartyId;
    qint32 PartySize;
    qint32 PartyMax;
    QString MatchSecret;
    QString SpectateSecret;
    QString JoinSecret;
    int8_t Instance;

    void UpdateRichPresence() const;
    QDiscordRichPresence();
};

class Q_DECL_EXPORT QtCreatorDRPCPlugin : public ExtensionSystem::IPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "org.qt-project.Qt.QtCreatorPlugin" FILE "CuteDiscordPresence.json" )

protected:
    struct RichPresenceFileDescriptor {
        QString ImageKey;       // The key of the art asset stored in the rich presence developer portal used for this file.
        QString Description;    // Description of the file type, e.g. C++ Source File, Python Script, QMake Project File, etc...
        QString WorkingVerb;    // Verb used when referring to this file, e.g. editing, designing, configuring.
    };

    // Maps the mime types of files as QStrings, to their respective RichPresenceFileDescriptor.
    static const QMap<QString, RichPresenceFileDescriptor> mimeTypeToRpcFileDescriptorMap;

    class MimeOverrider {
public:
        static QMap<QString, QList<QPair<QList<QString>, QString> > > MimeOverrideMap;
        static QString OverrideMimeIfApplicable( const QString& mime, const Utils::FilePath& file_path );
    };

    std::time_t drpcActivatedTimestamp;
    void initializeDiscordRichPresence( const char* application_id );

    std::time_t timeSpentOnCurrentEditor;

    QTimer drpcSyncTimer;

    QList<QMetaObject::Connection> syncSignalConnections;

protected slots:
    void setDrpcNotEditingState();
    void syncDrpcToCurrentEditorState();

    void activateDiscordRichPresence();
    void deactivateDiscordRichPresence();

    void initializeControlMenu();

public:
    virtual bool initialize( const QStringList& arguments, QString* error_string ) override;
    virtual void extensionsInitialized() override;
    virtual ShutdownFlag aboutToShutdown() override;

    QtCreatorDRPCPlugin();
    virtual ~QtCreatorDRPCPlugin() override;
};

};

#endif // CUTEDISCORDPRESENCEPLUGIN_H
