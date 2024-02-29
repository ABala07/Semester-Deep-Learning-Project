#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Strukturat
typedef struct {
    char isbn[14];
    char category[101];
    char title[201];
    char publicationYear[16];
    char author[21];
    int borrowCount;
} Book;

typedef struct {
    char studentID[11];
    char name[51];
    char surname[51];
    char faculty[51];
    int borrowCount; 
} Student;

typedef struct {
    char studentID[11];
    char isbn[14];
    char borrowDate[11];
    char returnDate[11];
    int status;
} BorrowedBook;

// Prototipet e funksijoneve
void registerBook();
void registerStudent();
void borrowBook();
void returnBook();
void availableBooks();
void searchBook();
void mostBorrowedBooks();
void mostActiveStudents();

//path per filet
const char bookFilePath[] = "libra.txt";
const char studentFilePath[] = "student.txt";
const char borrowedBookFilePath[] = "merr_libra.txt";

int main() {
    int choice;

    do {
        // Menuja
        printf("\nSistemi I Menaxhimit te Bibliotekes\n");
        printf("1. Registro Liber\n");
        printf("2. Registro Student\n");
        printf("3. Marrje libri\n");
        printf("4. Kthe librin \n");
        printf("5. Lista e librave qe jane te lire per ti lexuar\n");
        printf("6. Kerkim libin sipas ISBN ose titullit te librit\n");
        printf("7. Librat qe lexohen me shume \n");
        printf("8. Studentet qe lexojne me shume  \n");
        printf("0. Dalje\n");
        printf("Zgjidhni : ");
        scanf("%d", &choice);

        // Perform the chosen action
        switch (choice) {
            case 1:
                registerBook();
                break;
            case 2:
                registerStudent();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                availableBooks();
                break;
            case 6:
                searchBook();
                break;
            case 7:
                mostBorrowedBooks();
                break;
            case 8:
                mostActiveStudents();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Zgjedhje e Gabuar. Provoje Perseri.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

void registerBook() {
    Book newBook;

    printf("\nRregjistro Liber\n");
    printf("ISBN: ");
    scanf("%13s", newBook.isbn);
    printf("Kategoria: ");
    scanf("%100s", newBook.category);
    printf("Titulli: ");
    scanf(" %[^\n]s", newBook.title);
    printf("Viti i Publikimit: ");
    scanf("%15s", newBook.publicationYear);
    printf("Autori: ");
    scanf("%20s", newBook.author);
    newBook.borrowCount = 0;

    // Hap file
    FILE *file = fopen(bookFilePath, "a");
    if (file == NULL) {
        printf("Error gjate hapjes se dokumentit.\n");
        return;
    }

    // shkruaj librin e ri ne dokument
    fprintf(file, "%s;%s;%s;%s;%s;%d\n", newBook.isbn, newBook.category, newBook.title, newBook.publicationYear,
            newBook.author, newBook.borrowCount);

    // Close the file
    fclose(file);

    printf("Libri u rregjistrua me sukses.\n");
}

void registerStudent() {
    Student newStudent;

    printf("\nRegistro Student\n");
    printf("ID: ");
    scanf("%10s", newStudent.studentID);
    printf("Emer: ");
    scanf("%50s", newStudent.name);
    printf("Mbiemer: ");
    scanf("%50s", newStudent.surname);
    printf("Fakultet: ");
    scanf("%50s", newStudent.faculty);

    // Open the file in append mode
    FILE *file = fopen(studentFilePath, "a");
    if (file == NULL) {
        printf("Error gjate hapjes se dokumentit.\n");
        return;
    }

    // shkruaj studentin e ri ne dokument
    fprintf(file, "%s;%s;%s;%s\n", newStudent.studentID, newStudent.name, newStudent.surname, newStudent.faculty);

    // Close the file
    fclose(file);

    printf("Studenti u rregjistrua me sukses.\n");
}

void borrowBook() {
    BorrowedBook borrowedBook;
    char studentID[11], bookISBN[14];

    printf("\nBorrow Book\n");
    printf("ID Studenti : ");
    scanf("%10s", studentID);
    printf("ISBN e librit: ");
    scanf("%13s", bookISBN);

    // Open the file 
    FILE *file = fopen(borrowedBookFilePath, "a");
    if (file == NULL) {
        printf("Error gjate hapjes se file.\n");
        return;
    }

    // Kontrollo nese studenti os libri ekziston
    FILE *studentFile = fopen(studentFilePath, "r");
    FILE *bookFile = fopen(bookFilePath, "r");

    if (studentFile == NULL || bookFile == NULL) {
        printf("Error gjate hapjes se file.\n");
        fclose(file);
        return;
    }

    char line[256];
    int studentFound = 0, bookFound = 0;

    // kontroll nese studenti ekziston
    while (fgets(line, sizeof(line), studentFile)) {
        char *id = strtok(line, ";");
        if (strcmp(id, studentID) == 0) {
            studentFound = 1;
            break;
        }
    }

    // kontroll nese libri ekziston
    while (fgets(line, sizeof(line), bookFile)) {
        char *isbn = strtok(line, ";");
        if (strcmp(isbn, bookISBN) == 0) {
            bookFound = 1;
            break;
        }
    }

    fclose(studentFile);
    fclose(bookFile);

    if (!studentFound || !bookFound) {
        printf("Studenti ose libri nuk u gjet .\n");
        fclose(file);
        return;
    }

    strcpy(borrowedBook.studentID, studentID);
    strcpy(borrowedBook.isbn, bookISBN);

   //  Vendosni datat e huazimit dhe kthimit dhe update statusin e librit

    borrowedBook.status = 0;

    // shkruaj librin e huazuar ne file
    fprintf(file, "%s;%s;%s;%s;%d\n", borrowedBook.studentID, borrowedBook.isbn, borrowedBook.borrowDate,
            borrowedBook.returnDate, borrowedBook.status);

    // file close
    fclose(file);

    printf("Libri u huazua me sukses.\n");
}

void returnBook() {
    // TODO: Implement returnBook() function
    printf("Kthe Librin\n");
}

void availableBooks() {
    printf("\nLista e librave qe jane te lire per ti lexuar\n");

    // Open the file  
    FILE *file = fopen(bookFilePath, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];

    // lexo dhe shfaq cdo liber nga file
    while (fgets(line, sizeof(line), file)) {
        char *isbn = strtok(line, ";");
        char *category = strtok(NULL, ";");
        char *title = strtok(NULL, ";");
        char *publicationYear = strtok(NULL, ";");
        char *author = strtok(NULL, ";");
        int borrowCount = atoi(strtok(NULL, ";"));

        if (borrowCount == 0) {
            printf("ISBN: %s\nKategoria: %s\nTitulli: %s\nViti i Publikimit: %s\nAutori: %s\n\n",
                   isbn, category, title, publicationYear, author);
        }
    }

    // Close the file
    fclose(file);
}

void searchBook() {
    char searchISBN[14], searchTitle[201];
    int choice;

    printf("\nKerko Liber\n");
    printf("1. Kerko me ISBN\n");
    printf("2. Kerko me Titull\n");
    printf("Zgjedhja: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Vendosni ISBN: ");
            scanf("%13s", searchISBN);
            break;
        case 2:
            printf("Vendosni Titullin: ");
            scanf(" %[^\n]s", searchTitle);
            break;
        default:
            printf("Zgjedhje e gabuar. Provo perseri.\n");
            return;
    }

    printf("\nKerko Rezultatet\n");

    // Open the file 
    FILE *file = fopen(bookFilePath, "r");
    if (file == NULL) {
        printf("Error gjate hapjes se file.\n");
        return;
    }

    char line[256];
    int found = 0;

    // Kërkoni për librin bazuar në opsionin e zgjedhur
    while (fgets(line, sizeof(line), file)) {
        char *isbn = strtok(line, ";");
        char *category = strtok(NULL, ";");
        char *title = strtok(NULL, ";");
        char *publicationYear = strtok(NULL, ";");
        char *author = strtok(NULL, ";");
        int borrowCount = atoi(strtok(NULL, ";"));

        if ((choice == 1 && strcmp(isbn, searchISBN) == 0) ||
            (choice == 2 && strstr(title, searchTitle) != NULL)) {
            printf("ISBN: %s\nKategoria: %s\nTitulli: %s\nViti i Publikimit: %s\nAutori: %s\n\n",
                   isbn, category, title, publicationYear, author);
            found = 1;
        }
    }

    if (!found) {
        printf("Libri nuk u gjet.\n");
    }

    // Close the file
    fclose(file);
}

void mostBorrowedBooks() {
    
    printf("Librat qe lexohet me shume (10 te paret) \n");
    
        // Open the borrowed book file
    FILE *file = fopen(borrowedBookFilePath, "r");
    if (file == NULL) {
        printf("Nuk mund te hapet skedari %s.\n", borrowedBookFilePath);
        return;
    }

    // Count the borrow counts for each book
    const int MAX_BOOKS = 1000;
    Book books[MAX_BOOKS];
    int bookCount = 0;

    BorrowedBook borrowedBook;
    while (fread(&borrowedBook, sizeof(BorrowedBook), 1, file) == 1) {
        // Check if the book is already in the array
        int bookIndex = -1;
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(borrowedBook.isbn, books[i].isbn) == 0) {
                bookIndex = i;
                break;
            }
        }

        // If the book is not found, add it to the array
        if (bookIndex == -1) {
            // Check if the maximum number of books has been reached
            if (bookCount >= MAX_BOOKS) {
                printf("Mbetur pa vend ne varg. Nuk mund te shtohen me libra te tjere.\n");
                fclose(file);
                return;
            }

            // Open the book file to retrieve book details
            FILE *bookFile = fopen(bookFilePath, "r");
            if (bookFile == NULL) {
                printf("Nuk mund te hapet skedari %s.\n", bookFilePath);
                fclose(file);
                return;
            }

            // Find the book with the matching ISBN
            Book book;
            while (fread(&book, sizeof(Book), 1, bookFile) == 1) {
                if (strcmp(borrowedBook.isbn, book.isbn) == 0) {
                    strcpy(books[bookCount].isbn, book.isbn);
                    strcpy(books[bookCount].category, book.category);
                    strcpy(books[bookCount].title, book.title);
                    strcpy(books[bookCount].publicationYear, book.publicationYear);
                    strcpy(books[bookCount].author, book.author);
                    books[bookCount].borrowCount = 1;
                    bookCount++;
                    break;
                }
            }

            fclose(bookFile);
        } else {
            // If the book is found, increment the borrow count
            books[bookIndex].borrowCount++;
        }
    }

    fclose(file);

    // Sort the books by borrow count in descending order
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - i - 1; j++) {
            if (books[j].borrowCount < books[j + 1].borrowCount) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }

    // Display the most borrowed books
    const int numBooksToDisplay = 5;
    printf("ISBN\t\tTitulli\t\tAutori\t\t\tViti i publikimit\tKategoria\tSasia e huazimeve\n");
    for (int i = 0; i < numBooksToDisplay && i < bookCount; i++) {
        printf("%s\t%s\t%s\t\t%s\t\t%s\t\t%d\n", books[i].isbn, books[i].title, books[i].author, books[i].publicationYear, books[i].category, books[i].borrowCount);
    }

}

