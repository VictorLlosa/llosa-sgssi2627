#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int iMasFrec(int *lista);
void imprimirMensaje(const char *cifrado, const char *mapeo, int longitud);

int main(int argc, char *argv[]) {
  // Pre: el mensajeCifrado está en castellano y sin tildes ni ñ
  if (argc != 2) {
      printf("uso: frec \"mensaje cifrado\"\n");
      return 1;
  }

  const char charsMasFrec[26] = {'e','a','o','l','s','n','d','r','u','i','t','c','p','m','y','q','b','h','g','f','v','j','z','x','k','w'};

  char *mensajeCifrado = argv[1];
  int apariciones[26] = {0};
  int longitud = strlen(mensajeCifrado);

  // El mensaje cifrado se queda SIEMPRE en mayúsculas
  for (int i = 0; i < longitud; i++) {
    mensajeCifrado[i] = toupper((unsigned char)mensajeCifrado[i]);
  }

  // Contar solo letras (evita salirse del array con espacios, signos, etc.)
  for (int i = 0; i < longitud; i++) {
    if (isalpha((unsigned char)mensajeCifrado[i])) {
      apariciones[mensajeCifrado[i] - 'A']++;
    }
  }

  // mapeo[letra cifrada] = letra descifrada en minúscula (0 = sin mapeo)
  char mapeo[26] = {0};

  for (int j = 0; j < 26; j++) {
    int indiceMasFrec = iMasFrec(apariciones);
    if (apariciones[indiceMasFrec] == 0) break; // ya no quedan letras
    mapeo[indiceMasFrec] = charsMasFrec[j];
    apariciones[indiceMasFrec] = 0;
  }

  char buffer[100];

  for (;;) {
      imprimirMensaje(mensajeCifrado, mapeo, longitud);

      printf("\nIntroduce la letra a cambiar (MAYUS = cifrada, minus = descifrada): ");
      if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;

      // Solo Enter -> salir
      if (buffer[0] == '\n') break;

      // Tiene que ser exactamente un carácter + '\n'
      if (strlen(buffer) != 2 || !isalpha((unsigned char)buffer[0])) {
          printf("Introduce una unica letra.\n");
          continue;
      }
      char este = buffer[0];

      printf("Introduce la letra nueva (minuscula): ");
      if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;

      if (buffer[0] == '\n') break;

      if (strlen(buffer) != 2 || !isalpha((unsigned char)buffer[0])) {
          printf("Introduce una unica letra.\n");
          continue;
      }
      char ese = tolower((unsigned char)buffer[0]);

      if (isupper((unsigned char)este)) {
          // Se ha elegido una letra cifrada: se le asigna la nueva letra
          mapeo[este - 'A'] = ese;
      } else {
          // Se ha elegido una letra ya descifrada: se sustituye en el mapeo.
          // Si 'ese' ya estaba en uso, se intercambian para no duplicar.
          for (int k = 0; k < 26; k++) {
              if (mapeo[k] == este) mapeo[k] = ese;
              else if (mapeo[k] == ese) mapeo[k] = este;
          }
      }
  }

  return 0;
}

// Imprime el mensaje: cifradas sin mapeo en MAYUS, descifradas en minus
void imprimirMensaje(const char *cifrado, const char *mapeo, int longitud) {
  for (int i = 0; i < longitud; i++) {
    if (isalpha((unsigned char)cifrado[i]) && mapeo[cifrado[i] - 'A']) {
      putchar(mapeo[cifrado[i] - 'A']);
    } else {
      putchar(cifrado[i]);
    }
  }
  putchar('\n');
}

int iMasFrec(int *lista) {
  int frec = 0;
  int indiceMasFrec = 0;

  for (int i = 0; i < 26; i++) {
    if (*lista > frec) {
      frec = *lista;
      indiceMasFrec = i;
    }
    lista++;
  }

  return indiceMasFrec;
}
