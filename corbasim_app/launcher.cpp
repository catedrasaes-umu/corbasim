#include <iostream>
#include <QtCore>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QProcess proc;
    QProcessEnvironment env(QProcessEnvironment::systemEnvironment());
    proc.setProcessChannelMode(QProcess::ForwardedChannels);

    QStringList args;
    for (int i = 0; i < argc; i++) 
    {
        args << argv[i];
    }

    const QString applicationDirPath(
            QCoreApplication::applicationDirPath());

    // add LD_LIBRARY_PATH
    const QString libraryDirPath(applicationDirPath + "/../lib");

    QString ldLibraryPath = env.value("LD_LIBRARY_PATH");

    if (!ldLibraryPath.isEmpty()) ldLibraryPath += ':';

    ldLibraryPath += libraryDirPath;

    env.insert("LD_LIBRARY_PATH", ldLibraryPath);

    proc.setProcessEnvironment(env);

    proc.start(QCoreApplication::applicationFilePath()
            + ".real", args);


    if (!proc.waitForStarted(-1))
    {
        std::cerr << "Unable to launch!" << std::endl;
        return -1;
    }

    // wait for its end
    proc.waitForFinished(-1);
    
    return proc.exitCode();
}
