/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicCgiShowWebHelp.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "dicTypes.h"
#include "dicConst.h"
#include "dicErrors.h"
#include "dicFunctions.h"
#include "dicUserInterface.h"
#include "Libraries/mlcgi.h"

int
main (int argc, char **argv)
{
   environmentType ambiente;
   dicLanguageType dicLanguage = dicEnglish;
   char dicLanguageString [DIC_LANGUAGE_MAX_LENGTH + 1];
   char helpFileLine [DIC_HTMLLINE_MAX_LENGTH + 1];
   FILE *helpFile = NULL;

   if (mlCgiInitialize (&ambiente))
      exit (ML_CGI_OK);

   mlCgiBeginHttpHeader ("text/html");
   mlCgiGetFormStringNoNewLines ("dicLanguage", dicLanguageString, DIC_LANGUAGE_MAX_LENGTH);
   dicLanguage = DicGetLanguageIndex (dicLanguageString);
   mlCgiEndHttpHeader ();

   if (dicLanguage == dicPortuguese)
      helpFile = fopen ("/users/renan.passos/public/html/DIC/HTML/dicWebHelp_pt-br.html", "r");
   else 
      helpFile = fopen ("/users/renan.passos/public/html/DIC/HTML/dicWebHelp_en-us.html", "r");

   printf ("<html>\n");
   printf ("<head>\n");
   printf ("  <title>\n");
   printf ("    Olhar Discente\n");
   printf ("  </title>\n");        
   printf ("</head>\n");           
   printf ("<body bgcolor='%X'>\n", DIC_BACKGROUND_COLOR);
   printf ("<body>\n");                 
   printf ("  <center>\n");             
   printf ("    <hr>\n");               
   printf ("    <h1>Olhar Discente</h1>\n");
   printf ("    <hr>\n");
   printf ("    <a href='mailto:renanpassos@poli.ufrj.br?subject=[OLHAR%%20DISCENTE%%20-%%20%s]'>Renan Passos</a>\n",
           DicGetWebUserInterfaceMessage (dicContactUsMessage, dicLanguage));
   printf ("    </center>\n");
   printf ("    <br><br><br><br>\n");                                                                                           

   if (helpFile == NULL)
   {
      printf ("  %s\n", DicGetWebErrorMessage (dicHelpNotFound, dicLanguage));
   }
   else
   {
      while (fgets (helpFileLine, DIC_HTMLLINE_MAX_LENGTH, helpFile) != DIC_EOS)
      {
         printf ("  %s", helpFileLine);
      }
   }

   printf ("    <table align='center' style='width:350px'>\n");
   printf ("    <h5>");
   printf ("      <tr>\n");                                                                                                   
   printf ("        <td align='left'><a href='dicMain.cgi?dicLanguage=%s'>%s</a></td>\n",
           dicLanguageString, DicGetWebUserInterfaceMessage (dicHomeMessage, dicLanguage));
   printf ("        <td align='right'><a href='dicShowLicense.cgi?dicLanguage=%s'>%s</a></td>\n",
           dicLanguageString, DicGetWebUserInterfaceMessage (dicTermsOfUseMessage, dicLanguage));
   printf ("      </tr>\n");
   printf ("      <tr>\n");
   if (dicLanguage == dicEnglish)
   {
      printf ("        <td align='left'><a href='dicShowWebHelp.cgi?dicLanguage=dicPortuguese'>%s</a></td>\n",
              DicGetWebUserInterfaceMessage (dicPortugueseMessage, dicLanguage));
   }
   else if (dicLanguage == dicPortuguese)
   {
      printf ("        <td align='left'><a href='dicShowWebHelp.cgi?dicLanguage=dicEnglish'>%s</a></td>\n",
              DicGetWebUserInterfaceMessage (dicEnglishMessage, dicLanguage));
   }
   printf ("      </tr>\n");
   printf ("    </h5>");
   printf ("    </table>\n");
   printf ("  <center>\n");             
   printf ("</body>\n");
   printf ("</html>\n");

   mlCgiFreeResources ();

   return dicOk;
}

/*$RCSfile: dicCgiShowWebHelp.c,v $*/
