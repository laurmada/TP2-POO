import javax.swing.*;
import java.awt.*;

public class Forca {
    private int estadoAtual;

    public Forca() {
        this.estadoAtual = 0;
    }

    public void atualizarForca(boolean acertou) {
        if (!acertou && estadoAtual < 6) {
            estadoAtual++;
        }
    }

    public ImageIcon getImagemForca() {
        String caminhoImagem = "imagens/forca" + estadoAtual + ".png";
        ImageIcon imagem = new ImageIcon(caminhoImagem);
        Image img = imagem.getImage().getScaledInstance(150, 150, Image.SCALE_SMOOTH);
        return new ImageIcon(img);
    }
}
