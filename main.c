#include <stdio.h>

//Структура задачи
typedef struct {
    char name[100];    // Название задачи
    char startDate[11]; // Дата начала задачи (в формате ГГГГ-ММ-ДД)
    char endDate[11];   // Дата завершения задачи (в формате ГГГГ-ММ-ДД)
} Task;

// Создание задачи пользователем
void create_task(){
    Task newTask;
    //Имя задачи
    printf("Type task name: ");
    fgets(newTask.name, sizeof(newTask.name), stdin);
    //Дата начала
    printf("Type task start Date (YYYY-MM-DD): ");
    fgets(newTask.name, sizeof(newTask.name), stdin);
    //Дата конца
    printf("Type task end Date (YYYY-MM-DD): ");
    fgets(newTask.name, sizeof(newTask.name), stdin);
    //Передача задачи в функцию save_task_to_file()
    save_task_to_file(newTask);
}
// Сохранение введенной пользователем задачи в файл. Выбор пал на текстовый.
void save_task_to_file(Task task){
    // Открываю файл с задачами для добавления данных
    FILE *file = fopen("./tasks.txt", 'a');
    // Проверка на отсутствие файла или ошибку создания
    if(file == NULL){
        perror("err opening file");
        return;
    }
    fprint(file, "%s %s %s\n", task.name, task.startDate, task.endDate);
    fclose(file);
}g
// Чтение всех задач из файла по команде "show-all"
void read_tasks_from_file(){
    // Открываю файл с задачами для чтения данных
    FILE *file = fopen("./tasks.txt", 'r');
    // Проверка на отсутствие файла или ошибку создания
    if(file == NULL){
        perror("err opening file");
        return;
    }
    Task task;
    // Цикл продолжается до тех пор, пока из файла успешно считываются три строки
    while(fscanf(file, "%100s, %10s, %10s\n", task.name, task.startDate, task.endDate) == 3){
        printf("Name: %s, Start Date: %s, End Date: %s\n", task.name, task.startDate, task.endDate);
    }
    fclose(file);
}
// Удаление конкретной задачи из файла
void delete_task(){

}
// Редактирование задачи
void modify_task(){

}
int main() {
    return 0;
}
