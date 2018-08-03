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

#ifndef DIC_LOCKUSERACCOUNT_H
#define DIC_LOCKUSERACCOUNT_H "@(#)dicLockUserAccount.h $Revision$"

#include "dicTypes.h"
#include "dicErrors.h"

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
DicLockUserAccount (char*, char*);

#endif 

/*$RCSfile$*/
