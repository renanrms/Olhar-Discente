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

void
DicShowCliHelp (dicLanguageType dicLanguage)
{
	if (dicLanguage == dicEnglish)
	{
		printf ("
\nSee portuguese help.\n
		        ");
	}
	else
	{
		printf ("
\n		Exibir ajuda: -h | --help [language=english | portuguese]
\n
\n		Executar a interface Ncurses: -N | --Ncurses [nickname=<apelido>] [language=english | portuguese]
\n
\n		Criar a configuração inicial do sistema: -C | --Configure  username=<nome completo> confirm-username=<nome completo> email=<endereço eletrônico> confirm-email=<endereço eletrônico> [language=english | portuguese]
\n
\n		Adicionar um usuário ao sistema: -a | --add  user=<apelido> username=<nome completo> confirm-username=<nome completo> email=<endereço eletrônico> confirm-email=<endereço eletrônico> profile=<administrator | professor | student> [language=english | portuguese]
\n
\n		Convidar um usuário para participar do sistema: -i | --invite user=<apelido> username=<nome completo> confirm-username=<nome completo> email=<endereço eletrônico> confirm-email=<endereço eletrônico> profile=<administrator | professor | student> [language=english | portuguese]
\n
\n		Aceitar um convite para participar do sistema: -t | --accept user=<apelido> [language=english | portuguese]
\n
\n		Rejeitar um convite para participar do sistema: -j | --reject user=<apelido> [language=english | portuguese]
\n
\n		Solicitar cadastramento no sistema: -n | --new username=<nome completo> confirm-username=<nome completo> email=<endereço eletrônico> confirm-email=<endereço eletrônico> friend-email=<endereço eletrônico> [language=english | portuguese]
\n
\n		Obter a lista de solicitações de cadastramento no sistema sob responsabilidade deste usuário: -q | --request user=<apelido> [language=english | portuguese]
\n
\n		Obter a lista com todas as solicitações de cadastramento no sistema: -Q | --Request user=<apelido> [language=english | portuguese]
\n
\n		Aprovar um pedido de cadastramento no sistema: -v | --approve user=<apelido> nickname=<apelido> [language=english | portuguese]
\n
\n		Reprovar um pedido de cadastramento no sistema: -d | --disapprove user=<apelido> nickname=<apelido> [language=english | portuguese]
\n
\n		Obter a lista de solicitações de desbloqueio: -U | --Unlocking user=<apelido>  [language=english | portuguese]
\n
\n		Bloquear a conta de um usuário do sistema: -l | --lock user=<apelido> [nickname=<apelido>] [language=english | portuguese]
\n
\n		Desbloquear a conta de um usuário do sistema: -u | --unlock user=<apelido> [nickname=<apelido>] [language=english | portuguese]
\n
\n		Alterar a senha de um usuário do sistema: -p | --password  user=<apelido> [nickname=<apelido>] [language=english | portuguese]
\n
\n		Criar uma senha temporária para um usuário do sistema: -r | --reset user=<apelido> [nickname=<apelido>] [language=english | portuguese]
\n
\n		Alterar o nome de um usuário do sistema: -m | --modify user=<apelido> [nickname=<apelido>] username=<nome completo> confirm-username=<nome completo> [language=english | portuguese]
\n
\n		Alterar o endereço eletrônico de um usuário do sistema: -e | --edit user=<apelido> [nickname=<apelido>] email=<endereço eletrônico> confirm-email=<endereço eletrônico> [language=english | portuguese]
\n
\n		Confirmar a alteração do endereço eletrônico: -c | --confirm user=<apelido> key=<chave>  [language=english | portuguese]
\n
\n		Alterar o perfil de um usuário: -g | --group user=<apelido> nickname=<apelido> profile=<administrator | professor | student> [language=english | portuguese]
\n		O perfil poderá ser um dos três possíveis ou qualquer combinção dos três.
\n
\n		Obter todos os usuários: -s | --show [language=english | portuguese]
\n
\n		Buscar informações sobre usuários: -S | --Search [username=<nome completo ou parte do nome>] [email=<endereço eletrônico ou parte do endereço eletrônico>] [profile=<administrator | professor | administrador_professor | student | adminstrador_student | professor_student | adminstrador_professor_student> [language=english | portuguese]
\n		        ");
	}
}

/*$RCSfile$*/
