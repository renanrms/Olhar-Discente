/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicRequestRegistration.c,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "dicRequestRegistration.h"
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
 * DicRequestRegistration(char*, dicUserDataType*);
 *
 * Arguments:
 * char* - email of user responsible for approve the registration
 * dicUserDataType* - structure containing password, profile, username, email, fields and yours confirmations
 *
 * Returned values:
 * dicOk - registration request invited successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicInvalidEmail - email is invalid
 * dicInvalidEmailConfirmation - email confirmation differs from email
 * dicUserEmailAlreadyRegistered - email is already registered
 * dicInvalidPassword - invalid password
 * dicInvalidPasswordConfirmation - password confirmation differs from password
 * dicInvalidUsername - username is invalid
 * dicEmptyLastName - username has only one name
 * dicOverLengthNames - very large names to create nickname
 * dicIcorrectPassword - user authentication failed
 * dicUserEmailNotFound - the email of responsible user is not registered
 * dicNotPermitedProfileRequest - is not permited request the profile for this user
 *
 * Description:
 * This function verifys the validity of data, verifys if the email of responsible user is register
 * and the email of requesting user is not register, creates a nickname and save data in users file,
 * and then, save de requesting in requesting file and send an email for responsible user.
 */
dicErrorType
DicRequestRegistration(char *dicResponsibleEmail, dicUserDataType *dicRequestingUser)
{
	FILE *dicRequestingUsersFile;
	FILE *dicUsersFile;

	dicUserDataType dicUser;
	dicUserDataType dicResponsibleUser = NULL;
	char dicResponsibleFirstName [DIC_USERNAME_MAX_LENGTH];

	char dicFirstNickname [DIC_NICKNAME_MAX_LENGTH];
	char dicSecondNickname [DIC_NICKNAME_MAX_LENGTH];
	char dicEncodedPassword [DIC_PASSWORD_MAX_LENGTH];
	char dicEmailBody [DIC_EMAIL_BODY_MAX_LENGTH];

	time_t dicAbsoluteValidityTime;

	unsigned char dicFoundEmail = 0; /*flag variable*/

	dicErrorType dicReturnCode;

	/*Check requesting user email*/
	dicReturnCode = DicCheckEmail (dicRequestingUser->email, DIC_EMAIL_CARACTERS, DIC_EMAIL_MIN_LENGTH, DIC_EMAIL_MAX_LENGTH);
	if (dicReturnCode != dicOk)
		return dicReturnCode;
	if (strcmp (dicRequestingUser->email, dicRequestingUser->emailConfirmation) != 0)
		return dicInvalidEmailConfirmation;	

	/*Check requesting user password*/
	if (strlen (dicRequestingUser->password) != 0)
	{
		dicReturnCode = DicCheckStringField (dicRequestingUser->password, DIC_PASSWORD_CARACTERS, DIC_PASSWORD_MIN_LENGTH, DIC_PASSWORD_MAX_LENGTH);
		if (dicReturnCode != dicOk)
			return dicInvalidPassword;
	}
	if (strcmp (dicRequestingUser->password, dicRequestingUser->passwordConfirmation))
		return dicInvalidPasswordConfirmation;

	/*Check requesting user username*/
	dicReturnCode = DicCheckStringField (dicRequestingUser->username, DIC_USERNAME_CARACTERS, DIC_USERNAME_MIN_LENGTH, DIC_USERNAME_MAX_LENGTH);
	if (dicReturnCode != dicOk)
		return dicInvalidUsername;

	/*Create nickname*/
	dicReturnCode = DicCreateNickname (dicRequestingUser->username, dicFirstNickname, dicSecondNickname);
	if (dicReturnCode != dicOk)
		return dicReturnCode;
	dicRequestingUser->nickname = dicFirstNickname;

	DicGetUsers (&dicUser);
	/*search user email and verifys requesting user email and nickname*/
	while (dicUser != NULL)
	{
		if (!strcmp (dicUser->email, dicRequestingUser->email))
			return dicUserEmailAlreadyRegistered;

		if (!strcmp (dicUser->email, dicResponsibleEmail))
			dicResponsibleUser = dicUser;

		if (!strcmp (dicUser->nickname, dicRequestingUser->nickname))
			dicRequestingUser->nickname = dicSecondNickname;

		dicRequestingUser->userId = dicUser->userId;

		dicUser = dicUser->next;
	}
	if (dicResponsibleUser == NULL)
		return dicUserEmailNotFound;

	/*verifys if the profile of request is permited*/
	if (dicRequestingUser->profile == dicTeacher || dicRequestingUser->profile == dicStudent_teacher)
	{
		if (dicResponsibleUser->profile == dicStudent)
			return dicNotPermitedProfileRequest;
	}
	else if (dicRequestingUser->profile != dicStudent)
		return dicNotPermitedProfileRequest;

	DicEncodePasswordWithSpecificAlgorithm(dicRequestingUser->password, dicSha512, dicEncodedPassword);

	/*open users data file*/
	dicUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_USERS_DATA_FILENAME), "a");

	/*userId:nickname::profile:username:email\n*/
	fprintf (dicUsersFile, "%llu:%s::%i:%s:%s\n", 
	         dicRequestingUser->userId,
	         dicRequestingUser->nickname,
	         dicRequestingUser->profile,
	         dicRequestingUser->username,
	         dicRequestingUser->email);

	fclose (dicUsersFile);

	/*open requesting users data file*/
	dicRequestingUsersFile = fopen (DicGetAbsolutFileName (DIC_DATA_DIRECTORY, DIC_REQUESTING_USERS_DATA_FILENAME), "a");

	dicAbsoluteValidityTime = time (NULL) + DIC_REQUESTING_EXPIRATION_TIME;
	/*<validity><userId><encoded password>*/
	fwrite (&(dicAbsoluteValidityTime), sizeof (time_t), 1, dicRequestingUsersFile);
	fwrite (&(dicResponsibleUser->userId), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
	fwrite (&(dicRequestingUser->userId), sizeof (dicUserIdentifierType), 1, dicRequestingUsersFile);
	fwrite (dicEncodedPassword, sizeof (char), DIC_PASSWORD_MAX_LENGTH, dicRequestingUsersFile);

	fclose (dicRequestingUsersFile);

	strcpy (dicResponsibleFirstName, dicResponsibleUser->username);
	strtok (dicResponsibleFirstName, " ");

	sprintf (dicEmailBody, DIC_EMAIL_BODY_MAX_LENGTH + 1, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
	        "Hi, ", dicResponsibleFirstName, "!\n\n",
	        "You was indicated by ", dicRequestingUser->username, " for approve your registration as ",
	        DicGetUserProfileString (dicRequestingUser->profile, dicEnglish), " at Olhar Discente.\n\n\n",
	        "For approve or disapprove the requesting access the site:\n",
	        DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicEnglish\n",
	        "In majority of the e-mail systems this is a blue link and you can click. In other cases copy for your browser.\n\n\n",
	        "-------------------------------------------------------\n\n\n",
	        "Olá, ", dicResponsibleFirstName, "!\n\n",
	        "Você foi indicado por ", dicRequestingUser->username, " para aprovar seu cadastro como ",
	        DicGetUserProfileString (dicRequestingUser->profile, dicPortuguese), " no Olhar Discente.\n\n\n",
	        "Para aprovar ou desaprovar esta requisição acesse o site:\n",
	        DIC_WEB_SERVER_URL, "CGIs/dicMain.cgi?dicLanguage=dicPortuguese\n",
	        "Na maioria dos sistemas de e-mail isto é um link azul e é possível clicá-lo. Se este não é o caso copie para a barra do seu navegador.\n"
	        );

	/*Send email to responsible user*/
	sendMail (
		DIC_SMTP_CLIENT_DOMAIN,
		DIC_SMTP_SERVER_FULL_HOSTNAME,
		DIC_SMTP_SERVER_PORT,
		DIC_PRIMARY_ADMINISTRATOR_EMAIL, /*From Admin*/
		dicUserData->email, /*To*/
		NULL, /*cc*/
		NULL, /*bcc*/
		"Olhar Discente - User Registration Request", /*Subject*/
		dicEmailBody,   /*Body*/
		NULL  /*Attatchement*/
	);

	return dicOk;
}

/*$RCSfile: dicRequestRegistration.c,v $*/
