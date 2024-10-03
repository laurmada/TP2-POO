import java.io.*;
import java.util.*;

public class Jogo {
    private Palavra palavraAtual;
    private int tentativasRestantes;
    private Set<Character> letrasEscolhidas;
    private int vitorias;
    private int derrotas;
    private String nomeJogador;

    // construtor de um jogo
    public Jogo(String nomeJogador) {
        // define as tentativas restantes do jogo como 6
        this.tentativasRestantes = 6;
        // inicializa um hashset para conter as letras escolhidas, ja que elas nao podem se repetir
        this.letrasEscolhidas = new HashSet<>();
        //inicializa nome do jogador
        this.nomeJogador = nomeJogador;
        // chama o metodo que carrega a pontuacao do jogador
        carregarPontuacao(nomeJogador);
        // chama o metodo que seleciona uma palavra aleatoria para a rodada atual
        selecionarPalavraAleatoria();
    }

    // metodo para selecionar uma palavra aleatoria
    public void selecionarPalavraAleatoria() {
        // cria um array de string, le o arquivo e armazena as palavras do arquivo no array
        List<String> palavras = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader("palavras.txt"))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                // as palavras devem ser em letra maiuscula e sem espacos em branco no inicio ou no final
                palavras.add(linha.trim().toUpperCase());
            }
        } catch (IOException e) {
            System.err.println("Erro ao carregar palavras: " + e.getMessage());
        }
        // sorteamos uma palavra no vetor gerado
        Random random = new Random();  // cria um objeto Random
        int indiceAleatorio = random.nextInt(palavras.size());  // gera um índice aleatório na lista de palavras
        String palavraSelecionada = palavras.get(indiceAleatorio);  // seleciona a palavra correspondente ao índice gerado
        palavraAtual = new Palavra(palavraSelecionada); // inicia um objeto palavra com a palavra atual
    }

    // verificando a letra que o usuario clicou
    public boolean verificarLetra(char letra) {
        // adicionando a letra escolhida ao set de letras
        letrasEscolhidas.add(letra);
        // chama metodo da palavra que verifica se existe a letra na palavra
        boolean acertou = palavraAtual.revelarLetra(letra);
        // caso a letra seja errada, diminui uma tentativa do usuario
        if (!acertou) {
            tentativasRestantes--;
        }
        return acertou;
    }

    // metodo que verifica se o jogo finalizou
    public boolean jogoTerminado() {
        return tentativasRestantes == 0 || palavraAtual.foiRevelada();
    }

    public void atualizarPontuacao(boolean venceu) {
        if (venceu) {
            this.vitorias++;
        } else {
            this.derrotas++;
        }
        atualizarArquivoPontuacao();
    }

    private void atualizarArquivoPontuacao() {
        File arquivo = new File("pontuacao.txt");
        List<String> linhas = new ArrayList<>();

        // Ler todas as linhas do arquivo
        try (BufferedReader reader = new BufferedReader(new FileReader(arquivo))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                String[] partes = linha.split(":");
                if (partes[0].equals(nomeJogador)) {
                    linha = nomeJogador + ":" + vitorias + ":" + derrotas; // Atualiza a linha do jogador
                }
                linhas.add(linha);
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo pontuacao.txt: " + e.getMessage());
        }

        // Sobrescrever o arquivo com as linhas atualizadas
        try (PrintWriter writer = new PrintWriter(new FileWriter(arquivo))) {
            for (String linha : linhas) {
                writer.println(linha);
            }
        } catch (IOException e) {
            System.out.println("Erro ao atualizar o arquivo pontuacao.txt: " + e.getMessage());
        }
    }

    // Método para carregar pontuação do jogador
    public void carregarPontuacao(String nomeJogador) {
        File arquivo = new File("pontuacao.txt");

        if (!arquivo.exists()) {
            try {
                arquivo.createNewFile();
            } catch (IOException e) {
                System.out.println("Erro ao criar o arquivo pontuacao.txt: " + e.getMessage());
                return;
            }
        }

        boolean jogadorEncontrado = false;

        try (BufferedReader reader = new BufferedReader(new FileReader(arquivo))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                String[] partes = linha.split(":");
                if (partes[0].equals(nomeJogador)) {
                    this.vitorias = Integer.parseInt(partes[1]);
                    this.derrotas = Integer.parseInt(partes[2]);
                    jogadorEncontrado = true;
                    break;
                }
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo pontuacao.txt: " + e.getMessage());
        }

        // Se o jogador não for encontrado, adiciona-o ao arquivo com pontuação inicial de 0
        if (!jogadorEncontrado) {
            adicionarNovoJogador();
        }
    }

    private void adicionarNovoJogador() {
        try (PrintWriter writer = new PrintWriter(new FileWriter("pontuacao.txt", true))) {
            writer.println(nomeJogador + ":0:0");
        } catch (IOException e) {
            System.out.println("Erro ao adicionar novo jogador ao arquivo pontuacao.txt: " + e.getMessage());
        }
    }

    // Método para salvar pontuação do jogador
    public void salvarPontuacao(String nomeJogador) {
        try (BufferedReader br = new BufferedReader(new FileReader("pontuacao.txt"));
             BufferedWriter bw = new BufferedWriter(new FileWriter("pontuacao.tmp"))) {

            String linha;
            boolean jogadorEncontrado = false;
            while ((linha = br.readLine()) != null) {
                String[] dados = linha.split(",");
                if (dados[0].equalsIgnoreCase(nomeJogador)) {
                    linha = nomeJogador + "," + vitorias + "," + derrotas;
                    jogadorEncontrado = true;
                }
                bw.write(linha);
                bw.newLine();
            }

            // Se o jogador não foi encontrado, adiciona-o ao final
            if (!jogadorEncontrado) {
                bw.write(nomeJogador + "," + vitorias + "," + derrotas);
                bw.newLine();
            }
        } catch (IOException e) {
            System.err.println("Erro ao salvar pontuação: " + e.getMessage());
        }

        // Renomeia o arquivo temporário para substituir o original
        new File("pontuacao.tmp").renameTo(new File("pontuacao.txt"));
    }


    // Métodos para obter vitórias e derrotas
    public int getVitorias() {
        return this.vitorias;
    }

    public int getDerrotas() {
        return this.derrotas;
    }

    // metodo que retorna a quantidade de tentativas que o usuario possui
    public int getTentativasRestantes() {
        return tentativasRestantes;
    }

    // metodo que retorna a palavra com lacunas
    public String getPalavraComLacunas() {
        return palavraAtual.getPalavraComLacunas();
    }


    public Set<Character> getLetrasEscolhidas() {
        return letrasEscolhidas;
    }
    public char revelarLetraAleatoria() {
        List<Integer> indicesNaoRevelados = new ArrayList<>();
        for (int i = 0; i < palavraAtual.getTamanho(); i++) {
            if (palavraAtual.getLetraNaPosicao(i) == '_') {
                indicesNaoRevelados.add(i);  // Adiciona os índices que ainda não foram revelados
            }
        }

        if (!indicesNaoRevelados.isEmpty()) {
            Random random = new Random();
            int indiceAleatorio = indicesNaoRevelados.get(random.nextInt(indicesNaoRevelados.size()));
            char letraRevelada = palavraAtual.revelarLetraNaPosicao(indiceAleatorio);
            letrasEscolhidas.add(letraRevelada);  // Adiciona a letra revelada ao conjunto de letras escolhidas
            return letraRevelada;
        }

        return 0;  // Retorna 0 se não houver mais letras para revelar
    }

}
