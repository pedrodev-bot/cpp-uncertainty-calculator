#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

using big_float = boost::multiprecision::cpp_dec_float_50;
using namespace std;

typedef vector<big_float> vbf;

big_float calcularDesvios(int n, big_float media, vbf& medidas, int x);
big_float calcularIncerteza(big_float incertezaAleatoria, big_float incertezaInstrumental);
big_float calcularIncertezaAleatoria(int n, big_float somaDesvios);
big_float calcularIncertezaVelocidade(big_float velocidadeMedia, big_float mediaDist, big_float mediaTempo, big_float incertezaDist, big_float incertezaTempo);
big_float calcularMedia(int n, vbf& medidas);
big_float calcularVelocidadeMedia(big_float mediaDist, big_float mediaTempo);
void incertezasAcumuladas();
void incertezaTD(big_float n);
void incertezaVL();
void receberMedidas(int n, vbf& medidas, int x);

big_float INCERTEZA_INSTRUMENTAL_TEMPO = 0.001;
big_float INCERTEZA_INSTRUMENTAL_DISTANCIA = 0.05;

int main(){
    cout << setprecision(10);

    string entradaUsuario;
    entradaUsuario = toupper(entradaUsuario[0]);

    cout << endl;
    cout << "(1) Calculos sobre Tempo (t) (Media e Incerteza)." << endl;
    cout << "(2) Calculos sobre Distancia (d) (Media e Incerteza)." << endl;
    cout << "(3) Calculos sobre t, d e Velocidade." << endl;
    cout << "(4) Incertezas acumuladas." << endl;
    cout << "Digite o numero acima referente ao que quer calcular: ";
    cin >> entradaUsuario;

    if(entradaUsuario[0] == '1'){
        incertezaTD(INCERTEZA_INSTRUMENTAL_TEMPO);
    } else if (entradaUsuario[0] == '2'){
        incertezaTD(INCERTEZA_INSTRUMENTAL_DISTANCIA);
    } else if (entradaUsuario[0] == '3'){
        incertezaVL();
    } else if (entradaUsuario[0] == '4'){
        incertezasAcumuladas();
    }

    return 0;
}

// Cálculo do acumulado de incertezas. (Raiz quadrada da soma de todas as incertezas ao quadrado)
void incertezasAcumuladas() {
    cout << "Nota: O resultado deste comando e a incerteza para de todos os momentos," << endl;
    cout << "tal que, para tres incertezas, a saida e a incerteza acumulada para o" << endl;
    cout << "primeiro momento, em seguida o acumulativo para o segundo momento e por" << endl;
    cout << "ultimo o acumulativo ate o ultimo momento. Nao faca por etapas. Envie to-" << endl;
    cout << "dos os dados." << endl;
    cout << endl;
    cout << "Indique quantas incertezas quer somar: ";
    int qteIncertezas;
    cin >> qteIncertezas;
    cout << endl;

    vbf incertezas(qteIncertezas);
    for(int i = 0; i < qteIncertezas; i++){
        string entradaUsuario;
        cout << i+1 << ". Incerteza " << i+1<< ": ";
        cin >> entradaUsuario;
        
        replace(entradaUsuario.begin(), entradaUsuario.end(), ',', '.');
        incertezas[i] = big_float(entradaUsuario);
    }

    cout << endl;
    cout << "O resultado e a raiz quadrada da soma dos termos ao quadrado." << endl;
    for(int i = 0; i < qteIncertezas; i++){
        int counter = i+1;
        big_float actualSum = 0;
        while(counter != 0){
            actualSum+=(incertezas[counter-1])*(incertezas[counter-1]);
            counter--;
        }
        cout << i+1 << ". Soma de " << i+1 << " incertezas: " << sqrt(actualSum) << endl;
    }
}

// Cálculo da velocidade.
void incertezaVL(){
    vbf medidasDist;
    vbf medidasTempo;
    int qteMedidas;
    
    cout << endl;
    cout << "1. Quantidade de Medidas (Distancia): ";
    cin >> qteMedidas;

    medidasDist.resize(qteMedidas);
    
    receberMedidas(qteMedidas, medidasDist, 1);

    cout << "2. Quantidade de Medidas (Tempo): ";
    cin >> qteMedidas;

    medidasTempo.resize(qteMedidas);
    
    receberMedidas(qteMedidas, medidasTempo, 2);

    // Cálculo das Médias
    big_float mediaDist = calcularMedia(qteMedidas, medidasDist);
    big_float mediaTempo = calcularMedia(qteMedidas, medidasTempo);
    big_float velocidadeMedia = calcularVelocidadeMedia(mediaDist, mediaTempo);
    cout << "3. Medias" << endl;
    cout << "3.1 Media das Distancias: " << mediaDist << endl;
    cout << "3.2 Media do Tempo: " << mediaTempo << endl;
    cout << "3.3 Velocidade Media: " << velocidadeMedia << endl;

    // Cálculo dos Desvios
    cout << endl << "4. Calculo dos Desvios (Distancia)" << endl;
    big_float desvioDist = calcularDesvios(qteMedidas, mediaDist, medidasDist, 4);
    cout << endl << "5. Calculo dos Desvios (Tempo)" << endl;
    big_float desvioTempo = calcularDesvios(qteMedidas, mediaTempo, medidasTempo, 5);

    // Cálculo das Incertezas
    big_float incertezaAleatoriaDist = calcularIncertezaAleatoria(qteMedidas, desvioDist);
    big_float incertezaAleatoriaTempo = calcularIncertezaAleatoria(qteMedidas, desvioTempo);
    cout << endl;
    cout << "6. Incerteza Aleatoria (Distancia): " << incertezaAleatoriaDist << endl;
    cout << "7. Incerteza Aleatoria (Tempo): " << incertezaAleatoriaTempo << endl;
    big_float incertezaDist = calcularIncerteza(INCERTEZA_INSTRUMENTAL_DISTANCIA, incertezaAleatoriaDist);
    big_float incertezaTempo = calcularIncerteza(INCERTEZA_INSTRUMENTAL_TEMPO, incertezaAleatoriaTempo);
    cout << "8. Incerteza da Distancia: " << incertezaDist << endl;
    cout << "9. Incerteza do Tempo: " << incertezaTempo << endl;

    // Cálculo da incerteza da velocidade
    big_float incertezaVelocidade = calcularIncertezaVelocidade(velocidadeMedia, mediaDist, mediaTempo, incertezaDist, incertezaTempo);
    cout << "10. Incerteza da Velocidade: " << incertezaVelocidade << endl;

    return;
}

