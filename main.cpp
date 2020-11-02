#include <iostream>
#include <vector>
#include <string>

/*
Предметная область: Библиотека
Информационные объекты: Библиотека, Библиотекарь, Книги, Авторы, Посетитель

У книги может быть только один автор.

Посетитель посещает библиотеку с целью найти книгу по имени автора И/ИЛИ по названию книги.

Необходимо реализовать данный функционал, придерживаясь принципов DRY, KISS, YAGNI и Single Responsibility Principle
*/

using namespace  std;

class book {
    string name;
    string author;
public:
    book(const string name, const string author){
        this->name = name;
        this->author = author;
    }

    string getName() {
        return name;
    };

    string getAuthor() {
        return author;
    }
};

class Library {
    vector<book> books;
    friend class worker;
public:
    Library(vector<book> &_books) {
        books = _books;
    }

protected:
    void addBook(book _book) {
        books.push_back(_book);
    }

    void delBook(book _book) {
        for(int i = 0; i < books.size(); i++) //поиск
        {
            if ((_book.getName() == books[i].getName()) && (_book.getAuthor() == books[i].getAuthor()))
            {
                books.erase(books.begin() + i);
                return;
            }
        }
    }

public:
    void print() {
        cout << "Книги в библиотеке: " << endl;
        for(int i = 0; i < books.size(); i++)
        {
            cout << books[i].getName() << " by " << books[i].getAuthor() << endl;
        }
        cout << endl;
    }

private:
    int search(string name, string author) {
        for (int i = 0; i < books.size(); i++) {
            if ((name == books[i].getName()) && (author == books[i].getAuthor())) {
                return i;
            }
        }
        return -1;
    }

    int searchName(string title) {
        for (int i = 0; i < books.size(); i++) {
            if (title == books[i].getName()) {
                return i;
            }
        }
        return -1;
    }

    int searchAuthor(string author) {
        for (int i = 0; i < books.size(); i++) {
            if (author == books[i].getAuthor()) {
                return i;
            }
        }
        return -1;
    }
};

class worker :  public Library {
public:
    friend class Library;
    worker(vector<book> books) : Library(books) {

    };

    void findBook(string name, string author) {

        if (search(name, author) != -1) {
            cout << "Пожалуйста, ваша книга : " << name << " " << author << endl;
        } else {
            cout << "Нужной книги нет" << endl;
        }
    }

    void findName(string name) {

        if (searchName(name) != -1) {
            cout << "Пожалуйста, ваша книга : " << name << endl;
        } else {
            cout << "Нужной книги нет" << endl;
        }
    }

    void findAuthor(string author) {

        if (searchAuthor(author) != -1) {
            cout << "Пожалуйста, вот книга Автора : " << author << endl;
        } else {
            cout << "Нужной книги нет" << endl;
        }
    }
    void add(book _book) {
        addBook(_book);
    }

    void del(book _book) {
        delBook(_book);
    }
};


int main() {
    setlocale(LC_ALL, "RUS");

    book b1("Один","Пушкин");
    book b2("Два","Есенин");
    book b3("Три","Гоголь");
    book b4("Четыре","Толстой");
    book b5("Пять","Лермонтов");
    book b6("Шесть", "Мандельштам");

    vector<book> books = {b1, b2, b3, b4, b5};
    Library lb(books);
    worker wk(books);

    wk.print();
    wk.findBook("Три","Гоголь");

    wk.add(b6);
    wk.print();
    return 0;
}
