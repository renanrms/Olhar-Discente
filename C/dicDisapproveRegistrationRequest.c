/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicDisapproveRegistrationRequest.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dicDisapproveRegistrationRequest.h"
#include "dicFunctions.h"
#include "dicErrors.h"
#include "dicTypes.h"
#include "dicConst.h"
#include "dicConfig.h"
#include "Libraries/sendmail.h"

/*
 * dicErrorType
 * DicDisapproveRegistrationRequest (char*, char*);
 *
 * Arguments:
 * char* - nickname of responsible user (I)
 * char* - nickname of requesting (I)
 *
 * Returned values:
 * dicOk - registration request was disapproved successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicUserAlreadyRegistered - the user is in active state
 * dicNotRequestingUser - user is not requesting or your requesting has expired
 * dicNotResponsibleUser - user is nor the responsible for this request
 *
 * Description:
 * This function disapproves a registration request if the data received corresponds to requesting user
 * and your responsible user and the request is not expired, and then send an email for the requesting.
 */
dicErrorType
DicDisapproveRegistrationRequest (char *dicResponsibleNickname, char *dicRequestingNickname)
{
	FILE *dicRequestingUsersFile;
	FILE *dicRequestingUsersFile_Temp;
	FILE *dicUsersFile;
	FILE *dicUsersFile_Temp;

	char dicUsersFileLineCopy [DIC_USERSFILE_LINE_MAX_LENGTH + 1];
	char dicUsersFileLine [DIC_USERSFILE_LINE_MAX_LENGTH + 1];
	char *validation;
	char *dicTokenPointer;
	size_t dicReadBytes;
	unsigned char dicFoundResponsibleUser = 0; /*flag variable*/
	unsigned char dicFoundRequestingUser = 0; /*flag variable*/

	dicUserDataType *dicRequesting;
	dicUserDataType *dicResponsible;

	dicUserIdentifierType dicUserId1;
	dicUserIdentifierType dicUserId2;
	char dicUserNickname [DIC_NICKNAME_MAX_LENGTH + 1];

	char dicFirstName [DIC_USERNAME_MAX_LENGTH + 1];
	char dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1];
	char dicEmailBody [DIC_EMAIL_BODY_MAX_LENGTH + 1];
	time_t dicAbsoluteValidityTime;


	if (dicResponsibleNickname == NULL || dicRequestingNickname == NULL)
		return dicInvalidArgument;

	dicRequesting = malloc (sizeof(dicUserDataType));

	dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "r");
	dicUsersFile_Temp = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"), "w");

	strcpy (dicRequesting->nickname, dicRequestingNickname);

	/*obtain data of invited user*/
	while (fgets (dicUsersFileLine, DIC_USERSFILE_LINE_MAX_LENGTH + 1, dicUsersFile) != NULL)
	{
		strcpy (dicUsersFileLineCopy, dicUsersFileLine);

		dicUserId1 = strtoul (strtok (dicUsersFileLine, ":"), &validation, 10);
		strcpy (dicUserNickname, strtok (NULL, ":")); 

		if (!strcmp (dicUserNickname, dicResponsibleNickname))
		{
			dicFoundResponsibleUser = 1;
			dicResponsible->userId = dicUserId1;
			strcpy (dicResponsible->password, strtok (NULL, ":"));
			dicResponsible->profile = strtoul (strtok (NULL, ":"), &validation, 10);
			strcpy (dicRequesting->username, strtok (NULL, ":"));
			strcpy (dicRequesting->email, strtok (NULL, ":"));

			if (dicFoundRequestingUser)
				break;
		}

		/*if found user, verifys the password*/
		if (!strcmp (dicRequesting->nickname, dicUserNickname))
		{
			dicTokenPointer = strtok (NULL, ":");
			/*if password is empty*/
			if (*(dicTokenPointer - 1) == ':')
			{
				dicFoundRequestingUser = 1;
				dicRequesting->userId = dicUserId1;
				dicRequesting->profile = strtoul (dicTokenPointer, &validation, 10);
				strcpy (dicRequesting->username, strtok (NULL, ":"));
				strcpy (dicRequesting->email, strtok (NULL, ":"));
				
				if (dicFoundResponsibleUser)
					break;
			}
			else
			{
				fclose (dicUsersFile);
				fclose (dicUsersFile_Temp);
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
				return dicUserAlreadyRegistered;
			}
		}
		else /*if is not the shared user, copy this line*/
		{
			fprintf (dicUsersFile_Temp, "%s", dicUsersFileLineCopy);
		}
	}

	if (!dicFoundRequestingUser)
	{
		fclose (dicUsersFile);
		fclose (dicUsersFile_Temp);
		remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
		return dicNotRequestingUser;
	}
	if (!dicFoundResponsibleUser)
	{
		fclose (dicUsersFile);
		fclose (dicUsersFile_Temp);
		remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
		return dicNotResponsibleUser;
	}

	dicRequestingUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_REQUESTING_USERS_DATA_FILENAME), "r");
	dicRequestingUsersFile_Temp = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_requesting.users"), "w");

	/*<validity><userId><encoded password>*/
	fread (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicRequestingUsersFile);
	fread (&(dicUserId1), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
	fread (&(dicUserId2), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
	dicReadBytes = fread (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicRequestingUsersFile);
	dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1] = DIC_EOS;

	dicFoundRequestingUser = 0;
	/*copy from requesting users file to temporary file and search the userId corresponding to nickname*/
	while (dicReadBytes == sizeof (time_t) + 2*sizeof (dicUserIdentifierType) + DIC_PASSWORD_MAX_LENGTH*sizeof (char))
	{
		/*found user. This line is not copy*/
		if (dicUserId1 == dicRequesting->userId)
		{
			dicFoundRequestingUser = 1;
			/*request is expired*/
			if (time (NULL) > dicAbsoluteValidityTime)
			{
				fclose (dicUsersFile);
				fclose (dicUsersFile_Temp);
				fclose (dicRequestingUsersFile);
				fclose (dicRequestingUsersFile_Temp);
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_requesting.users"));
				return dicNotRequestingUser;
			}

			if (dicUserId2 != dicResponsible->userId && dicResponsible->profile % 2 != 1)
			{
				fclose (dicUsersFile);
				fclose (dicUsersFile_Temp);
				fclose (dicRequestingUsersFile);
				fclose (dicRequestingUsersFile_Temp);
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_requesting.users"));
				return dicNotResponsibleUser;
			}
		}
		else /*not is the requesting user. Copy data for temporary file*/
		{
			fwrite (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicRequestingUsersFile_Temp);
			fwrite (&(dicUserId1), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile_Temp);
			fwrite (&(dicUserId2), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile_Temp);
			fwrite (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicRequestingUsersFile_Temp);
		}

		/*<validity><userId><encoded password>*/
		fread (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicRequestingUsersFile);
		fread (&(dicUserId1), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
		fread (&(dicUserId2), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
		dicReadBytes = fread (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicRequestingUsersFile);
		dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1] = DIC_EOS;
	}

	/*not found user. Indicates that user is in other pendent state*/
	if (!dicFoundRequestingUser)
	{
		fclose (dicUsersFile);
		fclose (dicUsersFile_Temp);
		fclose (dicRequestingUsersFile);
		fclose (dicRequestingUsersFile_Temp);
		remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
		remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_requesting.users"));
		return dicNotRequestingUser;
	}

	/*close the files and deletes the invited users file*/
	fclose (dicRequestingUsersFile);
	fclose (dicRequestingUsersFile_Temp);
	remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_INVITED_USERS_DATA_FILENAME));
	/*rename temporary file created*/
	rename (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_requesting.users"),
	        DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_INVITED_USERS_DATA_FILENAME));

	/*copy the rest of users file for temporary file*/
	while (fgets (dicUsersFileLine, DIC_USERSFILE_LINE_MAX_LENGTH + 1, dicUsersFile) != NULL)
	{
		fprintf (dicUsersFile_Temp, "%s", dicUsersFileLine);
	}

	/*close the files and deletes the users file*/
	fclose (dicUsersFile);
	fclose (dicUsersFile_Temp);
	remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME));
	/*rename temporary file created */
	rename (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"),
	        DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME));

	strcpy (dicFirstName, dicRequesting->username);
	strtok (dicFirstName, " ");

	snprintf (dicEmailBody, DIC_EMAIL_BODY_MAX_LENGTH + 1, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
	        "Hi, ", dicFirstName,
	        "\n\nYour registration at Olhar Discente with this e-mail was disapproved.\n\n\n",
	        "For more informations contact us or visit the site: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicEnglish\n",
	        "In majority of the e-mail systems this is a blue link and you can click. In other cases copy for your browser.\n\n\n",
	        "-------------------------------------------------------\n\n\n",
	        "Olá, ", dicFirstName,
	        "\n\nSeu cadastro em Olhar Discente com este e-mail foi desprovado.\n\n\n",
	        "Para mais informações contacte-nos ou acesse aqui: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicPortuguese\n",
	        "Na maioria dos sistemas de e-mail isto é um link azul e é possível clicá-lo. Se este não é o caso copie para a barra do seu navegador.\n"
	        );

	/*Send email to new user*/
	sendMail (
		DIC_SMTP_CLIENT_DOMAIN,
		DIC_SMTP_SERVER_FULL_HOSTNAME,
		DIC_SMTP_SERVER_PORT,
		DIC_PRIMARY_ADMINISTRATOR_EMAIL, /*From Admin*/
		dicRequesting->email, /*To*/
		NULL, /*cc*/
		NULL, /*bcc*/
		"Olhar Discente - User Registration Disapproved", /*Subject*/
		dicEmailBody,   /*Body*/
		NULL  /*Attatchement*/
	);

	return dicOk;
}

/*$RCSfile: dicDisapproveRegistrationRequest.c,v $*/
