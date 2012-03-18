
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.TreeSet;

public class Solution {
    private static final int F_ORDER_ID = 0;
    private static final int F_DEAL_ID = 1;
    private static final int F_EMAIL = 2;
    private static final int F_ADDR_STREET = 3;
    private static final int F_ADDR_CITY = 4;
    private static final int F_ADDR_STATE = 5;
    private static final int F_ADDR_ZIP = 6;
    private static final int F_CCN = 7;

    private static final int CASE_1 = 1;
    private static final int CASE_2 = 2;

    private static HashMap<String, HashMap<String, ArrayList<Integer>>> case1;
    private static HashMap<String, HashMap<String, ArrayList<Integer>>> case2;
    private static HashMap<Integer, Boolean> fraudulentDeals;

    public static void main(String[] args) throws IOException {
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(stdin.readLine());

        case1 = new HashMap<String, HashMap<String, ArrayList<Integer>>>();
        case2 = new HashMap<String, HashMap<String, ArrayList<Integer>>>();
        fraudulentDeals = new HashMap<Integer, Boolean>();

        for (; n != 0; --n) {
            String line = stdin.readLine().toLowerCase();

            String[] fields = line.split(",");

            normalize(fields);

            organize(case1, fields, CASE_1);
            organize(case2, fields, CASE_2);
        }

        TreeSet<Integer> fraudOrderIds = new TreeSet(fraudulentDeals.keySet());

        Iterator<Integer> i = fraudOrderIds.iterator();

        boolean first = true;

        while (i.hasNext()) {
            Integer orderId = i.next();

            if (first) {
                first = false;
            } else {
                System.out.print(",");
            }

            System.out.print(orderId);
        }

        System.out.println();
    }

    private static void normalize(String[] fields) {
        /*
        for (int i = 0; i != fields.length; ++i) {
            fields[i] = fields[i].trim();
        }
         *
         */

        fields[F_EMAIL] = normalizeEmail(fields[F_EMAIL]);
        fields[F_ADDR_STREET] = normalizeAddrStreet(fields[F_ADDR_STREET]);
        fields[F_ADDR_CITY] = normalizeWhitespace(fields[F_ADDR_CITY]);
        fields[F_ADDR_STATE] = normalizeAddrState(fields[F_ADDR_STATE]);
        fields[F_ADDR_ZIP] = normalizeNumeric(fields[F_ADDR_ZIP]);
        fields[F_CCN] = normalizeNumeric(fields[F_CCN]);
    }

    private static String normalizeEmail(String email) {
        String[] cmp = email.split("@", 2);

        cmp[0] = cmp[0].replaceAll("(\\.|\\+.*)", "");

        return cmp[0].concat("@").concat(cmp[1]);
    }

    private static String normalizeAddrStreet(String street) {
        String[] cmps = normalizeWhitespace(street).split(" ");

        for (int i = 0; i != cmps.length; ++i) {
            cmps[i] = normalizeAddrStreetComponent(cmps[i]);
        }

        StringBuilder res = new StringBuilder();

        boolean first = true;

        for (int i = 0; i != cmps.length; ++i) {
            if (! first) {
                res.append(" ");
            } else {
                first = false;
            }
            
            res.append(cmps[i]);
        }

        return res.toString();
    }

    private static String normalizeAddrStreetComponent(String cmp) {
        if (cmp.contentEquals("street")) {
            return "st.";
        } else if (cmp.contentEquals("road")) {
            return "rd.";
        }

        return cmp;
    }

    private static String normalizeAddrState(String state) {
        if (state.contentEquals("california")) {
            return "ca";
        } else if (state.contentEquals("illinois")) {
            return "il";
        } else if (state.contentEquals("new york")) {
            return "ny";
        }

        return state;
    }

    private static String normalizeWhitespace(String str) {
        return str;
        //return str.replaceAll("\\W+", " ");
    }

    private static String normalizeNumeric(String str) {
        return str;
        //return str.replaceAll("[^0-9]", " ");
    }

    private static void organize(HashMap<String, HashMap<String, ArrayList<Integer>>> cs, String[] fields, int type) {
        String match;

        if (type == CASE_1) {
            match = getDealIdAndEmail(fields);
        } else {
            match = getDealIdAndAddress(fields);
        }

        String diff = fields[F_CCN];

        if (cs.containsKey(match)) {
            if (cs.get(match).size() > 1) {
                fraudulentDeals.put(Integer.parseInt(fields[F_ORDER_ID]), Boolean.TRUE);
            } else {
                if (cs.get(match).containsKey(diff)) {
                    cs.get(match).get(diff).add(Integer.parseInt(fields[F_ORDER_ID]));
                } else {
                    Iterator<ArrayList<Integer>> i = cs.get(match).values().iterator();

                    while (i.hasNext()) {
                        ArrayList<Integer> al = i.next();

                        Iterator<Integer> j = al.iterator();

                        while (j.hasNext()) {
                            Integer orderId = j.next();

                            fraudulentDeals.put(orderId, Boolean.TRUE);
                        }
                    }

                    fraudulentDeals.put(Integer.parseInt(fields[F_ORDER_ID]), Boolean.TRUE);

                    cs.get(match).put(diff, new ArrayList<Integer>());
                }
            }
        } else {
            ArrayList<Integer> newal = new ArrayList<Integer>();

            newal.add(Integer.parseInt(fields[F_ORDER_ID]));

            HashMap<String, ArrayList<Integer>> newhm = new HashMap<String, ArrayList<Integer>>();

            newhm.put(diff, newal);

            cs.put(match, newhm);
        }
    }

    private static String getDealIdAndEmail(String[] fields) {
        StringBuilder sb = new StringBuilder();

        sb.append(fields[F_DEAL_ID]).append("+").append(fields[F_EMAIL]);

        return sb.toString();
    }

    private static String getDealIdAndAddress(String[] fields) {
        StringBuilder sb = new StringBuilder();

        sb.append(fields[F_DEAL_ID]).append("+").append(fields[F_ADDR_STREET]).append("+").append(fields[F_ADDR_CITY]).append("+").append(fields[F_ADDR_STATE]).append(fields[F_ADDR_ZIP]);

        return sb.toString();
    }
}
