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
	dicUserDataType *dicUserData;
	dicUserDataType *dicCurrentUser;
	dicLanguageType dicLanguage = dicEnglish;
	dicErrorType dicReturnCode;

	char *dicArgumentValue;
	char dicShortOption;
	int dicLongOptionIndex;

	char *dicShortOptions = "hCNaitjnqQvdUluprmecgsS";

	struct option dicLongOptions [] =
	{
		{"help",       optional_argument, NULL, 'h'},
		{"Configure",  optional_argument, NULL, 'C'},
		{"Ncurses",    optional_argument, NULL, 'N'},  /*initial configure*/
		{"add",        optional_argument, NULL, 'a'},
		{"invite",     optional_argument, NULL, 'i'},
		{"accept",     optional_argument, NULL, 't'},
		{"reject",     optional_argument, NULL, 'j'},
		{"new",        optional_argument, NULL, 'n'},
		{"request",    optional_argument, NULL, 'q'},
		{"Request",    optional_argument, NULL, 'Q'},
		{"approve",    optional_argument, NULL, 'v'},
		{"disapprove", optional_argument, NULL, 'd'},
		{"Unlocking",  optional_argument, NULL, 'U'},
		{"lock",       optional_argument, NULL, 'l'},
		{"unlock",     optional_argument, NULL, 'u'},
		{"password",   optional_argument, NULL, 'p'},
		{"reset",      optional_argument, NULL, 'r'},
		{"modify",     optional_argument, NULL, 'm'},
		{"edit",       optional_argument, NULL, 'e'},
		{"confirm",    optional_argument, NULL, 'c'},
		{"group",      optional_argument, NULL, 'g'},
		{"show",       optional_argument, NULL, 's'},
		{"Search",     optional_argument, NULL, 'S'}
	};

	char *dicArgumentsNames[] = 
	{
		"language",
		"user",
		"nickname",
		"username",
		"confirm-username",
		"email",
		"confirm-email",
		"profile"
	};

	dicUserData = malloc (sizeof (dicUserDataType));
	dicCurrentUser = malloc (sizeof (dicUserDataType));

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
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}
				dicShowCliHelp (dicLanguage);
				break;
				
			case 'C':  /*initial configure*/
			
				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicUsernameArgument:
							strcpy (dicUserData->username, dicArgumentValue);
							break;

						case dicUsernameConfirmationArgument:
							strcpy (dicUserData->usernameConfirmation, dicArgumentValue);
							break;
						
						case dicEmailArgument:
							strcpy (dicUserData->email, dicArgumentValue);
							break;

						case dicEmailConfirmationArgument:
							strcpy (dicUserData->emailConfirmation, dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}
				if ((dicUserData->username[0] != DIC_EOS)
				 && (dicUserData->usernameConfirmation[0] != DIC_EOS)
				 && (dicUserData->email[0] != DIC_EOS)
				 && (dicUserData->emailConfirmation[0] ! DIC_EOS))
				{
					if (getuid () == DIC_ADMINISTRATOR_USER_IDENTIFIER)
					{
						dicUserData->password = getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage));
						dicUserData->passwordConfirmation = getpass (DicGetCliUserInterfaceMessage (dicPasswordConfirmationMessage, dicLanguage));
						
						dicUserData->userIdentifier = 0;
						dicUserData->profile = 0;
						dicUserData->nickname = ""; 
						dicUserData->next = NULL;
						dicUserData->previous = NULL;

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
						printf ("%s\n", DicGetCliErrorMessage (dicHaveNotPermission, dicLanguage));
						printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
						exit (dicHaveNotPermission);
					}
				}
				else
				{
					printf ("%s\n", DicGetCliErrorMessage (dicHasRequiredArguments, dicLanguage));
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
							strcpy (dicUserData->nickname, dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}
				DicRunNcursesInterface (dicLanguage, dicUserData->nickname);
				break;

			case 'a':

				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicCurrentUserArgument:
							strcpy (dicCurrentUser->nickname, dicArgumentValue);
							break;

						case dicUsernameArgument:
							strcpy (dicUserData->username, dicArgumentValue);
							break;

						case dicUsernameConfirmationArgument:
							strcpy (dicUserData->usernameConfirmation, dicArgumentValue);
							break;
						
						case dicEmailArgument:
							strcpy (dicUserData->email, dicArgumentValue);
							break;

						case dicEmailConfirmationArgument:
							strcpy (dicUserData->emailConfirmation, dicArgumentValue);
							break;

						case dicProfileArgument:
							strcpy (dicUserData->profile, dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}

				if (
						dicCurrentUser->nickname[0]          !=  DIC_EOS
					&&	dicUserData->username[0]             !=  DIC_EOS
					&& dicUserData->usernameConfirmation[0] !=  DIC_EOS
					&& dicUserData->email[0]                !=  DIC_EOS
					&& dicUserData->emailConfirmation[0]    !=  DIC_EOS
					&& dicUserData->profile[0]              !=  DIC_EOS
				)
				{
					dicCurrentUser->password = getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage));
					dicReturnCode = DicAuthenticateUser (dicCurrentUser);
					if (dicReturnCode != dicOk)
					{
						printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
						exit (dicReturnCode);
					}
					printf ("%s\n", DicGetCliUserInterfaceMessage (dicCorrectAuthenticateMessage, dicLanguage));

					if ((dicCurrentUser->profile % 2) = 1) /*if user is administrator*/
					{
						dicReturnCode = DicAddUser (dicUserData);
						if (dicReturnCode == dicOk)
						{
							printf ("%s\n", DicGetCliUserInterfaceMessage (dicCorrectAddUserMessage, dicLanguage));
							return dicOk;
						}
						else
						{
							printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
							exit (dicReturnCode);
						}

					}
					else
					{
						printf ("%s\n", DicGetCliErrorMessage (dicHaveNotPermission, dicLanguage));
						printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
						exit (dicHaveNotPermission);
					}
				}
				else
				{
					printf ("%s\n", DicGetCliErrorMessage (dicHasRequiredArguments, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHasRequiredArguments);
				}
				break;

			case 'generic':

				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicCurrentUserArgument:
							strcpy (dicCurrentUser->nickname, dicArgumentValue);
							break;

						case dicUsernameArgument:
							strcpy (dicUserData->username, dicArgumentValue);
							break;

						case dicUsernameConfirmationArgument:
							strcpy (dicUserData->usernameConfirmation, dicArgumentValue);
							break;
						
						case dicEmailArgument:
							strcpy (dicUserData->email, dicArgumentValue);
							break;

						case dicEmailConfirmationArgument:
							strcpy (dicUserData->emailConfirmation, dicArgumentValue);
							break;

						case dicNicknameArgument:
							strcpy (dicUserData->nickname, dicArgumentValue);
							break;

						case dicProfileArgument:
							strcpy (dicUserData->profile, dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}

				if (
						dicCurrentUser->nickname[0]          ==  DIC_EOS
					||	dicUserData->username[0]             ==  DIC_EOS
					|| dicUserData->usernameConfirmation[0] ==  DIC_EOS
					|| dicUserData->email[0]                ==  DIC_EOS
					|| dicUserData->emailConfirmation[0]    ==  DIC_EOS
					|| dicUserData->profile[0]              ==  DIC_EOS
				)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicHasRequiredArguments, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHasRequiredArguments);
				}
				dicCurrentUser->password = getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage));
				dicReturnCode = DicAuthenticateUser (dicCurrentUser);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}
				printf ("%s\n", DicGetCliUserInterfaceMessage (dicCorrectAuthenticateMessage, dicLanguage));

				if ((dicCurrentUser->profile % 2) = 1) /*if user is administrator*/
				{
					dicReturnCode = DicAddUser (dicUserData);
					if (dicReturnCode == dicOk)
					{
						printf ("%s\n", DicGetCliUserInterfaceMessage (dicCorrectAddUserMessage, dicLanguage));
						return dicOk;
					}
					else
					{
						printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
						exit (dicReturnCode);
					}

				}
				else if ((dicCurrentUser->profile % 2) == 2 || (dicCurrentUser->profile % 2) == 3) /*if user is teacher*/
				{

				}
				else /*user is student*/
				{
					
				}

				/*have not permission*/
				printf ("%s\n", DicGetCliErrorMessage (dicHaveNotPermission, dicLanguage));
				printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
				exit (dicHaveNotPermission);

				break;

			default:
				printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidOption, dicLanguage), argv [optind]);
				printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
				exit (dicInvalidOption);

		}
	}
}

/*$RCSfile$*/
