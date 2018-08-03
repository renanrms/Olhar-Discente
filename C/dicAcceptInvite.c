/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicAcceptInvite.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dicAcceptInvite.h"
#include "dicFunctions.h"
#include "dicErrors.h"
#include "dicTypes.h"
#include "dicConst.h"
#include "dicConfig.h"
#include "Libraries/sendmail.h"

/*
 * dicErrorType
 * DicAcceptInvite (char*, dicUserDataType*);
 *
 * Arguments:
 * char* - password of invited user (I)
 * dicUserDataType* - structure containing nickname, new password and your confirmation
 *
 * Returned values:
 * dicOk - invite was accept successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicUserAlreadyRegistered - the user is in active state
 * dicNotInvitedUser - if user is not invited or your invite has expired
 * dicIcorrectPassword - user authentication failed
 * dicInvalidPassword - new password is not in the specifications
 * dicInvalidPasswordConfirmation - new password confirmation differs from new password
 *
 * Description:
 * This function accepts a invite to register in the system if user was invited,
 * your invite is not expired, your password is correct and your new password and confirmation is valid.
 */
dicErrorType
DicAcceptInvite (char *dicPassword, dicUserDataType *dicInvitedUser)
{
	FILE *dicInvitedUsersFile;
	FILE *dicInvitedUsersFile_Temp;
	FILE *dicUsersFile;
	FILE *dicUsersFile_Temp;

	char dicUsersFileLineCopy [DIC_USERSFILE_LINE_MAX_LENGTH + 1];
	char dicUsersFileLine [DIC_USERSFILE_LINE_MAX_LENGTH + 1];
	char *validation;
	size_t dicReadBytes;
	unsigned char dicFoundInvitedUser = 0; /*flag variable*/

	dicUserDataType *dicUser;
	dicUserIdentifierType dicUserId;
	char *dicTokenPointer;
	char dicFirstName [DIC_USERNAME_MAX_LENGTH + 1];
	char dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1];
	char dicEmailBody [DIC_EMAIL_BODY_MAX_LENGTH + 1];
	time_t dicAbsoluteValidityTime;

	dicErrorType dicReturnCode;

	if (dicPassword == NULL || dicInvitedUser == NULL)
		return dicInvalidArgument;

	dicUser = malloc (sizeof (dicUserDataType));

	dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "r");
	dicUsersFile_Temp = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"), "w");

	/*obtain data of invited user*/
	while (1)
	{
		if (fgets (dicUsersFileLine, DIC_USERSFILE_LINE_MAX_LENGTH + 1, dicUsersFile) != NULL)
		{
			strcpy (dicUsersFileLineCopy, dicUsersFileLine);

			dicUser->userId = strtoul (strtok (dicUsersFileLine, ":"), &validation, 10);
			strcpy (dicUser->nickname, strtok (NULL, ":"));

			/*if found user, verifys the password*/
			if (!strcmp (dicUser->nickname, dicInvitedUser->nickname))
			{
				dicTokenPointer = strtok (NULL, ":");
				/*if password is empty*/
				if (*(dicTokenPointer - 1) == ':')
				{
					dicUser->password[0] = DIC_EOS;
					dicUser->profile = strtoul (dicTokenPointer, &validation, 10);
					strcpy (dicUser->username, strtok (NULL, ":"));
					strcpy (dicUser->email, strtok (NULL, "\n"));
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
		else /*final of file. user not found*/
		{
			fclose (dicUsersFile);
			fclose (dicUsersFile_Temp);
			remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
			return dicNotInvitedUser;
		}
	}

	dicInvitedUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_INVITED_USERS_DATA_FILENAME), "r");
	dicInvitedUsersFile_Temp = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"), "w");

	/*copy from invited users file to pemporary file and search the userId corresponding to nickname*/
	while (1)
	{
		/*<validity><userId><encoded password>*/
		fread (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicInvitedUsersFile);
		fread (&(dicUserId), sizeof (dicUserIdentifierType), 1, dicInvitedUsersFile);
		dicReadBytes = fread (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicInvitedUsersFile);
		dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH + 1] = DIC_EOS;

		/*final of file*/
		if (dicReadBytes != sizeof (time_t) + sizeof (dicUserIdentifierType) + DIC_PASSWORD_MAX_LENGTH*sizeof (char))
		{
			/*not found user. Indicates that user is in other pendent state*/
			if (!dicFoundInvitedUser)
			{
				fclose (dicUsersFile);
				fclose (dicUsersFile_Temp);
				fclose (dicInvitedUsersFile);
				fclose (dicInvitedUsersFile_Temp);
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"));
				return dicNotInvitedUser;
			}
			else
				break;
		}

		/*found user. This line is not copy*/
		if (dicUserId == dicUser->userId)
		{
			dicFoundInvitedUser = 1;
			/*invite is expired*/
			if (time (NULL) > dicAbsoluteValidityTime)
			{
				fclose (dicUsersFile);
				fclose (dicUsersFile_Temp);
				fclose (dicInvitedUsersFile);
				fclose (dicInvitedUsersFile_Temp);
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"));
				return dicNotInvitedUser;
			}

			if (DicCheckPassword (dicPassword, dicEncodedPassword) == dicOk)
			{
				/*validation of the new password*/
				dicReturnCode = DicCheckStringField (dicInvitedUser->password, DIC_PASSWORD_CARACTERS, DIC_PASSWORD_MIN_LENGTH, DIC_PASSWORD_MAX_LENGTH);
				if (dicReturnCode != dicOk)
				{
					fclose (dicUsersFile);
					fclose (dicUsersFile_Temp);
					fclose (dicInvitedUsersFile);
					fclose (dicInvitedUsersFile_Temp);
					remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
					remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"));
					return dicInvalidPassword;
				}
				if(strcmp (dicInvitedUser->password, dicInvitedUser->passwordConfirmation))
				{
					fclose (dicUsersFile);
					fclose (dicUsersFile_Temp);
					fclose (dicInvitedUsersFile);
					fclose (dicInvitedUsersFile_Temp);
					remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
					remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"));
					return dicInvalidPasswordConfirmation;
				}
				/*accept user. Encode new password*/
				DicEncodePasswordWithSpecificAlgorithm (dicInvitedUser->password, dicSha512, dicUser->password);
			}
			else
			{
				fclose (dicUsersFile);
				fclose (dicUsersFile_Temp);
				fclose (dicInvitedUsersFile);
				fclose (dicInvitedUsersFile_Temp);
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_users"));
				remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"));
				return dicIncorrectPassword;
			}
		}
		else /*not is the user invited. Copy data for temporary file*/
		{
			fwrite (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicInvitedUsersFile_Temp);
			fwrite (&(dicUserId), sizeof (dicUserIdentifierType), 1, dicInvitedUsersFile_Temp);
			fwrite (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicInvitedUsersFile_Temp);
		}
	}

	/*close the files and deletes the invited users file*/
	fclose (dicInvitedUsersFile);
	fclose (dicInvitedUsersFile_Temp);
	remove (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_INVITED_USERS_DATA_FILENAME));
	/*rename temporary file created*/
	rename (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, ".temporary_invited.users"),
	        DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_INVITED_USERS_DATA_FILENAME));

	/*rewriten the line corresponding to invited user with new password*/
	fprintf (dicUsersFile_Temp, "%llu:%s:%s:%i:%s:%s\n",
	         dicUser->userId,
	         dicUser->nickname,
	         dicUser->password,
	         dicUser->profile,
	         dicUser->username,
	         dicUser->email);

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

	strcpy (dicFirstName, dicUser->username);
	strtok (dicFirstName, " ");

	/*create message*/
	snprintf (dicEmailBody, DIC_EMAIL_BODY_MAX_LENGTH + 1, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
	        "Welcome, ", dicFirstName, "!\n\n",
	        "You was registered at Olhar Discente with success.\n\n\n",
	        "You are reistered as ", dicUser->username, " and your login data are:\n\n",
	        "\tNickname: ", dicUser->nickname,
	        "\n\tPassword: ", dicUser->password,
	        "\n\n\nVisit us in here: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicEnglish\n",
	        "In majority of the e-mail systems this is a blue link and you can click. In other cases copy for your browser.\n\n\n",
	        "-------------------------------------------------------\n\n\n",
	        "Bem-vindo, ", dicFirstName, "!\n\n",
	        "Você foi registrado em Olhar Discente com sucesso.\n\n\n",
	        "Você está registrado como ", dicUser->username, " e seus dados de login são:\n\n",
	        "\tApelido: ", dicUser->nickname,
	        "\n\tSenha: ", dicUser->password,
	        "\n\n\nAcesse aqui: ", DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicPortuguese\n",
	        "Na maioria dos sistemas de e-mail isto é um link azul e é possível clicá-lo. Se este não é o caso copie para a barra do seu navegador.\n"
	        );

	/*Send email to new user*/
	sendMail (
		DIC_SMTP_CLIENT_DOMAIN,
		DIC_SMTP_SERVER_FULL_HOSTNAME,
		DIC_SMTP_SERVER_PORT,
		DIC_PRIMARY_ADMINISTRATOR_EMAIL, /*From Admin*/
		dicUser->email, /*To*/
		NULL, /*cc*/
		NULL, /*bcc*/
		"Olhar Discente - User Registered successfully", /*Subject*/
		dicEmailBody,   /*Body*/
		NULL  /*Attatchement*/
	);

	return dicOk;
}

/*$RCSfile: dicAcceptInvite.c,v $*/
