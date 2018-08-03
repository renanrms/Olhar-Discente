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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "dicUnlockUserAccount.h"
#include "dicUserInterface.h"
#include "dicGetUsers.h"
#include "dicConfig.h"
#include "dicErrors.h"
#include "dicConst.h"
#include "dicTypes.h"
#include "dicFunctions.h"
#include "Libraries/sendmail.h"

/*
 * dicErrorType
 * DicUnlockUserAccount (char*, char*, char*);
 *
 * Arguments:
 * char* - nickname of courrent user
 * char* - nickname of locked user
 * char* - password of locked user that requests unlocking (empty string if the agument one is an administrator)
 *
 * Returned values:
 * dicOk - registration request invited successfully
 * dicInvalidArgument - first argument is NULL pointer
 * dicUserAlreadyRegistered - user that you try to unlock or user that requests unlocking is unlocked
 * dicLockedUserNotFound - the locked user not exist or is equal to courrent
 * dicNotLockedUser - user is in other pending state
 * dicIncorrectPassword - password of user that requests unlocking is incorrect
 *
 * Description:
 * If the locked user nickname is a valid and not empty string, this function suspposes that courrent user
 * is an administrator and to unlock the account of locked user and send an email for then.
 * If the locked user nickname is NULL or an empty string, this function verifys the password of locked user and then
 * request your unlocking and send email for all administrators of system, except for yourself if is administrator.
 * In firt case the password may have any value.
 */
