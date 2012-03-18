
import java.math.BigInteger;

public class Solution {
    public static void main(String[] args) throws Exception {
        java.io.BufferedReader stdin = new java.io.BufferedReader(new java.io.InputStreamReader(System.in));

        int t = Integer.parseInt(stdin.readLine());

        for (; t != 0; --t) {
            int n = Integer.parseInt(stdin.readLine());

            String l = stdin.readLine();

            String[] k = l.split(" ");

            int[] c = new int[n];

            for (int i = 0; i != n; ++i) {
                c[i] = (Integer.parseInt(k[i]));
            }

            System.out.println(calcComb(c).mod(BigInteger.valueOf(1000000007L)));
        }
    }

    private static BigInteger calcComb(int[] cards) {
        BigInteger[] freqs = buildFreq(cards);

        BigInteger result = BigInteger.ONE;

        BigInteger remainder = BigInteger.ZERO;

        for (int i = 0; i != freqs.length - 1; ++i) {
            BigInteger opts = remainder.add(freqs[i]);

            if (opts.compareTo(BigInteger.ZERO) == 0) {
                return BigInteger.ZERO;
            }

            result = result.multiply(opts);

            remainder = opts.subtract(BigInteger.ONE);
        }

        return result;
    }
    
    private static BigInteger[] buildFreq(int[] cards) {
        BigInteger[] freqs = new BigInteger[cards.length + 1];

        for (int i = 0; i != cards.length + 1; ++i) {
            freqs[i] = BigInteger.ZERO;
        }

        for (int i = 0; i != cards.length; ++i) {
            freqs[cards[i]] = freqs[cards[i]].add(BigInteger.ONE);
        }

        return freqs;
    }
}

