import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class InterfaceGrafica {
    private Jogo jogo;
    private Forca forca;

    private JFrame frame;
    private JPanel painelForca, painelInfo, painelLetras, painelTitulo;
    private JLabel labelForca, labelPalavra, labelDica, labelLetrasDigitadas, labelTitulo;
    private JButton btnNovoJogo, btnVerificar;

    public InterfaceGrafica() {
        this.jogo = new Jogo();
        this.forca = new Forca();
        inicializarComponentes();
    }

    private void inicializarComponentes() {
        frame = new JFrame("Jogo da Forca");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setLayout(null);  // Usando layout nulo para posicionar manualmente
        ImageIcon originalIcon = new ImageIcon("imagens/forca0.png");
        Image originalImage = originalIcon.getImage();  // Obtém a imagem original
        Image scaledImage = originalImage.getScaledInstance(200, 300, Image.SCALE_SMOOTH);  // Redimensiona a imagem (largura, altura)
        ImageIcon scaledIcon = new ImageIcon(scaledImage);  // Cria um novo ImageIcon com a imagem redimensionada

        // Painel da Forca (esquerda superior)
        painelForca = new JPanel();
        painelForca.setBounds(50, 50, 200, 200);  // Posicionamento exato
        labelForca = new JLabel(scaledIcon);  // Define o novo ImageIcon no JLabel  // Ajuste o caminho para sua imagem
        painelForca.add(labelForca);
        frame.add(painelForca);

        // Painel do Título (direita superior)
        painelTitulo = new JPanel();
        painelTitulo.setBounds(300, 50, 200, 200);  // Ajustando o posicionamento
        labelTitulo = new JLabel(new ImageIcon("ghgh"));  // Ajuste o caminho para sua imagem
        painelTitulo.add(labelTitulo);
        frame.add(painelTitulo);

        // Painel de Informações (esquerda inferior)
        painelInfo = new JPanel(new GridLayout(3, 1));
        painelInfo.setBounds(50, 300, 200, 150);  // Posicionamento manual
        painelInfo.setBackground(new Color(245, 245, 245));

        //PRECISA SER IMPLEMENTADO
        labelDica = new JLabel("Dica: " );
        labelPalavra = new JLabel("Palavra: " + jogo.getPalavraComLacunas());
        labelLetrasDigitadas = new JLabel("Letras Digitadas: ");
        painelInfo.add(labelDica);
        painelInfo.add(labelPalavra);
        painelInfo.add(labelLetrasDigitadas);
        frame.add(painelInfo);

        // Botão Novo Jogo (abaixo das informações)
        btnNovoJogo = new JButton("Novo Jogo");
        btnNovoJogo.setBounds(50, 460, 200, 30);  // Posicionamento manual
        frame.add(btnNovoJogo);

        // Painel de Letras (direita inferior)
        painelLetras = new JPanel(new GridLayout(4, 7, 5, 5));
        painelLetras.setBounds(300, 300, 360, 150);  // Posicionamento manual para combinar com a imagem
        painelLetras.setBackground(new Color(230, 230, 250));

        for (char letra = 'A'; letra <= 'Z'; letra++) {
            char letraFinal = letra;
            JButton botaoLetra = new JButton(String.valueOf(letraFinal));  // Definindo o texto do botão
            botaoLetra.setFont(new Font("Arial", Font.PLAIN, 14));
            botaoLetra.setBackground(Color.WHITE);
//            botaoLetra.setPreferredSize(new Dimension(1809, 180));  // Ajuste de tamanho do botão para caber a letra

            botaoLetra.addActionListener(e -> {
                verificarLetra(letraFinal);
                botaoLetra.setEnabled(false);
            });

            painelLetras.add(botaoLetra);
        }
        frame.add(painelLetras);

        // Botão Verificar (ao lado dos botões de letras)
        btnVerificar = new JButton("Dica");
        btnVerificar.setBounds(670, 300, 100, 50);  // Posicionamento manual
        frame.add(btnVerificar);
        //ATUALIZAR A FORCA forca.atualizarForca(acertou);
        frame.setVisible(true);
    }

    private void verificarLetra(char letra) {
        boolean acertou = jogo.verificarLetra(letra);
        forca.atualizarForca(acertou);
        atualizarInterface();
    }

    private void atualizarInterface() {
        labelForca.setIcon(forca.getImagemForca());
        labelPalavra.setText("Palavra: " + jogo.getPalavraComLacunas());
        labelLetrasDigitadas.setText("Letras Digitadas: " );

        if (jogo.jogoTerminado()) {
            String mensagem = jogo.getTentativasRestantes() > 0 ? "Você venceu!" : "Você perdeu!";
            int option = JOptionPane.showConfirmDialog(frame, mensagem + "\nDeseja jogar novamente?", "Fim de jogo", JOptionPane.YES_NO_OPTION);
            if (option == JOptionPane.YES_OPTION) {
            //METODO REINICIAR
                atualizarInterface();
            } else {
                frame.dispose();
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(InterfaceGrafica::new);
    }
}
