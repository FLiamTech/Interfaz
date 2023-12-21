#include "tasky.h"
#include "ui_tasky.h"

Tasky::Tasky(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasky)
{
    ui->setupUi(this); /*Todo lo que se crea en la interfaz */

    //Establecer la fecha y hora actual
    QDate hoy = QDate::currentDate();
    QTime ahora = QTime::currentTime();
    ui->dtFecha->setMinimumDate(hoy);
    ui->dtFecha->setDate(hoy);
    ui->dtHora->setTime(ahora);

    /*Configurar la tabla*/
    ui->tblTareas->setColumnCount(4);
    QStringList cabecera;
    cabecera << "Tarea" << "Asignatura" << "Fecha" << "Hora";
    ui->tblTareas->setHorizontalHeaderLabels(cabecera);
}

Tasky::~Tasky()
{
    delete ui;
}

void Tasky::on_btnAgregar_clicked() /*para que aparezca se usa go to slot al boton que vayamos a accionar*/
{
    QString nombre = ui->editTarea->text(); /*editTarea es el nombre que le pusimos al objeto | text es el metodo*/
    QString asignatura = ui->cmbAsignatura->currentText();
    QDate fecha = ui->dtFecha->date();
    QTime hora = ui->dtHora->time();
    /*Crea una tarea y Agrega una tarea a la lista*/
    m_tareas.append(new Tarea(nombre, asignatura, fecha, hora));

    // Cantidad de filas actuales
    int fila = ui->tblTareas->rowCount();

    // Va insertando una nueva fila
    ui->tblTareas->insertRow(fila);

    // guarda los datos en las celdas de cada columna creada (fila)

    ui->tblTareas->setItem(fila, 0, new QTableWidgetItem(nombre));
    ui->tblTareas->setItem(fila, 1, new QTableWidgetItem(asignatura));
    ui->tblTareas->setItem(fila, 2, new QTableWidgetItem(fecha.toString("dd/MM/yyyy")));
    ui->tblTareas->setItem(fila, 3, new QTableWidgetItem(hora.toString("hh:mm")));

    // resetea las opciones

    ui->editTarea->clear();
    ui->cmbAsignatura->setCurrentIndex(0);
    ui->dtFecha->setDate(QDate::currentDate());
    ui->dtHora->setTime(QTime::currentTime());
}

