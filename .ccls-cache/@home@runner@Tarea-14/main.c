#include "cola.h" // incluir archivo de encabezado de la cola
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxString 50
#define maxBooks 100
#define maxReserves 10

typedef struct {
  char title[maxString];
  char author[maxString];
  char genre[maxString];
  char isbn[maxString];
  char location[maxString];
  char status[maxString];
  char reserves[maxReserves][maxString];
  int num_reserves;
} Book;

Book library[maxBooks];
int numBooks = 0;

void registerBook() {
  if (numBooks >= maxBooks) {
    printf("Libreria llena, no se pueden registrar mas libros.\n");
    return;
  }

  Book newBook;

  while (getchar() != '\n')
    ;

  printf("Ingrese titulo del libro: ");
  fgets(newBook.title, sizeof(newBook.title), stdin);
  newBook.title[strcspn(newBook.title, "\n")] =
      '\0'; // Eliminar el '\n' al final

  while (strlen(newBook.title) > 50) {
    printf("Titulo invalido. Ingrese nuevamente: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';
  }

  printf("Ingrese autor: ");
  fgets(newBook.author, sizeof(newBook.author), stdin);
  newBook.author[strcspn(newBook.author, "\n")] = '\0';

  while (strlen(newBook.author) > 50) {
    printf("Autor invalido. Ingrese nuevamente: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';
  }

  printf("Ingrese genero: ");
  fgets(newBook.genre, sizeof(newBook.genre), stdin);
  newBook.genre[strcspn(newBook.genre, "\n")] = '\0';

  while (strlen(newBook.genre) > 50) {
    printf("Genero invalido. Ingrese nuevamente: ");
    fgets(newBook.genre, sizeof(newBook.genre), stdin);
    newBook.genre[strcspn(newBook.genre, "\n")] = '\0';
  }

  printf("Ingrese ISBN: ");
  fgets(newBook.isbn, sizeof(newBook.isbn), stdin);
  newBook.isbn[strcspn(newBook.isbn, "\n")] = '\0';

  while (strlen(newBook.isbn) > 50) {
    printf("ISBN invalido. Ingrese nuevamente: ");
    fgets(newBook.isbn, sizeof(newBook.isbn), stdin);
    newBook.isbn[strcspn(newBook.isbn, "\n")] = '\0';
  }

  printf("Ingrese ubicacion: ");
  fgets(newBook.location, sizeof(newBook.location), stdin);
  newBook.location[strcspn(newBook.location, "\n")] = '\0';

  while (strlen(newBook.location) > 50) {
    printf("Ubicacion invalida. Ingrese nuevamente: ");
    fgets(newBook.location, sizeof(newBook.location), stdin);
    newBook.location[strcspn(newBook.location, "\n")] = '\0';
  }

  strcpy(newBook.status, "Disponible");
  newBook.num_reserves = 0;

  library[numBooks++] = newBook;

  printf("Registro completado!\n");
}

void showBookData() {
  char title[maxString];
  char author[maxString];

  printf("Ingrese titulo del libro: ");
  scanf(" %[^\n]", title);

  printf("Ingrese autor: ");
  scanf(" %[^\n]", author);

  for (int i = 0; i < numBooks; i++) {
    if (strcmp(library[i].title, title) == 0 &&
        strcmp(library[i].author, author) == 0) {
      printf("Titulo: %s\n", library[i].title);
      printf("Autor: %s\n", library[i].author);
      printf("Genero: %s\n", library[i].genre);
      printf("ISBN: %s\n", library[i].isbn);
      printf("Ubicacion: %s\n", library[i].location);
      printf("Estado: %s\n", library[i].status);
      if (library[i].num_reserves > 0) {
        printf("Reservas:\n");
        for (int j = 0; j < library[i].num_reserves; j++) {
          printf("  %s\n", library[i].reserves[j]);
        }
      }
      return;
    }
  }

  printf("Libro no encontrado.\n");
}

void showAllBooks() {
  if (numBooks == 0) {
    printf("No hay libros registrados.\n");
    return;
  }

  printf("Lista de todos los libros:\n");
  for (int i = 0; i < numBooks; i++) {
    printf("%s - %s\n", library[i].title, library[i].author);
  }
}

int main() {
  int choice;

  Queue reserveQueue;
  initQueue(&reserveQueue);

  do {
    printf("\nSistema de biblioteca\n\n");
    printf("1. Registrar libro\n");
    printf("2. Datos del libro\n");
    printf("3. Mostrar todos los libros\n");
    printf("4. Reservar libro\n");
    printf("5. Cancelar reservacion\n");
    printf("6. Retirar libro\n");
    printf("7. Regresar libro\n");
    printf("8. Mostrar libros prestados\n");
    printf("9. Importar libros csv\n");
    printf("10.Exportar libros csv\n");
    printf("0. Salir\n\n");
    printf("Ingrese una opcion: ");

    int result = scanf("%d", &choice);

    if (result != 1) {
      printf("Error al leer la opcion.\n");
      break;
    }

    switch (choice) {
    case 1:
      registerBook();
      break;
    case 2:
      showBookData();
      break;
    case 3:
      showAllBooks();
      break;
    case 4:
      reserveBook(&reserveQueue);
      break;
    case 5:
      cancelReservation(&reserveQueue);
      break;
    case 6:
      borrowBook(&reserveQueue);
      break;
    case 7:
      returnBook(&reserveQueue);
      break;
    case 8:
      showBorrowedBooks(&reserveQueue);
      break;
    case 9:
      importBooks();
      break;
    case 10:
      exportBooks();
      break;
    case 0:
      printf("Saliendo...\n");
      break;
    default:
      printf("\nOpcion invalida, intente nuevamente.\n");
    }
  } while (choice != 0);

  return 0;
}