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

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h> /*for index() and rindex()*/
#include <getopt.h>
#include <sys/types.h> /*for getuid()*/
#include <pwd.h>

#include "dicAddUser.h"
#include "dicRequestRegistration.h"
#include "dicGetPendingRegistrationRequests.h"
#include "dicGetPendingRegistrationRequestsPerUser.h"
#include "dicApproveRegistrationRequest.h"
#include "dicDisapproveRegistrationRequest.h"
#include "dicGetUnlockingRequests.h"
#include "dicLockUserAccount.h"
#include "dicAcceptInvite.h"
#include "dicRejectInvite.h"
#include "dicShowCliHelp.h"
#include "dicGetUsers.h"
#include "dicUserInterface.h"
#include "dicFunctions.h"
#include "dicErrors.h"
#include "dicTypes.h"
#include "dicConst.h"
#include "dicConfig.h"

int
main (int argc, char **argv)
{
	char dicArgumentString [DIC_CLI_ARGUMENT_MAX_LENGTH + 1];
	char *dicEqualityOcourrance;
	char dicProfileString [DIC_PROFILE_MAX_LENGTH + 1];
	char dicFriendEmail [DIC_EMAIL_MAX_LENGTH + 1];
	dicUserDataType *dicUserData;
	dicUserDataType *dicCurrentUser;
	dicNicknameListType *dicNicknames;
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
		{"Ncurses",    optional_argument, NULL, 'N'},
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

					strcpy (dicArgumentString, argv [optind]);

					/*while the string argument has not an equality and a value, concatenate more one element of argv*/
					while ((optind + 1 < argc)
					   &&  ((index (dicArgumentString, '=') == NULL) || ((index (dicArgumentString, '=') + 1)* == DIC_EOS)))
					{
						optind++;
						strcat (dicArgumentString, argv [optind]);
					}

					/*while the next argument has a name before your equality or there are't a next equality symbol*/
					while ((optind + 1 < argc)
					    && (index (argv [optind + 1], '=') == NULL)
					    && (!(optind + 2 < argc) || (index (argv [optind + 2], '=') != argv [optind + 2])))
					{
						optind++;
						strcat (dicArgumentString, " ");
						strcat (dicArgumentString, argv [optind]);
					}

					dicEqualityOcourrance = index (dicArgumentString, '=');

					/*if the equality symbol is in begin or end of argument or there are more than one equality symbols*/
					if ((dicEqualityOcourrance < dicArgumentString)
					|| ((dicEqualityOcourrance + 1)* == DIC_EOS)
					||  (dicEqualityOcourrance != rindex (dicArgumentString, '=')))
					{
						printf ("%s\n", DicGetCliErrorMessage (dicNotBalancedArguments, dicLanguage));
						printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
						exit (dicNotBalancedArguments);
					}

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
						printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
						if (dicReturnCode != dicOk)
						{
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

						printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
						if (dicReturnCode != dicOk)
						{
							exit (dicReturnCode);
						}
						return dicOk;
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

					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					if (dicReturnCode != dicOk)
					{
						exit (dicReturnCode);
					}
					return dicOk;
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

					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					if (dicReturnCode != dicOk)
					{
						exit (dicReturnCode);
					}
					return dicOk;
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

					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					if (dicReturnCode != dicOk)
					{
						exit (dicReturnCode);
					}
					return dicOk;
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

				printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
				if (dicReturnCode != dicOk)
				{
					exit (dicReturnCode);
				}
				return dicOk;

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

				printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
				if (dicReturnCode != dicOk)
				{
					exit (dicReturnCode);
				}
				return dicOk;

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

				printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
				if (dicReturnCode != dicOk)
				{
					exit (dicReturnCode);
				}
				return dicOk;

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

			case 'v':

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

				/*required suboptions*/
				if (
					   dicCurrentUser->nickname[0]          ==  DIC_EOS
					|| dicUserData->nickname[0]             ==  DIC_EOS
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

				dicReturnCode = DicApproveRegistrationRequest (dicCurrentUser->nickname, dicUserData->nickname);
				printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
				if (dicReturnCode != dicOk)
				{
					exit (dicReturnCode);
				}

				break;

			case 'd':

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

				/*required suboptions*/
				if (
					   dicCurrentUser->nickname[0]          ==  DIC_EOS
					|| dicUserData->nickname[0]             ==  DIC_EOS
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

				dicReturnCode = DicDisapproveRegistrationRequest (dicCurrentUser->nickname, dicUserData->nickname);
				printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
				if (dicReturnCode != dicOk)
				{
					exit (dicReturnCode);
				}

				break;

			case 'U':

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

				/*permissions*/
				if (!(dicCurrentUser->profile & dicAdministrator)) /*if user is't administrator*/
				{
					/*have not permission*/
					printf ("%s\n", DicGetCliErrorMessage (dicHaveNotPermission, dicLanguage));
					printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
					exit (dicHaveNotPermission);
				}

				dicReturnCode = DicGetUnlockingRequests (&dicNicknames);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}

				while (dicNicknames != NULL)
				{
					printf ("%s\n", dicNicknames->nickname);
					dicNicknames = dicNicknames->next;
				}

				break;

			case 's':

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

				dicReturnCode = DicGetUsers (&dicUserData);
				if (dicReturnCode != dicOk)
				{
					printf ("%s\n", DicGetCliErrorMessage (dicReturnCode, dicLanguage));
					exit (dicReturnCode);
				}

				while (dicUserData != NULL)
				{
					if (dicUserData->password[0] != DIC_EOS)
					{
						printf ("%llu%s\t%s\t%s\t%s\n",
						        dicUserData->userId,
						        DicGetUserProfileString (dicUserData->profile, dicLanguage),
						        dicUserData->nickname,
						        dicUserData->username,
						        dicUserData->email);
						dicUserData = dicUserData->next;
					}
				}

				break;

			default:
				printf ("%s: %s\n", DicGetCliErrorMessage (dicInvalidOption, dicLanguage), argv [optind-1]);
				printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
				exit (dicInvalidOption);

		}

		return dicOk;
	}

	printf ("%s\n", DicGetCliErrorMessage (dicNoOptionEntered, dicEnglish));
	printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicEnglish), argv[0]);
	printf ("%s\n", DicGetCliErrorMessage (dicNoOptionEntered, dicPortuguese));
	printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicPortuguese), argv[0]);
	exit (dicNoOptionEntered);

}

/*$RCSfile: dic.c,v $*/
