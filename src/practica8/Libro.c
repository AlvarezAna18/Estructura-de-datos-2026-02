#include "Libro.h"

void imprimirLibro(void *vlibro)
{
	if(!vlibro) return;
	Libro *libro = vlibro;
    //printf("%-18s | %-41s | %-25s | %d | %s",libro.isbn, libro.titulo,libro.autor,libro.fecha,libro.disponible);
	printf("%-18s | ",libro->isbn);
	printf("%-41s | ",libro->titulo);
	printf("%-25s | ",libro->autor);
	printf("%d | ",libro->fecha);
	if(libro->disponible)
		printf("DISPONIBLE");
	else
		printf("PRESTADO");
}

Acervo obtener_libros(void)
{
    static Libro libros[] = {
        {"978-3-16-148410-0", "El Quijote", "Miguel de Cervantes", 1605, 1},
        {"978-0-7432-7356-5", "1984", "George Orwell", 1949, 1},
        {"978-0-452-28423-4", "Matar a un ruisenor", "Harper Lee", 1960, 0},
        {"978-0-14-044926-6", "Crimen y castigo", "Fiodor Dostoyevski", 1866, 1},
        {"978-0-307-74118-4", "El gran Gatsby", "F. Scott Fitzgerald", 1925, 0},
        {"978-1-56619-909-4", "Orgullo y prejuicio", "Jane Austen", 1813, 1},
        {"978-0-553-21311-7", "Fahrenheit 451", "Ray Bradbury", 1953, 1},
        {"978-0-553-21311-8", "La Metamorfosis", "Franz Kafka", 1915, 0},
        {"978-0-7434-9757-3", "Los miserables", "Victor Hugo", 1862, 1},
        {"978-0-399-50128-5", "La sombra del viento", "Carlos Ruiz Zafon", 2001, 1},
        {"978-0-8129-8655-4", "Cien anos de soledad", "Gabriel Garcia Marquez", 1967, 1},
        {"978-0-7432-7356-6", "Brave New World", "Aldous Huxley", 1932, 0},
        {"978-0-399-15124-2", "El codigo Da Vinci", "Dan Brown", 2003, 1},
        {"978-0-316-76948-1", "It", "Stephen King", 1986, 0},
        {"978-0-316-76948-2", "El resplandor", "Stephen King", 1977, 1},
        {"978-0-06-112008-4", "El Hobbit", "J.R.R. Tolkien", 1937, 1},
        {"978-0-618-64015-7", "El Senor de los Anillos", "J.R.R. Tolkien", 1954, 1},
        {"978-0-14-028333-4", "Ulises", "James Joyce", 1922, 0},
        {"978-0-7432-7356-7", "Las aventuras de Sherlock Holmes", "Arthur Conan Doyle", 1892, 1},
        {"978-0-307-38926-3", "Dracula", "Bram Stoker", 1897, 0},
        {"978-0-452-28423-5", "Frankenstein", "Mary Shelley", 1818, 1},
        {"978-0-7432-7356-8", "Los juegos del hambre", "Suzanne Collins", 2008, 1},
        {"978-1-4516-7321-1", "Los hombres que no amaban a las mujeres", "Stieg Larsson", 2005, 1},
        {"978-0-7653-4624-8", "Duna", "Frank Herbert", 1965, 0},
        {"978-0-307-28018-2", "La carretera", "Cormac McCarthy", 2006, 1},
        {"978-0-7475-3269-9", "Harry Potter y la piedra filosofal", "J.K. Rowling", 1997, 1},
        {"978-0-7475-3849-3", "Harry Potter y la camara secreta", "J.K. Rowling", 1998, 1},
        {"978-0-7475-4215-6", "Harry Potter y el prisionero de Azkaban", "J.K. Rowling", 1999, 1},
        {"978-0-7475-4624-6", "Harry Potter y el caliz de fuego", "J.K. Rowling", 2000, 1},
        {"978-0-7475-5100-5", "Harry Potter y la Orden del Fenix", "J.K. Rowling", 2003, 0},
        {"978-0-7475-8108-4", "Harry Potter y el misterio del principe", "J.K. Rowling", 2005, 1},
        {"978-0-545-01022-1", "Harry Potter y las Reliquias de la Muerte", "J.K. Rowling", 2007, 1},
        {"978-0-399-15834-6", "El nombre del viento", "Patrick Rothfuss", 2007, 1},
        {"978-0-7564-0714-2", "El temor de un hombre sabio", "Patrick Rothfuss", 2011, 0},
        {"978-0-553-21311-9", "La naranja mecanica", "Anthony Burgess", 1962, 1},
        {"978-0-7432-7356-9", "American Gods", "Neil Gaiman", 2001, 0},
        {"978-0-307-74327-1", "El silencio de los corderos", "Thomas Harris", 1988, 1},
        {"978-0-553-26317-5", "El perfume", "Patrick Suskind", 1985, 0},
        {"978-0-14-243717-9", "Moby Dick", "Herman Melville", 1851, 1},
        {"978-0-307-38927-0", "El cuento de la criada", "Margaret Atwood", 1985, 1},
        {"978-0-00-752550-8", "El problema de los tres cuerpos", "Liu Cixin", 2008, 0},
        {"978-0-14-144167-2", "Grandes esperanzas", "Charles Dickens", 1861, 1},
        {"978-0-7432-7356-1", "El extranjero", "Albert Camus", 1942, 1},
        {"978-0-06-085052-4", "El retrato de Dorian Gray", "Oscar Wilde", 1890, 0},
        {"978-0-618-00221-0", "La historia interminable", "Michael Ende", 1979, 1},
        {"978-0-7432-7356-2", "Los pilares de la Tierra", "Ken Follett", 1989, 1},
        {"978-0-7432-7356-3", "El medico", "Noah Gordon", 1986, 0},
        {"978-0-375-72463-7", "La ladrona de libros", "Markus Zusak", 2005, 1},
        {"978-0-06-231500-7", "Mil soles esplendidos", "Khaled Hosseini", 2007, 0},
        {"978-0-385-35139-2", "La chica del tren", "Paula Hawkins", 2015, 1}
    };
	
	Acervo temp = {sizeof(libros)/sizeof(Libro),&libros[0]};
    return temp;
}

