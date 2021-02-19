#include <iostream>
#include <cstdlib>

using namespace std;

 // Função pra recursão
void mostrar_vizinho(int x, int y, char **tab_usu, char **tab_aux, int x_esc, int y_esc){

    // Variáveis para laços
	int i, j;

	// Se for maior que 0, acaba a recursão
    if(tab_aux[x_esc][y_esc]>48 && tab_aux[x_esc][y_esc]<57){
    	tab_usu[x_esc][y_esc] = tab_aux[x_esc][y_esc];
	}else if(tab_aux[x_esc][y_esc]==48){
	    // Verifica os vizinhos
    	for(i=x_esc-1; i<=x_esc+1; i++){
        	for(j=y_esc-1; j<=y_esc+1; j++){
            	// Se for 0
            	if(tab_aux[i][j]==48 && i>0 && j>0 && i<x-1 && j<y-1){
                	// Verifica se já foi aberta no tabuleiro do usuário.
                	if(tab_usu[i][j]!=48){
                    	tab_usu[i][j]=tab_aux[i][j];
                    	mostrar_vizinho(x, y, tab_usu, tab_aux, i, j);
                	}
            	// Se for maior que 0 e não for bomba
            	}else if(tab_aux[i][j]>48 && tab_aux[i][j]<57){
                	mostrar_vizinho(x, y, tab_usu, tab_aux, i, j);
            	}
        	}
    	}
	}
}

