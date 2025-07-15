#include <iostream>
#include <string.h>
#include <locale.h>
#include <stdio.h>
#include <algorithm>
#include <iomanip>

using namespace std;

struct tiposProdutos{
	int codigo;
	string descricao;
};

struct produtos{
	int codigo; 
	string descricao;
	string tipoProduto;
	int codigoDoFornecedor;
	int qtdeEstoque;
	int estoqueMin;
    int estoqueMax;
	float valorUnitario;
};

struct cidades{
	int codigo;
	string descricao;
	string UF;
};

struct fornecedores {
	int codigo;
	string nome;
	string endereco;
	long long telefone;
	int codigoCidade;
	long long cnpj;
};

void lerTipoDeProduto(struct tiposProdutos t[], int cont){
	for(int i=0; i<cont; i++){
		cout << endl <<" Código do tipo do produto: ";
		cin >> t[i].codigo;
		cout <<" Descrição do tipo do produto: ";
		cin.ignore(); 
        getline(cin, t[i].descricao); 
	}
}

void lerCidades(struct cidades c[], int cont){
	for(int i=0; i<cont; i++){
		cout << endl <<" Codigo da cidade: ";
		cin >> c[i].codigo;
	    cout <<" Descrição da cidade: ";
		cin.ignore();
		getline(cin, c[i].descricao);
		cout <<" Estado da cidade: ";
		cin >> c[i].UF;
	}
}

void lerFornecedor(struct fornecedores f[], int cont){
	for(int i=0; i<cont; i++){
		cout << endl <<" Codigo do fornecedor: ";
		cin >> f[i].codigo;
	    cout <<" Nome do fornecedor: ";
		cin.ignore();
		getline(cin, f[i].nome);
		cout <<" Endereço do fornecedor: ";
		getline(cin, f[i].endereco);
		cout <<" Telefone do fornecedor (somente números): ";
		cin >> f[i].telefone;
		cout <<" Código da cidade do fornecedor: ";
		cin >> f[i].codigoCidade;
		cout <<" CNPJ do fornecedor (somente números): ";
		cin >> f[i].cnpj;
	}
}

void lerProduto(struct produtos p[], int cont){
	for(int i=0; i<cont; i++){
		cout << endl <<" Codigo do produto: ";
		cin>> p[i].codigo;
	    cout<<" Descrição do produto: ";
		cin.ignore();
		getline(cin, p[i].descricao);
		cout<<" Tipo do produto: ";
		getline(cin, p[i].tipoProduto);
		cout<<" Codigo do fornecedor do produto : ";
		cin>> p[i].codigoDoFornecedor;
		cout<<" Quantidade do Estoque: ";
		cin>> p[i].qtdeEstoque;
		cout<<" Estoque máximo do produto: ";
		cin>> p[i].estoqueMax;
		cout<<" Estoque minimo do produto: ";
		cin>> p[i].estoqueMin;
		cout<<" Valor unitario do produto (ex: 12.50, use ponto e não vírgula): ";
		cin>> p[i].valorUnitario;
	}
		
}

void buscaCidade (int cod, struct cidades c[]){
    int inicio = 0;
	int fim = 9;
    int meio = (inicio + fim) / 2;
    
    for (; fim > inicio && cod != c[meio].codigo; meio = (inicio + fim) / 2){
        if (cod > c[meio].codigo){
        	inicio = meio + 1;
		}else{
			fim = meio - 1;
	    }
    }
    if (cod == c[meio].codigo){
        cout << " " << c[meio].descricao << " - " << c[meio].UF << endl;
    }
    else{
    	cout << " Cidade nao registrada." << endl;
	}
}


