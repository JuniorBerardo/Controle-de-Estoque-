# 📦 Sistema de Controle de Estoque em C++

Este é um projeto acadêmico de um sistema de Controle de Estoque desenvolvido inteiramente em C++. A aplicação é executada via console e permite gerenciar produtos, fornecedores, vendas e relatórios básicos. Todos os dados são manipulados em memória durante a execução do programa, utilizando vetores e `structs`.

---

## ✨ Funcionalidades

O sistema é controlado por um menu interativo e oferece as seguintes funcionalidades:

* **1. Leitura de Dados:** Permite a inserção manual dos dados iniciais do sistema (Tipos de Produto, Cidades, Fornecedores e Produtos).
* **2. Inclusão de Fornecedores:** Adiciona novos fornecedores de forma ordenada na base de dados. Inclui uma **validação de CNPJ** para garantir que o número inserido seja matematicamente válido.
* **3. Inclusão de Produtos:** Adiciona novos produtos de forma ordenada, mantendo a classificação por código.
* **4. Módulo de Vendas:** Realiza a venda de um produto específico, consultando o estoque e atualizando a quantidade disponível após a confirmação.
* **5. Consulta de Estoque:** Verifica o valor total em estoque (quantidade * valor unitário) de um produto específico.
* **6. Relatório de Reposição:** Gera um relatório completo de todos os produtos que estão com a quantidade abaixo do estoque mínimo definido. O relatório sugere a quantidade a ser comprada para atingir o estoque máximo e calcula o valor total do investimento necessário.
* **7. Consulta de Palíndromos:** Uma função especial que varre o cadastro e localiza produtos cuja descrição é um **palíndromo** (lê-se da mesma forma de trás para frente, como "ovo" e "arara").

---

## ⚙️ Algoritmos e Conceitos Implementados

Este projeto aplica diversos conceitos de algoritmos e estruturas de dados:

* **Estruturas (Structs):** Utilização de `structs` para a modelagem dos dados, representando entidades como `Produto`, `Fornecedor`, `Cidade`, etc.
* **Algoritmo de Intercalação (Merge):** As funções de inclusão de novos produtos e fornecedores utilizam o método de intercalação para inserir os novos registros nos vetores principais, mantendo-os sempre ordenados por código.
* **Busca Binária:** Implementação de funções de busca binária para localizar registros (produtos, fornecedores) de forma mais eficiente nos vetores ordenados.
* **Validação de CNPJ:** Implementação do algoritmo de validação padrão para verificar a autenticidade de um número de CNPJ.
* **Verificação de Palíndromo:** Algoritmo para normalizar uma string (removendo espaços e convertendo para minúsculas) e verificar se ela é palíndroma.

---

## 🚀 Como Compilar e Executar

Para compilar e executar este projeto, você precisará de um compilador C++, como o **g++** (geralmente incluído no MinGW para Windows ou disponível por padrão no Linux).

1.  **Abra um terminal** (Prompt de Comando, PowerShell, ou Terminal do Linux) na pasta onde o arquivo `.cpp` está localizado.

2.  **Compile o código** usando o seguinte comando. Isso criará um arquivo executável chamado `estoque`.
    ```bash
    g++ "Controle-de-Estoque.cpp" -o estoque
    ```
  

3.  **Execute o programa:**
    * No **Windows**:
        ```bash
        .\estoque.exe
        ```
    * No **Linux ou macOS**:
        ```bash
        ./estoque
        ```

---

## 📋 Como Usar

Após a execução, um menu interativo será exibido no console.
1.  Digite o número da opção desejada e pressione `Enter` para prosseguir.
2.  A primeira etapa recomendada é a **"Leitura dos dados" (Opção 1)** para popular o sistema com informações iniciais antes de testar as outras funcionalidades.
3.  Siga as instruções de cada opção para interagir com o sistema.

---

## 👨‍💻 Autor

 **[Junior Ivair Berardo]** e **[Vi Nogueira de Souza]**