// Função pra gerar os tabuleiros
void cria_tabuleiro(int x, int y, int buum){

	cout << "\n";

	// Variáveis para laços
	int i, j, k, w;
    // Variável para ser contador
    int z=0, v=0;
	// Variáveis que recebem os valores aleatórios
	int ale_x, ale_y;
	// Variável para contar a quatidade de casas vizinhas com bombas
	int cont_bomba=0;
	// Variável para controlar o "jogo"
	int perdeu=0, cont_asterisco;
	// Matriz "tab_usu" será o tabuleiro mostrado para o usuário
	// Matriz "tab_aux" será o tabuleiro auxiliar que guardará as bomboas e as casas vizinhas
	char **tab_usu, **tab_aux;
	tab_usu = new char *[x];
    tab_aux = new char *[x];

	for(i=0; i<x; i++){
    	tab_usu[i] = new char[y];
    	tab_aux[i] = new char[y];
	}

	// Variáveis para receber as coordenadas e ação escolhidas
	int x_esc, y_esc;
	char acao_esc;

	srand( (unsigned)time(NULL) );

	// Inicializa as matrizes "zeradas"
	for(i=0; i<x; i++){
    	for(j=0; j<y; j++){
        	tab_aux[i][j] = 48;
        	tab_usu[i][j] = '*';
    	}
	}

	// Gera as bombas aleatoriamente
	i=0;
	while(i<buum){
    	ale_x = 1+(rand()%(x-2));
    	ale_y = 1+(rand()%(y-2));

    	// Escolhi o "%"(Tabela ASCII: 37) para representar as bombas
    	if(tab_aux[ale_x][ale_y] != 37){
        	tab_aux[ale_x][ale_y] = 37;
        	i++;
    	}
	}

	// Marca as posições
	for(i=1; i<x-1; i++){
    	for(j=1; j<y-1; j++){
        	if( tab_aux[i][j] != 37 ){
            	// Verifica os vizihos
            	for(k=i-1; k<=i+1; k++){
                	for(w=j-1; w<=j+1; w++){
                    	if( tab_aux[k][w] == 37 ){
                        	cont_bomba++;
                    	}
                	}
            	}
            	tab_aux[i][j] = cont_bomba+48;
            	cont_bomba = 0;
        	}
    	}
	}

	// Começar as jogadas
	do{
    	// Limpar a tela no Windows ou linux
        cout << "\033[2J\033[1;1H";

    	// Quantidade de casas sem bombas
    	// Essa variável será o controle para a vitória do jogador
    	// Ex: Se for o tabuleiro 9x9
    	// Vai ficar: 9*9-10=71(Que será a quantidade de casas que precisam ser abertas)
    	cont_asterisco = (x-2)*(y-2)-buum;

    	// Deixei que aparecesse tabuleiro com bombas pra facilitar a visualização do campo.
        /*
    	//cout << "Tabuleiro de bombas\n";
    	for(i=1; i<x-1; i++){
        	for(j=1; j<y-1; j++){
            	cout << tab_aux[i][j] << " ";
        	}
        	cout << "\n";
    	}
        */

        cout << "\n";

    	//cout << "Tabuleiro do usuario\n";
    	for(i=1; i<x-1; i++){
        	for(j=1; j<y-1; j++){
            	cout << tab_usu[i][j] << " ";
        	}
        	cout << "\n";
    	}

    	// Recebe os comandos
        do{
            cout << "\n>>> Digite [A/a] para abrir posição ou [B/b] para marcar bomba: ";
            cin >> acao_esc;

            if(acao_esc>64 && acao_esc<67){
                v++;
            }
            if(acao_esc>96 && acao_esc<99){
                v++;
            }
        }while(v<1);
        v=0;
        
        do{
            cout << ">>> Digite um valor de "<< x-x+1 << " a " << y-2 << " para as coordenadas X e Y no formato(X Y): ";
            cin >> x_esc >> y_esc;

            if((x_esc > (x-x)) && (x_esc < (y-1))){
                z++;
            }
            if((y_esc > (x-x)) && (y_esc < (y-1))){
                z++;
            }
        }while(z!=2);
        z=0;
        
    	// Realiza os testes
    	if(acao_esc=='A'||acao_esc=='a'){
        	// Se for bomba
        	if(tab_aux[x_esc][y_esc]==37){
            	tab_usu[x_esc][y_esc] = tab_aux[x_esc][y_esc];
            	perdeu++;
        	}else if(tab_aux[x_esc][y_esc]!=37){
            	// Se for 0 a quatidade de bombas ao redor
            	if(tab_aux[x_esc][y_esc]==48){
                	tab_usu[x_esc][y_esc] = tab_aux[x_esc][y_esc];
                	mostrar_vizinho(x, y, tab_usu, tab_aux, x_esc, y_esc);

            	// Se for maior que 0 a quatidade de bombas ao redor
            	}else if(tab_aux[x_esc][y_esc]>47 && tab_aux[x_esc][y_esc]<57){
                	tab_usu[x_esc][y_esc] = tab_aux[x_esc][y_esc];

                	//cout << "Tabuleiro do usuario\n";
                	for(i=1; i<x-1; i++){
                    	for(j=1; j<y-1; j++){
                        	cout << tab_usu[i][j] << " ";
                    	}
                    	cout << "\n";
                	}
                	// cout << "Casos restantes: %d\n", cont_casos);

            	}
        	}
    	}else if(acao_esc=='B'||acao_esc=='b'){
        	tab_usu[x_esc][y_esc] = 'B';

        	//cout << "Tabuleiro do usuario\n";
        	for(i=1; i<x-1; i++){
            	for(j=1; j<y-1; j++){
                	cout << tab_usu[i][j] << " ";
            	}
            	cout << "\n";
        	}
    	}

    	// Controle para o caso de vitória do jogador
    	for(i=1; i<x-1; i++){
        	for(j=1; j<y-1; j++){
            	if(tab_usu[i][j]!='*' && tab_usu[i][j]!='B'){
                	cont_asterisco--;
            	}
        	}
        	cout << "\n";
    	}

	}while(perdeu==0 && cont_asterisco>0);

	// Limpar a tela no Windows ou linux
    cout << "\033[2J\033[1;1H";

	if(perdeu>0){
    	cout << "\nBOOOMMMM\n";
    	cout << "Voce perdeu!!!\n";
	}else if(cont_asterisco==0){
    	cout << "\nPARABENS!\n";
    	cout << "Voce ganhou!!!\n";
	}

	//cout << "\nTabuleiro do usuario: \n";
	for(i=1; i<x-1; i++){
    	for(j=1; j<y-1; j++){
        	if(tab_aux[i][j]==37){
            	tab_usu[i][j] = tab_aux[i][j];
        	}
        	cout << tab_usu[i][j] << " ";
    	}
    	cout << "\n";
	}
}

int main(){

	int coord_x, coord_y, qt_bombas;
    char num_esco;

        do{
            cout << "Escolha uma das opcoes abaixo: \n";
            cout << "\nPara um tabuleiro 9x9(Com 10 bombas) digite 1: \n";
            cout << "Para um tabuleiro 16x16(Com 40 bombas) digite 2: \n";
            cout << "Para um tabuleiro 16x30(Com 99 bombas) digite 3: \n";
            cout << "Para encerrar o programa digite 4: \n\n";

            cout << "Escolha o modo de jogo: ";
            cin >> num_esco;

        }while(num_esco<48 && num_esco>51);

    	switch(num_esco){
        	case '1':
            	coord_x = 11;
            	coord_y = 11;
            	qt_bombas = 10;
            	cria_tabuleiro(coord_x, coord_y, qt_bombas);
            	break;
        	case '2':
            	coord_x = 18;
            	coord_y = 18;
            	qt_bombas = 40;
            	cria_tabuleiro(coord_x, coord_y, qt_bombas);
            	break;
        	case '3':
            	coord_x = 18;
            	coord_y = 32;
            	qt_bombas = 99;
            	cria_tabuleiro(coord_x, coord_y, qt_bombas);
            	break;
            case '4':
                break;
            break;

    	}

	cout << "\nO jogo acabou!!!\n";

	return 0;
}