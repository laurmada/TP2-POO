import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class InterfaceGrafica {
    // atributos da classe InterfaceGrafica
    private Jogo jogo;
    private Forca forca;
    private JFrame frame;
    private JPanel painelForca, painelInfo, painelLetras, painelTitulo;
    private JLabel labelForca, labelPalavra, labelDica, labelLetrasDigitadas, labelTitulo, labelTentativasRestantes;
    private JButton btnNovoJogo, btnVerificar;
    private String nomeJogador;


    // construtor da interface grafica
    public InterfaceGrafica(String nomeJogador) {
        // inicializa um objeto jogo e um objeto forca
        this.jogo = new Jogo();
        this.forca = new Forca();
        this.nomeJogador = nomeJogador;
        // chama o metodo que inicializa os componentes
        inicializarComponentes();
    }

    // metodo que inicializa os componentes graficos
    private void inicializarComponentes() {
        // inicializando a janela, definindo seu tamanho e definindo layout como nulo
        frame = new JFrame("Jogo da Forca");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setLayout(null);

        labelTentativasRestantes = new JLabel("Tentativas restantes: " + jogo.getTentativasRestantes());
        labelTentativasRestantes.setFont(new Font("Arial", Font.BOLD, 14));
        labelTentativasRestantes.setBounds(50, 20, 200, 30); // Ajuste a posição conforme necessário
        frame.add(labelTentativasRestantes);

        // obtendo a imagem inicial da forca (forca vazia)
        ImageIcon originalIcon = new ImageIcon("imagens/forca0.png");
        Image originalImage = originalIcon.getImage();
        // alterando escala da imagem
        Image scaledImage = originalImage.getScaledInstance(200, 200, Image.SCALE_SMOOTH);
        ImageIcon scaledIcon = new ImageIcon(scaledImage);

        // criando o painel onde estara a imagem da forca (superior esquerdo)
        painelForca = new JPanel();
        painelForca.setBounds(50, 50, 200, 200); // definindo tamanho e posicao do painel
        // adicionando a imagem no painel
        labelForca = new JLabel(scaledIcon);
        painelForca.add(labelForca);
        // adicionando o painel no frame
        frame.add(painelForca);

        // obtendo a imagem da logo do jogo
        ImageIcon logoJogo = new ImageIcon("imagens/titulo.png");
        Image imagemLogo = logoJogo.getImage();
        // alterando escala da imagem
        Image imagemEscalada = imagemLogo.getScaledInstance(200, 200, Image.SCALE_SMOOTH);
        ImageIcon iconeEscalado = new ImageIcon(imagemEscalada);

        // painel da logo do jogo (superior direito)
        painelTitulo = new JPanel();
        painelTitulo.setBounds(300, 50, 200, 200);  // definindo tamanho e posicao do painel
        // adicionando a imagem no painel
        labelTitulo = new JLabel(iconeEscalado);
        painelTitulo.add(labelTitulo);
        // adicionando o painel no frame
        frame.add(painelTitulo);

        // painel de informacoes (esquerda inferior)
        painelInfo = new JPanel(new GridLayout(4, 1)); // definindo tres linhas e uma coluna
        painelInfo.setBounds(50, 300, 200, 150);  // posicionamento do painel
        painelInfo.setBackground(new Color(245, 245, 245)); // cor do fundo do painel

        // criando informacoes que estarao dentro do painel de informacoes
        labelDica = new JLabel("Dica: " ); // texto de dica
        labelPalavra = new JLabel("Palavra: " + jogo.getPalavraComLacunas()); // imprimindo a palavra com as lacunas
        labelLetrasDigitadas = new JLabel("Letras já selecionadas: ");
        JLabel labelJogador = new JLabel("Jogador: " + nomeJogador);
        // adicionando cada label aos paineis
        painelInfo.add(labelDica);
        painelInfo.add(labelPalavra);
        painelInfo.add(labelLetrasDigitadas);
        // adicionando o painel ao frame
        frame.add(painelInfo);
        painelInfo.add(labelJogador);

        // botao para iniciar novo jogo ( abaixo do painel de informacoes)
        btnNovoJogo = new JButton("Novo Jogo");
        btnNovoJogo.setBounds(50, 460, 200, 30);  // definindo posicao do botao
        frame.add(btnNovoJogo); // adicionando botao ao frame
        btnNovoJogo.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                novoJogo(); // Chama o metodo que inicia um novo jogo
            }
        });

        // criando painel que ira conter todas as letras
        painelLetras = new JPanel(new GridLayout(4, 7, 5, 5)); // definindo numero de linhas e colunas e distancias
        painelLetras.setBounds(300, 300, 360, 150);  // posicao do painel
        painelLetras.setBackground(new Color(230, 230, 250)); // definindo cor de fundo

        // for para criar botao para cada letra
        for (char letra = 'A'; letra <= 'Z'; letra++) {
            char letraFinal = letra;
            JButton botaoLetra = new JButton(String.valueOf(letraFinal));  // definindo letra do botao
            botaoLetra.setFont(new Font("Arial", Font.PLAIN, 12)); // definindo fonte do botao
            botaoLetra.setBackground(Color.WHITE); // definindo cor de fundo do botao

            // adicionando actionListener para identificar quando o botao for clicado
            botaoLetra.addActionListener(new ActionListener() {
                @Override
                // metodo que sera chamado quando o botao for clicado
                public void actionPerformed(ActionEvent e) {
                    // verifica se o usuario acertou a letra e atualiza a forca
                    verificarLetra(letraFinal);
                    // desabilita o botao para clique
                    botaoLetra.setEnabled(false);
                }
            });

            // adiciona o botao de letra ao painel
            painelLetras.add(botaoLetra);
        }
        // adiciona o painel de letras ao frame
        frame.add(painelLetras);

        // Botão Verificar (ao lado dos botões de letras)
        btnVerificar = new JButton("Dica");
        btnVerificar.setBounds(50, 500, 200, 30);  // Posicionamento manual
        frame.add(btnVerificar);
        btnVerificar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                darDica(); // Chama o metodo que inicia um novo jogo
            }
        });
        frame.setVisible(true);
    }

    // metodo que verifica se o usuario acertou a letra clicada
    private void verificarLetra(char letra) {
        // cria booleano que verifica a letra na classe jogo
        boolean acertou = jogo.verificarLetra(letra);
        // atualiza a forca com base na resposta do usuario
        forca.atualizarForca(acertou);
        // atualiza a interface grafica
        atualizarInterface();
    }
    private void novoJogo() {
        jogo = new Jogo();  // Reinicia o objeto Jogo
        forca = new Forca();  // Reinicia o objeto Forca
        atualizarInterface();
        // Remove todos os componentes antigos do painel de letras
        painelLetras.removeAll();
        // Recria todos os botões de letras
        for (char letra = 'A'; letra <= 'Z'; letra++) {
            char letraFinal = letra;
            JButton botaoLetra = new JButton(String.valueOf(letraFinal));
            botaoLetra.setFont(new Font("Arial", Font.PLAIN, 12));
            botaoLetra.setBackground(Color.WHITE);
            // Adicionando o actionListener para identificar quando o botão for clicado
            botaoLetra.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Verifica se o usuário acertou a letra e atualiza a forca
                    verificarLetra(letraFinal);
                    // Desabilita o botão para clique
                    botaoLetra.setEnabled(false);
                }
            });
            // Adiciona o botão ao painel de letras
            painelLetras.add(botaoLetra);
        }
    }

    private void reiniciarJogo() {
        // Recria os objetos do jogo e da forca
        jogo = new Jogo();
        forca = new Forca();
        atualizarInterface();
        // Remove todos os componentes antigos do painel de letras
        painelLetras.removeAll();
        // Recria todos os botões de letras
        for (char letra = 'A'; letra <= 'Z'; letra++) {
            char letraFinal = letra;
            JButton botaoLetra = new JButton(String.valueOf(letraFinal));
            botaoLetra.setFont(new Font("Arial", Font.PLAIN, 12));
            botaoLetra.setBackground(Color.WHITE);
            // Adicionando o actionListener para identificar quando o botão for clicado
            botaoLetra.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Verifica se o usuário acertou a letra e atualiza a forca
                    verificarLetra(letraFinal);
                    // Desabilita o botão para clique
                    botaoLetra.setEnabled(false);
                }
            });
            // Adiciona o botão ao painel de letras
            painelLetras.add(botaoLetra);
        }
    }

    private void darDica() {
        char letraRevelada = jogo.revelarLetraAleatoria();
        if (letraRevelada != 0) {
            atualizarInterface();
        } else {
            JOptionPane.showMessageDialog(frame, "Nenhuma dica disponível. Todas as letras já foram reveladas.", "Dica", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    // metodo que atualiza a interface do jogo
    private void atualizarInterface() {
        // alterando a imagem da forca com base no estado atual
        labelForca.setIcon(forca.getImagemForca());
        // atualiza as tentativas restantes
        labelTentativasRestantes.setText("Tentativas restantes: " + jogo.getTentativasRestantes());
        // alterando a palavra com lacunas
        labelPalavra.setText("Palavra: " + jogo.getPalavraComLacunas());
        // alterando as letras que ja foram selecionadas usando html
        labelLetrasDigitadas.setText("<html>Letras já selecionadas:<br>" + jogo.getLetrasEscolhidas() + "</html>");

        // chama um metodo que verifica se o jogo acabou (usuario acertou palavra ou acabaram tentativas)
        if (jogo.jogoTerminado()) {
            // cria uma caixa de dialogo mostrando o resultado e dando opcao de jogar novamente
            String mensagem = jogo.getTentativasRestantes() > 0 ? "Você venceu!" : "Você perdeu!";
            int option = JOptionPane.showConfirmDialog(frame, mensagem + "\nDeseja jogar novamente?", "Fim de jogo", JOptionPane.YES_NO_OPTION);
            if (option == JOptionPane.YES_OPTION) {
                //METODO REINICIAR
                reiniciarJogo();
            } else {
                frame.dispose();
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame telaInicio = new JFrame("Jogo da Forca - Início");
            telaInicio.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            telaInicio.setSize(400, 300);
            telaInicio.setLayout(new GridLayout(3, 1));

            JPanel painelInicio = new JPanel();
            painelInicio.setLayout(new FlowLayout());

            JLabel labelBoasVindas = new JLabel("Bem-vindo ao Jogo da Forca!");
            labelBoasVindas.setFont(new Font("Arial", Font.BOLD, 18));
            painelInicio.add(labelBoasVindas);

            JPanel painelNome = new JPanel();
            painelNome.setLayout(new FlowLayout());
            JLabel labelNome = new JLabel("Digite seu nome: ");
            JTextField campoNomeJogador = new JTextField(20);
            painelNome.add(labelNome);
            painelNome.add(campoNomeJogador);

            JButton btnIniciarJogo = new JButton("Iniciar Jogo");
            btnIniciarJogo.addActionListener(e -> {
                String nomeJogador = campoNomeJogador.getText().trim();
                if (!nomeJogador.isEmpty()) {
                    telaInicio.dispose();  // Fecha a tela de boas-vindas
                    new InterfaceGrafica(nomeJogador);  // Inicia o jogo com o nome do jogador
                } else {
                    JOptionPane.showMessageDialog(telaInicio, "Por favor, insira um nome.", "Erro", JOptionPane.ERROR_MESSAGE);
                }
            });

            telaInicio.add(painelInicio);
            telaInicio.add(painelNome);
            telaInicio.add(btnIniciarJogo);

            telaInicio.setVisible(true);
        });
    }
}
