#include <QCommandLineParser>
#include <QApplication>
#include <QDialog>
#include <nodes/NodeStyle>
#include <nodes/FlowViewStyle>
#include <nodes/ConnectionStyle>
#include <nodes/DataModelRegistry>

#include "mainwindow.h"
#include "XML_utilities.hpp"
#include "startup_dialog.h"
#include "models/RootNodeModel.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowViewStyle;
using QtNodes::NodeStyle;
using QtNodes::ConnectionStyle;

void messageHandler(QtMsgType type, const QMessageLogContext & context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Groot");
    app.setWindowIcon(QPixmap(":/icons/BT.png"));
    app.setOrganizationName("EurecatRobotics");
    app.setOrganizationDomain("eurecat.org");

    qInstallMessageHandler(messageHandler);

    QFont font = QApplication::font("QMessageBox");
    QApplication::setFont(font);
    QApplication::setStyle("fusion");

    qRegisterMetaType<AbsBehaviorTree>();

    QCommandLineParser parser;
    parser.setApplicationDescription("Groot. The fancy BehaviorTree Editor");
    parser.addHelpOption();

    QCommandLineOption mode_option(QStringList() << "mode",
                                   "Start in one of these modes: [editor,monitor,replay]",
                                   "mode");
    parser.addOption(mode_option);
    parser.process( app );

    QFile styleFile( ":/stylesheet.qss" );
    styleFile.open( QFile::ReadOnly );
    QString style( styleFile.readAll() );
    app.setStyleSheet( style );

    if (true) {
        auto mode = GraphicMode::EDITOR;

        if (parser.isSet(mode_option)) {
            QString opt_mode = parser.value(mode_option);
            if( opt_mode == "editor")
            {
                mode = GraphicMode::EDITOR;
            }
            else if( opt_mode == "monitor")
            {
                mode = GraphicMode::MONITOR;
            }
            else if( opt_mode == "replay")
            {
                mode = GraphicMode::REPLAY;
            }
            else{
                std::cout << "wrong mode passed to --mode. Use on of these: editor / monitor /replay"
                          << std::endl;
                return 0;
            }
        } else {
            StartupDialog dialog;
            dialog.setWindowFlags( Qt::FramelessWindowHint );
            if(dialog.exec() != QDialog::Accepted)
            {
                return 0;
            }
            mode = dialog.getGraphicMode();
        }

        MainWindow win( mode );
        win.show();
        return app.exec();
    }
}

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString &msg) {
    QString time = QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
    QString level;
    switch (type) {
        case QtDebugMsg:    level = "DBG"; break;
        case QtInfoMsg:     level = "INF"; break;
        case QtWarningMsg:  level = "WRN"; break;
        case QtCriticalMsg: level = "CRT"; break;
        case QtFatalMsg:    level = "FTL"; break;
        default:            level = "???"; break;
    }
    QString category = context.category;

    if (MainWindow::loggerTextBox != nullptr) {
        QString content = QObject::tr("[%1] [%2] (%3): %4").arg(time).arg(level).arg(category).arg(msg);
        MainWindow::loggerTextBox->append(content);
    }
}
