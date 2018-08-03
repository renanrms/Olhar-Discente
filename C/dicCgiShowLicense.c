/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicCgiShowLicense.c,v $
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
   char licenseFileLine [DIC_HTMLLINE_MAX_LENGTH + 1];
   FILE *licenseFile = NULL;

   if (mlCgiInitialize (&ambiente))
      exit (ML_CGI_OK);

   mlCgiBeginHttpHeader ("text/html");
   mlCgiGetFormStringNoNewLines ("dicLanguage", dicLanguageString, DIC_LANGUAGE_MAX_LENGTH);
   dicLanguage = DicGetLanguageIndex (dicLanguageString);
   mlCgiEndHttpHeader ();

   if (dicLanguage == dicPortuguese)
      licenseFile = fopen ("/users/renan.passos/public/html/DIC/HTML/dicLicense_pt-br.html", "r");
   else 
      licenseFile = fopen ("/users/renan.passos/public/html/DIC/HTML/dicLicense_en-us.html", "r");

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
   printf ("  </center>\n");
   printf ("  <br><br><br><br>\n");                                                                                           

   if (licenseFile == NULL)
   {
      printf ("  %s\n", DicGetWebErrorMessage (dicLicenseNotFound, dicLanguage));
   }
   else
   {
      while (fgets (licenseFileLine, DIC_HTMLLINE_MAX_LENGTH, licenseFile) != DIC_EOS)
      {
         printf ("  %s", licenseFileLine);
      }
   }

   printf ("  <table align='center' style='width:350px'>\n");
   printf ("    <tr>\n");                                                                                                   
   printf ("      <td align='left'><a href='dicMain.cgi?dicLanguage=%s'>%s</a></td>\n",
           dicLanguageString, DicGetWebUserInterfaceMessage (dicHomeMessage, dicLanguage));
   printf ("      <td align='right'><a href='dicShowWebHelp.cgi?dicLanguage=%s'>%s</a></td>\n",
           dicLanguageString, DicGetWebUserInterfaceMessage (dicHelpMessage, dicLanguage));
   printf ("    </tr>\n");
   printf ("    <tr>\n");
   if (dicLanguage == dicEnglish)
   {
      printf ("      <td align='left'><a href='dicShowLicense.cgi?dicLanguage=dicPortuguese'>%s</a></td>\n",
              DicGetWebUserInterfaceMessage (dicPortugueseMessage, dicLanguage));
   }
   else if (dicLanguage == dicPortuguese)
   {
      printf ("      <td align='left'><a href='dicShowLicense.cgi?dicLanguage=dicEnglish'>%s</a></td>\n",
              DicGetWebUserInterfaceMessage (dicEnglishMessage, dicLanguage));
   }
   printf ("    </tr>\n");
   printf ("  </table>\n");
   printf ("</body>\n");
   printf ("</html>\n");

   mlCgiFreeResources ();

   return dicOk;
}

/*$RCSfile: dicCgiShowLicense.c,v $*/
