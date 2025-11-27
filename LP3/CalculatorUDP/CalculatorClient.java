import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class CalculatorClient {
    public static void main(String[] args) {
        String host = "localhost"; // ou IP do servidor
        int port = 9876;

        try (DatagramSocket clientSocket = new DatagramSocket(); Scanner sc = new Scanner(System.in)) {
            InetAddress serverAddress = InetAddress.getByName(host);

            // 1. Ler entrada do usuário
            System.out.println("Digite a expressão no formato: num1 op num2");
            System.out.println("Exemplo: 10 + 5");
            String expression = sc.nextLine();

            // 2. Enviar mensagem 
            byte[] sendBuffer = expression.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, serverAddress, port);
            clientSocket.send(sendPacket);

            // 3. Esperar resposta
            byte[] receiveBuffer = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
            clientSocket.receive(receivePacket);

            // 4. Exibir resposta
            String response = new String(receivePacket.getData(), 0, receivePacket.getLength());
            System.out.println("Resposta do servidor: " + response);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
