public class Calculator {

    public static String calculate(double num1, String op, double num2) {
        double result;

        switch (op) {
            case "+":
                result = num1 + num2;
                break;
            case "-":
                result = num1 - num2;
                break;
            case "*":
                result = num1 * num2;
                break;
            case "/":
                if (num2 == 0) {
                    return "Erro: divisão por zero!";
                }
                result = num1 / num2;
                break;
            default:
                return "Operação inválida!";
        }

        return "Resultado: " + result;
    }
}