// Cálculo da incerteza da distância e tempo.
void incertezaTD(big_float n){
    vbf medidas;
    int qteMedidas;
    big_float incertezaInstrumental = n;

    cout << endl;
    cout << "1. Quantidade de Medidas: ";
    cin >> qteMedidas;

    medidas.resize(qteMedidas);

    receberMedidas(qteMedidas, medidas, 1);

    // Cálculo da Média
    big_float media = calcularMedia(qteMedidas, medidas);
    cout << "# Media: " << media << endl;
    //

    // Cálculo da soma dos desvios padrões da média
    cout << endl;
    cout << "2. Resolucao da formula (Valor de X1 - Media de X)^2" << endl;
    big_float somaDesvios = calcularDesvios(qteMedidas, media, medidas, 2);
    cout << "# Soma dos desvios ao quadrado: " << somaDesvios << endl;
    //

    // Cálculo da incerteza aleatória (referente aos dados de medição)
    big_float incertezaAleatoria = calcularIncertezaAleatoria(qteMedidas, somaDesvios);
    cout << endl;
    cout << "3. Incerteza Aleatoria: " << incertezaAleatoria << endl;
    //

    cout << "4. Incerteza Instrumental: " << incertezaInstrumental << endl;

    // Cálculo da incerteza da grandeza
    big_float incerteza = calcularIncerteza(incertezaAleatoria, incertezaInstrumental);
    cout << "5. Incerteza final (Resposta): " << incerteza << endl;

    // debug
    // cout << endl;
    // for(int i = 0; i < qteMedidas; i++){
    //    cout << medidas[i] << " ";
    //}
    //cout << endl;

    return;
}

void receberMedidas(int n, vbf& medidas, int x){
    for(int i = 0; i < n; i++){
        string entradaUsuario;

        cout << x << "." << i+1 << ". Medida " << i+1 << ": ";
        cin >> entradaUsuario;

        replace(entradaUsuario.begin(), entradaUsuario.end(), ',', '.');
        medidas[i] = big_float(entradaUsuario);
    }
    cout << endl;

    return;
}
big_float calcularMedia(int n, vbf& medidas){
    big_float somaMedias = 0;

    for(auto &a_ : medidas) somaMedias+=a_;

    return somaMedias/n;
}
big_float calcularDesvios(int n, big_float media, vbf& medidas, int x){

    big_float somaDesvios = 0;
    for(int i = 0; i < n; i++){
        big_float actualAns = (medidas[i]-media)*(medidas[i]-media);
        cout << x << "." << i+1 << ". (" << medidas[i] << " - " << media << ")^2 = " << actualAns << endl;
        somaDesvios+=actualAns;
    }

    return somaDesvios;
}
big_float calcularIncertezaAleatoria(int n, big_float somaDesvios){
    big_float incertezaAleatoria = sqrt(somaDesvios/(n*(n-1)));
    return incertezaAleatoria;
}
big_float calcularIncerteza(big_float x, big_float y){
    big_float incerteza = sqrt((x*x)+(y*y));

    return incerteza;
}
big_float calcularVelocidadeMedia(big_float mediaDist, big_float mediaTempo){
    big_float v = mediaDist/mediaTempo;

    return v;
}
big_float calcularIncertezaVelocidade(big_float velocidadeMedia, big_float mediaDist, big_float mediaTempo, big_float incertezaDist, big_float incertezaTempo){
    cout << endl;
    // Resolucao dos calculos para as partes da distancia (x) e tempo (y)
    big_float x = (incertezaDist/mediaDist)*(incertezaDist/mediaDist);
    big_float y = (incertezaTempo/mediaTempo)*(incertezaTempo/mediaTempo);

    big_float incertezaVelocidade = velocidadeMedia*sqrt(x+y);

    return incertezaVelocidade;
}