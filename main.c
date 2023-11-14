#include <stdio.h>

typedef struct {
    int id;
    char name[500];
    char startDate[100];
    char endDate[100];
} Task;

void print_task_header() {
    printf("\n%-6s | %-30s | %-15s | %-15s\n", "ID", "Name", "Start Date", "End Date");
    printf("------+--------------------------------+-----------------+-----------------\n");
}

void print_task(Task task) {
    printf("%-6d | %-30s | %-15s | %-15s\n", task.id, task.name, task.startDate, task.endDate);
}

void read_tasks_from_file(){
    FILE *file = fopen("./tasks.txt", "r");
    if(file == NULL) {
        perror("Error opening file");
        return;
    }
    Task task;
    print_task_header();
    while(fscanf(file, "%d %500s %100s %100s", &task.id, task.name, task.startDate, task.endDate) == 4) {
        print_task(task);
    }
    fclose(file);
}
// Сохранение введенной пользователем задачи в файл. Выбор пал на текстовый.
void save_task_to_file(Task task) {
    FILE *file = fopen("./tasks.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
1
    // Добавляем '\n' в конце каждой записи для перехода на новую строку
    fprintf(file, "%d,%s,%s,%s\n", task.id, task.name, task.startDate, task.endDate);

    fclose(file);
}
// Создание задачи пользователем
void create_task() {
    static int current_id = 1;
    Task newTask;

    newTask.id = current_id++;
    printf("Enter task name: ");
    getchar();
    fgets(newTask.name, sizeof(newTask.name), stdin);
    printf("Enter start date (YYYY-MM-DD): ");
    fgets(newTask.startDate, sizeof(newTask.startDate), stdin);
    printf("Enter end date (YYYY-MM-DD): ");
    fgets(newTask.endDate, sizeof(newTask.endDate), stdin);
    save_task_to_file(newTask);
}
// Удаление конкретной задачи из файла
void delete_task(int id) {
    FILE *file = fopen("./tasks.txt", "r");
    FILE *tempFile = fopen("./temp.txt", "w");
    Task task;

    if (file == NULL || tempFile == NULL) {
        perror("err opening file");
        return;
    }

    while (fscanf(file, "%d %100s %10s %10s\n", &task.id, task.name, task.startDate, task.endDate) == 4) {
        if (task.id != id) {
            fprintf(tempFile, "%d %s %s %s\n", task.id, task.name, task.startDate, task.endDate);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("./tasks.txt");
    rename("./temp.txt", "./tasks.txt");
}
// Функция для редактирования задачи
void modify_task(){
    int id;
    // Запрашиваем у пользователя ID задачи для редактирования
    printf("Type ID to modify: ");
    scanf("%d", &id);

    // Открываем файл задач для чтения и временный файл для записи
    FILE *file = fopen("./tasks.txt", "r");
    FILE *tempFile = fopen("./temp.txt", "w");
    Task task;

    // Проверяем, успешно ли открылись файлы
    if (file == NULL || tempFile == NULL){
        perror("err opening file");
        return;
    }

    // Читаем задачи из файла
    while (fscanf(file, "%d %100s %10s %10s\n", &task.id, task.name, task.startDate, task.endDate) == 4) {
        // Проверяем, совпадает ли ID текущей задачи с введенным пользователем
        if (task.id == id){
            // Если да, запрашиваем у пользователя новые данные для задачи
            printf("Type task name: ");
            getchar();
            fgets(task.name, sizeof(task.name), stdin);

            printf("Type task start Date (YYYY-MM-DD): ");
            getchar();
            fgets(task.startDate, sizeof(task.startDate), stdin);

            printf("Type task end Date (YYYY-MM-DD): ");
            getchar();
            fgets(task.endDate, sizeof(task.endDate), stdin);
        } else {
            // Если задача с таким ID не найдена, выводим сообщение об ошибке
            perror("Task with this id not found!");
        }
        // Записываем (новую или неизмененную) задачу во временный файл
        fprintf(tempFile, "%d %s %s %s\n", task.id, task.name, task.startDate, task.endDate);
    }

    // Закрываем оба файла
    fclose(file);
    fclose(tempFile);

    // Удаляем оригинальный файл и переименовываем временный файл, заменяя оригинальный
    remove("./tasks.txt");
    rename("./temp.txt", "./tasks.txt");
}
int main() {
    int UserSelection;
    do {
        printf("\nTask Manager\n");
        printf("[1] Create New Task\n[2] Delete Task\n[3] Modify Task\n[4] Exit\n");
        printf("Select an option: ");
        scanf("%d", &UserSelection);

        if(UserSelection == 1) {
            create_task();
        } else if(UserSelection == 2) {
            int id;
            printf("Enter task ID to delete: ");
            scanf("%d", &id);
            delete_task(id);
        } else if(UserSelection == 3) {
            modify_task();
        }
    } while(UserSelection != 4);

    return 0;
}