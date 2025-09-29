# Atividade - Iluminação em 3D

1) Renderize uma cena com os seguintes requisitos: 
    1) Carregue um bule 3D. 
    2) Defina uma cor (material) para o bule. 
    3) Adicione as iluminações na cena: 
        - Ambiente (para a cena); 
        - Especular; 
        - Difusa. 
    > Obs: posicione a iluminação para que seja perceptível a sombra no objeto. 
    4) Adicione a atenuação radial. 
    5) Crie a cena com quatro viewports de tamanhos iguais, cada uma mostrando um plano diferente: XY, XZ, YZ e perspectiva. As cenas devem ter animações contínuas de rotação do bule (em relação ao centro do objeto) no eixo de rotação Y (ou seja, rotações horizontais).

Obs: a cena deve ser semelhante ao exemplo abaixo.

<img src="./light_example.png" style="display: block;margin-left: auto;margin-right: auto;width: 50%;">


## Instalação

Depende do seu sistema operacional. Siga as instruções dadas pela professora: MingW e GLUT (FreeGLUT) no Windows, e G++ com GLU no Linux.
Também recomendo a instalação do CMake para automatizar a build nos seus sistemas.

> [!TIP]
> Se você está usando o VsCode, você pode usar as tasks configuradas no repositório para build e execução. - **Necessário ter o Python e demais requisitos instalados.**

### Visual Studio

Na raiz do projeto execute o script abaixo no powershell:
```powershell
.\scripts\setup.ps1
```
Ele fará a instalação e vínculo das bibliotecas na sua IDE usando [vcpkg](https://vcpkg.io/). Após a configuração, abra a janela do Visual Studio e escolha `File` > `Open` > `CMake` e selecione o `CMakeLists.txt` do projeto.

> [!WARNING]
> Os arquivos de configuração do Visual Studio **não devem ser incluídos** no repositório remoto! Crie um branch do projeto se achar necessário!

----

> [!IMPORTANT]
> Os scripts referenciados abaixo se encontra na pasta [scripts/](./scripts/). Os comandos devem ser executados na pasta raiz do projeto (onde se encontra `README.md` e `build.py`).

----

## Build

> [!NOTE]
> Se você possui o Python instalado na sua máquina use o script `build.py`
> para executar o script de compilação correto. Você pode pular a explicação das seções abaixo. - **CMake necessário**.


### Windows

Execute `build.bat` ou compile com **MingW** com as flags necessárias. Você também pode usar o script CMake para compilar o seu projeto no Visual Studio com sua própria _solution_.

### Linux

Execute `build.sh`:
```bash
chmod +x ./build.sh
./build.sh
```
que irá invocar o CMake para gerenciar a build, ou compile com G++ (ou outro compilador de sua escolha) com as flags necessárias.

> [!TIP]
> No VSCode: Abra a paleta de comandos `Ctrl+Shift+P` > `Run Task` > `Build (Python Wrapper)`

----

## Execução

### Windows

Execute `run.bat` ou execute o programa .exe compilado diretamente - deve estar em `build/MyOpenGLApp.exe`.

### Linux

Execute `run.sh`:
```bash
chmod +x ./run.sh
./run.sh
```
ou inicie o executável compilado diretamente - deve estar em `build/MyOpenGLApp.exe`.

> [!TIP]
> No VSCode: Abra a paleta de comandos `Ctrl+Shift+P` > `Run Task` > `Run App (Python Wrapper)`
