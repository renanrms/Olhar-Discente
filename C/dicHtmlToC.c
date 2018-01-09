/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author$
 * $Date$
 * $Log$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMERO_ARGUMENTOS                 2
#define TAMANHO_MAX_NOME_ARQUIVO          50
#define EOS                               '\0'
#define OK                                0
#define NUMERO_ARGUMENTOS_INVALIDO        1
#define ERRO_ABRINDO_ARQUIVO              2

int main (int argc, char **argv)
{
   FILE *arquivoTextHtml = NULL;
   FILE *arquivoTextC = NULL;
   char nomeArquivoC [TAMANHO_MAX_NOME_ARQUIVO];
   char nomeArquivoHtml [TAMANHO_MAX_NOME_ARQUIVO];
   char caracter = EOS;
   char caracterAnterior = EOS;

   if (argc != NUMERO_ARGUMENTOS)
   {
      printf ("Uso: %s <nome util do arquivo>\n", argv [0]);
      exit (NUMERO_ARGUMENTOS_INVALIDO);
   }

   strcpy (nomeArquivoHtml, argv [1]);
   strcpy (nomeArquivoC, argv [1]);

   strcat (nomeArquivoHtml, ".html");
   strcat (nomeArquivoC, ".c");

   arquivoTextHtml = fopen (nomeArquivoHtml, "r");
   arquivoTextC = fopen (nomeArquivoC, "w");

   if ((arquivoTextHtml == NULL) || (arquivoTextC == NULL))
   {
      printf ("Erro abrindo arquivo\n");
      exit (ERRO_ABRINDO_ARQUIVO);
   }

   system ("clear");

   printf ("   printf (\"");
   fprintf (arquivoTextC, "   printf (\"");

   while (!feof(arquivoTextHtml))
   {
       caracter = (char) fgetc (arquivoTextHtml);

       if (caracter == '\n')
       {
          if (caracterAnterior != '\n')
          {
             printf ("\\n\");\n");
             fprintf (arquivoTextC, "\\n\");\n");
          }
       }
       else if (caracter != EOS)
       {
          if (caracterAnterior == '\n')
          {
             printf ("   printf (\"");
             fprintf (arquivoTextC, "   printf (\"");
          }
          if (caracter == '\"')
          {
             printf ("\\");
             fprintf (arquivoTextC, "\\");
          }
          else if (caracter == '%')
          {
             printf ("%%");
             fprintf (arquivoTextC, "%%");
          }
          printf ("%c", caracter);
          fprintf (arquivoTextC, "%c", caracter);
       }
       
       caracterAnterior = caracter;
   }

   printf ("\n");
   fprintf (arquivoTextC, "\n");

   fclose (arquivoTextHtml);
   fclose (arquivoTextC);

   return OK;
}

/*$RCSfile$*/
