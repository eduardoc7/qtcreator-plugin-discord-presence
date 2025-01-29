#include "cutediscordpresence.h"

namespace QtCreatorDRPC {

void QDiscordRichPresence::UpdateRichPresence() const {
    DiscordRichPresence presence {};
    memset( &presence, 0, sizeof( presence ) );

    const QByteArray& state_bytes               { State.toLocal8Bit() };
    const QByteArray& details_bytes             { Details.toLocal8Bit() };
    const QByteArray& large_image_key_bytes     { LargeImageKey.toLocal8Bit() };
    const QByteArray& large_image_text_bytes    { LargeImageText.toLocal8Bit() };
    const QByteArray& small_image_key_bytes     { SmallImageKey.toLocal8Bit() };
    const QByteArray& small_image_text_bytes    { SmallImageText.toLocal8Bit() };
    const QByteArray& party_id_bytes            { PartyId.toLocal8Bit() };
    const QByteArray& match_secret_bytes        { MatchSecret.toLocal8Bit() };
    const QByteArray& spectate_secret_bytes     { SpectateSecret.toLocal8Bit() };
    const QByteArray& join_secret_bytes         { JoinSecret.toLocal8Bit() };

    // Perform char* string conversions, for string types.
    presence.state             = state_bytes.size() ? state_bytes.data() : nullptr;
    presence.details           = details_bytes.size() ? details_bytes.data() : nullptr;
    presence.largeImageKey     = large_image_key_bytes.size() ? large_image_key_bytes.data() : nullptr;
    presence.largeImageText    = large_image_text_bytes.size() ? large_image_text_bytes.data() : nullptr;
    presence.smallImageKey     = small_image_key_bytes.size() ? small_image_key_bytes.data() : nullptr;
    presence.smallImageText    = small_image_text_bytes.size() ? small_image_text_bytes.data() : nullptr;
    presence.partyId           = party_id_bytes.size() ? party_id_bytes.data() : nullptr;
    presence.matchSecret       = match_secret_bytes.size() ? match_secret_bytes.data() : nullptr;
    presence.spectateSecret    = spectate_secret_bytes.size() ? spectate_secret_bytes.data() : nullptr;
    presence.joinSecret        = join_secret_bytes.size() ? join_secret_bytes.data() : nullptr;

    // Assign integer types.
    presence.startTimestamp    = StartTimestamp;
    presence.endTimestamp      = EndTimestamp;
    presence.partySize         = PartySize;
    presence.partyMax          = PartyMax;
    presence.instance          = Instance;

    Discord_UpdatePresence( &presence );
}

QDiscordRichPresence::QDiscordRichPresence() :
    StartTimestamp { NULL },
    EndTimestamp   { NULL },
    PartySize      { NULL },
    PartyMax       { NULL },
    Instance       { NULL } {}

const QMap<QString, QtCreatorDRPCPlugin::RichPresenceFileDescriptor> QtCreatorDRPCPlugin::mimeTypeToRpcFileDescriptorMap = {
    { "text/x-c++src", { "cxx", "C++ Source File", "Editing" } },
    { "text/x-c++hdr", { "cxx", "C++ Header File", "Editing" } },
    { "text/x-csrc", { "c", "C Source File", "Editing" } },
    { "text/x-chdr", { "c", "C Header File", "Editing" } },
    { "text/x-csharp", { "csharp", "C# Source File", "Editing" } },
    { "text/x-python", { "python", "Python Script", "Editing" } },
    { "application/x-ruby", { "ruby", "Ruby Script", "Editing" } },
    { "text/rust", { "rust", "Rust Source File", "Editing" } },
    { "text/x-lua", { "lua", "Lua Script", "Editing" } },
    { "text/css", { "css", "CSS Stylesheet", "Editing" } },
    { "text/qss", { "qss", "QSS Stylesheet", "Editing" } },
    { "application/javascript", { "js", "JavaScript File", "Editing" } },
    { "text/x-java", { "java", "Java Class", "Editing" } },
    { "text/x-qml", { "qml", "QtQuick QML File", "Editing" } },
    { "text/x-qt.ui+qml", { "qml", "QtQuick QML UI File", "Designing" } },
    { "application/octet-stream", { "binary", "Binary Data", "Inspecting" } },
    { "text/x-asm", { "asm", "Assembly Source File", "Editing" } },
    { "text/x-asminfo", { "asminfo", "Preprocessed C/C++ File", "Editing" } },
    { "application/vnd.qt.qmakeprofile", { "qmake", "QMake Project File", "Configuring" } },
    { "application/vnd.qt.qmakeproincludefile", { "qmake_pri", "QMake Include File", "Editing" } },
    { "application/vnd.qt.qmakeprostashfile", { "qt", "QMake Stash File", "Editing" } },
    { "text/x-cmake-project", { "cmake", "CMake Project File", "Editing" } },
    { "text/x-makefile", { "gnu", "GNU Makefile", "Editing" } },
    { "text/gitignore", { "git", "Gitignore File", "Configuring" } },
    { "application/x-designer", { "ui", "Qt User Interface File", "Designing" } },
    { "application/vnd.qt.xml.resource", { "qrc", "Qt Resource File", "Editing" } },
    { "application/json", { "json", "JSON File", "Editing" } },
    { "text/plain", { "txt", "Plain Text File", "Editing" } },
    { "text/markdown", { "markdown", "Markdown Document", "Writing" } },
    { "text/html", { "html", "HTML File", "Editing" } },
    { "application/xml", { "xml", "XML File", "Editing" } },
    { "text/vnd.qtcreator.git.submit", { "git", "Git Commit File", "Editing" } },
    { "image/png", { "image", "PNG Image", "Viewing" } }
};

QMap<QString, QList<QPair<QList<QString>, QString> > > QtCreatorDRPCPlugin::MimeOverrider::MimeOverrideMap {
    { "text/x-c++hdr", {
          { { ".h" }, "text/x-chdr" }
      } },

    { "text/plain", {
          { { ".qss" }, "text/qss" },
          { { ".gitignore" }, "text/gitignore" },
          { { ".i" }, "text/x-asminfo" }
      } }
};

QString QtCreatorDRPCPlugin::MimeOverrider::OverrideMimeIfApplicable( const QString& mime, const Utils::FilePath& file_path ) {
    if ( MimeOverrideMap.contains( mime ) ) {
        for ( const auto& potential_override : MimeOverrideMap[mime] ) {
            const QList<QString>& potential_extensions { potential_override.first };
            const QString& target_mime { potential_override.second };

            for ( const QString& potential_extension : potential_extensions ) {
                if ( file_path.endsWith( potential_extension ) ) {
                    return target_mime;
                }
            }
        }
    }

    return mime;
}

void QtCreatorDRPCPlugin::initializeDiscordRichPresence( const char* application_id ) {
    DiscordEventHandlers discord_event_handlers {};
    memset( &discord_event_handlers, 0, sizeof( discord_event_handlers ) );
    Discord_Initialize( application_id, &discord_event_handlers, 1, nullptr );
}

void QtCreatorDRPCPlugin::setDrpcNotEditingState() {
    DiscordRichPresence presence;
    memset( &presence, 0, sizeof( presence ) );
    presence.largeImageKey = "qt";
    presence.largeImageText = "Qt Creator";
    presence.details = "Not Currently Editing Anything";
    presence.startTimestamp = drpcActivatedTimestamp;
    Discord_UpdatePresence( &presence );
}

void QtCreatorDRPCPlugin::syncDrpcToCurrentEditorState() {
    const Core::IEditor* editor { Core::EditorManager::instance()->currentEditor() };
    if ( editor == nullptr ) return setDrpcNotEditingState();

    const ProjectExplorer::Project* active_project { ProjectExplorer::ProjectTree::currentProject() };
    const QString& active_project_name { active_project != nullptr ? active_project->displayName() : "No Project" };

    const Utils::FilePath& active_file_path { editor->document()->filePath() };
    const QString& active_file_mime { MimeOverrider::OverrideMimeIfApplicable( editor->document()->mimeType(), active_file_path ) };

    const RichPresenceFileDescriptor& rpc_file_descriptor {
        mimeTypeToRpcFileDescriptorMap.contains( active_file_mime )
            ? mimeTypeToRpcFileDescriptorMap[active_file_mime]
            : RichPresenceFileDescriptor { "unknown", "Unknown File (" + active_file_mime + ")", "Editing" }
    };

    QDiscordRichPresence presence {};

    presence.Details        = QString { "%1 %2" }.arg( rpc_file_descriptor.WorkingVerb, rpc_file_descriptor.Description );
    presence.State          = QString { "%1/%2" }.arg( active_file_path.fileName(), active_project_name );
    presence.LargeImageText = rpc_file_descriptor.WorkingVerb + " " + active_file_path.fileName() + " since " + QString::number( timeSpentOnCurrentEditor ) + " seconds  (" + active_file_mime + ")";
    presence.LargeImageKey  = rpc_file_descriptor.ImageKey;
    presence.SmallImageKey  = "qtcircle";
    presence.SmallImageText = active_project_name;
    presence.StartTimestamp = drpcActivatedTimestamp;

    presence.UpdateRichPresence();
}

void QtCreatorDRPCPlugin::activateDiscordRichPresence() {
    deactivateDiscordRichPresence();
    setDrpcNotEditingState();

    syncSignalConnections = {
        connect( Core::EditorManager::instance(), &Core::EditorManager::currentEditorChanged, [&]( Core::IEditor* editor ) -> void {
                Q_UNUSED( editor )
                timeSpentOnCurrentEditor = NULL;
                syncDrpcToCurrentEditorState();
            } ),

        connect( ProjectExplorer::ProjectTree::instance(), &ProjectExplorer::ProjectTree::currentProjectChanged, [&]( ProjectExplorer::Project* project ) -> void {
                Q_UNUSED( project )
                syncDrpcToCurrentEditorState();
            } ),

        connect( Core::EditorManager::instance(), &Core::EditorManager::currentDocumentStateChanged, [&]() -> void {
                syncDrpcToCurrentEditorState();
            } ),

        connect( Core::EditorManager::instance(), &Core::EditorManager::documentOpened, [&]( Core::IDocument* document ) -> void {
                Q_UNUSED( document )
                syncDrpcToCurrentEditorState();
            } ),

        connect( Core::EditorManager::instance(), &Core::EditorManager::documentClosed, [&]( Core::IDocument* document ) -> void {
                Q_UNUSED( document )
                syncDrpcToCurrentEditorState();
            } ),

        connect( Core::EditorManager::instance(), &Core::EditorManager::saved, [&]( Core::IDocument* document ) -> void {
                Q_UNUSED( document )
                syncDrpcToCurrentEditorState();
            } ),

        connect( &drpcSyncTimer, &QTimer::timeout, [&]() -> void {
                ++timeSpentOnCurrentEditor;
                syncDrpcToCurrentEditorState();
            } )
    };

    drpcSyncTimer.start( 1000 );
    drpcActivatedTimestamp = std::time( nullptr );
}

void QtCreatorDRPCPlugin::deactivateDiscordRichPresence() {
    for ( const QMetaObject::Connection& connection : syncSignalConnections ) {
        disconnect( connection );
    }

    drpcSyncTimer.stop();
    Discord_ClearPresence();
}

void QtCreatorDRPCPlugin::initializeControlMenu() {
    Core::ActionContainer* drpc_control_menu { Core::ActionManager::createMenu( GLOBAL_DRPC_CONTROL_MENU_ID ) };
    drpc_control_menu->menu()->setTitle( "Discord RPC" );

    QAction* drpc_control_start_action { new QAction { "Start Discord RPC", this } };
    QAction* drpc_control_stop_action  { new QAction { "Stop Discord RPC", this } };

    Core::Command* drpc_control_start_command {
        Core::ActionManager::registerAction( drpc_control_start_action,
                                             GLOBAL_DRPC_CONTROL_MENU_START_ACTION_ID,
                                             Core::Context { Core::Constants::C_GLOBAL } )
    };

    Core::Command* drpc_control_stop_command {
        Core::ActionManager::registerAction( drpc_control_stop_action,
                                             GLOBAL_DRPC_CONTROL_MENU_STOP_ACTION_ID,
                                             Core::Context { Core::Constants::C_GLOBAL } )
    };

    connect( drpc_control_start_action, &QAction::triggered,
             this, &QtCreatorDRPCPlugin::activateDiscordRichPresence );

    connect( drpc_control_stop_action, &QAction::triggered,
             this, &QtCreatorDRPCPlugin::deactivateDiscordRichPresence );

    drpc_control_menu->addAction( drpc_control_start_command );
    drpc_control_menu->addAction( drpc_control_stop_command );

    Core::ActionManager::actionContainer( Core::Constants::M_TOOLS )->addMenu( drpc_control_menu );
}

bool QtCreatorDRPCPlugin::initialize( const QStringList& arguments, QString* error_string ) {
    Q_UNUSED( arguments )
    Q_UNUSED( error_string )

    //set the plugin's unique ID
    setId("CuteDiscordPresence");

    initializeDiscordRichPresence( GLOBAL_DISCORD_APPLICATION_ID );
    initializeControlMenu();
    activateDiscordRichPresence();

    return true;
}

void QtCreatorDRPCPlugin::extensionsInitialized() {}

ExtensionSystem::IPlugin::ShutdownFlag QtCreatorDRPCPlugin::aboutToShutdown() {
    return SynchronousShutdown;
}

QtCreatorDRPCPlugin::QtCreatorDRPCPlugin() :
    drpcActivatedTimestamp      { NULL },
    timeSpentOnCurrentEditor    { NULL } {}

QtCreatorDRPCPlugin::~QtCreatorDRPCPlugin() {
    deactivateDiscordRichPresence();
    Discord_Shutdown();
}

};
