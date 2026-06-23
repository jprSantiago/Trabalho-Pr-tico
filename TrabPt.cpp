#include <iostream>
#include <fstream>

using namespace std;

// Estrutura com os dados de cada campeao de LOL.
struct campeoes{
    string nome;
    string classe;
    string regiao;
    string ano;
    float pickrate;
};

// Funçao de Busca Binaria para os nomes de campeoes.
int binaria(string nomes1[], string pesq, int pos_inicial, int pos_final){
    if(pos_inicial > pos_final) return -1;
    
    int meio = (pos_inicial + pos_final)/2;
    if(nomes1[meio] == pesq){
        return meio;
    }
    else if(pesq < nomes1[meio]){
        return binaria(nomes1, pesq, pos_inicial, meio - 1);
    }
    else{
        return binaria(nomes1, pesq, meio + 1, pos_final);
    }
}

// Declaraçao de que o Procedimento BUSCA ainda será feito, para poder ser usado no Procedimento Sequencial.
void BUSCA(int busca1, string pesq, int tam, campeoes perso[], string pesq2);

// Funçao de Busca Sequencial Para as Regioes dos Campeoes.
void sequencial(string regioes[], string regiao, int tamanho_original, campeoes perso[]){
    int definidor = 0;
    for(int i = 0; i < tamanho_original; i++){
        if(regiao == regioes[i]){
            definidor++; 
        }
    }
    char resposta;
    string desejo;
    if(definidor > 1){
        cout << "Foram Encontrados: " << definidor << " Campeoes" << endl;
        for(int i = 0; i < tamanho_original; i++){
            if(regiao == regioes[i]){
                cout << perso[i].nome << endl;
                cout << endl;
            }
        }
        string nada2 = "nada";
        cout << "Digite o nome do campeao que deseja" << endl;
        cin >> desejo;
        int buscador = 1;
        BUSCA(buscador, desejo, tamanho_original, perso, nada2);
        
    }
}

// Procedimento de Busca onde Retorna o Campeao Buscado.
void BUSCA(int busca1, string pesq, int tam, campeoes perso[], string pesq2){
    if(busca1 == 1 or busca1 == 2){
        string* vetorcomnomes = new string[tam];
        for(int i = 0; i < tam; i++){
            vetorcomnomes[i] = perso[i].nome;
        }
        int procura = binaria(vetorcomnomes, pesq, 0, tam - 1);
        if(procura == -1){
            cout << "Campeao nao encontrado!" << endl;
        }
        else{
            if(busca1 == 1){
                cout << perso[procura].nome << endl;
                cout << perso[procura].classe << endl;
                cout << perso[procura].regiao << endl;
                cout << perso[procura].ano << endl;
                cout << perso[procura].pickrate << endl;
            }
            else{
                // Buscar ambos os campeões
                int primeiro = binaria(vetorcomnomes, pesq, 0, tam - 1);
                int segundo = binaria(vetorcomnomes, pesq2, 0, tam - 1);
                
                if(primeiro == -1 || segundo == -1){
                    cout << "Um ou ambos os campeoes nao foram encontrados!" << endl;
                }
                else{
                    // Garantir que primeiro < segundo
                    if(primeiro > segundo){
                        int aux = primeiro;
                        primeiro = segundo;
                        segundo = aux;
                    }
                    
                    for(int i = primeiro; i <= segundo; i++){
                        cout << perso[i].nome << endl;
                        cout << perso[i].classe << endl;
                        cout << perso[i].regiao << endl;
                        cout << perso[i].ano << endl;
                        cout << perso[i].pickrate << endl;
                        cout << endl;
                    }
                }
            }
        }
        delete[] vetorcomnomes;
    }
    else{
        string *vetorcomregiao = new string[tam];
        for(int i = 0; i < tam; i++){
            vetorcomregiao[i] = perso[i].regiao;
        }
        sequencial(vetorcomregiao, pesq, tam, perso);
        delete[] vetorcomregiao;
    }
}

