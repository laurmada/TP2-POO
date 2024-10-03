import java.util.Arrays;

public class Palavra {
    // atributos da classe palavra
    private String palavraOriginal;
    private char[] palavraAtual;

    // construtor da classe palavra
    public Palavra(String palavra) {
        // palavraOriginal recebe a palavra completa vinda do arquivo
        this.palavraOriginal = palavra;
        // palavraAtual recebe um vetor de caracteres contendo apenas _
        this.palavraAtual = new char[palavra.length()];
        Arrays.fill(this.palavraAtual, '_');
    }

    // metodo que retorna true e revela as ocorrencias da letra se o usuario acertou e retorna false se errou
    public boolean revelarLetra(char letra) {
        boolean acertou = false;
        // percorre a palavra original para encontrar as ocorrencias da letra
        for (int i = 0; i < palavraOriginal.length(); i++) {
            // se encotrar pelo menos uma ocorrencia, revela a letra e acertou recebe true
            if (palavraOriginal.charAt(i) == letra) {
                palavraAtual[i] = letra;
                acertou = true;
            }
        }
        return acertou;
    }

    // metodo que indica se a palavra foi revelada
    public boolean foiRevelada() {
        return palavraOriginal.equals(new String(palavraAtual)); // compara a palavra original com a palavra atual
    }

    // metodo que retorna a palavra com lacunas
    public String getPalavraComLacunas() {
        // criacao de uma nova string para conter _ e espacos
        StringBuilder palavraComEspacos = new StringBuilder();
        // percorrendo a palavraAtual para adicionar um espaco entre cada letra
        for (int i = 0; i < palavraAtual.length; i++) {
            palavraComEspacos.append(palavraAtual[i]);
            if (i < palavraAtual.length - 1) {
                palavraComEspacos.append(' '); // adiciona o espaco
            }
        }
        return palavraComEspacos.toString();
    }
    public char revelarLetraNaPosicao(int posicao) {
        palavraAtual[posicao] = palavraOriginal.charAt(posicao);
        return palavraAtual[posicao];
    }

    // Método para obter a letra na posição especificada (para verificar se está '_')
    public char getLetraNaPosicao(int posicao) {
        return palavraAtual[posicao];
    }

    // Método para obter o tamanho da palavra
    public int getTamanho() {
        return palavraAtual.length;
    }
}
