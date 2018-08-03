/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicCgiShowRequestPasswordResetForm.c,v $
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

   if (mlCgiInitialize (&ambiente))
      exit (ML_CGI_OK);

   mlCgiBeginHttpHeader ("text/html");
   mlCgiGetFormStringNoNewLines ("dicLanguage", dicLanguageString, DIC_LANGUAGE_MAX_LENGTH);
   dicLanguage = DicGetLanguageIndex (dicLanguageString);
   mlCgiEndHttpHeader ();

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
   printf ("    <br><br><br><br>\n");                                                                                           
   printf ("    <table align='center' bgcolor='%X'>\n", DIC_CENTRAL_FRAME_COLOR);                                                                    
   printf ("      <form action='dicRequestRegistration.cgi' method='post'>\n");                                            
   printf ("        <input type='hidden' name='dicLanguage' value='dicPortuguese'>\n");                                         
   printf ("        <tr>\n");                                                                                                   
   printf ("          <td></td>\n");                                                                                            
   printf ("          <td><br></td>\n");                                                                                        
   printf ("          <td></td>\n");                                                                                            
   printf ("          <td></td>\n");                                                                                            
   printf ("          <td></td>\n");                                                                                            
   printf ("        </tr>\n");                                                                                                  
   printf ("        <tr>\n");                                                                                                   
   printf ("          <td></td>\n");                                                                                            
   printf ("          <td align='right'>%s:</td>\n",
           DicGetWebUserInterfaceMessage (dicUserNameMessage, dicLanguage));                                                                
   printf ("          <td></td>\n");
   printf ("          <td align='left'><input type='text' maxlength='%i' size='45' name='dicUserName'></td>\n", DIC_USERNAME_MAX_LENGTH);
   printf ("          <td></td>\n");
   printf ("        </tr>\n");
   printf ("        <tr>\n");
   printf ("          <td></td>\n");
   printf ("          <td align='right'>%s:</td>\n",
           DicGetWebUserInterfaceMessage (dicEmailMessage, dicLanguage));
   printf ("          <td></td>\n");
   printf ("          <td align='left'><input type='text' maxlength='%i' size='45' name='dicEmail'></td>\n", DIC_EMAIL_MAX_LENGTH);
   printf ("          <td></td>\n");
   printf ("        </tr>\n");
   printf ("        <tr>\n");
   printf ("          <td></td>\n");
   printf ("          <td><br><br><br></td>\n");
   printf ("          <td></td>\n");
   printf ("          <td align='center'><input type='submit' value='%s'></td>\n",
           DicGetWebUserInterfaceMessage (dicSendButtonMessage, dicLanguage));
   printf ("          <td></td>\n");
   printf ("        </tr>\n");
   printf ("      </form>\n");
   printf ("    </table>\n");
   printf ("    <br>\n");
   printf ("    <table align='center' style='width:350px'>\n");
   printf ("      <tr>\n");
   printf ("        <td align='left'><a href='dicMain.cgi?dicLanguage=%s'>%s</a></td>\n",
           dicLanguageString, DicGetWebUserInterfaceMessage (dicHomeMessage, dicLanguage));
   printf ("        <td align='right'><a href='dicShowLicense.cgi?dicLanguage=%s'>%s</a></td>\n",
           dicLanguageString, DicGetWebUserInterfaceMessage (dicTermsOfUseMessage, dicLanguage));
   printf ("      </tr>\n");
   printf ("      <tr>\n");
   if (dicLanguage == dicEnglish)
   {
      printf ("          <td align='left'><a href='dicShowRequestPasswordResetForm.cgi?dicLanguage=dicPortuguese'>%s</a></td>\n",
              DicGetWebUserInterfaceMessage (dicPortugueseMessage, dicLanguage));
   }
   else if (dicLanguage == dicPortuguese)
   {
      printf ("          <td align='left'><a href='dicShowRequestPasswordResetForm.cgi?dicLanguage=dicEnglish'>%s</a></td>\n",
              DicGetWebUserInterfaceMessage (dicEnglishMessage, dicLanguage));
   }
   printf ("        <td align='right'><a href='dicShowWebHelp.cgi?dicLanguage=%s'>%s</a></td>\n",
           dicLanguageString, DicGetWebUserInterfaceMessage (dicHelpMessage, dicLanguage));
   printf ("      </tr>\n");
   printf ("    </table>\n");
   printf ("  </center>\n");
   printf ("</body>\n");
   printf ("</html>\n");

   mlCgiFreeResources ();

   return dicOk;
}

/*$RCSfile: dicCgiShowRequestPasswordResetForm.c,v $*/
