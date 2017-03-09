public final class Murmur3 {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("usage: java Murmur3 A_STRING_TO_HASH");
        } else {
            System.out.println(hash(args[0]));
        }
    }

    public static int hash(CharSequence data) {
        final int c1 = 0xcc9e2d51;
        final int c2 = 0x1b873593;
        int h1 = 0;
        int pos = 0;
        int end = data.length();
        int k1 = 0;
        int k2 = 0;
        int shift = 0;
        int bits = 0;
        int nBytes = 0;
        while (pos < end) {
            int code = data.charAt(pos++);
            if (code < 0x80) {
                k2 = code;
                bits = 8;
            }
            else if (code < 0x800) {
                k2 = (0xC0 | (code >> 6))
                    | ((0x80 | (code & 0x3F)) << 8);
                bits = 16;
            }
            else if (code < 0xD800 || code > 0xDFFF || pos>=end) {
                k2 = (0xE0 | (code >> 12))
                    | ((0x80 | ((code >> 6) & 0x3F)) << 8)
                    | ((0x80 | (code & 0x3F)) << 16);
                bits = 24;
            } else {
                int utf32 = (int) data.charAt(pos++);
                utf32 = ((code - 0xD7C0) << 10) + (utf32 & 0x3FF);
                k2 = (0xff & (0xF0 | (utf32 >> 18)))
                    | ((0x80 | ((utf32 >> 12) & 0x3F))) << 8
                    | ((0x80 | ((utf32 >> 6) & 0x3F))) << 16
                    |  (0x80 | (utf32 & 0x3F)) << 24;
                bits = 32;
            }
            k1 |= k2 << shift;
            shift += bits;
            if (shift >= 32) {
                k1 *= c1;
                k1 = (k1 << 15) | (k1 >>> 17);
                k1 *= c2;
                h1 ^= k1;
                h1 = (h1 << 13) | (h1 >>> 19);
                h1 = h1*5+0xe6546b64;
                shift -= 32;
                if (shift != 0) {
                    k1 = k2 >>> (bits-shift);
                } else {
                    k1 = 0;
                }
                nBytes += 4;
            }
        }
        if (shift > 0) {
            nBytes += shift >> 3;
            k1 *= c1;
            k1 = (k1 << 15) | (k1 >>> 17);
            k1 *= c2;
            h1 ^= k1;
        }
        h1 ^= nBytes;
        h1 ^= h1 >>> 16;
        h1 *= 0x85ebca6b;
        h1 ^= h1 >>> 13;
        h1 *= 0xc2b2ae35;
        h1 ^= h1 >>> 16;
        return h1;
    }
}