void mostActiveStudents() {
    // TODO: Implement mostActiveStudents() function
    printf("Studentet qe lexojne me shume  \n");
    
    // Open the borrowed book file
    FILE *file = fopen(borrowedBookFilePath, "r");
    if (file == NULL) {
        printf("Nuk mund te hapet skedari %s.\n", borrowedBookFilePath);
        return;
    }

    // Count the borrow counts for each student
    const int MAX_STUDENTS = 1000;
    Student students[MAX_STUDENTS];
    int studentCount = 0;

    BorrowedBook borrowedBook;
    while (fread(&borrowedBook, sizeof(BorrowedBook), 1, file) == 1) {
        // Check if the student is already in the array
        int studentIndex = -1;
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(borrowedBook.studentID, students[i].studentID) == 0) {
                studentIndex = i;
                break;
            }
        }

        // If the student is not found, add them to the array
        if (studentIndex == -1) {
            // Check if the maximum number of students has been reached
            if (studentCount >= MAX_STUDENTS) {
                printf("Mbetur pa vend ne varg. Nuk mund te shtohen me studente te tjere.\n");
                fclose(file);
                return;
            }

            // Open the student file to retrieve student details
            FILE *studentFile = fopen(studentFilePath, "r");
            if (studentFile == NULL) {
                printf("Nuk mund te hapet skedari %s.\n", studentFilePath);
                fclose(file);
                return;
            }

            // Find the student with the matching student ID
            Student student;
            while (fread(&student, sizeof(Student), 1, studentFile) == 1) {
                if (strcmp(borrowedBook.studentID, student.studentID) == 0) {
                    strcpy(students[studentCount].studentID, student.studentID);
                    strcpy(students[studentCount].name, student.name);
                    strcpy(students[studentCount].surname, student.surname);
                    strcpy(students[studentCount].faculty, student.faculty);
                    studentCount++;
                    break;
                }
            }

            fclose(studentFile);
        }
    }

    fclose(file);

    // Sort the students by borrow count in descending order
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].borrowCount < students[j + 1].borrowCount) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // Display the most active students
    const int numStudentsToDisplay = 5;
    printf("Student ID\tEmri\t\tMbiemri\t\tFakulteti\t\tSasia e huazimeve\n");
    for (int i = 0; i < numStudentsToDisplay && i < studentCount; i++) {
        printf("%s\t%s\t%s\t%s\t\t%d\n", students[i].studentID, students[i].name, students[i].surname, students[i].faculty, students[i].borrowCount);
    
}
    
}

