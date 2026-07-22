#include <QGuiApplication>
#include <QQmlApplicationEngine>
int main(int argc, char** argv){ QGuiApplication app(argc, argv); QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL); QQmlApplicationEngine engine; engine.loadFromModule("LunaShell", "Main"); if(engine.rootObjects().isEmpty()) return 1; return app.exec(); }
