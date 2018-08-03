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

			case 'generic':

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
							strcpy (dicProfileString, dicArgumentValue);
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
					|| dicUserData->username[0]             ==  DIC_EOS
					|| dicUserData->usernameConfirmation[0] ==  DIC_EOS
					|| dicUserData->email[0]                ==  DIC_EOS
					|| dicUserData->emailConfirmation[0]    ==  DIC_EOS
					|| dicUserData->nickname[0]             ==  DIC_EOS
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

				/*permissions*/
				if ((dicCurrentUser->profile % 2) == 1) /*if user is administrator*/
				{
					dicReturnCode = DicAddUser (dicUserData);
					if (dicReturnCode == dicOk)
					{
						printf ("%s\n", DicGetCliUserInterfaceMessage (dicCreatedUserMessage, dicLanguage));
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
				else if (dicCurrentUser->profile >= 4)/*user is student*/
				{
					
				}

				/*have not permission*/
				printf ("%s\n", DicGetCliErrorMessage (dicHaveNotPermission, dicLanguage));
				printf ("%s: %s -h/--help\n", DicGetCliUserInterfaceMessage (dicForHelpMessage, dicLanguage), argv[0]);
				exit (dicHaveNotPermission);

				break;


/*$RCSfile$*/