bool validarCnpj(long long cnpj) {
    if (cnpj < 10000000000000 || cnpj > 99999999999999) {
        return false;
    }

    int digitos[14];

    long long divisor = 10000000000000; 
    for (int i = 0; i < 14; i++) {
        digitos[i] = cnpj / divisor % 10;
        divisor /= 10;
    }

    int pesos1[12] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int pesos2[13] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};

    int soma = 0;
    for (int i = 0; i < 12; i++) {
        soma += digitos[i] * pesos1[i];
    }

    int resto = soma % 11;
    int digito1 = (resto < 2) ? 0 : 11 - resto;

    if (digitos[12] != digito1) {
        return false;
    }

    soma = 0;
    for (int i = 0; i < 13; i++) {
        soma += digitos[i] * pesos2[i];
    }

    resto = soma % 11;
    int digito2 = (resto < 2) ? 0 : 11 - resto;

    if (digitos[13] != digito2) {
        return false;
    }
    
    return true;

}


void lerNovoFornecedor(struct fornecedores f2[], int contF2, struct cidades c[]){
	int codigo;
	bool valido;
	
	for(int i=0; i<contF2; i++){
		valido = false;
		
		cout << endl <<" Codigo do fornecedor: ";
		cin >> f2[i].codigo;
		
	    cout <<" Nome do fornecedor: ";
		cin.ignore();
		getline(cin, f2[i].nome);
		
		cout <<" Endereço do fornecedor: ";
		getline(cin, f2[i].endereco);
		
		cout <<" Telefone do fornecedor (somente números): ";
		cin >> f2[i].telefone;
		
		cout <<" Código da cidade do fornecedor: ";
		cin >> f2[i].codigoCidade;
		codigo = f2[i].codigoCidade;
		buscaCidade(codigo, c);  
		
		while (!valido) {
        cout << "\r CNPJ do fornecedor (14 dígitos): ";
        cin >> f2[i].cnpj;
        
            if (validarCnpj(f2[i].cnpj) == true) {
                cout << " CNPJ válido" << endl;
                valido = true;  
            } else {
                cout << "\033[F"; 
                cout << "\033[K"; 
                cout << "\r CNPJ inválido. Tente novamente.\n";
            }
        }
	}
}

void incluirRegistrosFornecedor (struct fornecedores f[], int &contF, struct fornecedores f2[], struct fornecedores f3[], struct cidades c[]){
	int contF2;
	int i=0, j=0, k=0;
	
	cout << endl << " Digite a quantidade de registros que deseja incluir:";
	cin >> contF2;
	
	lerNovoFornecedor(f2, contF2, c);
		
	for (;i < contF && j < contF2;k++){
       if (f[i].codigo < f2[j].codigo){     
	    	
            f3[k].codigo = f[i].codigo;           
            f3[k].nome = f[i].nome;           
            f3[k].endereco = f[i].endereco;            
            f3[k].telefone = f[i].telefone;            
            f3[k].codigoCidade = f[i].codigoCidade;            
            f3[k].cnpj = f[i].cnpj;
            
            i++;
       }else {	          	
            f3[k].codigo = f2[j].codigo;           
            f3[k].nome = f2[j].nome;          
            f3[k].endereco = f2[j].endereco;           
            f3[k].telefone = f2[j].telefone;           
            f3[k].codigoCidade = f2[j].codigoCidade;            
            f3[k].cnpj = f2[j].cnpj;
            
            j++;
       }
    }
    
    while (i < contF){  	
        f3[k].codigo = f[i].codigo;            
        f3[k].nome = f[i].nome;           
        f3[k].endereco = f[i].endereco;        
        f3[k].telefone = f[i].telefone;            
        f3[k].codigoCidade = f[i].codigoCidade;            
        f3[k].cnpj = f[i].cnpj;
        
        i++;
        k++;  
    }
	while (j < contF2){		
        f3[k].codigo = f2[j].codigo;            
        f3[k].nome = f2[j].nome;           
        f3[k].endereco = f2[j].endereco;           
        f3[k].telefone = f2[j].telefone;            
        f3[k].codigoCidade = f2[j].codigoCidade;            
        f3[k].cnpj = f2[j].cnpj;
        
        j++;
        k++;
    }
   
   contF = k;
   
    for(int i=0;i<contF;i++){   	
    	f[i].codigo = f3[i].codigo;           
        f[i].nome = f3[i].nome;            
        f[i].endereco = f3[i].endereco;       
        f[i].telefone = f3[i].telefone;            
        f[i].codigoCidade = f3[i].codigoCidade;         
        f[i].cnpj = f3[i].cnpj;
    }

}