int compararTitulo(void *a,void *b)
{
	return strcmp( ((Libro*)a)->titulo , ((Libro*)b)->titulo );
}

void imprimirLibroLinea(void *vlibro)
{
	imprimirLibro(vlibro);
	printf("\n");
}

//FOLDING
static int foldingCadena(char *cadena)
{
	int key = 0, sector = 1, sumatoria = 0;
	for(int i = 0; cadena[i] != '\0'; i++)
	{
		sumatoria += cadena[i];
		if(i != 0 && (i + 1) % 3 == 0)
		{
			key += sector * sumatoria;
			sumatoria = 0;
			sector++;
		}
	}
	key += sector * sumatoria;
	return key;
}

int foldingISBN(void *data)      { return foldingCadena(((Libro*)data)->isbn); }
int foldingAutor(void *data)     { return foldingCadena(((Libro*)data)->autor); }
int foldingFecha(void *data)     { return ((Libro*)data)->fecha; }
int foldingIniTitulo(void *data) { return toupper((unsigned char)((Libro*)data)->titulo[0]); }
int foldingIniAutor(void *data)  { return toupper((unsigned char)((Libro*)data)->autor[0]); }

//COMPARADORES HASH
int compararISBN(void *a, void *b)      { return strcmp(((Libro*)a)->isbn, ((Libro*)b)->isbn); }
int compararAutor(void *a, void *b)     { return strcmp(((Libro*)a)->autor, ((Libro*)b)->autor); }
int compararFecha(void *a, void *b)     { return ((Libro*)a)->fecha - ((Libro*)b)->fecha; }
int compararIniTitulo(void *a, void *b) { return toupper((unsigned char)((Libro*)a)->titulo[0]) - toupper((unsigned char)((Libro*)b)->titulo[0]); }
int compararIniAutor(void *a, void *b)  { return toupper((unsigned char)((Libro*)a)->autor[0]) - toupper((unsigned char)((Libro*)b)->autor[0]); }

//COMPARADORES ARBOL
int cmpArbolTitulo(void *a, void *b)
{
	int r = strcmp(((Libro*)a)->titulo, ((Libro*)b)->titulo);
	return (r != 0) ? r : strcmp(((Libro*)a)->isbn, ((Libro*)b)->isbn);
}

int cmpArbolFecha(void *a, void *b)
{
	int r = ((Libro*)a)->fecha - ((Libro*)b)->fecha;
	return (r != 0) ? r : cmpArbolTitulo(a, b);
}

int cmpArbolAutor(void *a, void *b)
{
	int r = strcmp(((Libro*)a)->autor, ((Libro*)b)->autor);
	return (r != 0) ? r : cmpArbolTitulo(a, b);
}

//FUNCIONES PARA EL ARBOL
void recolectar(HashQTable *t, Libro *buscado, Arbol *arbol)
{
	int key = t->folding(buscado);
	int idx = fn_hashQ(*t, key);
	int k = 0, pos = idx;

	while (t->table[pos] != NULL)
	{
		void *elem = t->table[pos];
		if (elem != t && t->comparar(elem, buscado) == 0)
			insertarArbolO(arbol, elem);
		k++;
		pos = fn_rehashQ(*t, idx, k);
	}
}

void mostrarResultados(Arbol *arbol)
{
	if (arbol->cant == 0)
	{
		printf("\nNo se encontraron libros\n");
		return;
	}

	printf("\n--- RESULTADOS (%zu) ---\n", arbol->cant);
	imprimirOrden(*arbol, imprimirLibroLinea, ORDEN);

	//liberar nodos del arbol
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol->raiz, *ultimo = NULL;
	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);
			if (padre->dch != NULL && ultimo != padre->dch)
				actual = padre->dch;
			else
			{
				ultimo = pop(&pila);
				free(ultimo);
			}
		}
	}
	arbol->raiz = NULL;
	arbol->cant = 0;
}
