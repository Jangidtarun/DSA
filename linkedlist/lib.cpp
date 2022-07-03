#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

class Patron;
class Book
{
public:
    Book()
    {
        patron = NULL;
    }
    bool operator==(const Book &bk) const
    {
        return title == bk.title;
    }

private:
    string title;
    Patron *patron;
    ostream &printBook(ostream &) const;
    friend ostream &operator<<(ostream &out, const Book &bk)
    {
        return bk.printBook(out);
    }
    friend class CheckedOutBook;
    friend Patron;
    friend void includeBook();
    friend void checkOutBook();
    friend void returnBook();
};

class Author
{
public:
    Author() {}
    bool operator==(const Author &ar) const
    {
        return ar.name == name;
    }

private:
    string name;
    list<Book> books;
    ostream &printAuthor(ostream &) const;
    friend ostream &operator<<(ostream &out, const Author &ar)
    {
        return ar.printAuthor(out);
    }
    friend void includeBook();
    friend void checkOutBook();
    friend void returnBook();
    friend class CheckedOutBook;
    friend Patron;
};

class CheckedOutBook
{
public:
    CheckedOutBook(list<Author>::iterator ar, list<Book>::iterator bk)
    {
        author = ar;
        book = bk;
    }

    bool operator==(const CheckedOutBook &bk) const
    {
        return author->name == bk.author->name &&
               book->title == bk.book->title;
    }

private:
    list<Author>::iterator author;
    list<Book>::iterator book;
    friend void checkOutBook();
    friend void returnBook();
    friend Patron;
};

class Patron
{
public:
    Patron() {}
    bool operator==(const Patron &pn) const
    {
        return name == pn.name;
    }

private:
    string name;
    list<CheckedOutBook> books;
    ostream &printPatron(ostream &) const;
    friend ostream &operator<<(ostream &out, const Patron &pn)
    {
        return pn.printPatron(out);
    }
    friend void checkOutBook();
    friend void returnBook();
    friend Book;
};

list<Author> catalog['Z' + 1];
list<Patron> people['Z' + 1];

ostream &Book::printBook(ostream &out) const
{
    out << " * " << title;
    if (patron != 0)
    {
        out << " - checked out to" << patron->name << '\n';
    }
    return out;
}

ostream &Author::printAuthor(ostream &out) const
{
    out << name << '\n';
    for (auto &it : books)
    {
        out << it;
    }
    return out;
}

ostream &Patron::printPatron(ostream &out) const
{
    out << name;
    if (!books.empty())
    {
        out << "has the following books:\n";
        for (auto &it : books)
        {
            out << " * " << it.author->name << ", " << it.book->title << endl;
        }
    }
    else
    {
        out << "has no books\n";
    }
    return out;
}

template <class T>
ostream &operator<<(ostream &out, const list<T> &lst)
{
    for (auto &ref : lst)
    {
        out << ref;
    }
    return out;
}

void status()
{
    cout << "library has the following books:\n";
    for (int i = 'A'; i <= 'Z'; i++)
    {
        if (!catalog[i].empty())
        {
            cout << catalog[i];
        }
    }

    cout << "\nthe following people are using the library:\n";
    for (int i = 'A'; i <= 'Z'; i++)
    {
        if (!people[i].empty())
        {
            cout << people[i];
        }
    }
}

void includeBook()
{
    Author newAuthor;
    Book newBook;
    cout << "enter author's name: ";
    getline(cin, newAuthor.name);
    cout << "enter the title of the book: ";
    getline(cin, newBook.title);

    auto oldAuthor = find(catalog[newAuthor.name[0]].begin(),
                          catalog[newAuthor.name[0]].end(), newAuthor);
    if (oldAuthor == catalog[newAuthor.name[0]].end())
    {
        newAuthor.books.push_front(newBook);
        catalog[newAuthor.name[0]].push_front(newAuthor);
    }
    else
    {
        (*oldAuthor).books.push_front(newBook);
    }
}

void checkOutBook()
{
    Patron patron;
    Author author;
    Book book;
    list<Author>::iterator authorRef;
    list<Book>::iterator bookRef;

    cout << "enter patron's name: ";
    getline(cin, patron.name);

    while (true)
    {
        cout << "enter author's name: ";
        getline(cin, author.name);
        authorRef = find(catalog[author.name[0]].begin(),
                         catalog[author.name[0]].end(), author);

        if (authorRef == catalog[author.name[0]].end())
            cout << "Misspelled author's name\n";
        else
            break;
    }

    while (true)
    {
        cout << "enter the title of the book: ";
        getline(cin, book.title);
        bookRef = find((*authorRef).books.begin(),
                       (*authorRef).books.end(), book);
        if (bookRef == (*authorRef).books.end())
            cout << "Misspelled title\n";
        else
            break;
    }

    list<Patron>::iterator patronRef;
    patronRef = find(people[patron.name[0]].begin(), people[patron.name[0]].end(), patron);
    CheckedOutBook checkedOutBook(authorRef, bookRef);
    if (patronRef == people[patron.name[0]].end())
    {
        patron.books.push_front(checkedOutBook);
        people[patron.name[0]].push_front(patron);
        bookRef->patron = &*people[patron.name[0]].begin();
    }

    else
    {
        patronRef->books.push_front(checkedOutBook);
        bookRef->patron = &*patronRef;
    }
}

void returnBook()
{
    Patron patron;
    Book book;
    Author author;
    list<Patron>::iterator patronRef;
    list<Book>::iterator bookRef;
    list<Author>::iterator authorRef;

    while (true)
    {
        cout << "Enter patron's name: ";
        getline(cin, patron.name);
        patronRef = find(people[patron.name[0]].begin(),
                         people[patron.name[0]].end(), patron);
        if (patronRef == people[patron.name[0]].end())
            cout << "Patron's name misspelled\n";
        else
            break;
    }
    while (true)
    {
        cout << "enter author's name: ";
        getline(cin, author.name);
        authorRef = find(catalog[author.name[0]].begin(),
                         catalog[author.name[0]].end(), author);
        if (authorRef == catalog[author.name[0]].end())
            cout << "Misspelled author's name\n";
        else
            break;
    }
    while (true)
    {
        cout << "enter the title of the book: ";
        getline(cin, book.title);
        bookRef = find((*authorRef).books.begin(),
                       (*authorRef).books.end(), book);
        if (bookRef == (*authorRef).books.end())
            cout << "Misspelled title\n";
        else
            break;
    }
    CheckedOutBook checkedOutBook(authorRef, bookRef);
    bookRef->patron = 0;
    patronRef->books.remove(checkedOutBook);
}

int menu()
{
    int option;
    cout << "\nEnter one of the following options:\n"
         << "1. Include a book in the catalog\n2. Check out a book\n"
         << "3. Return a book\n4. Status\n5. Exit\n"
         << "Your option? ";
    cin >> option;
    cin.get(); // discard '\n';
    return option;
}

int main()
{
    while (true)
        switch (menu())
        {
        case 1:
            includeBook();
            break;
        case 2:
            checkOutBook();
            break;
        case 3:
            returnBook();
            break;
        case 4:
            status();
            break;
        case 5:
            return 0;
        default:
            cout << "Wrong option, try again: ";
        }

    return EXIT_SUCCESS;
}