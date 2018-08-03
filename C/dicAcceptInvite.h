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

#ifndef DIC_ACCEPTINVITE_H
#define DIC_ACCEPTINVITE_H "@(#)dicAcceptInvite.h $Revision$"

#include "dicErrors.h"
#include "dicTypes.h"

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
DicAcceptInvite (char*, dicUserDataType*);

#endif 

/*$RCSfile$*/
