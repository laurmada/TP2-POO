import java.io.*;
import java.util.*;

public class Jogo {
    private Palavra palavraAtual;
    private int tentativasRestantes;
    private Set<Character> letrasEscolhidas;
    private int vitorias;
    private int derrotas;

    // construtor de um jogo
    public Jogo() {
        // define as tentativas restantes do jogo como 6
        this.tentativasRestantes = 6;
        // inicializa um hashset para conter as letras escolhidas, ja que elas nao podem se repetir
        this.letrasEscolhidas = new HashSet<>();
        // chama o metodo que carrega a pontuacao do jogador
        carregarPontuacao();
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
            vitorias++;
        } else {
            derrotas++;
        }
        salvarPontuacao();
    }

    private void carregarPontuacao() {
        try (BufferedReader br = new BufferedReader(new FileReader("pontuacao.txt"))) {
            vitorias = Integer.parseInt(br.readLine());
            derrotas = Integer.parseInt(br.readLine());
        } catch (IOException | NumberFormatException e) {
            vitorias = 0;
            derrotas = 0;
        }
    }

    private void salvarPontuacao() {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter("pontuacao.txt"))) {
            bw.write(vitorias + "\n" + derrotas);
        } catch (IOException e) {
            System.err.println("Erro ao salvar pontuação: " + e.getMessage());
        }
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

    public int getVitorias() {
        return vitorias;
    }

    public int getDerrotas() {
        return derrotas;
    }
}
