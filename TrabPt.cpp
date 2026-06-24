#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>

using namespace std;

// Estrutura com os dados de cada campeao de LOL.
struct campeoes{
    string nome;
    string classe;
    string regiao;
    string ano;
    float pickrate;
    
};

//Função para gravar as alterações no arquivo CSV.
void Gravar_csv(campeoes *perso, int tamanho_vetor, int capacidade, int ordem){
    ofstream arquivo2_csv("LOL.csv");
    if(not(arquivo2_csv)){
        cout << "Erro ao abrir o arquivo para gravação." << endl;
        return;
    }
    arquivo2_csv << "#nome,classe,regiao,ano de lançamento,pickrate em %;" << endl;
    arquivo2_csv << capacidade << endl;
    arquivo2_csv << tamanho_vetor << endl;
    arquivo2_csv << ordem << endl;

    for(int i = 0; i < tamanho_vetor; i++){
        arquivo2_csv << perso[i].nome << "," 
                    << perso[i].classe << "," 
                    << perso[i].regiao << "," 
                    << perso[i].ano << "," 
                    << perso[i].pickrate << ";";
        if(i < tamanho_vetor - 1){
            arquivo2_csv << endl;
        }
    }

    arquivo2_csv.close();
}

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

// Procedimento de Busca onde Retorna o Campeao Buscado através do redirecionamento da busca correta.
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
void selection_sort(campeoes *&perso, int tam, string *&vetor_pivo){

    int menor;
    string aux_troca;
    campeoes aux;

    for (int i = 0; i < tam-1; i++) {
    menor = i;

   	for (int j = i + 1; j < tam; j++) {
   		if (vetor_pivo[j] < vetor_pivo[menor]){
   			menor = j;
   		}
   	}

   	aux_troca = vetor_pivo[i];
    aux = perso[i];
   	vetor_pivo[i] = vetor_pivo[menor];
    perso[i] = perso[menor];
   	vetor_pivo[menor] = aux_troca;
    perso[menor] = aux;
    }
}

//Procedimento de Ordenaçao por Inserçao.
void shell_sort(campeoes *&perso, int tamanho){
    
    int gaps[8] = {1, 4, 10, 23, 57, 132, 301, 701};
    int pos_gap = 7;
    while (gaps[pos_gap] > tamanho) {
        pos_gap--;
    }    
    string value;
    campeoes aux;
    int j;
    while ( pos_gap >= 0 ){
        int gap = gaps[pos_gap];

        for (int i = gap; i < tamanho; i++) {
            value = perso[i].nome;
            aux = perso[i];
            j = i;
            while ((j >= gap) and (value < perso[j - gap].nome)) {
                perso[j].nome = perso[j - gap].nome;
                perso[j] = perso[j - gap];
                j = j - gap;
            }
            perso[j].nome = value;
            perso[j] = aux;
        }

        pos_gap--;
    }
}

//Procedimento de Ordenaçao onde redireciona para a ordenaçao correta.
void ORDENACAO(int qual_ordenacao, campeoes perso[], int tamanho){

    if(qual_ordenacao == 1){
        string *vetorcomnomes = new string[tamanho];
        for(int i = 0; i < tamanho; i++){
            vetorcomnomes[i] = perso[i].nome;
        }
        selection_sort(perso, tamanho, vetorcomnomes);
        delete[] vetorcomnomes;
    }
    else{
        string *vetorcomano = new string[tamanho];
        for(int i = 0; i < tamanho; i++){
            vetorcomano[i] = perso[i].ano;
        }
        selection_sort(perso, tamanho, vetorcomano);
        delete[] vetorcomano;
    }
}

//Procedimento que deixa as letras em Maiúsculo.
void maiusculo(string &para_transformar){
    for (int i = 0; i < para_transformar.length(); i++) {
        para_transformar[i] = toupper(para_transformar[i]);
    }
}

