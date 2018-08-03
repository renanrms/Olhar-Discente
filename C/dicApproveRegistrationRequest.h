/* Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2016/1
 * 
 * $Author: renan.passos $
 * $Date: 2016/08/30 14:05:18 $
 * $Log: dicApproveRegistrationRequest.h,v $
 * Revision 1.1  2016/08/30 14:05:18  renan.passos
 * Initial revision
 *
 */

#ifndef DIC_APPROVEREGISTRATIONREQUEST_H
#define DIC_APPROVEREGISTRATIONREQUEST_H "@(#)dicApproveRegistrationRequest.h $Revision: 1.1 $"

#include "dicErrors.h"

/*
 * dicErrorType
 * DicApproveRegistrationRequest (char*, char*);
 *
 * Arguments:
 * char* - nickname of responsible user (I)
 * char* - nickname of requesting (I)
 *
 * Returned values:
 * dicOk - registration request was approved successfully
 * dicInvalidArgument - one of the received arguments is NULL pointer
 * dicUserAlreadyRegistered - the user is in active state
 * dicNotRequestingUser - user is not requesting or your requesting has expired
 * dicNotResponsibleUser - user is nor the responsible for this request
 *
 * Description:
 * This function approves a registration request if the data received corresponds to requesting user
 * and your responsible user and the request is not expired, and then send an email for the requesting.
 */
dicErrorType
DicApproveRegistrationRequest (char*, char*);

#endif 

/*$RCSfile: dicApproveRegistrationRequest.h,v $*/