bool buscaProdutoExiste(int cod, struct produtos p[], int contP) {
    int inicio = 0;
	int fim = contP - 1;
    int meio;

     for (; fim > inicio && cod != p[meio].codigo; meio = (inicio + fim) / 2){
        if (cod > p[meio].codigo){
        	inicio = meio + 1;
		}else{
			fim = meio - 1;
	    }
    }
    if (cod == p[meio].codigo){
        return true; 
    }
    else{
    	return false; 
	}
}   

void buscaFornecedor(int cod, struct fornecedores f[], int contF) {
    int inicio = 0;
	int fim = contF - 1;
    int meio = (inicio + fim) / 2;

    for (; fim > inicio && cod != f[meio].codigo; meio = (inicio + fim) / 2) {
        if (cod > f[meio].codigo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (cod == f[meio].codigo) {
        cout << " Fornecedor: " << f[meio].nome << endl;
    } else {
        cout << " Fornecedor não encontrado." << endl;
    }
}

void lerNovoProduto(struct produtos p2[], int contP2, struct produtos p[], int contP, struct fornecedores f[], int contF){
	int codigo;
	int codAnterior = -1;
	bool valido;
	
	for(int i=0; i<contP2; i++){
		valido = false;
		
	    while (!valido) {
	        cout << endl << "\r Digite o código do produto: ";
	        cin >> p2[i].codigo;
	
	        if (p2[i].codigo <= codAnterior) {
	            cout << "\033[F";
	            cout << "\033[K";
	            cout << "\r Código inválido. Deve ser maior que o anterior.\n";
	        } else if (buscaProdutoExiste(p2[i].codigo, p, contP) == true) {
	            cout << "\033[F";
				cout << "\033[K";
	            cout << "\r Código já existe na tabela de produtos.\n";
	        } else {
	            codAnterior = p2[i].codigo;
	            valido = true;
	        }
	    }

	    cout << " Descrição do produto: ";
		cin.ignore();
		getline(cin, p2[i].descricao);
		
		cout << " Tipo do produto: ";
		getline(cin, p2[i].tipoProduto);
		
		cout << " Codigo do fornecedor do produto : ";
		cin>> p2[i].codigoDoFornecedor;
		codigo = p2[i].codigoDoFornecedor;
		buscaFornecedor(codigo, f, contF);
		
		cout << " Quantidade do Estoque: ";
		cin >> p2[i].qtdeEstoque;
		
		cout << " Estoque máximo do produto: ";
		cin >> p2[i].estoqueMax;
		
		cout << " Estoque minimo do produto: ";
		cin >> p2[i].estoqueMin;
		
		cout << " Valor unitario do produto (ex: 12.50, use ponto e não vírgula): ";
		cin >> p2[i].valorUnitario;
	}
}

void incluirRegistrosProdutos (struct produtos p[],int &contP, struct produtos p2[], struct produtos p3[], struct fornecedores f[], int &contF){
	int contP2;
	cout << endl << " Digite a quantidade de registros que deseja incluir: ";
	cin >> contP2;
	
	int i=0, j=0, k=0;
	
	lerNovoProduto(p2, contP2, p, contP, f, contF);
	
	for (;i < contP && j < contP2;k++){
       if (p[i].codigo < p2[j].codigo){
       	
       		p3[k].codigo = p[i].codigo;
            p3[k].descricao = p[i].descricao;           
            p3[k].tipoProduto = p[i].tipoProduto;           
            p3[k].codigoDoFornecedor = p[i].codigoDoFornecedor;           
            p3[k].qtdeEstoque = p[i].qtdeEstoque;           
            p3[k].estoqueMax = p[i].estoqueMax;            
            p3[k].estoqueMin = p[i].estoqueMin;            
            p3[k].valorUnitario = p[i].valorUnitario;
            
            i++;
       }else { 
	    	p3[k].codigo = p2[j].codigo;     	
            p3[k].descricao = p2[j].descricao;            
            p3[k].tipoProduto = p2[j].tipoProduto;            
            p3[k].codigoDoFornecedor = p2[j].codigoDoFornecedor;            
            p3[k].qtdeEstoque = p2[j].qtdeEstoque;            
            p3[k].estoqueMax = p2[j].estoqueMax;           
            p3[k].estoqueMin = p2[j].estoqueMin;           
            p3[k].valorUnitario = p2[j].valorUnitario;
            
            j++;
       }
    }
    
    while (i < contP){
    	p3[k].codigo = p[i].codigo;
        p3[k].descricao = p[i].descricao;            
        p3[k].tipoProduto = p[i].tipoProduto;            
        p3[k].codigoDoFornecedor = p[i].codigoDoFornecedor;           
        p3[k].qtdeEstoque = p[i].qtdeEstoque;            
        p3[k].estoqueMax = p[i].estoqueMax;           
        p3[k].estoqueMin = p[i].estoqueMin;            
        p3[k].valorUnitario = p[i].valorUnitario;
        
        i++;
        k++;  
    }
	while (j < contP2){
		p3[k].codigo = p2[j].codigo;
        p3[k].descricao = p2[j].descricao;          
        p3[k].tipoProduto = p2[j].tipoProduto;            
        p3[k].codigoDoFornecedor = p2[j].codigoDoFornecedor;            
        p3[k].qtdeEstoque = p2[j].qtdeEstoque;            
        p3[k].estoqueMax = p2[j].estoqueMax;            
        p3[k].estoqueMin = p2[j].estoqueMin;           
        p3[k].valorUnitario = p2[j].valorUnitario;
        
        j++;
        k++;
    }
     
    contP = k;
   
    for(int i=0;i<contP;i++){
    	p[i].codigo = p3[i].codigo;
    	p[i].descricao = p3[i].descricao;           
        p[i].tipoProduto = p3[i].tipoProduto;            
        p[i].codigoDoFornecedor = p3[i].codigoDoFornecedor;           
        p[i].qtdeEstoque = p3[i].qtdeEstoque;            
        p[i].estoqueMax = p3[i].estoqueMax;           
        p[i].estoqueMin = p3[i].estoqueMin;       
        p[i].valorUnitario = p3[i].valorUnitario;
    }
}

bool buscaProduto(int cod, struct produtos p[], int contP, int &indice) {
    int inicio = 0;
	int fim = contP - 1;
    int meio = (inicio + fim) / 2;

    for (; fim > inicio && cod != p[meio].codigo; meio = (inicio + fim) / 2) {
        if (cod > p[meio].codigo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (cod == p[meio].codigo) {
        indice = meio;
        return true;   
    } else {
        return false;  
    }
}

void vendaProduto(struct produtos p[], int &contP){
	int cod;
	int quant;
	int i; 
	bool valido;
	float venda;
	char confirmacao;
	
	while (!valido) {
	        cout << endl << "\r Digite o código do produto a ser vendido: ";
	        cin >> cod;
	        
	        if (buscaProduto(cod, p, contP, i) == true) {
	            cout << endl << " Descrição: " << p[i].descricao << endl;
				cout << " Tipo: " << p[i].tipoProduto << endl;
				cout << " Fornecedor: " << p[i].codigoDoFornecedor << endl;
				cout << " Estoque: " << p[i].qtdeEstoque << endl;
				cout << " Valor unitário: R$" << p[i].valorUnitario << endl;
				
				valido = true;
	        } else {
	            cout << "\033[F";
				cout << "\033[K";
	            cout << "\r Código não existe na tabela de produtos.\n";
	        } 
	}
	
	valido = false;
	
	while (!valido) {
	        cout << endl << " Digite a quantidade de " << p[i].descricao << " que deseja vender: ";
	        cin >> quant;
	        
	        if (quant <= p[i].qtdeEstoque) {
	        	venda = quant * p[i].valorUnitario;
	            cout << endl << " Valor da venda de [" << quant << "] " << p[i].descricao << "s : R$" << venda << endl;
				
				valido = true;
	        } else {
	            cout << "\033[F";
				cout << "\033[K";
	            cout << "\r Não há produtos suficientes para a venda.\n";
	        } 
	}	
	
	cout << " Confirmar venda [S/N]: ";
	cin >> confirmacao;
	confirmacao = tolower(confirmacao);
	
	if(confirmacao == 's'){
		p[i].qtdeEstoque = p[i].qtdeEstoque - quant;
	    cout << endl << " Venda concluída com sucesso!" << endl;
	}else {
		cout << endl << " Venda cancelada..." << endl;
	}
}

void consultaEstoque(struct produtos p[], int contP){
	int i; 
	int cod;
	bool valido;
	
	while (!valido) {
	    cout << endl << "\r Digite o código do produto a ser consultado: ";
	    cin >> cod;
	        
	    if (buscaProduto(cod, p, contP, i) == true) {
	        cout << endl << " Descrição: " << p[i].descricao << endl;
			cout << " Tipo: " << p[i].tipoProduto << endl;
			cout << " Fornecedor: " << p[i].codigoDoFornecedor << endl;
			cout << " Valor total em estoque: R$" << p[i].qtdeEstoque * p[i].valorUnitario << endl;
				
			valido = true;
	    } else {
	        cout << "\033[F";
			cout << "\033[K";
	        cout << "\r Código não existe na tabela de produtos.\n";
	    } 
	}
}


int buscaFornecedorPorCodigo(int cod, struct fornecedores f[], int contF) {
    int inicio = 0;
	int fim = contF - 1;
	int meio = (inicio + fim) / 2;

    for (; fim > inicio && cod != f[meio].codigo; meio = (inicio + fim) / 2) {
        if (cod > f[meio].codigo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (cod == f[meio].codigo) {
        return meio;   
    } else {
        return -1;     
    }
}

void consultaProdutosAbaixoDoMinimo(struct produtos p[], int contP, struct fornecedores f[], int contF) {
    float totalCompra = 0;
    int qtdeComprar;
    float valorCompra;
    bool encontrou = false;

    for (int i = 0; i < contP; i++) {
        if (p[i].qtdeEstoque < p[i].estoqueMin) {
        	encontrou = true;
        	
            qtdeComprar = p[i].estoqueMax - p[i].qtdeEstoque;
            valorCompra = qtdeComprar * p[i].valorUnitario;
            totalCompra += valorCompra;

            cout << "\n--- Produto abaixo do estoque mínimo ---\n";
            cout << " Código: " << p[i].codigo << endl;
            cout << " Descrição: " << p[i].descricao << endl;
            cout << " Estoque: " << p[i].qtdeEstoque << endl;
            cout << " Estoque Máximo: " << p[i].estoqueMax << endl;
            cout << " Quantidade a ser comprada: " << qtdeComprar << endl;
            cout << " Valor da compra: R$ " << fixed << setprecision(2) << valorCompra << endl;

            int indiceFornecedor = buscaFornecedorPorCodigo(p[i].codigoDoFornecedor, f, contF);

            if (indiceFornecedor != -1) {
                cout << " Fornecedor: " << f[indiceFornecedor].nome << endl;
                cout << " Telefone: " << f[indiceFornecedor].telefone << endl;
            } else {
                cout << " Fornecedor não encontrado.\n";
            }
        }
    }

    if (encontrou) {
        cout << "\n Valor total a ser comprado: R$ " << fixed << setprecision(2) << totalCompra << endl;
    } else {
        cout << "\n Nenhum produto está abaixo do estoque mínimo.\n";
    }
}

string normalizarDescricao(string desc) {
    string limpa;
    
    for (int i = 0; i < desc.length(); i++) {  
        char c = desc[i];                      

        if (!isspace(c)) {                     
            limpa += tolower(c);       
        }
    }
    return limpa;
}

void consultaPalindromo(struct produtos p[], int contP) {

    for (int i = 0; i < contP; i++) {
        string palavra = normalizarDescricao(p[i].descricao);  
        int tamanho = palavra.length();                       
        bool palindromo = true;

        for (int j = 0, k = tamanho - 1; j < k; j++, k--) {    
            if (palavra[j] != palavra[k]) {
            	palindromo = false;
                break;
            }
        }

        if (palindromo == true) {
            cout << "\n--- Produto com descrição palíndroma ---\n";
            cout << "Código: " << p[i].codigo << endl;
            cout << "Descrição: " << p[i].descricao << endl;
            cout << "Tipo: " << p[i].tipoProduto << endl;
            cout << "Fornecedor: " << p[i].codigoDoFornecedor << endl;
            cout << "Estoque: " << p[i].qtdeEstoque << "/" << p[i].estoqueMin << "-" << p[i].estoqueMax << endl;
            cout << "Valor unitário: R$ " << p[i].valorUnitario << endl;
        }
    }
}


void menu(tiposProdutos tipos[], produtos prod[], cidades cid[], fornecedores forn[]){

	struct fornecedores forn2[50], forn3[50];

	struct produtos prod2[50], prod3[50];
	
	int contadorForn = 2;
	int contadorProd = 2;
	int contadorTipos = 2;
	int contadorCid = 2;
	
	int opcao;
    bool sair = false; 

    while (!sair) {
        cout << "\n ||+------------------------ MENU ------------------------+||" << endl << endl;
        cout << " (1) -                   Leitura dos dados" << endl;
        cout << " (2) -         Incluir novos registros em 'Fornecedores'" << endl;
        cout << " (3) -         Incluir novos registros em 'Produtos'" << endl;
        cout << " (4) -                    Realizar venda" << endl;
        cout << " (5) -             Consultar produto em estoque" << endl;
        cout << " (6) -    Consultar todos os produtos abaixo do estoque mínimo" << endl;
        cout << " (7) -    Consultar produtos cuja descricao seja um palíndromo" << endl;
        cout << " (8) -                          Sair" << endl;
        cout << "\n Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
            	
            	lerTipoDeProduto(tipos, contadorTipos);
                lerCidades(cid, contadorCid);
                lerFornecedor(forn, contadorForn);
                lerProduto(prod, contadorProd);
                
                break;
                
            case 2:
            	
                incluirRegistrosFornecedor(forn, contadorForn, forn2, forn3, cid);
               
                break;
                
            case 3:
            	
            	incluirRegistrosProdutos(prod, contadorProd, prod2, prod3, forn, contadorForn);
             
                break;
                
            case 4:
            	
            	vendaProduto(prod, contadorProd);
              
                break;
                
            case 5:
            	
            	consultaEstoque(prod, contadorProd);
               
                break;
                
            case 6:
            	
            	consultaProdutosAbaixoDoMinimo(prod, contadorProd, forn, contadorForn);
             
                break;
                
            case 7:
            	
            	 consultaPalindromo(prod, contadorProd);
                
                break;
                
            case 8:
                cout << endl << " Encerrando o programa..." << endl;
                sair = true;
                break;
                
            default:
                cout << endl << " Opção invalida. Tente novamente." << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    tiposProdutos tiposProdutosArray[50]; 
    produtos produtosArray[50]; 
    fornecedores fornecedoresArray[50];
    cidades cidadesArray[50];
    
   // cidades cidadesArray[50] = {
	  //  {1, "São Paulo", "SP"},
	   // {2, "Rio de Janeiro", "RJ"},
	  //  {3, "Belo Horizonte", "MG"},
	   // {4, "Curitiba", "PR"},
	  //  {5, "Porto Alegre", "RS"},
	   // {6, "Assis", "SP"},
	 //   {7, "Palmital", "SP"},
	 //   {8, "Cãndido Mota", "SP"},
	 //   {9, "Salvador", "BA"},
	 //   {10, "Rio Branco", "AC"}
 //   };
    
   //   produtos produtosArray[50] = {
     //   {1, "Arara rara", "Brinquedo", 200, 150, 50, 300, 1.99},
     //   {2, "Estojo", "Papelaria", 201, 80, 20, 150, 15.50},
     //   {3, "Teclado", "Eletrônicos", 301, 25, 10, 50, 49.90},
    //    {4, "Ovo", "Alimento", 400, 10, 15, 100, 32.75}
  //  };
    
    menu(tiposProdutosArray, produtosArray, cidadesArray, fornecedoresArray);

}
