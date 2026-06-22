#include <iostream>
#include <fstream>

using namespace std;

// Estrutura com os dados de cada campeao de LOL.
struct campeoes{
    string nome;
    string classe;
    string regiao;
    int ano;
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
void BUSCA(int busca1, string pesq, int tam, campeoes perso[]);

// Funçao de Busca Sequencial Para as Regioes dos Campeoes.
void sequencial(string regioes[], string regiao, int cont, int tamanho_original, campeoes perso[]){
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
        cout << "Deseja que seja informado quais sao(S/N)? " << endl;
        cin >> resposta;
        if(resposta == 'S'){
            for(int i = 0; i < tamanho_original; i++){
                if(regiao == regioes[i]){
                    cout << perso[i].nome << endl;
                    cout << perso[i].classe << endl;
                    cout << perso[i].regiao << endl;
                    cout << perso[i].ano << endl;
                    cout << perso[i].pickrate << endl;
                    cout << endl;
                }
            }
        }
        else{
            cout << "Digite o nome do campeao que deseja" << endl;
            cin >> desejo;
            int buscador = 1;
            BUSCA(buscador, desejo, tamanho_original, perso);
        }
    }
}

// Procedimento de Busca onde Retorna o Campeao Buscado.
void BUSCA(int busca1, string pesq, int tam, campeoes perso[]){
    if(busca1 == 1){
        string* vetorcomnomes = new string[tam];
        for(int i = 0; i < tam; i++){
            vetorcomnomes[i] = perso[i].nome;
        }
        int procura = binaria(vetorcomnomes, pesq, 0, tam - 1);
        if(procura == -1){
            cout << "Campeao nao encontrado!" << endl;
        }
        else{
            cout << perso[procura].nome << endl;
            cout << perso[procura].classe << endl;
            cout << perso[procura].regiao << endl;
            cout << perso[procura].ano << endl;
            cout << perso[procura].pickrate << endl;
        }
        delete[] vetorcomnomes;
    }
    else{
        string *vetorcomregiao = new string[tam];
        for(int i = 0; i < tam; i++){
            vetorcomregiao[i] = perso[i].regiao;
        }
        sequencial(vetorcomregiao, pesq, busca1, tam, perso);
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

int main(){

    string linha;
    char lixo;
    int capacidade;
    campeoes *perso;
    int tamanho_vetor = 0;
    int total;

    // Leitura do Arquivo LOL.csv.
    ifstream arquivo_csv("LOL.csv");

    if(not(arquivo_csv)){
        cout << "Erro" << endl;
    }

    else{  //Coleta basica de dados do arquivo para o programa, com armazenamento na matriz memoria, onde cada linha é os dados de um personagem.
        getline(arquivo_csv, linha);
        arquivo_csv >> capacidade;
        arquivo_csv >> total;
        arquivo_csv.ignore();
        perso = new campeoes[capacidade];

        for(int i = 0; i < capacidade; i++){ 
            getline(arquivo_csv, perso[i].nome, ',');
            getline(arquivo_csv, perso[i].classe, ',');
            getline(arquivo_csv, perso[i].regiao, ','); 
            arquivo_csv >> perso[i].ano;
            arquivo_csv >> lixo;
            arquivo_csv >> perso[i].pickrate;
            arquivo_csv >> lixo;
            arquivo_csv.ignore();
            tamanho_vetor++;

            // Verificaçao de tamanho e se o vetor encheu.
            if(capacidade <= total and capacidade == tamanho_vetor){
                int antigo = capacidade;
                capacidade += 10;
                aloca_vetor(perso, capacidade, antigo);
            }
        }
    }
    int entrada = 0;
    int busca1 = 0;

    // POSTERIORMENTE ADICIONAR SE O USUARIO QUER RETIRAR O CAMPEAO.
    // PARA A INSERÇAO DE UM NOVO CAMPEAO, ALOCAR DINAMICAMENTE MAIS 1 DE ESPAÇO POR VEZ.
    // INSERÇAO E RETIRADA DEVE SER FEITO ORDENADAMENTE.
    // APOS A INSERÇAO DEVE SER CAPAZ SALVAR AS ALTERAÇOES.
    // A REMOÇAO PODE SER APENAS UMA MARCAÇAO E NAO UMA REMOÇAO EM SI.
    // DEVE SER POSSIVEL O USUARIO ESCOLHER DE QUAL A QUAL CAMPEAO ELE QUER VER, OU SEJA DO DECIMO AO VIGEGIMO POR EXEMPLO.
    // NOSSO ARQUIVO ESTA ORDENADO POR NOME, MAS TAMBEM DEVE SER ORDENADO POR OUTRA FORMA (PICKRATE É UMA OPÇAO).

    // Pedido ao usuario se ele quer adicionar, buscar ou remover um campeao.
    cout << tamanho_vetor << endl;
    cout << "Digite 1 para busca ou digite 2 para a adiçao ou digite 3 para a remoçao de um campeao" << endl;
    cin >> entrada;

    if(entrada != 1 and entrada != 2 and entrada != 3){
        cout << "Escolha inválida Selecione os números 1, 2 ou 3." << endl;
        entrada = 0;
        cin >> entrada;
    }

    else{
        if(entrada == 1){
            // Pedido ao usuario se ele quer buscar pela regiao ou nome.
            cout << "Digite 1 para buscar pelo nome ou 2 pela regiao" << endl;
            cin >> busca1;

            if(busca1 != 1 and busca1 != 2){
                cout << "Escolha inválida Selecione os números 1 ou 2." << endl;
                busca1 = 0;
                cin >> busca1;
            }

            else{
                if(busca1 == 1){
                    string nome;
                    cout << "Digite o nome que quer buscar: " << endl;
                    cin >> nome;
                    // Chamado da Funçao Busca pelo nome.
                    BUSCA(busca1, nome, tamanho_vetor, perso);
                }
                else{
                    string regiao;
                    cout << "Digite a regiao que quer buscar: " << endl;
                    cin >> regiao;
                    // Chamado da funçao Busca pela regiao.
                    BUSCA(busca1, regiao, tamanho_vetor, perso);
                }
            }
        }
    }
    
    arquivo_csv.close();
    delete[] perso;
    return 0;
}