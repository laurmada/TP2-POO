import java.util.Arrays;

public class Palavra {
    private String palavraOriginal;
    private char[] palavraAtual;

    public Palavra(String palavra) {
        this.palavraOriginal = palavra;
        this.palavraAtual = new char[palavra.length()];
        Arrays.fill(this.palavraAtual, '_');
    }

    public boolean revelarLetra(char letra) {
        boolean acertou = false;
        for (int i = 0; i < palavraOriginal.length(); i++) {
            if (palavraOriginal.charAt(i) == letra) {
                palavraAtual[i] = letra;
                acertou = true;
            }
        }
        return acertou;
    }

    public boolean foiRevelada() {
        return palavraOriginal.equals(new String(palavraAtual));
    }

    public String getPalavraComLacunas() {
        return new String(palavraAtual);
    }
}