// Procedimento de Alocaçao quando o vetor de armazenamento de personagens enche.
void aloca_vetor(campeoes *&vet, int tamanho_novo, int &tamanho_antigo){
    campeoes *novo = new campeoes[tamanho_novo];
    for(int i = 0; i < tamanho_antigo; i++){
        novo[i].nome = vet[i].nome;
        novo[i].classe = vet[i].classe;
        novo[i].regiao = vet[i].regiao;
        novo[i].ano = vet[i].ano;
        novo[i].pickrate = vet[i].pickrate;
    }
    delete[] vet;

    vet = novo;
    tamanho_antigo = tamanho_novo;
}

//Procedimento de Organizaçao da Struct Campeoes para a ordem de lançamento(ano).
void selection_sort(campeoes *&perso, int tam, string *&vetorano){

    int menor;
    string aux_troca;
    campeoes aux;

    for (int i = 0; i < tam-1; i++) {
    menor = i;

   	for (int j = i + 1; j < tam; j++) {
   		if (vetorano[j] < vetorano[menor]){
   			menor = j;
   		}
   	}

   	aux_troca = vetorano[i];
    aux = perso[i];
   	vetorano[i] = vetorano[menor];
    perso[i] = perso[menor];
   	vetorano[menor] = aux_troca;
    perso[menor] = aux;
    }
}