//Procedimento que exclui um campeao.
void remover(string nome_remocao, campeoes *&perso, int ordem, int tamanho){
    if(ordem == 1){
        string *vetorcomnomes =  new string[tamanho];
        for(int i = 0; i < tamanho; i++){
            vetorcomnomes[i] = perso[i].nome;
        }
        int indice = binaria(vetorcomnomes, nome_remocao, 0, tamanho - 1);
        perso[indice].nome = "";
        perso[indice].classe = "";
        perso[indice].regiao = "";
        perso[indice].ano = "";
        perso[indice].pickrate = 0;
        aloca_vetor(perso, tamanho - 1, tamanho);
        delete[] vetorcomnomes;
    }
    else{
        int qual = 1;
        ORDENACAO(qual, perso, tamanho);
        string *vetorcomnomes =  new string[tamanho];
        for(int i = 0; i < tamanho; i++){
            vetorcomnomes[i] = perso[i].nome;
        }
        int indice = binaria(vetorcomnomes, nome_remocao, 0, tamanho - 1);
        perso[indice].nome = "";
        perso[indice].classe = "";
        perso[indice].regiao = "";
        perso[indice].ano = "";
        perso[indice].pickrate = 0;
        aloca_vetor(perso, tamanho - 1, tamanho);
        delete[] vetorcomnomes;
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

    
    // INSERÇAO E RETIRADA DEVE SER FEITO ORDENADAMENTE.
    // A REMOÇAO PODE SER APENAS UMA MARCAÇAO E NAO UMA REMOÇAO EM SI.

    // Pedido ao usuario se ele quer adicionar, buscar ou remover um campeao.
    // Variavel para o loop de escolha do usuario.
    bool sair = false;
    // Loop do sistema.
    while(!sair){

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

                //Ordenado por nome.
                if(ordem==1){
                string nome;
                cout << "Digite o nome do campeão: " << endl;
                cin >> nome;
                maiusculo(nome);
                
                // Chamado da Funçao Busca pelo nome.
                BUSCA(busca1, nome, tamanho_vetor, perso, nada);
                }

                //Ordenado por ano.
                else{
                    int qual = 1;
                    ORDENACAO(qual, perso, tamanho_vetor);
                    string nome;
                    cout << "Digite o nome do campeão: " << endl;
                    cin >> nome;
                    maiusculo(nome);
                    int busca2 = 1;
                    BUSCA(busca2, nome, tamanho_vetor, perso, nada);
                    qual = 2;
                    ORDENACAO(qual, perso, tamanho_vetor);
                }
            }

            // Entrada para buscar pela regiao do campeao.
            else if(busca1 == 2){
                string regiao;
                cout << "Digite o nome da região: " << endl;
                cin >> regiao;
                maiusculo(regiao);
                // Chamado da funçao Busca pela regiao.
                BUSCA(busca1, regiao, tamanho_vetor, perso, nada);
            }

            // Entrada para buscar uma quantidade limitada de campeoes.
            else if(busca1 == 3){

                //Ordenado por nome.
                if(ordem==1){
                    string nome1, nome2;
                    cout << "Digite o nome do primeiro campeão: " << endl;
                    cin >> nome1;
                    maiusculo(nome1);
                    cout << "Digite o nome do segundo campeão: " << endl;
                    cin >> nome2;
                    maiusculo(nome2);
                    BUSCA(busca1, nome1, tamanho_vetor, perso, nome2);
                }

                //Ordenado por ano.
                else{
                    cout << "Para buscar por nome, os campeões serão considerdos em ordem alfabética." << endl;
                    int qual = 1;
                    ORDENACAO(qual, perso, tamanho_vetor);//Alterar para ordenar por nome.
                    string nome1, nome2;
                    cout << "Digite o nome do primeiro campeão: " << endl;
                    cin >> nome1;
                    maiusculo(nome1);
                    cout << "Digite o nome do segundo campeão: " << endl;
                    cin >> nome2;
                    maiusculo(nome2);
                    BUSCA(busca1, nome1, tamanho_vetor, perso, nome2);
                    qual = 2;
                    ORDENACAO(qual, perso, tamanho_vetor);
                }
            }
        }

        //Entrada para adicionar um campeão.
        else if(entrada == 2){
            if(ordem == 1){
                int antigo = tamanho_vetor;
                tamanho_vetor++;
                aloca_vetor(perso, tamanho_vetor, antigo);
                campeoes novo_campeao;
                cout << "Digite o nome, a classe, a região, o ano de lançamento e o pickrate do campeão a ser adicionado: " << endl;
                cout << "Ex: Aatrox,Lutador,Runeterra,2013,6.3; " << endl;
                cin.ignore();
                getline(cin, novo_campeao.nome, ',');
                maiusculo(novo_campeao.nome);
                getline(cin, novo_campeao.classe, ',');
                maiusculo(novo_campeao.classe);
                getline(cin, novo_campeao.regiao, ',');
                maiusculo(novo_campeao.regiao);
                getline(cin, novo_campeao.ano, ',');
                cin >> novo_campeao.pickrate;
                cin.ignore();
                shell_sort(perso, tamanho_vetor);
            }
            
            else{
                int qual = 1;
                ORDENACAO(qual, perso, tamanho_vetor);
                int antigo = tamanho_vetor;
                tamanho_vetor++;
                aloca_vetor(perso, tamanho_vetor, antigo);
                campeoes novo_campeao;
                cout << "Digite o nome, a classe, a região, o ano de lançamento e o pickrate do campeão a ser adicionado: " << endl;
                cout << "Ex: Aatrox,Lutador,Runeterra,2013,6.3; " << endl;
                cin.ignore();
                getline(cin, novo_campeao.nome, ',');
                maiusculo(novo_campeao.nome);
                getline(cin, novo_campeao.classe, ',');
                maiusculo(novo_campeao.classe);
                getline(cin, novo_campeao.regiao, ',');
                maiusculo(novo_campeao.regiao);
                getline(cin, novo_campeao.ano, ',');
                cin >> novo_campeao.pickrate;
                cin.ignore();
                shell_sort(perso, tamanho_vetor);
            }
        }

        //Entrada para remover um campeão.
        else if(entrada == 3){
            string nome_remover;
            cout << "Digite o nome do campeão a ser removido: " << endl;
            cin >> nome_remover;
            maiusculo(nome_remover);
            remover(nome_remover, perso, ordem, tamanho_vetor);
        }
        
        //Entrada para reordenar os campeões.
        else if(entrada == 4){
            cout << "Digite [1] para reordenar em ordem alfabética"<< endl <<" digite [2] para reordenar por ano de lançamento " << endl << "Digite sua opção: ";
            cin >> ordem;
            cin.ignore();

            if(ordem != 1 and ordem != 2){
                cout << "Escolha inválida. Selecione os números [1] ou [2]." << endl;
                ordem = 0;
                cin >> ordem;
            }
            
            //Reordenando campeoes em ordem alfabética.
            else if(ordem == 1){
                int qual = 1;
                //Chamada da funçao para organizar a struct em ordem alfabética.
                ORDENACAO(qual, perso, tamanho_vetor);
            }

            //Reordenando campeoes em ordem de lançamento(ano).
            else{
                int qual = 2;
                //Chamada da funçao para organizar a struct em ordem de lançamento(ano).
                ORDENACAO(qual, perso, tamanho_vetor);
            }
        }
        
        //Entrada para salvar as alterações feitas no programa.
        else if(entrada == 5){
            //Criar subprograma para gravar as alterações no arquivo CSV.
            Gravar_csv(perso, tamanho_vetor, capacidade, ordem);
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