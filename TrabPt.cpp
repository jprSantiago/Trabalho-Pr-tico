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
void BUSCA(int busca1, string pesq, int tam, campeoes perso[], string pesq2);

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
        sequencial(vetorcomregiao, pesq, busca1, tam, perso);
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

int main(){

    string linha;
    char lixo;
    int capacidade = 0;
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
    // NOSSO ARQUIVO ESTA ORDENADO POR NOME, MAS TAMBEM DEVE SER ORDENADO POR OUTRA FORMA (PICKRATE É UMA OPÇAO).

    // Pedido ao usuario se ele quer adicionar, buscar ou remover um campeao.
    cout << "Digite 1 para busca ou digite 2 para a adiçao, digite 3 para a remoçao de um campeao, digte 4 para a exclusao de um campeao, ou 5 para ver determinados campeoes" << endl;
    cin >> entrada;

    if(entrada != 1 and entrada != 2 and entrada != 3 and entrada != 4 and entrada != 5){
        cout << "Escolha inválida Selecione os números 1, 2, 3, 4 ou 5." << endl;
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
                    BUSCA(busca1, nome, tamanho_vetor, perso, nada);
                }
                else{
                    string regiao;
                    cout << "Digite a regiao que quer buscar: " << endl;
                    cin >> regiao;
                    // Chamado da funçao Busca pela regiao.
                    BUSCA(busca1, regiao, tamanho_vetor, perso, nada);
                }
            }
        }
        else if(entrada == 5){
            cout << "Deseja ver os campeoes em ordem alfabetica ou ordem de lançamento?(1 para alfábetica // 2 para ano de lançamento) " << endl;
            int ordem;
            cin >> ordem;
            cin.ignore();
            busca1 = 2;
            if(ordem == 1){
                cout <<  "De qual campeao dejesa ver?(informe o nome, ou 'todos') " << endl;
                string primeiro_campeao;
                getline(cin, primeiro_campeao);
                if(primeiro_campeao != "todos"){
                    cout << "Até qual campeao deseja ver?(informe o nome) " << endl;
                    string segundo_campeao;
                    getline(cin, segundo_campeao);
                    cin.ignore();
                    BUSCA(busca1, primeiro_campeao, tamanho_vetor, perso, segundo_campeao);
                }
                else{
                    for(int i = 0; i < tamanho_vetor; i++){
                        cout << perso[i].nome << endl;
                        cout << perso[i].classe << endl;
                        cout << perso[i].regiao << endl;
                        cout << perso[i].ano << endl;
                        cout << perso[i].pickrate << endl;
                    }
                }
            }
        }
    }
    
    arquivo_csv.close();
    delete[] perso;
    return 0;
}