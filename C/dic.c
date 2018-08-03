/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dic.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <pwd.h>

#include "dicAddUser.h"
#include "dicRequestRegistration.h"
#include "dicGetPendingRegistrationRequests.h"
#include "dicGetPendingRegistrationRequestsPerUser.h"
#include "dicAcceptInvite.h"
#include "dicRejectInvite.h"
#include "dicShowCliHelp.h"
#include "dicUserInterface.h"
#include "dicFunctions.h"
#include "dicErrors.h"
#include "dicTypes.h"
#include "dicConst.h"
#include "dicConfig.h"

int
main (int argc, char **argv)
{
	char dicProfileString [DIC_PROFILE_MAX_LENGTH];
	char dicFriendEmail [DIC_EMAIL_MAX_LENGTH];
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
		"profile",
		"friend-email"
	};

	dicUserData = malloc (sizeof (dicUserDataType));
	dicCurrentUser = malloc (sizeof (dicUserDataType));

	dicUserData->nickname[0]                = DIC_EOS;
	dicUserData->username[0]                = DIC_EOS;
	dicUserData->usernameConfirmation[0]    = DIC_EOS;
	dicUserData->email[0]                   = DIC_EOS;
	dicUserData->emailConfirmation[0]       = DIC_EOS;
	dicUserData->password[0]                = DIC_EOS;
	dicUserData->passwordConfirmation[0]    = DIC_EOS;

	dicCurrentUser->nickname[0]             = DIC_EOS;
	dicCurrentUser->username[0]             = DIC_EOS;
	dicCurrentUser->usernameConfirmation[0] = DIC_EOS;
	dicCurrentUser->email[0]                = DIC_EOS;
	dicCurrentUser->emailConfirmation[0]    = DIC_EOS;
	dicCurrentUser->password[0]             = DIC_EOS;
	dicCurrentUser->passwordConfirmation[0] = DIC_EOS;

	dicProfileString[0]                     = DIC_EOS;
	dicFriendEmail[0]                       = DIC_EOS;

	while ((dicShortOption = getopt_long (argc, argv, dicShortOptions, dicLongOptions, &dicLongOptionIndex)) != -1) /*Is -1 when argument list is exhausted*/
	{
		switch (dicShortOption)
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
				DicShowCliHelp (dicLanguage);
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
				 && (dicUserData->emailConfirmation[0] != DIC_EOS))
				{
					if (getuid () == DIC_ADMINISTRATOR_USER_IDENTIFIER)
					{
						strcpy (dicUserData->password, getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage)));
						strcpy (dicUserData->passwordConfirmation, getpass (DicGetCliUserInterfaceMessage (dicPasswordConfirmationMessage, dicLanguage)));
						
						dicUserData->userId = 0;
						dicUserData->profile = 0;
						dicUserData->nickname[0] = DIC_EOS; 
						dicUserData->next = NULL;
						dicUserData->previous = NULL;

						dicReturnCode = DicAddUser (dicUserData);

						if (dicReturnCode == dicOk)
						{
							printf ("%s\n", DicGetCliUserInterfaceMessage (dicSuccessMessage, dicLanguage));
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
				/*DicRunNcursesInterface (dicLanguage, dicUserData->nickname);*/
				break;

			case 'a':

				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicCurrentUserNicknameArgument:
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
							strcpy (dicProfileString, dicArgumentValue);
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
					&& dicUserData->username[0]             !=  DIC_EOS
					&& dicUserData->usernameConfirmation[0] !=  DIC_EOS
					&& dicUserData->email[0]                !=  DIC_EOS
					&& dicUserData->emailConfirmation[0]    !=  DIC_EOS
					&& dicProfileString[0]                  !=  DIC_EOS
				)
				{
					strcpy (dicCurrentUser->password, getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage)));
					dicReturnCode = DicAuthenticateUser (dicCurrentUser);
					if (dicReturnCode != dicOk)
					{
						printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
						exit (dicReturnCode);
					}
					printf ("%s\n", DicGetCliUserInterfaceMessage (dicCorrectAuthenticateMessage, dicLanguage));

					/*to obtain profile argument*/
					dicUserData->profile = DicGetUserProfileIndex (dicProfileString);
					if (dicUserData->profile == dicUserProfilesAmountMoreOne)
					{
						printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidProfile, dicLanguage), dicProfileString);
						printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
						exit (dicInvalidProfile);
					}


					if ((dicCurrentUser->profile % 2) == 1) /*if user is administrator*/
					{
						dicReturnCode = DicAddUser (dicUserData);
						if (dicReturnCode == dicOk)
						{
							printf ("%s\n", DicGetCliUserInterfaceMessage (dicSuccessMessage, dicLanguage));
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

			case 'i':

				while (optind < argc)
				{
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicCurrentUserNicknameArgument:
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
							strcpy (dicProfileString, dicArgumentValue);
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
					|| dicUserData->username[0]             ==  DIC_EOS
					|| dicUserData->usernameConfirmation[0] ==  DIC_EOS
					|| dicUserData->email[0]                ==  DIC_EOS
					|| dicUserData->emailConfirmation[0]    ==  DIC_EOS
					|| dicProfileString[0]                  ==  DIC_EOS
				)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicHasRequiredArguments, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHasRequiredArguments);
				}

				/*Authenticate current user*/
				strcpy (dicCurrentUser->password, getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage)));
				dicReturnCode = DicAuthenticateUser (dicCurrentUser);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}
				printf ("%s\n", DicGetCliUserInterfaceMessage (dicCorrectAuthenticateMessage, dicLanguage));

				/*to obtain profile argument*/
				dicUserData->profile = DicGetUserProfileIndex (dicProfileString);
				if (dicUserData->profile == dicUserProfilesAmountMoreOne)
				{
					printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidProfile, dicLanguage), dicProfileString);
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicInvalidProfile);
				}

				if ((dicCurrentUser->profile % 2) == 1) /*if user is administrator*/
				{
					/*invite user*/
					dicReturnCode = DicAddUser (dicUserData);
					if (dicReturnCode == dicOk)
					{
						printf ("%s\n", DicGetCliUserInterfaceMessage (dicSuccessMessage, dicLanguage));
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
					if ((dicUserData->profile % 2) == 1) /*invited user is administrator*/
					{
						/*have not permission*/
						printf ("%s\n", DicGetCliErrorMessage (dicHaveNotPermission, dicLanguage));
						printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
						exit (dicHaveNotPermission);
					}
					/*invite user*/
					dicReturnCode = DicAddUser (dicUserData);
					if (dicReturnCode == dicOk)
					{
						printf ("%s\n", DicGetCliUserInterfaceMessage (dicSuccessMessage, dicLanguage));
						return dicOk;
					}
					else
					{
						printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
						exit (dicReturnCode);
					}
				}
				else /*user is student*/
				{
					if (dicUserData->profile != 4) /*invited user is not only student*/
					{
						/*have not permission*/
						printf ("%s\n", DicGetCliErrorMessage (dicHaveNotPermission, dicLanguage));
						printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
						exit (dicHaveNotPermission);
					}
					/*invite user*/
					dicReturnCode = DicAddUser (dicUserData);
					if (dicReturnCode == dicOk)
					{
						printf ("%s\n", DicGetCliUserInterfaceMessage (dicSuccessMessage, dicLanguage));
						return dicOk;
					}
					else
					{
						printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
						exit (dicReturnCode);
					}
				}
				break;

			case 't':

				while (optind < argc)
				{
					/*possible suboptions for this option*/
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicCurrentUserNicknameArgument:
							strcpy (dicCurrentUser->nickname, dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}

				/*required suboptions*/
				if (dicCurrentUser->nickname[0] == DIC_EOS)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicHasRequiredArguments, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHasRequiredArguments);
				}

				/*Authenticate current user*/
				strcpy (dicCurrentUser->password, getpass (DicGetCliUserInterfaceMessage (dicTempPasswordMessage, dicLanguage)));
				
				strcpy (dicUserData->password, getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage)));
				strcpy (dicUserData->passwordConfirmation, getpass (DicGetCliUserInterfaceMessage (dicPasswordConfirmationMessage, dicLanguage)));

				dicReturnCode = DicAcceptInvite (dicCurrentUser->password, dicUserData);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}
				printf ("%s\n", DicGetCliUserInterfaceMessage (dicSuccessMessage, dicLanguage));

				break;

			case 'j':

				while (optind < argc)
				{
					/*possible suboptions for this option*/
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicCurrentUserNicknameArgument:
							strcpy (dicCurrentUser->nickname, dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}

				/*required suboptions*/
				if (dicCurrentUser->nickname[0] == DIC_EOS)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicHasRequiredArguments, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHasRequiredArguments);
				}

				/*Authenticate current user*/
				strcpy (dicCurrentUser->password, getpass (DicGetCliUserInterfaceMessage (dicTempPasswordMessage, dicLanguage)));
			
				dicReturnCode = DicRejectInvite (dicCurrentUser->password, dicCurrentUser->nickname);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}
				printf ("%s\n", DicGetCliUserInterfaceMessage (dicSuccessMessage, dicLanguage));

				break;

			case 'n':

				while (optind < argc)
				{
					/*possible suboptions for this option*/
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

						case dicProfileArgument:
							strcpy (dicProfileString, dicArgumentValue);
							break;

						case dicFriendEmailArgument:
							strcpy (dicFriendEmail, dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}

				/*required suboptions*/
				if (
					   dicUserData->username[0]             ==  DIC_EOS
					|| dicUserData->usernameConfirmation[0] ==  DIC_EOS
					|| dicUserData->email[0]                ==  DIC_EOS
					|| dicUserData->emailConfirmation[0]    ==  DIC_EOS
					|| dicProfileString[0]                  ==  DIC_EOS
					|| dicFriendEmail[0]                    ==  DIC_EOS
				)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicHasRequiredArguments, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHasRequiredArguments);
				}

				/*to obtain profile argument*/
				dicUserData->profile = DicGetUserProfileIndex (dicProfileString);
				if (dicUserData->profile == dicUserProfilesAmountMoreOne)
				{
					printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidProfile, dicLanguage), dicProfileString);
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicInvalidProfile);
				}

				strcpy (dicUserData->password, getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage)));
				strcpy (dicUserData->password, getpass (DicGetCliUserInterfaceMessage (dicPasswordConfirmationMessage, dicLanguage)));

				dicReturnCode = DicRequestRegistration (dicFriendEmail, dicUserData);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}
				printf ("%s\n", DicGetCliUserInterfaceMessage (dicSuccessMessage, dicLanguage));

				break;

			case 'q':

				while (optind < argc)
				{
					/*possible suboptions for this option*/
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicCurrentUserNicknameArgument:
							strcpy (dicCurrentUser->nickname, dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}

				/*required suboptions*/
				if (dicCurrentUser->nickname[0] == DIC_EOS)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicHasRequiredArguments, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHasRequiredArguments);
				}

				/*Authenticate current user*/
				strcpy (dicCurrentUser->password, getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage)));
				dicReturnCode = DicAuthenticateUser (dicCurrentUser);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}
				printf ("%s\n", DicGetCliUserInterfaceMessage (dicCorrectAuthenticateMessage, dicLanguage));

				dicReturnCode = DicGetPendingRegistrationRequestsPerUser (dicCurrentUser->nickname, &dicUserData);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}

				while (dicUserData != NULL)
				{
					printf ("%s\t%s\t%s\t%s\n", DicGetUserProfileString (dicUserData->profile, dicLanguage),
					        dicUserData->nickname,
					        dicUserData->username,
					        dicUserData->email);
					dicUserData = dicUserData->next;
				}

				break;

			case 'Q':

				while (optind < argc)
				{
					/*possible suboptions for this option*/
					switch (getsubopt (&(argv [optind]), dicArgumentsNames, &dicArgumentValue))
					{
						case dicLanguageArgument:
							dicLanguage = DicGetLanguageIndex (dicArgumentValue);
							break;

						case dicCurrentUserNicknameArgument:
							strcpy (dicCurrentUser->nickname, dicArgumentValue);
							break;

						default:
							printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidSuboption, dicLanguage), argv [optind]);
							printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
							exit (dicInvalidSuboption);
					}
					optind++;
				}

				/*required suboptions*/
				if (dicCurrentUser->nickname[0] == DIC_EOS)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicHasRequiredArguments, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHasRequiredArguments);
				}

				/*Authenticate current user*/
				strcpy (dicCurrentUser->password, getpass (DicGetCliUserInterfaceMessage (dicPasswordMessage, dicLanguage)));
				dicReturnCode = DicAuthenticateUser (dicCurrentUser);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}
				printf ("%s\n", DicGetCliUserInterfaceMessage (dicCorrectAuthenticateMessage, dicLanguage));

				dicReturnCode = DicGetPendingRegistrationRequests (&dicUserData);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}

				while (dicUserData != NULL)
				{
					printf ("%s\t%s\t%s\t%s\n", DicGetUserProfileString (dicUserData->profile, dicLanguage),
					        dicUserData->nickname,
					        dicUserData->username,
					        dicUserData->email);
					dicUserData = dicUserData->next;
				}

				break;

			default:
				printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidOption, dicLanguage), argv [optind]);
				printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
				exit (dicInvalidOption);

		}
	}

	printf ("%s: %s\n", DicGetCliErrorMessage (dicNoOptionEntered, dicLanguage), argv [optind]);
	printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
	exit (dicNoOptionEntered);

}

/*$RCSfile: dic.c,v $*/
