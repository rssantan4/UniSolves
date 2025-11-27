import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class CalculatorServer {
    public static void main(String[] args) {
        int port = 9876;

        try (DatagramSocket serverSocket = new DatagramSocket(port)) {
            System.out.println("Servidor UDP de Calculadora iniciado na porta " + port);

            byte[] receiveBuffer = new byte[1024];

            while (true) {
                // 1. Receber mensagem 
                DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
                serverSocket.receive(receivePacket);

                String received = new String(receivePacket.getData(), 0, receivePacket.getLength());
                System.out.println("Recebido: " + received);

                // 2. Interpretar mensagem (num1 op num2)
                String[] parts = received.trim().split(" ");
                double num1 = Double.parseDouble(parts[0]);
                String op = parts[1];
                double num2 = Double.parseDouble(parts[2]);

                // 3. Calcular usando a classe Calculator
                String response = Calculator.calculate(num1, op, num2);

                // 4. Enviar resposta de volta para o cliente
                byte[] sendBuffer = response.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(
                        sendBuffer, sendBuffer.length,
                        receivePacket.getAddress(), receivePacket.getPort());
                serverSocket.send(sendPacket);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
