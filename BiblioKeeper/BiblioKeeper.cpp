#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Структура книги
struct Book {
    string title;   // Название 
    string author;  // Автор 
    int year;       // Год 
    string isbn;    // ISBN 
    int quantity;   // Количество экземпляров 
};

const int MAX_BOOKS = 100;  // Максимальное количество книг в библиотеке
Book books[MAX_BOOKS];      // Массив книг
int bookCount = 0;           // Количество книг в библиотеке
string filename = "library.txt"; // Имя файла

// Добавление книги в библиотеку
void addBook(const Book& book) {
    if (bookCount < MAX_BOOKS) {
        books[bookCount++] = book; // Добавляем книгу в массив и увеличиваем счетчик книг
    }
    else {
        cout << "Библиотека переполнена, невозможно добавить новую книгу." << endl;
    }
}

// Функция сортировки пузырьком для сортировки книг по названию
void bubbleSortBooksByTitle(Book arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].title > arr[j + 1].title) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Если на этом проходе не было перестановок, значит массив уже отсортирован
        if (!swapped) {
            break;
        }
    }
}

// Удаление книги из библиотеки по ISBN
void removeBook(const string& isbn) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].isbn == isbn) { // Если найден книга с соответствующим ISBN
            for (int j = i; j < bookCount - 1; ++j) {
                books[j] = books[j + 1]; // Сдвигаем все книги на одну позицию влево
            }
            bookCount--; // Уменьшаем счетчик книг
            return;
        }
    }
    cout << "Книга с ISBN " << isbn << " не найдена." << endl;
}

// Редактирование книги в библиотеке по ISBN
void editBook(const string& isbn, const Book& newBook) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].isbn == isbn) { // Если найдена книга с соответствующим ISBN
            books[i] = newBook; // Заменяем существующую книгу на новую
            return;
        }
    }
    cout << "Книга с ISBN " << isbn << " не найдена." << endl;
}

// Поиск книги в библиотеке по названию
Book* findBookByTitle(const string& title) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].title == title) { // Если найдена книга с соответствующим названием
            return &books[i]; // Возвращаем указатель на эту книгу
        }
    }
    return nullptr; // Если книга не найдена, возвращаем nullptr
}

// Поиск книги в библиотеке по автору
Book** findBooksByAuthor(const string& author, int& foundCount) {
    Book** foundBooks = new Book * [bookCount]; // Создаем массив указателей на книги
    foundCount = 0; // Инициализируем количество найденных книг

    // Проходим по всем книгам в библиотеке
    for (int i = 0; i < bookCount; ++i) {
        // Если найдена книга с соответствующим автором
        if (books[i].author == author) {
            foundBooks[foundCount++] = &books[i]; // Добавляем указатель на эту книгу в массив найденных книг
        }
    }

    // Если не найдено ни одной книги автора, освобождаем выделенную память и возвращаем nullptr
    if (foundCount == 0) {
        delete[] foundBooks;
        foundBooks = nullptr;
    }

    return foundBooks; // Возвращаем массив указателей на найденные книги
}

// Поиск книги в библиотеке по ISBN
Book* findBookByISBN(const string& isbn) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].isbn == isbn) { // Если найдена книга с соответствующим ISBN
            return &books[i]; // Возвращаем указатель на эту книгу
        }
    }
    return nullptr; // Если книга не найдена, возвращаем nullptr
}

// Вывод списка всех книг в библиотеке
void displayBooks() {
    bubbleSortBooksByTitle(books, bookCount);
    for (int i = 0; i < bookCount; ++i) {
        cout << "Название: " << books[i].title
            << ", Автор: " << books[i].author
            << ", Год: " << books[i].year
            << ", ISBN: " << books[i].isbn
            << ", Количество: " << books[i].quantity << endl;
    }
}

// Сохранение данных библиотеки в файл
void saveToFile() {
    ofstream file(filename); // Открываем файл для записи
    if (file.is_open()) { // Если файл успешно открыт
        for (int i = 0; i < bookCount; ++i) {
            // Записываем данные каждой книги в файл
            file << books[i].title << "\n"
                << books[i].author << "\n"
                << books[i].year << "\n"
                << books[i].isbn << "\n"
                << books[i].quantity << "\n";
        }
        file.close(); // Закрываем файл
    }
    else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

// Загрузка данных библиотеки из файла
void loadFromFile() {
    ifstream file(filename); // Открываем файл для чтения
    if (file.is_open()) { // Если файл успешно открыт
        bookCount = 0;
        while (file.peek() != EOF && bookCount < MAX_BOOKS) {
            // Считываем данные каждой книги из файла
            getline(file, books[bookCount].title);
            getline(file, books[bookCount].author);
            file >> books[bookCount].year;
            file.ignore();
            getline(file, books[bookCount].isbn);
            file >> books[bookCount].quantity;
            file.ignore();
            bookCount++; // Увеличиваем счетчик книг
        }
        file.close(); // Закрываем файл
    }
    else {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

// Увеличение количества экземпляров книги по ISBN
void increaseQuantity(const string& isbn) {
    int increaseAmount;
    cout << "Введите количество для увеличения: ";
    cin >> increaseAmount;

    for (int i = 0; i < bookCount; ++i) {
        if (books[i].isbn == isbn) { // Если найдена книга с соответствующим ISBN
            books[i].quantity += increaseAmount; // Увеличиваем количество экземпляров этой книги на введенное число
            return;
        }
    }
    cout << "Книга с ISBN " << isbn << " не найдена." << endl;
}

// Уменьшение количества экземпляров книги по ISBN
void decreaseQuantity(const string& isbn) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].isbn == isbn) { // Если найдена книга с соответствующим ISBN
            if (books[i].quantity > 0) {
                books[i].quantity--; // Уменьшаем количество экземпляров этой книги, если оно больше нуля
            }
            else {
                cout << "Количество экземпляров книги с ISBN " << isbn << " уже равно нулю." << endl;
            }
            return;
        }
    }
    cout << "Книга с ISBN " << isbn << " не найдена." << endl;
}

