
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Solution {
    public static void main(String[] args) throws Exception {
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));

        int t = Integer.parseInt(stdin.readLine());

        for (; t != 0; --t) {
            int n = Integer.parseInt(stdin.readLine());

            System.out.println(calcComb(stdin, n).mod(BigInteger.valueOf(1000000007L)));
        }
    }

    private static BigInteger calcComb(BufferedReader r, int n) throws Exception {
        BigInteger result = BigInteger.ONE;
        BigInteger opts = BigInteger.ZERO;
        int current = 0;

        for (int i = 0; i != n; ++i) {
            StringBuffer st = new StringBuffer();

            char c;

            while (isDigit(c = (char) r.read())) {
                st.append(c);
            }

            int num = Integer.parseInt(st.toString());

            if (i == (n - 1)) {
                boolean later;

                if (current == num) {
                    opts = opts.add(BigInteger.ONE);
                    later = false;
                } else {
                    later = true;
                }

                result = result.multiply(opts);

                while (current < num) {
                    opts = opts.subtract(BigInteger.ONE);

                    if (opts.compareTo(BigInteger.ZERO) == 0) {
                        return BigInteger.ZERO;
                    }

                    result = result.multiply(opts);

                    ++current;
                }

                if (later) {
                    opts = opts.add(BigInteger.ONE);
                } else {
                    opts = opts.subtract(BigInteger.ONE);
                }

                while (current < (n - 1)) {
                    if (opts.compareTo(BigInteger.ZERO) == 0) {
                        return BigInteger.ZERO;
                    }

                    result = result.multiply(opts);

                    opts = opts.subtract(BigInteger.ONE);

                    ++current;
                }
            } else if (num == current) {
                opts = opts.add(BigInteger.ONE);
            } else {
                result = result.multiply(opts);

                while (current < num) {
                    opts = opts.subtract(BigInteger.ONE);

                    if (opts.compareTo(BigInteger.ZERO) == 0) {
                        return BigInteger.ZERO;
                    }
                    
                    result = result.multiply(opts);

                    ++current;
                }

                opts = opts.add(BigInteger.ONE);
            }
        }

        return result;
    }

    private static boolean isDigit(char c) {
        return (c >= '0') && (c <= '9');
    }
}

