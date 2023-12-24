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
    cargar();
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

    // Verificador para cambiar el color
    if(colorTarea(t))
    {
        QColor colorFondo(255, 0, 0);
        for (int i = 0; i < ui->tblTareas->columnCount(); ++i)
        {
            QTableWidgetItem *item = ui->tblTareas->item(fila, i);
            if (item)
            {
                item->setBackground(colorFondo);
            }
        }
    }
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

void Tasky::cargar()
{
    QFile archivo(ARCHIVO);
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream entrada(&archivo);

        while (!entrada.atEnd())
        {
            QString linea = entrada.readLine();
            QStringList datos = linea.split(";");
            QString nombre = datos[0];
            QString asignatura = datos[1];
            QStringList fecha = datos[2].split("/");
            QDate f(fecha[2].toInt(), fecha[1].toInt(), fecha[0].toInt());
            QStringList hora = datos[3].split(":");
            QTime h(hora[0].toInt(), hora[1].toInt());

            //QDate fecha = QDate::fromString(datos[2], "dd/MM/yyyy");
            //QTime hora = QTime::fromString(datos[3], "hh:mm");

            Tarea *t = new Tarea(nombre, asignatura, f, h);
            agregarTarea(t);
        }

        archivo.close();
    }
    else
    {
        QMessageBox::critical(this, "Cargar tareas", "No se puede leer desde " + ARCHIVO);
    }
}

void Tasky::eliminar(int fila)
{
    if(fila >= 0 && fila < ui->tblTareas->rowCount())
    {
        // Elimina la tarea de la lista
        Tarea *t = m_tareas.takeAt(fila);
        delete t;

        // Elimina la tarea de la tabla
        ui->tblTareas->removeRow(fila);
        guardar();
    }
}

void Tasky::on_tblTareas_cellDoubleClicked(int row, int column)
{
    if(column == TAREA)
    {
        QMessageBox::StandardButton respuesta = QMessageBox::question(this, "Eliminar tarea", "Seguro que desea eliminar esta tarea?", QMessageBox::Yes | QMessageBox::No);
        if (respuesta == QMessageBox::Yes)
        {
            eliminar(row);
        }
    }
}

bool Tasky::colorTarea(const Tarea *t)
{
    // Para la fecha actual
    QDate fechaActual = QDate::currentDate();
    // Para la fecha limite
    QDate fechaLimite = t->fecha();
    return (fechaLimite >= fechaActual && fechaLimite <= fechaActual.addDays(1));
}
