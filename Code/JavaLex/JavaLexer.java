import java.util.regex.*;
import java.util.*;
import java.io.*;
import java.nio.file.*;

public class JavaLexer {

    enum TokenType {
        JAVADOC, BLOCKCOMMENT, LINECOMMENT,
        STRINGLIT, CHARLIT,
        FLOATLIT, HEXADECIMALLIT, BINARYLIT, OCTALLIT, INTEGERLIT,
        KEYWORD, IDENTIFIER,
        OPERATOR, SEPARATOR,
        WHITESPACE, UNKNOWN
    }

    record Token(TokenType type, String lexeme, int line, int column) {
        public String toString() {
            return String.format("[L%-3d C%-3d] %-15s -> \"%s\"", line, column, type, lexeme);
        }
    }

    static final String KW_PATTERN =
            "\\b(abstract|assert|boolean|break|byte|case|catch|char|" +
            "class|const|continue|default|do|double|else|enum|extends|" +
            "final|finally|float|for|if|implements|import|instanceof|" +
            "int|interface|long|new|package|private|protected|public|" +
            "return|short|static|super|switch|synchronized|this|throw|" +
            "throws|try|void|volatile|while|true|false|null)\\b";

    static final Pattern MASTER = Pattern.compile(
            "(?<JAVADOC>/\\*\\*[\\s\\S]*?\\*/)|" +
            "(?<BLOCKCOMMENT>/\\*[\\s\\S]*?\\*/)|" +
            "(?<LINECOMMENT>//[^\\n]*)|" +
            "(?<STRINGLIT>\"([^\"\\\\]|\\\\.)*\")|" +
            "(?<CHARLIT>'([^'\\\\]|\\\\.)')|" +
            "(?<FLOATLIT>[0-9][0-9_]*\\.[0-9][0-9_]*([eE][+-]?[0-9]+)?[fFdD]?)|" +
            "(?<HEXADECIMALLIT>0[xX][0-9a-fA-F][0-9a-fA-F_]*[lL]?)|" +
            "(?<BINARYLIT>0[bB][01][01_]*[lL]?)|" +
            "(?<OCTALLIT>0[0-7]+[lL]?)|" +
            "(?<INTEGERLIT>0|[1-9][0-9_]*[lL]?)|" +
            "(?<KEYWORD>" + KW_PATTERN + ")|" +
            "(?<IDENTIFIER>[a-zA-Z_$][a-zA-Z0-9_$]*)|" +
            "(?<OPERATOR>==|!=|<=|>=|&&|\\|\\||<<|>>>|>>|\\+\\+|--|" +
            "\\+=|-=|\\*=|/=|%=|&=|\\|=|\\^=|<<=|>>=|[+\\-*/%<>=!&|^~?:])|" +
            "(?<SEPARATOR>[(){}\\[\\];,.])|" +
            "(?<WHITESPACE>[ \\t\\r\\n]+)",
            Pattern.MULTILINE
    );

    static List<Token> tokens = new ArrayList<>();
    static List<String> errores = new ArrayList<>();

