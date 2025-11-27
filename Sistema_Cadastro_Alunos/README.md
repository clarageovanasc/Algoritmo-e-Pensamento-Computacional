📝 Sistema de Cadastro de Alunos (Structs em C)

Desafio prático de programação desenvolvido para fixar o uso de Estruturas de Dados (struct) e validação de input do usuário. O programa simula o cadastro de um aluno, calculando automaticamente sua média e situação final.

🚀 Funcionalidades

O sistema solicita os dados do aluno e aplica regras de validação (Input Validation) para garantir a consistência das informações:

[x] Nome: Não aceita caracteres numéricos (apenas letras e símbolos).

[x] Matrícula: Deve estar entre 0 e 90000.

[x] Notas: Devem ser valores reais entre 0.0 e 10.0.

[x] Cálculo Automático: Gera a média aritmética simples.

[x] Situação: Define se o aluno está "Aprovado" (Média >= 6.0) ou "Reprovado".

💻 Estrutura do Código

O diferencial deste código é o uso de uma struct para agrupar os dados, simulando um objeto do mundo real:

struct Aluno {
    int matricula;
    char nome[50];
    float nota1;
    float nota2;
    float media;
};


Validação de Segurança

Foi implementada uma função dedicada para garantir que nomes não contenham números, utilizando a tabela ASCII indiretamente:

int nomeTemNumero(const char *nome) {
    // Percorre a string verificando se há dígitos de '0' a '9'
    // Retorna 1 (Erro) ou 0 (Ok)
}


🔧 Como Executar

Compile o código:

gcc main.c -o cadastro_alunos


Execute no terminal:

./cadastro_alunos


Interaja: Digite os dados solicitados. Tente digitar uma nota maior que 10 ou um número no nome para testar as travas de segurança!

Desenvolvido como exercício da disciplina de Algoritmos e Pensamento Computacional.
