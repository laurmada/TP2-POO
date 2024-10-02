import javax.swing.*;
import java.awt.*;

public class Forca {
    // atributo da classe Forca
    private int estadoAtual;

    // construtor da classe forca, iniciando o estado atual da forca como 0
    public Forca() {
        this.estadoAtual = 0;
    }

    // metodo que atualiza o estado atual da forca
    public void atualizarForca(boolean acertou) {
        // incrementa o estado atual do jogo
        if (!acertou && estadoAtual < 6) {
            estadoAtual++;
        }
    }

    // metodo que escolhe a imagem da forca com base no estado atual
    public ImageIcon getImagemForca() {
        // alterando o caminho da imagem com base no estado
        String caminhoImagem = "imagens/forca" + estadoAtual + ".png";
        ImageIcon imagem = new ImageIcon(caminhoImagem);
        Image img = imagem.getImage().getScaledInstance(200, 200, Image.SCALE_SMOOTH); // alterando tamanho
        return new ImageIcon(img); // retorna a imagem
    }
}