    public static List<Token> tokenize(String source) {
        tokens.clear();
        errores.clear();
        Matcher m = MASTER.matcher(source);
        int line = 1, pos = 0, lineStart = 0;

        while (m.find()) {
            // caracteres no reconocidos: recuperacion tipo panic (avanzar y seguir)
            if (m.start() > pos) {
                String illegal = source.substring(pos, m.start());
                for (int i = 0; i < illegal.length(); i++) {
                    int col = (pos + i) - lineStart + 1;
                    char c = illegal.charAt(i);
                    if (c == '\n') { line++; lineStart = pos + i + 1; continue; }
                    errores.add(String.format(
                        "Error lexico [L%d, C%d]: caracter ilegal '%c' (U+%04X)",
                        line, col, c, (int) c));
                    tokens.add(new Token(TokenType.UNKNOWN, String.valueOf(c), line, col));
                }
            }

            int col = pos == m.start() ? m.start() - lineStart + 1 : m.start() - lineStart + 1;

            if (m.group("WHITESPACE") != null) {
                String ws = m.group("WHITESPACE");
                for (int i = 0; i < ws.length(); i++) {
                    if (ws.charAt(i) == '\n') { line++; lineStart = m.start() + i + 1; }
                }
            } else if (m.group("JAVADOC") != null) {
                tokens.add(new Token(TokenType.JAVADOC, m.group(), line, col));
                actualizaLinea(m.group(), line, lineStart);
                line += contarSaltos(m.group());
            } else if (m.group("BLOCKCOMMENT") != null) {
                tokens.add(new Token(TokenType.BLOCKCOMMENT, m.group(), line, col));
                line += contarSaltos(m.group());
            } else if (m.group("LINECOMMENT") != null) {
                tokens.add(new Token(TokenType.LINECOMMENT, m.group(), line, col));
            } else if (m.group("STRINGLIT") != null) {
                tokens.add(new Token(TokenType.STRINGLIT, m.group(), line, col));
            } else if (m.group("CHARLIT") != null) {
                tokens.add(new Token(TokenType.CHARLIT, m.group(), line, col));
            } else if (m.group("FLOATLIT") != null) {
                tokens.add(new Token(TokenType.FLOATLIT, m.group(), line, col));
            } else if (m.group("HEXADECIMALLIT") != null) {
                tokens.add(new Token(TokenType.HEXADECIMALLIT, m.group(), line, col));
            } else if (m.group("BINARYLIT") != null) {
                tokens.add(new Token(TokenType.BINARYLIT, m.group(), line, col));
            } else if (m.group("OCTALLIT") != null) {
                tokens.add(new Token(TokenType.OCTALLIT, m.group(), line, col));
            } else if (m.group("INTEGERLIT") != null) {
                tokens.add(new Token(TokenType.INTEGERLIT, m.group(), line, col));
            } else if (m.group("KEYWORD") != null) {
                tokens.add(new Token(TokenType.KEYWORD, m.group(), line, col));
            } else if (m.group("IDENTIFIER") != null) {
                tokens.add(new Token(TokenType.IDENTIFIER, m.group(), line, col));
            } else if (m.group("OPERATOR") != null) {
                tokens.add(new Token(TokenType.OPERATOR, m.group(), line, col));
            } else if (m.group("SEPARATOR") != null) {
                tokens.add(new Token(TokenType.SEPARATOR, m.group(), line, col));
            }
            pos = m.end();
        }
        return tokens;
    }

    static int contarSaltos(String s) {
        int n = 0;
        for (char c : s.toCharArray()) if (c == '\n') n++;
        return n;
    }

    static void actualizaLinea(String s, int line, int lineStart) { /* solo referencia, no usado */ }

    public static void main(String[] args) throws IOException {
        String source;
        if (args.length > 0) {
            source = Files.readString(Path.of(args[0]));
        } else {
            source = """
                /** JavaDoc comment */
                public class Prueba {
                    public static void main(String[] args) {
                        int x = 0xFF;    // hex
                        double pi = 3.14;
                        String s = "mundo";
                        if (x == 255 && pi > 0.0) { x++; }
                        @  // caracter ilegal intencional
                    }
                }
                """;
        }

        List<Token> resultado = tokenize(source);
        Map<TokenType, Integer> frecuencia = new EnumMap<>(TokenType.class);

        for (Token t : resultado) {
            if (t.type() != TokenType.WHITESPACE) System.out.println(t);
            frecuencia.merge(t.type(), 1, Integer::sum);
        }

        if (!errores.isEmpty()) {
            System.out.println("\n--- Errores lexicos ---");
            errores.forEach(System.out::println);
        }

        System.out.println("\n--- Tabla de frecuencia de tokens ---");
        for (var e : frecuencia.entrySet()) {
            System.out.printf("%-15s : %d%n", e.getKey(), e.getValue());
        }
    }
}
