/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author$
 * $Date$
 * $Log$
 */

#ifndef DIC_ADDUSER_H
#define DIC_ADDUSER_H "@(#)dicAddUser.h $Revision$"

#include "dicTypes.h"
#include "dicErrors.h"

/*
 * dicErrorType
 * DicAddUser (dicUserDataType*);
 *
 * Arguments:
 * dicUserDataType - structure containing username, password (empty or not) and confirmation, email and profile (I)
 *
 * Returned values:
 * dicOk - user was added successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicInvalidNickname - nickname is invalid
 * dicInvalidEmail - email is invalid
 * dicInvalidEmailConfirmation - email confirmation differs from email
 * dicUserEmailAlreadyRegistered - email is already registered
 * dicInvalidPassword - invalid password
 * dicInvalidPasswordConfirmation - password confirmation differs from password
 * dicInvalidUsername - username is invalid
 * dicIcorrectPassword - user authentication failed
 * dicEmptyLastName - username has only one name
 * dicOverLengthNames - very large names to create nickname
 *
 * Description:
 * This function verifys the validity of data, creates an nickname and
 * if it's the first user, register as administrator, 
 * else register with profile received and send an email to user.
 * If password is empty, an invite is send by email. 
 */
dicErrorType
DicAddUser (dicUserDataType*);

#endif 

/*$RCSfile$*/
