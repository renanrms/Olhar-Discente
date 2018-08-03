/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2016/1
 * Prof. Marcelo Luiz Drumond Lanza
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicRequestRegistration.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_REQUESTREGISTRATION_H
#define DIC_REQUESTREGISTRATION_H "@(#)dicRequestRegistration.h $Revision: 1.1 $"

#include "dicTypes.h"
#include "dicErrors.h"

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
DicRequestRegistration(char*, dicUserDataType*);

#endif 

/*$RCSfile: dicRequestRegistration.h,v $*/
