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

#include "dicLockUserAccount.h"
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
 * DicLockUserAccount (char*, char*);
 *
 * Arguments:
 * char* - nickname of administrator that want to lock the account
 * char* - nickname of user that you try to lock
 *
 * Returned values:
 * dicOk - registration request invited successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicLockedUserNotFound - the user that you try to lock not exist or is your self
 * dicHaveNotPermission - the user that you try to lock is the primary administrator of system
 * dicUserIsPending - the user that you try to lock is pending
 *
 * Description:
 * This function locks the account of an user if it is not the primary administrator or pending user,
 * and send an email to locked user.
 */
dicErrorType
DicLockUserAccount (char *dicAdministratorNickname, char *dicLockedNickname)
{
	FILE *dicLockedUsersFile;
	FILE *dicUsersFile;
	FILE *dicUsersFile_Temp;

	dicUserDataType *dicUser;
	dicUserDataType *dicAdministrator = NULL;
	dicUserDataType *dicLockedUser = NULL;

	char dicUsersFileLineCopy [DIC_USERSFILE_LINE_MAX_LENGTH + 1];
	char dicUsersFileLine [DIC_USERSFILE_LINE_MAX_LENGTH + 1];

	char dicLockedFirstName [DIC_USERNAME_MAX_LENGTH];
	char dicEmailBody [DIC_EMAIL_BODY_MAX_LENGTH];

	char *validation;

	time_t dicLockTime;


	if (dicAdministratorNickname == NULL || dicLockedNickname == NULL)
		return dicInvalidArgument;

	DicGetUsers (&dicUser);
	/*search user email and verifys requesting user email and nickname*/
	while (dicUser != NULL)
	{
		if (!strcmp (dicUser->nickname, dicAdministratorNickname))
		{
			dicAdministrator = dicUser;

			if (dicLockedUser != NULL)
				break;
		}
		else if (!strcmp (dicUser->nickname, dicLockedNickname)) /*An user can not to lock your self*/
		{
			if (dicUser->userId == 0)
				return dicHaveNotPermission;

			if (dicUser->password[0] == DIC_EOS)
				return dicUserIsPending;

			dicLockedUser = dicUser;

			if (dicAdministrator != NULL)
				break;
		}

		dicUser = dicUser->next;
	}

	if (dicLockedUser == NULL)
		return dicLockedUserNotFound;

	/*open locked users data file*/
	dicLockedUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_LOCKED_USERS_DATA_FILENAME), "a");

	dicLockTime = time (NULL);

	/*<locked userId><admin userId><lock time><encoded password>*/
	fwrite (&(dicLockedUser->userId), sizeof (dicUserIdentifierType), 1, dicLockedUsersFile);
	fwrite (&(dicAdministrator->userId), sizeof (dicUserIdentifierType), 1, dicLockedUsersFile);
	fwrite (&(dicLockTime), sizeof (time_t), 1, dicLockedUsersFile);
	fwrite (dicLockedUser->password, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicLockedUsersFile);

	/*open users file and temporary users file*/
	dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "r");
	dicUsersFile_Temp = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"), "w");

	/*copy the users file for temporary file*/
	while (fgets (dicUsersFileLine, DIC_USERSFILE_LINE_MAX_LENGTH + 1, dicUsersFile) != NULL)
	{
		strcpy (dicUsersFileLineCopy, dicUsersFileLine);

		if (strtoul (strtok (dicUsersFileLineCopy, ":"), &validation, 10) == dicLockedUser->userId)
		{
			/*rewriten the line corresponding to locked user without the password*/
			fprintf (dicUsersFile_Temp, "%llu:%s::%i:%s:%s\n",
			         dicLockedUser->userId,
			         dicLockedUser->nickname,
			         dicLockedUser->profile,
			         dicLockedUser->username,
			         dicLockedUser->email);
		}
		else
		{
			fprintf (dicUsersFile_Temp, "%s", dicUsersFileLine);
		}
	}

	/*close the files and deletes the users file*/
	fclose (dicLockedUsersFile);
	fclose (dicUsersFile);
	fclose (dicUsersFile_Temp);
	remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME));
	/*rename temporary file created */
	rename (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"),
	        DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME));


	strcpy (dicLockedFirstName, dicLockedUser->username);
	strtok (dicLockedFirstName, " ");

	snprintf (dicEmailBody, DIC_EMAIL_BODY_MAX_LENGTH + 1, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
	        "Hi, ", dicLockedFirstName,
	        "\n\nYour account in Olhar Discente has been blocked.\n",
	        "For unlock your account access: ", DIC_WEB_SERVER_URL, "CGIs/dicUnlockUserAccountForm.cgi?dicLanguage=dicEnglish\n\n\n",
	        "For more informations contact us or visit the site: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicEnglish\n",
	        "In majority of the e-mail systems this is a blue link and you can click. In other cases copy for your browser.\n\n\n",
	        "-------------------------------------------------------\n\n\n",
	        "Olá, ", dicLockedFirstName,
	        "\n\nSua conta em Olhar Discente foi bloqueada.\n",
	        "Para desbloquear sua conta acesse: ", DIC_WEB_SERVER_URL, "CGIs/dicUnlockUserAccountForm.cgi?dicLanguage=dicPortuguese\n\n\n",
	        "Para mais informações contacte-nos ou acesse: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicPortuguese\n",
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
		"Olhar Discente - Locked Account", /*Subject*/
		dicEmailBody,   /*Body*/
		NULL  /*Attatchement*/
	);

	return dicOk;
}

/*$RCSfile$*/
