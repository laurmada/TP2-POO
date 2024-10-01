import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class InterfaceGrafica {
    private Jogo jogo;
    private Forca forca;

    private JFrame frame;
    private JPanel painelForca, painelJogo, painelLetras, painelInfo;
    private JLabel labelForca, labelPalavra, labelTentativas, labelVitorias, labelDerrotas;

    public InterfaceGrafica() {
        this.jogo = new Jogo();
        this.forca = new Forca();
        inicializarComponentes();
    }

    private void inicializarComponentes() {
        frame = new JFrame("Jogo da Forca");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(700, 400); // Aumentado o tamanho da janela para melhor acomodação
        frame.setLayout(new BorderLayout());

        painelForca = new JPanel();
        labelForca = new JLabel(forca.getImagemForca());
        painelForca.add(labelForca);

        painelJogo = new JPanel(new BorderLayout());
        labelPalavra = new JLabel(jogo.getPalavraComLacunas());
        labelPalavra.setFont(new Font("Arial", Font.BOLD, 24));
        labelPalavra.setHorizontalAlignment(SwingConstants.CENTER);
        painelJogo.add(labelPalavra, BorderLayout.NORTH);

        painelLetras = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5); // Espaçamento entre botões
        gbc.fill = GridBagConstraints.NONE;

        for (char letra = 'A'; letra <= 'Z'; letra++) {
            char letraFinal = letra;
            JButton botaoLetra = new JButton(String.valueOf(letraFinal));

            // Definir tamanho exato para o botão
            botaoLetra.setPreferredSize(new Dimension(50, 40)); // Largura aumentada para 50 pixels
            botaoLetra.setMinimumSize(new Dimension(50, 40));
            botaoLetra.setMaximumSize(new Dimension(50, 40));

            // Fonte ajustada
            botaoLetra.setFont(new Font("Arial", Font.PLAIN, 12)); // Diminuindo a fonte

            botaoLetra.addActionListener(e -> verificarLetra(letraFinal));

            gbc.gridx = (letra - 'A') % 9; // Colunas
            gbc.gridy = (letra - 'A') / 9; // Linhas
            painelLetras.add(botaoLetra, gbc);
        }

        painelInfo = new JPanel(new GridLayout(3, 1));
        labelTentativas = new JLabel("Tentativas Restantes: " + jogo.getTentativasRestantes());
        labelVitorias = new JLabel("Vitórias: " + jogo.getVitorias());
        labelDerrotas = new JLabel("Derrotas: " + jogo.getDerrotas());

        painelInfo.add(labelTentativas);
        painelInfo.add(labelVitorias);
        painelInfo.add(labelDerrotas);

        painelJogo.add(painelLetras, BorderLayout.CENTER);
        painelJogo.add(painelInfo, BorderLayout.SOUTH);

        frame.add(painelForca, BorderLayout.WEST);
        frame.add(painelJogo, BorderLayout.CENTER);

        frame.setVisible(true);
    }

    private void verificarLetra(char letra) {
        boolean acertou = jogo.verificarLetra(letra);
        forca.atualizarForca(acertou);

        atualizarInterface();
    }

    private void atualizarInterface() {
        labelForca.setIcon(forca.getImagemForca());
        labelPalavra.setText(jogo.getPalavraComLacunas());
        labelTentativas.setText("Tentativas Restantes: " + jogo.getTentativasRestantes());

        if (jogo.jogoTerminado()) {
            String mensagem = jogo.getTentativasRestantes() > 0 ? "Você venceu!" : "Você perdeu!";
            JOptionPane.showMessageDialog(frame, mensagem);
            jogo.atualizarPontuacao(jogo.getTentativasRestantes() > 0);
            frame.dispose();
            new InterfaceGrafica();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(InterfaceGrafica::new);
    }
}

