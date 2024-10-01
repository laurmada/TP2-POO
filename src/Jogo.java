import java.io.*;
import java.util.*;

public class Jogo {
    private Palavra palavraAtual;
    private int tentativasRestantes;
    private Set<Character> letrasEscolhidas;
    private int vitorias;
    private int derrotas;

    public Jogo() {
        this.tentativasRestantes = 6;
        this.letrasEscolhidas = new HashSet<>();
        carregarPontuacao();
        selecionarPalavraAleatoria();
    }

    public void selecionarPalavraAleatoria() {
        List<String> palavras = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader("palavras.txt"))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                palavras.add(linha.trim().toUpperCase());
            }
        } catch (IOException e) {
            System.err.println("Erro ao carregar palavras: " + e.getMessage());
        }
        if (!palavras.isEmpty()) {
            String palavraSelecionada = palavras.get(new Random().nextInt(palavras.size()));
            palavraAtual = new Palavra(palavraSelecionada);
        }
    }

    public boolean verificarLetra(char letra) {
        letra = Character.toUpperCase(letra);
        if (letrasEscolhidas.contains(letra)) {
            return false;
        }
        letrasEscolhidas.add(letra);
        boolean acertou = palavraAtual.revelarLetra(letra);
        if (!acertou) {
            tentativasRestantes--;
        }
        return acertou;
    }

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

    public int getTentativasRestantes() {
        return tentativasRestantes;
    }

    public String getPalavraComLacunas() {
        return palavraAtual.getPalavraComLacunas();
    }

    public Set<Character> getLetrasEscolhidas() {
        return letrasEscolhidas;
    }

    public int getVitorias() {
        return vitorias;
    }

    public int getDerrotas() {
        return derrotas;
    }
}
