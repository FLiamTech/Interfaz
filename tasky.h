#ifndef TASKY_H
#define TASKY_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

#include <tarea.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Tasky; }
QT_END_NAMESPACE

class Tasky : public QMainWindow
{
    Q_OBJECT

public:
    Tasky(QWidget *parent = nullptr);
    ~Tasky();

private slots:
    void on_btnAgregar_clicked();

    void on_tblTareas_cellDoubleClicked(int row, int column);

private:
    Ui::Tasky *ui;
    void agregarTarea(Tarea *t);
    void limpiar();
    void guardar();
    void cargar();
    bool colorTarea(const Tarea *t);
    void eliminar(int fila);
    const QString ARCHIVO = "tareas.csv";
    QList<Tarea*> m_tareas;
    enum Columna
    {
        TAREA, ASIGNATURA, FECHA, HORA
    };
};
#endif // TASKY_H
