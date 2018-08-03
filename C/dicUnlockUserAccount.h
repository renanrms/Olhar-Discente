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

#ifndef DIC_UNLOCKUSERACCOUNT_H
#define DIC_UNLOCKUSERACCOUNT_H "@(#)dicUnlockUserAccount.h $Revision$"

#include "dicErrors.h"

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
DicUnlockUserAccount (char*, char*, char*);

#endif 

/*$RCSfile$*/