dicErrorType
DicUnlockUserAccount (char *dicCourrentNickname, char *dicLockedNickname, char *dicLockedPassword)
{
	FILE *dicLockedUsersFile;
	FILE *dicLockedUsersFile_Temp;
	FILE *dicUsersFile;
	FILE *dicUsersFile_Temp;
	FILE *dicUnlockingUsersFile;

	dicUserDataType *dicUser;
	dicUserDataType *dicFirstUser;
	dicUserDataType *dicCourrentUser = NULL;
	dicUserDataType *dicLockedUser = NULL;

	char dicUsersFileLineCopy [DIC_USERSFILE_LINE_MAX_LENGTH + 1];
	char dicUsersFileLine [DIC_USERSFILE_LINE_MAX_LENGTH + 1];

	dicUserIdentifierType dicUserId1;
	dicUserIdentifierType dicUserId2;
	char dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1];
	char dicAdministratorFirstName [DIC_USERNAME_MAX_LENGTH + 1];
	char dicLockedFirstName [DIC_USERNAME_MAX_LENGTH + 1];
	char dicEmailBody [DIC_EMAIL_BODY_MAX_LENGTH + 1];

	unsigned char dicFoundLockedUser = 0; /*flag variable*/

	time_t dicTime;

	size_t dicReadBytes;

	char *validation;

	dicErrorType dicReturnCode;


	if (dicCourrentNickname == NULL)
		return dicInvalidArgument;

	DicGetUsers (&dicFirstUser);

	dicUser = dicFirstUser;

	if (dicLockedNickname == NULL || dicLockedNickname* == DIC_EOS)
	{
		/*search users*/
		while (dicUser != NULL)
		{
			if (!strcmp (dicUser->nickname, dicCourrentUserNickname))
			{
				if (dicUser->password[0] != DIC_EOS)
					return dicUserAlreadyRegistered;

				dicCourrentUser = dicUser;
				break;
			}
			dicUser = dicUser->next;
		}

		if (dicCourrentUser == NULL)
			return dicLockedUserNotFound;

		/*search in locked users file the userId corresponding to nickname and autenticate the locked user*/
		dicLockedUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_LOCKED_USERS_DATA_FILENAME), "r");

		while (1)
		{
			/*<locked userId><admin userId><lock time><encoded password>*/
			fread (&(dicUserId1), sizeof (dicUserIdentifierType), 1, dicLockedUsersFile);
			fread (&(dicUserId2), sizeof (dicUserIdentifierType), 1, dicLockedUsersFile);
			fread (&(dicTime), sizeof (time_t), 1, dicLockedUsersFile);
			dicReadBytes = fread (dicCourrentUser->password, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicLockedUsersFile);
			dicCourrentUser->password [DIC_PASSWORD_MAX_LENGTH + 1] = DIC_EOS;

			/*final of file*/
			if (dicReadBytes != sizeof (time_t) + 2 * sizeof (dicUserIdentifierType) + DIC_PASSWORD_MAX_LENGTH * sizeof (char))
			{
				return dicNotLockedUser;
			}

			/*found user. This line is not copy*/
			if (dicUserId1 == dicCourrentUser->userId)
			{
				if (DicCheckPassword (dicLockedPassword, dicCourrentUser->password) != dicOk)
				{
					fclose (dicLockedUsersFile);
					return dicIncorrectPassword;
				}

				break;
			}
		}

		dicUnlockingUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_UNLOCKING_USERS_DATA_FILENAME), "a");

		dicTime = time (NULL) + DIC_UNLOCKING_EXPIRATION_TIME;

		fwrite (&(dicTime), sizeof (time_t), 1, dicUnlockingUsersFile);
		fwrite (&(dicUserId1), sizeof (dicUserIdentifierType), 1, dicUnlockingUsersFile);

		fclose (dicUnlockingUsersFile);
		fclose (dicLockedUsersFile);

		dicUser = dicFirstUser;

		/*send email for all administrators except the locked user if he is administrator*/
		while (dicUser != NULL)
		{
			if (!(dicUser->profile & dicAdministrator) || !strcmp (dicUser->nickname, dicCourrentUser->nickname))
				continue;

			strcpy (dicAdministratorFirstName, dicUser->username);
			strtok (dicAdministratorFirstName, " ");

			snprintf (dicEmailBody, DIC_EMAIL_BODY_MAX_LENGTH + 1, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
			         "Hi, ", dicAdministratorFirstName,
			         "\n\nThis is a message sended for all administrators of Olhar Discente about an unlocking account request.\n\n",
			         "The data of user that request unlocking in the system are:",
			         "\nIdentifier: ", dicCourrentUser->userId,
			         "\nProfile: ", DicGetUserProfileString (dicCourrentUser->profile, dicEnglish),
			         "\nNickname: ", dicCourrentUser->nickname,
			         "\nUsername: ", dicCourrentUser->username,
			         "\nE-mail: ", dicCourrentUser->email,
			         "\n\nThis unlocking request expires in 24 hours.\n\n",
			         "For unlock this account access the site: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicEnglish\n",
			         "In majority of the e-mail systems this is a blue link and you can click. In other cases copy for your browser.\n\n\n",
			         "-------------------------------------------------------\n\n\n",
			         "Olá, ", dicAdministratorFirstName,
			         "\n\nEsta é uma mensagem enviada a todos os administradores do Olhar Discente sobre uma solicitação de desbloqueio de conta.\n\n",
			         "Os dados do usuário que solicitou desbloqueio no sistma são:",
			         "\nIdentificador: ", dicCourrentUser->userId,
			         "\nPerfil: ", DicGetUserProfileString (dicCourrentUser->profile, dicPortuguese),
			         "\nApelido: ", dicCourrentUser->nickname,
			         "\nNome completo: ", dicCourrentUser->username,
			         "\nE-mail: ", dicCourrentUser->email,
			         "\n\nEsta solicitação de bloqueio expira em 24 horas.\n\n",
			         "Para desbloquear esta conta acesse o site: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicPortuguese\n",
			         "Na maioria dos sistemas de e-mail isto é um link azul e é possível clicá-lo. Se este não é o caso copie para a barra do seu navegador.\n"
			         );

			/*Send email to responsible user*/
			sendMail (
				DIC_SMTP_CLIENT_DOMAIN,
				DIC_SMTP_SERVER_FULL_HOSTNAME,
				DIC_SMTP_SERVER_PORT,
				DIC_PRIMARY_ADMINISTRATOR_EMAIL, /*From Admin*/
				dicUser->email, /*To*/
				NULL, /*cc*/
				NULL, /*bcc*/
				"Olhar Discente - Unlocking Request Received", /*Subject*/
				dicEmailBody,   /*Body*/
				NULL  /*Attatchement*/
			);

			dicUser = dicUser->next;
		}
	}
	else /*copy from lock users file to temporary file and search the userId corresponding to nickname and then, write password in users file*/
	{
		/*search users*/
		while (dicUser != NULL)
		{
			if (!strcmp (dicUser->nickname, dicCourrentUserNickname))
			{
				dicCourrentUser = dicUser;

				if (dicLockedUser != NULL)
					break;
			}
			else if (!strcmp (dicUser->nickname, dicLockedNickname))
			{
				if (dicUser->password[0] != DIC_EOS)
					return dicUserAlreadyRegistered;

				dicLockedUser = dicUser;

				if (dicCourrentUser != NULL)
					break;
			}

			dicUser = dicUser->next;
		}

		if (dicLockedUser == NULL)
			return dicLockedUserNotFound;

		dicLockedUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_LOCKED_USERS_DATA_FILENAME), "r");
		dicLockedUsersFile_Temp = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_locked.users"), "w");

		while (1)
		{
			/*<locked userId><admin userId><lock time><encoded password>*/
			fread (&(dicUserId1), sizeof (dicUserIdentifierType), 1, dicLockedUsersFile);
			fread (&(dicUserId2), sizeof (dicUserIdentifierType), 1, dicLockedUsersFile);
			fread (&(dicTime), sizeof (time_t), 1, dicLockedUsersFile);
			dicReadBytes = fread (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicLockedUsersFile);
			dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1] = DIC_EOS;

			/*final of file*/
			if (dicReadBytes != sizeof (time_t) + sizeof (dicUserIdentifierType) + DIC_PASSWORD_MAX_LENGTH*sizeof (char))
			{
				/*not found user. Indicates that user is in other pending state*/
				if (!dicFoundLockedUser)
				{
					fclose (dicLockedUsersFile);
					fclose (dicLockedUsersFile_Temp);
					remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_locked.users"));
					return dicNotLockedUser;
				}
				else
					break;
			}

			/*found user. This line is not copy*/
			if (dicUserId1 == dicLockedUser->userId)
			{
				dicFoundLockedUser = 1;

				if (DicCheckPassword (dicLockedPassword, dicEncodedPassword) != dicOk)
				{
					fclose (dicLockedUsersFile);
					fclose (dicLockedUsersFile_Temp);
					remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_locked.users"));
					return dicIncorrectPassword;
				}

				strcpy (dicLockedUser->password, dicEncodedPassword);
			}
			else /*not is the user invited. Copy data for temporary file*/
			{
				fwrite (&(dicUserId1), sizeof (dicUserIdentifierType), 1, dicLockedUsersFile);
				fwrite (&(dicUserId2), sizeof (dicUserIdentifierType), 1, dicLockedUsersFile);
				fwrite (&(dicTime), sizeof (time_t), 1, dicLockedUsersFile);
				fwrite (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicLockedUsersFile);
			}
		}

		/*open users file and temporary users file*/
		dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "r");
		dicUsersFile_Temp = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"), "w");

		/*copy the users file for temporary file*/
		while (fgets (dicUsersFileLine, DIC_USERSFILE_LINE_MAX_LENGTH + 1, dicUsersFile) != NULL)
		{
			strcpy (dicUsersFileLineCopy, dicUsersFileLine);

			if (strtoul (strtok (dicUsersFileLineCopy, ":"), &validation, 10) == dicLockedUser->userId)
			{
				/*rewriten the line corresponding to locked user with the password*/
				fprintf (dicUsersFile_Temp, "%llu:%s:%s:%i:%s:%s\n",
				         dicLockedUser->userId,
				         dicLockedUser->nickname,
				         dicLockedUser->password,
				         dicLockedUser->profile,
				         dicLockedUser->username,
				         dicLockedUser->email);
			}
			else
			{
				fprintf (dicUsersFile_Temp, "%s", dicUsersFileLine);
			}
		}

		/*close the files and deletes the locked users file*/
		fclose (dicLockedUsersFile);
		fclose (dicLockedUsersFile_Temp);
		remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_LOCKED_USERS_DATA_FILENAME));
		/*rename temporary file created*/
		rename (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_locked.users"),
		        DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_LOCKED_USERS_DATA_FILENAME));

		/*close the files and deletes the users file*/
		fclose (dicUsersFile);
		fclose (dicUsersFile_Temp);
		remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME));
		/*rename temporary file created */
		rename (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"),
		        DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME));

		snprintf (dicEmailBody, DIC_EMAIL_BODY_MAX_LENGTH + 1, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		         "Hi, ", dicLockedFirstName,
		         "\n\nYour account in Olhar Discente has been unlocked.\n",
		         "For access the system: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicEnglish\n",,
		         "In majority of the e-mail systems this is a blue link and you can click. In other cases copy for your browser.\n\n\n",
		         "-------------------------------------------------------\n\n\n",
		         "Olá, ", dicLockedFirstName,
		         "\n\nSua conta em Olhar Discente foi desbloqueada.\n",
		         "Para acessar o sistema: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicPortuguese\n",
		         "Na maioria dos sistemas de e-mail isto é um link azul e é possível clicá-lo. Se este não é o caso copie para a barra do seu navegador.\n"
		         );

		/*Send email to responsible user*/
		sendMail (
			DIC_SMTP_CLIENT_DOMAIN,
			DIC_SMTP_SERVER_FULL_HOSTNAME,
			DIC_SMTP_SERVER_PORT,
			DIC_PRIMARY_ADMINISTRATOR_EMAIL, /*From Admin*/
			dicLockedUser->email, /*To*/
			NULL, /*cc*/
			NULL, /*bcc*/
			"Olhar Discente - Unlocked Account", /*Subject*/
			dicEmailBody,   /*Body*/
			NULL  /*Attatchement*/
		);

	}

	return dicOk;
}

/*$RCSfile$*/
