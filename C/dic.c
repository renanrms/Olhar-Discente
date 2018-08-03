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

#include <getopt.h>

#include "dicTypes.h"

int
main (int argc, char **argv)
{
	dicLanguageType dicLanguage = dicEnglish;
	char dicNickname [DIC_NICKNAME_MAX_LENGTH + 1] = "";
	char dicUsername [DIC_FULLNAME_MAX_LENGTH + 1] = "";
	char dicUsernameConfirmation [DIC_FULLNAME_MAX_LENGTH + 1] = "";
	char dicEmail [DIC_EMAIL_MAX_LENGTH + 1] = "";
	char dicEmailConfirmation [DIC_EMAIL_MAX_LENGTH + 1] = "";

	char *dicArgumentValue;
	char dicShortOption;
	int dicLongOptionIndex;

	char *dicShortOptions = "hCN";

	struct option dicLongOptions [] =
	{
		{"help",      optional_argument, NULL, 'h'},
		{"Configure", optional_argument, NULL, 'C'},
		{"Ncurses",   optional_argument, NULL, 'N'}
	};

	char *dicArgumentsNames[] = 
	{
		"language",
		"nickname",
		"username",
		"confirm-username",
		"email",
		"confirm-email"
	};

	while ((dicShotrOption = getopt_long (argc, argv, dicShortOptions, dicLongOptions, &dicLongOptionIndex)) != -1) /*Is -1 when argument list is exhausted*/
	{
		switch (dicShotrOption)
		{
			case 'h':

				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue)) /*returns a index of dicArgumentsNames[]*/
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
						
						default:
							printf ("%s: %s", DicGetCliUserInterfaceMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}
				dicShowCliHelp (dicLanguage);
				break;
				
			case 'C':
			
				if (optind == argc)
				{
					dicShowCliHelp (dicEnglish);
				}
				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue)) /*returns a index of dicArgumentsNames[]*/
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;
						
						default:
							printf ("%s: %s", DicGetCliUserInterfaceMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}
				break;

			case 'N':
			
				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue)) /*returns a index of dicArgumentsNames[]*/
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
						
						case dicNicknameArgument:
							dicNickname = dicArgumentValue;

						default:
							printf ("%s: %s", DicGetCliUserInterfaceMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}
				/*Call of RunNcursesInterface (dicNickname, dicLanguage)*/
				break;

			default:
				printf ("%s: %s", DicGetCliUserInterfaceMessage (dicInvalidOption, dicLanguage), argv [optind -1]);
				exit (dicInvalidOption);

		}
	}
}

/*$RCSfile$*/
