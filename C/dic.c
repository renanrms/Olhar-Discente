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
#include "dicConst.h"

int
main (int argc, char **argv)
{
	dicLanguageType dicLanguage = dicEnglish;
	char dicNickname [DIC_NICKNAME_MAX_LENGTH + 1] = "";
	char dicUsername [DIC_USERNAME_MAX_LENGTH + 1] = "";
	char dicUsernameConfirmation [DIC_USERNAME_MAX_LENGTH + 1] = "";
	char dicEmail [DIC_EMAIL_MAX_LENGTH + 1] = "";
	char dicEmailConfirmation [DIC_EMAIL_MAX_LENGTH + 1] = "";

	dicErrorType dicReturnCode;

	dicUserDataType *dicUserData = malloc (sizeof (dicUserDataType));

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

				while (optind < argc) /*optind (extern variable of getopt_long) is a pointer to next element of argv*/
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue)) /*returns a index of dicArgumentsNames[] or -1*/
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliUserInterfaceMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}
				dicShowCliHelp (dicLanguage);
				break;
				
			case 'C':
			
				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicUsernameArgument:
							(*dicUserData).username = dicArgumentValue;
							break;

						case dicUsernameConfirmationArgument:
							(*dicUserData).usernameConfirmation = dicArgumentValue;
							break;
						
						case dicEmailArgument:
							(*dicUserData).email = dicArgumentValue;
							break;

						case dicEmailConfirmationArgument:
							(*dicUserData).emailConfirmation = dicArgumentValue;
							break;

						default:
							printf ("%s: %s\n", DicGetCliUserInterfaceMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}
				if (((*dicUserData).username[0] != DIC_EOS) && ((*dicUserData).usernameConfirmation[0] != DIC_EOS) && ((*dicUserData).email[0] != DIC_EOS) && ((*dicUserData).emailConfirmation[0] ! DIC_EOS)
				{
					if (getuid () == DIC_ADMINISTRATOR_USER_IDENTIFIER)
					{
						(*dicUserData).password = getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage));
						(*dicUserData).passwordConfirmation = getpass (DicGetCliUserInterfaceMessage (dicPasswordConfirmationMessage, dicLanguage));
						
						(*dicUserData).userIdentifier = 0;
						(*dicUserData).perfil = 0;
						(*dicUserData).nickname = ""; 
						(*dicUserData).next = NULL;
						(*dicUserData).previous = NULL;

						dicReturnCode = DicAddUser (dicUserData);

						if (returnCode == dicOk)
						{
							printf ("%s\n", dicCreatedUser);
						}
						else
						{
							printf ("%s\n", dicReturnCode);
							exit (dicReturnCode);
						}
					}
					else
					{
						printf ("%s\n", DicGetCliUserInterfaceMessage (dicHaveNotPermission, dicLanguage));
						printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
						exit (dicHaveNotPermission);
					}
				}
				else
				{
					printf ("%s\n", DicGetCliUserInterfaceMessage (dicHasRequiredArguments, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHasRequiredArguments);
				}
				break;

			case 'N':
			
				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicNicknameArgument:
							dicNickname = dicArgumentValue;
							break;

						default:
							printf ("%s: %s\n", DicGetCliUserInterfaceMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}
				DicRunNcursesInterface (dicLanguage, dicNickname);
				break;

			default:
				printf ("%s: %s\n", DicGetCliUserInterfaceMessage (dicInvalidOption, dicLanguage), argv [optind]);
				printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
				exit (dicInvalidOption);

		}
	}
}

/*$RCSfile$*/