int main(){

    string linha;
    char lixo;
    int capacidade = 0;
    campeoes *perso;
    int tamanho_vetor = 0;
    int total;
    int ordem;

    // Leitura do Arquivo LOL.csv.
    ifstream arquivo_csv("LOL.csv");

    if(not(arquivo_csv)){
        cout << "Erro" << endl;
    }

    else{  //Coleta basica de dados do arquivo para o programa, com armazenamento na matriz memoria, onde cada linha representa os dados de um personagem.
        getline(arquivo_csv, linha);
        arquivo_csv >> capacidade;
        arquivo_csv >> total;
        arquivo_csv >> ordem;
        arquivo_csv.ignore();
        perso = new campeoes[capacidade];

        for(int i = 0; i < capacidade; i++){ 
            getline(arquivo_csv, perso[i].nome, ',');
            getline(arquivo_csv, perso[i].classe, ',');
            getline(arquivo_csv, perso[i].regiao, ','); 
            getline(arquivo_csv, perso[i].ano, ',');
            arquivo_csv >> perso[i].pickrate;
            arquivo_csv >> lixo;
            arquivo_csv.ignore();
            tamanho_vetor++;

            // Verificaçao de tamanho e se o vetor encheu.
            if(capacidade <= total and capacidade == tamanho_vetor){
                if((capacidade + 10) > total){
                    int antigo = capacidade;
                    capacidade = total;
                    aloca_vetor(perso, capacidade, antigo);
                }
                else{
                    int antigo = capacidade;
                    capacidade += 10;
                    aloca_vetor(perso, capacidade, antigo);
                }
            }
        }
    }
    int entrada = 0;
    int busca1 = 0;
    string nada = "nada";

    // PARA A INSERÇAO DE UM NOVO CAMPEAO, ALOCAR DINAMICAMENTE MAIS 1 DE ESPAÇO POR VEZ.
    // INSERÇAO E RETIRADA DEVE SER FEITO ORDENADAMENTE.
    // APOS A INSERÇAO DEVE SER CAPAZ SALVAR AS ALTERAÇOES.
    // A REMOÇAO PODE SER APENAS UMA MARCAÇAO E NAO UMA REMOÇAO EM SI.

    // Pedido ao usuario se ele quer adicionar, buscar ou remover um campeao.
    
    bool sair = false;// Variavel para o loop de escolha do usuario.
    while(!sair){// Loop do sistema.
        cout << "Digite [1] para buscar" << endl << "Digite [2] para adicionar" << endl << "Digite [3] para remover" << endl << "Digite [4] para reordenar" << endl << "Digite [5] para salvar" << endl << "Digite [6] para sair " << endl << "Digite sua opção:";
        cin >> entrada;
        //Entrada para Buscar um campeao em específico pelo nome ou regiao.
        if(entrada == 1){
            // Pedido ao usuario se ele quer buscar pela regiao ou nome.
            cout << "Digite [1] para buscar pelo nome"<< endl << "digite [2] para buscar pela regiao"<< endl << "[3] se deseja ver sequência de campeões" << endl << "Digite sua opção: ";
            cin >> busca1;

            // Validaçao da entrada do usuario.
            if(busca1 != 1 and busca1 != 2 and busca1 != 3){
                cout << "Escolha inválida. Selecione os números [1], [2] ou [3]." << endl;
                busca1 = 0;
                cin >> busca1;
            }

            // Entrada para buscar pelo nome do campeao.
            else if(busca1 == 1){
                if(ordem==1){//Ordenado por nome.
                string nome;
                cout << "Digite o nome do campeão: " << endl;
                cin >> nome;
                // Chamado da Funçao Busca pelo nome.
                BUSCA(busca1, nome, tamanho_vetor, perso, nada);
                }
                else{//Ordenado por ano.
                    selection_sort(perso, tamanho_vetor, perso[0].nome);//Alterar para ordenar por nome.
                    string nome;
                    cout << "Digite o nome do campeão: " << endl;
                    cin >> nome;
                    BUSCA(busca1, nome, tamanho_vetor, perso, nada);
                    selection_sort(perso, tamanho_vetor, perso[0].ano);//Criar função de criação de vetor e passar por referência.
                }
            }
            else if(busca1 == 2){// Entrada para buscar pela regiao do campeao.
                string regiao;
                cout << "Digite o nome da região: " << endl;
                cin >> regiao;
                // Chamado da funçao Busca pela regiao.
                BUSCA(busca1, regiao, tamanho_vetor, perso, nada);
            }
            else if(busca1 == 3){// Entrada para buscar uma quantidade limitada de campeoes.
                if(ordem==1){//Ordenado por nome.
                    string nome1, nome2;
                    cout << "Digite o nome do primeiro campeão: " << endl;
                    cin >> nome1;
                    cout << "Digite o nome do segundo campeão: " << endl;
                    cin >> nome2;
                    BUSCA(busca1, nome1, tamanho_vetor, perso, nome2);
                }
                else{//Ordenado por ano.
                    cout << "Para buscar por nome, os campeões serão considerdos em ordem alfabética." << endl;
                    selection_sort(perso, tamanho_vetor, perso[0].nome);//Alterar para ordenar por nome.
                    string nome1, nome2;
                    cout << "Digite o nome do primeiro campeão: " << endl;
                    cin >> nome1;
                    cout << "Digite o nome do segundo campeão: " << endl;
                    cin >> nome2;
                    BUSCA(busca1, nome1, tamanho_vetor, perso, nome2);
                    selection_sort(perso, tamanho_vetor, perso[0].ano);//Criar função de criação de vetor e passar por referência.
                }

               /*
                //Campeoes em ordem de lançamento(ano).
                string *vetorcomano = new string[tamanho_vetor];
                for(int i = 0; i < tamanho_vetor; i++){
                    vetorcomano[i] = perso[i].ano;
                }

                //Chamada da funçao para organizar a struct em ordem de lançamento(ano).
                selection_sort(perso, tamanho_vetor, vetorcomano);
               
                cout << "Qual ano deseja ver? " << endl;
                string ano1;
                cin >> ano1;
                cout << "Deseja ver ate algum outro ano?(S/N) " << endl;
                char resposta2;
                cin >> resposta2;

                //Quantidade limitada de campeoes informado pelo usuário.
                if(resposta2 == 'S'){
                    cout << "Ate qual Ano? " << endl;
                    string ano2;
                    cin >> ano2;

                    //Encontrando a Posiçao dos dois anos.
                    int indice1 = binaria(vetorcomano, ano1, 0, tamanho_vetor);
                    int indice2 = binaria(vetorcomano, ano2, 0, tamanho_vetor);

                    //Impressao no terminal de todos os personagens dos anos em específicos.
                    while(perso[indice1].ano == ano1){
                        cout << perso[indice1].nome << endl;
                        cout << perso[indice1].classe << endl;
                        cout << perso[indice1].regiao << endl;
                        cout << perso[indice1].ano << endl;
                        cout << perso[indice1].pickrate << endl;
                        cout << endl;
                        indice1++;
                    }

                    while(perso[indice2].ano == ano2){
                        cout << perso[indice2].nome << endl;
                        cout << perso[indice2].classe << endl;
                        cout << perso[indice2].regiao << endl;
                        cout << perso[indice2].ano << endl;
                        cout << perso[indice2].pickrate << endl;
                        cout << endl;
                        indice2++;
                    }
                }

                //Printado no terminal todos os personagens em ordem de lançamento(ano).
                else{
                    int indice1 = binaria(vetorcomano, ano1, 0, tamanho_vetor);
                    while(perso[indice1].ano == ano1){
                        cout << perso[indice1].nome << endl;
                        cout << perso[indice1].classe << endl;
                        cout << perso[indice1].regiao << endl;
                        cout << perso[indice1].ano << endl;
                        cout << perso[indice1].pickrate << endl;
                        cout << endl;
                        indice1++;
                    }
                }
                delete[] vetorcomano;
            }*/
        }
        //Entrada para adicionar um campeão.
        else if(entrada == 2){
            campeoes novo_campeao;
            cout << "Digite o nome, a classe, a região, o ano de lançamento e o pickrate do campeão a ser adicionado: " << endl;
            cout << "Ex: Aatrox,Lutador,Runeterra,2013,6.3; " << endl;
            cin.ignore();
            getline(cin, novo_campeao.nome, ',');
            getline(cin, novo_campeao.classe, ',');
            getline(cin, novo_campeao.regiao, ',');
            getline(cin, novo_campeao.ano, ',');
            cin >> novo_campeao.pickrate;
            cin.ignore();
        }

        //Entrada para remover um campeão.
        else if(entrada == 3){
            string nome_remover;
            cout << "Digite o nome do campeão a ser removido: " << endl;
            cin >> nome_remover;
        }
        
        //Entrada para reordenar os campeões.
        else if(entrada == 4){
            cout << "Digite [1] para reordenar em ordem alfabética"<< endl <<" digite [2] para reordenar por ano de lançamento " << endl << "Digite sua opção: ";
            cin >> ordem;
            cin.ignore();
            busca1 = 2;

            if(ordem != 1 and ordem != 2){
                cout << "Escolha inválida. Selecione os números [1] ou [2]." << endl;
                ordem = 0;
                cin >> ordem;
            }
            
            //Reordenando campeoes em ordem alfabética.
            else if(ordem == 1){
                string *vetorcomnomes = new string[tamanho_vetor];
                for(int i = 0; i < tamanho_vetor; i++){
                    vetorcomnomes[i] = perso[i].nome;
                }

                //Chamada da funçao para organizar a struct em ordem alfabética.
                selection_sort(perso, tamanho_vetor, vetorcomnomes);
                delete[] vetorcomnomes;
            }

            //Reordenando campeoes em ordem de lançamento(ano).
            else{
                string *vetorcomano = new string[tamanho_vetor];
                for(int i = 0; i < tamanho_vetor; i++){
                    vetorcomano[i] = perso[i].ano;
                }

                //Chamada da funçao para organizar a struct em ordem de lançamento(ano).
                selection_sort(perso, tamanho_vetor, vetorcomano);
                delete[] vetorcomano;
            }
        }
        
        //Entrada para salvar as alterações feitas no programa.
        else if(entrada == 5){
            //Salvar as alterações feitas no programa.
        }

        //Entrada para sair do programa.
        else if(entrada == 6){
            cout << "Saindo do programa." << endl;
            sair = true;
        }
       
        //Entrada inválida.
        else{
            cout << "Escolha inválida! "<< endl <<" Selecione os números [1], [2], [3], [4], [5] ou [6]." << endl <<" Digite sua opção: ";
        }
    }
   
    arquivo_csv.close();
    delete[] perso;
    return 0;
}