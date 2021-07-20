#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_action_Nuevo_triggered()
{
    this->nuevo();
}

void Principal::calcular()
{
    // Obtener el nombre
    QString nombre = ui->inNombre->text();
    // Valida que el nombre no este vacío
    if(nombre.isEmpty())
    {
        QMessageBox::warning(this,tr("Salarios"),tr("No has proporcionado el nombre del obrero"));
        return;
    }
    // Obtiene horas
    int horas = ui->inHoras->value();
    // Obtiene la jornada
    char jornada = '\0';
    if(ui->inMatutino->isChecked())
    {
        jornada = 'M';
    }else if(ui->inNocturna->isChecked())
    {
        jornada = 'N';
    }else if(ui->inVespertina->isChecked())
    {
        jornada = 'V';
    }
    // Instancia el Objeto y se calcula
    CalculoSalario *obrero = new CalculoSalario(nombre,horas,jornada);
    obrero->calcular();
    // Muestra los resultados
    ui->outResultado->appendPlainText(obrero->resultado());
    // Encerar los widgets
    this->borrar();
}

void Principal::borrar()
{
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutino->setChecked(true);
    ui->inNombre->setFocus();
}

void Principal::nuevo()
{
    ui->outResultado->clear();
}

void Principal::on_actionA_cerca_de_triggered()
{
    Acerca *acercaDe = new Acerca(this);
    acercaDe->setVersion(VERSION);
    acercaDe->show();
}

void Principal::on_cmdCalcular_clicked()
{
    this->calcular();
}

void Principal::on_actionA_brir_triggered()
{
    QDir directorio = QDir::home();
    QString pathArchivo = directorio.absolutePath();
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Abriendo archivo"),
                                                    pathArchivo,
                                                    tr("Archivo de texto (*.txt)"));
    QFile f(fileName);
    QTextStream in(&f);
    QString impresion;
    if(!f.open(QIODevice::ReadOnly))
        QMessageBox::warning(this,tr("Salarios"),tr("No se puede abrir el archivo"));
    while(!in.atEnd())
    {
        impresion = impresion + in.readLine() + "\n";
    }
    f.close();
    ui->outResultado->appendPlainText(impresion);
}

void Principal::on_action_Guardar_triggered()
{
    // Crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::home();
    // Agregar al path absoluto del objeto, un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath() + tr("/sin_nombre.txt");
    // Abrir un cuadro de diálogo para seleccionar el nombre y ubicación del archivo a guardar
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar archivo"),
                                                    pathArchivo,
                                                    tr("Archivo de texto (*.txt)"));
    // Crear el archivo a partir del nombre arrojado por el cuadro de diálogo
    QFile f(fileName);
    // Crear el objeto QTextStream (permite escribir sobre el archivo)
    QTextStream out(&f);
    // Intentar abrir el archivo ya sea para escribir (Si no existe) o para agregar texto (si existiera)
    if(!f.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        // Si no se puede abrir muestra mensaje de advertencia
        QMessageBox::warning(this,tr("Salarios"),tr("No se puede abrir el archivo") + fileName);
        // Salir de la función
        return;
    }
    // Guardar contenido del texto de resultado en el archivo
    out << ui->outResultado->toPlainText() << endl;
    // Cerrar el archivo
    f.close();
    // Mostrar mensaje en la barra de estados
    ui->statusbar->showMessage(tr("Archivo guardando en ") + fileName,3000);
}

void Principal::on_action_Calcular_triggered()
{
    this->calcular();
}

void Principal::on_action_Salir_triggered()
{
    this->close();
}
