/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicShowCliHelp.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "dicTypes.h"
#include "dicShowCliHelp.h"
#include "dicFunctions.h"
#include "dicConst.h"
#include "dicConfig.h"

void
DicShowCliHelp (dicLanguageType dicLanguage)
{
	FILE *dicCliHelpFile;
	char dicTextLine [DIC_TEXT_PARAGRAPH_MAX_LENGTH + 1];

	if (dicLanguage == dicEnglish)
	{
		dicCliHelpFile = fopen ("./dicCliHelp_en-us.txt", "r");
		if (dicCliHelpFile == NULL)
			printf ("Help file not found in this language. Please enter other language.");
	}
	else
	{
		dicCliHelpFile = fopen ("./dicCliHelp_pt-br.txt", "r");
		if (dicCliHelpFile == NULL)
			printf ("Arquivo de ajuda não encontrado nessa língua. Tente outro idioma.");
	}

	while (fgets (dicTextLine, DIC_TEXT_PARAGRAPH_MAX_LENGTH + 1, dicCliHelpFile) != NULL)
		printf ("%s", dicTextLine);
}

/*$RCSfile: dicShowCliHelp.c,v $*/
