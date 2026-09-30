/**
 * Clase de ejemplo para probar el analizador lexico.
 */
public class Ejemplo {
    private int contador;
    private double promedio = 3.14159;
    private String mensaje = "Hola\nMundo";
    private char inicial = 'A';
    private long codigoHex = 0xFF_AA;
    private int mascaraBin = 0b1010_1010;
    private int permisos = 0777;

    public Ejemplo() {
        contador = 0;
    }

    public void incrementar() {
        // suma uno al contador
        contador++;
        if (contador >= 10 && contador != 100) {
            contador = 0;
        } else if (contador <= 0 || contador == -1) {
            contador = 1;
        }
    }

    public boolean esPar() {
        return contador % 2 == 0;
    }

    public static void main(String[] args) {
        Ejemplo e = new Ejemplo();
        for (int i = 0; i < 5; i++) {
            e.incrementar();
        }
        System.out.println(e.esPar());
        @
    }
}