// Главная функция программы
int main() {
    setlocale(LC_ALL, "Russian");

    int choice; // Переменная для выбора пользователя

    loadFromFile(); // Загрузка данных библиотеки из файла при запуске программы

    // Главный цикл программы
    do {
        // Вывод меню на экран
        cout << "Меню библиотеки:\n";
        cout << "1. Добавить книгу\n";
        cout << "2. Удалить книгу\n";
        cout << "3. Редактировать книгу\n";
        cout << "4. Найти книгу\n";
        cout << "5. Показать все книги\n";
        cout << "6. Увеличить количество экземпляров книги\n";
        cout << "7. Уменьшить количество экземпляров книги\n";
        cout << "8. Сохранить и выйти\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        // В зависимости от выбора пользователя выполняем соответствующее действие
        if (choice == 1) {
            Book book;
            cout << "Введите название: ";
            cin.ignore();
            getline(cin, book.title);
            cout << "Введите автора: ";
            getline(cin, book.author);
            cout << "Введите год: ";
            cin >> book.year;
            cout << "Введите ISBN: ";
            cin.ignore();
            getline(cin, book.isbn);
            cout << "Введите количество: ";
            cin >> book.quantity;
            addBook(book);
        }
        else if (choice == 2) {
            string isbn;
            cout << "Введите ISBN книги для удаления: ";
            cin.ignore();
            getline(cin, isbn);
            removeBook(isbn);
        }
        else if (choice == 3) {
            string isbn;
            cout << "Введите ISBN книги для редактирования: ";
            cin.ignore();
            getline(cin, isbn);
            Book newBook;
            cout << "Введите новое название: ";
            getline(cin, newBook.title);
            cout << "Введите нового автора: ";
            getline(cin, newBook.author);
            cout << "Введите новый год: ";
            cin >> newBook.year;
            cout << "Введите новый ISBN: ";
            cin.ignore();
            getline(cin, newBook.isbn);
            cout << "Введите новое количество: ";
            cin >> newBook.quantity;
            editBook(isbn, newBook);
        }
        else if (choice == 4) {
            int searchChoice;
            cout << "Найти книгу по:\n";
            cout << "1. Названию\n";
            cout << "2. Автору\n";
            cout << "3. ISBN\n";
            cout << "Введите ваш выбор: ";
            cin >> searchChoice;

            if (searchChoice == 1) {
                string title;
                cout << "Введите название: ";
                cin.ignore();
                getline(cin, title);
                Book* book = findBookByTitle(title);
                if (book) {
                    cout << "Найдена книга:\n";
                    cout << "Название: " << book->title << ", Автор: " << book->author
                        << ", Год: " << book->year << ", ISBN: " << book->isbn
                        << ", Количество: " << book->quantity << endl;
                }
                else {
                    cout << "Книга с названием \"" << title << "\" не найдена." << endl;
                }
            }
            else if (searchChoice == 2) {
                string author;
                cout << "Введите автора: ";
                cin.ignore();
                getline(cin, author);
                int foundCount;
                Book** foundBooks = findBooksByAuthor(author, foundCount);
                if (foundBooks) {
                    cout << "Найдено книг: " << foundCount << endl;
                    for (int i = 0; i < foundCount; ++i) {
                        cout << "Название: " << foundBooks[i]->title << ", Автор: " << foundBooks[i]->author
                            << ", Год: " << foundBooks[i]->year << ", ISBN: " << foundBooks[i]->isbn
                            << ", Количество: " << foundBooks[i]->quantity << endl;
                    }
                    delete[] foundBooks;
                }
                else {
                    cout << "Книги автора \"" << author << "\" не найдены." << endl;
                }
            }
            else if (searchChoice == 3) {
                string isbn;
                cout << "Введите ISBN: ";
                cin.ignore();
                getline(cin, isbn);
                Book* book = findBookByISBN(isbn);
                if (book) {
                    cout << "Найдена книга:\n";
                    cout << "Название: " << book->title << ", Автор: " << book->author
                        << ", Год: " << book->year << ", ISBN: " << book->isbn
                        << ", Количество: " << book->quantity << endl;
                }
                else {
                    cout << "Книга с ISBN \"" << isbn << "\" не найдена." << endl;
                }
            }
            else {
                cout << "Неверный выбор." << endl;
            }
        }
        else if (choice == 5) {
            cout << "Список всех книг в библиотеке:\n";
            displayBooks();
        }
        else if (choice == 6) {
            string isbn;
            cout << "Введите ISBN книги для увеличения количества: ";
            cin.ignore();
            getline(cin, isbn);
            increaseQuantity(isbn);
        }
        else if (choice == 7) {
            string isbn;
            cout << "Введите ISBN книги для уменьшения количества: ";
            cin.ignore();
            getline(cin, isbn);
            decreaseQuantity(isbn);
        }
        else if (choice == 8) {
            saveToFile(); // Сохраняем данные библиотеки в файл перед выходом
            cout << "Данные сохранены. Программа завершена." << endl;
        }
        else {
            cout << "Неверный выбор." << endl;
        }

        cout << endl;
    } while (choice != 8);

    return 0;
}
