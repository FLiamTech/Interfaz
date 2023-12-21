#include "tasky.h"
#include "ui_tasky.h"

Tasky::Tasky(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasky)
{
    ui->setupUi(this); /*Todo lo que se crea en la interfaz */
     // Limpiar el formulario
    limpiar();


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
    if(nombre.length() == 0)
    {
        QMessageBox::warning(this, "Agregar Tarea", "El nombre de la tarea no puede estar vacio");
        ui->editTarea->setFocus();
        return;
    }
    QString asignatura = ui->cmbAsignatura->currentText();
    QDate fecha = ui->dtFecha->date();
    QTime hora = ui->dtHora->time();
    /*Crea una tarea y Agrega una tarea a la lista*/
    Tarea *t = new Tarea(nombre, asignatura, fecha, hora);
    agregarTarea(t);
    // Limpia el formulario
    limpiar();
    // Guardar tareas
    guardar();
}

void Tasky::agregarTarea(Tarea *t)
{
    m_tareas.append(t);
    // Cantidad de filas actuales
    int fila = ui->tblTareas->rowCount();

    // Va insertando una nueva fila
    ui->tblTareas->insertRow(fila);

    // guarda los datos en las celdas de cada columna creada (fila)

    ui->tblTareas->setItem(fila, TAREA, new QTableWidgetItem(t->nombre()));
    ui->tblTareas->setItem(fila, ASIGNATURA, new QTableWidgetItem(t->asignatura()));
    ui->tblTareas->setItem(fila, FECHA, new QTableWidgetItem(t->fecha().toString("dd/MM/yyyy")));
    ui->tblTareas->setItem(fila, HORA, new QTableWidgetItem(t->hora().toString("hh:mm")));
}

void Tasky::limpiar()
{
    //Establecer la fecha y hora actual
    QDate hoy = QDate::currentDate();
    QTime ahora = QTime::currentTime();
    ui->dtFecha->setMinimumDate(hoy);
    ui->dtFecha->setDate(hoy);
    ui->dtHora->setTime(ahora);

    // Resetear campos
    ui->editTarea->clear();
    ui->cmbAsignatura->setCurrentIndex(0);

    //Setear el foco
    ui->editTarea->setFocus();
}

void Tasky::guardar()
{
    // Abrir el archivo y guardar
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream salida(&archivo);
        Tarea *t;
        foreach(t, m_tareas)
        {
            salida << t->nombre() << ";"<< t->asignatura() << ";";
            salida << t->fecha().toString("dd/MM/yyyy") << ";";
            salida << t->hora().toString("hh:mm") << "\n";
        }

        archivo.close();
        //QMessageBox::information(this,"Guardar contactos","Contactos guardados con éxito");
    }
    else
    {
        QMessageBox::critical(this,"Guardar tareas", "No se puede escribir sobre " + ARCHIVO);
    }

}

