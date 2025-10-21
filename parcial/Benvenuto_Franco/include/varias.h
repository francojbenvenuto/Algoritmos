#ifndef VARIAS_H_INCLUDED
#define VARIAS_H_INCLUDED

#define TAM_MENU 32

void finAnormal(char *);
void pausa(char *);
char menu(const char m[][TAM_MENU], const char *tit);
char pedirOpcion(const char m[][TAM_MENU], const char * tit, const char * msj);

#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
#  define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#  define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif


#endif // VARIAS_H_INCLUDED
