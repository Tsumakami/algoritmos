#include <vector>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>

using namespace std;

#define TIPO CLIENTE

typedef struct {
    string status;
    int  cod_cliente;
    string nome;
    string endereco;
    string bairro;
    string cidade;
    string uf;
    string cep;
} CLIENTE ;

struct ARVORE{
    ARVORE *esquerda;
    TIPO *informacao;
//    int    codigo;
    ARVORE *direita;
} ;


ARVORE *P;
CLIENTE cadastro;

struct ARVORE *insere(ARVORE *tree, TIPO *informacao){
    cout << informacao->nome << endl;
    if(tree == NULL){
        tree->informacao = informacao;
    }else if(informacao->nome < tree->informacao->nome){
        tree->esquerda = insere(tree->esquerda, informacao);
    }else if(informacao->nome > tree->informacao->nome){
        tree->direita = insere(tree->direita, informacao);
    }
    return tree;
}

struct ARVORE *GetMax(ARVORE *tree){
    if (tree->direita == NULL)   {
        P=tree;
        tree = tree->esquerda;
    }else{
        tree->direita = GetMax(tree->direita);
    }
    return tree;
}
struct ARVORE *retira(ARVORE *tree, string nome){  //Preestststringif (tree==NULL)
    if(tree == NULL){
         cout << "Arvore vazia" << endl;
    }
    else{
        if (nome == tree->informacao->nome)
        {
            if (tree->esquerda==NULL)
            {
                tree = tree->direita;
            }
            else
            {
                if (tree->direita==NULL)
                {
                    tree = tree->esquerda;
                }
                else
                {
                    tree->esquerda = GetMax(tree->esquerda);
                    tree->informacao = P->informacao;
                }
//                free(P);
            }
        }
        else
        {
            if ( nome < tree->informacao->nome)
            {
                tree->esquerda = retira(tree->esquerda, nome);
            }
            else
            {
                tree->direita = retira(tree->direita, nome);
            }
        }
    }
    return tree;
}

void mostra(void) {
    if (cadastro.status != "*") {
        cout << endl << "Codigo Nome                                Endereco " << endl;
        cout << right << setw(6) << cadastro.cod_cliente <<" "<<left << setw(35) <<  cadastro.nome <<" "<<setw(35) << cadastro.endereco << endl;
        cout << "       " << setw(35) << cadastro.bairro <<" " << setw(35) << cadastro.cidade << endl;
        cout << "       " << cadastro.uf <<" "<< setw(10)<< cadastro.cep << endl;
    }
}

void infixa ( ARVORE *tree )
{
    if ( tree != NULL )
    {
        infixa(tree->esquerda ); ///perc sub-arvore esquerda
        mostra();
//        cout << tree->informacao << " ";
        infixa(tree->direita); ///perc rec. sub-arv direita
    }
}

void apresentacao_tela() {
    system ("clear");
    cout << setfill('-');
    cout << setw(79) << "-" << endl;
    cout << setw(49) << "LISTA DE CADASTROS" << setw(30) << "-" << endl;
    cout << setw(79) << "-" << endl << endl;
}

void ler_cliente(int codigo) {
    apresentacao_tela();
    string aux;
    getline(cin, aux);
    cadastro.status = "I";
    cadastro.cod_cliente = ++codigo;
    cout << "Nome: ";
    getline(cin,aux);
    cadastro.nome = aux;
    cout << "Endereco: ";
    getline(cin, cadastro.endereco);
    cout << "Bairro: ";
    getline(cin, cadastro.bairro);
    cout << "Cidade: ";
    getline(cin, cadastro.cidade);
    cout << "UF: ";
    getline(cin, cadastro.uf);
    cout << "Cep: ";
    getline(cin, cadastro.cep);
}

void excluir(void) {
    cadastro.status = '*';
}

int busca(ARVORE *tree, string informacao)
{
    int caminho;
    if(tree == NULL)
    {
        caminho = -1;
    }
    else
    {
        if ( informacao < tree->informacao->nome )
        {
            busca(tree->esquerda, informacao);
        }
        else if ( informacao > tree->informacao->nome )
        {
            busca(tree->direita, informacao);
        }
        else if(informacao == tree->informacao->nome)
        {
            caminho = tree->informacao->cod_cliente;
        }
    }
    return caminho;
}

int main (void) {
    P = NULL;
    ARVORE *raiz = NULL;
    string nome;
    string nome_minusculo;
    char status;

    //Arquivos.
    int retorno = 1;

    fstream arquivo;
    arquivo.open ("cadastro.dat", ios::in | ios::out | ios::binary);

    if (arquivo.is_open()) {
        //Joga  na árvore binaria todos os clientes já cadastrados.
        arquivo.clear();
        arquivo.seekg (0,ios::end);

        int tamanho = arquivo.tellg()/sizeof(CLIENTE); //Numero de cadastros feitos.
        if (tamanho != 0) {
            arquivo.clear();
            arquivo.seekg (0,ios::beg);
            while (arquivo.read((char *) &cadastro, sizeof(CLIENTE))) {
                status = ' '; //cadastro.getStatus();
                if (status != '*') {
//                    nome_minusculo = "";
//                    nome = cadastro.nome;
//                    for (int i = 0; i < (int)nome.length(); i++)
//                        nome_minusculo += (char)(tolower(nome[i]));
                    raiz= insere (raiz, &cadastro);
                }
            }
        }


        while (retorno != 0) {
            apresentacao_tela();

            cout << "Qual é a sua opcao: (1)Inserir (2)Excluir (3)Listar (4)Sair\n";
            cin >> retorno;


            if (retorno == 1) {//Insere cliente
                cout << sizeof(CLIENTE) << endl;
                arquivo.clear();
                arquivo.seekg (0,ios::end);
                ler_cliente(arquivo.tellg() /sizeof(CLIENTE));
                arquivo.write ((char *) &cadastro, sizeof (CLIENTE));

                //Insere na árvore.
                raiz = insere(raiz, &cadastro);
            }

            else if (retorno == 2) { //Excluir um cliente.
                cout <<  endl << "Qual cliente voce deseja excluir? " << endl;
                string nomee;
                //Mostra todos os clientes
                arquivo.clear();
                arquivo.seekg (0,ios::beg);
                while (arquivo.read((char *) &cadastro, sizeof(CLIENTE))) {
                    mostra();
                }
                cout << endl << "Digite o codigo do cliente: ";
                cin >> nomee;

                //Exclui da árvore.
                raiz = retira (raiz, nomee);

                //Exclui do arquivo.
                arquivo.clear();
                int codigoo = busca(raiz, nomee);
                arquivo.seekg(((codigoo-1) * sizeof(CLIENTE)));
                excluir();
                arquivo.write ((char *) &cadastro, sizeof (CLIENTE));

                system ("PAUSE");
            }


            else if (retorno == 3) { //Mostra clientes.
                arquivo.clear();//Limpa as variáveis.
                arquivo.seekg (0,ios::beg);//Posiciona no início.
                while (arquivo.read((char *) &cadastro, sizeof(CLIENTE))) {
                    mostra();
                }
                cout << endl;
                system ("PAUSE");
            }
            else { //sair
               retorno=0;
            }
        }
    } else {
        cout << "Incapaz de abrir/criar arquivo!!" << endl;
    }

    return 0;
}