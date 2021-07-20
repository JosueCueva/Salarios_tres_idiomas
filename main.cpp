#include "principal.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Crear lista de idiomas
    QStringList idiomas;
    idiomas << "Inglés (US)" << "Español (ECU)" << "Chino (HK)";
    // Solicitar al usuario que elija el idioma
    QString idiomaSel = QInputDialog::getItem(NULL, "Idioma", "Seleccione el idioma", idiomas);
    // Se crea un objeto para manejar la traducciones
    QTranslator traduccion;
    // Evaluar el idioma seleccionado
    if(idiomaSel == "Inglés (US)")
    {
        traduccion.load(":/Idiomas/SalarioIdiomas_en_US.qm");
    }else if(idiomaSel == "Chino (HK)")
    {
        traduccion.load(":/Idiomas/SalarioIdiomas_zh_HK.qm");
    }else{
        traduccion.load(":/Idiomas/SalarioIdiomas_es_EC.qm");
    }
    // Establecer idioma a la aplicación
    a.installTranslator(&traduccion);

    Principal w;
    w.show();
    return a.exec();
}
